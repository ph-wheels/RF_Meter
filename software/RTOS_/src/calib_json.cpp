#include "calib_json.h"
#include "config.h"        // SERIAL2_UART
#include <ArduinoJson.h>   // PlatformIO: lib_deps = bblanchon/ArduinoJson@^7
#include <Preferences.h>   // ESP32 Arduino wrapper around NVS
#include <string.h>
#include <cmath>          // std::isfinite

static const char *kNvsNamespace = "calib";
static const char *kNvsKey       = "coeffs";
static const char *kNvsKeyMCorr  = "mcorr";
static const char *kNvsKeyZFloor  = "zfloor";

bool calib_nvs_save(const CalibTable &table)
{
    Preferences prefs;
    if (!prefs.begin(kNvsNamespace, /*readOnly=*/false)) {
        Serial.println("[CALIB] NVS open (write) failed");
        return false;
    }
    // Only the coefficient data itself is persisted, not the transient
    // `valid` flag - a successful load always implies valid=true, and this
    // keeps the stored format independent of struct fields like `valid`
    // that could change later without meaning the stored data is invalid.
    size_t written  = prefs.putBytes(kNvsKey, table.ch, sizeof(table.ch));
    // M_A/B/C corrections, saved under their OWN key so adding/changing
    // them never invalidates (or requires resending) the polynomial data
    // above, and vice versa.
    size_t mwritten = prefs.putBytes(kNvsKeyMCorr, table.m_correction, sizeof(table.m_correction));
    // Z_A/B/C measurement floors: own key again, same reasoning.
    size_t zwritten = prefs.putBytes(kNvsKeyZFloor, table.z_floor, sizeof(table.z_floor));
    prefs.end();

    if (written != sizeof(table.ch)) {
        Serial.println("[CALIB] NVS write incomplete/failed (polynomial)");
        return false;
    }
    if (mwritten != sizeof(table.m_correction)) {
        // Not fatal to the overall save - the polynomial data (the part
        // that matters most, and the hardest to re-derive) did save fine.
        Serial.println("[CALIB] NVS write incomplete/failed (M_A/B/C corrections)");
    }
    if (zwritten != sizeof(table.z_floor)) {
        Serial.println("[CALIB] NVS write incomplete/failed (Z_A/B/C floors)");
    }
    Serial.println("[CALIB] table saved to NVS");
    return true;
}

bool calib_nvs_load(CalibTable &out)
{
    Preferences prefs;
    if (!prefs.begin(kNvsNamespace, /*readOnly=*/true)) {
        // Normal on first-ever boot - namespace doesn't exist until the
        // first successful save creates it.
        Serial.println("[CALIB] no NVS namespace yet (nothing saved so far)");
        return false;
    }
    size_t stored = prefs.getBytesLength(kNvsKey);
    if (stored != sizeof(out.ch)) {
        prefs.end();
        Serial.printf("[CALIB] NVS entry missing or wrong size (%u, expected %u)\n",
                      (unsigned)stored, (unsigned)sizeof(out.ch));
        return false;
    }
    prefs.getBytes(kNvsKey, out.ch, sizeof(out.ch));

    // M_A/B/C corrections: optional/newer than the polynomial data above -
    // a missing or wrong-sized entry (e.g. calibration saved before this
    // feature existed, or never sent) just means "no corrections yet",
    // defaulting to all-zero (no-op per the struct's schema), NOT a load
    // failure - the polynomial data on its own is still perfectly usable.
    size_t mstored = prefs.getBytesLength(kNvsKeyMCorr);
    if (mstored == sizeof(out.m_correction)) {
        prefs.getBytes(kNvsKeyMCorr, out.m_correction, sizeof(out.m_correction));
    } else {
        memset(out.m_correction, 0, sizeof(out.m_correction));
    }

    // Z_A/B/C floors: same treatment. This one matters more than it looks:
    // `out` is an uninitialised local in calib_json_start(), so a missing
    // entry (calibration saved before floors existed) MUST be zero-filled
    // here, or garbage would be subtracted from every reading.
    size_t zstored = prefs.getBytesLength(kNvsKeyZFloor);
    if (zstored == sizeof(out.z_floor)) {
        prefs.getBytes(kNvsKeyZFloor, out.z_floor, sizeof(out.z_floor));
    } else {
        memset(out.z_floor, 0, sizeof(out.z_floor));
    }

    prefs.end();
    out.valid = true;
    Serial.println("[CALIB] table loaded from NVS");
    return true;
}

void calib_nvs_erase()
{
    Preferences prefs;
    if (prefs.begin(kNvsNamespace, false)) {
        prefs.remove(kNvsKey);
        prefs.remove(kNvsKeyMCorr);
        prefs.remove(kNvsKeyZFloor);
        prefs.end();
        Serial.println("[CALIB] NVS entries erased");
    }
}

static CalibTable        g_calib_table;
static SemaphoreHandle_t g_calib_mutex;
static HardwareSerial   *g_calib_serial = nullptr;

static const char *kChannelNames[3] = {"A", "B", "C"};

static const char *kMKeys[3] = {"M_A", "M_B", "M_C"};
static const char *kZKeys[3] = {"Z_A", "Z_B", "Z_C"};

// Strict numeric parse for one coefficient entry. The JSON schema stores
// each value as a STRING (quoted), and ArduinoJson's JsonVariant::as<float>()
// on a string defers to strtod()-style parsing - which does NOT tolerate
// whitespace between a sign and its digits. A string like "- 2.164132"
// (a stray space after the minus sign) parses as "no digits found",
// silently returning 0.0 with no error at all - exactly how one real
// coefficient was lost, turning a correct polynomial into one producing
// wildly wrong output with nothing in the log to explain why.
//
// This instead requires the ENTIRE string (ignoring only leading/trailing
// whitespace) to be consumed by the number - anything else, stray
// internal whitespace included, is rejected rather than silently
// defaulting to 0.0.
static bool parse_coeff_strict(JsonVariant v, float &out, const char *context)
{
    const char *s = v.as<const char *>();
    if (s == nullptr) {
        // Not a string (e.g. a genuine bare JSON number, which the schema
        // doesn't currently use but costs nothing to accept) - fall back
        // to ArduinoJson's own conversion for that case.
        out = v.as<float>();
        return true;
    }
    while (*s == ' ' || *s == '\t') s++; // allow leading whitespace
    char  *end = nullptr;
    double val = strtod(s, &end);
    if (end == s) {
        Serial.printf("[CALIB] '%s': '%s' is not a valid number\n", context, s);
        return false;
    }
    while (*end == ' ' || *end == '\t') end++; // allow trailing whitespace
    if (*end != '\0') {
        Serial.printf("[CALIB] '%s': '%s' has unexpected characters after the number "
                      "(stray whitespace inside the value?)\n", context, s);
        return false;
    }
    out = (float)val;
    return true;
}

// `io` is BOTH the merge base and the output: the caller seeds it with
// whatever's currently live (see calib_json_task()) before calling this,
// so any key this particular JSON message doesn't include is left exactly
// as it was, rather than becoming garbage or getting reset to zero.
//
// The 9 polynomial keys (A_1.."C_3) are still strictly all-or-nothing, as
// before: if ANY of them appear, ALL 9 must be present and valid, or the
// WHOLE message is rejected - a partial set is exactly the kind of
// truncated/incomplete send this guard exists to catch. M_A/M_B/M_C are
// each independently optional on top of that (see calib_json.h).
static bool parse_calib_json(const char *json, size_t len, CalibTable &io)
{
    JsonDocument doc; // ArduinoJson v7: auto-sized, no manual capacity math
    DeserializationError err = deserializeJson(doc, json, len);
    if (err) {
        Serial.printf("[CALIB] JSON parse error: %s\n", err.c_str());
        return false;
    }

    int poly_keys_present = 0;
    for (int c = 0; c < 3; c++) {
        for (int s = 0; s < 3; s++) {
            char key[8];
            snprintf(key, sizeof(key), "%s_%d", kChannelNames[c], s + 1);
            if (!doc[key].isNull()) poly_keys_present++;
        }
    }
    if (poly_keys_present != 0 && poly_keys_present != 9) {
        Serial.printf("[CALIB] partial polynomial update rejected (%d/9 keys present - need all 9 or none)\n",
                      poly_keys_present);
        return false;
    }

    if (poly_keys_present == 9) {
        for (int c = 0; c < 3; c++) {
            for (int s = 0; s < 3; s++) {
                char key[8];
                snprintf(key, sizeof(key), "%s_%d", kChannelNames[c], s + 1);
                JsonArray arr = doc[key]["value"].as<JsonArray>();
                if (arr.isNull() || arr.size() < 5) {
                    Serial.printf("[CALIB] '%s.value' missing or too short\n", key);
                    return false;
                }
                int i = 0;
                for (JsonVariant v : arr) {
                    if (i >= 5) break;
                    char context[16];
                    snprintf(context, sizeof(context), "%s[%d]", key, i);
                    if (!parse_coeff_strict(v, io.ch[c].coeffs[s][i], context)) {
                        return false; // malformed coefficient - reject the WHOLE message
                    }
                    i++;
                }
            }
        }
    }

    bool any_m_present = false;
    for (int c = 0; c < 3; c++) {
        JsonVariant entry = doc[kMKeys[c]];
        if (entry.isNull()) continue; // not in this message - leave io's existing value alone
        JsonArray arr = entry["value"].as<JsonArray>();
        if (arr.isNull() || arr.size() < 3) {
            Serial.printf("[CALIB] '%s.value' missing or too short (need 3)\n", kMKeys[c]);
            return false;
        }
        int i = 0;
        for (JsonVariant v : arr) {
            if (i >= 3) break;
            char context[16];
            snprintf(context, sizeof(context), "%s[%d]", kMKeys[c], i);
            if (!parse_coeff_strict(v, io.m_correction[c][i], context)) {
                return false; // malformed correction value - reject the WHOLE message
            }
            i++;
        }
        any_m_present = true;
    }

    // Z_A/Z_B/Z_C measurement floors, in raw counts. Same shape and rules as
    // M_A/M_B/M_C (independently optional, anything absent is left as it was)
    // with one addition: the value must be a plausible raw 24-bit code. The
    // strict parser above still accepts "nan"/"inf" (strtod does), and a floor
    // of NaN would silently blank the readout - so reject those, negatives
    // (which would ADD to the reading), and anything past full scale.
    bool any_z_present = false;
    for (int c = 0; c < 3; c++) {
        JsonVariant entry = doc[kZKeys[c]];
        if (entry.isNull()) continue;
        JsonArray arr = entry["value"].as<JsonArray>();
        if (arr.isNull() || arr.size() < 3) {
            Serial.printf("[CALIB] '%s.value' missing or too short (need 3)\n", kZKeys[c]);
            return false;
        }
        int i = 0;
        for (JsonVariant v : arr) {
            if (i >= 3) break;
            char context[16];
            snprintf(context, sizeof(context), "%s[%d]", kZKeys[c], i);
            float z;
            if (!parse_coeff_strict(v, z, context)) {
                return false; // malformed floor value - reject the WHOLE message
            }
            if (!std::isfinite(z) || z < 0.0f || z > 16777215.0f) {
                Serial.printf("[CALIB] '%s' = %g is not a raw 24-bit code (need 0..16777215)\n",
                              context, (double)z);
                return false;
            }
            io.z_floor[c][i] = z;
            i++;
        }
        any_z_present = true;
    }

    if (poly_keys_present == 0 && !any_m_present && !any_z_present) {
        Serial.println("[CALIB] JSON contained none of the recognized keys (A_1..C_3, M_A..M_C or Z_A..Z_C)");
        return false;
    }

    // A corrections-only message (M_A/B/C or Z_A/B/C, no polynomial keys) is only
    // meaningful if there's already a valid polynomial in `io` (seeded
    // from the live table) to correct. Without this check, sending
    // corrections right after an erase - or on a board that never
    // received a polynomial at all - would mark an all-zero/garbage `ch`
    // as "valid" and get it PERSISTED to NVS, silently overwriting
    // whatever was there. This is also why "erase didn't help" is
    // plausible: the very next corrections-only send after an erase could
    // re-poison it the same way.
    if (poly_keys_present == 0 && !io.valid) {
        Serial.println("[CALIB] rejected: M_A/B/C or Z_A/B/C sent but no valid polynomial loaded yet to correct");
        return false;
    }

    io.valid = true;
    return true;
}

static void calib_json_task(void *)
{
    // Brace-depth framing: accumulate bytes until the braces balance back
    // to 0, marking one complete top-level JSON object. Robust to
    // whatever whitespace/newlines the sender uses, and to the object
    // arriving split across several serial reads - unlike readStringUntil,
    // which assumes a specific line-ending convention.
    static const size_t   kBufSize      = 2048; // ~10x this payload's size, cheap margin
    static const uint32_t kIdleResetMs  = 300;  // reset a partial object after this much silence
    static char buf[kBufSize];
    size_t len   = 0;
    int    depth = 0;
    bool   inString = false;
    bool   escaped  = false;
    TickType_t lastByteTick = 0;

    for (;;) {
        int c = g_calib_serial->read();
        if (c < 0) {
            // No byte available right now. If we're sitting on a partial
            // object and it's gone quiet for a while, that was noise or a
            // truncated send - drop it and wait for a fresh start, rather
            // than requiring the buffer to fill all the way to kBufSize
            // before recovering (which is what was happening: continuous
            // line noise filling the buffer over and over with the braces
            // never balancing, most likely from an unconnected/floating
            // RX pin or a baud mismatch on the sender side - worth
            // checking that wiring/baud if this keeps happening).
            if (len > 0 && (xTaskGetTickCount() - lastByteTick) > pdMS_TO_TICKS(kIdleResetMs)) {
                // Visible again (was silent before) - a partial object that
                // went quiet without ever completing is exactly what an
                // RX-buffer overflow / dropped-bytes mid-send looks like.
                // The byte count tells us whether this was probably real
                // data cut short (close to your payload's ~500-600 bytes)
                // or just a few stray noise bytes (a handful).
                Serial.printf("[CALIB] partial object abandoned after %ums idle, %u bytes, depth=%d\n",
                              (unsigned)kIdleResetMs, (unsigned)len, depth);
                len = 0; depth = 0; inString = false; escaped = false;
            }
            vTaskDelay(pdMS_TO_TICKS(5));
            continue;
        }
        lastByteTick = xTaskGetTickCount();

        if (len < kBufSize) {
            buf[len++] = (char)c;
        } else {
            // Overflowed without ever completing an object - drop and resync
            // rather than parsing garbage or growing unbounded.
            Serial.println("[CALIB] input overflowed buffer, resetting");
            len = 0; depth = 0; inString = false; escaped = false;
            continue;
        }

        // Track string/escape state so a brace INSIDE a quoted string
        // value (none in this schema, but cheap insurance) can't desync
        // the depth count.
        if (inString) {
            if (escaped)        escaped = false;
            else if (c == '\\') escaped = true;
            else if (c == '"')  inString = false;
        } else {
            if (c == '"') {
                inString = true;
            } else if (c == '{') {
                if (depth == 0) {
                    Serial.println("[CALIB] object start detected");
                }
                depth++;
            } else if (c == '}') {
                depth--;
                if (depth == 0) {
                    // Complete top-level object received.
                    CalibTable parsed;
                    // Seed from the CURRENT live table, not a blank one:
                    // parse_calib_json() now merges (any key this message
                    // doesn't include is left as-is), so the merge base
                    // has to be the existing data, not indeterminate/zero
                    // values - otherwise an M_A/B/C-only message would
                    // wipe out the polynomial coefficients it never even
                    // mentioned.
                    xSemaphoreTake(g_calib_mutex, portMAX_DELAY);
                    parsed = g_calib_table;
                    xSemaphoreGive(g_calib_mutex);

                    if (parse_calib_json(buf, len, parsed)) {
                        bool changed;
                        xSemaphoreTake(g_calib_mutex, portMAX_DELAY);
                        changed = !g_calib_table.valid ||
                                  memcmp(&parsed.ch, &g_calib_table.ch, sizeof(parsed.ch)) != 0 ||
                                  memcmp(&parsed.m_correction, &g_calib_table.m_correction,
                                         sizeof(parsed.m_correction)) != 0 ||
                                  memcmp(&parsed.z_floor, &g_calib_table.z_floor,
                                         sizeof(parsed.z_floor)) != 0;
                        g_calib_table = parsed;
                        xSemaphoreGive(g_calib_mutex);
                        Serial.println("[CALIB] table updated");

                        if (changed) {
                            calib_nvs_save(parsed);
                        } else {
                            Serial.println("[CALIB] unchanged from stored value, skipping NVS write");
                        }
                    }
                    len = 0; // ready for the next object
                } else if (depth < 0) {
                    // Unmatched closing brace - stream got out of sync
                    // (e.g. we started mid-object after boot). Resync.
                    depth = 0; len = 0;
                }
            }
        }
    }
}

void calib_json_start(HardwareSerial &serialPort, uint32_t baud,
                       UBaseType_t taskPriority, BaseType_t coreId,
                       uint16_t taskStackBytes)
{
    g_calib_mutex = xSemaphoreCreateMutex();

    // Pre-populate from flash so a valid calibration is available right
    // after boot, even before any fresh serial data has arrived this run.
    CalibTable loaded;
    if (calib_nvs_load(loaded)) {
        xSemaphoreTake(g_calib_mutex, portMAX_DELAY);
        g_calib_table = loaded;
        xSemaphoreGive(g_calib_mutex);

        // Diagnostic: print exactly what NVS actually contained, so a
        // bad/zero/garbage polynomial or correction can be confirmed or
        // ruled out directly from the boot log, rather than inferred
        // indirectly from what the ADC page shows later.
        Serial.println("[CALIB] boot dump:");
        for (int c = 0; c < 3; c++) {
            for (int s = 0; s < 3; s++) {
                const float *a = loaded.ch[c].coeffs[s];
                Serial.printf("  %s_%d: a0=%.6f a1=%.6f a2=%.6f a3=%.6f a4=%.6f  M=%.6f  Z=%.1f\n",
                              kChannelNames[c], s + 1, a[0], a[1], a[2], a[3], a[4],
                              loaded.m_correction[c][s], loaded.z_floor[c][s]);
            }
        }
    } else {
        Serial.println("[CALIB] boot dump: nothing loaded from NVS");
    }

    g_calib_serial = &serialPort;

#ifdef SERIAL2_UART
    // ESP32's default UART RX ring buffer is only 256 bytes. This JSON
    // payload as text runs 500-600+ bytes; if the sender bursts it out
    // faster than our task's polling loop drains it, bytes beyond the
    // default buffer are silently dropped by the driver itself - before
    // Serial2.read() ever sees them, so our code has no way to detect it
    // happened. That's the most likely explanation for "worked once,
    // incomplete other times": a timing race whose outcome varies run to
    // run. setRxBufferSize() MUST be called before begin() - it has no
    // effect afterward.
    g_calib_serial->setRxBufferSize(4096);
    g_calib_serial->begin(baud, SERIAL_8N1, GPIO_NUM_21, GPIO_NUM_22);
    Serial.println("[CALIB] receiving calibration JSON on Serial2 (GPIO21/22)");
#else
    // SERIAL2_UART not defined: `serialPort` here is the main USB Serial,
    // already begin()'d (with its own RX buffer already bumped - see
    // main.cpp's setup()) before calib_json_start() was called. Calling
    // setRxBufferSize()/begin() AGAIN here would be redundant at best -
    // and if it ever used Serial2's GPIO21/22 pin assignment on the
    // WRONG serial object, it would silently break the USB connection
    // entirely by reassigning UART0's pins out from under it. So in this
    // mode we deliberately do neither; `g_calib_serial` just reads
    // whatever's already flowing in on the port the caller set up.
    Serial.println("[CALIB] receiving calibration JSON on the main USB Serial (shared with the debug log)");
#endif

    xTaskCreatePinnedToCore(calib_json_task, "calib_json", taskStackBytes,
                             nullptr, taskPriority, nullptr, coreId);
}

bool calib_json_get(CalibTable &out)
{
    if (g_calib_mutex == nullptr) return false;
    xSemaphoreTake(g_calib_mutex, portMAX_DELAY);
    bool ok = g_calib_table.valid;
    if (ok) out = g_calib_table;
    xSemaphoreGive(g_calib_mutex);
    return ok;
}
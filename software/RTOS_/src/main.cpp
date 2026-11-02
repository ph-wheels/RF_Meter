// =============================================================================
//  main.cpp  –  FreeRTOS Rotary Encoder + ILI9341 320×480 SPI LCD + Touch
//              + MAX11270 24-bit ADC
// =============================================================================
//
//  Wiring
//  ──────
//  Rotary encoder (A/B Gray-code)    ESP32
//    A (CLK) ────────────────────────► GPIO 33
//    B (DT)  ────────────────────────► GPIO 34  *** input-only pin ***
//    SW      ────────────────────────► GPIO 35  *** input-only pin ***
//    GND  ──────────────────────────► GND
//    VCC  ──────────────────────────► 3.3V
//  Pull-ups for CLK/DT/SW are provided on-board (external), not via the
//  ESP32's internal pull-ups — GPIO34/35 don't have internal pull resistors
//  anyway, so this is required regardless.
//
//  ILI9341 + XPT2046 module          ESP32 (VSPI shared bus)
//    VCC  ──────────────────────────► 3.3V
//    GND  ──────────────────────────► GND
//    CS   ──────────────────────────► GPIO 15
//    RST  ──────────────────────────► GPIO 25
//    DC   ──────────────────────────► GPIO 2
//    MOSI ──────────────────────────► GPIO 23
//    SCK  ──────────────────────────► GPIO 18
//    MISO ──────────────────────────► GPIO 19
//    T_CS ──────────────────────────► GPIO 13
//    T_IRQ──────────────────────────► GPIO 36
//
//  MAX11270 24-bit ADC               ESP32 (shares the VSPI bus above)
//    VCC   ─────────────────────────► 3.3V
//    GND   ─────────────────────────► GND
//    DIN   (MOSI) ───────────────────► GPIO 23  (shared with TFT/touch)
//    DOUT  (MISO) ───────────────────► GPIO 19  (shared with TFT/touch)
//    SCLK  ─────────────────────────► GPIO 18  (shared with TFT/touch)
//    CSB   ─────────────────────────► GPIO 5
//    RDYB  ─────────────────────────► GPIO 4
//
//  NOTE — GPIO34 and GPIO35 are input-only pins with no internal pull
//  resistors (shared with 36/39). CLK/DT/SW all rely on the on-board
//  external pull-ups mentioned above. GPIO25 is a normal fully capable
//  digital pin and needs no special handling as TFT RST.
//
//  ENC_SW and TFT_RST are defined outside this file (config.h and your
//  TFT_eSPI User_Setup.h respectively) — update those definitions to
//  GPIO 35 and GPIO 25 to match this wiring.
//
//  FreeRTOS tasks
//  ──────────────
//   encoder_task   Core1 P6  — polls ISR delta, updates g_state
//   touch_task     Core0 P3  — reads XPT2046, maps taps to g_state actions
//   ui_task        Core0 P4  — renders display when g_state changes
//   heartbeat      Core0 P1  — blinks LED, logs heap
//   max11270 task  Core? P3  — internal reader task, created by max11270_init()
//   adc_consumer   Core1 P2  — drains ADC sample queue (was "app_task")
//
// =============================================================================

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "config.h"
#include "max11270.h"
#include "calib_json.h"
#include "board_corrections.h"

#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"
#include "adc_dbm.h"
#include "app_settings.h"
#include <math.h>
#include <cmath> // std::isfinite
#include "nvs_flash.h" // nvs_flash_erase()/nvs_flash_init() - see setup()'s temporary diagnostic block

// ─── Global FreeRTOS objects ──────────────────────────────────────────────────
SemaphoreHandle_t g_state_mutex;
// auto_range starts off unless AUTORANGE_DEFAULT_ON, and is never on in RAW mode (see config.h)
AppState g_state = { .counter = 0, .page = PAGE_ADC_GAIN, .brightness = 50, .channel = 0, .range = 0,
                     .auto_range = (ADC_APPLY_CALIBRATION ? AUTORANGE_DEFAULT_ON : 0) };

//define global variable
String input = "-1";

// ─── TFT + sprite + touch ─────────────────────────────────────────────────────
static TFT_eSPI             tft;
static TFT_eSprite          sprite(&tft);
static XPT2046_Touchscreen  touch(TOUCH_CS_PIN, TOUCH_IRQ_PIN);

static int  sprite_h     = 0;
static int  sprite_bands = 0;
static bool use_sprite   = false;

// =============================================================================
//  MAX11270 HAL
//
//  The MAX11270 shares the VSPI bus (MOSI/SCK/MISO) with the display and
//  touch controller; only CSB and RDYB are dedicated to it. Because
//  SPI.beginTransaction()/endTransaction() takes the bus's internal lock,
//  this is safe to interleave with TFT_eSPI/XPT2046 SPI activity from other
//  tasks/cores AS LONG AS those libraries also use SPI.beginTransaction()
//  around their own transfers (TFT_eSPI does this by default when
//  SUPPORT_TRANSACTIONS is enabled in its User_Setup — verify that's the
//  case in your build). If your TFT_eSPI config talks to the display
//  through a different/raw SPI path that bypasses the Arduino SPI class,
//  add an explicit shared mutex around all three peripherals' transfers.
// =============================================================================
// #define ENABLE_CAL_INFO        // show chip calibration data on startup (for debug only, not needed in production)
#define MAX11270_CS_PIN    5   // *** see pin conflict warning at top of file ***
#define MAX11270_RDY_PIN   4   // *** see pin conflict warning at top of file ***
// MOSI = GPIO23, SCK = GPIO18, MISO = GPIO19 — same physical bus as the
// display/touch wiring above; no separate SPI.begin() pins needed for these,
// just the shared SPI.begin(18, 19, 23, -1) call made once in setup().

static const uint32_t MAX11270_SPI_HZ = 4000000; // datasheet max SCLK = 5MHz

void max11270_hal_cs(bool assert_low)
{
    if (assert_low) {
        SPI.beginTransaction(SPISettings(MAX11270_SPI_HZ, MSBFIRST, SPI_MODE0));
        digitalWrite(MAX11270_CS_PIN, LOW);
    } else {
        digitalWrite(MAX11270_CS_PIN, HIGH);
        SPI.endTransaction();
    }
}

uint8_t max11270_hal_spi_xfer(uint8_t tx_byte)
{
    return SPI.transfer(tx_byte);
}

void max11270_hal_delay_ms(uint32_t ms)
{
    // Called only from task context (e.g. during calibration waits in
    // max11270_soft_reset()) — vTaskDelay is the FreeRTOS-correct choice
    // here rather than a blocking Arduino delay().
    vTaskDelay(pdMS_TO_TICKS(ms));
}

bool max11270_hal_rdyb_is_low(void)
{
    return digitalRead(MAX11270_RDY_PIN) == LOW;
}

static max11270_dev_t g_adc;

// PGA gain steps. The gain is not set directly by any control any more: it
// follows the selected range (see "ADC range <-> gain" below and the
// RANGEn_GAIN_STEP constants in config.h).
static const max11270_pga_gain_t kGainSteps[] = {
    MAX11270_PGA_GAIN_1,  MAX11270_PGA_GAIN_2,  MAX11270_PGA_GAIN_4,  MAX11270_PGA_GAIN_8,
    MAX11270_PGA_GAIN_16, MAX11270_PGA_GAIN_32, MAX11270_PGA_GAIN_64, MAX11270_PGA_GAIN_128
};
// Index into kGainSteps of the gain currently applied. Written only by
// range_apply_locked() (and once in setup(), from the range mapping).
static uint8_t gain_step = 0;

// Latest sample, published by adc_consumer_task for the UI to read.
// NOT sourced via xQueuePeek() on g_adc.out_queue: that queue is also
// being actively drained by adc_consumer_task's own xQueueReceive(), which
// wakes and empties each new item almost immediately (every ~8ms at
// 125 SPS). A peek from ui_task only "wins" that race on the rare occasion
// it lands in the brief window before the consumer claims the item -
// which is exactly why the gain page showed a value flash then "---".
// Publishing here removes the race entirely. Declared up here (rather than
// near adc_consumer_task further down) so draw_page_adc_gain(), defined
// earlier in the file, can see it - C++ needs the declaration before use.
static max11270_sample_t g_latest_sample;
static bool              g_latest_sample_valid = false;
static SemaphoreHandle_t g_latest_sample_mutex;
static uint8_t           g_rxflag = 0;

// ─── ADC noise statistics ───────────────────────────────────────────────────
// Lowest / highest / mean raw24 code over the last NOISE_WINDOW_SAMPLES
// samples (config.h). Published by adc_consumer_task together with
// g_latest_sample, under the same mutex, so the bar always describes the
// same moment as the sample on screen.
static_assert(NOISE_WINDOW_SAMPLES >= 2 && NOISE_WINDOW_SAMPLES <= 1000,
              "NOISE_WINDOW_SAMPLES must be 2..1000");
static_assert(NOISE_BAR_FULLSCALE_COUNTS > 0, "NOISE_BAR_FULLSCALE_COUNTS must be > 0");
static_assert(SETTLE_HOLD_MS >= 0 && SETTLE_HOLD_MS <= 10000, "SETTLE_HOLD_MS must be 0..10000");

struct NoiseStats {
    int32_t  lo;     // lowest raw24 in the window
    int32_t  hi;     // highest raw24 in the window
    int32_t  mean;   // integer mean (always between lo and hi)
    uint16_t count;  // samples currently in the window (0..NOISE_WINDOW_SAMPLES)
};
static NoiseStats g_noise = { 0, 0, 0, 0 };

// ─── Battery indicator ──────────────────────────────────────────────────────
#if BATTERY_INDICATOR
static_assert(BATTERY_DIVIDER_RATIO > 0, "BATTERY_DIVIDER_RATIO must be > 0");
static_assert(BATTERY_SMOOTHING >= 1, "BATTERY_SMOOTHING must be >= 1");
static_assert(BATTERY_PRESENT_MIN_MV < BATTERY_EMPTY_MV && BATTERY_EMPTY_MV < BATTERY_FULL_MV,
              "need BATTERY_PRESENT_MIN_MV < BATTERY_EMPTY_MV < BATTERY_FULL_MV");
static_assert(BATTERY_RED_PCT < BATTERY_ORANGE_PCT && BATTERY_ORANGE_PCT < BATTERY_YELLOW_PCT,
              "need BATTERY_RED_PCT < BATTERY_ORANGE_PCT < BATTERY_YELLOW_PCT");

struct BatteryStatus {
    uint16_t mv;     // battery voltage in mV (after the divider ratio, smoothed)
    uint8_t  pct;    // 0..100
    bool     valid;  // false until a believable reading exists
};
// Published by battery_task under g_latest_sample_mutex - the same mutex
// the ADC page already takes to read the latest sample, so reading this
// costs the draw code nothing extra.
static BatteryStatus g_battery = { 0, 0, false };

// Battery millivolts -> percent. The cubic is the one from the earlier
// project (fitted to that cell). Notes on its behaviour:
//  - it reads about 7 % at 3.4 V, so there is a step down to 0 % below
//    BATTERY_EMPTY_MV, as in the original;
//  - it peaks at about 4.205 V and turns DOWN above that, so anything at or
//    above BATTERY_FULL_MV is pinned to 100 % instead of being evaluated;
//  - the result is clamped to 0..100 (the original did not clamp).
static uint8_t battery_percent_from_mv(int32_t mv)
{
    if (mv < BATTERY_EMPTY_MV) return 0;
    if (mv >= BATTERY_FULL_MV) return 100;
    const double v   = mv / 1000.0;
    double       chg = -96.63 * v * v * v + 999.34 * v * v - 3278.71 * v + 3400.59;
    if (chg < 0.0)   chg = 0.0;
    if (chg > 100.0) chg = 100.0;
    return (uint8_t)(chg + 0.5);
}

// One smoothing step: move 1/BATTERY_SMOOTHING of the way from the running
// value towards the new reading. ema_mv < 0 means "no running value yet".
static int32_t battery_smooth(int32_t ema_mv, int32_t new_mv)
{
    if (ema_mv < 0) return new_mv;
    return ema_mv + (new_mv - ema_mv) / BATTERY_SMOOTHING;
}
#endif // BATTERY_INDICATOR

// Sliding window over the most recent GOOD raw codes. Owned by
// adc_consumer_task alone (no locking needed); only the NoiseStats it
// returns is shared.
//
// Settling is TIME based: restart() starts a hold of `hold_ms`, and samples
// that arrive before it ends are simply not added. (It used to skip a fixed
// NUMBER of samples, but samples reach the consumer unevenly - bursts 8 ms
// apart, then holes of ~115 ms - so "4 samples" could mean anything from
// 30 ms to over 400 ms, while the thing being waited for, the signal path
// settling after a gain change, takes a fixed amount of TIME.)
struct NoiseWindow {
    int32_t  buf[NOISE_WINDOW_SAMPLES];
    uint16_t idx;         // next slot to write
    uint16_t count;       // valid samples (0..NOISE_WINDOW_SAMPLES)
    uint32_t hold_until;  // millis() value at which the hold ends

    // Empty the window and ignore samples for the next `hold_ms`.
    void restart(uint32_t now_ms, uint32_t hold_ms)
    {
        idx = 0; count = 0; hold_until = now_ms + hold_ms;
    }

    // True while still inside the hold. Compared as a signed difference, so
    // it stays correct when millis() wraps (every ~49.7 days).
    bool holding(uint32_t now_ms) const { return (int32_t)(now_ms - hold_until) < 0; }

    // Add one sample unless the hold is still running. Returns true if it
    // was added. Because restart() resets idx to 0, the valid entries are
    // always buf[0..count-1], both while the window fills and once it wraps.
    bool add(uint32_t now_ms, int32_t raw)
    {
        if (holding(now_ms)) return false;
        buf[idx] = raw;
        idx = (uint16_t)((idx + 1) % NOISE_WINDOW_SAMPLES);
        if (count < NOISE_WINDOW_SAMPLES) count++;
        return true;
    }

    // Lowest / highest / mean of what is in the window right now.
    NoiseStats stats() const
    {
        NoiseStats s = { 0, 0, 0, count };
        if (count > 0) {
            int64_t sum = 0;
            s.lo = s.hi = buf[0];
            for (uint16_t i = 0; i < count; i++) {
                if (buf[i] < s.lo) s.lo = buf[i];
                if (buf[i] > s.hi) s.hi = buf[i];
                sum += buf[i];
            }
            s.mean = (int32_t)(sum / count);
        }
        return s;
    }
};

// Everything the consumer does with one sample on its way into the noise
// statistics, as one unit so it can be tested without hardware:
//  - a sample flagged DOR is the converter's output CLIPPED at zero: in
//    unipolar mode the code cannot go negative, so when noise pushes the true
//    reading below zero the chip reports 0 and sets the flag. It carries real
//    information ("the reading was at or below 0"), so it is COUNTED AS 0 like
//    any other sample. Throwing those away would bias the average upward -
//    near the noise floor, where 5-12 % of samples are flagged, by 15-40
//    counts, which is worth 0.2-0.4 dB at -55 dBm. (The flag is inferred from
//    behaviour to mean "clipped"; see the MAX11270 datasheet's STAT register.)
//    It is only counted separately, for the log;
//  - everything goes into the window unless the settle hold is running;
//  - the "since change" mean counts exactly the samples the window accepted,
//    and "recent" is the same mean over roughly the last kRecent samples, so a
//    floor that drifts (it did, ~60 counts in the first minute) can be read
//    off as it is NOW instead of as a lifetime average.
struct NoiseFeed {
    enum { kRecent = 256 };     // length of the "recent" average, in samples

    NoiseWindow win;
    int64_t     since_sum = 0;  // sum of accepted samples since begin()
    uint32_t    since_n   = 0;  // how many
    float       recent    = 0;  // running mean over ~the last kRecent samples
    uint32_t    dor_count = 0;  // DOR-flagged samples seen so far (never reset - for the log)

    // A channel / range / attenuator change: empty the window, start the
    // hold, and start both averages afresh.
    void begin(uint32_t now_ms, uint32_t hold_ms)
    {
        win.restart(now_ms, hold_ms);
        since_sum = 0;
        since_n   = 0;
        recent    = 0;
    }

    // Feed one sample; returns the window's stats afterwards (unchanged if
    // the sample arrived inside the hold).
    NoiseStats feed(uint32_t now_ms, bool dor, int32_t raw)
    {
        if (dor) {
            dor_count++;
            raw = 0;            // clipped at zero: its value IS zero
        }
        if (win.add(now_ms, raw)) {
            since_sum += raw;
            since_n++;
            // Exact running mean while fewer than kRecent samples, then an
            // exponential average with the same weight: no start-up bias.
            const uint32_t n = since_n < (uint32_t)kRecent ? since_n : (uint32_t)kRecent;
            recent += ((float)raw - recent) / (float)n;
        }
        return win.stats();
    }

    int32_t since_mean()  const { return since_n ? (int32_t)(since_sum / (int64_t)since_n) : 0; }
    int32_t recent_mean() const { return since_n ? (int32_t)(recent + 0.5f) : 0; }
};

// The raw code the big Vac/dBm readout is computed from, and whether there
// is one to show yet (see ADC_DISPLAY_AVERAGED in config.h).
//  1: the MEAN of the noise window. Nothing to show while the window is
//     empty - that is the hold after a channel / range / attenuator change
//     (SETTLE_HOLD_MS) - so the caller shows "---" instead of a half-settled
//     number. Samples flagged DOR are in that mean as zeros (see NoiseFeed).
//  0: the latest sample, as before. A DOR-flagged one is the code 0, which
//     the caller turns into "---" like any reading at or below the floor.
// The mean is taken in the RAW domain and converted afterwards, not the
// other way round: the noise is in the raw codes, and averaging already
// log-converted dBm values would bias the result.
static bool adc_display_raw(bool have_sample, int32_t latest_raw,
                            const NoiseStats &n, double &raw_out)
{
#if ADC_DISPLAY_AVERAGED
    (void)latest_raw;
    if (!have_sample || n.count < 1) return false;
    raw_out = (double)n.mean;
    return true;
#else
    (void)n;
    if (!have_sample) return false;
    raw_out = (double)latest_raw;
    return true;
#endif
}

static const char *kChannelNames[3] = {"A", "B", "C"};

// ─── Touch calibration state machine ───────────────────────────────────────
// Triggered from the Settings page's "Calibrate Touch" button. While
// active, touch_task bypasses ALL normal page touch handling (it reads
// raw touch points directly, not through read_touch(), since the very
// calibration constants read_touch() depends on are what's being
// re-derived) and ui_task/render_ui show a full-screen crosshair instead
// of the current page. See touch_calib_compute_and_save() for the math.
//
// Targets are chosen inside the screen edges (not the extreme corners),
// since resistive touch panels are typically least reliable right at
// their physical border.
// 4 corners rather than 2 diagonal points: a 2-point linear fit has zero
// redundancy, so any single noisy/imprecise tap gets baked directly into
// the result with nothing to catch it. With 4 points + least-squares
// fitting (see touch_calib_compute_and_save()), one bad tap shows up as
// an outlier that gets partially averaged out instead of fully
// dictating the fit, and per-point raw values are logged so a genuinely
// bad tap can be spotted by eye too.
#define CALIB_NUM_POINTS 4
static const int16_t kCalibTargetX[CALIB_NUM_POINTS] = { 40, 440,  40, 440 };
static const int16_t kCalibTargetY[CALIB_NUM_POINTS] = { 40,  40, 280, 280 };

static volatile bool g_calib_mode = false;
static volatile int  g_calib_step = 0;      // 0..3: which target we're waiting for
static int16_t       g_calib_raw_x[CALIB_NUM_POINTS];
static int16_t       g_calib_raw_y[CALIB_NUM_POINTS];

// ─── ADC Vac display format ─────────────────────────────────────────────────
// Toggled by Button #3 on the ADC GAIN page. Controls the RIGHT side of
// the big value readout in draw_page_adc_gain(): dBm shown directly
// (VAC_MODE_DBM), or converted to mW via dbm_to_mw() (VAC_MODE_WATT).
// The Vac/mV side (left) is independent - it auto-switches units purely
// by magnitude, not by this toggle.
enum VacDisplayMode { VAC_MODE_DBM = 0, VAC_MODE_WATT= 1 };
static VacDisplayMode g_vac_mode = VAC_MODE_DBM; // matches prior behavior by default

// ─── ADC range <-> gain/attenuator ──────────────────────────────────────────
// The current range lives in g_state.range (0..2 = "Rng 1".."Rng 3").
// Selecting a range applies, as one unit: the PGA gain from
// RANGE1/2/3_GAIN_STEP, the attenuator state from RANGE1/2/3_ATTEN_ON
// (both in config.h), and that range's calibration polynomial in
// adc_to_vac()/adc_to_dbm(). Gain and attenuator are ONLY ever changed via
// range_apply_locked() below (the one exception: Button #4 can still
// manually override the attenuator between range changes - see its
// handler), so none of these three can silently drift out of sync with
// each other.
static constexpr int NUM_RANGES = 3; // matches the JSON's _1/_2/_3 sets
static const uint8_t kRangeGainStep[NUM_RANGES] = {
    RANGE1_GAIN_STEP, RANGE2_GAIN_STEP, RANGE3_GAIN_STEP
};
static const bool kRangeAttenOn[NUM_RANGES] = {
    (bool)RANGE1_ATTEN_ON, (bool)RANGE2_ATTEN_ON, (bool)RANGE3_ATTEN_ON
};

// Compile-time check that every mapped gain is a valid kGainSteps index.
#define KGAIN_COUNT (sizeof(kGainSteps) / sizeof(kGainSteps[0]))
static_assert((size_t)RANGE1_GAIN_STEP < KGAIN_COUNT, "RANGE1_GAIN_STEP is not a valid gain index (0..7)");
static_assert((size_t)RANGE2_GAIN_STEP < KGAIN_COUNT, "RANGE2_GAIN_STEP is not a valid gain index (0..7)");
static_assert((size_t)RANGE3_GAIN_STEP < KGAIN_COUNT, "RANGE3_GAIN_STEP is not a valid gain index (0..7)");

// Result of range_apply_locked(): which hardware writes (if any) the
// caller must make AFTER releasing g_state_mutex (no SPI under the UI
// mutex). new_gain_step is 0xFF if the gain is already right.
// new_attenuator_on is -1 if the attenuator is already right, else 0/1
// for the value to set it to.
struct RangeApplyResult {
    uint8_t new_gain_step;
    int8_t  new_attenuator_on;
};

// Sets the range and the gain/attenuator that go with it. MUST be called
// with g_state_mutex held. Skips a hardware write whenever the current
// state already matches the target - every register write restarts
// conversion, so a redundant one is worth avoiding, not just harmless.
static RangeApplyResult range_apply_locked(uint8_t range)
{
    RangeApplyResult result = { 0xFF, -1 };

    if (range >= NUM_RANGES) range = NUM_RANGES - 1; // defensive clamp
    g_state.range = range; // AppState change -> ui_task redraws immediately

    const uint8_t target_gain = kRangeGainStep[range];
    if (target_gain != gain_step) {
        gain_step = target_gain;
        result.new_gain_step = target_gain;
    }

    // RAW mode (ADC_APPLY_CALIBRATION==0) always forces the attenuator
    // off, same rule Button #4's manual handler enforces - the range
    // mapping doesn't get to override that.
#if ADC_APPLY_CALIBRATION
    const bool target_atten = kRangeAttenOn[range];
#else
    const bool target_atten = false;
#endif
    if (target_atten != g_adc.attenuator_on) {
        result.new_attenuator_on = target_atten ? 1 : 0;
    }

    return result;
}

// ─── Auto range decision ────────────────────────────────────────────────────
// Which range auto range wants next, given the current one and the noise
// window's stats. Returns `cur` when nothing should change; otherwise the
// neighbouring range (one step at a time). Pure function, no hardware.
// Thresholds are in config.h; each is a raw code in the scale of the range
// it is tested in. The comparisons are strict ("below"/"above"), so a mean
// exactly on a threshold does not switch.
static_assert(AUTORANGE_R1_TO_R2_BELOW_RAW > 0 && AUTORANGE_R2_TO_R3_BELOW_RAW > 0 &&
              AUTORANGE_R3_TO_R2_ABOVE_RAW > 0 && AUTORANGE_R2_TO_R1_ABOVE_RAW > 0,
              "auto-range thresholds must be positive");
static_assert(AUTORANGE_R2_TO_R3_BELOW_RAW < AUTORANGE_R2_TO_R1_ABOVE_RAW,
              "Rng 2's down threshold must be below its up threshold");
static_assert(AUTORANGE_MIN_SAMPLES >= 1 && AUTORANGE_MIN_SAMPLES <= NOISE_WINDOW_SAMPLES,
              "AUTORANGE_MIN_SAMPLES must be 1..NOISE_WINDOW_SAMPLES");

static int autorange_decide(int cur, const NoiseStats &n, bool overrange)
{
    // count == 0: nothing settled yet since the last change. The settle
    // skip must pass before ANY decision, including overload, so the jump
    // after a switch can't trigger the next one.
    if (n.count < 1) return cur;

    // Analog overrange: go to the less sensitive range straight away
    // instead of waiting for the window to fill. Rng 1 is the least
    // sensitive, so there is nowhere further to go from it.
    if (overrange) return cur > 0 ? cur - 1 : cur;

    if (n.count < AUTORANGE_MIN_SAMPLES) return cur;

    const int32_t m = n.mean;
    switch (cur) {
        case 0:  // Rng 1
            if (m < AUTORANGE_R1_TO_R2_BELOW_RAW) return 1;
            break;
        case 1:  // Rng 2: test "too high" first, that is the overload side
            if (m > AUTORANGE_R2_TO_R1_ABOVE_RAW) return 0;
            if (m < AUTORANGE_R2_TO_R3_BELOW_RAW) return 2;
            break;
        case 2:  // Rng 3
            if (m > AUTORANGE_R3_TO_R2_ABOVE_RAW) return 1;
            break;
        default:
            break;
    }
    return cur;
}

// Converts dBm to milliwatts: P(mW) = 10^(dBm/10). This is what actually
// makes Button #3 (g_vac_mode) do something now, instead of just
// relabeling itself - see draw_page_adc_gain()'s use of it.
static double dbm_to_mw(double dbm)
{
    return pow(10.0, dbm / 10.0);
}

CalibTable calib;

/** GPIO interrupt for RDYB (falling edge = conversion result ready). */
void IRAM_ATTR RDYB_EXTI_IRQHandler()
{
    BaseType_t higher_prio_woken = pdFALSE;
    max11270_isr_notify_from_gpio(&g_adc, &higher_prio_woken);
    portYIELD_FROM_ISR(higher_prio_woken);
}

// ─── Colours ──────────────────────────────────────────────────────────────────
#define C_BG      0x0841
#define C_PANEL   0x10A2
#define C_ACCENT  0x07FF
#define C_ACCENT2 0xFD20
#define C_TEXT    0xFFFF
#define C_SUBTEXT 0x8410
#define C_GREEN   0x07E0
#define C_RED     0xF800

// =============================================================================
//  ISR — A/B Gray-code encoder with µs debounce
// =============================================================================
static volatile DRAM_ATTR int16_t isr_delta    = 0;
static volatile DRAM_ATTR uint8_t isr_btn_flag = 0;

static const DRAM_ATTR int8_t FSM[16] = {
//  curr: 00  01  10  11
           0,  1, -1,  0,   // prev 00
          -1,  0,  0,  1,   // prev 01
           1,  0,  0, -1,   // prev 10
           0, -1,  1,  0    // prev 11
};
static DRAM_ATTR uint8_t  fsm_state   = 0;
static DRAM_ATTR uint32_t fsm_last_us = 0;

static const int RX_BUF_SIZE = 1024;

#define TXD_PIN (GPIO_NUM_22)
#define RXD_PIN (GPIO_NUM_21)

#define ENC_DEBOUNCE_US  2000u

static void IRAM_ATTR encoder_isr()
{
    uint32_t now  = esp_timer_get_time();
    // digitalRead() correctly resolves GPIO32+ (a separate hardware
    // register, GPIO_IN1_REG, from GPIO0-31's GPIO_IN_REG) — a raw
    // "REG_READ(GPIO_IN_REG) >> pin" trick breaks silently for pins >= 32.
    uint8_t  a    = (uint8_t)digitalRead(ENC_CLK);
    uint8_t  b    = (uint8_t)digitalRead(ENC_DT);
    uint8_t  curr = (a << 1) | b;

    int8_t delta = FSM[((fsm_state & 0x03) << 2) | curr];
    fsm_state    = curr;

    if (delta != 0 && (now - fsm_last_us) >= ENC_DEBOUNCE_US) {
        isr_delta   += delta;
        fsm_last_us  = now;
    }
}

static void IRAM_ATTR button_isr()
{
    isr_btn_flag = 1;
}

// =============================================================================
//  TASK 1 – encoder_task  (Core 1, Priority 6)
// =============================================================================
static void encoder_task(void *pvParam)
{
    TickType_t last_btn_tick = 0;

    for (;;) {
        portDISABLE_INTERRUPTS();
        int16_t raw = isr_delta;  isr_delta    = 0;
        uint8_t btn = isr_btn_flag; isr_btn_flag = 0;
        portENABLE_INTERRUPTS();

        // Accumulate pulses; emit one count per 4 pulses (one detent)
        static int16_t pulse_accum = 0;
        pulse_accum += raw;
        int16_t delta = pulse_accum / 4;
        pulse_accum  %= 4;

        if (delta != 0 || btn != 0) {
            uint8_t new_gain_step     = 0xFF; // sentinel: no gain change pending
            int8_t  new_attenuator_on = -1;   // sentinel: no attenuator change pending

            xSemaphoreTake(g_state_mutex, portMAX_DELAY);

            if (btn) {
                TickType_t now = xTaskGetTickCount();
                if ((now - last_btn_tick) > pdMS_TO_TICKS(200)) {
                    last_btn_tick = now;
                    if (g_calib_mode) {
                        // Cancel calibration instead of changing pages -
                        // safety valve given the Calibrate Touch button's
                        // own touch zone is itself an unverified estimate
                        // (same chicken-and-egg problem as any new
                        // button), so an accidental/stuck entry needs a
                        // way out that doesn't depend on touch at all.
                        g_calib_mode = false;
                        g_calib_step = 0;
                        Serial.println("[CALIB] cancelled via encoder button");
                    } else {
                        g_state.page = (Page)((g_state.page + 1) % PAGE_COUNT);
                    }
                }
            }

            if (delta != 0) {
                switch (g_state.page) {
                    case PAGE_INFO:
                        // Pure info/status display now
                        // no encoder interaction on this page anymore.
                        break;
                    case PAGE_BARGRAPH:
                        g_state.counter = constrain(g_state.counter + (int32_t)delta * 5, 0, 100);
                        break;
                    case PAGE_SETTINGS:
                        g_state.brightness = (uint8_t)constrain(
                            (int)g_state.brightness + delta * 5, 0, 100);
                        break;
                    case PAGE_ADC_GAIN: {
                        // The knob steps the RANGE (Rng 1..3), not the gain
                        // directly: gain, attenuator, and calibration
                        // polynomial all follow the range via
                        // range_apply_locked(), so they can't get out of
                        // sync. Clockwise = higher range = more gain, same
                        // direction as before. Clamped (no wrap) - the
                        // Range button is the one that wraps.
                        int new_range = constrain((int)g_state.range + delta, 0, NUM_RANGES - 1);
                        if (new_range != g_state.range) {
                            // Both SPI writes (if needed) are deferred
                            // until after g_state_mutex is released, below.
                            RangeApplyResult r = range_apply_locked((uint8_t)new_range);
                            new_gain_step     = r.new_gain_step;
                            new_attenuator_on = r.new_attenuator_on;
                            g_state.auto_range = 0; // a hand-set range switches auto range off
                        }
                        break;
                    }
                    default: break;
                }
            }
            xSemaphoreGive(g_state_mutex);

            // SPI calls deliberately made AFTER releasing g_state_mutex, so
            // a (potentially bus-contended, e.g. with ui_task's TFT pushes)
            // SPI transaction never holds the UI mutex hostage.
            if (new_gain_step != 0xFF) {
                max11270_set_gain(&g_adc, kGainSteps[new_gain_step]);
            }
            if (new_attenuator_on >= 0) {
                max11270_set_attenuator(&g_adc, new_attenuator_on != 0);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

// =============================================================================
//  Touch helper
// =============================================================================
struct TouchPoint { int16_t x; int16_t y; bool valid; };

static TouchPoint read_touch()
{
    TouchPoint tp = { 0, 0, false };
    if (!touch.tirqTouched() || !touch.touched()) return tp;

    TS_Point raw = touch.getPoint();

    const int screen_w = tft.width();   // 480 after setRotation(3)
    const int screen_h = tft.height();  // 320 after setRotation(3)

    // Calibrate each RAW channel against its own min/max first (per-
    // channel electrical calibration, independent of orientation), THEN
    // decide which calibrated value becomes the final x vs y based on
    // swap_xy. Now sourced from the runtime g_touch_calib struct (NVS-
    // backed, see app_settings.h) rather than the TOUCH_X_MIN-style
    // #defines in config.h - those still exist and are used only as the
    // fallback defaults settings_load() seeds NVS with on first boot.
    int16_t cal_x, cal_y;
    if (g_touch_calib.swap_xy) {
        cal_y = (int16_t)map(raw.x, g_touch_calib.x_min, g_touch_calib.x_max, 0, screen_h - 1);
        cal_x = (int16_t)map(raw.y, g_touch_calib.y_min, g_touch_calib.y_max, 0, screen_w - 1);
    } else {
        cal_x = (int16_t)map(raw.x, g_touch_calib.x_min, g_touch_calib.x_max, 0, screen_w - 1);
        cal_y = (int16_t)map(raw.y, g_touch_calib.y_min, g_touch_calib.y_max, 0, screen_h - 1);
    }

    if (g_touch_calib.invert_x) { cal_x = (int16_t)(screen_w - 1 - cal_x); }
    if (g_touch_calib.invert_y) { cal_y = (int16_t)(screen_h - 1 - cal_y); }

    tp.x     = constrain(cal_x, 0, screen_w - 1);
    tp.y     = constrain(cal_y, 0, screen_h - 1);
    tp.valid = true;
    return tp;
}

// Least-squares linear fit: given n (cal, raw) pairs where raw is
// expected to vary linearly with cal (raw = a + b*cal), returns the
// fitted MIN (=a) and MAX (=a + b*(screen_dim-1)). More robust than
// solving 2 points exactly - with 4 points, one noisy/imprecise tap
// pulls the fit slightly rather than fully dictating it.
static void solve_linear_fit(const int16_t *cal_vals, const int16_t *raw_vals, int n,
                              int screen_dim, float *out_min, float *out_max)
{
    double sum_cal = 0, sum_raw = 0;
    for (int i = 0; i < n; i++) { sum_cal += cal_vals[i]; sum_raw += raw_vals[i]; }
    double mean_cal = sum_cal / n;
    double mean_raw = sum_raw / n;

    double num = 0, den = 0;
    for (int i = 0; i < n; i++) {
        double dc = cal_vals[i] - mean_cal;
        double dr = raw_vals[i] - mean_raw;
        num += dc * dr;
        den += dc * dc;
    }
    double b = (den != 0.0) ? (num / den) : 0.0; // slope: raw per unit of cal
    double a = mean_raw - b * mean_cal;          // intercept: raw at cal=0

    *out_min = (float)a;
    *out_max = (float)(a + b * (screen_dim - 1));
}

// Solves for new x_min/x_max/y_min/y_max from the CALIB_NUM_POINTS
// captured (raw touch reading, known target screen position) pairs,
// keeping the current swap_xy/invert_x/invert_y settings as-is (this
// recalibrates MIN/MAX only, it does not auto-detect swap/invert - if the
// axes are genuinely swapped or mirrored, that still needs to be set
// correctly in config.h/NVS beforehand for this math to produce a sane
// result).
//
// Derivation: read_touch() computes cal = (raw-MIN)/(MAX-MIN)*(N-1), then
// optionally inverts. For each captured point, reverse the invert to get
// the pre-invert calibrated value that target should produce, then fit
// raw vs cal linearly (see solve_linear_fit) to get MIN/MAX.
static void touch_calib_compute_and_save()
{
    const int scr_w = tft.width();
    const int scr_h = tft.height();

    auto pre_invert = [](int16_t v, int n, bool inv) -> int16_t {
        return inv ? (int16_t)(n - 1 - v) : v;
    };

    int16_t cal_x[CALIB_NUM_POINTS], cal_y[CALIB_NUM_POINTS];
    int16_t raw_for_x[CALIB_NUM_POINTS], raw_for_y[CALIB_NUM_POINTS];

    Serial.println("[CALIB] captured points:");
    for (int i = 0; i < CALIB_NUM_POINTS; i++) {
        cal_x[i] = pre_invert(kCalibTargetX[i], scr_w, g_touch_calib.invert_x);
        cal_y[i] = pre_invert(kCalibTargetY[i], scr_h, g_touch_calib.invert_y);

        if (g_touch_calib.swap_xy) {
            // raw.x feeds the y calibration, raw.y feeds the x calibration
            // (mirrors read_touch()'s swap branch).
            raw_for_y[i] = g_calib_raw_x[i];
            raw_for_x[i] = g_calib_raw_y[i];
        } else {
            raw_for_x[i] = g_calib_raw_x[i];
            raw_for_y[i] = g_calib_raw_y[i];
        }

        // Logged so a genuinely bad/imprecise tap can be spotted by eye:
        // all 4 raw values for one axis should trend smoothly with that
        // axis's target position, not jump around unpredictably.
        Serial.printf("  [%d] target=(%d,%d) raw=(%d,%d)\n",
                      i, kCalibTargetX[i], kCalibTargetY[i],
                      g_calib_raw_x[i], g_calib_raw_y[i]);
    }

    float new_x_min, new_x_max, new_y_min, new_y_max;
    solve_linear_fit(cal_x, raw_for_x, CALIB_NUM_POINTS, scr_w, &new_x_min, &new_x_max);
    solve_linear_fit(cal_y, raw_for_y, CALIB_NUM_POINTS, scr_h, &new_y_min, &new_y_max);

    g_touch_calib.x_min = (int16_t)lroundf(new_x_min);
    g_touch_calib.x_max = (int16_t)lroundf(new_x_max);
    g_touch_calib.y_min = (int16_t)lroundf(new_y_min);
    g_touch_calib.y_max = (int16_t)lroundf(new_y_max);

    Serial.printf("[CALIB] new touch calibration: x[%d,%d] y[%d,%d]\n",
                  g_touch_calib.x_min, g_touch_calib.x_max,
                  g_touch_calib.y_min, g_touch_calib.y_max);

    settings_save(g_state.brightness);
}

// =============================================================================
//  TASK 2 – touch_task  (Core 0, Priority 3)
//
//  Touch zones (all pages):
//    Footer area (y > 276) is now a no-op - page switching is done via
//    the encoder's push button (see encoder_task), not by tapping here.
//
//  PAGE_INFO:
//    Non-interactive - pure status display (CPU/RTOS/heap).
//
//  PAGE_BARGRAPH:
//    y < 160            → +5%
//    y 160-276          → -5%
//
//  PAGE_SETTINGS:
//    y 96-126           → drag brightness bar (x position = value)
//    y < 96 or >126     → tap upper=+5% lower=-5% brightness
//
//  PAGE_ADC_GAIN (5-button row, y 234-276):
//    x   9-91   → Button #1: Channel select (cycle A/B/C)
//    x 103-185  → Button #2: Range select (Rng 1/2/3): sets the range's
//                 gain (kRangeGainStep), attenuator (kRangeAttenOn), and
//                 selects its calibration polynomial, all together
//    x 197-279  → Button #3: dBm/mW display toggle (right side of the
//                 big readout - see dbm_to_mw())
//    x 291-373  → Button #4: Attenuator on/off (ON blocked when
//                 ADC_APPLY_CALIBRATION==0 - see its handler below)
//    x 385-479  → Button #5: Auto range on/off (to the screen edge, see its handler)
//
// =============================================================================
static void touch_task(void *pvParam)
{
    TickType_t last_action   = 0;
    bool       was_touching  = false;

    for (;;) {
        // Calibration mode bypasses ALL normal touch handling below - it
        // needs raw touch points directly (touch.getPoint()), not the
        // read_touch()-transformed ones, since g_touch_calib (which
        // read_touch() depends on) is exactly what's being re-derived
        // here. fresh_press logic reused so one physical tap = one
        // captured target, regardless of how long the finger stays down.
        if (g_calib_mode) {
            bool touched = touch.tirqTouched() && touch.touched();
            if (touched) {
                if (!was_touching) {
                    // Average several samples over ~120ms rather than
                    // trusting one instantaneous reading - resistive
                    // touch panels are genuinely noisy per-sample, and a
                    // linear fit (even with 4 points) has limited ability
                    // to absorb a badly noisy single point.
                    long sum_x = 0, sum_y = 0;
                    int  n = 0;
                    for (int i = 0; i < 6; i++) {
                        if (touch.touched()) {
                            TS_Point raw = touch.getPoint();
                            sum_x += raw.x;
                            sum_y += raw.y;
                            n++;
                        }
                        vTaskDelay(pdMS_TO_TICKS(20));
                    }
                    if (n > 0) {
                        g_calib_raw_x[g_calib_step] = (int16_t)(sum_x / n);
                        g_calib_raw_y[g_calib_step] = (int16_t)(sum_y / n);
                        Serial.printf("[CALIB] target %d captured (avg of %d samples): raw x=%d y=%d\n",
                                      g_calib_step, n,
                                      g_calib_raw_x[g_calib_step], g_calib_raw_y[g_calib_step]);
                        g_calib_step++;
                        if (g_calib_step >= CALIB_NUM_POINTS) {
                            touch_calib_compute_and_save();
                            g_calib_mode = false;
                            g_calib_step = 0;
                        }
                    }
                }
                was_touching = true;
            } else {
                was_touching = false;
            }
            vTaskDelay(pdMS_TO_TICKS(30));
            continue;
        }

        TouchPoint tp = read_touch();

        if (tp.valid) {
            TickType_t now = xTaskGetTickCount();

            // Diagnostic - re-enable both lines below if any future
            // touch-position work is needed. Left commented (not
            // removed) since this proved genuinely useful across this
            // whole calibration debugging arc; settings/calibration
            // load/save/erase logging in app_settings.cpp and
            // touch_calib_compute_and_save() stays active, just this
            // noisy every-tap pair is silenced now that touch is
            // confirmed working end to end.
            // TS_Point p = touch.getPoint();
            // Serial.printf("raw x=%d y=%d  ->  computed tp.x=%d tp.y=%d\n", p.x, p.y, tp.x, tp.y);

            // Debounce: ignore new touch within 50 ms of last one
            bool fresh_press = !was_touching; // true only on this touch's very
                                               // first poll (finger just went
                                               // down) - see PAGE_ADC_GAIN below
            bool is_new = !was_touching || (now - last_action) > pdMS_TO_TICKS(50);
            was_touching = true;

            if (is_new) {
                xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                Page page = g_state.page;
                xSemaphoreGive(g_state_mutex);

                if (page == PAGE_ADC_GAIN && fresh_press &&
                    tp.x >= 9 && tp.x < 91 && tp.y >= 234 && tp.y < 276) {

                    // Button #1 - Channel select. Zone matches the drawn
                    // button at x=7-93, y=232-276 in draw_page_adc_gain().
                    // fresh_press (not is_new) gates this: cycling through
                    // 3 discrete channels should happen exactly once per
                    // physical tap - is_new alone re-fires every ~50ms
                    // for as long as the finger stays down.
                    uint8_t new_channel;
                    xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                    // (g_state.channel++) reads AND writes the same
                    // variable with no sequence point between them -
                    // undefined behavior in C/C++. Plain modulo increment
                    // instead, computed once and reused.
                    new_channel = (uint8_t)((g_state.channel + 1) % 3);
                    g_state.channel = new_channel;
                    xSemaphoreGive(g_state_mutex);

                    // Actually talk to the chip: writing g_adc.channel
                    // directly (as before) only updates the driver's
                    // bookkeeping field - it never touches CTRL4, so the
                    // physical mux never switches. max11270_set_channel()
                    // does the real GPIO1/GPIO2 register write AND
                    // re-arms continuous conversion afterward (any
                    // register write interrupts it - see
                    // max11270_resume_conversion()). Called after
                    // releasing g_state_mutex, same reasoning as the
                    // gain-change path in encoder_task: an SPI transaction
                    // shouldn't hold the UI mutex hostage.
                    max11270_set_channel(&g_adc, new_channel);

                } else if (page == PAGE_ADC_GAIN && fresh_press &&
                    tp.x >= 103 && tp.x < 185 && tp.y >= 234 && tp.y < 276) {
                    // Button #2 - Range select (Rng 1/2/3). Zone matches
                    // the drawn button at x=101-187. Cycles the range
                    // (wrapping 3 -> 1) via range_apply_locked(), the same
                    // path the rotary knob uses: it sets g_state.range
                    // (selects the calibration polynomial) and works out
                    // whether the PGA gain AND attenuator have to change
                    // with it.
                    RangeApplyResult r;
                    xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                    r = range_apply_locked((uint8_t)((g_state.range + 1) % NUM_RANGES));
                    g_state.auto_range = 0; // a hand-set range switches auto range off
                    xSemaphoreGive(g_state_mutex);

                    // SPI calls after releasing g_state_mutex, same as the
                    // encoder's gain path and the channel/attenuator paths.
                    if (r.new_gain_step != 0xFF) {
                        max11270_set_gain(&g_adc, kGainSteps[r.new_gain_step]);
                    }
                    if (r.new_attenuator_on >= 0) {
                        max11270_set_attenuator(&g_adc, r.new_attenuator_on != 0);
                    }

                } else if (page == PAGE_ADC_GAIN && fresh_press &&
                    tp.x >= 197 && tp.x < 279 && tp.y >= 234 && tp.y < 276) {
                    // Button #3 - dBm/mW display toggle. Zone matches the
                    // drawn button at x=195-281. Toggles g_vac_mode, which
                    // draw_page_adc_gain() now actually uses (via
                    // dbm_to_mw()) to switch the right side of the big
                    // readout between dBm and mW.
                    g_vac_mode = (g_vac_mode == VAC_MODE_DBM)
                                     ? VAC_MODE_WATT: VAC_MODE_DBM;

                } else if (page == PAGE_ADC_GAIN && fresh_press &&
                           tp.x >= 291 && tp.x < 373 && tp.y >= 234 && tp.y < 276) {
                    // Button #4 - Attenuator on/off toggle. Zone matches
                    // the drawn button at x=289-375. Stays tappable and
                    // its display stays live in both builds - only
                    // actually turning it ON is gated: with
                    // ADC_APPLY_CALIBRATION==0 (config.h, RAW/uncorrected
                    // mode) it's forced to stay off, so the attenuator
                    // isn't one more uncontrolled variable while
                    // collecting clean data to build new polynomials
                    // from. Turning it OFF always works, in both builds.
                    bool new_attenuator_on = !g_adc.attenuator_on;
#if !ADC_APPLY_CALIBRATION
                    new_attenuator_on = false;
#endif
                    if (new_attenuator_on != g_adc.attenuator_on) {
                        max11270_set_attenuator(&g_adc, new_attenuator_on);
                    }

                } else if (page == PAGE_ADC_GAIN && fresh_press &&
                           tp.x >= 385 && tp.x <= 479 && tp.y >= 234 && tp.y < 276) {
                    // Button #5 - Auto range on/off. Drawn at x=383-469, but
                    // the zone runs to the screen edge: a real tap on it
                    // logged tp=(479,260) - 479 is the clamped maximum, the
                    // panel saturates near its right edge - which the first
                    // zone (x<467) missed. Nothing else is to the right of
                    // this button, so extending it costs nothing. The decisions themselves are
                    // made in adc_consumer_task (it owns the noise window
                    // they are based on); this only flips the flag. Cannot
                    // be turned on in RAW mode (ADC_APPLY_CALIBRATION 0):
                    // the attenuator is forced off there, which changes
                    // the raw scale the thresholds were measured in - so
                    // there the tap does nothing.
#if ADC_APPLY_CALIBRATION
                    xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                    g_state.auto_range = g_state.auto_range ? 0 : 1;
                    xSemaphoreGive(g_state_mutex);
#endif

                } else if (tp.y > 387) {
                    // Footer is now purely a visual hint bar - page
                    // switching is done via the encoder's push button
                    // (see encoder_task/button_isr), not by tapping here.
                    // Kept as a no-op zone (rather than deleted outright)
                    // so a tap landing in this y-range doesn't fall
                    // through into whatever page-specific zone logic
                    // happens to occupy the same rows below (e.g. it
                    // would otherwise register as a settings brightness
                    // tap on the PAGE_SETTINGS page).

                } else if (page == PAGE_BARGRAPH) {
                    int16_t dir = (tp.y < 160) ? 5 : -5;
                    xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                    g_state.counter = constrain(g_state.counter + dir, 0, 100);
                    xSemaphoreGive(g_state_mutex);

                } else if (page == PAGE_SETTINGS && fresh_press &&
                           tp.x >= 120 && tp.x < 360 && tp.y >= 190 && tp.y < 255) {
                    // Calibrate Touch button - zone widened/shifted to
                    // track its new drawn position (y=204-240, was
                    // 196-232) after the brightness bar grew taller.
                    // Generous margin since (same as any new button) its
                    // real touch response can't be verified until tried.
                    // Enters calibration mode; the crosshair screen and
                    // its own touch handling take over from here (see the
                    // g_calib_mode block at the top of this task's loop).
                    g_calib_step = 0;
                    g_calib_mode = true;

                } else if (page == PAGE_SETTINGS) {
                    if ((tp.x >= 120 && tp.x <= 360) && (tp.y >= 78 && tp.y <= 114)) {
                        // Drag directly on brightness bar - bar geometry
                        // matches draw_page_settings()'s
                        // cv_fillRoundRect(40, 90, 400, 24, ...) with the
                        // fill inset 2px: x 42..438.
                        uint8_t bri = (uint8_t)constrain(map(tp.x, 140, 340, 0, 100), 0, 100);
                        xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                        g_state.brightness = bri;
                        xSemaphoreGive(g_state_mutex);
                    } else {
                        // Tap above/below bar = ±5% (102 = bar's vertical
                        // center, (90+114)/2)
                        int dir = (tp.y < 102) ? 5 : -5;
                        xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                        g_state.brightness = (uint8_t)constrain(
                            (int)g_state.brightness + dir, 0, 100);
                        xSemaphoreGive(g_state_mutex);
                    }
                }

                last_action = now;
            }

        } else {
            was_touching = false;
        }

        vTaskDelay(pdMS_TO_TICKS(30));   // ~33 Hz touch poll
    }
}

// =============================================================================
//  Drawing abstraction (sprite bands or direct tft)
// =============================================================================
static int draw_y_offset = 0;

static inline TFT_eSPI* cv() { return use_sprite ? (TFT_eSPI*)&sprite : &tft; }
static inline int ly(int y)  { return y - draw_y_offset; }

static int  band_top()    { return draw_y_offset; }
static int  band_bottom() { return use_sprite ? draw_y_offset + sprite_h : tft.height(); }
static bool in_band(int y, int h = 1) { return (y+h > band_top()) && (y < band_bottom()); }

static void cv_fillRoundRect(int x,int y,int w,int h,int r,uint16_t c){if(!in_band(y,h))return;cv()->fillRoundRect(x,ly(y),w,h,r,c);}
static void cv_fillRect(int x,int y,int w,int h,uint16_t c){if(!in_band(y,h))return;cv()->fillRect(x,ly(y),w,h,c);}
static void cv_drawRoundRect(int x,int y,int w,int h,int r,uint16_t c){if(!in_band(y,h))return;cv()->drawRoundRect(x,ly(y),w,h,r,c);}
static void cv_drawFastHLine(int x,int y,int w,uint16_t c){if(!in_band(y))return;cv()->drawFastHLine(x,ly(y),w,c);}
static void cv_drawFastVLine(int x,int y,int h,uint16_t c){if(!in_band(y,h))return;cv()->drawFastVLine(x,ly(y),h,c);}

static void cv_text(const char *s, int x, int y, uint8_t font,
                    uint16_t fg, uint16_t bg, uint8_t datum)
{
    int fh = (font==1)?8:(font==2)?16:(font==4)?26:48;
    if (!in_band(y, fh)) return;
    cv()->setTextFont(font);
    cv()->setTextColor(fg, bg);
    cv()->setTextDatum(datum);
    cv()->drawString(s, x, ly(y));
}

// =============================================================================
//  Page draw functions
// =============================================================================
static void draw_header(const char *title, uint16_t accent)
{
    cv_fillRoundRect(8, 8, 464, 40, 8, C_PANEL);
    cv_drawRoundRect(8, 8, 464, 40, 8, accent);
    cv_text(title, 240, 28, 4, accent, C_PANEL, MC_DATUM);
}

static void draw_footer(const char *hint)
{
    cv_fillRoundRect(8, 286, 464, 32, 8, C_PANEL);
    cv_text(hint, 240, 302, 1, C_SUBTEXT, C_PANEL, MC_DATUM);
}

static void draw_measure(const char *title, uint16_t accent)
{
    cv_fillRoundRect(8, 8, 464, 120, 8, C_PANEL);
    cv_drawRoundRect(8, 8, 464, 120, 8, accent);

}

// How far the noise bar reaches left and right of its centre line, in
// pixels, for the given window stats. Pure function (no drawing) so the
// scaling can be checked on its own.
//   left_px  = mean - lowest,  right_px = highest - mean,
//   each scaled so NOISE_BAR_FULLSCALE_COUNTS fills `half_px`.
//   saturated = either side reached the full-scale count.
// Fewer than 2 samples can't say anything about noise, so the bar stays empty.
static void noise_bar_extents(const NoiseStats &n, int half_px,
                              int &left_px, int &right_px, bool &saturated)
{
    left_px = right_px = 0;
    saturated = false;
    if (n.count < 2) return;

    int32_t below = n.mean - n.lo;   // both >= 0, see NoiseStats::mean
    int32_t above = n.hi - n.mean;
    if (below >= NOISE_BAR_FULLSCALE_COUNTS || above >= NOISE_BAR_FULLSCALE_COUNTS) {
        saturated = true;
    }
    // Clamp BEFORE scaling: a raw spread in the millions times half_px
    // would overflow a 32-bit int.
    if (below > NOISE_BAR_FULLSCALE_COUNTS) below = NOISE_BAR_FULLSCALE_COUNTS;
    if (above > NOISE_BAR_FULLSCALE_COUNTS) above = NOISE_BAR_FULLSCALE_COUNTS;
    left_px  = (int)((int64_t)below * half_px / NOISE_BAR_FULLSCALE_COUNTS);
    right_px = (int)((int64_t)above * half_px / NOISE_BAR_FULLSCALE_COUNTS);
}

// ADC-page noise bar. Panel geometry as in your draw_bar(): x=8..471,
// y=132, 15 px tall, centre line at x=240 (= the window mean). The fill
// runs from the lowest code (left of centre) to the highest (right of
// centre); green normally, red when it hits the end of the scale.
static void draw_noise_bar(const NoiseStats &n, uint16_t accent)
{
    const int x = 8, y = 132, w = 464, h = 15;
    const int cx      = x + w / 2;  // 240
    const int half_px = 216;        // keeps the fill clear of the panel's rounded ends

    cv_fillRoundRect(x, y, w, h, 8, C_PANEL);
    cv_drawRoundRect(x, y, w, h, 8, accent);

    int  left_px, right_px;
    bool saturated;
    noise_bar_extents(n, half_px, left_px, right_px, saturated);
    if (left_px + right_px > 0) {
        cv_fillRect(cx - left_px, y + 2, left_px + right_px, h - 4,
                    saturated ? C_RED : C_GREEN);
    }
    cv_drawFastVLine(cx, y, h, C_SUBTEXT); // drawn last so it stays visible over the fill
}

#if BATTERY_INDICATOR
// Colour by charge level, same steps as the earlier project (green, then
// yellow below 70 %, orange below 50 %, red below 30 %; thresholds are in
// config.h).
static uint16_t battery_color(uint8_t pct)
{
    if (pct < BATTERY_RED_PCT)    return C_RED;
    if (pct < BATTERY_ORANGE_PCT) return C_ACCENT2; // orange
    if (pct < BATTERY_YELLOW_PCT) return TFT_YELLOW;
    return C_GREEN;
}

// Battery icon, right-aligned under the noise bar (the bar's right edge is
// x=471; the icon's terminal nub ends there too). Outline + nub, with an
// inner fill whose width follows the charge, and the percentage ("NN%")
// in white inside it. Grey outline and "--" when there is no believable
// reading.
//
// The text is drawn WITHOUT a background (foreground colour == background
// colour is how TFT_eSPI draws transparent text), because the icon's inside
// is part fill, part empty: an opaque text background would show as a block
// over one of them. It gets a 1 px dark outline (the 3x3 loop below) because
// plain white is nearly invisible on the bright fills - the contrast with
// pure yellow is about 1:1, with pure green only about 1.4:1. Delete the
// loop for plain white text.
//
// The text uses TC_DATUM (top-centre) with its anchor 3 px below the icon's
// top, so its 16 rows span y=155..170. That crosses the y=160 band boundary
// of the banded renderer; cv_text() handles that for top-anchored text (the
// INFO page's "RTOS:" line does the same). A centre-anchored datum would be
// clipped at the boundary, which is why this isn't MC_DATUM.
static void draw_battery(const BatteryStatus &b)
{
    const int body_x = 398, body_y = 152, body_w = 71, body_h = 22;
    const int nub_w  = 3;                 // body_x+body_w+nub_w-1 = 471
    const int inner_w = body_w - 6;       // 3 px of margin inside the outline
    const uint16_t col = b.valid ? battery_color(b.pct) : C_SUBTEXT;

    cv_drawRoundRect(body_x, body_y, body_w, body_h, 3, col);
    cv_fillRect(body_x + body_w, body_y + 6, nub_w, body_h - 12, col); // terminal nub

    if (b.valid) {
        int fill = (b.pct * inner_w) / 100;
        if (b.pct > 0 && fill < 1) fill = 1;   // never show a non-empty battery as empty
        if (fill > 0) {
            cv_fillRect(body_x + 3, body_y + 3, fill, body_h - 6, col);
        }
    }

    char buf[16];
    if (b.valid) snprintf(buf, sizeof(buf), "%d%%", (int)b.pct);
    else         snprintf(buf, sizeof(buf), "--");

    const int tx = body_x + body_w / 2;   // centred on the icon body
    const int ty = body_y + 3;
    // Dark outline first: the same text, black, nudged 1 px in every direction...
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx != 0 || dy != 0) {
                cv_text(buf, tx + dx, ty + dy, 2, TFT_BLACK, TFT_BLACK, TC_DATUM);
            }
        }
    }
    // ...then the white text on top (fg == bg = transparent, see above).
    cv_text(buf, tx, ty, 2, C_TEXT, C_TEXT, TC_DATUM);
}
#endif // BATTERY_INDICATOR

// Was draw_page_counter() - the counter's own coding (increment/range/
// tap hints) was dropped and this page repurposed to a pure info/status
// display, showing what used to live on the Settings page (CPU/RTOS/heap).
static void draw_page_info(const AppState &s)
{
    (void)s; // pure info/status display, doesn't use AppState
    draw_header("INFO", C_ACCENT);
    cv_text("CPU:  240 MHz dual-core", 30, 120, 2, C_SUBTEXT, C_BG, TL_DATUM);
    cv_text("RTOS: FreeRTOS 10.x",     30, 152, 2, C_SUBTEXT, C_BG, TL_DATUM);
    char hbuf[28];
    snprintf(hbuf, sizeof(hbuf), "Firmware version: %s", firmware);
    cv_text(hbuf, 30, 184, 2, C_SUBTEXT, C_BG, TL_DATUM);
    snprintf(hbuf, sizeof(hbuf), "Heap: %lu B free", (unsigned long)esp_get_free_heap_size());
    cv_text(hbuf, 30, 216, 2, C_GREEN, C_BG, TL_DATUM);
    draw_footer("Push: next page");
}

static void draw_page_bargraph(const AppState &s)
{
    draw_header("BARGRAPH", C_ACCENT2);
    char buf[8];
    snprintf(buf, sizeof(buf), "%d%%", s.counter);
    cv_text(buf, 240, 90, 6, C_ACCENT2, C_BG, MC_DATUM);
    cv_fillRoundRect(60, 150, 360, 44, 8, C_PANEL);
    int bar_w = (s.counter * 356) / 100;
    if (bar_w > 0) {
        uint16_t bar_col = (s.counter < 50) ? C_GREEN :
                           (s.counter < 80) ? C_ACCENT2 : C_RED;
        cv_fillRoundRect(62, 152, bar_w, 40, 6, bar_col);
    }
    for (int t : {25, 50, 75}) {
        int x = 62 + (t * 356) / 100;
        cv_drawFastVLine(x, 142, 10, C_SUBTEXT);
        char tbuf[4]; snprintf(tbuf, sizeof(tbuf), "%d", t);
        cv_text(tbuf, x, 204, 1, C_SUBTEXT, C_BG, TC_DATUM);
    }
    cv_text("Tap top +5% / bottom -5%", 240, 235, 1, C_SUBTEXT, C_BG, MC_DATUM);
    draw_footer("Rotate or tap   |   Push: next page");
}

static void draw_page_settings(const AppState &s)
{
    draw_header("SETTINGS", 0xF81F);
    cv_text("Brightness",30, 85, 2, C_TEXT, C_BG, TL_DATUM);
    char buf[8];
    snprintf(buf, sizeof(buf), "%d%%", s.brightness);
    cv_text(buf, 450, 82, 4, 0xF81F, C_BG, TR_DATUM);

    // Brightness bar: bigger touch target (400 wide x 24 tall, was
    // 440x16), with +/- labels at the ends to show drag direction.
    // Fill rect's x-start/width-scale updated to match the new
    // background bounds (x=40..440) - it was left pointing at the OLD
    // bounds (x=20..460) when the background moved, which would have
    // drawn the highlighted portion partly outside the new box.
    cv_fillRoundRect(140, 78, 200, 36, 6, C_PANEL);
    cv_text("-", 130, 84, 4, 0xF81F, C_PANEL, TR_DATUM);
    cv_text("+", 354, 84, 4, 0xF81F, C_PANEL, TR_DATUM);
    int bbar = (s.brightness * 198) / 100;
    if (bbar > 0)
        cv_fillRoundRect(142, 80, bbar, 32, 5, 0xF81F);

    cv_drawFastHLine(20, 126, 440, C_PANEL);

    // Calibrate Touch button. Sized generously since - same
    // chicken-and-egg problem as any new button on this panel - its
    // exact touch response can't be verified until it's tried; if it
    // doesn't respond, the raw/computed touch print (already active in
    // touch_task) will show where taps actually land.
    cv_text("Touch",30, 222, 2, C_TEXT, C_BG, TL_DATUM);
    cv_fillRoundRect(140, 204, 200, 36, 8, C_ACCENT2);
    cv_text("Calibrate", 245, 222, 2, C_BG, C_ACCENT2, MC_DATUM);

    //cv_text("Drag bar or tap +/-5%", 240, 256, 1, C_SUBTEXT, C_BG, MC_DATUM);
    draw_footer("Rotate or drag bar   |   Push: next page");
}

// Full-screen crosshair shown while g_calib_mode is active. Draws
// directly at absolute screen coordinates (not tied to any page's normal
// layout) since it replaces whatever page was showing.
static void draw_calib_screen()
{
    int step = g_calib_step; // 0 or 1
    int16_t tx = kCalibTargetX[step];
    int16_t ty = kCalibTargetY[step];

    cv_fillRoundRect(8, 8, 464, 40, 8, C_PANEL);
    char hdr[32];
    snprintf(hdr, sizeof(hdr), "Touch Calibration (%d/%d)", step + 1, CALIB_NUM_POINTS);
    cv_text(hdr, 240, 28, 4, C_ACCENT2, C_PANEL, MC_DATUM);

    cv_text("Tap the crosshair exactly", 240, 100, 2, C_TEXT, C_BG, MC_DATUM);
    cv_text("Push encoder button to cancel", 240, 124, 1, C_SUBTEXT, C_BG, MC_DATUM);

    // Crosshair at the target position.
    cv_drawFastHLine(tx - 12, ty, 24, C_GREEN);
    cv_drawFastVLine(tx, ty - 12, 24, C_GREEN);
    cv_drawRoundRect(tx - 14, ty - 14, 28, 28, 4, C_GREEN);
}

static void draw_page_adc_gain(const AppState &s)
{
    // s.range (from the snapshot ui_task took under the mutex) is the
    // current range; channel still comes from g_adc.channel.

    char gbuf[16];
    //snprintf(gbuf, sizeof(gbuf), "ADC on Chan (%s)", kChannelNames[g_adc.channel]);
    draw_measure(gbuf, C_GREEN  );

    // Gain setting label

    //snprintf(gbuf, sizeof(gbuf), "Gain: x%u", (unsigned)g_adc.pga_gain);
    //cv_text(gbuf, 240, 68, 4, C_GREEN, C_BG, MC_DATUM);

    // Read the latest sample published by adc_consumer_task (see its
    // definition for why this isn't xQueuePeek() on the queue directly).
    max11270_sample_t last;
    NoiseStats noise;
#if BATTERY_INDICATOR
    BatteryStatus battery;
#endif
    bool have_sample;
    xSemaphoreTake(g_latest_sample_mutex, portMAX_DELAY);
    have_sample = g_latest_sample_valid;
    last = g_latest_sample;
    noise = g_noise; // same critical section as the sample it belongs to
#if BATTERY_INDICATOR
    battery = g_battery;
#endif
    xSemaphoreGive(g_latest_sample_mutex);
    bool fault = have_sample && (last.status & (MAX11270_STAT_AOR | MAX11270_STAT_DOR));

    // Big, prominent voltage readout - the actual measured value. Vac
    // portion now goes through format_vac() (engineering notation, or
    // floating-point with auto-mV under 1V, per g_vac_mode - toggled by
    // the Fmt button below). vbuf bumped from 16->40 bytes while here:
    // the old %.3e + %.2f combo could already exceed 16 chars and
    // silently truncate.
    // REVIEW FIX: the value and its unit label used to be decided by two
    // SEPARATE `fabs(vac) < 1.0` checks (one for the snprintf, one for the
    // label text below) - and they'd drifted out of sync: the branch that
    // multiplied by 1000 (i.e. actually produced a mV number) was labeled
    // "Vac", and the branch that left it in volts was labeled "mV" -
    // backwards from what's on screen. Consolidated into one boolean,
    // computed once, so the number and its label can never disagree again
    // (same reasoning the old format_vac() had, by keeping the unit
    // string in the same snprintf call as the value - this restores that
    // guarantee without reintroducing that function).
    //
    // Also: `vac`/`dbm` are now initialized at declaration - previously,
    // when !have_sample, they were read further below (the label-choosing
    // `fabs(vac) < 1.0` checks ran unconditionally) while still
    // uninitialized, which is undefined behavior and could make the "Vac"
    // vs "mV" label flicker unpredictably before the first real sample.
    char vbuf[80];
    double vac = 0.0;
    double dbm = 0.0;
    bool   vac_is_mv = false; // single source of truth for value AND label
    // Raw code the readout is computed from: the noise-window mean or the
    // latest sample, per ADC_DISPLAY_AVERAGED. have_value is false while
    // there is nothing settled to show yet.
    double display_raw = 0.0;
    bool have_value = adc_display_raw(have_sample, (int32_t)last.raw24, noise, display_raw);
    if (have_value) {
        // Calibration polynomial = (selected channel, selected range):
        // Button #1 picks the channel, Button #2 the range. Both values
        // are snapshotted once here so vac and dbm are computed from the
        // same (channel, range) even if a button is tapped mid-draw.
        const int cal_channel = g_adc.channel;
        const int cal_range   = s.range;
        vac = adc_to_vac(display_raw, cal_channel, cal_range);
        dbm = adc_to_dbm(display_raw, cal_channel, cal_range, 50.0);
        // NaN means the code is at or below this channel/range's measured
        // floor (the Z_A/Z_B/Z_C values, see calib_json.h): there is no
        // signal to report, so show "---" rather than a number.
        if (!std::isfinite(vac) || !std::isfinite(dbm)) {
            have_value = false;
        }
    }
    if (have_value) {
        vac_is_mv = fabs(vac) < 1.0;

        // Button #3 (g_vac_mode) now genuinely controls this side of the
        // readout: dBm shown directly, or converted to mW via
        // dbm_to_mw(). mW gets scientific notation outside a "normal"
        // range since it's linear and can span many orders of magnitude -
        // unlike dBm, which is already log-scaled and stays compact.
        char power_str[24];
        if (g_vac_mode == VAC_MODE_WATT) {
            double mw = dbm_to_mw(dbm);
            if (fabs(mw) < 0.001 || fabs(mw) >= 1000.0) {
                snprintf(power_str, sizeof(power_str), "%.3e", mw);
            } else {
                snprintf(power_str, sizeof(power_str), "%.4f", mw);
            }
        } else {
            snprintf(power_str, sizeof(power_str), "%.2f", dbm);
        }

        if (vac_is_mv) {
            snprintf(vbuf, sizeof(vbuf), "%.4f  %s", vac * 1000.0, power_str);
        } else {
            snprintf(vbuf, sizeof(vbuf), "%.4f  %s", vac, power_str);
        }
    } else {
        snprintf(vbuf, sizeof(vbuf), "---");
    }
#if ADC_APPLY_CALIBRATION
    uint16_t vcol = !have_value ? C_SUBTEXT : fault ? C_RED : C_GREEN;
#else
    // Uncorrected mode: always red, regardless of fault/have_value, so
    // this can't be mistaken for a normal calibrated reading at a glance.
    uint16_t vcol = C_RED;
#endif
    cv_text(vbuf, 240, 60, 6, vcol, C_BG, MC_DATUM);

#if ADC_APPLY_CALIBRATION
    cv_text(vac_is_mv ? "mV" : "Volt", 150, 100, 4, C_GREEN, C_BG, MC_DATUM);

    // Matches Button #3's own label logic exactly - the button now
    // actually reflects what's shown here, not just its own state.
    cv_text(g_vac_mode == VAC_MODE_WATT ? "mW" : "dBm", 360, 100, 4, C_GREEN, C_BG, MC_DATUM);
#else
    // ADC_APPLY_CALIBRATION==0: both unit labels replaced with "RAW" in
    // red - see config.h's comment on this macro. The number shown is
    // NOT a real voltage or power reading.
    cv_text("RAW", 150, 100, 4, C_RED, C_BG, MC_DATUM);
    cv_text("RAW", 360, 100, 4, C_RED, C_BG, MC_DATUM);
#endif
    // Raw code + status, for anyone debugging rather than just reading volts
    char rbuf[40];
    if (have_sample) {
        snprintf(rbuf, sizeof(rbuf), "raw 0x%06lX (%lu)",
                 (unsigned long)(last.raw24 & 0xFFFFFF), (unsigned long)last.raw24);
    } else {
        snprintf(rbuf, sizeof(rbuf), "raw --");
    }
    cv_text(rbuf, 240, 196, 2, C_SUBTEXT, C_BG, MC_DATUM);

    char sbuf[24];
    if (have_sample) {
        snprintf(sbuf, sizeof(sbuf), "AOR:%d  DOR:%d",
                 (last.status & MAX11270_STAT_AOR) ? 1 : 0,
                 (last.status & MAX11270_STAT_DOR) ? 1 : 0);
    } else {
        snprintf(sbuf, sizeof(sbuf), "AOR:-  DOR:-");
    }
    cv_text(sbuf, 240, 118, 2, fault ? C_RED : C_SUBTEXT, C_BG, MC_DATUM);

    // Noise bar (y=132-146), just below the AOR/DOR line (centred at y=118,
    // so it reaches down to about y=126 and clears the bar).
    draw_noise_bar(noise, C_GREEN);

#if BATTERY_INDICATOR
    // Battery icon (y=152-173), right side, just under the noise bar.
    draw_battery(battery);
#endif

    // 5-button row, y=232-276. The touch zones for all five buttons are in
    // touch_task (search "Button #1" etc there).

    // Button #1 - Channel select (x=7-93).
    cv_fillRoundRect(7, 232, 86, 44, 4, C_GREEN);
    snprintf(gbuf, sizeof(gbuf), "CH.  %s", kChannelNames[g_adc.channel]);
    cv_text(gbuf, 45, 258, 4, C_BG, C_GREEN, MC_DATUM);

    // Button #2 - Range select (x=101-187). Shows the current range;
    // tapping cycles it, the rotary knob steps it. Either way the range's
    // PGA gain is applied and its calibration polynomial selected.
    cv_fillRoundRect(101, 232, 86, 44, 4, C_GREEN);
    snprintf(gbuf, sizeof(gbuf), "Rng %d", (int)s.range + 1);
    cv_text(gbuf, 138, 258, 4, C_BG, C_GREEN, MC_DATUM);

    // Button #3 - dBm/mW display toggle (x=195-281). Genuinely switches
    // the right side of the big value readout above (see dbm_to_mw()),
    // not just this button's own label.
    cv_fillRoundRect(195, 232, 86, 44, 4, C_GREEN);
    cv_text(g_vac_mode == VAC_MODE_WATT ? "mW" : "dBm", 235, 258, 4, C_BG, C_GREEN, MC_DATUM);

    // Button #4 - Attenuator on/off toggle (x=289-375). Always drawn and
    // tappable; see touch_task's handler for why ON is blocked when
    // ADC_APPLY_CALIBRATION==0 (RAW mode) - this label just reflects
    // g_adc.attenuator_on, so it correctly always reads "Off" in that
    // build without needing its own compile guard here.
    cv_fillRoundRect(289, 232, 86, 44, 4, C_GREEN);
    cv_text("Att", 309, 258, 4, C_BG, C_GREEN, MC_DATUM);
    cv_text(g_adc.attenuator_on ? "On" : "Off", 349, 258, 4, C_BG, C_GREEN, MC_DATUM);

    // Button #5 - Auto range on/off (x=383-469). "Auto" and "On"/"Off" on
    // two lines: side by side in font 4 they would not fit the 86 px width.
    // The state line is centred at y=262 so its 26 px cell ends at the
    // button's bottom edge (y=275) instead of spilling below it.
    cv_fillRoundRect(383, 232, 86, 44, 4, C_GREEN);
    cv_text("Auto", 426, 244, 2, C_BG, C_GREEN, MC_DATUM);
    cv_text(s.auto_range ? "On" : "Off", 426, 262, 4, C_BG, C_GREEN, MC_DATUM);

    draw_footer("Rotate: gain 1x-128x  |  Push: next page");
}

static void begin_band(int b) {
    draw_y_offset = b * sprite_h;
    if (use_sprite) sprite.fillSprite(C_BG);
}
static void end_band(int b) {
    if (use_sprite) sprite.pushSprite(0, b * sprite_h);
}

static void render_ui(const AppState &s)
{
    int passes = use_sprite ? sprite_bands : 1;
    if (!use_sprite) { tft.fillScreen(C_BG); begin_band(0); }
    for (int b = 0; b < passes; b++) {
        if (use_sprite) begin_band(b);
        if (g_calib_mode) {
            // Full-screen override - takes priority over whatever page
            // was showing, same idea as any modal screen.
            draw_calib_screen();
        } else {
            switch (s.page) {
                case PAGE_INFO:      draw_page_info(s);     break;
                case PAGE_BARGRAPH:  draw_page_bargraph(s); break;
                case PAGE_SETTINGS:  draw_page_settings(s); break;
                case PAGE_ADC_GAIN:  draw_page_adc_gain(s); break;
                default: break;
            }
        }
        if (use_sprite) end_band(b);
    }
}

// =============================================================================
//  TASK 5 – adc_consumer  (Core 1, Priority 2)
//  Drains samples pushed by the MAX11270 driver's internal reader task
//  (that task is created inside max11270_init(), currently unpinned —
//  see note in setup()).
// =============================================================================
// Liveness counter for adc_consumer_task - see heartbeat_task for how this
// (and the driver's own g_max11270_reader_beats) get used to tell whether
// the ADC pipeline is actually still moving, without needing
// uxTaskGetSystemState/vTaskList (which need configUSE_TRACE_FACILITY,
// not compiled into the default PlatformIO Arduino-ESP32 FreeRTOS lib).
static volatile uint32_t g_adc_consumer_beats = 0;

#if SETTLE_TRACE
// ─── ADC settle-time trace ──────────────────────────────────────────────────
// See SETTLE_TRACE in config.h. Records the first SETTLE_TRACE_SAMPLES
// samples after a channel / range / attenuator change and prints them as one
// table once the last one has arrived. Printing is deliberately held back
// until then: at 115200 baud a few lines fill the serial TX buffer and block
// the caller, and blocking the consumer mid-trace would skew the very
// timestamps being measured.
static_assert(SETTLE_TRACE_SAMPLES >= 2 && SETTLE_TRACE_SAMPLES <= 64,
              "SETTLE_TRACE_SAMPLES must be 2..64");

// The driver masks the channel to 2 bits, so it can hold 3 even though only
// A/B/C (0..2) are used - never index kChannelNames with it unchecked.
static const char *channel_name(unsigned c) { return c < 3 ? kChannelNames[c] : "?"; }

static void settle_describe(char *out, size_t n,
                            unsigned old_ch, unsigned new_ch,
                            int old_rng, int new_rng,
                            int old_gain, int new_gain,
                            bool old_att, bool new_att)
{
    snprintf(out, n, "ch %s->%s  rng %d->%d  gain idx %d->%d  atten %s->%s",
             channel_name(old_ch), channel_name(new_ch),
             old_rng + 1, new_rng + 1, old_gain, new_gain,
             old_att ? "on" : "off", new_att ? "on" : "off");
}

struct SettleRow {
    uint32_t t_ms;    // millis() when the consumer received the sample
    int32_t  raw;     // raw24 code, unmodified
    uint16_t status;  // driver status word (AOR/DOR/...)
};

struct SettleTrace {
    SettleRow rows[SETTLE_TRACE_SAMPLES];
    int       n        = -1;   // -1 = idle, otherwise rows recorded so far
    uint32_t  id       = 0;    // traces started so far
    char      desc[96] = { 0 };

    // Begin a new trace. If one is still collecting, say so and drop it -
    // two changes in quick succession leave no clean settling to look at.
    void start(const char *what)
    {
        if (n >= 0) {
            Serial.printf("[SETTLE] #%lu abandoned after %d of %d samples: another change arrived first\n",
                          (unsigned long)id, n, SETTLE_TRACE_SAMPLES);
        }
        id++;
        n = 0;
        snprintf(desc, sizeof(desc), "%s", what);
    }

    // Feed one sample; does nothing while idle. Prints the table when the
    // last row arrives, then goes idle again.
    void add(uint32_t t_ms, int32_t raw, uint16_t status)
    {
        if (n < 0) return;
        rows[n].t_ms   = t_ms;
        rows[n].raw    = raw;
        rows[n].status = status;
        n++;
        if (n < SETTLE_TRACE_SAMPLES) return;
        print();
        n = -1;
    }

    void print() const
    {
        Serial.printf("[SETTLE] #%lu  %s\n", (unsigned long)id, desc);
        Serial.println("[SETTLE]   n  t_ms        raw     d_raw  status");
        for (int i = 0; i < n; i++) {
            char delta[16];
            if (i == 0) snprintf(delta, sizeof(delta), "-");
            else        snprintf(delta, sizeof(delta), "%+ld", (long)(rows[i].raw - rows[i - 1].raw));
            Serial.printf("[SETTLE] %3d %5ld %10ld %8s  0x%04X%s\n",
                          i, (long)(rows[i].t_ms - rows[0].t_ms), (long)rows[i].raw, delta,
                          (unsigned)rows[i].status,
                          ((rows[i].t_ms - rows[0].t_ms) < (uint32_t)SETTLE_HOLD_MS) ? " *" : "");
        }
        Serial.printf("[SETTLE] * = inside the %d ms hold, ignored by the noise window/readout/auto range. "
                      "n=0 is the first sample seen after the change and may still predate it.\n",
                      SETTLE_HOLD_MS);
    }
};
#endif // SETTLE_TRACE

static void adc_consumer_task(void *pvParameters)
{
    (void)pvParameters;
    max11270_sample_t sample;
    uint32_t print_counter = 0;
    uint8_t act_gain;

    // Noise window (see NoiseWindow). A channel, range (which carries the
    // gain) or attenuator change moves the signal level, so the window is
    // restarted when any of them changes - otherwise the step between the
    // old and new level would show up as a burst of "noise" on the bar.
    // The feed also keeps the average of every good sample since the last
    // change: with the input terminated that is the measurement floor, the
    // number to put in Z_A/Z_B/Z_C for this channel and range (calib_json.h).
    NoiseFeed nfeed;
    nfeed.begin(millis(), 0);
#if SETTLE_TRACE
    SettleTrace settle; // same trigger as the noise-window restart below
#endif
    decltype(g_adc.channel)       seen_channel = g_adc.channel;
    decltype(g_adc.attenuator_on) seen_atten   = g_adc.attenuator_on;
    uint8_t                       seen_range;
    xSemaphoreTake(g_state_mutex, portMAX_DELAY);
    seen_range = g_state.range;
    xSemaphoreGive(g_state_mutex);

    for (;;) {
        if (xQueueReceive(g_adc.out_queue, &sample, portMAX_DELAY) == pdTRUE) {
            g_adc_consumer_beats++;
            const uint32_t now_ms = millis(); // one clock reading per sample

            uint8_t cur_range, cur_auto;
            xSemaphoreTake(g_state_mutex, portMAX_DELAY);
            cur_range = g_state.range;
            cur_auto  = g_state.auto_range;
            xSemaphoreGive(g_state_mutex);
            // Read once, so the comparison and what gets remembered agree.
            const decltype(g_adc.channel)       cur_channel = g_adc.channel;
            const decltype(g_adc.attenuator_on) cur_atten   = g_adc.attenuator_on;
            if (cur_channel != seen_channel || cur_atten != seen_atten ||
                cur_range != seen_range) {
#if SETTLE_TRACE
                // Gain only changes with the range (see range_apply_locked), so
                // the gain index is looked up from the range mapping.
                const int old_gain = seen_range < NUM_RANGES ? (int)kRangeGainStep[seen_range] : -1;
                const int new_gain = cur_range  < NUM_RANGES ? (int)kRangeGainStep[cur_range]  : -1;
                char what[96];
                settle_describe(what, sizeof(what),
                                (unsigned)seen_channel, (unsigned)cur_channel,
                                (int)seen_range, (int)cur_range,
                                old_gain, new_gain,
                                seen_atten, cur_atten);
                settle.start(what);
#endif
                seen_channel = cur_channel;
                seen_atten   = cur_atten;
                seen_range   = cur_range;
                // Hold for SETTLE_HOLD_MS (config.h) before trusting samples again.
                nfeed.begin(now_ms, SETTLE_HOLD_MS);
            }
#if SETTLE_TRACE
            // Every sample from the one that revealed the change onwards,
            // INCLUDING those the noise window ignores - those are exactly
            // the ones this trace exists to show.
            settle.add(now_ms, (int32_t)sample.raw24, (uint16_t)sample.status);
#endif
            // A DOR-flagged sample is the converter's output clipped at zero.
            // The feed counts it as a 0 like any other sample (see NoiseFeed).
            // It still shows in the status line and the settle trace, and is
            // counted separately for the log below.
            const bool dor = (sample.status & MAX11270_STAT_DOR) != 0;
            const NoiseStats noise = nfeed.feed(now_ms, dor, (int32_t)sample.raw24);

            // Auto range (Button #5). The decision is pure (autorange_decide);
            // acting on it uses the same range_apply_locked() path as the
            // Range button, so gain, attenuator and calibration polynomial
            // still move together. The change-detection block above then
            // sees the new range on the next sample, restarts the noise
            // window, and (if enabled) starts a settle trace - so nothing
            // is decided from samples taken while the ADC is still settling.
            if (cur_auto) {
                const bool overrange = (sample.status & MAX11270_STAT_AOR) != 0;
                const int  want      = autorange_decide((int)cur_range, noise, overrange);
                if (want != (int)cur_range) {
                    RangeApplyResult r = { 0xFF, -1 };
                    bool applied = false;
                    xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                    // Re-check under the lock: a manual change (which also
                    // switches auto range off) may have got in first.
                    if (g_state.auto_range && g_state.range == cur_range) {
                        r = range_apply_locked((uint8_t)want);
                        applied = true;
                    }
                    xSemaphoreGive(g_state_mutex);

                    if (applied) {
                        // SPI writes after releasing g_state_mutex, like every
                        // other path that changes gain or attenuator.
                        if (r.new_gain_step != 0xFF) {
                            max11270_set_gain(&g_adc, kGainSteps[r.new_gain_step]);
                        }
                        if (r.new_attenuator_on >= 0) {
                            max11270_set_attenuator(&g_adc, r.new_attenuator_on != 0);
                        }
                        Serial.printf("[AUTO] rng %d -> %d  (%s: mean raw %ld, %u samples)\n",
                                      (int)cur_range + 1, want + 1,
                                      overrange ? "overrange" : (want > (int)cur_range ? "signal low" : "signal high"),
                                      (long)noise.mean, (unsigned)noise.count);
                    }
                }
            }

            xSemaphoreTake(g_latest_sample_mutex, portMAX_DELAY);
            g_latest_sample = sample;
            g_latest_sample_valid = true;
            g_noise = noise;
            xSemaphoreGive(g_latest_sample_mutex);

            if (sample.status & MAX11270_STAT_AOR) {
                /* analog input overrange - handle as needed */
            }
            /* At 1000 SPS this task runs 1000x/second. Printing every
             * sample would (a) far exceed what a 115200 baud UART can
             * carry, causing Serial to back up/block, and (b) is exactly
             * the kind of float-printf-under-load scenario that overflowed
             * this task's stack before. Throttle to ~10 Hz instead. */
            if ((print_counter++ % 100) == 0) {
                max11270_read_reg(MAX11270_REG_CTRL2, &act_gain, 1);
				Serial.printf("[ADC] raw=%ld volts=%.6f status=0x%04X AOR=%d DOR=%d PDSTAT=%d GAIN=%d\n",
              		(long)sample.raw24, sample.volts, sample.status,
              		(sample.status & MAX11270_STAT_AOR) ? 1 : 0,
              		(sample.status & MAX11270_STAT_DOR) ? 1 : 0,
              		(sample.status >> 10) & 0x3,
                    act_gain & 0x7);
                // Same (channel, range) selection as draw_page_adc_gain(),
                // so this debug log matches what the display shows.
                const int cal_channel = g_adc.channel;
                xSemaphoreTake(g_state_mutex, portMAX_DELAY);
                const int cal_range   = g_state.range;
                xSemaphoreGive(g_state_mutex);
                Serial.printf("[ADC] ch=%s rng=%d polynom adjusted raw=%ld, dBm= %2.2f\n",
                              kChannelNames[cal_channel], cal_range + 1, (long)sample.raw24,
                              adc_to_dbm(sample.raw24, cal_channel, cal_range, 50.0));
                Serial.printf("[ADC] ch=%s rng=%d polynom adjusted raw=%ld, vac= %2.2f\n",
                              kChannelNames[cal_channel], cal_range + 1, (long)sample.raw24,
                              adc_to_vac(sample.raw24, cal_channel, cal_range));
                // The numbers behind the noise bar - use these to pick
                // NOISE_BAR_FULLSCALE_COUNTS (config.h).
                Serial.printf("[ADC] noise n=%u lo=%ld hi=%ld mean=%ld p2p=%ld (bar half = %d counts)\n",
                              (unsigned)noise.count, (long)noise.lo, (long)noise.hi,
                              (long)noise.mean, (long)(noise.hi - noise.lo),
                              NOISE_BAR_FULLSCALE_COUNTS);
                // Averages of every sample since the last change (DOR samples
                // counted as 0). With the input TERMINATED, the floor for
                // Z_A/Z_B/Z_C is the "recent" value once the unit has warmed
                // up: the floor drifts, so the lifetime mean "mean" lags it.
                Serial.printf("[ADC] since change: n=%lu mean=%ld  recent(%d)=%ld  |  DOR samples (clipped at 0) so far: %lu\n",
                              (unsigned long)nfeed.since_n,
                              (long)nfeed.since_mean(),
                              (int)NoiseFeed::kRecent,
                              (long)nfeed.recent_mean(),
                              (unsigned long)nfeed.dor_count);

            }
        }
    }
}

// =============================================================================
//  TASK 3 – ui_task  (Core 0, Priority 4)
// =============================================================================
static void ui_task(void *pvParam)
{
    AppState local, prev;
    memset(&prev, 0xFF, sizeof(prev));
    for (;;) {
        xSemaphoreTake(g_state_mutex, portMAX_DELAY);
        memcpy(&local, &g_state, sizeof(AppState));
        xSemaphoreGive(g_state_mutex);

        // ADC gain page shows a live voltage reading that updates
        // continuously, not just when gain_step changes - but redrawing
        // the WHOLE screen at the normal 33ms/~30Hz UI cadence pushes the
        // entire 3-band sprite over the shared SPI bus non-stop, competing
        // heavily with the MAX11270's own SPI traffic. Throttle this page's
        // forced redraw to ~3Hz instead - plenty readable for a voltage
        // display, far lighter on the bus.
        static TickType_t last_gain_page_redraw = 0;
        static bool       last_calib_mode = false;
        static int        last_calib_step = -1;
        TickType_t now_ticks = xTaskGetTickCount();
        bool force_redraw = (local.page == PAGE_ADC_GAIN && !g_calib_mode) &&
                             ((now_ticks - last_gain_page_redraw) > pdMS_TO_TICKS(300));
        if (force_redraw) {
            last_gain_page_redraw = now_ticks;
        }

        // Calibration screen isn't part of AppState, so the memcmp below
        // wouldn't notice it starting, ending, or advancing to the next
        // target - redraw immediately on any of those transitions.
        bool calib_mode_now = g_calib_mode;
        int  calib_step_now = g_calib_step;
        if (calib_mode_now != last_calib_mode || calib_step_now != last_calib_step) {
            force_redraw = true;
            last_calib_mode = calib_mode_now;
            last_calib_step = calib_step_now;
        }

        if (force_redraw || memcmp(&local, &prev, sizeof(AppState)) != 0) {
            render_ui(local);
            memcpy(&prev, &local, sizeof(AppState));
        }
        vTaskDelay(pdMS_TO_TICKS(33));
    }
}

// =============================================================================
//  TASK 4 – heartbeat_task  (Core 0, Priority 1)
// =============================================================================
static void heartbeat_task(void *pvParam)
{
    const uint8_t LED = 2;
    pinMode(LED, OUTPUT);
    uint32_t uptime_s = 0;
    UBaseType_t last_task_count = uxTaskGetNumberOfTasks();
    uint32_t last_reader_beats = 0, last_consumer_beats = 0;

    for (;;) {
        digitalWrite(LED, HIGH); vTaskDelay(pdMS_TO_TICKS(50));
        digitalWrite(LED, LOW);  vTaskDelay(pdMS_TO_TICKS(4950));
        uptime_s += 5;

        UBaseType_t task_count = uxTaskGetNumberOfTasks();

        // Lightweight liveness check that needs no special FreeRTOS config
        // (unlike uxTaskGetSystemState/vTaskList, which need
        // configUSE_TRACE_FACILITY - not compiled into the prebuilt
        // PlatformIO Arduino-ESP32 FreeRTOS lib by default). Each counter
        // increments once per loop iteration inside its own task; if the
        // delta over this 5s window is 0, that task has stopped doing
        // work, whether it exited, crashed, or is just stuck.
        uint32_t reader_beats   = g_max11270_reader_beats;
        uint32_t consumer_beats = g_adc_consumer_beats;

        Serial.printf("[HRTBT] uptime=%lus  heap=%lu B  tasks=%u  "
                      "readerBeats=+%lu  consumerBeats=+%lu\n",
                      (unsigned long)uptime_s,
                      (unsigned long)esp_get_free_heap_size(),
                      task_count,
                      (unsigned long)(reader_beats - last_reader_beats),
                      (unsigned long)(consumer_beats - last_consumer_beats));

        if (task_count != last_task_count) {
            Serial.printf("[HRTBT] *** task count changed %u -> %u ***\n",
                          (unsigned)last_task_count, (unsigned)task_count);
        }
        if ((reader_beats - last_reader_beats) == 0) {
            Serial.println("[HRTBT] *** MAX11270 reader task produced NOTHING this window ***");
        }

        last_task_count    = task_count;
        last_reader_beats  = reader_beats;
        last_consumer_beats = consumer_beats;

        // Piggyback settings persistence on this existing 5s tick rather
        // than adding a new timer - settings_save() internally no-ops if
        // brightness/touch-calib haven't actually changed since the last
        // save, so this doesn't wear the flash on every heartbeat.
        uint8_t current_brightness;
        xSemaphoreTake(g_state_mutex, portMAX_DELAY);
        current_brightness = g_state.brightness;
        xSemaphoreGive(g_state_mutex);
        settings_save(current_brightness);
    }
}

#if BATTERY_INDICATOR
// =============================================================================
//  TASK – battery_task  (Core 0, lowest priority)
//
//  Reads the battery through the divider on BATTERY_ADC_PIN every
//  BATTERY_SAMPLE_PERIOD_MS and publishes the result in g_battery for the
//  ADC page. Improvements over analogRead() * a fudge factor:
//   - analogReadMilliVolts() applies the chip's factory ADC calibration, so
//     only the divider ratio has to be tuned (BATTERY_DIVIDER_RATIO);
//   - each reading is the mean of 16 samples, because the ADC is noisy
//     while the TFT/SPI traffic is running;
//   - readings are smoothed, so the percentage doesn't flicker;
//   - a reading too low to be a battery is shown as "no battery" rather than
//     as a red 0 %.
//  Integer-only printf on purpose: float printf needs a bigger stack.
// =============================================================================
static void battery_task(void *pvParam)
{
    (void)pvParam;
    static const int kOversamples = 16;

    int32_t ema_mv   = -1;  // -1 = no running value yet
    int     last_pct = -2;  // -2 = nothing logged yet, -1 = last logged "no battery"

    for (;;) {
        uint32_t sum_mv = 0;
        for (int i = 0; i < kOversamples; i++) {
            sum_mv += analogReadMilliVolts(BATTERY_ADC_PIN);
            vTaskDelay(pdMS_TO_TICKS(2));
        }
        const int32_t pin_mv = (int32_t)(sum_mv / kOversamples);
        const int32_t bat_mv = (int32_t)((float)pin_mv * BATTERY_DIVIDER_RATIO + 0.5f);

        BatteryStatus st = { 0, 0, false };
        if (bat_mv >= BATTERY_PRESENT_MIN_MV) {
            ema_mv = battery_smooth(ema_mv, bat_mv);
            st.mv    = (uint16_t)ema_mv;
            st.pct   = battery_percent_from_mv(ema_mv);
            st.valid = true;
        } else {
            ema_mv = -1; // start fresh when a battery reappears
        }

        xSemaphoreTake(g_latest_sample_mutex, portMAX_DELAY);
        g_battery = st;
        xSemaphoreGive(g_latest_sample_mutex);

        // Log only when the shown value changes, so this doesn't add to the
        // heartbeat's chatter. pin= and bat= are what you need to calibrate
        // BATTERY_DIVIDER_RATIO against a multimeter.
        const int shown = st.valid ? (int)st.pct : -1;
        if (shown != last_pct) {
            if (st.valid) {
                Serial.printf("[BATT] pin=%ld mV  bat=%ld mV (smoothed %u mV) -> %u %%\n",
                              (long)pin_mv, (long)bat_mv, (unsigned)st.mv, (unsigned)st.pct);
            } else {
                Serial.printf("[BATT] pin=%ld mV -> bat=%ld mV, below %d mV: no battery sensed\n",
                              (long)pin_mv, (long)bat_mv, BATTERY_PRESENT_MIN_MV);
            }
            last_pct = shown;
        }

        vTaskDelay(pdMS_TO_TICKS(BATTERY_SAMPLE_PERIOD_MS));
    }
}
#endif // BATTERY_INDICATOR

// =============================================================================
//  Sprite allocation
// =============================================================================
static void init_sprite()
{
    const int screen_w = tft.width();   // 480 after setRotation(3), not hardcoded
    const int screen_h = tft.height();  // 320 after setRotation(3), not hardcoded

    const int candidates[] = { 160, 80, 40, 0 };
    for (int i = 0; candidates[i] != 0; i++) {
        int h = candidates[i];
        sprite.setColorDepth(16);
        void *ptr = sprite.createSprite(screen_w, h);   // was hardcoded 320
        if (ptr != nullptr) {
            sprite_h     = h;
            sprite_bands = (screen_h + h - 1) / h;       // was hardcoded 480
            use_sprite   = true;
            Serial.printf("[TFT] Sprite %dx%d  bands=%d  heap=%lu B\n",
                          screen_w, h, sprite_bands, (unsigned long)esp_get_free_heap_size());
            return;
        }
        sprite.deleteSprite();
    }
    use_sprite = false; sprite_h = screen_h; sprite_bands = 1;
    Serial.println("[TFT] No sprite — direct draw mode");
}

// =============================================================================
//  setup()
// =============================================================================
void setup()
{
#ifndef SERIAL2_UART
    Serial.setRxBufferSize(4096);  // default 256 is too small for the calibration JSON payload
#endif
    Serial.begin(115200);
    delay(300);
    Serial.printf("\n=== Rotary + ILI9341 + Touch + MAX11270 FreeRTOS Demo ===\n");
    Serial.printf("Free heap at boot: %lu B\n", (unsigned long)esp_get_free_heap_size());

    // TEMPORARY DIAGNOSTIC - wipes the ENTIRE NVS partition (every
    // namespace: "calib", "appset", anything else), not just the
    // calibration data calib_nvs_erase() touches. Remove this block once
    // you've confirmed the issue is/isn't NVS-related - leaving it in
    // means EVERY boot wipes all settings, including touch calibration
    // and brightness.
#ifdef NVS_FULL_ERASE
        Serial.println("[DIAG] NVS_FULL_ERASE defined - erasing entire NVS partition");
        esp_err_t err = nvs_flash_erase();
        Serial.printf("[DIAG] nvs_flash_erase() -> %s\n", esp_err_to_name(err));
        err = nvs_flash_init();
        Serial.printf("[DIAG] nvs_flash_init() -> %s\n", esp_err_to_name(err));
#endif

    g_state_mutex = xSemaphoreCreateMutex();
    g_latest_sample_mutex = xSemaphoreCreateMutex();

    // Load persisted touch calibration + brightness from NVS, falling
    // back to config.h's #defines (the "current found optimum" values)
    // if nothing's been saved yet. Must happen before touch_task starts,
    // since read_touch() uses g_touch_calib immediately.
    {
        TouchCalib defaults;
        defaults.x_min    = TOUCH_X_MIN;
        defaults.x_max    = TOUCH_X_MAX;
        defaults.y_min    = TOUCH_Y_MIN;
        defaults.y_max    = TOUCH_Y_MAX;
        defaults.swap_xy  = (bool)TOUCH_SWAP_XY;
        defaults.invert_x = (bool)TOUCH_INVERT_X;
        defaults.invert_y = (bool)TOUCH_INVERT_Y;

        uint8_t loaded_brightness;
        settings_load(defaults, g_state.brightness, &loaded_brightness);
        g_state.brightness = loaded_brightness;
    }

    // Encoder — CLK/DT/SW all use external on-board pull-ups (required for
    // GPIO34/35 regardless, since those input-only pins have no internal
    // pull resistors), so plain INPUT is correct here rather than
    // INPUT_PULLUP.
    pinMode(ENC_CLK, INPUT);
    pinMode(ENC_DT,  INPUT);
    pinMode(ENC_SW,  INPUT);
    attachInterrupt(digitalPinToInterrupt(ENC_CLK), encoder_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_DT),  encoder_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_SW),  button_isr,  FALLING);

    // Shared VSPI bus for TFT/touch/MAX11270 (SCK, MISO, MOSI; no default CS).
    // Safe to call once here even if TFT_eSPI/XPT2046 also touch these pins
    // internally, as long as everyone re-uses this same bus instance.
    SPI.begin(/*SCK*/18, /*MISO*/19, /*MOSI*/23, /*SS unused*/-1);

    // MAX11270 ADC
    pinMode(MAX11270_CS_PIN, OUTPUT);
    digitalWrite(MAX11270_CS_PIN, HIGH);
    pinMode(MAX11270_RDY_PIN, INPUT);
    // NOTE: the RDYB interrupt is intentionally NOT attached here yet.
    // g_adc.drdy_sem doesn't exist until max11270_init() creates it below;
    // attaching the interrupt this early let a RDYB glitch during TFT/touch
    // init call xSemaphoreGiveFromISR() on a NULL handle, which crashes
    // FreeRTOS ("assert failed: xQueueGiveFromISR queue.c:1217 (pxQueue)").
    // The attachInterrupt() call now happens after max11270_init() succeeds.

    // TFT
    tft.init();
    tft.setRotation(3);
    Serial.printf("[TFT] effective size after rotation: %dx%d\n", tft.width(), tft.height());
    tft.fillScreen(C_BG);
    tft.setTextFont(4);
    tft.setTextColor(C_ACCENT, C_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Initialising...", 120, 140);

    init_sprite();

    // Touch — must begin() after TFT init (shared SPI bus)
    touch.begin();
    touch.setRotation(0);
    Serial.println("[Touch] XPT2046 ready");

    tft.setTextFont(2);
    tft.setTextColor(C_SUBTEXT, C_BG);
    if (use_sprite) {
        char sbuf[36];
        snprintf(sbuf, sizeof(sbuf), "Sprite: %dx%d (%d bands)", tft.width(), sprite_h, sprite_bands);
        tft.drawString(sbuf, 240, 175);
    } else {
        tft.drawString("Direct draw mode", 240, 175);
    }
    tft.drawString("Touch: XPT2046 ready", 240, 195);

/* add-on for serial communication */
 /*   const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_2, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_2, &uart_config);
    uart_set_pin(UART_NUM_2, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE); */
    // Which serial port actually carries calibration JSON - see
    // SERIAL2_UART's comment in config.h. This is the piece that makes
    // calib_json.cpp's and this file's own #ifdef SERIAL2_UART guards
    // meaningful: without picking the matching object here, calib_json
    // would keep reading from Serial2 regardless of the flag.
#ifdef SERIAL2_UART
    calib_json_start(Serial2, 115200);
#else
    calib_json_start(Serial, 115200);
#endif

    delay(1200);

    xTaskCreatePinnedToCore(encoder_task,   "encoder",   3072, nullptr, PRIO_ENCODER,   nullptr, 1);
    xTaskCreatePinnedToCore(touch_task,     "touch",     3072, nullptr, PRIO_TOUCH,     nullptr, 0);
    xTaskCreatePinnedToCore(ui_task,        "ui",        8192, nullptr, PRIO_UI,        nullptr, 0);
    xTaskCreatePinnedToCore(heartbeat_task, "heartbeat", 2048, nullptr, PRIO_HEARTBEAT, nullptr, 0);
#if BATTERY_INDICATOR
    xTaskCreatePinnedToCore(battery_task,   "battery",   3072, nullptr, PRIO_HEARTBEAT, nullptr, 0);
#endif

    /* comm task add-on */
    //xTaskCreatePinnedToCore(rx_task, "uart_rx_task", 1024*2, NULL, configMAX_PRIORITIES, NULL,  1);
    //xTaskCreatePinnedToCore(tx_task, "uart_tx_task", 1024*2, NULL, configMAX_PRIORITIES-1, NULL,  1);

    // 2.5V reference, PGA gain x1, bipolar input, continuous conversion
    // at 1000 samples/sec, queue depth 16, reader-task priority 3.
    // NOTE: on ESP-IDF/Arduino-ESP32, FreeRTOS's task stack-size parameter
    // is in BYTES, not words as in vanilla FreeRTOS. 4096 bytes gives
    // headroom for the SPI transfer chain + float math in the reader task;
    // 512 (bytes) was far too small and caused a stack-canary crash.
    //
    // Start at the gain the current range is mapped to (config.h's
    // RANGEn_GAIN_STEP), not a hard-coded x1 - otherwise changing the
    // Rng 1 mapping would leave the hardware at x1 while the Rng 1
    // polynomial expects a different gain until the first range change.
    gain_step = kRangeGainStep[g_state.range];
    bool ok = max11270_init(&g_adc,
                             REFERENCE_VOLTS,
                             kGainSteps[gain_step],
                             true /* unipolar */,
                             true  /* continuous */,
                             MAX11270_RATE_125SPS,
                             16,
                             3,
                             4096);
    if (!ok) {
        Serial.println("[MAX11270] init FAILED — check wiring/semaphore alloc");
    } else {
        // Safe to arm the RDYB interrupt now that g_adc.drdy_sem exists.
        attachInterrupt(digitalPinToInterrupt(MAX11270_RDY_PIN), RDYB_EXTI_IRQHandler, FALLING);

        // Apply the current range's attenuator state too, same reasoning
        // as the gain line above: the driver has no "initial attenuator"
        // parameter the way it does for gain, so without this the
        // hardware would silently stay off at boot even when the current
        // range is mapped to attenuator-on (e.g. Rng 1 by default) -
        // exactly the mismatch observed when this was first added. RAW
        // mode (ADC_APPLY_CALIBRATION==0) still forces it off regardless,
        // same rule as everywhere else.
#if ADC_APPLY_CALIBRATION
        max11270_set_attenuator(&g_adc, kRangeAttenOn[g_state.range]);
#else
        max11270_set_attenuator(&g_adc, false);
#endif
    }

    // Stack bumped from 2048 -> 6144 bytes: Serial.printf() with a %f
    // float specifier pulls in vsnprintf's dtoa float-to-string routines,
    // which use noticeably more stack than integer/string formatting. With
    // only 2048 bytes this task overflowed its stack (worse: an RDYB
    // interrupt landing mid-printf runs on top of this same stack on
    // ESP32, since GPIO ISRs aren't given a separate stack here).
    xTaskCreatePinnedToCore(adc_consumer_task, "adc_consumer", 6144, nullptr, 2, nullptr, 1);

    #ifdef ENABLE_CAL_INFO
    show_cal_data();
    #endif

    Serial.println("All tasks started.\n");
}

void loop()
{
    vTaskDelay(portMAX_DELAY);
}
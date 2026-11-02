#pragma once
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

// Calibration table layout matching the JSON schema:
//   "A_1".."A_3", "B_1".."B_3", "C_1".."C_3", each {"value":[5 floats]}
// Interpreted as 3 channels (A/B/C), each with 3 coefficient sets, each a
// 5-term polynomial: coeffs[0] + coeffs[1]*x + coeffs[2]*x^2 + ... x^4.
//
// Optional small-correction schema, added later:
//   "M_A", "M_B", "M_C", each {"value":[3 floats]}
// One value per range (1/2/3), added directly to that range's coeffs[0]
// (the polynomial's constant/log-space term) in adc_dbm.cpp - a value of
// 0.0 (the default, and what an all-zero/never-sent table reads as) is a
// no-op. Meant for small manual touch-ups without re-deriving a whole
// polynomial: unlike A_1.."C_3, which must ALWAYS be sent as a complete
// set of all 9 (any subset is rejected - see calib_json.cpp), M_A/M_B/M_C
// are each independently optional - send one, all three, alongside a
// full polynomial update, or not at all. Whichever of M_A/M_B/M_C a given
// JSON message doesn't include is left exactly as it was (not reset to
// 0.0), so a correction, once sent, persists across later polynomial-only
// updates too.
//
// Second optional schema, the measurement FLOOR ("zero"):
//   "Z_A", "Z_B", "Z_C", each {"value":[3 floats]}
// One value per range (1/2/3): the raw ADC code the front end reads with the
// input TERMINATED, in raw counts. adc_dbm.cpp subtracts it from the raw code
// BEFORE the polynomial is evaluated, so a reading near the floor isn't
// inflated by the floor itself (a -50 dBm signal read about 1.6 dB high
// without it). Subtracting is an additive correction in the raw domain; the
// M_A/B/C values above are a multiplicative (log-space) one - they do
// different jobs and can be used together. A code at or below its floor has
// no signal to report: adc_to_vac()/adc_to_dbm() return NaN for it.
// Same rules as M_A/B/C: each key independently optional, anything not in a
// message is left as it was, persists across later polynomial updates, and a
// value of 0.0 (the default) is a no-op. Values must be 0..16777215 (a raw
// 24-bit code) - anything else, including nan/inf, rejects the whole message.
// To measure one: terminate the input, let the unit warm up for a couple of
// minutes (the floor drifts down during the first minute or so), select that
// channel and range by hand (this turns auto range off), and read the
// "recent(256)" value in the "[ADC] since change: n=... mean=... recent(256)=..."
// log line. "mean" is a lifetime average and lags a drifting floor; "recent"
// follows it. Samples the converter clipped at zero (DOR) are counted as 0 in
// both, which is what keeps the average honest close to the floor.
struct ChannelCalib {
    float coeffs[3][5];   // [set 0..2] x [coefficient 0..4]
};

struct CalibTable {
    ChannelCalib ch[3];          // 0=A, 1=B, 2=C
    float m_correction[3][3];    // [channel 0..2][range 0..2], see M_A/B/C above
    float z_floor[3][3];         // [channel 0..2][range 0..2], raw counts, see Z_A/B/C above
    bool  valid = false;
};

// Call once from setup(). Starts a FreeRTOS task that owns `serialPort`,
// accumulates one complete JSON object at a time (brace-depth framed, so
// it doesn't care about embedded newlines/whitespace or the object
// arriving split across several serial reads), parses it with ArduinoJson,
// and republishes the result into a mutex-protected shared table.
void calib_json_start(HardwareSerial &serialPort,
                       uint32_t baud,
                       UBaseType_t taskPriority = 2,
                       BaseType_t coreId = 0,
                       uint16_t taskStackBytes = 6144);

// Thread-safe copy of the most recently parsed table. Returns false (and
// leaves `out` untouched) if nothing valid has been received yet.
bool calib_json_get(CalibTable &out);

// --- NVS persistence -------------------------------------------------------
// calib_json_start() calls these automatically (load once at startup,
// save whenever a genuinely new table is parsed) - you normally don't need
// to call them yourself. Exposed individually in case you want manual
// control, e.g. a "factory reset calibration" menu action.
// The M_A/B/C corrections are stored under their OWN NVS key, independent
// of the polynomial coefficients: a missing/old-format corrections entry
// (e.g. calibration saved before this feature existed) just loads as all
// zero (no-op), it does not invalidate the polynomial data, and saving
// new corrections never touches the polynomial entry either.
// The Z_A/B/C floors work the same way under a third key ("zfloor"): missing
// = all zero (no-op), never affects the polynomial or the M entry.
bool calib_nvs_save(const CalibTable &table);
bool calib_nvs_load(CalibTable &out);
void calib_nvs_erase();
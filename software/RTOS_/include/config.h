#pragma once
// ─────────────────────────────────────────────────────────────────────────────
// config.h  –  Pin map, constants, shared FreeRTOS handles
// ─────────────────────────────────────────────────────────────────────────────
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#define firmware "3.0"

// Uncomment to receive calibration JSON over a dedicated Serial2 (GPIO21
// RX / GPIO22 TX) as before. Leave commented (the default) to share the
// main USB Serial connection instead - calibration JSON can then be
// pasted directly into the same terminal/monitor already open for the
// debug log, with no second serial cable or terminal program needed.
// Both calib_json.cpp (which serial port to actually read from) and
// main.cpp (whether the debug Serial's RX buffer needs bumping for the
// JSON payload) key off this same flag - see both for the full picture.
//#define SERIAL2_UART 1

// ── Rotary encoder ────────────────────────────────────────────────────────────
#define ENC_CLK   34   // A channel
#define ENC_DT    33   // B channel
#define ENC_SW    35   // push button (if present, else leave unconnected)

// ── Touch (XPT2046) ──────────────────────────────────────────────────────────
#define TOUCH_CS_PIN   16   // XPT2046 CS — shares SPI bus with TFT
#define TOUCH_IRQ_PIN  32   // XPT2046 IRQ (T_IRQ) — input only, no pull-up needed

// Touch calibration — run once with serial output to find your values
// These map raw ADC (0-4095) to screen pixels (0-239, 0-319)
#define TOUCH_X_MIN    643
#define TOUCH_X_MAX   3656
#define TOUCH_Y_MIN    343
#define TOUCH_Y_MAX   3690
#define TOUCH_SWAP_XY    1   // set 1 if axes are swapped on your module
#define TOUCH_INVERT_X   1   // set 1 if x is mirrored
#define TOUCH_INVERT_Y   1   // set 1 if y is mirrored

// ── ADC calibration ───────────────────────────────────────────────────────────
// Set to 0 to bypass the per-channel/range calibration polynomial
// entirely: adc_to_vac()/adc_to_dbm() (adc_dbm.cpp) then return an
// uncorrected, monotonic value derived directly from the raw ADC code -
// NOT a real voltage - instead of evaluating the fitted curve. Whatever
// calibration is already in NVS is left completely alone either way,
// just unused while this is 0. Intended for taking clean, uncorrected
// measurements while building a NEW set of polynomials: sweep a known
// reference and record (raw code, reference value) pairs - the raw code
// is what matters, this value is just a rough on-screen indicator.
// draw_page_adc_gain() shows "RAW" in red instead of the normal Vac/dBm
// units whenever this is 0, so the mode can't be mistaken for a
// calibrated reading.
#define ADC_APPLY_CALIBRATION 1

// ── ADC range -> PGA gain mapping ─────────────────────────────────────────────
// The gain each range runs at, as an INDEX into kGainSteps[] in main.cpp:
//     0 = x1   1 = x2   2 = x4   3 = x8   4 = x16   5 = x32   6 = x64   7 = x128
//
// Selecting a range (Range button or rotary knob) does two things together:
// it applies that range's gain, AND it selects that range's calibration
// polynomial (the JSON's A_1/A_2/A_3, B_1/..., C_1/... entries). So if you
// change a mapping here, the polynomials for that range must have been
// measured at the SAME gain, otherwise the readings will be wrong.
// Values are checked at compile time (see static_assert in main.cpp).
#define RANGE1_GAIN_STEP   0   // Rng 1 -> x1
#define RANGE2_GAIN_STEP   2   // Rng 2 -> x4
#define RANGE3_GAIN_STEP   4   // Rng 3 -> x16

// Attenuator state each range runs at (1=on, 0=off). Applied by the same
// range_apply_locked() in main.cpp that applies the gain above, so
// selecting a range sets BOTH together - gain, attenuator, and
// calibration polynomial all follow the range as one unit. Only takes
// effect when ADC_APPLY_CALIBRATION==1: in RAW mode the attenuator is
// always forced off regardless of these values, so it isn't one more
// uncontrolled variable while collecting clean measurement data (see
// adc_dbm.cpp / the Button #4 handler in main.cpp).
#define RANGE1_ATTEN_ON    1   // Rng 1 -> attenuator on
#define RANGE2_ATTEN_ON    0   // Rng 2 -> attenuator off
#define RANGE3_ATTEN_ON    0   // Rng 3 -> attenuator off

// ── Auto range ────────────────────────────────────────────────────────────────
// Button #5 on the ADC page switches auto range on/off. While it is on, the
// range follows the signal using the mean raw24 code of the noise window
// (the last NOISE_WINDOW_SAMPLES samples) and the switch points below, one
// range step at a time. Turning the range by hand (Button #2 or the knob)
// switches auto range off. Same thresholds for channel A and B.
//
// Each threshold is a raw24 code in the raw scale of the range it is tested
// IN (the one currently selected), which depends on that range's gain and
// attenuator setting above - change RANGEn_GAIN_STEP / RANGEn_ATTEN_ON and
// these must be re-measured. The dBm values are only labels.
//   falling signal, in Rng 1: mean below ...  -> Rng 2
//   falling signal, in Rng 2: mean below ...  -> Rng 3
//   rising signal,  in Rng 3: mean above ...  -> Rng 2
//   rising signal,  in Rng 2: mean above ...  -> Rng 1
// The gap between "falling" and "rising" is the hysteresis that stops it
// flipping back and forth. After a switch, the signal as read in the NEW
// range must sit between that range's own two thresholds, or it will switch
// straight back.
#define AUTORANGE_R1_TO_R2_BELOW_RAW   57450     // ~ -10 dBm
#define AUTORANGE_R2_TO_R3_BELOW_RAW   27680     // ~ -30 dBm
#define AUTORANGE_R3_TO_R2_ABOVE_RAW   277000    // observed on the bench: back to Rng 2 at about
                                                 // -25 dBm on a rising signal (earlier label said -15)
#define AUTORANGE_R2_TO_R1_ABOVE_RAW   3985097   // ~  -5 dBm
// Samples (after the SETTLE_HOLD_MS that is skipped following any change)
// the window needs before auto range will decide anything. Must not
// exceed NOISE_WINDOW_SAMPLES.
#define AUTORANGE_MIN_SAMPLES          5
// 1 = auto range is on at power-up. It is never on in RAW mode
// (ADC_APPLY_CALIBRATION 0): the attenuator is forced off there, which
// changes the raw scale the thresholds were measured in.
#define AUTORANGE_DEFAULT_ON           0

// ── ADC noise bar (ADC page) ──────────────────────────────────────────────────
// A bar centred on the MEAN of the last NOISE_WINDOW_SAMPLES raw24 codes,
// reaching left to the lowest and right to the highest code in that window.
// Centre dot/line only = perfectly quiet; wide bar = noisy. The same window
// also feeds auto range (its mean) and, with ADC_DISPLAY_AVERAGED, the readout.
// Sample rate as seen in the heartbeat log is ~32/s, so 10 samples is about
// 0.3 s - roughly one ADC-page redraw interval, so a redraw sees about one
// redraw's worth of samples. A much shorter window can miss noise between
// redraws; a much longer one reacts slowly.
#define NOISE_WINDOW_SAMPLES        10
// Deviation from the mean, in raw ADC counts, that fills one HALF of the
// bar. When either side reaches it the bar turns red (= "off the scale").
// Tune it by watching the "[ADC] noise ..." serial line with a typical
// signal connected.
#define NOISE_BAR_FULLSCALE_COUNTS  1000
// How long, in milliseconds, to ignore samples after a channel / range /
// attenuator change, so the jump to the new signal level and the settling
// that follows isn't shown as signal or noise. During the hold the noise
// window stays empty, the readout shows "---", and auto range does not
// decide anything. A TIME rather than a number of samples because samples
// reach the consumer unevenly (bursts 8 ms apart, then ~115 ms holes), and
// the thing being waited for - the signal path settling after a gain change
// - takes a fixed amount of time. A -50 dBm signal was still above its
// final level 382 ms after a range change, hence 500 as the starting value;
// the settle trace below shows whether it needs to be longer or shorter.
#define SETTLE_HOLD_MS              500
// 1 = the big Vac/dBm readout on the ADC page is computed from the MEAN raw
// code of the noise window instead of the latest single sample, which calms
// the digits when the signal is weak and noisy (random noise shrinks by
// about the square root of NOISE_WINDOW_SAMPLES; slow drift or hum is not
// removed). 0 = latest sample, as before. With 1, the readout shows "---"
// for SETTLE_HOLD_MS after every channel / range / attenuator change (the
// window is empty while the ADC settles), and the window length above now also
// sets how much the readout is averaged: longer = calmer but slower to
// follow a change. The "raw 0x..." line under it always shows the latest
// sample, so the unaveraged jitter stays visible next to the calm value.
#define ADC_DISPLAY_AVERAGED        1

// ── ADC settle-time trace (serial diagnostic) ─────────────────────────────────
// After every channel / range / attenuator change, record the first
// SETTLE_TRACE_SAMPLES samples and print them as one table: sample number,
// time since the first sample, raw24 code, change from the previous code and
// the status word. Use it to see how long the ADC really takes to settle,
// then set SETTLE_HOLD_MS (above) from what it shows. Rows marked * are the
// ones inside that hold. Nothing is printed while the samples are being
// collected - printing at 115200 baud would block the sample consumer and
// distort the very timing being measured.
// Set SETTLE_TRACE to 0 to remove it (e.g. once an A/B sequencer switches
// channels continuously, where it would print on every switch).
#define SETTLE_TRACE                1
// 32 samples cover roughly a second at the sample rate seen so far, which is
// longer than SETTLE_HOLD_MS, so the trace shows what happens AFTER the hold
// too. The printed t_ms column gives the real time span.
#define SETTLE_TRACE_SAMPLES        32

// ── Battery indicator (ADC page, under the noise bar) ─────────────────────────
// Set to 0 to remove the icon AND its measuring task entirely (e.g. on a
// board with no battery divider wired to BATTERY_ADC_PIN).
#define BATTERY_INDICATOR            1
// GPIO that sees the battery through a resistor divider. GPIO27 is what the
// earlier project used and nothing else here uses it, but check it is wired
// on THIS board. It is an ADC2 pin: ADC2 stops working if WiFi/Bluetooth is
// ever enabled (ADC1 pins, GPIO32-39, don't have that limit).
#define BATTERY_ADC_PIN              27
// Battery volts = voltage at the pin x this. 2.0 = two equal resistors.
// Calibrate it with a multimeter: ratio = real battery volts / pin volts.
// The "[BATT]" serial line prints both the pin and battery millivolts.
#define BATTERY_DIVIDER_RATIO        2.9f
// Milliseconds between readings. Each reading is the mean of 16 ADC samples
// (the TFT/SPI traffic makes single reads noisy). A battery changes slowly,
// so there is no reason to read it often.
#define BATTERY_SAMPLE_PERIOD_MS     5000
// Each new reading moves the displayed value 1/N of the way towards it, so
// the percentage doesn't flicker. 1 = no smoothing.
#define BATTERY_SMOOTHING            4
// Below this the pin is assumed to have no battery on it (unconnected /
// USB only): the icon shows "--" in a grey outline instead of a misleading 0 %.
#define BATTERY_PRESENT_MIN_MV       2500
// At or below EMPTY_MV the charge reads 0 %, at or above FULL_MV 100 %.
// In between it follows the cubic from the earlier project.
#define BATTERY_EMPTY_MV             3400
#define BATTERY_FULL_MV              4200
// Colour steps (percent): green at/above YELLOW_PCT, then yellow, orange, red.
#define BATTERY_YELLOW_PCT           70
#define BATTERY_ORANGE_PCT           50
#define BATTERY_RED_PCT              30

// ── UI pages ──────────────────────────────────────────────────────────────────
typedef enum {
PAGE_ADC_GAIN = 0,
PAGE_INFO,
PAGE_BARGRAPH,
PAGE_SETTINGS,
PAGE_COUNT
} Page;

// ── Shared state (guarded by g_state_mutex) ───────────────────────────────────
typedef struct {
int32_t counter;
Page    page;
uint8_t brightness;
uint8_t gain_rev;   // bumped whenever ADC gain changes, just to force a UI redraw
uint8_t channel;
uint8_t range;      // 0..2 = Rng 1..3 (single source of truth for the range)
uint8_t auto_range; // 1 = auto range on (Button #5)
} AppState;

// ── FreeRTOS handles (defined in main.cpp) ────────────────────────────────────
extern SemaphoreHandle_t g_state_mutex;
extern AppState          g_state;

// ── Task priorities ───────────────────────────────────────────────────────────
#define PRIO_ENCODER    6
#define PRIO_UI         4
#define PRIO_HEARTBEAT  1
#define PRIO_TOUCH      3

//#define NVS_FULL_ERASE 1
//#define SERIAL2_UART 1
#include "adc_dbm.h"
#include "calib_json.h"
#include "board_corrections.h"
#include "config.h" // ADC_APPLY_CALIBRATION
#include <math.h>

// Shared core: evaluates the calibration polynomial. Both adc_to_vac()
// and adc_to_dbm() call this - a single place doing the actual math means
// they can never numerically disagree with each other for identical
// inputs. Returns false (leaving *out_vac untouched) on the same failure
// conditions the public functions document (bad channel, no calibration).
static bool adc_polynomial_vac(double adc_raw, int channel, int range,
                                double *out_vac)
{
    if (channel < 0 || channel > 2) {
        return false; // bad channel
    }
    if (range < 0 || range > 2) {
        return false; // bad range (valid: 0..2 = range 1..3)
    }

#if ADC_APPLY_CALIBRATION
    CalibTable calib;
    if (!calib_json_get(calib)) {
        return false; // no calibration received/persisted yet
    }

    // Measurement floor (JSON's Z_A/Z_B/Z_C, see calib_json.h): the raw code
    // this channel/range reads with the input terminated. Subtracted from the
    // raw code BEFORE the polynomial, because the floor adds to a reading
    // rather than scaling it - near the bottom of a range it inflated the
    // result (a -50 dBm signal read about 1.6 dB high). 0 (the default, and
    // what a table without floors reads as) changes nothing.
    // A code at or below its floor leaves no signal to report, so the result
    // is NaN - callers must treat a non-finite value as "no reading"
    // (draw_page_adc_gain() shows "---"). This is deliberately not the -1.0
    // the failure paths use: -1.0 is a plausible-looking number, NaN is not.
    const double net_raw = adc_raw - (double)calib.z_floor[channel][range];
    if (!(net_raw > 0.0)) {   // also catches a NaN input
        *out_vac = NAN;
        return true;
    }
#else
    const double net_raw = adc_raw; // RAW mode is uncorrected by definition: no floor either
#endif

    // Same half-wave rectifier correction raw_to_volts() applies to
    // sample.volts (see board_corrections.h) - applied here to the
    // polynomial's input rather than to sample.raw24 itself, so the raw
    // sample stays a true, diagnostic-usable ADC code. Currently 1.0
    // (neutral). Applied in BOTH modes below - it's a fixed, simple
    // correction unrelated to the per-channel fitted polynomial that
    // ADC_APPLY_CALIBRATION (config.h) controls.
    double x = log10(net_raw * (double)AC_HALFWAVE_CORRECTION);

#if ADC_APPLY_CALIBRATION

    // The JSON's per-channel _1/_2/_3 entries are stored as coeffs[0..2],
    // so the range index selects the set directly. How a range relates to
    // the PGA gain is NOT decided here - that mapping lives in main.cpp
    // (kRangeGainStep), so it can change without touching calibration code.
    const float *a = calib.ch[channel].coeffs[range];

    // Small manual correction (JSON's M_A/M_B/M_C, see calib_json.h) -
    // an additive nudge to the constant/log-space term, for touching up
    // a polynomial slightly without re-deriving the whole thing. Defaults
    // to 0.0 (no-op) until a correction is explicitly sent.
    const float m_correction = calib.m_correction[channel][range];

    // Base quadratic (first 3 coefficients always used), extended to
    // cubic/quartic only if the source JSON provided a non-zero value
    // there - identical "optional higher-order term" behavior to the
    // original *(a+3)/*(a+4) checks.
    double log_vac = (double)a[0] + (double)m_correction + (double)a[1] * x + (double)a[2] * x * x;
    if (a[3] != 0.0f) {
        log_vac += (double)a[3] * x * x * x;
    }
    if (a[4] != 0.0f) {
        log_vac += (double)a[4] * x * x * x * x;
    }
#else
    // ADC_APPLY_CALIBRATION == 0: calib_json_get() and the fitted
    // polynomial are deliberately skipped - anything already in NVS is
    // left completely alone. Without any scaling, log_vac would just be
    // x (~log10 of the raw code itself, a number in the millions) - never
    // small enough to trigger the existing auto Volt/mV formatting in
    // draw_page_adc_gain(), so it wouldn't read as a voltage at all.
    //
    // Scaled here against the chip's NOMINAL full-scale transfer
    // function for the mode it's actually configured in - unipolar
    // 24-bit, 3.0V reference, matching the exact arguments passed to
    // max11270_init() in main.cpp's setup() (not a value invented for
    // this file). This is the textbook ideal response, NOT derived from
    // any per-channel trim or fitted calibration data, so it will not be
    // precisely accurate - only good enough to land in a sensible,
    // readable range for relative trend-watching while sweeping a
    // reference signal, which is this mode's actual purpose. Still
    // labeled "RAW" on screen rather than "Volt"/"mV", since it is not a
    // calibrated reading regardless of what range it displays in.
    const double kNominalFullScaleCode = 16777215.0; // 2^24 - 1, unipolar 24-bit
    //const double kNominalVrefVolts     = 3.0;        // matches max11270_init()'s reference arg
    double log_vac = x + log10(REFERENCE_VOLTS / kNominalFullScaleCode);
#endif

    *out_vac = pow(10.0, log_vac);
    return true;
}

double adc_to_vac(double adc_raw, int channel, int range)
{
    double vac;
    if (!adc_polynomial_vac(adc_raw, channel, range, &vac)) {
        return -1.0;
    }
    return vac;
}

double adc_to_dbm(double adc_raw, int channel, int range, double load_ohms)
{
    double vac;
    if (!adc_polynomial_vac(adc_raw, channel, range, &vac)) {
        return -1.0;
    }
    return 10.0 * log10((vac * vac) / (load_ohms * 0.001));
}
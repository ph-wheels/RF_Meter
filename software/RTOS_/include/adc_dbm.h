#pragma once
#include <stdint.h>

// Converts a raw MAX11270 ADC code to Vac or dBm, using a per-channel,
// per-range calibration polynomial sourced from the NVS-backed
// CalibTable (see calib_json.h) - replaces the old polyBase.a_r1-style
// direct struct-pointer access with a live lookup into whatever
// calibration was last received/persisted.
//
// Polynomial form (base quadratic, extended to cubic/quartic only if the
// source JSON supplied a non-zero coefficient there - same "optional
// higher-order term" behavior as the original):
//   log10(Vac) = c0 + c1*x + c2*x^2 [+ c3*x^3] [+ c4*x^4],  x = log10(adc_raw)
//   Vac = 10 ^ log10(Vac)
//
// IMPORTANT - same-instant consistency: both functions below are PURE
// (same adc_raw/channel/range in -> same output, every time, no
// internal "go fetch the latest live sample" step). If you need both Vac
// AND dBm describing the same measurement, capture ONE sample (e.g. one
// sample.raw24 from the ADC queue / g_latest_sample) and pass that SAME
// value into both calls. Don't call one, then separately fetch a fresh
// live sample and call the other - the ADC may have advanced to a new
// conversion in between, and the two results would then describe two
// different instants. adc_to_dbm() internally calls adc_to_vac() with
// your same adc_raw, so the two can never numerically disagree with each
// other for identical inputs - only your choice of WHEN to sample can
// introduce a mismatch.
//
// Common parameters for both functions:
// @param adc_raw    Raw 24-bit ADC code - e.g. sample.raw24 from the
//                    MAX11270 driver, cast to double, UNMODIFIED (both
//                    functions apply the board's half-wave rectifier
//                    correction internally - see board_corrections.h -
//                    same as raw_to_volts() does for sample.volts. Do NOT
//                    pre-correct adc_raw yourself before calling this, or
//                    the correction will be applied twice).
// @param channel    0=A, 1=B, 2=C - which physical channel's calibration
//                    to use (matches the JSON's A_x/B_x/C_x keys).
// @param range      0..2 = range 1..3: which of that channel's three
//                    calibration polynomials to use (the JSON's A_1/A_2/
//                    A_3, B_1/..., C_1/... entries). This module does NOT
//                    know how a range relates to the PGA gain - that
//                    mapping is owned by the caller (main.cpp's
//                    kRangeGainStep), so it can change without touching
//                    calibration code. (This parameter used to be
//                    `gain_step`, mapped to a range internally; any other
//                    caller still passing a gain index will now silently
//                    get the wrong polynomial, or -1.0 for indices > 2.)

// NOTE: if config.h's ADC_APPLY_CALIBRATION is 0, both functions skip the
// fitted polynomial entirely (NVS contents untouched, just unused) and
// return an uncorrected, monotonic value instead - NOT a real voltage.
// See that macro's comment in config.h for why/when to use this.

// NaN RESULT: when the calibration has a measurement floor for this
// channel/range (Z_A/Z_B/Z_C, see calib_json.h) and `adc_raw` is at or below
// it, there is no signal to report and both functions return NaN (not -1.0).
// Callers that print a value must check std::isfinite() first - the ADC page
// does and shows "---". Never happens in ADC_APPLY_CALIBRATION==0 (RAW) mode,
// which is uncorrected by definition, or while all floors are 0 (the default)
// and the code is positive.

// Returns the calibrated Vac reading, or -1.0 if no calibration is
// available yet (nothing received this session and nothing in NVS), or
// `channel` / `range` is out of range. (With ADC_APPLY_CALIBRATION==0,
// -1.0 is only returned for a bad channel/range - see above.)
double adc_to_vac(double adc_raw, int channel, int range);

// Returns the calibrated dBm reading (derived from adc_to_vac()'s output -
// see the consistency note above), or -1.0 on the same failure conditions.
// @param load_ohms  Load impedance for the dBm calculation (was the
//                    implicit global `setTerm` in the old code - passed
//                    explicitly here instead; use 50.0 for the usual RF
//                    50-ohm assumption).
double adc_to_dbm(double adc_raw, int channel, int range,
                   double load_ohms = 50.0);
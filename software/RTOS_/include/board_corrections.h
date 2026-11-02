#pragma once

/* This board feeds every channel through a half-wave rectifier ahead of
 * the ADC, so the raw code / DC level the ADC actually sees runs ~2x the
 * signal's true value, on every channel.
 *
 * This lives in its own tiny shared header because TWO different places
 * need to apply it consistently:
 *   - max11270.c's raw_to_volts(): the direct linear V = code/2^24 * VREF
 *     / gain calculation, corrected at the end.
 *   - adc_dbm.cpp's adc_to_dbm(): the polynomial-based dBm/Vac conversion,
 *     corrected on its raw24 input before taking log10().
 * A single #define here means those two can't silently drift out of sync
 * with each other if this factor is ever revisited.
 *
 * sample.raw24 itself is intentionally left as the TRUE, unmodified ADC
 * code (useful for diagnostics/debugging against the datasheet's own
 * formulas, and for CTRL2/readback-style sanity checks) - this correction
 * is applied at the point each consumer turns that raw code into a
 * real-world reading, never baked into the raw code stored in the sample
 * itself.
 */
#define AC_HALFWAVE_CORRECTION 1.0f

#define REFERENCE_VOLTS 3.3f

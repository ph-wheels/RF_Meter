#pragma once
#include <stdint.h>

// Touch calibration is now a RUNTIME struct rather than compile-time
// #defines (TOUCH_X_MIN etc in config.h), so the interactive calibration
// routine in main.cpp can update it and persist the result. The config.h
// #defines still exist and are used as the INITIAL/FALLBACK defaults
// (the "current found optimum" values from manual tuning) - see
// settings_load()'s defaults parameter.
struct TouchCalib {
    int16_t x_min, x_max, y_min, y_max;
    bool    swap_xy, invert_x, invert_y;
};

extern TouchCalib g_touch_calib;

// Call once at boot, before touch_task starts (read_touch() uses
// g_touch_calib immediately). Loads touch calibration + brightness from
// NVS if present; anything not yet saved falls back to `defaults` /
// `default_brightness`. `*out_brightness` receives the value to apply
// (either the NVS one or the fallback default).
void settings_load(const TouchCalib &defaults, uint8_t default_brightness,
                    uint8_t *out_brightness);

// Persist the current g_touch_calib and the given brightness to NVS.
// Cheap to call often (e.g. every heartbeat tick) - internally skips the
// actual flash write if nothing has changed since the last save, so
// frequent brightness dragging or repeated calibration attempts don't
// wear the flash.
void settings_save(uint8_t brightness);

// Wipes all persisted settings (touch calibration + brightness). Next
// boot's settings_load() will fall back to the `defaults` you pass it -
// use this when a config.h default (e.g. TOUCH_SWAP_XY) needs to take
// effect again after a bad value was already saved to NVS, since a saved
// record otherwise overrides config.h defaults entirely.
void settings_erase();
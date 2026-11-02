#include "app_settings.h"
#include <Arduino.h>
#include <Preferences.h>
#include <string.h>

TouchCalib g_touch_calib;

static const char *kNvsNamespace   = "appset";
static const char *kNvsKeyTouchCal = "touchcal";
static const char *kNvsKeyBright   = "bright";

// Last-saved snapshots, used purely to detect "did anything actually
// change" before touching flash - same dedup pattern used for the
// calibration-JSON NVS save earlier in this project.
static TouchCalib s_last_saved_calib;
static uint8_t    s_last_saved_brightness = 0xFFu; // sentinel: force first save

void settings_load(const TouchCalib &defaults, uint8_t default_brightness,
                    uint8_t *out_brightness)
{
    g_touch_calib   = defaults;
    *out_brightness = default_brightness;

    Preferences prefs;
    if (!prefs.begin(kNvsNamespace, /*readOnly=*/true)) {
        // Normal on first-ever boot - namespace doesn't exist until the
        // first successful save creates it.
        Serial.println("[SETTINGS] no NVS namespace yet, using defaults");
        return;
    }

    size_t sz = prefs.getBytesLength(kNvsKeyTouchCal);
    if (sz == sizeof(TouchCalib)) {
        TouchCalib loaded;
        prefs.getBytes(kNvsKeyTouchCal, &loaded, sizeof(loaded));
        g_touch_calib = loaded;
        Serial.printf("[SETTINGS] touch calibration loaded from NVS: "
                      "x[%d,%d] y[%d,%d] swap=%d invx=%d invy=%d\n",
                      g_touch_calib.x_min, g_touch_calib.x_max,
                      g_touch_calib.y_min, g_touch_calib.y_max,
                      (int)g_touch_calib.swap_xy, (int)g_touch_calib.invert_x,
                      (int)g_touch_calib.invert_y);
    } else {
        Serial.println("[SETTINGS] no saved touch calibration yet, using config.h defaults");
    }

    if (prefs.isKey(kNvsKeyBright)) {
        *out_brightness = prefs.getUChar(kNvsKeyBright, default_brightness);
        Serial.printf("[SETTINGS] brightness loaded from NVS: %u%%\n", *out_brightness);
    } else {
        Serial.println("[SETTINGS] no saved brightness yet, using default");
    }

    prefs.end();

    s_last_saved_calib      = g_touch_calib;
    s_last_saved_brightness = *out_brightness;
}

void settings_save(uint8_t brightness)
{
    bool calib_changed  = memcmp(&g_touch_calib, &s_last_saved_calib, sizeof(TouchCalib)) != 0;
    bool bright_changed = (brightness != s_last_saved_brightness);
    if (!calib_changed && !bright_changed) {
        return; // nothing to do - avoid pointless flash wear
    }

    Preferences prefs;
    if (!prefs.begin(kNvsNamespace, /*readOnly=*/false)) {
        Serial.println("[SETTINGS] NVS open (write) failed");
        return;
    }
    if (calib_changed) {
        prefs.putBytes(kNvsKeyTouchCal, &g_touch_calib, sizeof(g_touch_calib));
    }
    if (bright_changed) {
        prefs.putUChar(kNvsKeyBright, brightness);
    }
    prefs.end();

    s_last_saved_calib      = g_touch_calib;
    s_last_saved_brightness = brightness;
    Serial.println("[SETTINGS] saved to NVS");
}

void settings_erase()
{
    Preferences prefs;
    if (prefs.begin(kNvsNamespace, /*readOnly=*/false)) {
        prefs.clear();
        prefs.end();
        Serial.println("[SETTINGS] all persisted settings erased");
    } else {
        Serial.println("[SETTINGS] NVS open (erase) failed");
    }
}
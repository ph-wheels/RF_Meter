# FreeRTOS Rotary Encoder + ILI9341 240×320 SPI LCD — ESP32 / PlatformIO

## Wiring

```
ESP32                  Rotary Encoder KY-040
─────                  ──────────────────────
GPIO 22  ──────────►   CLK  (A)
GPIO 21  ──────────►   DT   (B)
GPIO  5  ──────────►   SW   (push button)
3.3 V    ──────────►   +
GND      ──────────►   GND

ESP32                  ILI9341 SPI LCD module
─────                  ─────────────────────────
GPIO 23  ──────────►   SDI / MOSI / DIN
GPIO 18  ──────────►   SCK / CLK
GPIO 15  ──────────►   CS
GPIO  4  ──────────►   RESET
GPIO  2  ──────────►   DC / RS
GPIO 19  ──────────►   SDO / MISO  (optional)
3.3 V    ──────────►   VCC  (some modules accept 5 V on VIN)
GND      ──────────►   GND
3.3 V    ──────────►   LED / BL   (or PWM for dimming)
```

## Project layout

```
rotary_lcd/
├── platformio.ini       ← build config + TFT_eSPI pin defines
├── include/
│   └── config.h         ← pin map, AppState, FreeRTOS handles
└── src/
    └── main.cpp         ← tasks, ISR, UI rendering
```

## FreeRTOS architecture

```
  GPIO ISR  (CLK / DT edges  →  CHANGE interrupt)
  GPIO ISR  (SW  / button    →  FALLING interrupt)
       │
       │  xQueueSendFromISR(g_enc_queue, EncEvent)
       ▼
 ┌──────────────────┐   xSemaphoreTake(g_state_mutex)
 │  encoder_task    │──────────────────────────────► g_state { counter, page, brightness }
 │  Core 1 │ P = 6  │   updates based on page context
 └──────────────────┘
                               g_state (copy under mutex)
 ┌──────────────────┐◄──────────────────────────────
 │    ui_task       │   sprite.fillSprite()
 │  Core 0 │ P = 4  │   draw_page_*()               ──► ILI9341 SPI DMA
 └──────────────────┘   sprite.pushSprite()          (flicker-free blitting)

 ┌──────────────────┐
 │ heartbeat_task   │   blinks LED, prints heap/uptime every 5 s
 │  Core 0 │ P = 1  │
 └──────────────────┘
```

## Key FreeRTOS concepts demonstrated

| Concept | Where used |
|---|---|
| `xQueueCreate` / `xQueueSendFromISR` | ISR → encoder_task event handoff |
| `xSemaphoreCreateMutex` | Protect `g_state` between encoder & UI tasks |
| `xTaskCreatePinnedToCore` | Encoder on Core 1, UI + heartbeat on Core 0 |
| Task priorities | Encoder (6) > UI (4) > Heartbeat (1) |
| `portYIELD_FROM_ISR` | Yield to woken task immediately after ISR send |
| `vTaskDelay(pdMS_TO_TICKS(33))` | Non-blocking 30 FPS cap in UI task |
| State snapshot pattern | UI copies g_state under mutex, draws without holding it |

## UI pages (press encoder button to cycle)

| Page | Encoder action | What displays |
|---|---|---|
| **COUNTER** | +1 / -1 | Large signed number, range −9999–9999 |
| **BARGRAPH** | +5% / -5% | Horizontal bar 0–100 % with tick marks |
| **SETTINGS** | +5% / -5% | Brightness bar + free heap / RTOS info |

## Changing the LCD driver

TFT_eSPI supports ST7789, ST7735, ILI9488, and more.  
Edit `platformio.ini` build_flags:

```ini
; Replace ILI9341_DRIVER with your driver, e.g.:
-DST7789_DRIVER=1
-DTFT_WIDTH=240
-DTFT_HEIGHT=240    ; for square ST7789 modules
```

## Sprite memory note

A 240×320×16-bit sprite uses ~150 KB. The ESP32 has ~320 KB DRAM.  
If you hit allocation failures, reduce to a partial sprite and call  
`sprite.pushSprite(0, y_offset)` in sections, or enable PSRAM.

## Adding hardware PWM backlight control

```cpp
// In setup(), after tft.init():
ledcSetup(0, 5000, 8);          // channel 0, 5 kHz, 8-bit
ledcAttachPin(YOUR_BL_PIN, 0);

// In ui_task, after copying g_state:
ledcWrite(0, (local.brightness * 255) / 100);
```

// place holder for correction formula
// correction = log10(707 / 724) ≈ -0.010319 where 707 = should be / 724 = actual

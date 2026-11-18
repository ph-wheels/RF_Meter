# Dual channel RF meter

A battery powered, two-channel RF millivolt / power meter built around an ESP32 and a 24-bit MAX11270 ADC. Measures from below −55 dBm up to +23 dBm (50 Ω), from below 10 MHz to beyond 1 GHz, with auto range, an A-B (difference) mode and correction tables kept in non-volatile memory.

How to use the display: [DISPLAY_HELP.md](DISPLAY_HELP.md).

## History

This project started, quite a few months ago, with a question about a replacement or source for suitable detector diodes for the Boonton RF millivolt meter. From that the idea was born to build a millivolt and/or power meter with one of the modern ADC chips available today. Since then a few test drawings and PCBs were made, up to the current V5 of the ADC board (now a 4-layer board).

The project is a combined effort with Jacques (VE2AZX, http://www.ve2azx.net), who had already developed a replacement board for the Boonton millivolt / power meter series that fixes the problem with the mechanical chopper. Without his valued contribution, experience, feedback and high-precision RF measurements this project would not exist.

## Hardware

The design is based on two main PCBs and a battery board, which also shields the ADC board when mounted on top of it.

**Control board.** Connection to the battery board, a flat cable to the ADC board and a TTL-level UART to an external USB serial interface, which is also used to flash the ESP32. The ESP32 drives the 3.5" 480×320 touch display, reads the rotary encoder, the touch screen and the on-board push buttons, and controls the ADC board. The meter is battery powered and should run for several hours from 2× 2000 mAh or larger cells. There is optional board space for a BMS unit. Charging is with a 2S 1A charger module or through a barrel jack, and an on-board regulator (3V3) supplies the MCU and display.

**ADC board.** Two SMA inputs and the flat cable to the control board; optionally a 2-pin Amphenol connector, like the Boonton instruments. It has three areas: the three input circuits, the multiplexer with the ADC chip, and the voltage and reference sources with control for the attenuator and optional panel LEDs.
- Channels A and B: 50 Ω termination, detector circuit and attenuator (this gives the +23 dBm range), into a differential low-noise ×1 amplifier.
- Channel C (components populated, but not used in the current firmware): only the differential 5M6 resistors, the attenuator and the differential amplifier, so it is not a 50 Ω input.

| Part | Notes |
|---|---|
| ESP32 | Arduino-ESP32, PlatformIO, FreeRTOS |
| ILI9488 480×320 SPI display (landscape) | via TFT_eSPI, 18-bit colour |
| XPT2046 touch | shares the SPI bus, CS and IRQ pins in `config.h` |
| MAX11270 24-bit ADC | shares the SPI bus (4 MHz, mode 0), RDYB on an interrupt pin, 3.3 V reference |
| Rotary encoder with push button | pins in `config.h` |
| ADC board | 4-layer (signal, ground, power, signal); gain and attenuator switched through the ADC's GPIO pins |

Pin assignments are listed at the top of `main.cpp` and defined in `config.h`; the TFT pins are in your TFT_eSPI `User_Setup.h`.

| Signal | GPIO |
|---|---|
| SPI bus (shared by TFT, touch and ADC) | SCK 18, MISO 19, MOSI 23 |
| Touch CS / IRQ | 16 / 32 |
| ADC CSB / RDYB | 5 / 4 |
| Encoder CLK / DT / SW | 34 / 33 / 35 (external pull-ups) |
| Battery voltage | 27 (through a divider) |
| Optional second UART | TX 22, RX 21 |

## Project status

The main development goals have been reached:

- a battery powered instrument with modern chips and a display large enough to be usable
- an input range from below −55 dBm up to +23 dBm
- a frequency range from below 10 MHz to beyond 1 GHz (flat within about ±0.13 dB from 10 to 100 MHz, corrected above)
- auto range over the entire input range
- correction tables loaded and kept in non-volatile memory

The **A-B mode** (difference between the channels) now works over all ranges: the meter switches between A and B by itself, auto ranges each channel separately and shows A, B and the difference in dB. The price is the update rate: every channel switch needs about 0.5 s to settle, so a full A/B update takes about 1.2 s. In a test with a splitter at 400 MHz the channels agreed within ±0.2 dB, and a 10 dB attenuator in one lead gave a 10 dB difference in both directions.

Future plans: none at the moment, other than an updated schematic based on a dual ADC chip, which would make the A-B mode 2× to 3× faster. That costs more to build because of the extra ADC and the SSR / mux chip.

Build instructions (how to build the ADC and control boards, and how to test and commission each board) will follow in the folder `Build`.

Paul (PE1FCB (ex))

## Features

- **Two channels (A, B)** with a measured spread of about 0.1 dB at 50 MHz. Channel C is in the software as a placeholder (its calibration is a copy of A); it is not a 50 Ω input.
- **Three ranges per channel** (gain ×1 with attenuator, ×4, ×16), manual or **auto range** with hysteresis.
- **Bipolar ADC mode**, so the offset of the front end can be negative and is not clipped. 125 samples per second.
- **Per-channel, per-range calibration** as a polynomial in log space, loaded as JSON over USB serial and kept in NVS.
- **Zero (floor) correction** per channel and range, set from the display or over serial.
- **A-B page:** automatically alternates between A and B, autoranges each separately and shows A, B and the difference in dB.
- **Frequency correction:** one dB table for 200 to 1200 MHz, selectable on the display.
- Battery indicator, noise bar, touch calibration, brightness control.

## Software layout

| File | Content |
|---|---|
| `main.cpp` | Tasks, UI pages, touch handling, ADC consumer, auto range, A-B scheduler, Zero |
| `config.h` | All settings: ADC mode, range mapping, auto-range thresholds, timing, pages, pins |
| `max11270.c/.h` | ADC driver (ISR, reader task, bipolar format, gain/attenuator/channel control) |
| `adc_dbm.cpp/.h` | Raw code → Vac and dBm, floor subtraction |
| `calib_json.cpp/.h` | JSON calibration over serial, NVS storage |
| `app_settings.cpp/.h` | Touch calibration storage |
| `board_corrections.h` | Reference voltage and detector correction factor |

### Tasks

| Task | Core / priority | Job |
|---|---|---|
| encoder | 1 / 6 | knob and push button |
| touch | 0 / 3 | touch buttons |
| ui | 0 / 4 | renders the page when the state changes (about 3 Hz on live pages) |
| adc consumer | 1 / 2 | settle hold, noise window, auto range, A-B, Zero data |
| MAX11270 reader | – / 3 | reads the ADC when RDYB falls |
| heartbeat, battery | 0 / 1 | LED and battery voltage |

### How a reading is made

1. The ADC converts at 125 SPS. The RDYB interrupt wakes the reader task, which reads the sample and queues it.
2. After any channel, range or attenuator change, samples are ignored for `SETTLE_HOLD_MS` (500 ms).
3. The mean of the last 10 settled samples is the reading; it also feeds auto range.
4. Net code = raw − Z (floor). `log10(Vac) = a0 + M + a1·x + a2·x² + a3·x³`, with `x = log10(net)`. Then `dBm = 10·log10(Vac² / (50 Ω · 1 mW))`. A code at or below the floor gives no reading (`---`).
5. The selected frequency adds its dB correction.

### Display and ADC share one SPI bus

A full screen push used to hold the bus about 110 ms and cost most of the ADC samples. The display is therefore sent in thin slices (`UI_PUSH_SLICE_ROWS`, `UI_PUSH_GAP_US`) and the driver skips stale ready tokens. Result: the full 125 samples per second arrive. With `ADC_RATE_DIAG 1` a `[RATE]` line on serial shows this every 2 s.

## Build

PlatformIO, Arduino-ESP32. Libraries: TFT_eSPI, XPT2046_Touchscreen, ArduinoJson 7. Set your TFT_eSPI `User_Setup.h` for the ILI9488 and the display pins. Serial monitor at 115200 baud.

Main switches in `config.h`:

| Setting | Meaning |
|---|---|
| `ADC_APPLY_CALIBRATION` | 1 = calibrated readings, 0 = RAW codes for measuring a new calibration (attenuator forced off) |
| `ADC_BIPOLAR` | 1 = bipolar mode (current), 0 = unipolar |
| `RANGEn_GAIN_STEP`, `RANGEn_ATTEN_ON` | gain and attenuator of each range |
| `AUTORANGE_*` | switch points (raw counts) and sample count for auto range |
| `SETTLE_HOLD_MS`, `NOISE_WINDOW_SAMPLES` | settle hold and averaging window |
| `ZERO_*` | Zero button interlocks and NVS saving |
| `ENABLE_PAGE_BARGRAPH` | brings the bargraph page back |
| `ADC_RATE_DIAG`, `SETTLE_TRACE` | diagnostic output on serial |

Auto-range thresholds are raw counts and only hold for the current gains, attenuator states and bipolar mode. Re-measure them after changing any of these.

## Calibration

1. Build with `ADC_APPLY_CALIBRATION 0` and take raw readings at a series of known levels per channel and range (50 MHz). In range 1 the attenuator must be on, so measure it in calibrated mode.
2. Fit a cubic polynomial per channel and range (log10 of the net code against log10 of the voltage). Quartic fits diverge outside the measured range.
3. Send the JSON over USB serial (see [DISPLAY_HELP.md](DISPLAY_HELP.md#loading-calibration-data-usb-serial-115200-baud)).
4. Terminate the inputs, warm up, and zero each range from the display.
5. Optional: measure the roll-off at 200 to 1200 MHz and load it as `F_COR`.

Current calibration: 50 MHz, bipolar, cubic fits, both channels flat to about ±0.13 dB from 10 to 100 MHz.

## Known limits

- The input has parasitic capacitance, a single-pole roll-off at roughly 820 MHz, which is independent of level. `F_COR` compensates it in software; above about 1 GHz the accuracy is limited by the front end, and the noise floor goes up by the correction.
- The floors drift by a few µV over hours (range 3 of B the most). Zero again after warm-up.
- Noise is front-end dominated, so a higher gain than ×16 does not help.
- Channel C is a placeholder (calibration copied from A) and has no measured calibration.
- Redrawing the display takes about 0.5 s per frame; it is throttled to keep the ADC supplied.

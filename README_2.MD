RF power meter (ESP32 + MAX11270)

A two-channel RF level meter for about −55 dBm to +15 dBm (23 dBm not yet tested) into 50 Ω, built on an ESP32 running FreeRTOS. The RF detector output goes to a 24-bit MAX11270 delta-sigma ADC through a switchable gain and attenuator stage. A calibration polynomial per channel and range turns the ADC code into volts and dBm.

Display and controls: 480×320 ILI9488 touch display (XPT2046), rotary encoder with push button. See DISPLAY_HELP.md for how to use it.

Features
Two channels (A, B) with a measured spread of about 0.1 dB at 50 MHz. A third channel (C) is in the software, but the hardware does not exist yet.
Three ranges per channel (gain ×1 with attenuator, ×4, ×16), manual or auto range with hysteresis.
Bipolar ADC mode, so the offset of the front end can be negative and is not clipped. 125 samples per second.
Per-channel, per-range calibration as a polynomial in log space, loaded as JSON over USB serial and kept in NVS.
Zero (floor) correction per channel and range, set from the display or over serial.
A-B page: automatically alternates between A and B, autoranges each separately and shows A, B and the difference in dB.
Frequency correction: one dB table for 200 to 1200 MHz, selectable on the display.
Battery indicator, noise bar, touch calibration, brightness control.
Hardware
Part	Notes
ESP32	Arduino-ESP32, PlatformIO, FreeRTOS
ILI9488 480×320 SPI display (landscape)	via TFT_eSPI, 18-bit colour
XPT2046 touch	shares the SPI bus, CS and IRQ pins in config.h
MAX11270 24-bit ADC	shares the SPI bus (4 MHz, mode 0), RDYB on an interrupt pin, 3.3 V reference
Rotary encoder with push button	pins in config.h
Analog board	4-layer (signal, ground, power, signal); input network with bias resistors and diode detector; gain and attenuator switched through the ADC's GPIO pins

Pin assignments are in config.h and the start of main.cpp; the TFT pins are in your TFT_eSPI User_Setup.h. Check them against your board: the wiring comment at the top of main.cpp is from an earlier hardware version.

Software layout
File	Content
main.cpp	Tasks, UI pages, touch handling, ADC consumer, auto range, A-B scheduler, Zero
config.h	All settings: ADC mode, range mapping, auto-range thresholds, timing, pages, pins
max11270.c/.h	ADC driver (ISR, reader task, bipolar format, gain/attenuator/channel control)
adc_dbm.cpp/.h	Raw code → Vac and dBm, floor subtraction
calib_json.cpp/.h	JSON calibration over serial, NVS storage
app_settings.cpp/.h	Touch calibration storage
board_corrections.h	Reference voltage and detector correction factor
Tasks
Task	Core / priority	Job
encoder	1 / 6	knob and push button
touch	0 / 3	touch buttons
ui	0 / 4	renders the page when the state changes (about 3 Hz on live pages)
adc consumer	1 / 2	settle hold, noise window, auto range, A-B, Zero data
MAX11270 reader	– / 3	reads the ADC when RDYB falls
heartbeat, battery	0 / 1	LED and battery voltage
How a reading is made
The ADC converts at 125 SPS. The RDYB interrupt wakes the reader task, which reads the sample and queues it.
After any channel, range or attenuator change, samples are ignored for SETTLE_HOLD_MS (500 ms).
The mean of the last 10 settled samples is the reading; it also feeds auto range.
Net code = raw − Z (floor). log10(Vac) = a0 + M + a1·x + a2·x² + a3·x³, with x = log10(net). Then dBm = 10·log10(Vac² / (50 Ω · 1 mW)). A code at or below the floor gives no reading (---).
The selected frequency adds its dB correction.
Display and ADC share one SPI bus

A full screen push used to hold the bus about 110 ms and cost most of the ADC samples. The display is therefore sent in thin slices (UI_PUSH_SLICE_ROWS, UI_PUSH_GAP_US) and the driver skips stale ready tokens. Result: the full 125 samples per second arrive. With ADC_RATE_DIAG 1 a [RATE] line on serial shows this every 2 s.

Build

PlatformIO, Arduino-ESP32. Libraries: TFT_eSPI, XPT2046_Touchscreen, ArduinoJson 7. Set your TFT_eSPI User_Setup.h for the ILI9488 and the display pins. Serial monitor at 115200 baud.

Main switches in config.h:

Setting	Meaning
ADC_APPLY_CALIBRATION	1 = calibrated readings, 0 = RAW codes for measuring a new calibration (attenuator forced off)
ADC_BIPOLAR	1 = bipolar mode (current), 0 = unipolar
RANGEn_GAIN_STEP, RANGEn_ATTEN_ON	gain and attenuator of each range
AUTORANGE_*	switch points (raw counts) and sample count for auto range
SETTLE_HOLD_MS, NOISE_WINDOW_SAMPLES	settle hold and averaging window
ZERO_*	Zero button interlocks and NVS saving
ENABLE_PAGE_BARGRAPH	brings the bargraph page back
ADC_RATE_DIAG, SETTLE_TRACE	diagnostic output on serial

Auto-range thresholds are raw counts and only hold for the current gains, attenuator states and bipolar mode. Re-measure them after changing any of these.

Calibration
Build with ADC_APPLY_CALIBRATION 0 and take raw readings at a series of known levels per channel and range (50 MHz). In range 1 the attenuator must be on, so measure it in calibrated mode.
Fit a cubic polynomial per channel and range (log10 of the net code against log10 of the voltage). Quartic fits diverge outside the measured range.
Send the JSON over USB serial (see DISPLAY_HELP.md).
Terminate the inputs, warm up, and zero each range from the display.
Optional: measure the roll-off at 200 to 1200 MHz and load it as F_COR.

Current calibration: 50 MHz, bipolar, cubic fits, both channels flat to about ±0.13 dB from 10 to 100 MHz.

Known limits
The input has parasitic capacitance, a single-pole roll-off at roughly 820 MHz, which is independent of level. F_COR compensates it in software; above about 1 GHz the accuracy is limited by the front end, and the noise floor goes up by the correction.
The floors drift by a few µV over hours (range 3 of B the most). Zero again after warm-up.
Noise is front-end dominated, so a higher gain than ×16 does not help.
Channel C is a placeholder (copy of A).
Redrawing the display takes about 0.5 s per frame; it is throttled to keep the ADC supplied.

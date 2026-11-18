DISPLAY HELP · MD
Display help

The instrument has a 480×320 touch display and one rotary knob with a push button.

Controls
Control	Action
Knob push	Next page: Measure → A-B → Info → Settings → Measure
Knob turn (Measure page)	Range down / up (turns auto range off)
Touch	Buttons on the page (see below)

The knob push also cancels the touch-calibration screen if it is open.

Measure page

Reading one channel, one range at a time.

┌──────────────────────────────────────────────┐
│        0.1234  -7.42            ← Vac   dBm  │
│        mV        dBm                          │
│        AOR:0  DOR:0                           │
│        ▐████░░░░░▌   noise bar                │
│        raw 0x00A1B2 (41394)           [batt]  │
│ [Zero]                               [Freq]  │
│ [CH. A][Rng 1][dBm][Att Off][Auto Off]       │
└──────────────────────────────────────────────┘

Readout. Voltage on the left (mV below 1 V, otherwise Volt) and power on the right (dBm or mW, 50 Ω). --- means the signal is at or below the floor of that channel and range, so there is nothing to report. The number turns red when the converter reports overrange or data-out-of-range, then go to a lower range.

Noise bar. Spread of the last 10 samples around their mean. A wide bar means an unstable or noisy input.

Buttons (left to right, bottom row)

Button	Function
CH. A / B / C	Selects the input. C has no hardware yet.
Rng 1 / 2 / 3	Selects the range. Each range sets the gain and the attenuator and picks its own calibration. Rng 1 is the least sensitive (high levels), Rng 3 the most sensitive (low levels).
dBm / mW	Switches the power part of the readout between dBm and milliwatts.
Att On / Off	Manual attenuator. In normal use it follows the range (on in Rng 1 only).
Auto On / Off	Auto range. Steps one range at a time using the mean of the last samples, with hysteresis so it doesn't flip back and forth. Off by default; any manual range, channel or knob change turns it off.

Extra buttons (row above)

Button	Function
Zero (above CH.)	Stores the current reading as the floor of this channel and range (see Zero below).
Freq (above Auto)	Frequency correction: Def, 200, 400, 600, 800, 1G0, 1G2 MHz. Def is the 50 MHz calibration with no correction; the others add the dB values of the F_COR table. The button turns orange when a correction is active.
Zero

Use it to remove the small offset of the front end (it drifts by a few µV over hours).

Terminate the input, let the unit warm up a few minutes.
Pick the channel and range by hand (auto must be off).
Tap Zero. The button turns orange and reads Sure?, and the footer shows the offset in µV that would be stored.
Tap Zero again within 4 s. The footer shows Zero stored: A R2 = …. The value is also written to NVS, so it survives a reboot.

Zero is refused (footer shows why, and the button shows No) when:

auto range is on,
the channel or range changed since the average started or it is still settling (wait about 2 s after any change),
the reading is more than ±500 µV from zero at the ADC input, meaning a signal is connected.

Zero one range at a time; repeat for every channel and range you use.

A-B page

Shows both channels together and their difference.

Large number: A minus B in dB.
Below: A and B in dBm, each with its own range (Rng n). OVR in red means overrange on the least sensitive range.
The instrument alternates between A and B by itself and autoranges each channel separately, so A and B can be far apart in level. A full A/B update takes about 1.2 s (each channel switch waits 0.5 s for the input to settle).
--- appears if a channel is at or below its floor, or has not updated for 6 s.
If a Freq correction is selected, a note shows it. Both channels get the same correction, so it does not change the A-B number.
There are no touch buttons on this page.
Info page

Firmware version, CPU and the free heap.

Settings page
Brightness: drag on the bar, or tap above or below it for ±5 %.
Touch Calibrate: starts the touch calibration (tap the targets as shown). The knob push cancels it.
Not shown

The Bargraph page is switched off (ENABLE_PAGE_BARGRAPH 0 in config.h).

Loading calibration data (USB serial, 115200 baud)

Send one JSON object. Everything is stored in NVS.

Key	Content
A_1…C_3	{"value":[5 floats]} polynomial per channel and range. All nine or none.
M_A, M_B, M_C	[3] small log-space correction per range.
Z_A, Z_B, Z_C	[3] floors in raw counts per range (the Zero button writes these too).
F_COR	{"value":[6 floats]} dB to add at 200, 400, 600, 800, 1000, 1200 MHz.

Keys missing from a message keep their stored value. The serial log shows [CALIB] table updated and table saved to NVS when it was accepted, or the reason when it was rejected.

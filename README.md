# RF_Meter
dual channel rf meter (work in progress)

This project started off with a question concerning replacement or source for
suitable detector diodes for the Boonton RF Millivolt meter quite a few months ago.
As a result of that, the idea was born to create a millivolt and/or power meter
using one of the modern ADC chips available today and since that time a few test
drawning and PCB where used in the process to the current V5 of the ADC board.
This project has been a combined effort with Jacques (ve2azx, http://www.ve2azx.net),
who already had developped a replacement board for the Boonton series of millivolt/
power meter as to fixed the issue with the mechanical chopper, without his valued
contribution, experiance, feedback and high precision RF measurement this project
would never exist.

The current design is based to 2 main PCB's and a battery board which also provides
some shielding to ADC board when mounted on top off it.

The control board consist of a connection to battery board, a flatcable connection
to ADC board and uart connection (ttl level) to external usb serial interface.
The board has and ESP32 MCU chip, which can be flashed via the USB serial interface,
will display info on the LCD screen (3.5" 480x240), monitors changes of the rotary
switch, touch screen, on-board push buttons and read/controls behaviour of the ADC
board. The RF Meter is battery powered and should be capable to provide adequate power
for several hours from 2x 2000 mAh or larger capacity batteries, optional board space
is provided to house a BMS unit and can be charged by the 2S 1A battery charger module
or via a barrel jack socket to deliver power via on-board regulator (3V3) to the MCU and
LCD screen.

The ADC board consist of 2 SMA and a flatcable connection to the control board,
optionally a connection to a 2 pin Amphenol connector, simular to the Boonton instruments.
This board holds 3 main area's being 3x input circuit, multiplexer with the ADC chip and the
voltages / reference sources with some control to switch attenuator and optional panel leds.
The input circuits for channels A/B are terminated with 50 Ohm followed by detector circuit
and attenuator, which is used to obtain a +23dBm range, into a differential low noise x1
amplifier, channel C (with it's components populated) only has the differential 5M6 resistors, the
attenuator and differential low noise x1 amplifier and is therefore not be a 50 Ohm input source.

Project status has been closed for now as we have finished our mean development goals being:
- a battery powered, using modern chips with large enough display making it a usable instrument
- obtained a less than -55 dBm and up to +23 dBm input range
- having a frequency range off less then 10 MHz upto in excess of 1 GHz
- having an auto range mechanism in place over entire input range
- having mechanism to load and maintain correction tables in none volatile memory

One area left for improvement is the option to obtain differential power reading between channel
B - A which kind of works (reasonably well within the lower 2 ranges) but will be slower in it's
update frequency then we expected it to be.

Future plans currently don't exist other then having an update schematic in place base on a dual
ADC chip approach which will speedup the channel B - A mode by factor 2x to 3x BUT this will yield
into a higher build cost due to extra ADC and the SSR / Mux chip.

Suggestion as how to build can be found in due time in folder 'Build' which will provide info and
steps to build the ADC and Control board and best practice to test and put each board into operation.

Paul	(PE1FCB (ex))

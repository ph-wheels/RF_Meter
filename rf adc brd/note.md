IMPORTANT NOTE: New rf_meter_v51_rf_adc has a MAX input voltage of 5Vdc @ J6 pin 14/16
any higher than that may destroy the Vref U10 !!!

The new firmware for the adjusted control board is now operational and tested to work

The new rf v1.6 board needs two trace cuts & two bodge wires as to swap:
The 3v6 signal from pin 14 to pin 9 and the vRef signal from pin 9 to pin 14, both are on
the top layer near U8 and C27 / C37 and require this mandatory change, see 

In due time a enhanced rf_brd v1.7 may become available which fixes the bodge wires and
will reduce capacity losses of input section

A few changes to the old control board are needed prior to usage with the v1.6 rf board
as the max supply voltage for analog board has been reduced to be 5Vdc or little less.

Also also don't use U4 AMS1117-3V3, to noisy, using the LT1671-3V3 instead is advised.
Board changes for the control board are: U2 wire from pin 14 to pin 1
add 5Vdc output regulator instead of L1

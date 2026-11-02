IMPORTANT NOTE: New rf_meter_v51_rf_adc has a MAX input voltage of 5Vdc @ J6 pin 14/16
any higher than that may destroy the Vref U10 !!!

A new firmware is needed for the control board, work in progress, operational but still lacks
the A - B mode
Also also don't use U4 AMS1117-3V3, to noisy, using the LT1671-3V3 instead is advised.
Board changes for the control board are: U2 wire from pin 14 to pin 1
add 5Vdc output regulator instead of L1

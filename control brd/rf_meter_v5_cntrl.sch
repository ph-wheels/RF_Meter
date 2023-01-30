EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR022
U 1 1 606DD335
P 5600 2250
F 0 "#PWR022" H 5600 2000 50  0001 C CNN
F 1 "GND" H 5605 2077 50  0000 C CNN
F 2 "" H 5600 2250 50  0001 C CNN
F 3 "" H 5600 2250 50  0001 C CNN
	1    5600 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 606CD476
P 3500 1450
F 0 "#PWR010" H 3500 1200 50  0001 C CNN
F 1 "GND" H 3505 1277 50  0000 C CNN
F 2 "" H 3500 1450 50  0001 C CNN
F 3 "" H 3500 1450 50  0001 C CNN
	1    3500 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 607A1CDB
P 10350 1350
F 0 "#PWR032" H 10350 1100 50  0001 C CNN
F 1 "GND" H 10355 1177 50  0000 C CNN
F 2 "" H 10350 1350 50  0001 C CNN
F 3 "" H 10350 1350 50  0001 C CNN
	1    10350 1350
	1    0    0    -1  
$EndComp
Text Notes 835  7610 0    100  ~ 0
Power & MCU section
$Comp
L Device:R_Small R13
U 1 1 6071FD6A
P 7750 1600
F 0 "R13" V 7795 1435 50  0000 C CNN
F 1 "33" V 7750 1600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7750 1600 50  0001 C CNN
F 3 "~" H 7750 1600 50  0001 C CNN
	1    7750 1600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R14
U 1 1 60759A2C
P 7750 1700
F 0 "R14" V 7800 1530 50  0000 C CNN
F 1 "33" V 7755 1695 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7750 1700 50  0001 C CNN
F 3 "~" H 7750 1700 50  0001 C CNN
	1    7750 1700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R12
U 1 1 6075B4E1
P 7750 1500
F 0 "R12" V 7795 1335 50  0000 C CNN
F 1 "33" V 7755 1495 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7750 1500 50  0001 C CNN
F 3 "~" H 7750 1500 50  0001 C CNN
	1    7750 1500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R11
U 1 1 6075C303
P 7750 1400
F 0 "R11" V 7785 1240 50  0000 C CNN
F 1 "33" V 7750 1405 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7750 1400 50  0001 C CNN
F 3 "~" H 7750 1400 50  0001 C CNN
	1    7750 1400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R10
U 1 1 607B0510
P 7750 1300
F 0 "R10" V 7785 1150 50  0000 C CNN
F 1 "33" V 7750 1300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7750 1300 50  0001 C CNN
F 3 "~" H 7750 1300 50  0001 C CNN
	1    7750 1300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R18
U 1 1 607EC455
P 9100 3100
F 0 "R18" V 9170 3095 50  0000 C CNN
F 1 "4K7" V 9100 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9100 3100 50  0001 C CNN
F 3 "~" H 9100 3100 50  0001 C CNN
	1    9100 3100
	1    0    0    -1  
$EndComp
Text Notes 7030 7000 0    197  ~ 39
RF Meter control & power
Text Notes 8510 7630 0    39   ~ 0
23-mar-2022
$Comp
L power:GND #PWR017
U 1 1 60BD347C
P 4700 1450
F 0 "#PWR017" H 4700 1200 50  0001 C CNN
F 1 "GND" H 4705 1277 50  0000 C CNN
F 2 "" H 4700 1450 50  0001 C CNN
F 3 "" H 4700 1450 50  0001 C CNN
	1    4700 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C8
U 1 1 60EDD62F
P 4700 1200
F 0 "C8" H 4705 1310 50  0000 L CNN
F 1 "47u" H 4730 1090 50  0000 L CNN
F 2 "DigiKey:1206" H 4700 1200 50  0001 C CNN
F 3 "~" H 4700 1200 50  0001 C CNN
	1    4700 1200
	1    0    0    -1  
$EndComp
$Comp
L My-Design:LT1763-S8 U5
U 1 1 60F2F8E7
P 5600 1800
F 0 "U5" H 5275 2095 50  0000 C CNN
F 1 "LT1763-3V3" H 5715 2100 50  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 5600 1000 50  0001 C CNN
F 3 "" H 6400 1950 50  0001 C CNN
	1    5600 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C16
U 1 1 61055AF8
P 7200 3100
F 0 "C16" H 7205 3210 50  0000 L CNN
F 1 "100u" H 7230 2990 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_6.3x5.7" H 7200 3100 50  0001 C CNN
F 3 "~" H 7200 3100 50  0001 C CNN
	1    7200 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C13
U 1 1 61059B99
P 6600 1855
F 0 "C13" H 6615 1965 50  0000 L CNN
F 1 "0.1" H 6630 1770 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6600 1855 50  0001 C CNN
F 3 "~" H 6600 1855 50  0001 C CNN
	1    6600 1855
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 610ED261
P 7200 3250
F 0 "#PWR028" H 7200 3000 50  0001 C CNN
F 1 "GND" H 7205 3077 50  0000 C CNN
F 2 "" H 7200 3250 50  0001 C CNN
F 3 "" H 7200 3250 50  0001 C CNN
	1    7200 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 610EE499
P 6600 2005
F 0 "#PWR025" H 6600 1755 50  0001 C CNN
F 1 "GND" H 6605 1832 50  0000 C CNN
F 2 "" H 6600 2005 50  0001 C CNN
F 3 "" H 6600 2005 50  0001 C CNN
	1    6600 2005
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C9
U 1 1 6113C68F
P 4850 1200
F 0 "C9" H 4865 1310 50  0000 L CNN
F 1 "0.1" H 4880 1115 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4850 1200 50  0001 C CNN
F 3 "~" H 4850 1200 50  0001 C CNN
	1    4850 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 6113E07D
P 4850 1450
F 0 "#PWR018" H 4850 1200 50  0001 C CNN
F 1 "GND" H 4855 1277 50  0000 C CNN
F 2 "" H 4850 1450 50  0001 C CNN
F 3 "" H 4850 1450 50  0001 C CNN
	1    4850 1450
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 613FEF0E
P 4850 905
F 0 "#FLG02" H 4850 980 50  0001 C CNN
F 1 "PWR_FLAG" H 4775 1085 50  0000 C CNN
F 2 "" H 4850 905 50  0001 C CNN
F 3 "~" H 4850 905 50  0001 C CNN
	1    4850 905 
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C11
U 1 1 609BCD14
P 6150 1850
F 0 "C11" H 6165 1960 50  0000 L CNN
F 1 "10n" H 6180 1765 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6150 1850 50  0001 C CNN
F 3 "~" H 6150 1850 50  0001 C CNN
	1    6150 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR038
U 1 1 60EECD6C
P 10750 1955
F 0 "#PWR038" H 10750 1705 50  0001 C CNN
F 1 "GND" H 10755 1782 50  0000 C CNN
F 2 "" H 10750 1955 50  0001 C CNN
F 3 "" H 10750 1955 50  0001 C CNN
	1    10750 1955
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R15
U 1 1 61012F94
P 7750 1800
F 0 "R15" V 7795 1635 50  0000 C CNN
F 1 "33" V 7750 1800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7750 1800 50  0001 C CNN
F 3 "~" H 7750 1800 50  0001 C CNN
	1    7750 1800
	0    -1   -1   0   
$EndComp
Text GLabel 8750 5100 2    39   Input ~ 0
V_MOSI
Text GLabel 7600 1300 0    39   Input ~ 0
V_MOSI
Text GLabel 7600 1400 0    39   Input ~ 0
V_MISO
Text GLabel 8750 4800 2    39   Input ~ 0
V_MISO
Text GLabel 7595 1500 0    39   Input ~ 0
V_SCK
Text GLabel 8750 4700 2    39   Input ~ 0
V_SCK
Text GLabel 7600 1600 0    39   Input ~ 0
CS_0
Text GLabel 8750 4000 2    39   Input ~ 0
CS_0
Text GLabel 7600 1700 0    39   Input ~ 0
SYNC
Text GLabel 8750 4600 2    39   Input ~ 0
SYNC
Text GLabel 8750 4400 2    39   Input ~ 0
CS_4
Text GLabel 7600 1800 0    39   Input ~ 0
~RDY
Text GLabel 8750 3900 2    39   Input ~ 0
~RDY
Text GLabel 9200 5000 2    39   Input ~ 0
SCL
Text GLabel 9200 4900 2    39   Input ~ 0
SDA
$Comp
L Device:CP_Small C14
U 1 1 6092A2F0
P 6750 1855
F 0 "C14" H 6755 1965 50  0000 L CNN
F 1 "10u" H 6780 1745 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6750 1855 50  0001 C CNN
F 3 "~" H 6750 1855 50  0001 C CNN
	1    6750 1855
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 6092B650
P 6750 2005
F 0 "#PWR026" H 6750 1755 50  0001 C CNN
F 1 "GND" H 6755 1832 50  0000 C CNN
F 2 "" H 6750 2005 50  0001 C CNN
F 3 "" H 6750 2005 50  0001 C CNN
	1    6750 2005
	1    0    0    -1  
$EndComp
$Comp
L PJ-037A:PJ-037A J1
U 1 1 60B1C2EB
P 850 3100
F 0 "J1" H 845 3440 50  0000 C CNN
F 1 "PJ-037A" H 845 3349 50  0000 C CNN
F 2 "PJ-037:CUI_PJ-037A" H 850 3100 50  0001 L BNN
F 3 "" H 850 3100 50  0001 L BNN
F 4 "CUI INC" H 850 3100 50  0001 L BNN "MANUFACTURER"
F 5 "Manufacturer recommendations" H 850 3100 50  0001 L BNN "STANDARD"
	1    850  3100
	1    0    0    -1  
$EndComp
$Comp
L Device:Polyfuse_Small F1
U 1 1 60B36531
P 1450 3000
F 0 "F1" V 1245 3000 50  0000 C CNN
F 1 "Polyfuse_.5A" V 1336 3000 50  0000 C CNN
F 2 "Fuse_Holders_and_Fuses:Fuse_SMD1206_HandSoldering" H 1500 2800 50  0001 L CNN
F 3 "~" H 1450 3000 50  0001 C CNN
	1    1450 3000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 60B47BDB
P 1050 3450
F 0 "#PWR02" H 1050 3200 50  0001 C CNN
F 1 "GND" H 1055 3277 50  0000 C CNN
F 2 "" H 1050 3450 50  0001 C CNN
F 3 "" H 1050 3450 50  0001 C CNN
	1    1050 3450
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 60B8B314
P 4350 1250
F 0 "#FLG01" H 4350 1325 50  0001 C CNN
F 1 "PWR_FLAG" H 4350 1423 50  0000 C CNN
F 2 "" H 4350 1250 50  0001 C CNN
F 3 "~" H 4350 1250 50  0001 C CNN
	1    4350 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 60B94228
P 4350 1450
F 0 "#PWR015" H 4350 1200 50  0001 C CNN
F 1 "GND" H 4355 1277 50  0000 C CNN
F 2 "" H 4350 1450 50  0001 C CNN
F 3 "" H 4350 1450 50  0001 C CNN
	1    4350 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 60BADE8D
P 3550 3500
F 0 "R2" V 3620 3495 50  0000 C CNN
F 1 "4K7" V 3550 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3550 3500 50  0001 C CNN
F 3 "~" H 3550 3500 50  0001 C CNN
	1    3550 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 60BAD99F
P 3450 3500
F 0 "R1" V 3380 3490 50  0000 C CNN
F 1 "4K7" V 3450 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3450 3500 50  0001 C CNN
F 3 "~" H 3450 3500 50  0001 C CNN
	1    3450 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 60C1784D
P 4045 4650
F 0 "#PWR013" H 4045 4400 50  0001 C CNN
F 1 "GND" H 4050 4477 50  0000 C CNN
F 2 "" H 4045 4650 50  0001 C CNN
F 3 "" H 4045 4650 50  0001 C CNN
	1    4045 4650
	1    0    0    -1  
$EndComp
Text GLabel 3350 4100 0    50   Input ~ 0
SWA
Text GLabel 3350 4300 0    50   Input ~ 0
SWB
Text GLabel 8750 5500 2    39   Input ~ 0
CS_3
Text GLabel 8750 5600 2    39   Input ~ 0
SWA
Text GLabel 8750 5800 2    39   Input ~ 0
SWC
$Comp
L Connector_Generic:Conn_01x12 J6
U 1 1 60D17F25
P 10150 950
F 0 "J6" V 10367 896 50  0000 C CNN
F 1 "RF_Brd" V 10276 896 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 10150 950 50  0001 C CNN
F 3 "~" H 10150 950 50  0001 C CNN
	1    10150 950 
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR037
U 1 1 6129C37A
P 10750 1350
F 0 "#PWR037" H 10750 1100 50  0001 C CNN
F 1 "GND" H 10755 1177 50  0000 C CNN
F 2 "" H 10750 1350 50  0001 C CNN
F 3 "" H 10750 1350 50  0001 C CNN
	1    10750 1350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x10 J5
U 1 1 612DBEB7
P 10050 2150
F 0 "J5" V 10175 2096 50  0000 C CNN
F 1 "Logic Test" V 10266 2096 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10_Pitch2.54mm" H 10050 2150 50  0001 C CNN
F 3 "~" H 10050 2150 50  0001 C CNN
	1    10050 2150
	0    -1   1    0   
$EndComp
Text GLabel 10945 1800 2    39   Input ~ 0
SCL
Text GLabel 10945 1700 2    39   Input ~ 0
SDA
Text GLabel 1450 6100 0    39   Input ~ 0
CS_2
Text GLabel 3200 5100 2    39   Input ~ 0
CS_3
$Comp
L power:GND #PWR05
U 1 1 6154EBE1
P 1700 6950
F 0 "#PWR05" H 1700 6700 50  0001 C CNN
F 1 "GND" H 1705 6777 50  0000 C CNN
F 2 "" H 1700 6950 50  0001 C CNN
F 3 "" H 1700 6950 50  0001 C CNN
	1    1700 6950
	1    0    0    -1  
$EndComp
Text GLabel 1450 4700 0    39   Input ~ 0
RST
Text GLabel 1450 4900 0    39   Input ~ 0
DC
Text Notes 1925 7220 0    50   ~ 0
MSP2807 2.8" / 3.5" TFT \n 320 x 240 / 480 px\n/w Touch screen
Text GLabel 8750 5200 2    39   Input ~ 0
RST
Text GLabel 8750 5300 2    39   Input ~ 0
DC
Text Notes 3270 4725 0    50   ~ 0
rotary / push\n
Text GLabel 8750 4200 2    39   Input ~ 0
H_MOSI
Text GLabel 8750 4100 2    39   Input ~ 0
H_MISO
Text Notes 4005 5330 0    50   ~ 0
SPI devices:\n- ADC - CS_0\n- LCD - CS_1a\n- Touch CS_2\n- SD card CS_3 (no plans for implementation)
$Comp
L My-Design:RotaryEncoder_Switch SW1
U 1 1 60D23163
P 4045 4200
F 0 "SW1" H 4045 4567 50  0000 C CNN
F 1 "Encoder_Switch" H 4045 4476 50  0000 C CNN
F 2 "DigiKey:Rotary_Encoder_Switched_PEC11R" H 3895 4360 50  0001 C CNN
F 3 "~" H 4045 4460 50  0001 C CNN
	1    4045 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C12
U 1 1 60DF4C8C
P 6300 1850
F 0 "C12" H 6305 1960 50  0000 L CNN
F 1 "10u" H 6330 1740 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6300 1850 50  0001 C CNN
F 3 "~" H 6300 1850 50  0001 C CNN
	1    6300 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 60DF533A
P 6300 2000
F 0 "#PWR024" H 6300 1750 50  0001 C CNN
F 1 "GND" H 6305 1827 50  0000 C CNN
F 2 "" H 6300 2000 50  0001 C CNN
F 3 "" H 6300 2000 50  0001 C CNN
	1    6300 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 60E76691
P 3500 2400
F 0 "J3" H 3418 2717 50  0000 C CNN
F 1 "Bat/Ext/Off" H 3418 2626 50  0000 C CNN
F 2 "DigiKey:PinHeader_1x3_P2.54_Drill1.1mm" H 3500 2400 50  0001 C CNN
F 3 "~" H 3500 2400 50  0001 C CNN
	1    3500 2400
	-1   0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_GSD Q2
U 1 1 60EDAE9B
P 3500 1100
F 0 "Q2" V 3842 1100 50  0000 C CNN
F 1 "IRF6402" V 3751 1100 50  0000 C CNN
F 2 "DigiKey:SOT-23-3" H 3700 1200 50  0001 C CNN
F 3 "~" H 3500 1100 50  0001 C CNN
	1    3500 1100
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 60DC5E91
P 3250 1250
F 0 "C3" H 3265 1360 50  0000 L CNN
F 1 "10uF" H 3280 1165 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3250 1250 50  0001 C CNN
F 3 "~" H 3250 1250 50  0001 C CNN
	1    3250 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 60DC6F6E
P 3250 1450
F 0 "#PWR08" H 3250 1200 50  0001 C CNN
F 1 "GND" H 3255 1277 50  0000 C CNN
F 2 "" H 3250 1450 50  0001 C CNN
F 3 "" H 3250 1450 50  0001 C CNN
	1    3250 1450
	1    0    0    -1  
$EndComp
Text Notes 1355 3510 0    39   ~ 0
Note: If TFT LCD could be powered from MCU then\nremove U5, C2, L2 and install solder jumper JP1
Text Notes 1360 3245 0    39   ~ 0
Note: Q1/Q2 act as polarity protection
$Comp
L My-Design:MSP2807 U2
U 1 1 60E7E116
P 2400 5400
F 0 "U2" H 2400 6962 50  0000 C CNN
F 1 "MSP2807" H 2400 6871 50  0000 C CNN
F 2 "User:3.5_TFT" H 2350 7110 50  0001 C CNN
F 3 "" H 2340 7100 50  0001 C CNN
	1    2400 5400
	1    0    0    -1  
$EndComp
NoConn ~ 1900 6700
Text GLabel 8750 4300 2    39   Input ~ 0
H_SCK
Text GLabel 8750 4500 2    39   Input ~ 0
CS_2
Text GLabel 8750 5700 2    39   Input ~ 0
SWB
$Comp
L power:GND #PWR01
U 1 1 60D591CD
P 1050 2550
F 0 "#PWR01" H 1050 2300 50  0001 C CNN
F 1 "GND" H 1055 2377 50  0000 C CNN
F 2 "" H 1050 2550 50  0001 C CNN
F 3 "" H 1050 2550 50  0001 C CNN
	1    1050 2550
	1    0    0    -1  
$EndComp
$Comp
L My-Design:USB_C_Charge_2S U1
U 1 1 60C91F57
P 1050 1600
F 0 "U1" H 1157 2467 50  0000 C CNN
F 1 "USB_C_Charge_2S" H 1157 2376 50  0000 C CNN
F 2 "User:USB-C_Charge_2S" H 1050 1600 50  0001 C CNN
F 3 "" H 1050 1600 50  0001 C CNN
	1    1050 1600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 60CEC076
P 1700 1850
F 0 "J2" H 1618 2167 50  0000 C CNN
F 1 "Bat 2S Li-Ion" H 1618 2076 50  0000 C CNN
F 2 "DigiKey:PinHeader_1x3_P2.54_Drill1.1mm" H 1700 1850 50  0001 C CNN
F 3 "~" H 1700 1850 50  0001 C CNN
	1    1700 1850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 60D4E54D
P 2550 2800
F 0 "#PWR06" H 2550 2550 50  0001 C CNN
F 1 "GND" H 2555 2627 50  0000 C CNN
F 2 "" H 2550 2800 50  0001 C CNN
F 3 "" H 2550 2800 50  0001 C CNN
	1    2550 2800
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L1
U 1 1 60DC0BE1
P 3900 1500
F 0 "L1" H 3740 1625 50  0000 C CNN
F 1 "8.4 mH" H 3975 1630 50  0000 C CNN
F 2 "Inductors_SMD:L_1210_HandSoldering" H 3900 1500 50  0001 C CNN
F 3 "~" H 3900 1500 50  0001 C CNN
	1    3900 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 1000 4850 1000
Wire Wire Line
	4700 1000 4700 1100
Wire Wire Line
	5050 1950 5050 1650
Wire Wire Line
	5050 1950 5100 1950
Wire Wire Line
	5100 1650 5050 1650
Connection ~ 5050 1650
Wire Wire Line
	5050 1650 5050 1000
Wire Wire Line
	5500 2150 5500 2200
Wire Wire Line
	5700 2200 5700 2150
Wire Wire Line
	5500 2200 5600 2200
Wire Wire Line
	5600 2150 5600 2200
Connection ~ 5600 2200
Wire Wire Line
	5600 2200 5700 2200
Wire Wire Line
	5600 2200 5600 2250
Wire Wire Line
	6150 1750 6100 1750
Wire Wire Line
	6600 1755 6600 1655
Wire Wire Line
	7200 3250 7200 3200
Wire Wire Line
	6600 2005 6600 1955
Wire Wire Line
	4700 1450 4700 1300
Wire Wire Line
	4850 1450 4850 1300
Wire Wire Line
	4850 1100 4850 1000
Connection ~ 4850 1000
Wire Wire Line
	4850 1000 5050 1000
Wire Wire Line
	10350 1150 10350 1350
Wire Wire Line
	4850 905  4850 1000
Wire Wire Line
	6100 1650 6150 1650
Wire Wire Line
	6150 1750 6150 1650
Connection ~ 6150 1650
Wire Wire Line
	6150 1650 6300 1650
Connection ~ 6150 1750
Wire Wire Line
	6100 1950 6150 1950
Wire Wire Line
	9850 1150 9850 1500
Wire Wire Line
	9950 1150 9950 1600
Wire Wire Line
	10050 1150 10050 1700
Wire Wire Line
	9750 1950 9750 1400
Wire Wire Line
	9650 1950 9650 1300
Wire Wire Line
	7850 1300 8100 1300
Connection ~ 9650 1300
Wire Wire Line
	9650 1300 9650 1150
Connection ~ 9750 1400
Wire Wire Line
	9750 1400 9750 1150
Connection ~ 9850 1500
Wire Wire Line
	9850 1500 9850 1950
Connection ~ 9950 1600
Wire Wire Line
	9950 1600 9950 1950
Connection ~ 10050 1700
Wire Wire Line
	10050 1700 10050 1950
Wire Wire Line
	10150 1150 10150 1800
Wire Wire Line
	10550 1950 10550 1900
Wire Wire Line
	10550 1900 10750 1900
Wire Wire Line
	10750 1900 10750 1955
Wire Wire Line
	7600 1300 7650 1300
Wire Wire Line
	7600 1400 7650 1400
Wire Wire Line
	7595 1500 7650 1500
Wire Wire Line
	7600 1600 7650 1600
Wire Wire Line
	7600 1700 7650 1700
Wire Wire Line
	7600 1800 7650 1800
Wire Wire Line
	6750 1755 6750 1655
Wire Wire Line
	6750 1655 6600 1655
Wire Wire Line
	6750 1955 6750 2005
Connection ~ 4700 1000
Connection ~ 10150 1800
Connection ~ 6600 1655
Connection ~ 6750 1655
Wire Wire Line
	7200 3000 7200 2950
Wire Wire Line
	3750 3000 3750 2500
Wire Wire Line
	1050 3000 1350 3000
Wire Wire Line
	1050 3200 1050 3450
Wire Wire Line
	4350 1250 4350 1450
Wire Wire Line
	3450 3300 3450 3400
Wire Wire Line
	3550 3400 3550 3300
Connection ~ 3550 3300
Wire Wire Line
	3550 3300 3450 3300
Wire Wire Line
	3550 3600 3550 3650
Wire Wire Line
	3550 4100 3745 4100
Wire Wire Line
	3745 4300 3450 4300
Wire Wire Line
	3450 4300 3450 3650
Wire Wire Line
	4045 4550 3695 4550
Wire Wire Line
	3695 4550 3695 4200
Wire Wire Line
	3695 4200 3745 4200
Wire Wire Line
	4045 4550 4045 4650
Wire Wire Line
	4345 4300 4395 4300
Wire Wire Line
	4395 4300 4395 4550
Wire Wire Line
	4395 4550 4045 4550
Connection ~ 4045 4550
Wire Wire Line
	3350 4300 3450 4300
Connection ~ 3450 4300
Wire Wire Line
	3350 4100 3550 4100
Connection ~ 3550 4100
Wire Wire Line
	4345 4100 4350 4100
Wire Wire Line
	1900 1250 1950 1250
Wire Wire Line
	2550 2750 2550 2800
Wire Wire Line
	1050 2500 1050 2550
Wire Wire Line
	3250 1000 3300 1000
Connection ~ 3250 1000
Connection ~ 5050 1000
Wire Wire Line
	10250 1600 10650 1600
Wire Wire Line
	10250 1150 10250 1600
Wire Wire Line
	10650 1150 10650 1600
Connection ~ 10650 1600
Wire Wire Line
	10750 1150 10750 1350
Wire Wire Line
	10350 1700 10450 1700
Wire Wire Line
	10450 1800 10550 1800
Wire Wire Line
	10450 1800 10450 1950
Wire Wire Line
	10350 1700 10350 1950
Wire Wire Line
	10150 1800 10150 1950
Wire Wire Line
	1450 4700 1900 4700
Wire Wire Line
	1900 1850 1950 1850
Wire Wire Line
	1900 1950 1900 2450
Wire Wire Line
	1900 2450 1950 2450
Wire Wire Line
	10450 1150 10450 1700
Connection ~ 10450 1700
Wire Wire Line
	10450 1700 10945 1700
Wire Wire Line
	10550 1150 10550 1800
Connection ~ 10550 1800
Wire Wire Line
	10550 1800 10945 1800
Wire Wire Line
	6300 1750 6300 1650
Wire Wire Line
	6300 1950 6300 2000
Connection ~ 6300 1650
Wire Wire Line
	3500 1300 3500 1450
Wire Wire Line
	3700 2500 3750 2500
Wire Wire Line
	3700 2300 3750 2300
Wire Wire Line
	3750 2300 3750 1000
Wire Wire Line
	3700 1000 3750 1000
Wire Wire Line
	3250 1350 3250 1450
Wire Wire Line
	3250 1150 3250 1000
Wire Wire Line
	1450 4900 1900 4900
Wire Wire Line
	1900 4300 1700 4300
Wire Wire Line
	1700 4300 1700 6950
Wire Wire Line
	1650 4100 1900 4100
Wire Wire Line
	1650 4100 1650 5500
Wire Wire Line
	1650 5500 1900 5500
Wire Wire Line
	1800 5100 1800 6300
Wire Wire Line
	1800 6300 1900 6300
Wire Wire Line
	1800 5100 1900 5100
Wire Wire Line
	1450 6100 1900 6100
Wire Wire Line
	1900 5900 1750 5900
Wire Wire Line
	1750 5900 1750 5300
Wire Wire Line
	1750 5300 1900 5300
$Comp
L pspice:INDUCTOR L2
U 1 1 60F187A7
P 3900 2100
F 0 "L2" H 3740 2225 50  0000 C CNN
F 1 "8.4 mH" H 3975 2230 50  0000 C CNN
F 2 "Inductors_SMD:L_1210_HandSoldering" H 3900 2100 50  0001 C CNN
F 3 "~" H 3900 2100 50  0001 C CNN
	1    3900 2100
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 60E77C7F
P 4150 2050
F 0 "C6" H 4165 2160 50  0000 L CNN
F 1 "10u" H 4180 1965 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4150 2050 50  0001 C CNN
F 3 "~" H 4150 2050 50  0001 C CNN
	1    4150 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1250 3150 1000
Wire Wire Line
	3150 1000 3250 1000
$Comp
L power:GND #PWR014
U 1 1 60EE9294
P 4150 2200
F 0 "#PWR014" H 4150 1950 50  0001 C CNN
F 1 "GND" H 4155 2027 50  0000 C CNN
F 2 "" H 4150 2200 50  0001 C CNN
F 3 "" H 4150 2200 50  0001 C CNN
	1    4150 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2150 4150 2200
Text Notes 3995 5620 0    50   ~ 0
PCB board real-estate changed to 99 x 95 for 3.5"\ndisplay as 2.8" may just be little to small, same pinout\nchanged/updated footprint to bare ESP32
$Comp
L Device:C_Small C4
U 1 1 60FC5750
P 3350 3750
F 0 "C4" H 3365 3860 50  0000 L CNN
F 1 "10n" H 3380 3665 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3350 3750 50  0001 C CNN
F 3 "~" H 3350 3750 50  0001 C CNN
	1    3350 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 60FC7B77
P 3650 3750
F 0 "C5" H 3665 3860 50  0000 L CNN
F 1 "10n" H 3680 3665 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3650 3750 50  0001 C CNN
F 3 "~" H 3650 3750 50  0001 C CNN
	1    3650 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 60FCBB21
P 3350 3900
F 0 "#PWR09" H 3350 3650 50  0001 C CNN
F 1 "GND" H 3355 3727 50  0000 C CNN
F 2 "" H 3350 3900 50  0001 C CNN
F 3 "" H 3350 3900 50  0001 C CNN
	1    3350 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 60FCCD6A
P 3650 3900
F 0 "#PWR012" H 3650 3650 50  0001 C CNN
F 1 "GND" H 3655 3727 50  0000 C CNN
F 2 "" H 3650 3900 50  0001 C CNN
F 3 "" H 3650 3900 50  0001 C CNN
	1    3650 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3650 3450 3650
Connection ~ 3450 3650
Wire Wire Line
	3450 3650 3450 3600
Wire Wire Line
	3650 3650 3550 3650
Connection ~ 3550 3650
Wire Wire Line
	3550 3650 3550 4100
Wire Wire Line
	3350 3850 3350 3900
Wire Wire Line
	3650 3850 3650 3900
$Comp
L Switch:SW_Push SW2
U 1 1 610A0A3A
P 5500 3350
F 0 "SW2" H 5500 3635 50  0000 C CNN
F 1 "Reset" H 5500 3544 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_EVPBF" H 5500 3550 50  0001 C CNN
F 3 "~" H 5500 3550 50  0001 C CNN
	1    5500 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C10
U 1 1 610A2FE5
P 5500 3500
F 0 "C10" H 5515 3610 50  0000 L CNN
F 1 "1n" H 5530 3415 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5500 3500 50  0001 C CNN
F 3 "~" H 5500 3500 50  0001 C CNN
	1    5500 3500
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R7
U 1 1 610A6A8C
P 5900 3350
F 0 "R7" V 5970 3345 50  0000 C CNN
F 1 "470" V 5900 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5900 3350 50  0001 C CNN
F 3 "~" H 5900 3350 50  0001 C CNN
	1    5900 3350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 610A8655
P 5250 3550
F 0 "#PWR020" H 5250 3300 50  0001 C CNN
F 1 "GND" H 5255 3377 50  0000 C CNN
F 2 "" H 5250 3550 50  0001 C CNN
F 3 "" H 5250 3550 50  0001 C CNN
	1    5250 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3350 5750 3350
Wire Wire Line
	5300 3350 5250 3350
Wire Wire Line
	5250 3350 5250 3500
Wire Wire Line
	5400 3500 5250 3500
Connection ~ 5250 3500
Wire Wire Line
	5250 3500 5250 3550
Wire Wire Line
	5750 3500 5750 3350
Wire Wire Line
	5600 3500 5750 3500
Connection ~ 5750 3350
Wire Wire Line
	5750 3350 5700 3350
$Comp
L power:GND #PWR023
U 1 1 611B9971
P 5750 7200
F 0 "#PWR023" H 5750 6950 50  0001 C CNN
F 1 "GND" H 5755 7027 50  0000 C CNN
F 2 "" H 5750 7200 50  0001 C CNN
F 3 "" H 5750 7200 50  0001 C CNN
	1    5750 7200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J4
U 1 1 611ED526
P 3800 6800
F 0 "J4" H 3850 7217 50  0000 C CNN
F 1 "JTAG" H 3850 7126 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x05_Pitch2.54mm" H 3800 6800 50  0001 C CNN
F 3 "~" H 3800 6800 50  0001 C CNN
	1    3800 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 6700 3500 6700
Wire Wire Line
	3500 6700 3500 6800
Wire Wire Line
	3600 6800 3500 6800
Connection ~ 3500 6800
Wire Wire Line
	3600 7000 3500 7000
Connection ~ 3500 7000
Wire Wire Line
	3500 7000 3500 7100
$Comp
L power:GND #PWR011
U 1 1 61265C54
P 3500 7100
F 0 "#PWR011" H 3500 6850 50  0001 C CNN
F 1 "GND" H 3505 6927 50  0000 C CNN
F 2 "" H 3500 7100 50  0001 C CNN
F 3 "" H 3500 7100 50  0001 C CNN
	1    3500 7100
	1    0    0    -1  
$EndComp
NoConn ~ 4100 7000
Text GLabel 6800 1500 2    39   Input ~ 0
MCU_3V3
Text GLabel 3500 6600 0    39   Input ~ 0
MCU_3V3
Wire Wire Line
	3500 6600 3600 6600
Text GLabel 4200 6600 2    39   Input ~ 0
H_SCK
Text GLabel 4200 6900 2    39   Input ~ 0
H_MISO
Text GLabel 4200 6700 2    39   Input ~ 0
H_MOSI
Text GLabel 4200 6800 2    39   Input ~ 0
CS_4
Wire Wire Line
	4100 6600 4200 6600
Wire Wire Line
	4100 6700 4200 6700
Wire Wire Line
	4100 6800 4200 6800
Wire Wire Line
	4100 6900 4200 6900
Text GLabel 3195 5300 2    39   Input ~ 0
V_MOSI
Text GLabel 3200 5600 2    39   Input ~ 0
V_MISO
Text GLabel 3200 5900 2    39   Input ~ 0
V_SCK
Text GLabel 8750 3500 2    39   Input ~ 0
CS_1
Wire Wire Line
	1850 6850 2950 6850
Wire Wire Line
	2950 5500 2950 5600
Wire Wire Line
	2950 5500 2900 5500
Wire Wire Line
	1900 6500 1850 6500
Wire Wire Line
	1850 6500 1850 6850
Wire Wire Line
	1800 6300 1800 6900
Wire Wire Line
	1800 6900 3000 6900
Wire Wire Line
	3000 6900 3000 5300
Connection ~ 1800 6300
Connection ~ 3000 5300
Wire Wire Line
	3000 5300 2900 5300
Wire Wire Line
	1750 5900 1750 6950
Connection ~ 1750 5900
Wire Wire Line
	3050 5700 3050 5900
Wire Wire Line
	1750 6950 3050 6950
Wire Wire Line
	3050 5700 2900 5700
Text Notes 10130 2605 0    50   ~ 0
Note: J4 pin 9 - 10 can\nalso serve as I2C bus.
Wire Wire Line
	3000 5300 3195 5300
Wire Wire Line
	3200 5600 2950 5600
Connection ~ 2950 5600
Wire Wire Line
	2950 5600 2950 6850
Wire Wire Line
	3200 5900 3050 5900
Connection ~ 3050 5900
Wire Wire Line
	3050 5900 3050 6950
Text GLabel 1450 4500 0    39   Input ~ 0
CS_1
Wire Wire Line
	1450 4500 1900 4500
$Comp
L My-Design:BMS_Li-Ion U3
U 1 1 613B69F6
P 2550 1850
F 0 "U3" H 2535 2125 50  0000 C CNN
F 1 "BMS_Li-Ion" H 2550 2626 50  0000 C CNN
F 2 "User:HX-2S-A10" H 2560 1850 50  0001 C CNN
F 3 "" H 2560 1850 50  0001 C CNN
	1    2550 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6800 3500 6900
Wire Wire Line
	3600 6900 3500 6900
Connection ~ 3500 6900
Wire Wire Line
	3500 6900 3500 7000
$Comp
L Device:R_Small R8
U 1 1 61338C1A
P 6450 1655
F 0 "R8" V 6385 1660 50  0000 C CNN
F 1 "0" V 6450 1655 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6450 1655 50  0001 C CNN
F 3 "~" H 6450 1655 50  0001 C CNN
	1    6450 1655
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 1655 6600 1655
Wire Wire Line
	6300 1650 6350 1655
Wire Wire Line
	880  2500 1050 2500
Connection ~ 1050 2500
$Comp
L power:PWR_FLAG #FLG03
U 1 1 61621E0A
P 6600 1555
F 0 "#FLG03" H 6600 1630 50  0001 C CNN
F 1 "PWR_FLAG" H 6535 1725 50  0000 C CNN
F 2 "" H 6600 1555 50  0001 C CNN
F 3 "~" H 6600 1555 50  0001 C CNN
	1    6600 1555
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1555 6600 1655
$Comp
L Device:R_Small R3
U 1 1 60BBBB96
P 4350 3500
F 0 "R3" V 4420 3495 50  0000 C CNN
F 1 "4K7" V 4350 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 4350 3500 50  0001 C CNN
F 3 "~" H 4350 3500 50  0001 C CNN
	1    4350 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3400 4350 3300
Wire Wire Line
	4350 3300 3550 3300
Wire Wire Line
	4350 3650 4350 3600
Wire Wire Line
	4350 3650 4350 4100
Connection ~ 4350 3650
Connection ~ 4350 4100
$Comp
L Device:C_Small C7
U 1 1 60FCA656
P 4450 3750
F 0 "C7" H 4465 3860 50  0000 L CNN
F 1 "10n" H 4480 3665 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4450 3750 50  0001 C CNN
F 3 "~" H 4450 3750 50  0001 C CNN
	1    4450 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3650 4350 3650
Wire Wire Line
	4450 3850 4450 3900
$Comp
L power:GND #PWR016
U 1 1 60FCF2C8
P 4450 3900
F 0 "#PWR016" H 4450 3650 50  0001 C CNN
F 1 "GND" H 4455 3727 50  0000 C CNN
F 2 "" H 4450 3900 50  0001 C CNN
F 3 "" H 4450 3900 50  0001 C CNN
	1    4450 3900
	1    0    0    -1  
$EndComp
Connection ~ 1650 4100
Wire Wire Line
	4350 4100 4550 4100
$Comp
L power:GND #PWR036
U 1 1 6125B4AD
P 9450 6200
F 0 "#PWR036" H 9450 5950 50  0001 C CNN
F 1 "GND" H 9455 6027 50  0000 C CNN
F 2 "" H 9450 6200 50  0001 C CNN
F 3 "" H 9450 6200 50  0001 C CNN
	1    9450 6200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9450 6150 9450 6200
Wire Wire Line
	9450 5950 9450 5400
Wire Wire Line
	9300 6150 9300 6200
$Comp
L Device:C_Small C19
U 1 1 61201721
P 9450 6050
F 0 "C19" H 9465 6160 50  0000 L CNN
F 1 "1n" H 9480 5965 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9450 6050 50  0001 C CNN
F 3 "~" H 9450 6050 50  0001 C CNN
	1    9450 6050
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR034
U 1 1 60DA278D
P 9300 6200
F 0 "#PWR034" H 9300 5950 50  0001 C CNN
F 1 "GND" H 9305 6027 50  0000 C CNN
F 2 "" H 9300 6200 50  0001 C CNN
F 3 "" H 9300 6200 50  0001 C CNN
	1    9300 6200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R21
U 1 1 60D8FA60
P 9450 5200
F 0 "R21" V 9520 5195 50  0000 C CNN
F 1 "27K" V 9450 5200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9450 5200 50  0001 C CNN
F 3 "~" H 9450 5200 50  0001 C CNN
	1    9450 5200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R20
U 1 1 60D8D83E
P 9300 6050
F 0 "R20" V 9370 6045 50  0000 C CNN
F 1 "10K" V 9300 6050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9300 6050 50  0001 C CNN
F 3 "~" H 9300 6050 50  0001 C CNN
	1    9300 6050
	-1   0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 61842064
P 5500 6000
F 0 "H1" V 5625 6045 50  0000 C CNN
F 1 "MH" V 5605 5900 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 5500 6000 50  0001 C CNN
F 3 "~" H 5500 6000 50  0001 C CNN
	1    5500 6000
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 618C9F77
P 5500 6500
F 0 "H3" V 5610 6540 50  0000 C CNN
F 1 "MH" V 5646 6503 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 5500 6500 50  0001 C CNN
F 3 "~" H 5500 6500 50  0001 C CNN
	1    5500 6500
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 618CB582
P 5500 6250
F 0 "H2" V 5620 6290 50  0000 C CNN
F 1 "MH" V 5646 6253 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 5500 6250 50  0001 C CNN
F 3 "~" H 5500 6250 50  0001 C CNN
	1    5500 6250
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 618E7900
P 5500 6750
F 0 "H4" V 5625 6790 50  0000 C CNN
F 1 "MH" V 5585 7260 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 5500 6750 50  0001 C CNN
F 3 "~" H 5500 6750 50  0001 C CNN
	1    5500 6750
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H5
U 1 1 618E81AE
P 5500 7000
F 0 "H5" V 5610 7025 50  0000 C CNN
F 1 "MH" V 5550 7505 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad" H 5500 7000 50  0001 C CNN
F 3 "~" H 5500 7000 50  0001 C CNN
	1    5500 7000
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H7
U 1 1 618E81C2
P 6000 6250
F 0 "H7" V 6130 6300 50  0000 C CNN
F 1 "MH" V 6145 5460 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad" H 6000 6250 50  0001 C CNN
F 3 "~" H 6000 6250 50  0001 C CNN
	1    6000 6250
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H6
U 1 1 619044AC
P 6000 6000
F 0 "H6" V 6125 6030 50  0000 C CNN
F 1 "MH" V 6000 6530 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad" H 6000 6000 50  0001 C CNN
F 3 "~" H 6000 6000 50  0001 C CNN
	1    6000 6000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 6000 5650 6000
Wire Wire Line
	5650 6000 5650 6250
Wire Wire Line
	5650 7150 5750 7150
Wire Wire Line
	5750 7150 5750 7200
Wire Wire Line
	6100 6000 6150 6000
Wire Wire Line
	6150 6000 6150 6250
Wire Wire Line
	6150 7150 5750 7150
Connection ~ 5750 7150
Wire Wire Line
	5600 6250 5650 6250
Connection ~ 5650 6250
Wire Wire Line
	5600 6750 5650 6750
Connection ~ 5650 6750
Wire Wire Line
	5650 6750 5650 7000
Wire Wire Line
	5600 7000 5650 7000
Connection ~ 5650 7000
Wire Wire Line
	5650 7000 5650 7150
Wire Wire Line
	6100 6250 6150 6250
Connection ~ 6150 6250
$Comp
L Mechanical:MountingHole_Pad H8
U 1 1 618CB596
P 6000 6500
F 0 "H8" V 6125 6535 50  0000 C CNN
F 1 "MH" V 6295 5640 50  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad" H 6000 6500 50  0001 C CNN
F 3 "~" H 6000 6500 50  0001 C CNN
	1    6000 6500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6150 6250 6150 6500
Wire Wire Line
	6100 6500 6150 6500
Connection ~ 6150 6500
Wire Wire Line
	5650 6250 5650 6500
Wire Wire Line
	5600 6500 5650 6500
Connection ~ 5650 6500
Wire Wire Line
	5650 6500 5650 6750
$Comp
L RF_Module:ESP32-WROOM-32 U6
U 1 1 6239358F
P 8000 4700
F 0 "U6" H 7575 6070 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 8095 6125 50  0000 C CNN
F 2 "DigiKey:ESP32-WROOM-32D" H 8000 3200 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 7700 4750 50  0001 C CNN
	1    8000 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 2950 7200 2950
Wire Wire Line
	9100 3000 9100 2950
$Comp
L Regulator_Linear:AMS1117-3.3 U4
U 1 1 625A8D78
P 5600 1000
F 0 "U4" H 5440 1120 50  0000 C CNN
F 1 "AMS1117-3.3" H 5795 1125 50  0000 C CNN
F 2 "DigiKey:SOT-223-4" H 5600 1200 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 5700 750 50  0001 C CNN
	1    5600 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 1000 6150 1000
Wire Wire Line
	6150 1000 6150 1650
$Comp
L power:GND #PWR021
U 1 1 625FA784
P 5600 1350
F 0 "#PWR021" H 5600 1100 50  0001 C CNN
F 1 "GND" H 5740 1335 50  0000 C CNN
F 2 "" H 5600 1350 50  0001 C CNN
F 3 "" H 5600 1350 50  0001 C CNN
	1    5600 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1300 5600 1350
Wire Wire Line
	6800 1500 6750 1500
Wire Wire Line
	6750 1500 6750 1655
$Comp
L Device:Polyfuse_Small F2
U 1 1 60D2CA44
P 1900 1350
F 0 "F2" V 1695 1350 50  0000 C CNN
F 1 "Polyfuse_1A" V 1786 1350 50  0000 C CNN
F 2 "Fuse_Holders_and_Fuses:Fuse_SMD1206_HandSoldering" H 1950 1150 50  0001 L CNN
F 3 "~" H 1900 1350 50  0001 C CNN
	1    1900 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	1900 1450 1900 1750
Wire Wire Line
	1650 1000 3150 1000
Connection ~ 3150 1000
Wire Wire Line
	3900 1000 4700 1000
Wire Wire Line
	3900 1000 3900 1250
Wire Wire Line
	3900 1750 3900 1800
Wire Wire Line
	3900 1800 3900 1850
Connection ~ 3900 1800
Wire Wire Line
	3900 1800 4150 1800
Wire Wire Line
	4150 1800 4150 1950
Wire Wire Line
	3900 2350 3900 2400
Wire Wire Line
	3900 2400 3700 2400
Wire Wire Line
	5050 1000 5300 1000
Wire Wire Line
	3250 3000 3750 3000
Wire Wire Line
	1550 3000 2850 3000
Wire Wire Line
	3050 3300 3050 3450
$Comp
L Device:Q_PMOS_GSD Q1
U 1 1 60EE08AE
P 3050 3100
F 0 "Q1" V 3392 3100 50  0000 C CNN
F 1 "IRF6402" V 3301 3100 50  0000 C CNN
F 2 "DigiKey:SOT-23-3" H 3250 3200 50  0001 C CNN
F 3 "~" H 3050 3100 50  0001 C CNN
	1    3050 3100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 60B23F1A
P 3050 3450
F 0 "#PWR07" H 3050 3200 50  0001 C CNN
F 1 "GND" H 3055 3277 50  0000 C CNN
F 2 "" H 3050 3450 50  0001 C CNN
F 3 "" H 3050 3450 50  0001 C CNN
	1    3050 3450
	1    0    0    -1  
$EndComp
Text GLabel 6200 3350 2    39   Input ~ 0
EN
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 62EACD67
P 1600 5850
F 0 "JP1" V 1510 5700 50  0000 L CNN
F 1 "SDO En" V 1600 5500 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 1600 5850 50  0001 C CNN
F 3 "~" H 1600 5850 50  0001 C CNN
	1    1600 5850
	0    1    1    0   
$EndComp
Wire Wire Line
	1600 5700 1900 5700
Wire Wire Line
	1850 6500 1600 6500
Wire Wire Line
	1600 6500 1600 6000
Connection ~ 1850 6500
$Comp
L Device:C_Small C15
U 1 1 62F0CBF5
P 6850 3750
F 0 "C15" H 6865 3860 50  0000 L CNN
F 1 "1n" H 6880 3665 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6850 3750 50  0001 C CNN
F 3 "~" H 6850 3750 50  0001 C CNN
	1    6850 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R9
U 1 1 62F0F098
P 6850 3105
F 0 "R9" V 6920 3100 50  0000 C CNN
F 1 "12K" V 6850 3105 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6850 3105 50  0001 C CNN
F 3 "~" H 6850 3105 50  0001 C CNN
	1    6850 3105
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3205 6850 3500
Wire Wire Line
	7400 3500 6850 3500
Connection ~ 6850 3500
Wire Wire Line
	6850 3500 6850 3650
Text GLabel 6750 3500 0    39   Input ~ 0
EN
Wire Wire Line
	6750 3500 6850 3500
NoConn ~ 7400 3700
NoConn ~ 7400 3800
Wire Wire Line
	9450 5300 9450 5400
Wire Wire Line
	9300 5400 9300 5950
Wire Wire Line
	9450 5400 9300 5400
Connection ~ 9300 5400
Wire Wire Line
	9300 5400 8600 5400
Wire Wire Line
	8600 4900 9100 4900
Wire Wire Line
	8600 5000 9000 5000
Connection ~ 9450 5400
Wire Wire Line
	9100 3200 9100 4900
Connection ~ 9100 4900
Wire Wire Line
	9100 4900 9200 4900
Wire Wire Line
	9000 3200 9000 5000
Connection ~ 9000 5000
Wire Wire Line
	9000 5000 9200 5000
Wire Wire Line
	8600 5100 8750 5100
Wire Wire Line
	8600 4800 8750 4800
Wire Wire Line
	8600 4700 8750 4700
Wire Wire Line
	8600 4000 8750 4000
Wire Wire Line
	8600 4600 8750 4600
Wire Wire Line
	8600 4500 8750 4500
Wire Wire Line
	8600 3900 8750 3900
Wire Wire Line
	8600 4400 8750 4400
Wire Wire Line
	8600 5800 8750 5800
Wire Wire Line
	8600 5500 8750 5500
Wire Wire Line
	8600 5600 8750 5600
Wire Wire Line
	8600 5200 8750 5200
Wire Wire Line
	8600 5300 8750 5300
Wire Wire Line
	8750 4100 8600 4100
Wire Wire Line
	8600 4300 8750 4300
Wire Wire Line
	8000 3300 8000 2950
Connection ~ 8000 2950
Connection ~ 9000 2950
Wire Wire Line
	9000 2950 9100 2950
Wire Wire Line
	8000 2950 8700 2950
Wire Wire Line
	9000 3000 9000 2950
$Comp
L Device:R_Small R17
U 1 1 607E7877
P 9000 3100
F 0 "R17" V 8930 3090 50  0000 C CNN
F 1 "4K7" V 9000 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9000 3100 50  0001 C CNN
F 3 "~" H 9000 3100 50  0001 C CNN
	1    9000 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 3000 8700 2950
$Comp
L Device:R_Small R16
U 1 1 6346958E
P 8700 3100
F 0 "R16" V 8630 3090 50  0000 C CNN
F 1 "NC" V 8700 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8700 3100 50  0001 C CNN
F 3 "~" H 8700 3100 50  0001 C CNN
	1    8700 3100
	1    0    0    -1  
$EndComp
Connection ~ 8700 2950
Wire Wire Line
	8700 2950 9000 2950
Wire Wire Line
	8600 3500 8700 3500
Wire Wire Line
	8700 3200 8700 3350
Connection ~ 8700 3500
Wire Wire Line
	8700 3500 8750 3500
Connection ~ 7200 2950
Wire Wire Line
	7200 2950 7350 2950
$Comp
L Device:CP_Small C17
U 1 1 6350B896
P 7350 3100
F 0 "C17" H 7355 3210 50  0000 L CNN
F 1 "10u" H 7380 2990 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7350 3100 50  0001 C CNN
F 3 "~" H 7350 3100 50  0001 C CNN
	1    7350 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR029
U 1 1 6350C174
P 7350 3250
F 0 "#PWR029" H 7350 3000 50  0001 C CNN
F 1 "GND" H 7355 3077 50  0000 C CNN
F 2 "" H 7350 3250 50  0001 C CNN
F 3 "" H 7350 3250 50  0001 C CNN
	1    7350 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3200 7350 3250
Wire Wire Line
	7350 2950 7350 3000
Connection ~ 7350 2950
Wire Wire Line
	7350 2950 7500 2950
$Comp
L Device:C_Small C18
U 1 1 6355C501
P 7500 3100
F 0 "C18" H 7515 3210 50  0000 L CNN
F 1 "0.1" H 7530 3015 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7500 3100 50  0001 C CNN
F 3 "~" H 7500 3100 50  0001 C CNN
	1    7500 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 6355CDFD
P 7500 3250
F 0 "#PWR030" H 7500 3000 50  0001 C CNN
F 1 "GND" H 7505 3077 50  0000 C CNN
F 2 "" H 7500 3250 50  0001 C CNN
F 3 "" H 7500 3250 50  0001 C CNN
	1    7500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3250 7500 3200
Wire Wire Line
	7500 2950 7500 3000
Connection ~ 7500 2950
Wire Wire Line
	7500 2950 8000 2950
Wire Wire Line
	6850 3005 6850 2950
$Comp
L Device:R_Small R19
U 1 1 635B1BF3
P 9200 3950
F 0 "R19" V 9130 3940 50  0000 C CNN
F 1 "NC" V 9200 3950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9200 3950 50  0001 C CNN
F 3 "~" H 9200 3950 50  0001 C CNN
	1    9200 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR033
U 1 1 635B3738
P 9200 4100
F 0 "#PWR033" H 9200 3850 50  0001 C CNN
F 1 "GND" H 9205 3927 50  0000 C CNN
F 2 "" H 9200 4100 50  0001 C CNN
F 3 "" H 9200 4100 50  0001 C CNN
	1    9200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4100 9200 4050
Wire Wire Line
	9200 3850 9200 3700
Wire Wire Line
	9200 3700 8600 3700
NoConn ~ 7400 4700
NoConn ~ 7400 4800
NoConn ~ 7400 4900
NoConn ~ 7400 5000
NoConn ~ 7400 5100
NoConn ~ 7400 5200
$Comp
L power:GND #PWR031
U 1 1 6379AC9B
P 8000 6200
F 0 "#PWR031" H 8000 5950 50  0001 C CNN
F 1 "GND" H 8005 6027 50  0000 C CNN
F 2 "" H 8000 6200 50  0001 C CNN
F 3 "" H 8000 6200 50  0001 C CNN
	1    8000 6200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8000 6100 8000 6200
$Comp
L power:GND #PWR027
U 1 1 637E9380
P 6850 3950
F 0 "#PWR027" H 6850 3700 50  0001 C CNN
F 1 "GND" H 6855 3777 50  0000 C CNN
F 2 "" H 6850 3950 50  0001 C CNN
F 3 "" H 6850 3950 50  0001 C CNN
	1    6850 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3850 6850 3950
Text GLabel 8050 2795 2    39   Input ~ 0
MCU_3V3
Wire Wire Line
	8050 2795 8000 2795
Wire Wire Line
	8000 2795 8000 2950
$Comp
L power:GND #PWR040
U 1 1 6390AAB1
P 9950 3850
F 0 "#PWR040" H 9950 3600 50  0001 C CNN
F 1 "GND" H 9955 3677 50  0000 C CNN
F 2 "" H 9950 3850 50  0001 C CNN
F 3 "" H 9950 3850 50  0001 C CNN
	1    9950 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 3850 9950 3800
Wire Wire Line
	10000 3800 9950 3800
Wire Wire Line
	10000 3500 9950 3500
Wire Wire Line
	10000 3700 9650 3700
Wire Wire Line
	9400 3700 9400 3800
Wire Wire Line
	9400 3800 8600 3800
Wire Wire Line
	10000 3600 9650 3600
Text GLabel 8750 3350 2    39   Input ~ 0
IO0
Wire Wire Line
	8750 3350 8700 3350
Connection ~ 8700 3350
Wire Wire Line
	8700 3350 8700 3500
Text GLabel 4400 3145 2    39   Input ~ 0
MCU_3V3
Wire Wire Line
	4400 3145 4350 3145
Wire Wire Line
	4350 3145 4350 3300
Connection ~ 4350 3300
Text GLabel 1700 3850 2    39   Input ~ 0
MCU_3V3
Wire Wire Line
	1700 3850 1650 3850
Wire Wire Line
	1650 3850 1650 4100
$Comp
L Device:C_Small C1
U 1 1 62513E84
P 1250 4050
F 0 "C1" H 1265 4160 50  0000 L CNN
F 1 "0.1" H 1280 3965 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1250 4050 50  0001 C CNN
F 3 "~" H 1250 4050 50  0001 C CNN
	1    1250 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6251475E
P 1250 4200
F 0 "#PWR03" H 1250 3950 50  0001 C CNN
F 1 "GND" H 1255 4027 50  0000 C CNN
F 2 "" H 1250 4200 50  0001 C CNN
F 3 "" H 1250 4200 50  0001 C CNN
	1    1250 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C2
U 1 1 62514768
P 1400 4050
F 0 "C2" H 1405 4160 50  0000 L CNN
F 1 "10u" H 1430 3940 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1400 4050 50  0001 C CNN
F 3 "~" H 1400 4050 50  0001 C CNN
	1    1400 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 62514772
P 1400 4200
F 0 "#PWR04" H 1400 3950 50  0001 C CNN
F 1 "GND" H 1405 4027 50  0000 C CNN
F 2 "" H 1400 4200 50  0001 C CNN
F 3 "" H 1400 4200 50  0001 C CNN
	1    1400 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 3950 1250 3850
Wire Wire Line
	1250 4200 1250 4150
Wire Wire Line
	1400 3950 1400 3850
Wire Wire Line
	1400 4150 1400 4200
Wire Wire Line
	1250 3850 1400 3850
Wire Wire Line
	1400 3850 1650 3850
Connection ~ 1400 3850
Connection ~ 1650 3850
Text GLabel 7600 1900 0    39   Input ~ 0
MCU_3V3
Wire Wire Line
	7600 1900 10250 1900
Wire Wire Line
	10250 1900 10250 1950
$Comp
L Device:R_Small R22
U 1 1 625B1601
P 9550 3600
F 0 "R22" V 9515 3485 50  0000 C CNN
F 1 "0" V 9550 3600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9550 3600 50  0001 C CNN
F 3 "~" H 9550 3600 50  0001 C CNN
	1    9550 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 3600 8600 3600
$Comp
L Device:R_Small R23
U 1 1 625B3A6E
P 9550 3700
F 0 "R23" V 9515 3585 50  0000 C CNN
F 1 "0" V 9550 3700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9550 3700 50  0001 C CNN
F 3 "~" H 9550 3700 50  0001 C CNN
	1    9550 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 3700 9400 3700
Wire Wire Line
	9200 1000 9200 1050
Wire Wire Line
	7200 1050 7200 1100
Wire Wire Line
	8000 1000 8000 1050
Connection ~ 8000 1050
Wire Wire Line
	8200 1000 8200 1050
Connection ~ 8200 1050
Wire Wire Line
	8200 1050 8000 1050
Wire Wire Line
	8400 1000 8400 1050
Connection ~ 8400 1050
Wire Wire Line
	8400 1050 8200 1050
Wire Wire Line
	8600 1000 8600 1050
Connection ~ 8600 1050
Wire Wire Line
	8600 1050 8400 1050
Wire Wire Line
	9200 1050 9000 1050
Wire Wire Line
	8800 1000 8800 1050
Connection ~ 8800 1050
Wire Wire Line
	8800 1050 8600 1050
Wire Wire Line
	9000 1000 9000 1050
Connection ~ 9000 1050
Wire Wire Line
	9000 1050 8800 1050
Text GLabel 5100 800  2    50   Input ~ 0
V_Ana
Text GLabel 7600 1150 0    50   Input ~ 0
V_Ana
Text GLabel 10950 1600 2    50   Input ~ 0
V_Ana
Wire Wire Line
	5100 800  5050 800 
Wire Wire Line
	5050 800  5050 1000
Wire Wire Line
	10650 1600 10950 1600
$Comp
L power:GND #PWR0101
U 1 1 62A77401
P 7200 1100
F 0 "#PWR0101" H 7200 850 50  0001 C CNN
F 1 "GND" H 7205 927 50  0000 C CNN
F 2 "" H 7200 1100 50  0001 C CNN
F 3 "" H 7200 1100 50  0001 C CNN
	1    7200 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1000 8100 1300
Text GLabel 9500 5000 2    50   Input ~ 0
V_Ana
Wire Wire Line
	9450 5000 9500 5000
Wire Wire Line
	9450 5000 9450 5100
Text Notes 10680 7635 0    50   ~ 0
V5
Text Notes 7490 7490 0    50   ~ 0
RF Meter control board
Wire Wire Line
	6000 3350 6200 3350
$Comp
L Switch:SW_Push SW3
U 1 1 625102CE
P 5500 4100
F 0 "SW3" H 5500 4385 50  0000 C CNN
F 1 "Boot" H 5500 4294 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_EVPBF" H 5500 4300 50  0001 C CNN
F 3 "~" H 5500 4300 50  0001 C CNN
	1    5500 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 62510C5C
P 5900 4100
F 0 "R4" V 5970 4095 50  0000 C CNN
F 1 "470" V 5900 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5900 4100 50  0001 C CNN
F 3 "~" H 5900 4100 50  0001 C CNN
	1    5900 4100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 62510C66
P 5250 4300
F 0 "#PWR019" H 5250 4050 50  0001 C CNN
F 1 "GND" H 5255 4127 50  0000 C CNN
F 2 "" H 5250 4300 50  0001 C CNN
F 3 "" H 5250 4300 50  0001 C CNN
	1    5250 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 4100 5250 4100
Text GLabel 6200 4100 2    39   Input ~ 0
IO0
Wire Wire Line
	6000 4100 6200 4100
Wire Wire Line
	5250 4100 5250 4250
Wire Wire Line
	5700 4100 5750 4100
Wire Wire Line
	9100 2950 9950 2950
Connection ~ 9100 2950
Wire Wire Line
	9950 2950 9950 3050
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 626C5931
P 9950 3200
F 0 "JP2" V 9860 3050 50  0000 L CNN
F 1 "3V3 Pwr" H 9895 3110 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9950 3200 50  0001 C CNN
F 3 "~" H 9950 3200 50  0001 C CNN
	1    9950 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	9950 3350 9950 3500
$Comp
L Connector_Generic:Conn_01x04 J7
U 1 1 626CABE6
P 10200 3600
F 0 "J7" H 10280 3592 50  0000 L CNN
F 1 "Uart" H 10280 3501 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 10200 3600 50  0001 C CNN
F 3 "~" H 10200 3600 50  0001 C CNN
	1    10200 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C20
U 1 1 626CEEDF
P 5500 4250
F 0 "C20" H 5515 4360 50  0000 L CNN
F 1 "1n" H 5530 4165 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5500 4250 50  0001 C CNN
F 3 "~" H 5500 4250 50  0001 C CNN
	1    5500 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 4250 5250 4250
Wire Wire Line
	5750 4250 5750 4100
Wire Wire Line
	5600 4250 5750 4250
Connection ~ 5250 4250
Wire Wire Line
	5250 4250 5250 4300
Connection ~ 5750 4100
Wire Wire Line
	5750 4100 5800 4100
Text GLabel 4550 4100 2    50   Input ~ 0
SWC
Wire Wire Line
	8600 4200 8750 4200
Wire Wire Line
	2900 5100 3200 5100
Wire Wire Line
	8600 5700 8750 5700
Wire Wire Line
	6150 6500 6150 7150
$Comp
L Connector:Conn_01x16_Female J8
U 1 1 6248AAE8
P 8700 800
F 0 "J8" V 8865 730 50  0000 C CNN
F 1 "FFC MCU Interface" V 8774 730 50  0000 C CNN
F 2 "Connector_FFC:TE_1-84952-6_1x16-1MP_P1.0mm_Horizontal" H 8700 800 50  0001 C CNN
F 3 "~" H 8700 800 50  0001 C CNN
	1    8700 800 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9200 1050 9400 1050
Wire Wire Line
	9400 1050 9400 1000
Connection ~ 9200 1050
Wire Wire Line
	7200 1050 8000 1050
Wire Wire Line
	7600 1150 9300 1150
Connection ~ 9300 1150
Wire Wire Line
	9300 1150 9500 1150
Wire Wire Line
	9500 1000 9500 1150
Wire Wire Line
	9300 1000 9300 1150
Connection ~ 8100 1300
Wire Wire Line
	8500 1000 8500 1500
Wire Wire Line
	8300 1000 8300 1400
Connection ~ 8700 1600
Wire Wire Line
	8700 1600 9950 1600
Connection ~ 8900 1700
Wire Wire Line
	8900 1700 10050 1700
Connection ~ 9100 1800
Wire Wire Line
	9100 1800 10150 1800
Wire Wire Line
	9100 1000 9100 1800
Wire Wire Line
	8100 1300 9650 1300
Wire Wire Line
	7850 1400 8300 1400
Wire Wire Line
	8900 1000 8900 1700
Wire Wire Line
	7850 1800 9100 1800
Wire Wire Line
	7850 1500 8500 1500
Wire Wire Line
	8700 1000 8700 1600
Connection ~ 8500 1500
Wire Wire Line
	8500 1500 9850 1500
Connection ~ 8300 1400
Wire Wire Line
	8300 1400 9750 1400
Wire Wire Line
	7850 1600 8700 1600
Wire Wire Line
	7850 1700 8900 1700
Text Notes 650  5850 0    50   ~ 0
Open on display\nmodel ILI9488
$EndSCHEMATC

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
L Device:R_Small R29
U 1 1 6059560D
P 2910 5300
F 0 "R29" V 2825 5300 50  0000 C CNN
F 1 "385" V 2910 5290 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2910 5300 50  0001 C CNN
F 3 "~" H 2910 5300 50  0001 C CNN
	1    2910 5300
	0    1    1    0   
$EndComp
Connection ~ 3250 5300
$Comp
L Device:C_Small C19
U 1 1 605B23B6
P 3050 5450
F 0 "C19" H 3000 5525 50  0000 L CNN
F 1 "100n" H 2905 5375 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3050 5450 50  0001 C CNN
F 3 "~" H 3050 5450 50  0001 C CNN
	1    3050 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 5600 3050 5550
$Comp
L Device:CP_Small C23
U 1 1 605BC3E0
P 3250 5450
F 0 "C23" H 3200 5525 50  0000 L CNN
F 1 "10u" H 3150 5375 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3250 5450 50  0001 C CNN
F 3 "~" H 3250 5450 50  0001 C CNN
	1    3250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3010 5300 3050 5300
Wire Wire Line
	3050 5350 3050 5300
Connection ~ 3050 5300
Wire Wire Line
	3250 5600 3250 5550
Wire Wire Line
	3250 5350 3250 5300
$Comp
L Device:C_Small C40
U 1 1 606A059A
P 5300 5650
F 0 "C40" H 5245 5745 50  0000 L CNN
F 1 "100n" H 5200 5565 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5300 5650 50  0001 C CNN
F 3 "~" H 5300 5650 50  0001 C CNN
	1    5300 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C26
U 1 1 60716EBD
P 7000 5600
F 0 "C26" H 7005 5695 50  0000 L CNN
F 1 "100n" H 6900 5510 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7000 5600 50  0001 C CNN
F 3 "~" H 7000 5600 50  0001 C CNN
	1    7000 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C27
U 1 1 606192C6
P 7150 5600
F 0 "C27" H 7155 5695 50  0000 L CNN
F 1 "10u" H 7100 5510 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7150 5600 50  0001 C CNN
F 3 "~" H 7150 5600 50  0001 C CNN
	1    7150 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5850 7000 5700
Text Notes 5955 6315 0    100  ~ 0
Analog to Digital section
Text Notes 7030 7000 0    197  ~ 39
RF Meter ADC front-end
Text Notes 8510 7630 0    39   ~ 0
7-jun-2021 / v1.2
$Comp
L Device:CP_Small C41
U 1 1 606553BC
P 5450 5650
F 0 "C41" H 5395 5750 50  0000 L CNN
F 1 "4u7" H 5400 5560 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5450 5650 50  0001 C CNN
F 3 "~" H 5450 5650 50  0001 C CNN
	1    5450 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 5755 6400 5850
$Comp
L Device:CP_Small C45
U 1 1 6059FA6C
P 6400 5655
F 0 "C45" H 6350 5805 50  0000 L CNN
F 1 "10u" H 6350 5565 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6400 5655 50  0001 C CNN
F 3 "~" H 6400 5655 50  0001 C CNN
	1    6400 5655
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C44
U 1 1 606C71E0
P 6250 5650
F 0 "C44" H 6195 5790 50  0000 L CNN
F 1 "100n" H 6150 5555 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6250 5650 50  0001 C CNN
F 3 "~" H 6250 5650 50  0001 C CNN
	1    6250 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5850 6250 5750
$Comp
L power:PWR_FLAG #FLG06
U 1 1 60693D90
P 6400 5200
F 0 "#FLG06" H 6400 5275 50  0001 C CNN
F 1 "PWR_FLAG" H 6250 5350 50  0000 C CNN
F 2 "" H 6400 5200 50  0001 C CNN
F 3 "~" H 6400 5200 50  0001 C CNN
	1    6400 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 5450 6400 5555
Wire Wire Line
	6400 5200 6400 5450
Connection ~ 6400 5450
$Comp
L Device:R_Small R28
U 1 1 60791F95
P 2750 5455
F 0 "R28" V 2850 5450 50  0000 C CNN
F 1 "1K" V 2665 5450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2750 5455 50  0001 C CNN
F 3 "~" H 2750 5455 50  0001 C CNN
	1    2750 5455
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small RL2
U 1 1 609B5C2D
P 1095 1550
F 0 "RL2" H 1145 1555 50  0000 L CNN
F 1 "~" V 1015 1470 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" H 1095 1550 50  0001 C CNN
F 3 "~" H 1095 1550 50  0001 C CNN
	1    1095 1550
	1    0    0    -1  
$EndComp
Text Notes 710  795  0    100  ~ 0
A - Probe 50 Ohm
Wire Notes Line
	645  1990 2370 1995
Wire Notes Line
	640  635  645  1990
Wire Notes Line
	2365 635  640  635 
Wire Notes Line
	2370 1990 2365 635 
$Comp
L Device:R_Small R6
U 1 1 609B5CB2
P 2200 1000
F 0 "R6" V 2130 950 50  0000 L CNN
F 1 "560" V 2270 920 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2200 1000 50  0001 C CNN
F 3 "~" H 2200 1000 50  0001 C CNN
	1    2200 1000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R5
U 1 1 609B5CA8
P 2195 1600
F 0 "R5" V 2110 1545 50  0000 L CNN
F 1 "560" V 2260 1520 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2195 1600 50  0001 C CNN
F 3 "~" H 2195 1600 50  0001 C CNN
	1    2195 1600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R1
U 1 1 609B5C9E
P 1800 1000
F 0 "R1" V 1720 950 50  0000 L CNN
F 1 "110" V 1865 930 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 1800 1000 50  0001 C CNN
F 3 "~" H 1800 1000 50  0001 C CNN
	1    1800 1000
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 609B5C94
P 2000 1150
F 0 "C3" H 2010 1215 50  0000 L CNN
F 1 "1n" H 2005 1080 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2000 1150 50  0001 C CNN
F 3 "~" H 2000 1150 50  0001 C CNN
	1    2000 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 609B5C8A
P 2000 1450
F 0 "C4" H 2010 1510 50  0000 L CNN
F 1 "1n" H 1995 1390 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2000 1450 50  0001 C CNN
F 3 "~" H 2000 1450 50  0001 C CNN
	1    2000 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 609B5C80
P 1800 1600
F 0 "R2" V 1720 1545 50  0000 L CNN
F 1 "110" V 1860 1525 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 1800 1600 50  0001 C CNN
F 3 "~" H 1800 1600 50  0001 C CNN
	1    1800 1600
	0    -1   -1   0   
$EndComp
$Comp
L Diode:BAT54S D1
U 1 1 609B5C76
P 1600 1300
F 0 "D1" V 1635 1345 50  0000 L CNN
F 1 "BAT62" V 1555 1350 50  0000 L CNN
F 2 "DigiKey:SOT-143-4-SPC" H 1675 1425 50  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds11005.pdf" H 1480 1300 50  0001 C CNN
	1    1600 1300
	0    1    -1   0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 609B5C6C
P 1250 1300
F 0 "C1" V 1350 1250 50  0000 L CNN
F 1 "1n" V 1140 1230 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1250 1300 50  0001 C CNN
F 3 "~" H 1250 1300 50  0001 C CNN
	1    1250 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 1300 1400 1300
Wire Wire Line
	1600 1000 1700 1000
Wire Wire Line
	1900 1000 2000 1000
Wire Wire Line
	2000 1050 2000 1000
Connection ~ 2000 1000
Wire Wire Line
	2000 1000 2100 1000
Wire Wire Line
	1600 1600 1700 1600
Wire Wire Line
	1900 1600 2000 1600
Wire Wire Line
	2000 1550 2000 1600
Connection ~ 2000 1600
Wire Wire Line
	2000 1600 2095 1600
Wire Wire Line
	2000 1250 2000 1300
Connection ~ 2000 1300
Wire Wire Line
	2000 1300 2000 1350
$Comp
L Connector:Conn_Coaxial J1
U 1 1 609B5C4F
P 895 1300
F 0 "J1" H 910 1535 50  0000 C CNN
F 1 "SMA" H 890 1445 50  0000 C CNN
F 2 "Coax:SMA_Samtec_SMA-J-P-X-ST-EM1_EdgeMount" H 895 1300 50  0001 C CNN
F 3 " ~" H 895 1300 50  0001 C CNN
	1    895  1300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1645 1545 2000 1300
Wire Wire Line
	1095 1300 1150 1300
Wire Wire Line
	895  1500 895  1700
Wire Wire Line
	1645 1545 1645 1700
$Comp
L Device:R_Small RL1
U 1 1 609B5C23
P 1095 1050
F 0 "RL1" H 1130 1015 50  0000 L CNN
F 1 "~" V 1015 975 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" H 1095 1050 50  0001 C CNN
F 3 "~" H 1095 1050 50  0001 C CNN
	1    1095 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1095 950  1095 900 
Wire Wire Line
	1095 900  1195 900 
Wire Wire Line
	1195 900  1195 950 
Wire Wire Line
	1095 1150 1095 1300
Connection ~ 1095 1300
Wire Wire Line
	1095 1450 1095 1300
Wire Wire Line
	1095 1650 1095 1700
Text Notes 760  2160 0    100  ~ 0
B - Probe 50 Ohm
Wire Notes Line
	645  1995 650  3350
Wire Notes Line
	2370 1995 645  1995
Wire Notes Line
	2370 3705 2370 1985
$Comp
L Device:R_Small R8
U 1 1 60732B14
P 2205 2400
F 0 "R8" V 2135 2350 50  0000 L CNN
F 1 "560" V 2275 2320 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2205 2400 50  0001 C CNN
F 3 "~" H 2205 2400 50  0001 C CNN
	1    2205 2400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R7
U 1 1 607392D0
P 2200 3000
F 0 "R7" V 2115 2945 50  0000 L CNN
F 1 "560" V 2270 2905 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2200 3000 50  0001 C CNN
F 3 "~" H 2200 3000 50  0001 C CNN
	1    2200 3000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 60739C33
P 1800 2400
F 0 "R3" V 1720 2350 50  0000 L CNN
F 1 "110" V 1865 2330 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 1800 2400 50  0001 C CNN
F 3 "~" H 1800 2400 50  0001 C CNN
	1    1800 2400
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 6073AE57
P 2000 2550
F 0 "C5" H 2020 2625 50  0000 L CNN
F 1 "1nF" H 2010 2465 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2000 2550 50  0001 C CNN
F 3 "~" H 2000 2550 50  0001 C CNN
	1    2000 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 6073BA32
P 2000 2850
F 0 "C6" H 2020 2945 50  0000 L CNN
F 1 "1nF" H 2000 2775 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2000 2850 50  0001 C CNN
F 3 "~" H 2000 2850 50  0001 C CNN
	1    2000 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 6073CB4C
P 1800 3000
F 0 "R4" V 1720 2945 50  0000 L CNN
F 1 "110" V 1860 2925 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 1800 3000 50  0001 C CNN
F 3 "~" H 1800 3000 50  0001 C CNN
	1    1800 3000
	0    -1   -1   0   
$EndComp
$Comp
L Diode:BAT54S D2
U 1 1 6073E26B
P 1600 2700
F 0 "D2" V 1635 2745 50  0000 L CNN
F 1 "BAT62" V 1555 2750 50  0000 L CNN
F 2 "DigiKey:SOT-143-4-SPC" H 1675 2825 50  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds11005.pdf" H 1480 2700 50  0001 C CNN
	1    1600 2700
	0    1    -1   0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 607583AF
P 1250 2700
F 0 "C2" V 1370 2655 50  0000 L CNN
F 1 "1nF" V 1130 2635 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1250 2700 50  0001 C CNN
F 3 "~" H 1250 2700 50  0001 C CNN
	1    1250 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 2700 1400 2700
Wire Wire Line
	1600 2400 1700 2400
Wire Wire Line
	1900 2400 2000 2400
Wire Wire Line
	2000 2450 2000 2400
Connection ~ 2000 2400
Wire Wire Line
	2000 2400 2105 2400
Wire Wire Line
	1600 3000 1700 3000
Wire Wire Line
	1900 3000 2000 3000
Wire Wire Line
	2000 2950 2000 3000
Connection ~ 2000 3000
Wire Wire Line
	2000 3000 2100 3000
Wire Wire Line
	2000 2650 2000 2700
Connection ~ 2000 2700
Wire Wire Line
	2000 2700 2000 2750
$Comp
L Connector:Conn_Coaxial J2
U 1 1 607A7AFB
P 895 2700
F 0 "J2" H 910 2935 50  0000 C CNN
F 1 "SMA" H 890 2845 50  0000 C CNN
F 2 "Coax:SMA_Samtec_SMA-J-P-X-ST-EM1_EdgeMount" H 895 2700 50  0001 C CNN
F 3 " ~" H 895 2700 50  0001 C CNN
	1    895  2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1645 2945 2000 2700
Wire Wire Line
	1095 2700 1150 2700
Wire Wire Line
	895  2900 895  3100
$Comp
L Device:R_Small RL4
U 1 1 6064D6E8
P 1095 2950
F 0 "RL4" H 1145 2955 50  0000 L CNN
F 1 "100" V 1015 2870 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" H 1095 2950 50  0001 C CNN
F 3 "~" H 1095 2950 50  0001 C CNN
	1    1095 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small RL3
U 1 1 6065C33B
P 1095 2450
F 0 "RL3" H 1130 2415 50  0000 L CNN
F 1 "100" V 1015 2375 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" H 1095 2450 50  0001 C CNN
F 3 "~" H 1095 2450 50  0001 C CNN
	1    1095 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1095 2350 1095 2300
Wire Wire Line
	1095 2300 1200 2300
Wire Wire Line
	1200 2300 1200 2350
Wire Wire Line
	1095 2550 1095 2700
Connection ~ 1095 2700
Wire Wire Line
	1095 2850 1095 2700
Wire Wire Line
	1095 3050 1095 3100
Wire Wire Line
	5300 5550 5300 5450
Connection ~ 5300 5450
Wire Wire Line
	5300 5450 5450 5450
Wire Wire Line
	5450 5550 5450 5450
Connection ~ 5450 5450
Wire Notes Line
	2365 6535 2370 1765
Wire Notes Line
	11150 650  11150 5350
Wire Notes Line
	11100 5350 11100 5345
Wire Notes Line
	2530 6365 11180 6365
$Comp
L Device:R_Small R10
U 1 1 60CD2FCD
P 2900 2550
F 0 "R10" V 2985 2475 50  0000 L CNN
F 1 "5M6" V 2830 2460 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2900 2550 50  0001 C CNN
F 3 "~" H 2900 2550 50  0001 C CNN
	1    2900 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R11
U 1 1 60CD3AD3
P 2900 2850
F 0 "R11" V 2970 2790 50  0000 L CNN
F 1 "5M6" V 2825 2765 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2900 2850 50  0001 C CNN
F 3 "~" H 2900 2850 50  0001 C CNN
	1    2900 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C10
U 1 1 60CD3AE7
P 2650 2850
F 0 "C10" H 2670 2950 50  0000 L CNN
F 1 "47n" H 2600 2765 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W3.5mm_P5.00mm" H 2650 2850 50  0001 C CNN
F 3 "~" H 2650 2850 50  0001 C CNN
	1    2650 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2100 4650 2850
Wire Wire Line
	4650 2850 4700 2850
Wire Wire Line
	4600 2050 4600 2550
Wire Wire Line
	4600 2550 4700 2550
Wire Wire Line
	5600 2050 5600 2250
Wire Wire Line
	5600 2250 5500 2250
Wire Wire Line
	5550 2100 5550 2450
Wire Wire Line
	5550 2450 5500 2450
Wire Wire Line
	2650 3000 2650 2950
Wire Wire Line
	2650 3000 2900 3000
Wire Wire Line
	2900 3000 2900 2950
Connection ~ 2650 3000
Wire Wire Line
	2900 2400 2900 2450
Connection ~ 2650 2400
Connection ~ 2900 2700
Wire Wire Line
	2900 2700 2900 2750
Wire Wire Line
	4700 2650 4150 2650
Wire Wire Line
	4150 2650 4150 2400
Wire Wire Line
	2650 2400 2900 2400
Connection ~ 2900 2400
Wire Wire Line
	2900 2400 3350 2400
Wire Wire Line
	3700 3000 3700 2950
Wire Wire Line
	3700 2950 4700 2950
Connection ~ 2900 3000
$Comp
L My-Analog:AD8639 IC2
U 1 1 60CD3B65
P 5100 2650
F 0 "IC2" H 5510 2245 50  0000 C CNN
F 1 "LTC2055" H 5225 2290 50  0000 C CNN
F 2 "SO:MSOP-8_3x3mm_P0.65mm" H 4800 2050 50  0001 L CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/AD8638_8639.pdf" H 4800 1950 50  0001 L CNN
F 4 "AD8639ARMZ-ND" H 4800 1850 50  0001 L CNN "Digikey"
	1    5100 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R13
U 1 1 60E133E0
P 2900 4250
F 0 "R13" V 2970 4190 50  0000 L CNN
F 1 "5M6" V 2825 4165 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2900 4250 50  0001 C CNN
F 3 "~" H 2900 4250 50  0001 C CNN
	1    2900 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C11
U 1 1 60E133EA
P 2655 3950
F 0 "C11" H 2675 4020 50  0000 L CNN
F 1 "47n" H 2595 3865 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W3.5mm_P5.00mm" H 2655 3950 50  0001 C CNN
F 3 "~" H 2655 3950 50  0001 C CNN
	1    2655 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C12
U 1 1 60E133F4
P 2655 4250
F 0 "C12" H 2665 4345 50  0000 L CNN
F 1 "47n" H 2605 4180 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W3.5mm_P5.00mm" H 2655 4250 50  0001 C CNN
F 3 "~" H 2655 4250 50  0001 C CNN
	1    2655 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 4250 4700 4250
Wire Wire Line
	4600 3950 4700 3950
Wire Wire Line
	5600 3650 5500 3650
Wire Wire Line
	5550 3850 5500 3850
Wire Wire Line
	2500 4100 2500 4450
Wire Wire Line
	2450 4400 2655 4400
Wire Wire Line
	2655 4400 2655 4350
Wire Wire Line
	2655 4400 2900 4400
Wire Wire Line
	2900 4400 2900 4350
Connection ~ 2655 4400
Wire Wire Line
	2450 3800 2655 3800
Wire Wire Line
	2655 3800 2655 3850
Connection ~ 2655 3800
Wire Wire Line
	2900 4050 2900 4100
Connection ~ 2900 4100
Wire Wire Line
	2900 4100 2900 4150
Wire Wire Line
	4700 4050 4150 4050
Wire Wire Line
	4150 4050 4150 3800
Wire Wire Line
	2655 3800 2900 3800
Connection ~ 2900 3800
Wire Wire Line
	2900 3800 3350 3800
Wire Wire Line
	3700 4400 3700 4350
Wire Wire Line
	3700 4350 4700 4350
Connection ~ 2900 4400
Wire Wire Line
	2450 3800 2450 4000
Wire Wire Line
	2450 4400 2450 4200
$Comp
L My-Analog:AD8639 IC3
U 1 1 60E13472
P 5100 4050
F 0 "IC3" H 5520 3650 50  0000 C CNN
F 1 "LTC2055" H 5215 3685 50  0000 C CNN
F 2 "SO:MSOP-8_3x3mm_P0.65mm" H 4800 3450 50  0001 L CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/AD8638_8639.pdf" H 4800 3350 50  0001 L CNN
F 4 "AD8639ARMZ-ND" H 4800 3250 50  0001 L CNN "Digikey"
	1    5100 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2305 2400 2650 2400
Wire Wire Line
	2300 3000 2650 3000
Wire Notes Line
	650  5505 2375 5500
Wire Notes Line
	650  3365 650  5495
Wire Notes Line
	2380 5460 2375 3715
Text Notes 730  3670 0    100  ~ 0
C - Boonton Probe
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 614241CC
P 2000 4100
F 0 "J3" H 2020 4340 50  0000 C CNN
F 1 "Amphenol 80-PC2F" H 2035 3885 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 2000 4100 50  0001 C CNN
F 3 "~" H 2000 4100 50  0001 C CNN
	1    2000 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2200 4000 2450 4000
Wire Wire Line
	2200 4100 2500 4100
Wire Wire Line
	2200 4200 2450 4200
Wire Wire Line
	3100 4150 3100 4100
Connection ~ 5600 2250
Connection ~ 5550 2450
Wire Wire Line
	2505 2700 2505 3050
Wire Wire Line
	2000 2700 2505 2700
Text GLabel 4400 2250 0    39   Input ~ 0
AV3V6DD
Text GLabel 4400 3650 0    39   Input ~ 0
AV3V6DD
Wire Wire Line
	2750 5600 2750 5555
Wire Wire Line
	2750 5355 2750 5300
Text GLabel 2650 5300 0    39   Input ~ 0
VPre
Text GLabel 3200 2700 2    39   Input ~ 0
VPre
Text GLabel 3200 4100 2    39   Input ~ 0
VPre
Wire Wire Line
	5300 5750 5300 5850
Wire Wire Line
	5450 5750 5450 5850
Wire Wire Line
	6250 5550 6250 5450
Connection ~ 6250 5450
$Comp
L Device:C_Small C28
U 1 1 62C19229
P 7450 5600
F 0 "C28" H 7395 5675 50  0000 L CNN
F 1 "100n" H 7350 5515 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7450 5600 50  0001 C CNN
F 3 "~" H 7450 5600 50  0001 C CNN
	1    7450 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C29
U 1 1 62C19ED1
P 7600 5600
F 0 "C29" H 7545 5675 50  0000 L CNN
F 1 "4u7" H 7545 5510 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7600 5600 50  0001 C CNN
F 3 "~" H 7600 5600 50  0001 C CNN
	1    7600 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 5500 7450 5400
Wire Wire Line
	7600 5500 7600 5400
Wire Wire Line
	7750 5450 7750 5400
$Comp
L Device:C_Small C31
U 1 1 62C19EDE
P 7750 5300
F 0 "C31" V 7700 5330 50  0000 L CNN
F 1 "10nF" V 7695 5080 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7750 5300 50  0001 C CNN
F 3 "~" H 7750 5300 50  0001 C CNN
	1    7750 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	7450 5700 7450 5850
Wire Wire Line
	7600 5700 7600 5850
Wire Wire Line
	7450 5400 7600 5400
Connection ~ 7450 5400
Connection ~ 7600 5400
Connection ~ 7750 5400
Wire Wire Line
	7750 5400 7900 5400
Wire Wire Line
	8300 5850 8300 5800
Text GLabel 4950 5450 0    39   Input ~ 0
D3V3DD
$Comp
L Device:R_Small R31
U 1 1 64764D4A
P 7750 5550
F 0 "R31" V 7815 5445 50  0000 C CNN
F 1 "10K" V 7815 5620 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7750 5550 50  0001 C CNN
F 3 "~" H 7750 5550 50  0001 C CNN
	1    7750 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R32
U 1 1 647EF62B
P 8000 5800
F 0 "R32" V 7930 5730 50  0000 C CNN
F 1 "20K" V 7930 5915 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8000 5800 50  0001 C CNN
F 3 "~" H 8000 5800 50  0001 C CNN
	1    8000 5800
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R33
U 1 1 647F5277
P 8000 5900
F 0 "R33" V 8065 5810 50  0000 C CNN
F 1 "6K8" V 8065 5970 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8000 5900 50  0001 C CNN
F 3 "~" H 8000 5900 50  0001 C CNN
	1    8000 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	8100 5900 8150 5900
Wire Wire Line
	8100 5800 8150 5800
Wire Wire Line
	7900 5900 7850 5900
Wire Wire Line
	7850 5900 7850 5800
Wire Wire Line
	7900 5800 7850 5800
Connection ~ 7850 5800
Wire Wire Line
	7900 5600 7850 5600
$Comp
L Regulator_Linear:LT1761-BYP U7
U 1 1 6224AC6D
P 8300 5500
F 0 "U7" H 8110 5240 50  0000 C CNN
F 1 "LT1761-BYP" H 8300 5776 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 8300 5850 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/1761sff.pdf" H 8300 5500 50  0001 C CNN
	1    8300 5500
	-1   0    0    -1  
$EndComp
Text Notes 8250 5500 0    39   ~ 0
3V6\nregulator
$Comp
L Device:C_Small C25
U 1 1 60C212A3
P 4350 5550
F 0 "C25" H 4300 5635 50  0000 L CNN
F 1 "100n" H 4300 5465 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4350 5550 50  0001 C CNN
F 3 "~" H 4350 5550 50  0001 C CNN
	1    4350 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C24
U 1 1 60C23BC0
P 4200 5550
F 0 "C24" H 4150 5630 50  0000 L CNN
F 1 "100n" H 4105 5465 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4200 5550 50  0001 C CNN
F 3 "~" H 4200 5550 50  0001 C CNN
	1    4200 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 5850 3750 5800
Wire Wire Line
	3450 5500 3400 5500
Wire Wire Line
	3400 5500 3400 5300
Wire Wire Line
	3400 5300 3450 5300
Wire Wire Line
	3250 5300 3400 5300
Connection ~ 3400 5300
Wire Wire Line
	4050 5200 4100 5200
Wire Wire Line
	4200 5450 4200 5400
Wire Wire Line
	4050 5400 4200 5400
Wire Wire Line
	4350 5450 4350 5200
Wire Wire Line
	4350 5650 4350 5850
Wire Wire Line
	4050 5600 4100 5600
Wire Wire Line
	4100 5600 4100 5200
Connection ~ 4100 5200
Wire Wire Line
	4100 5200 4350 5200
$Comp
L Device:C_Small C22
U 1 1 60D82B1F
P 4450 3900
F 0 "C22" H 4400 3980 50  0000 L CNN
F 1 "100n" H 4300 3835 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4450 3900 50  0001 C CNN
F 3 "~" H 4450 3900 50  0001 C CNN
	1    4450 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C21
U 1 1 60DD812B
P 4450 2500
F 0 "C21" H 4400 2595 50  0000 L CNN
F 1 "100n" H 4305 2415 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4450 2500 50  0001 C CNN
F 3 "~" H 4450 2500 50  0001 C CNN
	1    4450 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2700 4450 2600
Text Notes 10695 5120 0    39   ~ 0
6V - 8V4 pwr\nfrom Li-Ion\n(2S - BMS)
Wire Wire Line
	4450 4000 4450 4100
Wire Wire Line
	7150 5500 7150 5400
Connection ~ 7150 5400
Wire Wire Line
	7150 5700 7150 5850
Wire Wire Line
	4600 2050 5600 2050
Wire Wire Line
	4650 2100 5550 2100
Wire Wire Line
	4650 700  5550 700 
Wire Wire Line
	4600 650  5600 650 
Text GLabel 4400 850  0    39   Input ~ 0
AV3V6DD
Connection ~ 5550 1050
Connection ~ 5600 850 
$Comp
L My-Analog:AD8639 IC1
U 1 1 6054709F
P 5100 1250
F 0 "IC1" H 5495 855 50  0000 C CNN
F 1 "LTC2055" H 5230 870 50  0000 C CNN
F 2 "SO:MSOP-8_3x3mm_P0.65mm" H 4800 650 50  0001 L CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/AD8638_8639.pdf" H 4800 550 50  0001 L CNN
F 4 "AD8639ARMZ-ND" H 4800 450 50  0001 L CNN "Digikey"
	1    5100 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1550 4700 1550
Wire Wire Line
	3650 1600 3650 1550
Wire Wire Line
	4100 1250 4100 1000
Wire Wire Line
	5550 1050 5500 1050
Wire Wire Line
	5550 700  5550 1050
Wire Wire Line
	5600 850  5500 850 
Wire Wire Line
	5600 650  5600 850 
Wire Wire Line
	4600 1150 4700 1150
Wire Wire Line
	4600 650  4600 1150
Wire Wire Line
	4650 1450 4700 1450
Wire Wire Line
	4650 700  4650 1450
Wire Wire Line
	3050 5300 3250 5300
Wire Wire Line
	4450 1000 4450 850 
Text GLabel 3200 1300 2    39   Input ~ 0
VPre
Wire Wire Line
	2000 1300 2500 1300
Wire Wire Line
	2295 1600 2650 1600
Wire Wire Line
	2300 1000 2650 1000
Connection ~ 2905 1600
Connection ~ 2905 1000
Wire Wire Line
	2650 1000 2905 1000
Wire Wire Line
	2905 1300 2905 1350
Connection ~ 2905 1300
Wire Wire Line
	2905 1250 2905 1300
Connection ~ 2650 1000
Wire Wire Line
	2905 1000 2905 1050
Wire Wire Line
	2650 1000 2650 1050
Connection ~ 2650 1600
Wire Wire Line
	2905 1600 2905 1550
Wire Wire Line
	2650 1600 2905 1600
Wire Wire Line
	2650 1600 2650 1550
$Comp
L Device:C_Small C8
U 1 1 6054CCC6
P 2650 1450
F 0 "C8" H 2660 1540 50  0000 L CNN
F 1 "47n" H 2600 1380 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W3.5mm_P5.00mm" H 2650 1450 50  0001 C CNN
F 3 "~" H 2650 1450 50  0001 C CNN
	1    2650 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 6054C082
P 2650 1150
F 0 "C7" H 2660 1235 50  0000 L CNN
F 1 "47n" H 2600 1070 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W3.5mm_P5.00mm" H 2650 1150 50  0001 C CNN
F 3 "~" H 2650 1150 50  0001 C CNN
	1    2650 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R15
U 1 1 6054B074
P 2905 1450
F 0 "R15" V 2975 1390 50  0000 L CNN
F 1 "5M6" V 2830 1365 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2905 1450 50  0001 C CNN
F 3 "~" H 2905 1450 50  0001 C CNN
	1    2905 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R14
U 1 1 6054A74A
P 2905 1150
F 0 "R14" V 2990 1075 50  0000 L CNN
F 1 "5M6" V 2835 1075 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2905 1150 50  0001 C CNN
F 3 "~" H 2905 1150 50  0001 C CNN
	1    2905 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3000 3350 3000
Connection ~ 3100 4100
Wire Wire Line
	3100 4100 2900 4100
$Comp
L Device:C_Small C15
U 1 1 605B18BA
P 3100 4250
F 0 "C15" H 3110 4315 50  0000 L CNN
F 1 "100nF" H 3005 4175 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3100 4250 50  0001 C CNN
F 3 "~" H 3100 4250 50  0001 C CNN
	1    3100 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 4400 3350 4400
Wire Wire Line
	3100 4350 3100 4445
Wire Wire Line
	2750 5300 2810 5300
Connection ~ 2750 5300
Wire Wire Line
	2650 1250 2650 1300
Wire Wire Line
	2500 1300 2500 1650
Wire Wire Line
	2500 1300 2650 1300
Connection ~ 2500 1300
Connection ~ 2650 1300
Wire Wire Line
	2650 1300 2650 1350
Wire Wire Line
	2650 2400 2650 2450
$Comp
L Device:C_Small C9
U 1 1 60CD3ADD
P 2650 2550
F 0 "C9" H 2660 2640 50  0000 L CNN
F 1 "47n" H 2595 2475 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W3.5mm_P5.00mm" H 2650 2550 50  0001 C CNN
F 3 "~" H 2650 2550 50  0001 C CNN
	1    2650 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2650 2650 2700
Wire Wire Line
	2900 2650 2900 2700
Wire Wire Line
	2505 2700 2650 2700
Connection ~ 2505 2700
Connection ~ 2650 2700
Wire Wire Line
	2650 2700 2650 2750
Wire Wire Line
	2900 3800 2900 3850
$Comp
L Device:R_Small R12
U 1 1 60E12822
P 2900 3950
F 0 "R12" V 2985 3875 50  0000 L CNN
F 1 "5M6" V 2830 3875 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2900 3950 50  0001 C CNN
F 3 "~" H 2900 3950 50  0001 C CNN
	1    2900 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2655 4050 2655 4100
Wire Wire Line
	2500 4100 2655 4100
Connection ~ 2500 4100
Connection ~ 2655 4100
Wire Wire Line
	2655 4100 2655 4150
Wire Wire Line
	7000 5500 7000 5400
Wire Wire Line
	7000 5400 7150 5400
Wire Wire Line
	10900 5450 10900 5350
Connection ~ 10900 5350
Wire Wire Line
	10900 5350 11100 5350
Wire Wire Line
	10800 5450 10800 5400
$Comp
L power:PWR_FLAG #FLG04
U 1 1 60FDFA46
P 7000 5200
F 0 "#FLG04" H 7000 5275 50  0001 C CNN
F 1 "PWR_FLAG" H 7000 5350 50  0000 C CNN
F 2 "" H 7000 5200 50  0001 C CNN
F 3 "~" H 7000 5200 50  0001 C CNN
	1    7000 5200
	1    0    0    -1  
$EndComp
Text Notes 645  7360 0    39   ~ 0
Note: R8/R29  divider for 1V8 used for Pre to obtain 1V3\n      R20 to adjust and obtain output of U7 to 3V6 dc MAX !.\n\nNote: R34, R35, C32 / R53, R54, C30 may serve as a \nfilter option else place jumper wire or 0 Ohm for \nR34, R35, R53, R54 and omit C32, C30\n\nNote: check all regulator voltages prior to installing\n      LTC2055's and MAX11270's\n
Text Notes 645  7655 0    39   ~ 0
R1...R4: For BAT62 diode  use 110 or 113 ohms\n              For 1SS351 diode use 82.5 ohms.\n
$Comp
L Device:R_Small R30
U 1 1 61397D78
P 7300 5400
F 0 "R30" V 7380 5370 50  0000 C CNN
F 1 "0" V 7295 5395 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7300 5400 50  0001 C CNN
F 3 "~" H 7300 5400 50  0001 C CNN
	1    7300 5400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7150 5400 7200 5400
$Comp
L Device:R_Small R40
U 1 1 61468949
P 5150 5450
F 0 "R40" V 5230 5420 50  0000 C CNN
F 1 "0" V 5145 5445 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5150 5450 50  0001 C CNN
F 3 "~" H 5150 5450 50  0001 C CNN
	1    5150 5450
	0    -1   -1   0   
$EndComp
Connection ~ 4450 850 
Wire Wire Line
	4450 850  4700 850 
Wire Wire Line
	4400 850  4450 850 
Wire Wire Line
	4550 950  4550 1300
Wire Wire Line
	4550 950  4700 950 
Wire Wire Line
	4450 1200 4450 1300
Wire Wire Line
	4100 1250 4700 1250
$Comp
L Device:R_Small R16
U 1 1 6277B2D8
P 3400 1000
F 0 "R16" V 3320 950 50  0000 L CNN
F 1 "100K" V 3465 930 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3400 1000 50  0001 C CNN
F 3 "~" H 3400 1000 50  0001 C CNN
	1    3400 1000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 1000 3550 1000
$Comp
L Device:R_Small R17
U 1 1 6277CE55
P 3405 1600
F 0 "R17" V 3325 1550 50  0000 L CNN
F 1 "100K" V 3470 1530 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3405 1600 50  0001 C CNN
F 3 "~" H 3405 1600 50  0001 C CNN
	1    3405 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3505 1600 3550 1600
$Comp
L Device:R_Small R22
U 1 1 6277EDCC
P 3750 1150
F 0 "R22" H 3650 1370 50  0000 L CNN
F 1 "100K" V 3680 1075 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3750 1150 50  0001 C CNN
F 3 "~" H 3750 1150 50  0001 C CNN
	1    3750 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R25
U 1 1 6277F909
P 3850 1150
F 0 "R25" H 3810 1370 50  0000 L CNN
F 1 "100K" V 3920 1080 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3850 1150 50  0001 C CNN
F 3 "~" H 3850 1150 50  0001 C CNN
	1    3850 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C16
U 1 1 627F3D37
P 3550 1300
F 0 "C16" H 3395 1375 50  0000 L CNN
F 1 "10n" H 3450 1230 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3550 1300 50  0001 C CNN
F 3 "~" H 3550 1300 50  0001 C CNN
	1    3550 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 1050 3750 1000
Connection ~ 3750 1000
Wire Wire Line
	3750 1000 3850 1000
Wire Wire Line
	3850 1050 3850 1000
Connection ~ 3850 1000
Wire Wire Line
	3850 1000 4100 1000
Wire Wire Line
	2905 1000 3300 1000
Wire Wire Line
	2905 1600 3305 1600
Wire Wire Line
	3550 1200 3550 1000
Connection ~ 3550 1000
Wire Wire Line
	3550 1000 3750 1000
Wire Wire Line
	3550 1400 3550 1600
Connection ~ 3550 1600
Wire Wire Line
	3550 1600 3650 1600
$Comp
L Relay_SolidState:CPC1117N U1
U 1 1 620341A5
P 4050 1800
F 0 "U1" H 4030 1580 50  0000 C CNN
F 1 "AQY212" H 4050 2005 50  0000 C CNN
F 2 "DigiKey:SOP-4_W3.81mm" H 3850 1600 50  0001 L CIN
F 3 "http://www.ixysic.com/home/pdfs.nsf/www/CPC1117N.pdf/$file/CPC1117N.pdf" H 4000 1800 50  0001 L CNN
	1    4050 1800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3750 1900 3650 1900
Wire Wire Line
	3650 1900 3650 1600
Connection ~ 3650 1600
Wire Wire Line
	3750 1700 3750 1300
Wire Wire Line
	3850 1250 3850 1300
Wire Wire Line
	3850 1300 3750 1300
Connection ~ 3750 1300
Wire Wire Line
	3750 1300 3750 1250
Text GLabel 4400 1700 2    39   Input ~ 0
D3V3DD
Wire Wire Line
	4400 1700 4350 1700
Text GLabel 4400 1900 2    39   Input ~ 0
Att_A
Wire Wire Line
	4400 1900 4350 1900
Wire Wire Line
	4400 2250 4450 2250
Wire Wire Line
	4450 2250 4450 2400
Connection ~ 4450 2250
Wire Wire Line
	4450 2250 4700 2250
Wire Wire Line
	4550 2700 4550 2350
Wire Wire Line
	4550 2350 4700 2350
$Comp
L Relay_SolidState:CPC1117N U2
U 1 1 625AD667
P 4100 3200
F 0 "U2" H 4080 2980 50  0000 C CNN
F 1 "AQY212" H 4100 3405 50  0000 C CNN
F 2 "DigiKey:SOP-4_W3.81mm" H 3900 3000 50  0001 L CIN
F 3 "http://www.ixysic.com/home/pdfs.nsf/www/CPC1117N.pdf/$file/CPC1117N.pdf" H 4050 3200 50  0001 L CNN
	1    4100 3200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 3300 3700 3300
Wire Wire Line
	3700 3300 3700 3000
Wire Wire Line
	3800 3100 3800 2700
Text GLabel 4450 3300 2    39   Input ~ 0
Att_B_C
Wire Wire Line
	4450 3300 4400 3300
Connection ~ 3700 3000
$Comp
L Device:R_Small R18
U 1 1 625EE970
P 3450 2400
F 0 "R18" V 3370 2350 50  0000 L CNN
F 1 "100K" V 3515 2330 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3450 2400 50  0001 C CNN
F 3 "~" H 3450 2400 50  0001 C CNN
	1    3450 2400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 2400 3600 2400
$Comp
L Device:R_Small R23
U 1 1 625EF59D
P 3800 2550
F 0 "R23" H 3765 2780 50  0000 L CNN
F 1 "100K" V 3730 2475 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3800 2550 50  0001 C CNN
F 3 "~" H 3800 2550 50  0001 C CNN
	1    3800 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R26
U 1 1 625EF5A7
P 3900 2550
F 0 "R26" H 3910 2775 50  0000 L CNN
F 1 "100K" V 3970 2480 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3900 2550 50  0001 C CNN
F 3 "~" H 3900 2550 50  0001 C CNN
	1    3900 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C17
U 1 1 625EF5B1
P 3600 2700
F 0 "C17" H 3445 2795 50  0000 L CNN
F 1 "10n" H 3505 2620 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3600 2700 50  0001 C CNN
F 3 "~" H 3600 2700 50  0001 C CNN
	1    3600 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2450 3800 2400
Connection ~ 3800 2400
Wire Wire Line
	3800 2400 3900 2400
Wire Wire Line
	3900 2450 3900 2400
Connection ~ 3900 2400
Wire Wire Line
	3900 2400 4150 2400
Wire Wire Line
	3600 2600 3600 2400
Connection ~ 3600 2400
Wire Wire Line
	3600 2400 3800 2400
Wire Wire Line
	3600 2800 3600 3000
Wire Wire Line
	3900 2650 3900 2700
Wire Wire Line
	3900 2700 3800 2700
Connection ~ 3800 2700
Wire Wire Line
	3800 2700 3800 2650
Connection ~ 3600 3000
Wire Wire Line
	3600 3000 3700 3000
$Comp
L Device:R_Small R19
U 1 1 6263B2D3
P 3450 3000
F 0 "R19" V 3370 2950 50  0000 L CNN
F 1 "100K" V 3515 2930 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3450 3000 50  0001 C CNN
F 3 "~" H 3450 3000 50  0001 C CNN
	1    3450 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 3000 3600 3000
Wire Wire Line
	4550 3750 4550 4100
Wire Wire Line
	4550 3750 4700 3750
Wire Wire Line
	4400 3650 4450 3650
Wire Wire Line
	4450 3800 4450 3650
Connection ~ 4450 3650
Wire Wire Line
	4450 3650 4700 3650
Text GLabel 4400 3650 0    39   Input ~ 0
AV3V6DD
$Comp
L Relay_SolidState:CPC1117N U3
U 1 1 62B02E93
P 4100 4600
F 0 "U3" H 4080 4380 50  0000 C CNN
F 1 "AQY212" H 4100 4805 50  0000 C CNN
F 2 "DigiKey:SOP-4_W3.81mm" H 3900 4400 50  0001 L CIN
F 3 "http://www.ixysic.com/home/pdfs.nsf/www/CPC1117N.pdf/$file/CPC1117N.pdf" H 4050 4600 50  0001 L CNN
	1    4100 4600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 4700 3700 4700
Wire Wire Line
	3700 4700 3700 4400
Wire Wire Line
	3800 4500 3800 4100
Connection ~ 3700 4400
$Comp
L Device:R_Small R20
U 1 1 62B02EA1
P 3450 3800
F 0 "R20" V 3370 3750 50  0000 L CNN
F 1 "100K" V 3515 3730 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3450 3800 50  0001 C CNN
F 3 "~" H 3450 3800 50  0001 C CNN
	1    3450 3800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 3800 3600 3800
$Comp
L Device:R_Small R24
U 1 1 62B02EAC
P 3800 3950
F 0 "R24" H 3765 4180 50  0000 L CNN
F 1 "100K" V 3730 3875 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3800 3950 50  0001 C CNN
F 3 "~" H 3800 3950 50  0001 C CNN
	1    3800 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R27
U 1 1 62B02EB6
P 3900 3950
F 0 "R27" H 3910 4175 50  0000 L CNN
F 1 "100K" V 3970 3880 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3900 3950 50  0001 C CNN
F 3 "~" H 3900 3950 50  0001 C CNN
	1    3900 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C18
U 1 1 62B02EC0
P 3600 4100
F 0 "C18" H 3430 4180 50  0000 L CNN
F 1 "10n" H 3505 4015 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3600 4100 50  0001 C CNN
F 3 "~" H 3600 4100 50  0001 C CNN
	1    3600 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3850 3800 3800
Connection ~ 3800 3800
Wire Wire Line
	3800 3800 3900 3800
Wire Wire Line
	3900 3850 3900 3800
Connection ~ 3900 3800
Wire Wire Line
	3900 3800 4150 3800
Wire Wire Line
	3600 4000 3600 3800
Connection ~ 3600 3800
Wire Wire Line
	3600 3800 3800 3800
Wire Wire Line
	3600 4200 3600 4400
Wire Wire Line
	3900 4050 3900 4100
Wire Wire Line
	3900 4100 3800 4100
Connection ~ 3800 4100
Wire Wire Line
	3800 4100 3800 4050
Connection ~ 3600 4400
Wire Wire Line
	3600 4400 3700 4400
$Comp
L Device:R_Small R21
U 1 1 62B02EDA
P 3450 4400
F 0 "R21" V 3370 4350 50  0000 L CNN
F 1 "100K" V 3515 4330 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3450 4400 50  0001 C CNN
F 3 "~" H 3450 4400 50  0001 C CNN
	1    3450 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 4400 3600 4400
Text GLabel 4450 4700 2    39   Input ~ 0
Att_B_C
Wire Wire Line
	4450 4700 4400 4700
Wire Wire Line
	2750 5200 2750 5300
Wire Wire Line
	7400 5400 7450 5400
Text GLabel 6900 5250 0    39   Input ~ 0
AV3V6DD
Connection ~ 7000 5400
Wire Wire Line
	5250 5450 5300 5450
$Comp
L power:PWR_FLAG #FLG05
U 1 1 60761F55
P 5000 5200
F 0 "#FLG05" H 5000 5275 50  0001 C CNN
F 1 "PWR_FLAG" H 4850 5350 50  0000 C CNN
F 2 "" H 5000 5200 50  0001 C CNN
F 3 "~" H 5000 5200 50  0001 C CNN
	1    5000 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 5450 5000 5450
Wire Wire Line
	8900 5705 8900 5850
$Comp
L Device:CP_Small C34
U 1 1 6419EE43
P 8900 5605
F 0 "C34" H 8845 5700 50  0000 L CNN
F 1 "10u" H 8855 5525 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8900 5605 50  0001 C CNN
F 3 "~" H 8900 5605 50  0001 C CNN
	1    8900 5605
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C33
U 1 1 6419EE4D
P 8750 5600
F 0 "C33" H 8695 5690 50  0000 L CNN
F 1 "100n" H 8650 5520 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8750 5600 50  0001 C CNN
F 3 "~" H 8750 5600 50  0001 C CNN
	1    8750 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 5850 8750 5700
Wire Wire Line
	8750 5500 8750 5400
Connection ~ 8750 5400
Wire Wire Line
	8750 5400 8900 5400
Wire Wire Line
	8900 5400 8900 5505
Wire Wire Line
	8700 5400 8750 5400
Wire Wire Line
	7600 5400 7750 5400
Wire Wire Line
	7650 5300 7600 5300
Wire Wire Line
	7600 5300 7600 5400
Wire Wire Line
	7850 5300 7850 5500
Wire Wire Line
	7850 5500 7900 5500
Wire Wire Line
	7850 5600 7850 5800
Wire Wire Line
	7850 5800 7750 5800
Wire Wire Line
	7750 5650 7750 5800
Wire Wire Line
	6250 5450 6400 5450
Text GLabel 6500 5450 2    39   Input ~ 0
D7VDD
Wire Wire Line
	6400 5450 6500 5450
Text GLabel 10900 5205 2    39   Input ~ 0
D7VDD
Wire Wire Line
	10900 5205 10800 5205
Connection ~ 10800 5400
Text GLabel 9000 5200 2    39   Input ~ 0
D7VDD
Connection ~ 8900 5400
Wire Wire Line
	4200 5650 4200 5850
Wire Wire Line
	3100 4100 3200 4100
$Comp
L power:PWR_FLAG #FLG01
U 1 1 655ADE53
P 2750 5200
F 0 "#FLG01" H 2750 5275 50  0001 C CNN
F 1 "PWR_FLAG" H 2600 5350 50  0000 C CNN
F 2 "" H 2750 5200 50  0001 C CNN
F 3 "~" H 2750 5200 50  0001 C CNN
	1    2750 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 6567C970
P 895 1700
F 0 "#PWR01" H 895 1450 50  0001 C CNN
F 1 "GND" H 900 1527 50  0000 C CNN
F 2 "" H 895 1700 50  0001 C CNN
F 3 "" H 895 1700 50  0001 C CNN
	1    895  1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6567E1EE
P 1095 1700
F 0 "#PWR03" H 1095 1450 50  0001 C CNN
F 1 "GND" H 1100 1527 50  0000 C CNN
F 2 "" H 1095 1700 50  0001 C CNN
F 3 "" H 1095 1700 50  0001 C CNN
	1    1095 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 6567F596
P 1645 1700
F 0 "#PWR07" H 1645 1450 50  0001 C CNN
F 1 "GND" H 1650 1527 50  0000 C CNN
F 2 "" H 1645 1700 50  0001 C CNN
F 3 "" H 1645 1700 50  0001 C CNN
	1    1645 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 65680B3E
P 3100 1650
F 0 "#PWR014" H 3100 1400 50  0001 C CNN
F 1 "GND" H 3105 1477 50  0000 C CNN
F 2 "" H 3100 1650 50  0001 C CNN
F 3 "" H 3100 1650 50  0001 C CNN
	1    3100 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 65683CE1
P 2500 1650
F 0 "#PWR09" H 2500 1400 50  0001 C CNN
F 1 "GND" H 2505 1477 50  0000 C CNN
F 2 "" H 2500 1650 50  0001 C CNN
F 3 "" H 2500 1650 50  0001 C CNN
	1    2500 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 65686D15
P 895 3100
F 0 "#PWR02" H 895 2850 50  0001 C CNN
F 1 "GND" H 900 2927 50  0000 C CNN
F 2 "" H 895 3100 50  0001 C CNN
F 3 "" H 895 3100 50  0001 C CNN
	1    895  3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 656895C6
P 1095 3100
F 0 "#PWR04" H 1095 2850 50  0001 C CNN
F 1 "GND" H 1100 2927 50  0000 C CNN
F 2 "" H 1095 3100 50  0001 C CNN
F 3 "" H 1095 3100 50  0001 C CNN
	1    1095 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1645 2945 1645 3100
$Comp
L power:GND #PWR08
U 1 1 6568AAA7
P 1645 3100
F 0 "#PWR08" H 1645 2850 50  0001 C CNN
F 1 "GND" H 1650 2927 50  0000 C CNN
F 2 "" H 1645 3100 50  0001 C CNN
F 3 "" H 1645 3100 50  0001 C CNN
	1    1645 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 6568C75C
P 2505 3050
F 0 "#PWR011" H 2505 2800 50  0001 C CNN
F 1 "GND" H 2510 2877 50  0000 C CNN
F 2 "" H 2505 3050 50  0001 C CNN
F 3 "" H 2505 3050 50  0001 C CNN
	1    2505 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 6568F0C1
P 3100 3050
F 0 "#PWR015" H 3100 2800 50  0001 C CNN
F 1 "GND" H 3105 2877 50  0000 C CNN
F 2 "" H 3100 3050 50  0001 C CNN
F 3 "" H 3100 3050 50  0001 C CNN
	1    3100 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 6569344C
P 2500 4450
F 0 "#PWR010" H 2500 4200 50  0001 C CNN
F 1 "GND" H 2505 4277 50  0000 C CNN
F 2 "" H 2500 4450 50  0001 C CNN
F 3 "" H 2500 4450 50  0001 C CNN
	1    2500 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 65694E27
P 3100 4445
F 0 "#PWR016" H 3100 4195 50  0001 C CNN
F 1 "GND" H 3105 4272 50  0000 C CNN
F 2 "" H 3100 4445 50  0001 C CNN
F 3 "" H 3100 4445 50  0001 C CNN
	1    3100 4445
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 6576C69A
P 4550 4100
F 0 "#PWR025" H 4550 3850 50  0001 C CNN
F 1 "GND" H 4555 3927 50  0000 C CNN
F 2 "" H 4550 4100 50  0001 C CNN
F 3 "" H 4550 4100 50  0001 C CNN
	1    4550 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 6576DD24
P 4450 4100
F 0 "#PWR022" H 4450 3850 50  0001 C CNN
F 1 "GND" H 4455 3927 50  0000 C CNN
F 2 "" H 4450 4100 50  0001 C CNN
F 3 "" H 4450 4100 50  0001 C CNN
	1    4450 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 6576EF5A
P 4550 2700
F 0 "#PWR024" H 4550 2450 50  0001 C CNN
F 1 "GND" H 4555 2527 50  0000 C CNN
F 2 "" H 4550 2700 50  0001 C CNN
F 3 "" H 4550 2700 50  0001 C CNN
	1    4550 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 6576FA89
P 4450 2700
F 0 "#PWR021" H 4450 2450 50  0001 C CNN
F 1 "GND" H 4455 2527 50  0000 C CNN
F 2 "" H 4450 2700 50  0001 C CNN
F 3 "" H 4450 2700 50  0001 C CNN
	1    4450 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 65770102
P 4550 1300
F 0 "#PWR023" H 4550 1050 50  0001 C CNN
F 1 "GND" H 4555 1127 50  0000 C CNN
F 2 "" H 4550 1300 50  0001 C CNN
F 3 "" H 4550 1300 50  0001 C CNN
	1    4550 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 65770AE7
P 4450 1300
F 0 "#PWR020" H 4450 1050 50  0001 C CNN
F 1 "GND" H 4455 1127 50  0000 C CNN
F 2 "" H 4450 1300 50  0001 C CNN
F 3 "" H 4450 1300 50  0001 C CNN
	1    4450 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR035
U 1 1 65770FB5
P 7000 5850
F 0 "#PWR035" H 7000 5600 50  0001 C CNN
F 1 "GND" H 7005 5677 50  0000 C CNN
F 2 "" H 7000 5850 50  0001 C CNN
F 3 "" H 7000 5850 50  0001 C CNN
	1    7000 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 657B388F
P 2750 5600
F 0 "#PWR017" H 2750 5350 50  0001 C CNN
F 1 "GND" H 2755 5427 50  0000 C CNN
F 2 "" H 2750 5600 50  0001 C CNN
F 3 "" H 2750 5600 50  0001 C CNN
	1    2750 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 657B4D53
P 3050 5600
F 0 "#PWR019" H 3050 5350 50  0001 C CNN
F 1 "GND" H 3055 5427 50  0000 C CNN
F 2 "" H 3050 5600 50  0001 C CNN
F 3 "" H 3050 5600 50  0001 C CNN
	1    3050 5600
	1    0    0    -1  
$EndComp
Text GLabel 4500 5200 2    39   Input ~ 0
AV3V6DD
Wire Wire Line
	4350 5200 4500 5200
Connection ~ 4350 5200
Wire Wire Line
	4650 3500 5550 3500
Wire Wire Line
	4650 3500 4650 4250
Wire Wire Line
	5550 3500 5550 3850
Wire Wire Line
	4600 3450 5600 3450
Wire Wire Line
	4600 3450 4600 3950
Wire Wire Line
	5600 3450 5600 3650
Connection ~ 5550 3850
Connection ~ 5600 3650
Wire Notes Line
	655  4400 2380 4395
Wire Notes Line
	625  3495 2350 3490
Wire Wire Line
	10900 6100 10900 6050
Wire Wire Line
	10700 6050 10500 6050
Connection ~ 10700 6050
Wire Wire Line
	10500 6050 10300 6050
Connection ~ 10500 6050
Wire Wire Line
	10300 6050 10100 6050
Connection ~ 10300 6050
Wire Wire Line
	10100 6050 9900 6050
Connection ~ 10100 6050
Wire Wire Line
	9900 6050 9700 6050
Connection ~ 9900 6050
Wire Wire Line
	9700 6050 9500 6050
Connection ~ 9700 6050
Wire Wire Line
	9500 6050 9300 6050
Connection ~ 9500 6050
Wire Wire Line
	10800 5205 10800 5400
$Comp
L Connector_Generic:Conn_01x12 J7
U 1 1 613B7209
P 10300 5650
F 0 "J7" V 10300 6255 50  0000 C CNN
F 1 "MCU interface" V 10450 5100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 10300 5650 50  0001 C CNN
F 3 "~" H 10300 5650 50  0001 C CNN
	1    10300 5650
	0    -1   1    0   
$EndComp
Wire Wire Line
	10400 5400 10400 5450
Wire Wire Line
	10500 5350 10500 5450
Wire Wire Line
	10400 5400 10800 5400
Wire Wire Line
	10500 5350 10900 5350
NoConn ~ 10600 5450
NoConn ~ 10700 5450
Wire Wire Line
	10800 5400 11000 5400
Wire Wire Line
	11000 5400 11000 6000
Connection ~ 10100 5150
Wire Wire Line
	10100 5150 10100 5450
Connection ~ 10000 5100
Wire Wire Line
	10000 5100 10000 5450
Connection ~ 9900 5050
Wire Wire Line
	9900 5050 9900 5450
Connection ~ 9800 5000
Wire Wire Line
	9800 5000 9800 5450
Wire Wire Line
	10200 5200 10200 5450
Wire Wire Line
	9650 5250 10300 5250
Connection ~ 10300 5250
Wire Wire Line
	10300 5250 10300 5450
Wire Wire Line
	10600 6000 10800 6000
Wire Wire Line
	3100 1550 3100 1650
Wire Wire Line
	3100 1300 2905 1300
Connection ~ 3100 1300
Wire Wire Line
	3200 1300 3100 1300
$Comp
L Device:C_Small C13
U 1 1 61163778
P 3100 1450
F 0 "C13" H 3100 1525 50  0000 L CNN
F 1 "100n" H 3005 1380 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3100 1450 50  0001 C CNN
F 3 "~" H 3100 1450 50  0001 C CNN
	1    3100 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1350 3100 1300
$Comp
L Device:C_Small C20
U 1 1 60E5B23E
P 4450 1100
F 0 "C20" H 4395 1175 50  0000 L CNN
F 1 "100n" H 4305 1035 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4450 1100 50  0001 C CNN
F 3 "~" H 4450 1100 50  0001 C CNN
	1    4450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2950 3100 3050
Wire Wire Line
	3100 2700 3200 2700
Connection ~ 3100 2700
Wire Wire Line
	3100 2750 3100 2700
$Comp
L Device:C_Small C14
U 1 1 61133E29
P 3100 2850
F 0 "C14" H 3120 2920 50  0000 L CNN
F 1 "100nF" H 3010 2760 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3100 2850 50  0001 C CNN
F 3 "~" H 3100 2850 50  0001 C CNN
	1    3100 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2700 3100 2700
$Comp
L Regulator_Linear:AMS1117-3.3 U10
U 1 1 62086427
P 5850 5450
F 0 "U10" H 5540 5360 50  0000 C CNN
F 1 "AMS1117-3.3" H 5850 5601 50  0000 C CNN
F 2 "DigiKey:SOT-223-4" H 5850 5650 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 5950 5200 50  0001 C CNN
	1    5850 5450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5850 5750 5850 5850
$Comp
L Connector_Generic:Conn_01x05 J5
U 1 1 625ACED3
P 1450 5100
F 0 "J5" H 1440 5410 50  0000 C CNN
F 1 "Panel Leds" H 1455 4795 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 1450 5100 50  0001 C CNN
F 3 "~" H 1450 5100 50  0001 C CNN
	1    1450 5100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1650 5100 1700 5100
Wire Wire Line
	1650 5200 1700 5200
Wire Wire Line
	1650 5000 1700 5000
$Comp
L power:GND #PWR0101
U 1 1 62095C02
P 7150 5850
F 0 "#PWR0101" H 7150 5600 50  0001 C CNN
F 1 "GND" H 7155 5677 50  0000 C CNN
F 2 "" H 7150 5850 50  0001 C CNN
F 3 "" H 7150 5850 50  0001 C CNN
	1    7150 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 62097D05
P 7450 5850
F 0 "#PWR0102" H 7450 5600 50  0001 C CNN
F 1 "GND" H 7455 5677 50  0000 C CNN
F 2 "" H 7450 5850 50  0001 C CNN
F 3 "" H 7450 5850 50  0001 C CNN
	1    7450 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 620991FE
P 7600 5850
F 0 "#PWR0103" H 7600 5600 50  0001 C CNN
F 1 "GND" H 7605 5677 50  0000 C CNN
F 2 "" H 7600 5850 50  0001 C CNN
F 3 "" H 7600 5850 50  0001 C CNN
	1    7600 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 6209F598
P 3250 5600
F 0 "#PWR0106" H 3250 5350 50  0001 C CNN
F 1 "GND" H 3255 5427 50  0000 C CNN
F 2 "" H 3250 5600 50  0001 C CNN
F 3 "" H 3250 5600 50  0001 C CNN
	1    3250 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 620A3099
P 3750 5850
F 0 "#PWR0107" H 3750 5600 50  0001 C CNN
F 1 "GND" H 3755 5677 50  0000 C CNN
F 2 "" H 3750 5850 50  0001 C CNN
F 3 "" H 3750 5850 50  0001 C CNN
	1    3750 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 620A4449
P 4200 5850
F 0 "#PWR0108" H 4200 5600 50  0001 C CNN
F 1 "GND" H 4205 5677 50  0000 C CNN
F 2 "" H 4200 5850 50  0001 C CNN
F 3 "" H 4200 5850 50  0001 C CNN
	1    4200 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 6218DCE8
P 4350 5850
F 0 "#PWR026" H 4350 5600 50  0001 C CNN
F 1 "GND" H 4355 5677 50  0000 C CNN
F 2 "" H 4350 5850 50  0001 C CNN
F 3 "" H 4350 5850 50  0001 C CNN
	1    4350 5850
	1    0    0    -1  
$EndComp
Text Notes 7950 6200 0    39   ~ 0
Note: Use R43 and omit C31\nwhen using LT1761
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 62712736
P 6150 6850
F 0 "H3" H 6250 6853 50  0000 L CNN
F 1 "MH" H 6250 6808 50  0001 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 6150 6850 50  0001 C CNN
F 3 "~" H 6150 6850 50  0001 C CNN
	1    6150 6850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 62712AB1
P 5795 6850
F 0 "H1" H 5895 6853 50  0000 L CNN
F 1 "MH" H 5895 6808 50  0001 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 5795 6850 50  0001 C CNN
F 3 "~" H 5795 6850 50  0001 C CNN
	1    5795 6850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 62714151
P 5800 7100
F 0 "H2" H 5900 7103 50  0000 L CNN
F 1 "MH" H 5900 7058 50  0001 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 5800 7100 50  0001 C CNN
F 3 "~" H 5800 7100 50  0001 C CNN
	1    5800 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 627153A4
P 6150 7100
F 0 "H4" H 6250 7103 50  0000 L CNN
F 1 "MH" H 6250 7058 50  0001 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 6150 7100 50  0001 C CNN
F 3 "~" H 6150 7100 50  0001 C CNN
	1    6150 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 6950 6350 6950
Wire Wire Line
	6350 6950 6350 7200
Wire Wire Line
	6150 7200 6350 7200
Connection ~ 6350 7200
Wire Wire Line
	6350 7200 6350 7300
Wire Wire Line
	5795 6950 5950 6950
Wire Wire Line
	5950 6950 5950 7200
Wire Wire Line
	5800 7200 5950 7200
Connection ~ 5950 7200
Wire Wire Line
	5950 7200 5950 7300
$Comp
L power:GND #PWR0109
U 1 1 628E8C2C
P 5950 7300
F 0 "#PWR0109" H 5950 7050 50  0001 C CNN
F 1 "GND" H 5955 7127 50  0000 C CNN
F 2 "" H 5950 7300 50  0001 C CNN
F 3 "" H 5950 7300 50  0001 C CNN
	1    5950 7300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H5
U 1 1 628EA6B7
P 5350 6850
F 0 "H5" H 5450 6853 50  0000 L CNN
F 1 "MH" H 5450 6808 50  0001 L CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 5350 6850 50  0001 C CNN
F 3 "~" H 5350 6850 50  0001 C CNN
	1    5350 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 6950 5550 6950
Connection ~ 5795 6950
$Comp
L Mechanical:MountingHole_Pad H7
U 1 1 6217C5E1
P 4905 6850
F 0 "H7" H 5005 6853 50  0000 L CNN
F 1 "MH" H 5005 6808 50  0001 L CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 4905 6850 50  0001 C CNN
F 3 "~" H 4905 6850 50  0001 C CNN
	1    4905 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4905 6950 5350 6950
Connection ~ 5350 6950
$Comp
L Mechanical:MountingHole_Pad H8
U 1 1 621CB309
P 4900 7100
F 0 "H8" H 5000 7103 50  0000 L CNN
F 1 "MH" H 5000 7058 50  0001 L CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 4900 7100 50  0001 C CNN
F 3 "~" H 4900 7100 50  0001 C CNN
	1    4900 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H9
U 1 1 62218FAD
P 4460 6850
F 0 "H9" H 4560 6853 50  0000 L CNN
F 1 "MH" H 4560 6808 50  0001 L CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 4460 6850 50  0001 C CNN
F 3 "~" H 4460 6850 50  0001 C CNN
	1    4460 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4460 6950 4905 6950
Connection ~ 4905 6950
$Comp
L Mechanical:MountingHole_Pad H10
U 1 1 62266F8C
P 4455 7100
F 0 "H10" H 4555 7103 50  0000 L CNN
F 1 "MH" H 4555 7058 50  0001 L CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 4455 7100 50  0001 C CNN
F 3 "~" H 4455 7100 50  0001 C CNN
	1    4455 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4455 7200 4900 7200
Connection ~ 4900 7200
Wire Wire Line
	4900 7200 5345 7200
$Comp
L Mechanical:MountingHole_Pad H6
U 1 1 623097CD
P 5345 7100
F 0 "H6" H 5445 7103 50  0000 L CNN
F 1 "MH" H 5445 7058 50  0001 L CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 5345 7100 50  0001 C CNN
F 3 "~" H 5345 7100 50  0001 C CNN
	1    5345 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5345 7200 5550 7200
Wire Wire Line
	5550 7200 5550 6950
Connection ~ 5345 7200
Connection ~ 5550 6950
Wire Wire Line
	5550 6950 5795 6950
$Comp
L power:GND #PWR0111
U 1 1 6210C635
P 8900 5850
F 0 "#PWR0111" H 8900 5600 50  0001 C CNN
F 1 "GND" H 8904 5695 50  0000 C CNN
F 2 "" H 8900 5850 50  0001 C CNN
F 3 "" H 8900 5850 50  0001 C CNN
	1    8900 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 62110903
P 5300 5850
F 0 "#PWR0114" H 5300 5600 50  0001 C CNN
F 1 "GND" H 5304 5695 50  0000 C CNN
F 2 "" H 5300 5850 50  0001 C CNN
F 3 "" H 5300 5850 50  0001 C CNN
	1    5300 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 62114241
P 5450 5850
F 0 "#PWR0115" H 5450 5600 50  0001 C CNN
F 1 "GND" H 5454 5695 50  0000 C CNN
F 2 "" H 5450 5850 50  0001 C CNN
F 3 "" H 5450 5850 50  0001 C CNN
	1    5450 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 62166D1F
P 6250 5850
F 0 "#PWR0117" H 6250 5600 50  0001 C CNN
F 1 "GND" H 6254 5695 50  0000 C CNN
F 2 "" H 6250 5850 50  0001 C CNN
F 3 "" H 6250 5850 50  0001 C CNN
	1    6250 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 62168601
P 6400 5850
F 0 "#PWR0118" H 6400 5600 50  0001 C CNN
F 1 "GND" H 6404 5695 50  0000 C CNN
F 2 "" H 6400 5850 50  0001 C CNN
F 3 "" H 6400 5850 50  0001 C CNN
	1    6400 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 621B8DE3
P 5850 5850
F 0 "#PWR0120" H 5850 5600 50  0001 C CNN
F 1 "GND" H 5854 5695 50  0000 C CNN
F 2 "" H 5850 5850 50  0001 C CNN
F 3 "" H 5850 5850 50  0001 C CNN
	1    5850 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 621C0428
P 6350 7300
F 0 "#PWR0124" H 6350 7050 50  0001 C CNN
F 1 "GND" H 6354 7145 50  0000 C CNN
F 2 "" H 6350 7300 50  0001 C CNN
F 3 "" H 6350 7300 50  0001 C CNN
	1    6350 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 62211760
P 11100 5450
F 0 "#PWR0125" H 11100 5200 50  0001 C CNN
F 1 "GND" H 11104 5295 50  0000 C CNN
F 2 "" H 11100 5450 50  0001 C CNN
F 3 "" H 11100 5450 50  0001 C CNN
	1    11100 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	11100 5350 11100 5450
$Comp
L power:GND #PWR0126
U 1 1 6226313A
P 10900 6100
F 0 "#PWR0126" H 10900 5850 50  0001 C CNN
F 1 "GND" H 10904 5945 50  0000 C CNN
F 2 "" H 10900 6100 50  0001 C CNN
F 3 "" H 10900 6100 50  0001 C CNN
	1    10900 6100
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 623536AB
P 4550 5750
F 0 "#FLG02" H 4550 5825 50  0001 C CNN
F 1 "PWR_FLAG" H 4655 5880 50  0000 C CNN
F 2 "" H 4550 5750 50  0001 C CNN
F 3 "~" H 4550 5750 50  0001 C CNN
	1    4550 5750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 624491F2
P 4550 5850
F 0 "#PWR0127" H 4550 5600 50  0001 C CNN
F 1 "GND" H 4554 5695 50  0000 C CNN
F 2 "" H 4550 5850 50  0001 C CNN
F 3 "" H 4550 5850 50  0001 C CNN
	1    4550 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 6244B515
P 1200 2350
F 0 "#PWR0128" H 1200 2100 50  0001 C CNN
F 1 "GND" H 1205 2177 50  0000 C CNN
F 2 "" H 1200 2350 50  0001 C CNN
F 3 "" H 1200 2350 50  0001 C CNN
	1    1200 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0129
U 1 1 624EE3E5
P 1195 950
F 0 "#PWR0129" H 1195 700 50  0001 C CNN
F 1 "GND" H 1200 777 50  0000 C CNN
F 2 "" H 1195 950 50  0001 C CNN
F 3 "" H 1195 950 50  0001 C CNN
	1    1195 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 5750 4550 5850
Wire Wire Line
	5000 5450 5050 5450
Wire Wire Line
	10100 6050 10100 6100
Wire Wire Line
	9900 6050 9900 6100
Wire Wire Line
	9700 6050 9700 6100
Wire Wire Line
	9500 6050 9500 6100
Wire Wire Line
	10700 6100 10700 6050
Wire Wire Line
	10600 6100 10600 6000
Wire Wire Line
	10500 6050 10500 6100
Wire Wire Line
	10300 6050 10300 6100
Wire Wire Line
	9300 6050 9300 6100
$Comp
L Connector:Conn_01x16_Female J6
U 1 1 626A4827
P 10000 6300
F 0 "J6" V 9960 7110 50  0000 C CNN
F 1 "FFC MCU Interface" V 10100 5850 50  0000 C CNN
F 2 "Connector_FFC:TE_1-84952-6_1x16-1MP_P1.0mm_Horizontal" H 10000 6300 50  0001 C CNN
F 3 "~" H 10000 6300 50  0001 C CNN
	1    10000 6300
	0    -1   1    0   
$EndComp
Wire Wire Line
	10700 6050 10900 6050
Wire Wire Line
	10800 6100 10800 6000
Connection ~ 10800 6000
Wire Wire Line
	10800 6000 11000 6000
Wire Wire Line
	5450 5450 5550 5450
Wire Wire Line
	6150 5450 6250 5450
Connection ~ 5000 5450
Wire Wire Line
	5000 5200 5000 5450
Text GLabel 10350 5250 2    39   Input ~ 0
~RDYB
Wire Wire Line
	10300 5250 10350 5250
Text GLabel 10350 5050 2    39   Input ~ 0
DOUT
Wire Wire Line
	9900 5050 10350 5050
Text GLabel 10350 5150 2    39   Input ~ 0
~CS_A
Wire Wire Line
	10350 5150 10100 5150
Text GLabel 10350 4950 2    39   Input ~ 0
SCLK
Wire Wire Line
	10000 4950 10350 4950
Wire Wire Line
	10000 4950 10000 5100
Text GLabel 10350 4850 2    39   Input ~ 0
DIN
Wire Wire Line
	10350 4850 9800 4850
Wire Wire Line
	9800 4850 9800 5000
$Comp
L power:GND #PWR031
U 1 1 646FFB81
P 8750 5850
F 0 "#PWR031" H 8750 5600 50  0001 C CNN
F 1 "GND" H 8754 5695 50  0000 C CNN
F 2 "" H 8750 5850 50  0001 C CNN
F 3 "" H 8750 5850 50  0001 C CNN
	1    8750 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 64700724
P 8300 5850
F 0 "#PWR027" H 8300 5600 50  0001 C CNN
F 1 "GND" H 8304 5695 50  0000 C CNN
F 2 "" H 8300 5850 50  0001 C CNN
F 3 "" H 8300 5850 50  0001 C CNN
	1    8300 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR033
U 1 1 646CA587
P 9300 2400
F 0 "#PWR033" H 9300 2150 50  0001 C CNN
F 1 "GND" H 9304 2245 50  0000 C CNN
F 2 "" H 9300 2400 50  0001 C CNN
F 3 "" H 9300 2400 50  0001 C CNN
	1    9300 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR036
U 1 1 646C862C
P 9500 2400
F 0 "#PWR036" H 9500 2150 50  0001 C CNN
F 1 "GND" H 9504 2245 50  0000 C CNN
F 2 "" H 9500 2400 50  0001 C CNN
F 3 "" H 9500 2400 50  0001 C CNN
	1    9500 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 1550 10450 1550
Wire Wire Line
	9950 1450 10450 1450
Wire Wire Line
	9950 1350 10450 1350
Wire Wire Line
	9950 1650 10450 1650
Wire Wire Line
	9950 1750 10450 1750
Text GLabel 10450 1750 2    39   Input ~ 0
~RDYB
Text GLabel 10450 1650 2    39   Input ~ 0
DOUT
Text GLabel 10450 1550 2    39   Input ~ 0
DIN
Text GLabel 10450 1450 2    39   Input ~ 0
SCLK
Text GLabel 10450 1350 2    39   Input ~ 0
~CS_A
$Comp
L My-Analog:MAX11270 U8
U 1 1 607364BB
P 9200 1450
F 0 "U8" H 8640 990 50  0000 R CNN
F 1 "MAX11270" H 9380 1505 50  0000 R CNN
F 2 "DigiKey:TSSOP-24_W4.40mm" H 9020 1460 50  0001 C CNN
F 3 "" H 9020 1460 50  0001 C CNN
	1    9200 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10095 600  10300 600 
Connection ~ 10095 600 
Wire Wire Line
	9950 600  10095 600 
Connection ~ 9950 600 
Wire Wire Line
	9700 600  9950 600 
Wire Wire Line
	9000 800  9000 900 
Wire Wire Line
	9700 900  9700 600 
Wire Wire Line
	9600 900  9600 800 
$Comp
L power:GND #PWR0122
U 1 1 621BCA02
P 9700 2400
F 0 "#PWR0122" H 9700 2150 50  0001 C CNN
F 1 "GND" H 9704 2245 50  0000 C CNN
F 2 "" H 9700 2400 50  0001 C CNN
F 3 "" H 9700 2400 50  0001 C CNN
	1    9700 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 6210F010
P 10100 900
F 0 "#PWR0113" H 10100 650 50  0001 C CNN
F 1 "GND" H 10104 745 50  0000 C CNN
F 2 "" H 10100 900 50  0001 C CNN
F 3 "" H 10100 900 50  0001 C CNN
	1    10100 900 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 6210DC11
P 9950 900
F 0 "#PWR0112" H 9950 650 50  0001 C CNN
F 1 "GND" H 9954 745 50  0000 C CNN
F 2 "" H 9950 900 50  0001 C CNN
F 3 "" H 9950 900 50  0001 C CNN
	1    9950 900 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 6297E5E2
P 8650 900
F 0 "#PWR0110" H 8650 650 50  0001 C CNN
F 1 "GND" H 8555 735 50  0000 C CNN
F 2 "" H 8650 900 50  0001 C CNN
F 3 "" H 8650 900 50  0001 C CNN
	1    8650 900 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR048
U 1 1 65765B35
P 9150 900
F 0 "#PWR048" H 9150 650 50  0001 C CNN
F 1 "GND" H 9315 820 50  0000 C CNN
F 2 "" H 9150 900 50  0001 C CNN
F 3 "" H 9150 900 50  0001 C CNN
	1    9150 900 
	1    0    0    -1  
$EndComp
Connection ~ 9000 600 
Wire Wire Line
	9150 600  9000 600 
Wire Wire Line
	9150 650  9150 600 
Wire Wire Line
	9150 850  9150 900 
$Comp
L Device:C_Small C37
U 1 1 649FB343
P 9150 750
F 0 "C37" H 9165 815 50  0000 L CNN
F 1 "100n" H 9155 655 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9150 750 50  0001 C CNN
F 3 "~" H 9150 750 50  0001 C CNN
	1    9150 750 
	1    0    0    -1  
$EndComp
Connection ~ 9000 800 
Wire Wire Line
	9000 600  9000 800 
Wire Wire Line
	8900 600  9000 600 
Text GLabel 8900 600  0    39   Input ~ 0
AV3V6DD
Connection ~ 9700 600 
Connection ~ 10300 600 
Wire Wire Line
	7750 1400 7850 1400
Wire Wire Line
	8150 1400 8280 1400
Wire Wire Line
	8150 1600 8280 1600
Wire Wire Line
	7850 1600 7650 1600
Connection ~ 8150 1600
Wire Wire Line
	8050 1600 8150 1600
Connection ~ 8150 1400
Wire Wire Line
	8050 1400 8150 1400
$Comp
L Device:R_Small R35
U 1 1 613254F1
P 7950 1600
F 0 "R35" V 8010 1605 50  0000 C CNN
F 1 "1K" V 7880 1590 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7950 1600 50  0001 C CNN
F 3 "~" H 7950 1600 50  0001 C CNN
	1    7950 1600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R34
U 1 1 61324576
P 7950 1400
F 0 "R34" V 8010 1405 50  0000 C CNN
F 1 "1K" V 7880 1395 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7950 1400 50  0001 C CNN
F 3 "~" H 7950 1400 50  0001 C CNN
	1    7950 1400
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C32
U 1 1 61321FD2
P 8150 1500
F 0 "C32" H 8085 1665 50  0000 L CNN
F 1 "100n" H 8055 1445 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8150 1500 50  0001 C CNN
F 3 "~" H 8150 1500 50  0001 C CNN
	1    8150 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 800  9000 800 
Wire Wire Line
	8650 900  8900 900 
Wire Wire Line
	9950 1150 10300 1150
Wire Wire Line
	9950 1250 10450 1250
Wire Wire Line
	9950 1850 9950 2150
Wire Wire Line
	9950 2150 9700 2150
Wire Wire Line
	9500 2150 9500 2400
Connection ~ 9500 2150
Wire Wire Line
	9400 2150 9500 2150
Wire Wire Line
	9400 2100 9400 2150
Wire Wire Line
	9700 2150 9700 2400
Connection ~ 9700 2150
Wire Wire Line
	9600 2150 9700 2150
Wire Wire Line
	9600 2100 9600 2150
Wire Wire Line
	9700 2100 9700 2150
Wire Wire Line
	9500 2100 9500 2150
Wire Wire Line
	9300 2100 9300 2150
Wire Wire Line
	9100 2100 9100 2150
$Comp
L Device:C_Small C36
U 1 1 60DA5715
P 9100 2250
F 0 "C36" H 9050 2325 50  0000 L CNN
F 1 "100n" H 9000 2185 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9100 2250 50  0001 C CNN
F 3 "~" H 9100 2250 50  0001 C CNN
	1    9100 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 2350 9200 2100
Wire Wire Line
	9300 2350 9300 2400
Wire Wire Line
	9100 2350 9200 2350
$Comp
L Device:C_Small C39
U 1 1 60D88059
P 9300 2250
F 0 "C39" H 9250 2325 50  0000 L CNN
F 1 "1u" H 9305 2160 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9300 2250 50  0001 C CNN
F 3 "~" H 9300 2250 50  0001 C CNN
	1    9300 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 850  10450 1250
Wire Wire Line
	10095 650  10095 600 
Wire Wire Line
	10100 900  10095 850 
$Comp
L Device:C_Small C35
U 1 1 60A5FC3A
P 9950 750
F 0 "C35" H 9895 840 50  0000 L CNN
F 1 "100n" H 9855 665 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9950 750 50  0001 C CNN
F 3 "~" H 9950 750 50  0001 C CNN
	1    9950 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9645 600  9700 600 
Text GLabel 9645 600  0    39   Input ~ 0
D3V3DD
Wire Wire Line
	10450 600  10300 600 
Wire Wire Line
	10450 650  10450 600 
Wire Wire Line
	10300 600  10300 650 
$Comp
L Device:R_Small R41
U 1 1 60700BD9
P 10300 750
F 0 "R41" V 10360 910 50  0000 C CNN
F 1 "10K" V 10370 725 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 10300 750 50  0001 C CNN
F 3 "~" H 10300 750 50  0001 C CNN
	1    10300 750 
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R42
U 1 1 606FF8CC
P 10450 750
F 0 "R42" V 10510 905 50  0000 C CNN
F 1 "10K" V 10515 735 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 10450 750 50  0001 C CNN
F 3 "~" H 10450 750 50  0001 C CNN
	1    10450 750 
	-1   0    0    1   
$EndComp
Wire Wire Line
	10300 850  10300 1150
Wire Wire Line
	9950 650  9950 600 
$Comp
L Device:CP_Small C38
U 1 1 60584BDC
P 10095 750
F 0 "C38" H 10050 840 50  0000 L CNN
F 1 "10u" H 10050 665 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10095 750 50  0001 C CNN
F 3 "~" H 10095 750 50  0001 C CNN
	1    10095 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 900  9950 850 
Wire Wire Line
	9650 5250 9650 5750
Wire Wire Line
	9650 5750 10400 5750
Wire Wire Line
	10400 5750 10400 6100
Wire Wire Line
	10200 6100 10200 5800
Wire Wire Line
	10200 5800 9600 5800
Wire Wire Line
	9600 5800 9600 5200
Wire Wire Line
	9600 5200 10200 5200
Wire Wire Line
	10000 6100 10000 5850
Wire Wire Line
	10000 5850 9550 5850
Wire Wire Line
	9550 5850 9550 5150
Wire Wire Line
	9550 5150 10100 5150
Wire Wire Line
	9500 5100 9500 5900
Wire Wire Line
	9500 5900 9800 5900
Wire Wire Line
	9800 5900 9800 6100
Wire Wire Line
	9500 5100 10000 5100
Wire Wire Line
	9450 5050 9450 5950
Wire Wire Line
	9450 5950 9600 5950
Wire Wire Line
	9600 5950 9600 6100
Wire Wire Line
	9450 5050 9900 5050
Wire Wire Line
	9400 5000 9800 5000
Wire Wire Line
	9000 5200 8900 5200
Wire Wire Line
	8900 5200 8900 5400
Wire Wire Line
	7000 5200 7000 5250
Wire Wire Line
	6900 5250 7000 5250
Connection ~ 7000 5250
Wire Wire Line
	7000 5250 7000 5400
Wire Wire Line
	2650 5300 2750 5300
Wire Wire Line
	8150 5800 8150 5900
Wire Wire Line
	8150 5800 8300 5800
Connection ~ 8150 5800
Connection ~ 8300 5800
Wire Wire Line
	9400 5000 9400 6100
$Comp
L power:GND #PWR034
U 1 1 652EB74F
P 9300 4550
F 0 "#PWR034" H 9300 4300 50  0001 C CNN
F 1 "GND" H 9304 4395 50  0000 C CNN
F 2 "" H 9300 4550 50  0001 C CNN
F 3 "" H 9300 4550 50  0001 C CNN
	1    9300 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR037
U 1 1 652EC3A7
P 9500 4550
F 0 "#PWR037" H 9500 4300 50  0001 C CNN
F 1 "GND" H 9504 4395 50  0000 C CNN
F 2 "" H 9500 4550 50  0001 C CNN
F 3 "" H 9500 4550 50  0001 C CNN
	1    9500 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 3700 10450 3700
Wire Wire Line
	9950 3600 10450 3600
Wire Wire Line
	9950 3500 10450 3500
Wire Wire Line
	9950 3800 10450 3800
Wire Wire Line
	9950 3900 10450 3900
Text GLabel 10450 3900 2    39   Input ~ 0
~RDYB
Text GLabel 10450 3800 2    39   Input ~ 0
DOUT
Text GLabel 10450 3700 2    39   Input ~ 0
DIN
Text GLabel 10450 3600 2    39   Input ~ 0
SCLK
Text GLabel 10450 3500 2    39   Input ~ 0
~CS_B
$Comp
L My-Analog:MAX11270 U9
U 1 1 652EC3BB
P 9200 3600
F 0 "U9" H 8640 3140 50  0000 R CNN
F 1 "MAX11270" H 9380 3655 50  0000 R CNN
F 2 "DigiKey:TSSOP-24_W4.40mm" H 9020 3610 50  0001 C CNN
F 3 "" H 9020 3610 50  0001 C CNN
	1    9200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10095 2750 10300 2750
Connection ~ 10095 2750
Wire Wire Line
	9950 2750 10095 2750
Connection ~ 9950 2750
Wire Wire Line
	9700 2750 9950 2750
Wire Wire Line
	9000 2950 9000 3050
Wire Wire Line
	9700 3050 9700 2750
Wire Wire Line
	9600 3050 9600 2950
$Comp
L power:GND #PWR038
U 1 1 652EC3CD
P 9700 4550
F 0 "#PWR038" H 9700 4300 50  0001 C CNN
F 1 "GND" H 9704 4395 50  0000 C CNN
F 2 "" H 9700 4550 50  0001 C CNN
F 3 "" H 9700 4550 50  0001 C CNN
	1    9700 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR040
U 1 1 652EC3D7
P 10100 3050
F 0 "#PWR040" H 10100 2800 50  0001 C CNN
F 1 "GND" H 10104 2895 50  0000 C CNN
F 2 "" H 10100 3050 50  0001 C CNN
F 3 "" H 10100 3050 50  0001 C CNN
	1    10100 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR039
U 1 1 652EC3E1
P 9950 3050
F 0 "#PWR039" H 9950 2800 50  0001 C CNN
F 1 "GND" H 9954 2895 50  0000 C CNN
F 2 "" H 9950 3050 50  0001 C CNN
F 3 "" H 9950 3050 50  0001 C CNN
	1    9950 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 652EC3EB
P 8650 3050
F 0 "#PWR030" H 8650 2800 50  0001 C CNN
F 1 "GND" H 8555 2885 50  0000 C CNN
F 2 "" H 8650 3050 50  0001 C CNN
F 3 "" H 8650 3050 50  0001 C CNN
	1    8650 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 652EC3F5
P 9150 3050
F 0 "#PWR032" H 9150 2800 50  0001 C CNN
F 1 "GND" H 9315 2970 50  0000 C CNN
F 2 "" H 9150 3050 50  0001 C CNN
F 3 "" H 9150 3050 50  0001 C CNN
	1    9150 3050
	1    0    0    -1  
$EndComp
Connection ~ 9000 2750
Wire Wire Line
	9150 2750 9000 2750
Wire Wire Line
	9150 2800 9150 2750
Wire Wire Line
	9150 3000 9150 3050
$Comp
L Device:C_Small C43
U 1 1 652EC403
P 9150 2900
F 0 "C43" H 9165 2965 50  0000 L CNN
F 1 "100n" H 9155 2805 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9150 2900 50  0001 C CNN
F 3 "~" H 9150 2900 50  0001 C CNN
	1    9150 2900
	1    0    0    -1  
$EndComp
Connection ~ 9000 2950
Wire Wire Line
	9000 2750 9000 2950
Wire Wire Line
	8900 2750 9000 2750
Text GLabel 8900 2750 0    39   Input ~ 0
AV3V6DD
Text GLabel 1700 5200 2    39   Input ~ 0
D3V3DD
Connection ~ 9700 2750
Connection ~ 10300 2750
Wire Wire Line
	7750 3550 7850 3550
Wire Wire Line
	8150 3550 8280 3550
Wire Wire Line
	8150 3750 8280 3750
Wire Wire Line
	7850 3750 7650 3750
Connection ~ 8150 3750
Wire Wire Line
	8050 3750 8150 3750
Connection ~ 8150 3550
Wire Wire Line
	8050 3550 8150 3550
$Comp
L Device:R_Small R54
U 1 1 652EC41C
P 7950 3750
F 0 "R54" V 8010 3755 50  0000 C CNN
F 1 "1K" V 7880 3740 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7950 3750 50  0001 C CNN
F 3 "~" H 7950 3750 50  0001 C CNN
	1    7950 3750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R53
U 1 1 652EC426
P 7950 3550
F 0 "R53" V 8010 3555 50  0000 C CNN
F 1 "1K" V 7880 3545 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7950 3550 50  0001 C CNN
F 3 "~" H 7950 3550 50  0001 C CNN
	1    7950 3550
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C30
U 1 1 652EC430
P 8150 3650
F 0 "C30" H 8085 3815 50  0000 L CNN
F 1 "100n" H 8055 3595 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8150 3650 50  0001 C CNN
F 3 "~" H 8150 3650 50  0001 C CNN
	1    8150 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 2950 9000 2950
Wire Wire Line
	8650 3050 8900 3050
Wire Wire Line
	9950 3300 10300 3300
Wire Wire Line
	9950 3400 10450 3400
Wire Wire Line
	9950 4000 9950 4300
Wire Wire Line
	9950 4300 9700 4300
Wire Wire Line
	9500 4300 9500 4550
Connection ~ 9500 4300
Wire Wire Line
	9400 4300 9500 4300
Wire Wire Line
	9400 4250 9400 4300
Wire Wire Line
	9700 4300 9700 4550
Connection ~ 9700 4300
Wire Wire Line
	9600 4300 9700 4300
Wire Wire Line
	9600 4250 9600 4300
Wire Wire Line
	9700 4250 9700 4300
Wire Wire Line
	9500 4250 9500 4300
Wire Wire Line
	9300 4250 9300 4300
Wire Wire Line
	9100 4250 9100 4300
$Comp
L Device:C_Small C42
U 1 1 652EC44C
P 9100 4400
F 0 "C42" H 9050 4475 50  0000 L CNN
F 1 "100n" H 9000 4335 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9100 4400 50  0001 C CNN
F 3 "~" H 9100 4400 50  0001 C CNN
	1    9100 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4500 9200 4250
Wire Wire Line
	9300 4500 9300 4550
Wire Wire Line
	9100 4500 9200 4500
$Comp
L Device:C_Small C46
U 1 1 652EC459
P 9300 4400
F 0 "C46" H 9250 4475 50  0000 L CNN
F 1 "1u" H 9305 4310 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9300 4400 50  0001 C CNN
F 3 "~" H 9300 4400 50  0001 C CNN
	1    9300 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 3000 10450 3400
Wire Wire Line
	10095 2800 10095 2750
Wire Wire Line
	10100 3050 10095 3000
$Comp
L Device:C_Small C47
U 1 1 652EC466
P 9950 2900
F 0 "C47" H 9895 2990 50  0000 L CNN
F 1 "100n" H 9855 2815 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9950 2900 50  0001 C CNN
F 3 "~" H 9950 2900 50  0001 C CNN
	1    9950 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9645 2750 9700 2750
Text GLabel 9645 2750 0    39   Input ~ 0
D3V3DD
Wire Wire Line
	10450 2750 10300 2750
Wire Wire Line
	10450 2800 10450 2750
Wire Wire Line
	10300 2750 10300 2800
$Comp
L Device:R_Small R59
U 1 1 652EC475
P 10300 2900
F 0 "R59" V 10360 3060 50  0000 C CNN
F 1 "10K" V 10370 2875 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 10300 2900 50  0001 C CNN
F 3 "~" H 10300 2900 50  0001 C CNN
	1    10300 2900
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R60
U 1 1 652EC47F
P 10450 2900
F 0 "R60" V 10510 3055 50  0000 C CNN
F 1 "10K" V 10515 2885 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 10450 2900 50  0001 C CNN
F 3 "~" H 10450 2900 50  0001 C CNN
	1    10450 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	10300 3000 10300 3300
Wire Wire Line
	9950 2800 9950 2750
$Comp
L Device:CP_Small C48
U 1 1 652EC48B
P 10095 2900
F 0 "C48" H 10050 2990 50  0000 L CNN
F 1 "10u" H 10050 2815 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10095 2900 50  0001 C CNN
F 3 "~" H 10095 2900 50  0001 C CNN
	1    10095 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 3050 9950 3000
Wire Wire Line
	7750 1400 7750 850 
Wire Wire Line
	5600 850  7750 850 
Wire Wire Line
	7650 1050 7650 1600
Wire Wire Line
	5550 1050 7650 1050
$Comp
L User_des:AC45S-Q U4
U 1 1 654355AE
P 6600 2850
F 0 "U4" V 6646 2420 50  0000 R CNN
F 1 "AC45S-Q" V 6555 2420 50  0000 R CNN
F 2 "Package_SMD:SOP-8_W9.4mm" H 6600 2350 50  0001 C CIN
F 3 "http://www.ixysic.com/home/pdfs.nsf/www/LCC110.pdf/$file/LCC110.pdf" H 6600 2850 50  0001 L CNN
	1    6600 2850
	0    -1   -1   0   
$EndComp
$Comp
L User_des:AC45S-Q U6
U 1 1 6543D69B
P 6600 4250
F 0 "U6" V 6646 3820 50  0000 R CNN
F 1 "AC45S-Q" V 6555 3820 50  0000 R CNN
F 2 "Package_SMD:SOP-8_W9.4mm" H 6600 3750 50  0001 C CIN
F 3 "http://www.ixysic.com/home/pdfs.nsf/www/LCC110.pdf/$file/LCC110.pdf" H 6600 4250 50  0001 L CNN
	1    6600 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6300 2450 6300 2550
Wire Wire Line
	5550 2450 6300 2450
Wire Wire Line
	6700 2250 6700 2550
Wire Wire Line
	5600 2250 6700 2250
Wire Wire Line
	6500 2550 6500 2450
Wire Wire Line
	6500 2450 7650 2450
Wire Wire Line
	7650 2450 7650 3750
Wire Wire Line
	6900 2550 6900 2250
Wire Wire Line
	6900 2250 7750 2250
Wire Wire Line
	7750 2250 7750 3550
Wire Wire Line
	6300 3850 6300 3950
Wire Wire Line
	5550 3850 6300 3850
Wire Wire Line
	6700 3650 6700 3950
Wire Wire Line
	5600 3650 6700 3650
Wire Wire Line
	6500 3950 6500 3850
Wire Wire Line
	6500 3850 7650 3850
Wire Wire Line
	7650 3850 7650 3750
Connection ~ 7650 3750
Wire Wire Line
	6900 3950 6900 3650
Connection ~ 7750 3550
$Comp
L Device:R_Small R47
U 1 1 65683F3E
P 6500 3350
F 0 "R47" V 6560 3355 50  0000 C CNN
F 1 "270" V 6430 3345 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6500 3350 50  0001 C CNN
F 3 "~" H 6500 3350 50  0001 C CNN
	1    6500 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R49
U 1 1 656848B2
P 6900 3350
F 0 "R49" V 6960 3355 50  0000 C CNN
F 1 "270" V 6830 3345 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6900 3350 50  0001 C CNN
F 3 "~" H 6900 3350 50  0001 C CNN
	1    6900 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R48
U 1 1 65813745
P 6500 4750
F 0 "R48" V 6560 4755 50  0000 C CNN
F 1 "270" V 6430 4745 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6500 4750 50  0001 C CNN
F 3 "~" H 6500 4750 50  0001 C CNN
	1    6500 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R50
U 1 1 65814601
P 6900 4750
F 0 "R50" V 6960 4755 50  0000 C CNN
F 1 "270" V 6830 4745 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6900 4750 50  0001 C CNN
F 3 "~" H 6900 4750 50  0001 C CNN
	1    6900 4750
	1    0    0    -1  
$EndComp
Text GLabel 5950 3950 0    39   Input ~ 0
D3V3DD
$Comp
L power:GND #PWR012
U 1 1 6590213E
P 6700 4900
F 0 "#PWR012" H 6700 4650 50  0001 C CNN
F 1 "GND" H 6704 4745 50  0000 C CNN
F 2 "" H 6700 4900 50  0001 C CNN
F 3 "" H 6700 4900 50  0001 C CNN
	1    6700 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 65902BED
P 8000 4950
F 0 "#PWR018" H 8000 4700 50  0001 C CNN
F 1 "GND" H 8004 4795 50  0000 C CNN
F 2 "" H 8000 4950 50  0001 C CNN
F 3 "" H 8000 4950 50  0001 C CNN
	1    8000 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q5
U 1 1 63E66683
P 8100 4650
F 0 "Q5" H 8305 4696 50  0000 L CNN
F 1 "BSS138" H 8305 4605 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8300 4575 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 8100 4650 50  0001 L CNN
	1    8100 4650
	-1   0    0    -1  
$EndComp
Text GLabel 10350 4750 2    39   Input ~ 0
~CS_B
Wire Wire Line
	10350 4750 10200 4750
Wire Wire Line
	10200 5200 10200 4750
Connection ~ 10200 5200
Wire Wire Line
	7750 3650 7750 3550
Wire Wire Line
	6900 3650 7750 3650
$Comp
L Device:R_Small R58
U 1 1 641A4073
P 8500 4650
F 0 "R58" V 8560 4655 50  0000 C CNN
F 1 "1K" V 8430 4645 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8500 4650 50  0001 C CNN
F 3 "~" H 8500 4650 50  0001 C CNN
	1    8500 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 4600 6300 4550
Wire Wire Line
	6300 4600 6700 4600
Wire Wire Line
	6700 4600 6700 4550
Connection ~ 6300 4600
Wire Wire Line
	6050 3950 5950 3950
Wire Wire Line
	6900 4850 6900 4900
Wire Wire Line
	6900 4900 6700 4900
Wire Wire Line
	6700 4900 6500 4900
Wire Wire Line
	6500 4900 6500 4850
Connection ~ 6700 4900
Wire Wire Line
	6500 4650 6500 4550
Wire Wire Line
	6900 4650 6900 4550
Wire Wire Line
	4500 4600 4500 4500
Wire Wire Line
	4500 4500 4400 4500
Wire Wire Line
	5700 4750 5750 4750
$Comp
L Device:R_Small R44
U 1 1 64638B7F
P 5850 4750
F 0 "R44" V 5910 4755 50  0000 C CNN
F 1 "1K" V 5780 4745 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5850 4750 50  0001 C CNN
F 3 "~" H 5850 4750 50  0001 C CNN
	1    5850 4750
	0    1    1    0   
$EndComp
Text GLabel 6050 4750 2    39   Input ~ 0
Chn_C
Wire Wire Line
	6050 4750 5950 4750
$Comp
L Device:Q_PMOS_GSD Q1
U 1 1 646DF850
P 5950 2950
F 0 "Q1" H 6155 2904 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 6155 2995 50  0000 L CNN
F 2 "" H 6150 3050 50  0001 C CNN
F 3 "~" H 5950 2950 50  0001 C CNN
	1    5950 2950
	1    0    0    1   
$EndComp
Text GLabel 5950 2550 0    39   Input ~ 0
D3V3DD
$Comp
L Device:Q_PMOS_GSD Q2
U 1 1 642739CB
P 5950 4350
F 0 "Q2" H 6155 4304 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 6155 4395 50  0000 L CNN
F 2 "" H 6150 4450 50  0001 C CNN
F 3 "~" H 5950 4350 50  0001 C CNN
	1    5950 4350
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R43
U 1 1 641A5A53
P 5850 4100
F 0 "R43" V 5910 4105 50  0000 C CNN
F 1 "10K" V 5780 4095 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5850 4100 50  0001 C CNN
F 3 "~" H 5850 4100 50  0001 C CNN
	1    5850 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 4600 5050 4600
Wire Wire Line
	6050 4550 6050 4600
Connection ~ 6050 4600
Wire Wire Line
	6050 4600 6300 4600
Wire Wire Line
	6050 4150 6050 4100
Wire Wire Line
	5950 4100 6050 4100
Connection ~ 6050 4100
Wire Wire Line
	6050 4100 6050 3950
Wire Wire Line
	5700 4100 5750 4100
Wire Wire Line
	5700 4100 5700 4350
Wire Wire Line
	5750 4350 5700 4350
Connection ~ 5700 4350
Wire Wire Line
	5700 4350 5700 4750
$Comp
L Device:R_Small R38
U 1 1 649B76D3
P 5850 2700
F 0 "R38" V 5910 2705 50  0000 C CNN
F 1 "10K" V 5780 2695 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5850 2700 50  0001 C CNN
F 3 "~" H 5850 2700 50  0001 C CNN
	1    5850 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	6700 3150 6700 3200
Wire Wire Line
	6700 3200 6300 3200
Wire Wire Line
	4500 3200 4500 3100
Wire Wire Line
	4400 3100 4500 3100
Wire Wire Line
	6050 3150 6050 3200
Connection ~ 6050 3200
Wire Wire Line
	6050 3200 5050 3200
Wire Wire Line
	6300 3150 6300 3200
Connection ~ 6300 3200
Wire Wire Line
	6300 3200 6050 3200
Wire Wire Line
	6500 3150 6500 3250
Wire Wire Line
	6900 3150 6900 3250
Wire Wire Line
	6900 3450 6900 3500
Wire Wire Line
	6900 3500 6700 3500
Wire Wire Line
	6500 3500 6500 3450
Wire Wire Line
	6050 2750 6050 2700
Wire Wire Line
	6050 2550 5950 2550
Wire Wire Line
	5950 2700 6050 2700
Connection ~ 6050 2700
Wire Wire Line
	6050 2700 6050 2550
Wire Wire Line
	5750 2700 5700 2700
Wire Wire Line
	5700 2700 5700 2950
Wire Wire Line
	5700 2950 5750 2950
Wire Wire Line
	5700 3350 5750 3350
$Comp
L Device:R_Small R39
U 1 1 64C670E6
P 5850 3350
F 0 "R39" V 5910 3355 50  0000 C CNN
F 1 "1K" V 5780 3345 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5850 3350 50  0001 C CNN
F 3 "~" H 5850 3350 50  0001 C CNN
	1    5850 3350
	0    1    1    0   
$EndComp
Text GLabel 6050 3350 2    39   Input ~ 0
Chn_B
Wire Wire Line
	6050 3350 5950 3350
Wire Wire Line
	5700 2950 5700 3350
Connection ~ 5700 2950
$Comp
L power:GND #PWR06
U 1 1 64CB807B
P 6700 3500
F 0 "#PWR06" H 6700 3250 50  0001 C CNN
F 1 "GND" H 6704 3345 50  0000 C CNN
F 2 "" H 6700 3500 50  0001 C CNN
F 3 "" H 6700 3500 50  0001 C CNN
	1    6700 3500
	1    0    0    -1  
$EndComp
Connection ~ 6700 3500
Wire Wire Line
	6700 3500 6500 3500
Text GLabel 8750 4350 0    39   Input ~ 0
Chn_C
Text GLabel 8750 4450 0    39   Input ~ 0
Chn_B
Wire Wire Line
	8800 4250 8800 4350
Wire Wire Line
	8800 4350 8750 4350
Wire Wire Line
	8900 4250 8900 4450
Wire Wire Line
	8900 4450 8750 4450
Wire Wire Line
	9000 4250 9000 4650
$Comp
L Device:R_Small R56
U 1 1 64E5281B
P 8350 4800
F 0 "R56" V 8410 4805 50  0000 C CNN
F 1 "10K" V 8280 4795 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8350 4800 50  0001 C CNN
F 3 "~" H 8350 4800 50  0001 C CNN
	1    8350 4800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR029
U 1 1 64E53DFE
P 8350 4950
F 0 "#PWR029" H 8350 4700 50  0001 C CNN
F 1 "GND" H 8354 4795 50  0000 C CNN
F 2 "" H 8350 4950 50  0001 C CNN
F 3 "" H 8350 4950 50  0001 C CNN
	1    8350 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 4650 9000 4650
Wire Wire Line
	8400 4650 8350 4650
Wire Wire Line
	8350 4700 8350 4650
Connection ~ 8350 4650
Wire Wire Line
	8350 4650 8300 4650
Wire Wire Line
	8350 4950 8350 4900
Wire Wire Line
	8000 4950 8000 4850
Wire Wire Line
	8000 4450 8000 4400
Wire Wire Line
	8000 4400 7900 4400
$Comp
L Device:R_Small R52
U 1 1 6503AF29
P 7800 4400
F 0 "R52" V 7860 4405 50  0000 C CNN
F 1 "270" V 7730 4395 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7800 4400 50  0001 C CNN
F 3 "~" H 7800 4400 50  0001 C CNN
	1    7800 4400
	0    1    1    0   
$EndComp
Text GLabel 7650 4400 0    39   Input ~ 0
Att_B_C
Wire Wire Line
	7700 4400 7650 4400
$Comp
L power:GND #PWR013
U 1 1 650E33BD
P 8000 2600
F 0 "#PWR013" H 8000 2350 50  0001 C CNN
F 1 "GND" H 8004 2445 50  0000 C CNN
F 2 "" H 8000 2600 50  0001 C CNN
F 3 "" H 8000 2600 50  0001 C CNN
	1    8000 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q4
U 1 1 650E43A9
P 8100 2300
F 0 "Q4" H 8305 2346 50  0000 L CNN
F 1 "BSS138" H 8305 2255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8300 2225 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 8100 2300 50  0001 L CNN
	1    8100 2300
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R57
U 1 1 650E43B3
P 8500 2300
F 0 "R57" V 8560 2305 50  0000 C CNN
F 1 "1K" V 8430 2295 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8500 2300 50  0001 C CNN
F 3 "~" H 8500 2300 50  0001 C CNN
	1    8500 2300
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R55
U 1 1 650E43BD
P 8350 2450
F 0 "R55" V 8410 2455 50  0000 C CNN
F 1 "10K" V 8280 2445 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8350 2450 50  0001 C CNN
F 3 "~" H 8350 2450 50  0001 C CNN
	1    8350 2450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR028
U 1 1 650E43C7
P 8350 2600
F 0 "#PWR028" H 8350 2350 50  0001 C CNN
F 1 "GND" H 8354 2445 50  0000 C CNN
F 2 "" H 8350 2600 50  0001 C CNN
F 3 "" H 8350 2600 50  0001 C CNN
	1    8350 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2300 8350 2300
Wire Wire Line
	8350 2350 8350 2300
Connection ~ 8350 2300
Wire Wire Line
	8350 2300 8300 2300
Wire Wire Line
	8350 2600 8350 2550
Wire Wire Line
	8000 2600 8000 2500
Wire Wire Line
	8000 2100 8000 2050
Wire Wire Line
	8000 2050 7900 2050
$Comp
L Device:R_Small R51
U 1 1 650E43D9
P 7800 2050
F 0 "R51" V 7860 2055 50  0000 C CNN
F 1 "270" V 7730 2045 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7800 2050 50  0001 C CNN
F 3 "~" H 7800 2050 50  0001 C CNN
	1    7800 2050
	0    1    1    0   
$EndComp
Text GLabel 7650 2050 0    39   Input ~ 0
Att_A
Wire Wire Line
	7700 2050 7650 2050
Wire Wire Line
	8600 2300 9000 2300
Wire Wire Line
	9000 2300 9000 2100
Text GLabel 8750 2150 0    39   Input ~ 0
Chn_A
Wire Wire Line
	8900 2150 8750 2150
Wire Wire Line
	8900 2100 8900 2150
Text GLabel 1950 5000 2    39   Input ~ 0
Chn_BL
Text GLabel 1950 5100 2    39   Input ~ 0
Chn_CL
$Comp
L power:GND #PWR05
U 1 1 65299C68
P 1750 5350
F 0 "#PWR05" H 1750 5100 50  0001 C CNN
F 1 "GND" H 1755 5177 50  0000 C CNN
F 2 "" H 1750 5350 50  0001 C CNN
F 3 "" H 1750 5350 50  0001 C CNN
	1    1750 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 5350 1750 5300
$Comp
L Device:R_Small R9
U 1 1 655418AD
P 1800 4900
F 0 "R9" V 1850 4800 50  0000 C CNN
F 1 "270" V 1800 4900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 1800 4900 50  0001 C CNN
F 3 "~" H 1800 4900 50  0001 C CNN
	1    1800 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 4900 1700 4900
Text GLabel 1950 4900 2    39   Input ~ 0
Chn_AL
$Comp
L Device:R_Small R36
U 1 1 6584CD9A
P 1800 5000
F 0 "R36" V 1850 4900 50  0000 C CNN
F 1 "270" V 1800 5000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 1800 5000 50  0001 C CNN
F 3 "~" H 1800 5000 50  0001 C CNN
	1    1800 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R37
U 1 1 6584D064
P 1800 5100
F 0 "R37" V 1850 5000 50  0000 C CNN
F 1 "270" V 1800 5100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 1800 5100 50  0001 C CNN
F 3 "~" H 1800 5100 50  0001 C CNN
	1    1800 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 4900 1950 4900
Wire Wire Line
	1900 5000 1950 5000
Wire Wire Line
	1900 5100 1950 5100
Wire Wire Line
	1650 5300 1750 5300
Text GLabel 5100 3300 2    39   Input ~ 0
Chn_BL
Text GLabel 5100 4700 2    39   Input ~ 0
Chn_CL
Wire Wire Line
	5100 3300 5050 3300
Wire Wire Line
	5050 3300 5050 3200
Connection ~ 5050 3200
Wire Wire Line
	5050 3200 4500 3200
Wire Wire Line
	5100 4700 5050 4700
Wire Wire Line
	5050 4700 5050 4600
Connection ~ 5050 4600
Wire Wire Line
	5050 4600 6050 4600
$Comp
L Device:Q_PMOS_GSD Q3
U 1 1 65B0CF25
P 6000 1550
F 0 "Q3" H 6205 1504 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 6205 1595 50  0000 L CNN
F 2 "" H 6200 1650 50  0001 C CNN
F 3 "~" H 6000 1550 50  0001 C CNN
	1    6000 1550
	1    0    0    1   
$EndComp
Text GLabel 6000 1150 0    39   Input ~ 0
D3V3DD
$Comp
L Device:R_Small R45
U 1 1 65B0DFE2
P 5900 1300
F 0 "R45" V 5960 1305 50  0000 C CNN
F 1 "10K" V 5830 1295 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5900 1300 50  0001 C CNN
F 3 "~" H 5900 1300 50  0001 C CNN
	1    5900 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	6100 1350 6100 1300
Wire Wire Line
	6100 1150 6000 1150
Wire Wire Line
	6000 1300 6100 1300
Connection ~ 6100 1300
Wire Wire Line
	6100 1300 6100 1150
Wire Wire Line
	5800 1300 5750 1300
Wire Wire Line
	5750 1300 5750 1550
Wire Wire Line
	5750 1550 5800 1550
Wire Wire Line
	5750 1550 5750 1950
Connection ~ 5750 1550
Wire Wire Line
	5750 1950 5800 1950
$Comp
L Device:R_Small R46
U 1 1 65B6B943
P 5900 1950
F 0 "R46" V 5960 1955 50  0000 C CNN
F 1 "1K" V 5830 1945 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 5900 1950 50  0001 C CNN
F 3 "~" H 5900 1950 50  0001 C CNN
	1    5900 1950
	0    1    1    0   
$EndComp
Text GLabel 6100 1950 2    39   Input ~ 0
Chn_A
Wire Wire Line
	6100 1950 6000 1950
Text GLabel 6200 1800 2    39   Input ~ 0
Chn_AL
Wire Wire Line
	6100 1750 6100 1800
Wire Wire Line
	6100 1800 6200 1800
NoConn ~ 8800 2100
$Comp
L Device:CP_Small C50
U 1 1 65D3F42D
P 10800 3450
F 0 "C50" H 10745 3545 50  0000 L CNN
F 1 "1u" H 10755 3370 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10800 3450 50  0001 C CNN
F 3 "~" H 10800 3450 50  0001 C CNN
	1    10800 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR042
U 1 1 65D40FEE
P 10800 3600
F 0 "#PWR042" H 10800 3350 50  0001 C CNN
F 1 "GND" H 10804 3445 50  0000 C CNN
F 2 "" H 10800 3600 50  0001 C CNN
F 3 "" H 10800 3600 50  0001 C CNN
	1    10800 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 3300 10800 3300
Wire Wire Line
	10800 3300 10800 3350
Connection ~ 10300 3300
Wire Wire Line
	10800 3550 10800 3600
$Comp
L Device:CP_Small C49
U 1 1 65DFC996
P 10800 1300
F 0 "C49" H 10745 1395 50  0000 L CNN
F 1 "1u" H 10755 1220 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10800 1300 50  0001 C CNN
F 3 "~" H 10800 1300 50  0001 C CNN
	1    10800 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR041
U 1 1 65DFDAAA
P 10800 1450
F 0 "#PWR041" H 10800 1200 50  0001 C CNN
F 1 "GND" H 10804 1295 50  0000 C CNN
F 2 "" H 10800 1450 50  0001 C CNN
F 3 "" H 10800 1450 50  0001 C CNN
	1    10800 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 1150 10800 1150
Wire Wire Line
	10800 1150 10800 1200
Wire Wire Line
	10800 1400 10800 1450
Connection ~ 10300 1150
$Comp
L max6070:MAX6070 U5
U 1 1 60BF8172
P 3750 5400
F 0 "U5" H 3750 5887 60  0000 C CNN
F 1 "MAX6070 - 1V8" H 3750 5781 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6_Handsoldering" H 3600 5850 60  0001 C CNN
F 3 "" H 3600 5850 60  0001 C CNN
	1    3750 5400
	-1   0    0    -1  
$EndComp
Text Notes 2650 6300 0    39   ~ 0
Use R29 to trim voltage\ndown to 1.3V max\nAlternative to regulator usage\nis to short pad 4 & 5, omit\nC24 and adjust R29 value to\nset voltage @ 1V3 for VPre
$EndSCHEMATC

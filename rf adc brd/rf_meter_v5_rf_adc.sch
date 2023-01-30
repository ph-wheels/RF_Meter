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
P 4160 5400
F 0 "R29" V 4075 5400 50  0000 C CNN
F 1 "438" V 4245 5390 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 4160 5400 50  0001 C CNN
F 3 "~" H 4160 5400 50  0001 C CNN
	1    4160 5400
	0    1    1    0   
$EndComp
Connection ~ 4550 5400
$Comp
L Device:C_Small C19
U 1 1 605B23B6
P 4350 5550
F 0 "C19" H 4300 5625 50  0000 L CNN
F 1 "100n" H 4205 5475 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4350 5550 50  0001 C CNN
F 3 "~" H 4350 5550 50  0001 C CNN
	1    4350 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5700 4350 5650
$Comp
L Device:CP_Small C23
U 1 1 605BC3E0
P 4550 5550
F 0 "C23" H 4500 5625 50  0000 L CNN
F 1 "10u" H 4450 5475 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4550 5550 50  0001 C CNN
F 3 "~" H 4550 5550 50  0001 C CNN
	1    4550 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4260 5400 4350 5400
Wire Wire Line
	4350 5450 4350 5400
Connection ~ 4350 5400
Wire Wire Line
	4550 5700 4550 5650
Wire Wire Line
	4550 5450 4550 5400
$Comp
L Device:C_Small C40
U 1 1 606A059A
P 9250 1100
F 0 "C40" H 9195 1195 50  0000 L CNN
F 1 "100n" H 9150 1015 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9250 1100 50  0001 C CNN
F 3 "~" H 9250 1100 50  0001 C CNN
	1    9250 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 2800 9700 2750
$Comp
L Device:C_Small C26
U 1 1 60716EBD
P 6450 1100
F 0 "C26" H 6455 1195 50  0000 L CNN
F 1 "100n" H 6350 1010 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6450 1100 50  0001 C CNN
F 3 "~" H 6450 1100 50  0001 C CNN
	1    6450 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C38
U 1 1 60584BDC
P 9845 2650
F 0 "C38" H 9800 2740 50  0000 L CNN
F 1 "10u" H 9800 2565 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9845 2650 50  0001 C CNN
F 3 "~" H 9845 2650 50  0001 C CNN
	1    9845 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C27
U 1 1 606192C6
P 6600 1100
F 0 "C27" H 6605 1195 50  0000 L CNN
F 1 "10u" H 6550 1010 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6600 1100 50  0001 C CNN
F 3 "~" H 6600 1100 50  0001 C CNN
	1    6600 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1300 6450 1200
Text Notes 5955 6315 0    100  ~ 0
Analog to Digital section
Text Notes 7030 7000 0    197  ~ 39
RF Meter ADC front-end
Text Notes 8510 7630 0    39   ~ 0
7-jun-2021 / v1.2
Connection ~ 9550 900 
$Comp
L Device:CP_Small C41
U 1 1 606553BC
P 9400 1100
F 0 "C41" H 9345 1200 50  0000 L CNN
F 1 "4u7" H 9350 1010 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9400 1100 50  0001 C CNN
F 3 "~" H 9400 1100 50  0001 C CNN
	1    9400 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 1205 10800 1300
$Comp
L Device:CP_Small C45
U 1 1 6059FA6C
P 10800 1105
F 0 "C45" H 10750 1255 50  0000 L CNN
F 1 "10u" H 10750 1015 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10800 1105 50  0001 C CNN
F 3 "~" H 10800 1105 50  0001 C CNN
	1    10800 1105
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C44
U 1 1 606C71E0
P 10650 1100
F 0 "C44" H 10595 1240 50  0000 L CNN
F 1 "100n" H 10550 1005 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10650 1100 50  0001 C CNN
F 3 "~" H 10650 1100 50  0001 C CNN
	1    10650 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 1300 10650 1200
$Comp
L power:PWR_FLAG #FLG06
U 1 1 60693D90
P 10800 650
F 0 "#FLG06" H 10800 725 50  0001 C CNN
F 1 "PWR_FLAG" H 10570 720 50  0000 C CNN
F 2 "" H 10800 650 50  0001 C CNN
F 3 "~" H 10800 650 50  0001 C CNN
	1    10800 650 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 900  10800 1005
Wire Wire Line
	10800 650  10800 900 
Connection ~ 10800 900 
$Comp
L Device:R_Small R28
U 1 1 60791F95
P 3950 5555
F 0 "R28" V 4035 5490 50  0000 C CNN
F 1 "1K" V 3865 5550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 3950 5555 50  0001 C CNN
F 3 "~" H 3950 5555 50  0001 C CNN
	1    3950 5555
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
	9700 2550 9700 2500
Wire Wire Line
	9250 1000 9250 900 
Connection ~ 9250 900 
Wire Wire Line
	9250 900  9400 900 
Wire Wire Line
	9400 1000 9400 900 
Connection ~ 9400 900 
Wire Wire Line
	9400 900  9550 900 
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
Wire Wire Line
	6050 850  6050 2200
Wire Wire Line
	5600 2250 6000 2250
Connection ~ 5600 2250
Wire Wire Line
	5550 2450 5900 2450
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
	3950 5700 3950 5655
Wire Wire Line
	3950 5455 3950 5400
Text GLabel 3900 5200 0    39   Input ~ 0
VPre
Text GLabel 3200 2700 2    39   Input ~ 0
VPre
Text GLabel 3200 4100 2    39   Input ~ 0
VPre
$Comp
L Regulator_Linear:LT1761-3.3 U9
U 1 1 60A9906C
P 10100 1000
F 0 "U9" H 9845 710 50  0000 C CNN
F 1 "LT1761-3.3" H 10100 1276 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 10100 1325 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/1761sff.pdf" H 10100 1000 50  0001 C CNN
	1    10100 1000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9550 900  9650 900 
Wire Wire Line
	9550 1000 9550 900 
$Comp
L Device:C_Small C42
U 1 1 60655392
P 9550 1100
F 0 "C42" H 9500 1200 50  0000 L CNN
F 1 "10nF" H 9465 960 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9550 1100 50  0001 C CNN
F 3 "~" H 9550 1100 50  0001 C CNN
	1    9550 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 1350 10100 1300
Wire Wire Line
	9700 1200 9550 1200
Wire Wire Line
	9250 1200 9250 1300
Wire Wire Line
	9400 1200 9400 1300
Wire Wire Line
	10500 900  10550 900 
Wire Wire Line
	10500 1000 10650 1000
Wire Wire Line
	10650 1000 10650 900 
Connection ~ 10650 900 
$Comp
L Device:C_Small C28
U 1 1 62C19229
P 6900 1100
F 0 "C28" H 6845 1175 50  0000 L CNN
F 1 "100n" H 6800 1015 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6900 1100 50  0001 C CNN
F 3 "~" H 6900 1100 50  0001 C CNN
	1    6900 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C29
U 1 1 62C19ED1
P 7050 1100
F 0 "C29" H 6995 1175 50  0000 L CNN
F 1 "4u7" H 6995 1010 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7050 1100 50  0001 C CNN
F 3 "~" H 7050 1100 50  0001 C CNN
	1    7050 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1000 6900 900 
Wire Wire Line
	7050 1000 7050 900 
Wire Wire Line
	7200 950  7200 900 
$Comp
L Device:C_Small C31
U 1 1 62C19EDE
P 7200 800
F 0 "C31" V 7150 830 50  0000 L CNN
F 1 "10nF" V 7145 580 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7200 800 50  0001 C CNN
F 3 "~" H 7200 800 50  0001 C CNN
	1    7200 800 
	0    1    1    0   
$EndComp
Wire Wire Line
	6900 1200 6900 1300
Wire Wire Line
	7050 1200 7050 1300
Wire Wire Line
	6900 900  7050 900 
Connection ~ 6900 900 
Connection ~ 7050 900 
Connection ~ 7200 900 
Wire Wire Line
	7200 900  7350 900 
Wire Wire Line
	7750 1450 7750 1300
Wire Wire Line
	10050 2750 10050 3050
$Comp
L Device:R_Small R42
U 1 1 606FF8CC
P 10200 2650
F 0 "R42" V 10260 2805 50  0000 C CNN
F 1 "10K" V 10265 2635 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 10200 2650 50  0001 C CNN
F 3 "~" H 10200 2650 50  0001 C CNN
	1    10200 2650
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R41
U 1 1 60700BD9
P 10050 2650
F 0 "R41" V 10110 2810 50  0000 C CNN
F 1 "10K" V 10120 2625 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 10050 2650 50  0001 C CNN
F 3 "~" H 10050 2650 50  0001 C CNN
	1    10050 2650
	-1   0    0    1   
$EndComp
Wire Wire Line
	10050 2500 10050 2550
Wire Wire Line
	10200 2550 10200 2500
Wire Wire Line
	10200 2500 10050 2500
Text GLabel 9395 2500 0    39   Input ~ 0
D3V3DD
Wire Wire Line
	9395 2500 9450 2500
Text GLabel 8900 750  0    39   Input ~ 0
D3V3DD
$Comp
L Device:R_Small R31
U 1 1 64764D4A
P 7200 1050
F 0 "R31" V 7265 945 50  0000 C CNN
F 1 "10K" V 7265 1120 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7200 1050 50  0001 C CNN
F 3 "~" H 7200 1050 50  0001 C CNN
	1    7200 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R32
U 1 1 647EF62B
P 7450 1300
F 0 "R32" V 7380 1230 50  0000 C CNN
F 1 "20K" V 7380 1415 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7450 1300 50  0001 C CNN
F 3 "~" H 7450 1300 50  0001 C CNN
	1    7450 1300
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R33
U 1 1 647F5277
P 7450 1400
F 0 "R33" V 7515 1310 50  0000 C CNN
F 1 "6K8" V 7515 1470 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7450 1400 50  0001 C CNN
F 3 "~" H 7450 1400 50  0001 C CNN
	1    7450 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 1400 7600 1400
Wire Wire Line
	7550 1300 7600 1300
Wire Wire Line
	7600 1300 7600 1400
Connection ~ 7600 1400
Wire Wire Line
	7350 1400 7300 1400
Wire Wire Line
	7300 1400 7300 1300
Wire Wire Line
	7350 1300 7300 1300
Connection ~ 7300 1300
Wire Wire Line
	7350 1100 7300 1100
$Comp
L Regulator_Linear:LT1761-BYP U7
U 1 1 6224AC6D
P 7750 1000
F 0 "U7" H 7560 740 50  0000 C CNN
F 1 "LT1761-BYP" H 7750 1276 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 7750 1350 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/1761sff.pdf" H 7750 1000 50  0001 C CNN
	1    7750 1000
	-1   0    0    -1  
$EndComp
Text Notes 7920 1650 0    39   ~ 0
3V6 regulator
$Comp
L Device:C_Small C35
U 1 1 60A5FC3A
P 9700 2650
F 0 "C35" H 9645 2740 50  0000 L CNN
F 1 "100n" H 9605 2565 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9700 2650 50  0001 C CNN
F 3 "~" H 9700 2650 50  0001 C CNN
	1    9700 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C25
U 1 1 60C212A3
P 5650 5650
F 0 "C25" H 5600 5735 50  0000 L CNN
F 1 "100n" H 5600 5565 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5650 5650 50  0001 C CNN
F 3 "~" H 5650 5650 50  0001 C CNN
	1    5650 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C24
U 1 1 60C23BC0
P 5500 5650
F 0 "C24" H 5450 5730 50  0000 L CNN
F 1 "100n" H 5405 5565 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5500 5650 50  0001 C CNN
F 3 "~" H 5500 5650 50  0001 C CNN
	1    5500 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 5950 5050 5900
Wire Wire Line
	4750 5600 4700 5600
Wire Wire Line
	4700 5600 4700 5400
Wire Wire Line
	4700 5400 4750 5400
Wire Wire Line
	4550 5400 4700 5400
Connection ~ 4700 5400
Wire Wire Line
	5350 5300 5400 5300
Wire Wire Line
	5500 5550 5500 5500
Wire Wire Line
	5350 5500 5500 5500
Wire Wire Line
	5650 5550 5650 5300
Wire Wire Line
	5650 5750 5650 5950
Wire Wire Line
	5350 5700 5400 5700
Wire Wire Line
	5400 5700 5400 5300
Connection ~ 5400 5300
Wire Wire Line
	5400 5300 5650 5300
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
Wire Wire Line
	9850 2800 9845 2750
Wire Wire Line
	9845 2550 9845 2500
Text Notes 10545 5120 0    39   ~ 0
6V0 - 8V4 power\nsource from Li-Ion\n(2S - BMS)
Wire Wire Line
	4450 4000 4450 4100
Wire Wire Line
	6600 1000 6600 900 
Connection ~ 6600 900 
Wire Wire Line
	6600 1200 6600 1300
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
Wire Wire Line
	5550 1050 5950 1050
Connection ~ 5600 850 
Wire Wire Line
	5600 850  6050 850 
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
$Comp
L max6070:MAX6070 U5
U 1 1 60BF8172
P 5050 5500
F 0 "U5" H 5050 5987 60  0000 C CNN
F 1 "MAX6070 - 1V8" H 5050 5881 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6_Handsoldering" H 4900 5950 60  0001 C CNN
F 3 "" H 4900 5950 60  0001 C CNN
	1    5050 5500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4350 5400 4550 5400
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
	3950 5400 4060 5400
Connection ~ 3950 5400
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
$Comp
L Device:C_Small C43
U 1 1 60A617F4
P 8600 5050
F 0 "C43" H 8605 5115 50  0000 L CNN
F 1 "100n" H 8610 4980 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8600 5050 50  0001 C CNN
F 3 "~" H 8600 5050 50  0001 C CNN
	1    8600 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1000 6450 900 
Wire Wire Line
	6450 900  6600 900 
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 61D3600F
P 2000 4950
F 0 "J4" H 1918 5167 50  0000 C CNN
F 1 "Vtest" H 1918 5076 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2000 4950 50  0001 C CNN
F 3 "~" H 2000 4950 50  0001 C CNN
	1    2000 4950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2200 5050 2600 5050
Wire Wire Line
	2600 5050 2600 5200
Wire Wire Line
	2200 4950 2650 4950
Text Notes 1700 5230 0    39   ~ 0
Test Voltage Input
Connection ~ 10200 3150
Wire Wire Line
	10200 2750 10200 3150
$Comp
L Device:C_Small C39
U 1 1 60D88059
P 9050 4150
F 0 "C39" H 9000 4225 50  0000 L CNN
F 1 "1u" H 9055 4060 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9050 4150 50  0001 C CNN
F 3 "~" H 9050 4150 50  0001 C CNN
	1    9050 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 4250 8950 4250
Wire Wire Line
	9050 4250 9050 4300
Wire Wire Line
	8950 4250 8950 4000
Wire Wire Line
	9700 3450 9800 3450
Wire Wire Line
	9700 3550 9900 3550
Wire Wire Line
	9700 3350 10000 3350
Wire Wire Line
	9700 3250 10100 3250
$Comp
L Device:C_Small C36
U 1 1 60DA5715
P 8850 4150
F 0 "C36" H 8800 4225 50  0000 L CNN
F 1 "100n" H 8750 4085 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8850 4150 50  0001 C CNN
F 3 "~" H 8850 4150 50  0001 C CNN
	1    8850 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 4000 8850 4050
Wire Wire Line
	9050 4000 9050 4050
Wire Wire Line
	9250 4000 9250 4050
Wire Wire Line
	9450 4000 9450 4050
Wire Wire Line
	9350 4000 9350 4050
Wire Wire Line
	9350 4050 9450 4050
Connection ~ 9450 4050
Wire Wire Line
	9450 4050 9450 4300
Wire Wire Line
	9150 4000 9150 4050
Wire Wire Line
	9150 4050 9250 4050
Connection ~ 9250 4050
Wire Wire Line
	9250 4050 9250 4300
Wire Wire Line
	9700 4050 9450 4050
Wire Wire Line
	9700 3750 9700 4050
Wire Wire Line
	9700 3650 10300 3650
Wire Wire Line
	8750 4150 8750 4000
Wire Wire Line
	8650 4000 8650 4050
Wire Wire Line
	9700 3150 10200 3150
Wire Wire Line
	9700 3050 10050 3050
Wire Wire Line
	8750 4150 8150 4150
Wire Wire Line
	8650 4050 8050 4050
Wire Wire Line
	8400 2800 8650 2800
Wire Wire Line
	9350 2700 8750 2700
$Comp
L Device:C_Small C32
U 1 1 61321FD2
P 7900 3400
F 0 "C32" H 7835 3565 50  0000 L CNN
F 1 "100n" H 7805 3345 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7900 3400 50  0001 C CNN
F 3 "~" H 7900 3400 50  0001 C CNN
	1    7900 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R34
U 1 1 61324576
P 7700 3300
F 0 "R34" V 7760 3305 50  0000 C CNN
F 1 "1K" V 7630 3295 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7700 3300 50  0001 C CNN
F 3 "~" H 7700 3300 50  0001 C CNN
	1    7700 3300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R35
U 1 1 613254F1
P 7700 3500
F 0 "R35" V 7760 3505 50  0000 C CNN
F 1 "1K" V 7630 3490 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7700 3500 50  0001 C CNN
F 3 "~" H 7700 3500 50  0001 C CNN
	1    7700 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7800 3300 7900 3300
Connection ~ 7900 3300
Wire Wire Line
	7800 3500 7900 3500
Connection ~ 7900 3500
Wire Wire Line
	7600 3500 7400 3500
Wire Wire Line
	10900 5500 10900 5450
Connection ~ 10900 5450
Wire Wire Line
	10900 5450 11100 5450
Wire Wire Line
	10800 5500 10800 5400
Text GLabel 3250 5400 2    39   Input ~ 0
AV3V6DD
$Comp
L Device:R_Small R9
U 1 1 60DC4F09
P 2750 4950
F 0 "R9" V 2825 4945 50  0000 C CNN
F 1 "1K" V 2675 4940 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 2750 4950 50  0001 C CNN
F 3 "~" H 2750 4950 50  0001 C CNN
	1    2750 4950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7900 3500 8030 3500
Wire Wire Line
	7900 3300 8030 3300
$Comp
L My-Design:MAX4618 U6
U 1 1 611E4CB7
P 6600 2900
F 0 "U6" H 6595 4040 50  0000 C CNN
F 1 "MAX4618" H 6590 3480 50  0000 C CNN
F 2 "SO:TSSOP-16-1EP_4.4x5mm_P0.65mm" H 6590 1890 50  0001 C CNN
F 3 "" H 6970 2850 50  0001 C CNN
	1    6600 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2200 6200 2200
Wire Wire Line
	6000 2800 6200 2800
Wire Wire Line
	5850 2400 6200 2400
Wire Wire Line
	5800 2600 6200 2600
Wire Wire Line
	5800 2600 5800 4950
Wire Wire Line
	5950 1050 5950 3000
Wire Wire Line
	5950 3000 6200 3000
Wire Wire Line
	5900 3600 6200 3600
Wire Wire Line
	5950 3200 6200 3200
Wire Wire Line
	6100 3400 6200 3400
Wire Wire Line
	6100 3400 6100 4250
Wire Wire Line
	7500 2400 7500 3300
Wire Wire Line
	7000 2400 7500 2400
Wire Wire Line
	7500 3300 7600 3300
Wire Wire Line
	7000 2600 7400 2600
Wire Wire Line
	7400 2600 7400 3500
NoConn ~ 7000 3400
Wire Wire Line
	7200 3000 7200 4150
Wire Wire Line
	7000 3000 7200 3000
Wire Wire Line
	7300 2800 7300 4050
Wire Wire Line
	7000 2800 7300 2800
Wire Wire Line
	6600 3800 6600 3850
Text GLabel 6400 1850 0    39   Input ~ 0
AV3V6DD
Wire Wire Line
	6400 1850 6600 1850
Wire Wire Line
	6600 1850 6600 2000
$Comp
L Device:C_Small C30
U 1 1 616F2D1F
P 7100 2000
F 0 "C30" H 7005 2070 50  0000 L CNN
F 1 "0.1" H 6970 1920 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7100 2000 50  0001 C CNN
F 3 "~" H 7100 2000 50  0001 C CNN
	1    7100 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2150 7100 2100
Wire Wire Line
	7100 1850 7100 1900
Wire Wire Line
	6600 1850 7100 1850
Connection ~ 6600 1850
$Comp
L power:PWR_FLAG #FLG04
U 1 1 60FDFA46
P 6450 650
F 0 "#FLG04" H 6450 725 50  0001 C CNN
F 1 "PWR_FLAG" H 6690 725 50  0000 C CNN
F 2 "" H 6450 650 50  0001 C CNN
F 3 "~" H 6450 650 50  0001 C CNN
	1    6450 650 
	1    0    0    -1  
$EndComp
Connection ~ 10050 2500
Connection ~ 9450 2500
Text Notes 695  6810 0    39   ~ 0
Note: Do not populate R21 for 1V8 VPre,\n      R18 is used to adjust output of U7 to 3V6 dc MAX !.\n\nNote: R25, R26, C47 may serve as a filter option\n      else place jumper wire or 0 Ohm for R25, R26\n\nNote: check all regulator voltages prior to installing\n      LTC2055's, MAX4618 and MAX11270\n\nNote: Usage of U8 is optional, adc circuit to monitor\n      various supply voltages, usage of U2 is optional\n      circuit to indicate which channel is selected.
Text Notes 690  7405 0    39   ~ 0
Fixes: U8 ->M3V6, fixed traces which where little close
Text Notes 695  7105 0    39   ~ 0
R1...R4: For BAT62 diode  use 110 or 113 ohms\n              For 1SS351 diode use 82.5 ohms.\n              D5 diode could be the same as D1, D2.\n
$Comp
L Device:R_Small R30
U 1 1 61397D78
P 6750 900
F 0 "R30" V 6830 870 50  0000 C CNN
F 1 "0" V 6745 895 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6750 900 50  0001 C CNN
F 3 "~" H 6750 900 50  0001 C CNN
	1    6750 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6600 900  6650 900 
$Comp
L Device:R_Small R40
U 1 1 61468949
P 9100 900
F 0 "R40" V 9180 870 50  0000 C CNN
F 1 "0" V 9095 895 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9100 900 50  0001 C CNN
F 3 "~" H 9100 900 50  0001 C CNN
	1    9100 900 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R36
U 1 1 614D15DC
P 8050 3850
F 0 "R36" V 7975 3745 50  0000 C CNN
F 1 "4K7" V 7975 3890 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8050 3850 50  0001 C CNN
F 3 "~" H 8050 3850 50  0001 C CNN
	1    8050 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R37
U 1 1 614D37F3
P 8150 3850
F 0 "R37" V 8220 3745 50  0000 C CNN
F 1 "4K7" V 8220 3880 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8150 3850 50  0001 C CNN
F 3 "~" H 8150 3850 50  0001 C CNN
	1    8150 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 3950 8050 4050
Connection ~ 8050 4050
Wire Wire Line
	8050 4050 7650 4050
Wire Wire Line
	8150 3950 8150 4150
Connection ~ 8150 4150
Wire Wire Line
	8150 4150 7750 4150
Wire Wire Line
	8150 3700 8050 3700
Wire Wire Line
	8050 3750 8050 3700
Connection ~ 8050 3700
Wire Wire Line
	8050 3700 7850 3700
Wire Wire Line
	8150 3750 8150 3700
Wire Wire Line
	7100 3200 7100 3850
Wire Wire Line
	7100 3850 6600 3850
Wire Wire Line
	7100 3200 7000 3200
Connection ~ 6600 3850
Wire Wire Line
	6600 3850 6600 4250
Text GLabel 7850 3700 0    39   Input ~ 0
D3V3DD
Text Notes 700  7210 0    39   ~ 0
R33 & R34 are optional, value 4k7 up to 10K
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
D3V3R
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
Text GLabel 4450 3100 2    39   Input ~ 0
D3V3R
Wire Wire Line
	4450 3100 4400 3100
Text GLabel 4450 3300 2    39   Input ~ 0
Att_B
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
	6155 4850 6060 4850
Wire Wire Line
	6060 4750 6155 4750
Wire Wire Line
	6060 4650 6155 4650
Wire Wire Line
	2850 4950 2900 4950
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
Text GLabel 4450 4500 2    39   Input ~ 0
D3V3R
Wire Wire Line
	4450 4500 4400 4500
Text GLabel 4450 4700 2    39   Input ~ 0
Att_C
Wire Wire Line
	4450 4700 4400 4700
Wire Wire Line
	2600 5450 2600 5400
Wire Wire Line
	7300 4050 7300 4650
Connection ~ 7300 4050
Text GLabel 6060 4850 0    39   Input ~ 0
Att_C
Text GLabel 6060 4750 0    39   Input ~ 0
Att_B
Text GLabel 6060 4650 0    39   Input ~ 0
Att_A
NoConn ~ 6155 4950
Wire Wire Line
	3950 5200 3900 5200
Wire Wire Line
	3950 5200 3950 5400
Wire Wire Line
	6850 900  6900 900 
Text GLabel 6400 750  0    39   Input ~ 0
AV3V6DD
Wire Wire Line
	6400 750  6450 750 
Wire Wire Line
	6450 750  6450 900 
Connection ~ 6450 900 
Wire Wire Line
	9200 900  9250 900 
Wire Wire Line
	6450 650  6450 750 
Connection ~ 6450 750 
$Comp
L power:PWR_FLAG #FLG05
U 1 1 60761F55
P 8950 650
F 0 "#FLG05" H 8950 725 50  0001 C CNN
F 1 "PWR_FLAG" H 9185 725 50  0000 C CNN
F 2 "" H 8950 650 50  0001 C CNN
F 3 "~" H 8950 650 50  0001 C CNN
	1    8950 650 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 650  8950 750 
Wire Wire Line
	8900 750  8950 750 
Connection ~ 8950 750 
Wire Wire Line
	8950 750  8950 900 
Text GLabel 8500 4250 0    39   Input ~ 0
Att_Ena
Wire Wire Line
	8550 4000 8550 4250
Wire Wire Line
	8550 4250 8500 4250
Wire Wire Line
	8350 1205 8350 1300
$Comp
L Device:CP_Small C34
U 1 1 6419EE43
P 8350 1105
F 0 "C34" H 8295 1200 50  0000 L CNN
F 1 "10u" H 8305 1025 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8350 1105 50  0001 C CNN
F 3 "~" H 8350 1105 50  0001 C CNN
	1    8350 1105
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C33
U 1 1 6419EE4D
P 8200 1100
F 0 "C33" H 8145 1190 50  0000 L CNN
F 1 "100n" H 8100 1020 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8200 1100 50  0001 C CNN
F 3 "~" H 8200 1100 50  0001 C CNN
	1    8200 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1300 8200 1200
Wire Wire Line
	8200 1000 8200 900 
Connection ~ 8200 900 
Wire Wire Line
	8200 900  8350 900 
Wire Wire Line
	8350 900  8350 1005
Wire Wire Line
	8150 900  8200 900 
Wire Wire Line
	9700 1200 9700 1000
Wire Wire Line
	7050 900  7200 900 
Wire Wire Line
	7100 800  7050 800 
Wire Wire Line
	7050 800  7050 900 
Wire Wire Line
	7300 800  7300 1000
Wire Wire Line
	7300 1000 7350 1000
Wire Wire Line
	7300 1100 7300 1300
Wire Wire Line
	7300 1300 7200 1300
Wire Wire Line
	7200 1150 7200 1300
Wire Wire Line
	10650 900  10800 900 
Connection ~ 10650 1000
Text GLabel 10900 900  2    39   Input ~ 0
D7VDD
Wire Wire Line
	10800 900  10900 900 
Text GLabel 10900 5205 2    39   Input ~ 0
D7VDD
Wire Wire Line
	10900 5205 10800 5205
Connection ~ 10800 5400
Text GLabel 8650 2500 0    39   Input ~ 0
AV3V6DD
Wire Wire Line
	8650 2500 8750 2500
Wire Wire Line
	8750 2500 8750 2700
Connection ~ 8750 2700
$Comp
L Device:C_Small C37
U 1 1 649FB343
P 8900 2650
F 0 "C37" H 8915 2715 50  0000 L CNN
F 1 "100n" H 8905 2555 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8900 2650 50  0001 C CNN
F 3 "~" H 8900 2650 50  0001 C CNN
	1    8900 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 2750 8900 2800
Wire Wire Line
	8900 2550 8900 2500
Wire Wire Line
	8900 2500 8750 2500
Connection ~ 8750 2500
Wire Wire Line
	2900 4950 5800 4950
$Comp
L Diode:BAT54S D3
U 1 1 60DBE473
P 2900 5400
F 0 "D3" H 2745 5510 50  0000 L CNN
F 1 "BAT62" H 2875 5505 50  0000 L CNN
F 2 "DigiKey:SOT-143-4-SPC" H 2975 5525 50  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds11005.pdf" H 2780 5400 50  0001 C CNN
	1    2900 5400
	1    0    0    1   
$EndComp
Wire Wire Line
	2900 5200 2900 4950
Connection ~ 2900 4950
Text GLabel 8450 900  2    39   Input ~ 0
D7VDD
Wire Wire Line
	8450 900  8350 900 
Connection ~ 8350 900 
Wire Wire Line
	5500 5750 5500 5950
Wire Wire Line
	3100 4100 3200 4100
$Comp
L power:PWR_FLAG #FLG01
U 1 1 655ADE53
P 4050 5200
F 0 "#FLG01" H 4050 5275 50  0001 C CNN
F 1 "PWR_FLAG" H 4060 5235 50  0000 C CNN
F 2 "" H 4050 5200 50  0001 C CNN
F 3 "~" H 4050 5200 50  0001 C CNN
	1    4050 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 5200 3950 5200
Connection ~ 3950 5200
$Comp
L power:GND #PWR050
U 1 1 6567BF83
P 9050 4300
F 0 "#PWR050" H 9050 4050 50  0001 C CNN
F 1 "GND" H 9055 4127 50  0000 C CNN
F 2 "" H 9050 4300 50  0001 C CNN
F 3 "" H 9050 4300 50  0001 C CNN
	1    9050 4300
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
L power:GND #PWR012
U 1 1 65698EA4
P 2600 5200
F 0 "#PWR012" H 2600 4950 50  0001 C CNN
F 1 "GND" H 2605 5027 50  0000 C CNN
F 2 "" H 2600 5200 50  0001 C CNN
F 3 "" H 2600 5200 50  0001 C CNN
	1    2600 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 65699AF6
P 2600 5450
F 0 "#PWR013" H 2600 5200 50  0001 C CNN
F 1 "GND" H 2605 5277 50  0000 C CNN
F 2 "" H 2600 5450 50  0001 C CNN
F 3 "" H 2600 5450 50  0001 C CNN
	1    2600 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR052
U 1 1 65720F78
P 9250 4300
F 0 "#PWR052" H 9250 4050 50  0001 C CNN
F 1 "GND" H 9255 4127 50  0000 C CNN
F 2 "" H 9250 4300 50  0001 C CNN
F 3 "" H 9250 4300 50  0001 C CNN
	1    9250 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR048
U 1 1 65765B35
P 8900 2800
F 0 "#PWR048" H 8900 2550 50  0001 C CNN
F 1 "GND" H 9065 2720 50  0000 C CNN
F 2 "" H 8900 2800 50  0001 C CNN
F 3 "" H 8900 2800 50  0001 C CNN
	1    8900 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR037
U 1 1 6576905B
P 6600 4250
F 0 "#PWR037" H 6600 4000 50  0001 C CNN
F 1 "GND" H 6605 4077 50  0000 C CNN
F 2 "" H 6600 4250 50  0001 C CNN
F 3 "" H 6600 4250 50  0001 C CNN
	1    6600 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 6576AD3A
P 6100 4250
F 0 "#PWR032" H 6100 4000 50  0001 C CNN
F 1 "GND" H 6105 4077 50  0000 C CNN
F 2 "" H 6100 4250 50  0001 C CNN
F 3 "" H 6100 4250 50  0001 C CNN
	1    6100 4250
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
P 6450 1300
F 0 "#PWR035" H 6450 1050 50  0001 C CNN
F 1 "GND" H 6455 1127 50  0000 C CNN
F 2 "" H 6450 1300 50  0001 C CNN
F 3 "" H 6450 1300 50  0001 C CNN
	1    6450 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 657B388F
P 3950 5700
F 0 "#PWR017" H 3950 5450 50  0001 C CNN
F 1 "GND" H 3955 5527 50  0000 C CNN
F 2 "" H 3950 5700 50  0001 C CNN
F 3 "" H 3950 5700 50  0001 C CNN
	1    3950 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 657B4D53
P 4350 5700
F 0 "#PWR019" H 4350 5450 50  0001 C CNN
F 1 "GND" H 4355 5527 50  0000 C CNN
F 2 "" H 4350 5700 50  0001 C CNN
F 3 "" H 4350 5700 50  0001 C CNN
	1    4350 5700
	1    0    0    -1  
$EndComp
Text GLabel 5800 5300 2    39   Input ~ 0
AV3V6DD
Wire Wire Line
	5650 5300 5800 5300
Connection ~ 5650 5300
Wire Wire Line
	3200 5400 3250 5400
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
Wire Wire Line
	5950 3850 5550 3850
Connection ~ 5550 3850
Wire Wire Line
	5850 3650 5600 3650
Wire Wire Line
	5850 2400 5850 3650
Connection ~ 5600 3650
Wire Wire Line
	5900 2450 5900 3600
Wire Wire Line
	6000 2250 6000 2800
Wire Wire Line
	5950 3200 5950 3850
Wire Notes Line
	655  4400 2380 4395
Wire Notes Line
	625  3495 2350 3490
Wire Wire Line
	10250 6100 10250 6050
Wire Wire Line
	10050 6050 9850 6050
Connection ~ 10050 6050
Wire Wire Line
	9850 6050 9650 6050
Connection ~ 9850 6050
Wire Wire Line
	9650 6050 9450 6050
Connection ~ 9650 6050
Wire Wire Line
	9450 6050 9250 6050
Connection ~ 9450 6050
Wire Wire Line
	9250 6050 9050 6050
Connection ~ 9250 6050
Wire Wire Line
	9050 6050 8850 6050
Connection ~ 9050 6050
Wire Wire Line
	8850 6050 8650 6050
Connection ~ 8850 6050
Wire Wire Line
	10900 5350 10900 5450
Wire Wire Line
	10800 5205 10800 5400
Wire Wire Line
	9800 3450 9800 5000
Wire Wire Line
	9900 3550 9900 5050
Wire Wire Line
	10000 3350 10000 5100
Wire Wire Line
	10100 3250 10100 5150
Wire Wire Line
	10300 3650 10300 5250
$Comp
L Connector_Generic:Conn_01x12 J7
U 1 1 613B7209
P 10300 5700
F 0 "J7" V 10300 6305 50  0000 C CNN
F 1 "MCU interface" V 10450 5685 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 10300 5700 50  0001 C CNN
F 3 "~" H 10300 5700 50  0001 C CNN
	1    10300 5700
	0    -1   1    0   
$EndComp
Wire Wire Line
	10400 5400 10400 5500
Wire Wire Line
	10500 5350 10500 5500
Wire Wire Line
	10400 5400 10800 5400
Wire Wire Line
	10500 5350 10900 5350
NoConn ~ 10600 5500
NoConn ~ 10700 5500
Wire Wire Line
	10800 5400 11000 5400
Wire Wire Line
	11000 5400 11000 6000
Wire Wire Line
	9350 5150 10100 5150
Connection ~ 10100 5150
Wire Wire Line
	10100 5150 10100 5500
Wire Wire Line
	9150 5100 10000 5100
Connection ~ 10000 5100
Wire Wire Line
	10000 5100 10000 5500
Wire Wire Line
	8950 5050 9900 5050
Connection ~ 9900 5050
Wire Wire Line
	9900 5050 9900 5500
Wire Wire Line
	8750 5000 9800 5000
Connection ~ 9800 5000
Wire Wire Line
	9800 5000 9800 5500
Wire Wire Line
	10200 3150 10200 5200
Wire Wire Line
	9550 5200 10200 5200
Connection ~ 10200 5200
Wire Wire Line
	10200 5200 10200 5500
Wire Wire Line
	9750 6000 9650 6000
Wire Wire Line
	9650 6000 9650 5250
Wire Wire Line
	9650 5250 10300 5250
Connection ~ 10300 5250
Wire Wire Line
	10300 5250 10300 5500
Wire Wire Line
	9950 6000 10150 6000
Text Notes 10570 1655 0    39   ~ 0
3V3 regulator\ninstall either one
Text Notes 4305 6140 0    39   ~ 0
1V8 Vref regulator
$Comp
L 74xx:74LS139 U4
U 2 1 6207067D
P 7150 5600
F 0 "U4" H 7150 5967 50  0000 C CNN
F 1 "74LVC139" H 7150 5876 50  0000 C CNN
F 2 "SMD_Packages:SO-16-N" H 7150 5600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74ls139a.pdf" H 7150 5600 50  0001 C CNN
	2    7150 5600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7155 4750 7200 4750
Wire Wire Line
	7200 4750 7200 4150
Connection ~ 7200 4150
Wire Wire Line
	7155 4650 7300 4650
Text GLabel 8525 4750 2    39   Input ~ 0
D3V3DD
Wire Wire Line
	8120 4750 8225 4750
Text GLabel 8120 4750 0    39   Input ~ 0
D3V3R
$Comp
L Device:R_Small R39
U 1 1 61023FD2
P 8325 4750
F 0 "R39" V 8255 4675 50  0000 L CNN
F 1 "270" V 8395 4680 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8325 4750 50  0001 C CNN
F 3 "~" H 8325 4750 50  0001 C CNN
	1    8325 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 5800 7700 5800
Wire Wire Line
	7700 5800 7700 5900
Wire Wire Line
	8300 6155 8300 6100
Wire Wire Line
	8425 4750 8450 4750
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
P 10100 1800
F 0 "U10" H 9790 1710 50  0000 C CNN
F 1 "AMS1117-3.3" H 10100 1951 50  0000 C CNN
F 2 "DigiKey:SOT-223-4" H 10100 2000 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 10200 1550 50  0001 C CNN
	1    10100 1800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9800 1800 9650 1800
Wire Wire Line
	9650 1800 9650 900 
Connection ~ 9650 900 
Wire Wire Line
	9650 900  9700 900 
Wire Wire Line
	10400 1800 10550 1800
Wire Wire Line
	10550 1800 10550 900 
Connection ~ 10550 900 
Wire Wire Line
	10550 900  10650 900 
Wire Wire Line
	10100 2100 10100 2200
Wire Wire Line
	8115 4950 8220 4950
Text GLabel 8115 4950 0    39   Input ~ 0
D3V3LED
$Comp
L Device:R_Small R38
U 1 1 624DBEDB
P 8320 4950
F 0 "R38" V 8250 4875 50  0000 L CNN
F 1 "270" V 8390 4880 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8320 4950 50  0001 C CNN
F 3 "~" H 8320 4950 50  0001 C CNN
	1    8320 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	8420 4950 8450 4950
Wire Wire Line
	8450 4750 8450 4950
Connection ~ 8450 4750
Wire Wire Line
	8450 4750 8525 4750
$Comp
L Connector_Generic:Conn_01x05 J5
U 1 1 625ACED3
P 6400 5600
F 0 "J5" H 6390 5910 50  0000 C CNN
F 1 "Panel Leds" H 6405 5295 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 6400 5600 50  0001 C CNN
F 3 "~" H 6400 5600 50  0001 C CNN
	1    6400 5600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7650 5600 7750 5600
Wire Wire Line
	7750 5600 7750 4150
Connection ~ 7750 4150
Wire Wire Line
	7750 4150 7200 4150
Wire Wire Line
	7650 5500 7650 4050
Connection ~ 7650 4050
Wire Wire Line
	7650 4050 7300 4050
Wire Wire Line
	6600 5500 6650 5500
Wire Wire Line
	6600 5600 6650 5600
Wire Wire Line
	6600 5700 6650 5700
Wire Wire Line
	6600 5800 6650 5800
Text GLabel 6700 5250 2    39   Input ~ 0
D3V3LED
Wire Wire Line
	6700 5250 6650 5250
Wire Wire Line
	6650 5250 6650 5400
Wire Wire Line
	6650 5400 6600 5400
$Comp
L 74xx:74LS139 U4
U 3 1 620724D6
P 8300 5600
F 0 "U4" H 8530 5646 50  0000 L CNN
F 1 "74LVC139" H 8530 5555 50  0000 L CNN
F 2 "SMD_Packages:SO-16-N" H 8300 5600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74ls139a.pdf" H 8300 5600 50  0001 C CNN
	3    8300 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 4950 8450 5050
Wire Wire Line
	8450 5050 8300 5050
Wire Wire Line
	8300 5050 8300 5100
Connection ~ 8450 4950
$Comp
L power:GND #PWR0101
U 1 1 62095C02
P 6600 1300
F 0 "#PWR0101" H 6600 1050 50  0001 C CNN
F 1 "GND" H 6605 1127 50  0000 C CNN
F 2 "" H 6600 1300 50  0001 C CNN
F 3 "" H 6600 1300 50  0001 C CNN
	1    6600 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 62097D05
P 6900 1300
F 0 "#PWR0102" H 6900 1050 50  0001 C CNN
F 1 "GND" H 6905 1127 50  0000 C CNN
F 2 "" H 6900 1300 50  0001 C CNN
F 3 "" H 6900 1300 50  0001 C CNN
	1    6900 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 620991FE
P 7050 1300
F 0 "#PWR0103" H 7050 1050 50  0001 C CNN
F 1 "GND" H 7055 1127 50  0000 C CNN
F 2 "" H 7050 1300 50  0001 C CNN
F 3 "" H 7050 1300 50  0001 C CNN
	1    7050 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1400 7600 1450
$Comp
L power:GND #PWR0104
U 1 1 6209CB2F
P 7600 1450
F 0 "#PWR0104" H 7600 1200 50  0001 C CNN
F 1 "GND" H 7605 1277 50  0000 C CNN
F 2 "" H 7600 1450 50  0001 C CNN
F 3 "" H 7600 1450 50  0001 C CNN
	1    7600 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 6209E1AD
P 7750 1450
F 0 "#PWR0105" H 7750 1200 50  0001 C CNN
F 1 "GND" H 7755 1277 50  0000 C CNN
F 2 "" H 7750 1450 50  0001 C CNN
F 3 "" H 7750 1450 50  0001 C CNN
	1    7750 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 6209F598
P 4550 5700
F 0 "#PWR0106" H 4550 5450 50  0001 C CNN
F 1 "GND" H 4555 5527 50  0000 C CNN
F 2 "" H 4550 5700 50  0001 C CNN
F 3 "" H 4550 5700 50  0001 C CNN
	1    4550 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 620A3099
P 5050 5950
F 0 "#PWR0107" H 5050 5700 50  0001 C CNN
F 1 "GND" H 5055 5777 50  0000 C CNN
F 2 "" H 5050 5950 50  0001 C CNN
F 3 "" H 5050 5950 50  0001 C CNN
	1    5050 5950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 620A4449
P 5500 5950
F 0 "#PWR0108" H 5500 5700 50  0001 C CNN
F 1 "GND" H 5505 5777 50  0000 C CNN
F 2 "" H 5500 5950 50  0001 C CNN
F 3 "" H 5500 5950 50  0001 C CNN
	1    5500 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R43
U 1 1 620A9EE6
P 7750 650
F 0 "R43" V 7830 620 50  0000 C CNN
F 1 "0" V 7745 645 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 7750 650 50  0001 C CNN
F 3 "~" H 7750 650 50  0001 C CNN
	1    7750 650 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7850 650  8200 650 
Wire Wire Line
	8200 650  8200 900 
Wire Wire Line
	7650 650  7300 650 
Wire Wire Line
	7300 650  7300 800 
Connection ~ 7300 800 
$Comp
L power:GND #PWR028
U 1 1 6213F055
P 8200 1300
F 0 "#PWR028" H 8200 1050 50  0001 C CNN
F 1 "GND" H 8205 1127 50  0000 C CNN
F 2 "" H 8200 1300 50  0001 C CNN
F 3 "" H 8200 1300 50  0001 C CNN
	1    8200 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 6218C4C4
P 7100 2150
F 0 "#PWR027" H 7100 1900 50  0001 C CNN
F 1 "GND" H 7105 1977 50  0000 C CNN
F 2 "" H 7100 2150 50  0001 C CNN
F 3 "" H 7100 2150 50  0001 C CNN
	1    7100 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 6218DCE8
P 5650 5950
F 0 "#PWR026" H 5650 5700 50  0001 C CNN
F 1 "GND" H 5655 5777 50  0000 C CNN
F 2 "" H 5650 5950 50  0001 C CNN
F 3 "" H 5650 5950 50  0001 C CNN
	1    5650 5950
	1    0    0    -1  
$EndComp
Text Notes 7495 1870 0    39   ~ 0
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
L power:GND #PWR0110
U 1 1 6297E5E2
P 8400 2800
F 0 "#PWR0110" H 8400 2550 50  0001 C CNN
F 1 "GND" H 8305 2635 50  0000 C CNN
F 2 "" H 8400 2800 50  0001 C CNN
F 3 "" H 8400 2800 50  0001 C CNN
	1    8400 2800
	1    0    0    -1  
$EndComp
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
P 8350 1300
F 0 "#PWR0111" H 8350 1050 50  0001 C CNN
F 1 "GND" H 8354 1145 50  0000 C CNN
F 2 "" H 8350 1300 50  0001 C CNN
F 3 "" H 8350 1300 50  0001 C CNN
	1    8350 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 6210DC11
P 9700 2800
F 0 "#PWR0112" H 9700 2550 50  0001 C CNN
F 1 "GND" H 9704 2645 50  0000 C CNN
F 2 "" H 9700 2800 50  0001 C CNN
F 3 "" H 9700 2800 50  0001 C CNN
	1    9700 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 6210F010
P 9850 2800
F 0 "#PWR0113" H 9850 2550 50  0001 C CNN
F 1 "GND" H 9854 2645 50  0000 C CNN
F 2 "" H 9850 2800 50  0001 C CNN
F 3 "" H 9850 2800 50  0001 C CNN
	1    9850 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 62110903
P 9250 1300
F 0 "#PWR0114" H 9250 1050 50  0001 C CNN
F 1 "GND" H 9254 1145 50  0000 C CNN
F 2 "" H 9250 1300 50  0001 C CNN
F 3 "" H 9250 1300 50  0001 C CNN
	1    9250 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 62114241
P 9400 1300
F 0 "#PWR0115" H 9400 1050 50  0001 C CNN
F 1 "GND" H 9404 1145 50  0000 C CNN
F 2 "" H 9400 1300 50  0001 C CNN
F 3 "" H 9400 1300 50  0001 C CNN
	1    9400 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 62115F9A
P 10100 1350
F 0 "#PWR0116" H 10100 1100 50  0001 C CNN
F 1 "GND" H 10104 1195 50  0000 C CNN
F 2 "" H 10100 1350 50  0001 C CNN
F 3 "" H 10100 1350 50  0001 C CNN
	1    10100 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 62166D1F
P 10650 1300
F 0 "#PWR0117" H 10650 1050 50  0001 C CNN
F 1 "GND" H 10654 1145 50  0000 C CNN
F 2 "" H 10650 1300 50  0001 C CNN
F 3 "" H 10650 1300 50  0001 C CNN
	1    10650 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 62168601
P 10800 1300
F 0 "#PWR0118" H 10800 1050 50  0001 C CNN
F 1 "GND" H 10804 1145 50  0000 C CNN
F 2 "" H 10800 1300 50  0001 C CNN
F 3 "" H 10800 1300 50  0001 C CNN
	1    10800 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 6210B4BB
P 7700 5900
F 0 "#PWR0119" H 7700 5650 50  0001 C CNN
F 1 "GND" H 7704 5745 50  0000 C CNN
F 2 "" H 7700 5900 50  0001 C CNN
F 3 "" H 7700 5900 50  0001 C CNN
	1    7700 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 621B8DE3
P 10100 2200
F 0 "#PWR0120" H 10100 1950 50  0001 C CNN
F 1 "GND" H 10104 2045 50  0000 C CNN
F 2 "" H 10100 2200 50  0001 C CNN
F 3 "" H 10100 2200 50  0001 C CNN
	1    10100 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 621BA4E2
P 8600 5200
F 0 "#PWR0121" H 8600 4950 50  0001 C CNN
F 1 "GND" H 8604 5045 50  0000 C CNN
F 2 "" H 8600 5200 50  0001 C CNN
F 3 "" H 8600 5200 50  0001 C CNN
	1    8600 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 621BCA02
P 9450 4300
F 0 "#PWR0122" H 9450 4050 50  0001 C CNN
F 1 "GND" H 9454 4145 50  0000 C CNN
F 2 "" H 9450 4300 50  0001 C CNN
F 3 "" H 9450 4300 50  0001 C CNN
	1    9450 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 621BED25
P 8300 6155
F 0 "#PWR0123" H 8300 5905 50  0001 C CNN
F 1 "GND" H 8304 6000 50  0000 C CNN
F 2 "" H 8300 6155 50  0001 C CNN
F 3 "" H 8300 6155 50  0001 C CNN
	1    8300 6155
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
P 11100 5500
F 0 "#PWR0125" H 11100 5250 50  0001 C CNN
F 1 "GND" H 11104 5345 50  0000 C CNN
F 2 "" H 11100 5500 50  0001 C CNN
F 3 "" H 11100 5500 50  0001 C CNN
	1    11100 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	11100 5450 11100 5500
$Comp
L power:GND #PWR0126
U 1 1 6226313A
P 10250 6100
F 0 "#PWR0126" H 10250 5850 50  0001 C CNN
F 1 "GND" H 10254 5945 50  0000 C CNN
F 2 "" H 10250 6100 50  0001 C CNN
F 3 "" H 10250 6100 50  0001 C CNN
	1    10250 6100
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 623536AB
P 5850 5750
F 0 "#FLG02" H 5850 5825 50  0001 C CNN
F 1 "PWR_FLAG" H 5955 5880 50  0000 C CNN
F 2 "" H 5850 5750 50  0001 C CNN
F 3 "~" H 5850 5750 50  0001 C CNN
	1    5850 5750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 624491F2
P 5850 5950
F 0 "#PWR0127" H 5850 5700 50  0001 C CNN
F 1 "GND" H 5854 5795 50  0000 C CNN
F 2 "" H 5850 5950 50  0001 C CNN
F 3 "" H 5850 5950 50  0001 C CNN
	1    5850 5950
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
	5850 5750 5850 5950
$Comp
L 74xx:74LS139 U4
U 1 1 6206E129
P 6655 4750
F 0 "U4" H 6775 5005 50  0000 C CNN
F 1 "74LVC139" H 6645 4405 50  0000 C CNN
F 2 "SMD_Packages:SO-16-N" H 6655 4750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74ls139a.pdf" H 6655 4750 50  0001 C CNN
	1    6655 4750
	-1   0    0    -1  
$EndComp
Text GLabel 7200 4950 2    39   Input ~ 0
Att_Ena
Wire Wire Line
	7155 4950 7200 4950
Wire Wire Line
	9350 2800 9350 2700
Wire Wire Line
	9450 2800 9450 2500
Wire Wire Line
	8750 2700 8750 2800
$Comp
L My-Analog:MAX11270 U8
U 1 1 607364BB
P 8950 3350
F 0 "U8" H 8390 2890 50  0000 R CNN
F 1 "MAX11270" H 9130 3405 50  0000 R CNN
F 2 "DigiKey:TSSOP-24_W4.40mm" H 8770 3360 50  0001 C CNN
F 3 "" H 8770 3360 50  0001 C CNN
	1    8950 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 2500 9700 2500
Wire Wire Line
	8600 5200 8600 5150
Wire Wire Line
	8600 4950 8450 4950
Connection ~ 9700 2500
Wire Wire Line
	9700 2500 9845 2500
Connection ~ 9845 2500
Wire Wire Line
	9845 2500 10050 2500
Wire Wire Line
	8950 900  9000 900 
Wire Wire Line
	9450 6050 9450 6100
Wire Wire Line
	9350 6100 9350 5150
Wire Wire Line
	9250 6050 9250 6100
Wire Wire Line
	9150 6100 9150 5100
Wire Wire Line
	9050 6050 9050 6100
Wire Wire Line
	8950 6100 8950 5050
Wire Wire Line
	8850 6050 8850 6100
Wire Wire Line
	8750 6100 8750 5000
Wire Wire Line
	10050 6100 10050 6050
Wire Wire Line
	9950 6100 9950 6000
Wire Wire Line
	9850 6050 9850 6100
Wire Wire Line
	9750 6100 9750 6000
Wire Wire Line
	9650 6050 9650 6100
Wire Wire Line
	9550 6100 9550 5200
Wire Wire Line
	8650 6050 8650 6100
$Comp
L Connector:Conn_01x16_Female J6
U 1 1 626A4827
P 9350 6300
F 0 "J6" V 9310 7110 50  0000 C CNN
F 1 "FFC MCU Interface" V 9470 6300 50  0000 C CNN
F 2 "Connector_FFC:TE_1-84952-6_1x16-1MP_P1.0mm_Horizontal" H 9350 6300 50  0001 C CNN
F 3 "~" H 9350 6300 50  0001 C CNN
	1    9350 6300
	0    -1   1    0   
$EndComp
Wire Wire Line
	10050 6050 10250 6050
Wire Wire Line
	10150 6100 10150 6000
Connection ~ 10150 6000
Wire Wire Line
	10150 6000 11000 6000
Text Notes 3100 6300 0    39   ~ 0
Use R29 to trim voltage\ndown to 1.3V max\nAlternative to regulator usage\nis to short pad 4 & 5, omit\nC24 and adjust R29 value to\nset voltage @ 1V3 for VPre
$EndSCHEMATC

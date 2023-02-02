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
L Mechanical:MountingHole H1
U 1 1 60B498C1
P 1000 1500
F 0 "H1" H 1100 1546 50  0000 L CNN
F 1 "MountingHole" H 1100 1455 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 1000 1500 50  0001 C CNN
F 3 "~" H 1000 1500 50  0001 C CNN
	1    1000 1500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 60B49C63
P 1000 2000
F 0 "H3" H 1100 2046 50  0000 L CNN
F 1 "MountingHole" H 1100 1955 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 1000 2000 50  0001 C CNN
F 3 "~" H 1000 2000 50  0001 C CNN
	1    1000 2000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 60B4A0AF
P 2000 1500
F 0 "H2" H 2100 1546 50  0000 L CNN
F 1 "MountingHole" H 2100 1455 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 2000 1500 50  0001 C CNN
F 3 "~" H 2000 1500 50  0001 C CNN
	1    2000 1500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 60B4A5A5
P 2000 2000
F 0 "H4" H 2100 2046 50  0000 L CNN
F 1 "MountingHole" H 2100 1955 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_Pad_Via" H 2000 2000 50  0001 C CNN
F 3 "~" H 2000 2000 50  0001 C CNN
	1    2000 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 60D3233A
P 4700 2100
F 0 "BT1" H 4818 2196 50  0000 L CNN
F 1 "Li-Ion 18650" H 4818 2105 50  0000 L CNN
F 2 "User:Battery_Holder_2S" V 4700 2160 50  0001 C CNN
F 3 "~" V 4700 2160 50  0001 C CNN
	1    4700 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT2
U 1 1 60D32BE6
P 4700 2500
F 0 "BT2" H 4818 2596 50  0000 L CNN
F 1 "Li-Ion 18650" H 4818 2505 50  0000 L CNN
F 2 "User:Battery_Holder_2S" V 4700 2560 50  0001 C CNN
F 3 "~" V 4700 2560 50  0001 C CNN
	1    4700 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2200 4700 2250
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 60D35757
P 5500 2250
F 0 "J1" H 5580 2292 50  0000 L CNN
F 1 "Bat_Cntrl" H 5580 2201 50  0000 L CNN
F 2 "DigiKey:PinHeader_1x3_P2.54_Drill1.1mm" H 5500 2250 50  0001 C CNN
F 3 "~" H 5500 2250 50  0001 C CNN
	1    5500 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2250 5300 2250
Connection ~ 4700 2250
Wire Wire Line
	4700 2250 4700 2300
Wire Wire Line
	4700 1900 5300 1900
Wire Wire Line
	5300 1900 5300 2150
Wire Wire Line
	4700 2600 5300 2600
Wire Wire Line
	5300 2600 5300 2350
$Comp
L power:GND #PWR0101
U 1 1 60D3C480
P 3150 2200
F 0 "#PWR0101" H 3150 1950 50  0001 C CNN
F 1 "GND" H 3155 2027 50  0000 C CNN
F 2 "" H 3150 2200 50  0001 C CNN
F 3 "" H 3150 2200 50  0001 C CNN
	1    3150 2200
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 60D3CA63
P 3150 1850
F 0 "#FLG0101" H 3150 1925 50  0001 C CNN
F 1 "PWR_FLAG" H 3150 2023 50  0000 C CNN
F 2 "" H 3150 1850 50  0001 C CNN
F 3 "~" H 3150 1850 50  0001 C CNN
	1    3150 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1850 3150 2200
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 60D282AA
P 4050 2250
F 0 "J2" H 3968 2567 50  0000 C CNN
F 1 "Bat_Test" H 3968 2476 50  0000 C CNN
F 2 "DigiKey:PinHeader_1x4_P2.54mm_Drill1.02mm" H 4050 2250 50  0001 C CNN
F 3 "~" H 4050 2250 50  0001 C CNN
	1    4050 2250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4250 2250 4700 2250
Wire Wire Line
	4250 2150 4350 2150
Wire Wire Line
	4350 2150 4350 1900
Wire Wire Line
	4350 1900 4700 1900
Connection ~ 4700 1900
Wire Wire Line
	4250 2350 4350 2350
Wire Wire Line
	4350 2350 4350 2600
Wire Wire Line
	4350 2600 4700 2600
Connection ~ 4700 2600
Wire Wire Line
	4250 2450 4250 2600
$Comp
L power:GND #PWR0102
U 1 1 60D2F594
P 4250 2600
F 0 "#PWR0102" H 4250 2350 50  0001 C CNN
F 1 "GND" H 4255 2427 50  0000 C CNN
F 2 "" H 4250 2600 50  0001 C CNN
F 3 "" H 4250 2600 50  0001 C CNN
	1    4250 2600
	1    0    0    -1  
$EndComp
Text Notes 8375 7645 0    50   ~ 0
7-jun-2021 / v1.2
$Comp
L power:GND #PWR0103
U 1 1 61599C8E
P 1500 2250
F 0 "#PWR0103" H 1500 2000 50  0001 C CNN
F 1 "GND" H 1505 2077 50  0000 C CNN
F 2 "" H 1500 2250 50  0001 C CNN
F 3 "" H 1500 2250 50  0001 C CNN
	1    1500 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2200 1500 2200
Wire Wire Line
	1500 2200 1500 2250
Wire Wire Line
	2000 1500 2000 2200
Wire Wire Line
	1000 2200 1500 2200
Wire Wire Line
	1000 1500 1000 2200
Connection ~ 1500 2200
$EndSCHEMATC

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title "FLASH"
Date "2022-03-19"
Rev "Rev. 1"
Comp "HardGFX"
Comment1 "Esp. Eng. Sciarrone, Hanes Nahuel"
Comment2 "Magister in embedded systems"
Comment3 "UBA - Facultad de Ingeniería"
Comment4 ""
$EndDescr
$Comp
L MT25QL512ABB8ESF-0AAT:MT25QL512ABB8ESF-0AAT U5
U 1 1 62388A92
P 2700 1750
F 0 "U5" H 3800 2037 60  0000 C CNN
F 1 "MT25QL512ABB8ESF-0AAT" H 3800 1931 60  0000 C CNN
F 2 "MT25QL512ABB8ESF-0AAT:MT25QL512ABB8ESF-0AAT" H 3800 1990 60  0001 C CNN
F 3 "https://media-www.micron.com/-/media/client/global/documents/products/data-sheet/nor-flash/serial-nor/mt25q/die-rev-b/mt25q_qlkt_l_512_abb_0.pdf" H 2700 1750 60  0001 C CNN
F 4 "MICRON" H 2700 1750 50  0001 C CNN "MANUFACTURER"
F 5 "" H 2700 1750 50  0001 C CNN "digikey#"
F 6 "MT25QL512ABB8ESF-0AAT" H 2700 1750 50  0001 C CNN "manf#"
F 7 "" H 2700 1750 50  0001 C CNN "mouser#"
	1    2700 1750
	1    0    0    -1  
$EndComp
$Comp
L MT25QL512ABB8ESF-0AAT:MT25QL512ABB8ESF-0AAT U6
U 1 1 62389932
P 7500 1750
F 0 "U6" H 8600 2037 60  0000 C CNN
F 1 "MT25QL512ABB8ESF-0AAT" H 8600 1931 60  0000 C CNN
F 2 "MT25QL512ABB8ESF-0AAT:MT25QL512ABB8ESF-0AAT" H 8600 1990 60  0001 C CNN
F 3 "https://media-www.micron.com/-/media/client/global/documents/products/data-sheet/nor-flash/serial-nor/mt25q/die-rev-b/mt25q_qlkt_l_512_abb_0.pdf" H 7500 1750 60  0001 C CNN
F 4 "MICRON" H 7500 1750 50  0001 C CNN "MANUFACTURER"
F 5 "" H 7500 1750 50  0001 C CNN "digikey#"
F 6 "MT25QL512ABB8ESF-0AAT" H 7500 1750 50  0001 C CNN "manf#"
F 7 "" H 7500 1750 50  0001 C CNN "mouser#"
	1    7500 1750
	1    0    0    -1  
$EndComp
NoConn ~ 2950 2050
NoConn ~ 7750 2050
$Comp
L power:GNDD #PWR0136
U 1 1 62392004
P 4900 3150
F 0 "#PWR0136" H 4900 2900 50  0001 C CNN
F 1 "GNDD" H 4904 2995 50  0000 C CNN
F 2 "" H 4900 3150 50  0001 C CNN
F 3 "" H 4900 3150 50  0001 C CNN
	1    4900 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0137
U 1 1 62392765
P 9700 3150
F 0 "#PWR0137" H 9700 2900 50  0001 C CNN
F 1 "GNDD" H 9704 2995 50  0000 C CNN
F 2 "" H 9700 3150 50  0001 C CNN
F 3 "" H 9700 3150 50  0001 C CNN
	1    9700 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2650 4900 2650
Wire Wire Line
	4900 2650 4900 3150
Wire Wire Line
	9700 3150 9700 2650
Wire Wire Line
	9700 2650 9450 2650
$Comp
L Device:C C53
U 1 1 62393583
P 1500 2100
F 0 "C53" H 1615 2146 50  0000 L CNN
F 1 "100nf" H 1615 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1538 1950 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/mlcc/UPY-GPHC_X7R_6.3V-to-50V_20.pdf" H 1500 2100 50  0001 C CNN
F 4 "YAGEO" H 1500 2100 50  0001 C CNN "MANUFACTURER"
F 5 "311-1088-1-ND" H 1500 2100 50  0001 C CNN "digikey#"
F 6 "CC0603KRX7R7BB104 " H 1500 2100 50  0001 C CNN "manf#"
F 7 "603-CC603KRX7R7BB104 " H 1500 2100 50  0001 C CNN "mouser#"
	1    1500 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C54
U 1 1 62393F43
P 6300 2100
F 0 "C54" H 6415 2146 50  0000 L CNN
F 1 "100nf" H 6415 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6338 1950 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/mlcc/UPY-GPHC_X7R_6.3V-to-50V_20.pdf" H 6300 2100 50  0001 C CNN
F 4 "YAGEO" H 6300 2100 50  0001 C CNN "MANUFACTURER"
F 5 "311-1088-1-ND" H 6300 2100 50  0001 C CNN "digikey#"
F 6 "CC0603KRX7R7BB104 " H 6300 2100 50  0001 C CNN "manf#"
F 7 "603-CC603KRX7R7BB104 " H 6300 2100 50  0001 C CNN "mouser#"
	1    6300 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0138
U 1 1 623956A8
P 1500 3150
F 0 "#PWR0138" H 1500 2900 50  0001 C CNN
F 1 "GNDD" H 1504 2995 50  0000 C CNN
F 2 "" H 1500 3150 50  0001 C CNN
F 3 "" H 1500 3150 50  0001 C CNN
	1    1500 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0139
U 1 1 62395C08
P 6300 3150
F 0 "#PWR0139" H 6300 2900 50  0001 C CNN
F 1 "GNDD" H 6304 2995 50  0000 C CNN
F 2 "" H 6300 3150 50  0001 C CNN
F 3 "" H 6300 3150 50  0001 C CNN
	1    6300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 3150 6300 2250
Wire Wire Line
	7750 1900 6300 1900
Wire Wire Line
	6300 1900 6300 1950
Wire Wire Line
	2950 1900 1500 1900
Wire Wire Line
	1500 1900 1500 1950
Wire Wire Line
	1500 2250 1500 3150
$Comp
L power:+3V3 #PWR0140
U 1 1 62398741
P 1500 1450
F 0 "#PWR0140" H 1500 1300 50  0001 C CNN
F 1 "+3V3" H 1515 1623 50  0000 C CNN
F 2 "" H 1500 1450 50  0001 C CNN
F 3 "" H 1500 1450 50  0001 C CNN
	1    1500 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0141
U 1 1 6239970A
P 6300 1450
F 0 "#PWR0141" H 6300 1300 50  0001 C CNN
F 1 "+3V3" H 6315 1623 50  0000 C CNN
F 2 "" H 6300 1450 50  0001 C CNN
F 3 "" H 6300 1450 50  0001 C CNN
	1    6300 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1450 6300 1900
Connection ~ 6300 1900
Wire Wire Line
	1500 1450 1500 1900
Connection ~ 1500 1900
$Comp
L Device:R R65
U 1 1 6239ADC3
P 2450 1750
F 0 "R65" V 2243 1750 50  0000 C CNN
F 1 "33" V 2334 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2380 1750 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 2450 1750 50  0001 C CNN
F 4 "YAGEO" H 2450 1750 50  0001 C CNN "MANUFACTURER"
F 5 "311-33.0HRCT-ND" H 2450 1750 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0733RL" H 2450 1750 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0733RL" H 2450 1750 50  0001 C CNN "mouser#"
	1    2450 1750
	0    1    1    0   
$EndComp
$Comp
L Device:R R66
U 1 1 6239B52D
P 2450 2800
F 0 "R66" V 2550 2800 50  0000 C CNN
F 1 "33" V 2650 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2380 2800 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 2450 2800 50  0001 C CNN
F 4 "YAGEO" H 2450 2800 50  0001 C CNN "MANUFACTURER"
F 5 "311-33.0HRCT-ND" H 2450 2800 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0733RL" H 2450 2800 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0733RL" H 2450 2800 50  0001 C CNN "mouser#"
	1    2450 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R69
U 1 1 6239B951
P 5150 2800
F 0 "R69" V 4943 2800 50  0000 C CNN
F 1 "33" V 5034 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5080 2800 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 5150 2800 50  0001 C CNN
F 4 "YAGEO" H 5150 2800 50  0001 C CNN "MANUFACTURER"
F 5 "311-33.0HRCT-ND" H 5150 2800 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0733RL" H 5150 2800 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0733RL" H 5150 2800 50  0001 C CNN "mouser#"
	1    5150 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R68
U 1 1 6239C27F
P 5150 1900
F 0 "R68" V 5250 1900 50  0000 C CNN
F 1 "33" V 5350 1900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5080 1900 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 5150 1900 50  0001 C CNN
F 4 "YAGEO" H 5150 1900 50  0001 C CNN "MANUFACTURER"
F 5 "311-33.0HRCT-ND" H 5150 1900 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0733RL" H 5150 1900 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0733RL" H 5150 1900 50  0001 C CNN "mouser#"
	1    5150 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R R70
U 1 1 623A4078
P 7250 1750
F 0 "R70" V 7043 1750 50  0000 C CNN
F 1 "33" V 7134 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7180 1750 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 7250 1750 50  0001 C CNN
F 4 "YAGEO" H 7250 1750 50  0001 C CNN "MANUFACTURER"
F 5 "311-33.0HRCT-ND" H 7250 1750 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0733RL" H 7250 1750 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0733RL" H 7250 1750 50  0001 C CNN "mouser#"
	1    7250 1750
	0    1    1    0   
$EndComp
$Comp
L Device:R R71
U 1 1 623A4EF8
P 7250 2800
F 0 "R71" V 7350 2800 50  0000 C CNN
F 1 "33" V 7450 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7180 2800 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 7250 2800 50  0001 C CNN
F 4 "YAGEO" H 7250 2800 50  0001 C CNN "MANUFACTURER"
F 5 "311-33.0HRCT-ND" H 7250 2800 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0733RL" H 7250 2800 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0733RL" H 7250 2800 50  0001 C CNN "mouser#"
	1    7250 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R72
U 1 1 623A5429
P 9950 1900
F 0 "R72" V 9850 1900 50  0000 C CNN
F 1 "33" V 9750 1900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9880 1900 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 9950 1900 50  0001 C CNN
F 4 "YAGEO" H 9950 1900 50  0001 C CNN "MANUFACTURER"
F 5 "311-33.0HRCT-ND" H 9950 1900 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0733RL" H 9950 1900 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0733RL" H 9950 1900 50  0001 C CNN "mouser#"
	1    9950 1900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R73
U 1 1 623A6A9B
P 9950 2800
F 0 "R73" V 9743 2800 50  0000 C CNN
F 1 "33" V 9834 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9880 2800 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 9950 2800 50  0001 C CNN
F 4 "YAGEO" H 9950 2800 50  0001 C CNN "MANUFACTURER"
F 5 "311-33.0HRCT-ND" H 9950 2800 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0733RL" H 9950 2800 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0733RL" H 9950 2800 50  0001 C CNN "mouser#"
	1    9950 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 1750 2950 1750
Wire Wire Line
	2600 2800 2950 2800
Wire Wire Line
	5000 1900 4650 1900
Wire Wire Line
	5000 2800 4650 2800
Wire Wire Line
	7400 2800 7750 2800
Wire Wire Line
	7400 1750 7750 1750
Wire Wire Line
	9800 1900 9450 1900
Wire Wire Line
	9800 2800 9450 2800
Text HLabel 2150 1750 0    50   BiDi ~ 0
QSPI_BK1_IO3
Text HLabel 2150 2800 0    50   BiDi ~ 0
QSPI_BK1_IO1
Text HLabel 5450 2800 2    50   BiDi ~ 0
QSPI_BK1_IO2
Text HLabel 5450 1900 2    50   BiDi ~ 0
QSPI_BK1_IO0
Text HLabel 5450 1750 2    50   BiDi ~ 0
QSPI_CLK
Text HLabel 6950 1750 0    50   BiDi ~ 0
QSPI_BK2_IO3
Text HLabel 6950 2800 0    50   BiDi ~ 0
QSPI_BK2_IO1
Text HLabel 10250 2800 2    50   BiDi ~ 0
QSPI_BK2_IO2
Wire Wire Line
	10100 2800 10250 2800
Text HLabel 10250 1900 2    50   BiDi ~ 0
QSPI_BK2_IO0
Text HLabel 10250 1750 2    50   BiDi ~ 0
QSPI_CLK
Wire Wire Line
	9450 1750 10250 1750
Wire Wire Line
	10250 1900 10100 1900
Wire Wire Line
	7100 1750 6950 1750
Wire Wire Line
	6950 2800 7100 2800
Wire Wire Line
	5450 2800 5300 2800
Wire Wire Line
	5450 1900 5300 1900
Wire Wire Line
	5450 1750 4650 1750
Wire Wire Line
	2150 2800 2300 2800
Wire Wire Line
	2150 1750 2300 1750
$Comp
L Device:R R67
U 1 1 623C3963
P 2750 2350
F 0 "R67" H 2550 2400 50  0000 L CNN
F 1 "10K" H 2500 2300 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2680 2350 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 2750 2350 50  0001 C CNN
F 4 "YAGEO" H 2750 2350 50  0001 C CNN "MANUFACTURER"
F 5 "311-10.0KHRCT-ND" H 2750 2350 50  0001 C CNN "digikey#"
F 6 "RC0603FR-0710KL" H 2750 2350 50  0001 C CNN "manf#"
F 7 "603-RC0603FR-0710KL" H 2750 2350 50  0001 C CNN "mouser#"
	1    2750 2350
	1    0    0    -1  
$EndComp
Text HLabel 2150 2650 0    50   BiDi ~ 0
QSPI_BK1_NCS
Wire Wire Line
	2150 2650 2750 2650
Wire Wire Line
	2750 2500 2750 2650
Connection ~ 2750 2650
Wire Wire Line
	2750 2650 2950 2650
Text HLabel 6950 2650 0    50   BiDi ~ 0
QSPI_BK1_NCS
Wire Wire Line
	6950 2650 7750 2650
$Comp
L power:+3V3 #PWR0142
U 1 1 623CAAEA
P 2750 1450
F 0 "#PWR0142" H 2750 1300 50  0001 C CNN
F 1 "+3V3" H 2765 1623 50  0000 C CNN
F 2 "" H 2750 1450 50  0001 C CNN
F 3 "" H 2750 1450 50  0001 C CNN
	1    2750 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1450 2750 2200
Text Notes 1000 7200 0    79   ~ 0
* Reference the plane using GND or PWR (if PWR, add 10nf stitching cap between \nPWR and GND.\n\n* Trace the impedance: 50 Ω ± 10%.\n\n* The maximum trace length should be below 120mm. If the signal trace exceeds\n this trace-length/speed criterion, then a termination should be used.\n\n* Avoid using multiple signal layers for the data signal routing.\n\n* Route the clock signal at least 3x of the trace away from other signals. Use as \nless vias as possible to avoid the impedance change and reflection. Avoid using\n a serpentine routing.\n\n* Match the trace lengths for the data group within ± 10 mm of each other to\n diminish skew.\n\n* Avoid using a serpentine routing for the clock signal and as less via(s) as possible for\nthe whole path. a via alters the impedance and adds a reflection to the signal.\n\n* All connections must match net lengths Tolerance=2.54mm
$EndSCHEMATC

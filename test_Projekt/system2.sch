EESchema Schematic File Version 4
LIBS:test_Projekt-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 9
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 4700 1650 1100 3100
U 63824A94
F0 "sheet63824A8A" 50
F1 "µC.sch" 50
F2 "I2C_SCL" O L 4700 2850 50 
F3 "I2C_SDA" B L 4700 2750 50 
F4 "TIM2" I L 4700 3750 50 
F5 "TIM5" I L 4700 3850 50 
F6 "CAN_RX" I R 5800 2550 50 
F7 "CAN_TX" O R 5800 2450 50 
$EndSheet
$Comp
L Regulator_Linear:LD1117S50TR_SOT223 U9
U 1 1 63824A9A
P 2000 1950
F 0 "U9" H 2000 2192 50  0000 C CNN
F 1 "LD1117S50TR_SOT223" H 2000 2101 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 2000 2150 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 2100 1700 50  0001 C CNN
	1    2000 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C23
U 1 1 63824AA1
P 1400 2150
F 0 "C23" H 1492 2196 50  0000 L CNN
F 1 "0.1µF" H 1492 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1400 2150 50  0001 C CNN
F 3 "~" H 1400 2150 50  0001 C CNN
	1    1400 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C26
U 1 1 63824AA8
P 2500 2150
F 0 "C26" H 2592 2196 50  0000 L CNN
F 1 "10µF" H 2592 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2500 2150 50  0001 C CNN
F 3 "~" H 2500 2150 50  0001 C CNN
	1    2500 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2050 1400 1950
Wire Wire Line
	1400 1950 1700 1950
Wire Wire Line
	2300 1950 2500 1950
Wire Wire Line
	2500 1950 2500 2050
Wire Wire Line
	1400 2350 1400 2250
Wire Wire Line
	2500 2350 2500 2250
$Comp
L power:GND #PWR066
U 1 1 63824AB5
P 1400 2350
F 0 "#PWR066" H 1400 2100 50  0001 C CNN
F 1 "GND" H 1405 2177 50  0000 C CNN
F 2 "" H 1400 2350 50  0001 C CNN
F 3 "" H 1400 2350 50  0001 C CNN
	1    1400 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR075
U 1 1 63824ABB
P 2500 2350
F 0 "#PWR075" H 2500 2100 50  0001 C CNN
F 1 "GND" H 2505 2177 50  0000 C CNN
F 2 "" H 2500 2350 50  0001 C CNN
F 3 "" H 2500 2350 50  0001 C CNN
	1    2500 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1650 1400 1950
Connection ~ 1400 1950
$Comp
L power:+5V #PWR065
U 1 1 63824AC3
P 1400 1650
F 0 "#PWR065" H 1400 1500 50  0001 C CNN
F 1 "+5V" H 1415 1823 50  0000 C CNN
F 2 "" H 1400 1650 50  0001 C CNN
F 3 "" H 1400 1650 50  0001 C CNN
	1    1400 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR074
U 1 1 63824AC9
P 2500 1650
F 0 "#PWR074" H 2500 1500 50  0001 C CNN
F 1 "+3.3V" H 2515 1823 50  0000 C CNN
F 2 "" H 2500 1650 50  0001 C CNN
F 3 "" H 2500 1650 50  0001 C CNN
	1    2500 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1650 2500 1950
Connection ~ 2500 1950
Wire Wire Line
	2000 2350 2000 2250
$Comp
L power:GND #PWR071
U 1 1 63824AD2
P 2000 2350
F 0 "#PWR071" H 2000 2100 50  0001 C CNN
F 1 "GND" H 2005 2177 50  0000 C CNN
F 2 "" H 2000 2350 50  0001 C CNN
F 3 "" H 2000 2350 50  0001 C CNN
	1    2000 2350
	1    0    0    -1  
$EndComp
$Comp
L Interface_CAN_LIN:TJA1051T U11
U 1 1 63824AD8
P 8500 2650
F 0 "U11" H 8800 3250 50  0000 C CNN
F 1 "TJA1051T" H 8900 3150 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 8500 2150 50  0001 C CIN
F 3 "http://www.nxp.com/documents/data_sheet/TJA1051.pdf" H 8500 2650 50  0001 C CNN
	1    8500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2450 8000 2450
Wire Wire Line
	5800 2550 8000 2550
Wire Wire Line
	7500 2750 7500 2850
Wire Wire Line
	7500 2850 7600 2850
$Comp
L power:+3.3V #PWR077
U 1 1 63824AE3
P 7500 2750
F 0 "#PWR077" H 7500 2600 50  0001 C CNN
F 1 "+3.3V" H 7515 2923 50  0000 C CNN
F 2 "" H 7500 2750 50  0001 C CNN
F 3 "" H 7500 2750 50  0001 C CNN
	1    7500 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R28
U 1 1 63824AE9
P 7700 2850
F 0 "R28" V 7504 2850 50  0000 C CNN
F 1 "0" V 7595 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7700 2850 50  0001 C CNN
F 3 "~" H 7700 2850 50  0001 C CNN
	1    7700 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 2850 8000 2850
$Comp
L power:GND #PWR080
U 1 1 63824AF1
P 8500 3150
F 0 "#PWR080" H 8500 2900 50  0001 C CNN
F 1 "GND" H 8505 2977 50  0000 C CNN
F 2 "" H 8500 3150 50  0001 C CNN
F 3 "" H 8500 3150 50  0001 C CNN
	1    8500 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3150 8500 3050
$Comp
L power:+5V #PWR079
U 1 1 63824AF8
P 8500 1650
F 0 "#PWR079" H 8500 1500 50  0001 C CNN
F 1 "+5V" H 8515 1823 50  0000 C CNN
F 2 "" H 8500 1650 50  0001 C CNN
F 3 "" H 8500 1650 50  0001 C CNN
	1    8500 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1650 8500 1750
$Comp
L Device:C_Small C27
U 1 1 63824AFF
P 7800 1950
F 0 "C27" H 7892 1996 50  0000 L CNN
F 1 "0.1µF" H 7892 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7800 1950 50  0001 C CNN
F 3 "~" H 7800 1950 50  0001 C CNN
	1    7800 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1850 7800 1750
Wire Wire Line
	7800 1750 8500 1750
Connection ~ 8500 1750
Wire Wire Line
	8500 1750 8500 2250
$Comp
L power:GND #PWR078
U 1 1 63824B0A
P 7800 2150
F 0 "#PWR078" H 7800 1900 50  0001 C CNN
F 1 "GND" H 7805 1977 50  0000 C CNN
F 2 "" H 7800 2150 50  0001 C CNN
F 3 "" H 7800 2150 50  0001 C CNN
	1    7800 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 2150 7800 2050
Wire Wire Line
	9900 2550 9000 2550
Wire Wire Line
	9000 2750 9100 2750
Wire Wire Line
	9100 2750 9100 2650
Wire Wire Line
	9100 2650 9900 2650
Text Notes 9900 2350 0    50   ~ 0
CAN BUS connector\n
Wire Wire Line
	3900 3750 3900 2750
Wire Wire Line
	3900 2750 4700 2750
Wire Wire Line
	4000 3900 4000 2850
Wire Wire Line
	4000 2850 4700 2850
$Sheet
S 4750 5100 1000 300 
U 63824B96
F0 "sheet63824A8B" 50
F1 "Freq_source_etalon.sch" 50
F2 "Freq_output_CLK" O L 4750 5250 50 
$EndSheet
$Sheet
S 4750 5600 1000 300 
U 63824B99
F0 "sheet63824A8C" 50
F1 "Freq_source_not eltalon.sch" 50
F2 "Freq_output_CLK" O L 4750 5750 50 
$EndSheet
Text Notes 5900 5250 0    50   ~ 0
Etalon frequenz Generator\n
Text Notes 5900 5750 0    50   ~ 0
Non etalon frequenz Generator
Wire Wire Line
	4750 5250 4550 5250
Wire Wire Line
	4550 5250 4550 3850
Wire Wire Line
	4550 3850 4700 3850
Wire Wire Line
	4700 3750 4450 3750
Wire Wire Line
	4450 3750 4450 5750
Wire Wire Line
	4450 5750 4750 5750
Text HLabel 9900 2550 2    50   BiDi ~ 0
CANH_2
Text HLabel 9900 2650 2    50   BiDi ~ 0
CANL_2
Wire Wire Line
	3650 3750 3750 3750
Wire Wire Line
	3650 3900 3900 3900
Text HLabel 3650 3750 0    50   BiDi ~ 0
SDA_2
Text HLabel 3650 3900 0    50   Output ~ 0
SCL_2
$Comp
L Memory_EEPROM:24LC512 U3
U 1 1 63A725F2
P 2050 4650
F 0 "U3" H 2300 5100 50  0000 C CNN
F 1 "24LC512" H 2300 5000 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2050 4650 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21754M.pdf" H 2050 4650 50  0001 C CNN
	1    2050 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 4550 3750 4550
Wire Wire Line
	3750 4550 3750 3750
Connection ~ 3750 3750
Wire Wire Line
	3750 3750 3900 3750
Wire Wire Line
	3900 3900 3900 4650
Wire Wire Line
	3900 4650 2450 4650
Connection ~ 3900 3900
Wire Wire Line
	3900 3900 4000 3900
Wire Wire Line
	1550 4550 1550 4650
Wire Wire Line
	1550 4750 1650 4750
Wire Wire Line
	1550 4550 1650 4550
Wire Wire Line
	1650 4650 1550 4650
Connection ~ 1550 4650
Wire Wire Line
	1550 4650 1550 4750
$Comp
L power:GND #PWR073
U 1 1 63A746AB
P 2050 5050
F 0 "#PWR073" H 2050 4800 50  0001 C CNN
F 1 "GND" H 2055 4877 50  0000 C CNN
F 2 "" H 2050 5050 50  0001 C CNN
F 3 "" H 2050 5050 50  0001 C CNN
	1    2050 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 5050 2050 4950
$Comp
L power:GND #PWR070
U 1 1 63A76AAE
P 1550 5050
F 0 "#PWR070" H 1550 4800 50  0001 C CNN
F 1 "GND" H 1555 4877 50  0000 C CNN
F 2 "" H 1550 5050 50  0001 C CNN
F 3 "" H 1550 5050 50  0001 C CNN
	1    1550 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 5050 1550 4750
Connection ~ 1550 4750
$Comp
L power:+3.3V #PWR072
U 1 1 63A77836
P 2050 3800
F 0 "#PWR072" H 2050 3650 50  0001 C CNN
F 1 "+3.3V" H 2065 3973 50  0000 C CNN
F 2 "" H 2050 3800 50  0001 C CNN
F 3 "" H 2050 3800 50  0001 C CNN
	1    2050 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR076
U 1 1 63A78505
P 2500 5050
F 0 "#PWR076" H 2500 4800 50  0001 C CNN
F 1 "GND" H 2505 4877 50  0000 C CNN
F 2 "" H 2500 5050 50  0001 C CNN
F 3 "" H 2500 5050 50  0001 C CNN
	1    2500 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5050 2500 4750
Wire Wire Line
	2500 4750 2450 4750
$Comp
L Device:C_Small C24
U 1 1 63A86043
P 1250 4150
F 0 "C24" H 1342 4196 50  0000 L CNN
F 1 "0.1µF" H 1342 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1250 4150 50  0001 C CNN
F 3 "~" H 1250 4150 50  0001 C CNN
	1    1250 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 4350 1250 4250
$Comp
L power:GND #PWR069
U 1 1 63A8604B
P 1250 4350
F 0 "#PWR069" H 1250 4100 50  0001 C CNN
F 1 "GND" H 1255 4177 50  0000 C CNN
F 2 "" H 1250 4350 50  0001 C CNN
F 3 "" H 1250 4350 50  0001 C CNN
	1    1250 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 4050 1250 3950
Wire Wire Line
	1250 3950 2050 3950
Wire Wire Line
	2050 3800 2050 3950
Connection ~ 2050 3950
Wire Wire Line
	2050 3950 2050 4350
$EndSCHEMATC
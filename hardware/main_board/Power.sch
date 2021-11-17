EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L power:+12V #PWR0205
U 1 1 61C0D0D6
P 4250 2350
F 0 "#PWR0205" H 4250 2200 50  0001 C CNN
F 1 "+12V" H 4265 2523 50  0000 C CNN
F 2 "" H 4250 2350 50  0001 C CNN
F 3 "" H 4250 2350 50  0001 C CNN
	1    4250 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2350 4250 2400
Wire Wire Line
	4250 2400 4400 2400
Wire Wire Line
	4400 2400 4400 2500
Connection ~ 4400 2400
Wire Wire Line
	4400 2400 4650 2400
$Comp
L power:GND #PWR0207
U 1 1 61C10DC4
P 4950 2850
F 0 "#PWR0207" H 4950 2600 50  0001 C CNN
F 1 "GND" H 4955 2677 50  0000 C CNN
F 2 "" H 4950 2850 50  0001 C CNN
F 3 "" H 4950 2850 50  0001 C CNN
	1    4950 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2400 5600 2400
Wire Wire Line
	5600 2400 5600 2550
Connection ~ 5600 2400
Wire Wire Line
	4950 2700 4950 2850
$Comp
L power:GND #PWR0206
U 1 1 61C17268
P 4400 3000
F 0 "#PWR0206" H 4400 2750 50  0001 C CNN
F 1 "GND" H 4405 2827 50  0000 C CNN
F 2 "" H 4400 3000 50  0001 C CNN
F 3 "" H 4400 3000 50  0001 C CNN
	1    4400 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2800 4400 3000
$Comp
L power:GND #PWR0208
U 1 1 61C176B1
P 5600 3000
F 0 "#PWR0208" H 5600 2750 50  0001 C CNN
F 1 "GND" H 5605 2827 50  0000 C CNN
F 2 "" H 5600 3000 50  0001 C CNN
F 3 "" H 5600 3000 50  0001 C CNN
	1    5600 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2850 5600 3000
Text Notes 4500 1950 0    50   ~ 0
12V - 5V Linear Regulator
Text GLabel 2050 1900 0    50   Input ~ 0
PWR_IN
Text GLabel 2300 1900 2    50   Input ~ 0
PWR_SW_ON
Wire Wire Line
	2050 1900 2300 1900
Text GLabel 2350 2300 2    50   Input ~ 0
PWR_SW_OFF
$Comp
L power:+12V #PWR0203
U 1 1 61CB6F7F
P 1800 2250
F 0 "#PWR0203" H 1800 2100 50  0001 C CNN
F 1 "+12V" H 1815 2423 50  0000 C CNN
F 2 "" H 1800 2250 50  0001 C CNN
F 3 "" H 1800 2250 50  0001 C CNN
	1    1800 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2250 1800 2300
Wire Wire Line
	1800 2300 2350 2300
Text Notes 1750 1650 0    50   ~ 0
Power Switch (and ESTOP)
$Comp
L formula:Test_Point_SMD TP203
U 1 1 61DA7A2E
P 1800 3000
F 0 "TP203" H 1712 2996 50  0000 R CNN
F 1 "12V_LED" H 1712 3087 50  0000 R CNN
F 2 "footprints:Test_Point_SMD" H 1800 2850 50  0001 C CNN
F 3 "" H 1800 3000 50  0001 C CNN
	1    1800 3000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R202
U 1 1 61DAAC12
P 1800 2650
F 0 "R202" H 1870 2696 50  0000 L CNN
F 1 "R_500" H 1870 2605 50  0000 L CNN
F 2 "" V 1730 2650 50  0001 C CNN
F 3 "~" H 1800 2650 50  0001 C CNN
	1    1800 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2300 1800 2500
Connection ~ 1800 2300
Wire Wire Line
	1800 2800 1800 2950
Text Notes 2350 2250 0    50   ~ 0
Off Side of Power Switch
Text Notes 2300 1850 0    50   ~ 0
On Side of Power Switch
Text Notes 1000 1850 0    50   ~ 0
12V from the power supply
$Comp
L formula:Test_Point_SMD TP204
U 1 1 61DB0FD2
P 1800 3450
F 0 "TP204" H 1878 3538 50  0000 L CNN
F 1 "12V_LED_GND" H 1878 3447 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1800 3300 50  0001 C CNN
F 3 "" H 1800 3450 50  0001 C CNN
	1    1800 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0204
U 1 1 61DB17A4
P 1800 3750
F 0 "#PWR0204" H 1800 3500 50  0001 C CNN
F 1 "GND" H 1805 3577 50  0000 C CNN
F 2 "" H 1800 3750 50  0001 C CNN
F 3 "" H 1800 3750 50  0001 C CNN
	1    1800 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 3500 1800 3750
Text Notes 1300 3250 0    50   ~ 0
Solder the LED wires onto the exposed copper
Wire Wire Line
	6550 2400 6550 2350
$Comp
L formula:Test_Point_SMD TP205
U 1 1 61DB8599
P 6400 2900
F 0 "TP205" H 6312 2896 50  0000 R CNN
F 1 "5V_LED" H 6312 2987 50  0000 R CNN
F 2 "footprints:Test_Point_SMD" H 6400 2750 50  0001 C CNN
F 3 "" H 6400 2900 50  0001 C CNN
	1    6400 2900
	-1   0    0    1   
$EndComp
$Comp
L formula:R_100 R203
U 1 1 61DB93FF
P 6400 2600
F 0 "R203" H 6470 2646 50  0000 L CNN
F 1 "R_100" H 6470 2555 50  0000 L CNN
F 2 "footprints:R_0805_OEM" H 5600 2750 50  0001 C CNN
F 3 "https://www.seielect.com/Catalog/SEI-rncp.pdf" H 6100 3100 50  0001 C CNN
F 4 "DK" H 6400 2600 60  0001 C CNN "MFN"
F 5 "RNCP0805FTD100RCT-ND" H 5750 2850 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/products/en?keywords=RNCP0805FTD100RCT-ND" H 6880 3000 60  0001 C CNN "PurchasingLink"
	1    6400 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 2400 6400 2450
Wire Wire Line
	5600 2400 6400 2400
Connection ~ 6400 2400
Wire Wire Line
	6400 2400 6550 2400
Wire Wire Line
	6400 2750 6400 2850
Text Notes 6800 2600 0    50   ~ 0
min 65Ohm resistor
$Comp
L formula:Test_Point_SMD TP206
U 1 1 61DBD197
P 6400 3350
F 0 "TP206" H 6478 3438 50  0000 L CNN
F 1 "5V_LED_GND" H 6478 3347 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 6400 3200 50  0001 C CNN
F 3 "" H 6400 3350 50  0001 C CNN
	1    6400 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0209
U 1 1 61DBDB3A
P 6400 3600
F 0 "#PWR0209" H 6400 3350 50  0001 C CNN
F 1 "GND" H 6405 3427 50  0000 C CNN
F 2 "" H 6400 3600 50  0001 C CNN
F 3 "" H 6400 3600 50  0001 C CNN
	1    6400 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3400 6400 3600
Text Notes 6150 3150 0    50   ~ 0
Solder the LED wires onto the exposed copper
$Comp
L power:+5V #PWR0210
U 1 1 61E49762
P 6550 2350
F 0 "#PWR0210" H 6550 2200 50  0001 C CNN
F 1 "+5V" H 6565 2523 50  0000 C CNN
F 2 "" H 6550 2350 50  0001 C CNN
F 3 "" H 6550 2350 50  0001 C CNN
	1    6550 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 62297415
P 1750 4600
AR Path="/619053FC/62297415" Ref="#PWR?"  Part="1" 
AR Path="/61902E4F/62297415" Ref="#PWR0201"  Part="1" 
F 0 "#PWR0201" H 1750 4450 50  0001 C CNN
F 1 "+3.3V" H 1765 4773 50  0000 C CNN
F 2 "" H 1750 4600 50  0001 C CNN
F 3 "" H 1750 4600 50  0001 C CNN
	1    1750 4600
	1    0    0    -1  
$EndComp
$Comp
L formula:Test_Point_SMD TP?
U 1 1 6229741B
P 1750 5200
AR Path="/619053FC/6229741B" Ref="TP?"  Part="1" 
AR Path="/61902E4F/6229741B" Ref="TP201"  Part="1" 
F 0 "TP201" H 1662 5196 50  0000 R CNN
F 1 "3.3_LED" H 1662 5287 50  0000 R CNN
F 2 "footprints:Test_Point_SMD" H 1750 5050 50  0001 C CNN
F 3 "" H 1750 5200 50  0001 C CNN
	1    1750 5200
	-1   0    0    1   
$EndComp
$Comp
L formula:R_100 R?
U 1 1 62297424
P 1750 4850
AR Path="/619053FC/62297424" Ref="R?"  Part="1" 
AR Path="/61902E4F/62297424" Ref="R201"  Part="1" 
F 0 "R201" H 1820 4896 50  0000 L CNN
F 1 "R_100" H 1820 4805 50  0000 L CNN
F 2 "footprints:R_0805_OEM" H 950 5000 50  0001 C CNN
F 3 "https://www.seielect.com/Catalog/SEI-rncp.pdf" H 1450 5350 50  0001 C CNN
F 4 "DK" H 1750 4850 60  0001 C CNN "MFN"
F 5 "RNCP0805FTD100RCT-ND" H 1100 5100 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/products/en?keywords=RNCP0805FTD100RCT-ND" H 2230 5250 60  0001 C CNN "PurchasingLink"
	1    1750 4850
	1    0    0    -1  
$EndComp
$Comp
L formula:Test_Point_SMD TP?
U 1 1 6229742A
P 1750 5650
AR Path="/619053FC/6229742A" Ref="TP?"  Part="1" 
AR Path="/61902E4F/6229742A" Ref="TP202"  Part="1" 
F 0 "TP202" H 1828 5738 50  0000 L CNN
F 1 "3.3_LED_GND" H 1828 5647 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1750 5500 50  0001 C CNN
F 3 "" H 1750 5650 50  0001 C CNN
	1    1750 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62297430
P 1750 5900
AR Path="/619053FC/62297430" Ref="#PWR?"  Part="1" 
AR Path="/61902E4F/62297430" Ref="#PWR0202"  Part="1" 
F 0 "#PWR0202" H 1750 5650 50  0001 C CNN
F 1 "GND" H 1755 5727 50  0000 C CNN
F 2 "" H 1750 5900 50  0001 C CNN
F 3 "" H 1750 5900 50  0001 C CNN
	1    1750 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 5700 1750 5900
Wire Wire Line
	1750 5150 1750 5000
Wire Wire Line
	1750 4700 1750 4600
Text Notes 2300 5050 2    50   ~ 0
min 65 Ohms
Text Notes 1600 5500 1    50   ~ 0
3.3V Indicator LED
Text Notes 1800 5450 0    50   ~ 0
solder the LED wires to the exposed copper
$Comp
L Regulator_Linear:LM1117-5.0 U201
U 1 1 6239189A
P 4950 2400
F 0 "U201" H 4950 2642 50  0000 C CNN
F 1 "LM1117-5.0" H 4950 2551 50  0000 C CNN
F 2 "" H 4950 2400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 4950 2400 50  0001 C CNN
	1    4950 2400
	1    0    0    -1  
$EndComp
$Comp
L formula:C_10uF_16V C201
U 1 1 623924BD
P 4400 2650
F 0 "C201" H 4700 2650 50  0000 R CNN
F 1 "C_10uF_16V" H 4900 2750 50  0000 R CNN
F 2 "footprints:C_0805_OEM" H 4438 2500 50  0001 C CNN
F 3 "http://www.samsungsem.com/kr/support/product-search/mlcc/__icsFiles/afieldfile/2016/01/15/Data%20sheet_CL21A106KOCLRNC.pdf" H 4425 2750 50  0001 C CNN
F 4 "DK" H 4400 2650 60  0001 C CNN "MFN"
F 5 "1276-2399-1-ND" H 4400 2650 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/product-detail/en/samsung-electro-mechanics/CL21A106KOCLRNC/1276-2399-1-ND/3890485" H 4825 3150 60  0001 C CNN "PurchasingLink"
	1    4400 2650
	-1   0    0    1   
$EndComp
$Comp
L formula:C_10uF_16V C202
U 1 1 6239EB03
P 5600 2700
F 0 "C202" H 5900 2700 50  0000 R CNN
F 1 "C_10uF_16V" H 6100 2800 50  0000 R CNN
F 2 "footprints:C_0805_OEM" H 5638 2550 50  0001 C CNN
F 3 "http://www.samsungsem.com/kr/support/product-search/mlcc/__icsFiles/afieldfile/2016/01/15/Data%20sheet_CL21A106KOCLRNC.pdf" H 5625 2800 50  0001 C CNN
F 4 "DK" H 5600 2700 60  0001 C CNN "MFN"
F 5 "1276-2399-1-ND" H 5600 2700 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/product-detail/en/samsung-electro-mechanics/CL21A106KOCLRNC/1276-2399-1-ND/3890485" H 6025 3200 60  0001 C CNN "PurchasingLink"
	1    5600 2700
	-1   0    0    1   
$EndComp
Text Notes 4200 3650 0    50   ~ 0
change caps to this:\nhttps://www.vishay.com/docs/40080/tr3.pdf
$EndSCHEMATC

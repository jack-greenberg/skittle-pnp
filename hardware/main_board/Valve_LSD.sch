EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L power:+12V #PWR?
U 1 1 6286E096
P 6000 1750
AR Path="/619053FC/6286E096" Ref="#PWR?"  Part="1" 
AR Path="/6286C9DB/6286E096" Ref="#PWR0501"  Part="1" 
F 0 "#PWR0501" H 6000 1600 50  0001 C CNN
F 1 "+12V" H 6015 1923 50  0000 C CNN
F 2 "" H 6000 1750 50  0001 C CNN
F 3 "" H 6000 1750 50  0001 C CNN
	1    6000 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6286E09C
P 6000 3500
AR Path="/619053FC/6286E09C" Ref="#PWR?"  Part="1" 
AR Path="/6286C9DB/6286E09C" Ref="#PWR0502"  Part="1" 
F 0 "#PWR0502" H 6000 3250 50  0001 C CNN
F 1 "GND" H 6005 3327 50  0000 C CNN
F 2 "" H 6000 3500 50  0001 C CNN
F 3 "" H 6000 3500 50  0001 C CNN
	1    6000 3500
	1    0    0    -1  
$EndComp
$Comp
L formula:R_10K R?
U 1 1 6286E0A5
P 5450 3050
AR Path="/619053FC/6286E0A5" Ref="R?"  Part="1" 
AR Path="/6286C9DB/6286E0A5" Ref="R501"  Part="1" 
F 0 "R501" H 5520 3096 50  0000 L CNN
F 1 "R_10K" H 5520 3005 50  0000 L CNN
F 2 "footprints:R_0805_OEM" H 5380 3050 50  0001 C CNN
F 3 "http://www.bourns.com/data/global/pdfs/CRS.pdf" H 5530 3050 50  0001 C CNN
F 4 "DK" H 5450 3050 60  0001 C CNN "MFN"
F 5 "CRS0805-FX-1002ELFCT-ND" H 5450 3050 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/products/en?keywords=CRS0805-FX-1002ELFCT-ND" H 5930 3450 60  0001 C CNN "PurchasingLink"
	1    5450 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2800 5450 2900
Connection ~ 5450 2800
Wire Wire Line
	5450 2800 5700 2800
Wire Wire Line
	5450 3300 5450 3200
Wire Wire Line
	5450 3300 6000 3300
Connection ~ 6000 3300
Wire Wire Line
	5200 2800 5450 2800
Text Notes 4750 1750 0    79   ~ 0
Valve LSD
Wire Notes Line
	4250 1500 4250 3750
Wire Notes Line
	6900 3750 6900 1500
Wire Wire Line
	6000 3300 6000 3500
Wire Wire Line
	6000 3000 6000 3300
Text Notes 4250 3950 0    50   ~ 0
diode: https://www.diodes.com/assets/Datasheets/ds14001.pdf\n200V, 1A
Wire Notes Line
	4250 1500 6900 1500
Wire Notes Line
	4250 3750 6900 3750
Text GLabel 5200 2800 0    50   Input ~ 0
VALVE_CONTROL
Text GLabel 6150 2100 2    50   Output ~ 0
VALVE_PWR
$Comp
L skittle_pnp:D_200_1A D501
U 1 1 62A9BBC4
P 5700 2250
F 0 "D501" V 5650 2000 50  0000 L CNN
F 1 "D_200_1A" V 5750 1800 50  0000 L CNN
F 2 "skittle_pnp:DIOM5226X240N" H 5700 2250 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds14001.pdf" H 5700 2250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/ES1D-13-F/768873" H 5700 2250 50  0001 C CNN "Purchasing Link"
	1    5700 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 2100 6150 2100
Wire Wire Line
	6000 1750 6000 1950
$Comp
L formula:SSM3K333R Q501
U 1 1 619884FC
P 5900 2800
F 0 "Q501" H 6106 2846 50  0000 L CNN
F 1 "SSM3K333R" H 6106 2755 50  0000 L CNN
F 2 "footprints:SOT-23F" H 6100 2725 50  0001 L CIN
F 3 "https://drive.google.com/drive/folders/0B-V-iZf33Y4GNzhDQTJZanJRbVk" H 6100 2875 50  0001 L CNN
F 4 "DK" H 6400 3175 60  0001 C CNN "MFN"
F 5 "SSM3K333RLFCT-ND" H 6300 3075 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/product-detail/en/toshiba-semiconductor-and-storage/SSM3K333RLF/SSM3K333RLFCT-ND/3522391" H 6200 2975 60  0001 C CNN "PurchasingLink"
	1    5900 2800
	1    0    0    -1  
$EndComp
Text GLabel 6150 2350 2    50   Input ~ 0
VALVE_GND
Wire Wire Line
	6000 2350 6000 2500
Wire Wire Line
	5700 2100 5700 1950
Wire Wire Line
	5700 1950 6000 1950
Connection ~ 6000 1950
Wire Wire Line
	6000 1950 6000 2100
Wire Wire Line
	5700 2400 5700 2500
Wire Wire Line
	5700 2500 6000 2500
Connection ~ 6000 2500
Wire Wire Line
	6000 2500 6000 2600
Wire Wire Line
	6000 2350 6150 2350
$EndSCHEMATC

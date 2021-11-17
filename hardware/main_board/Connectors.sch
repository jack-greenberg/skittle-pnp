EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
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
L Connector_Generic:Conn_01x20 J?
U 1 1 61905837
P 3450 2400
F 0 "J?" H 3400 3550 50  0000 L CNN
F 1 "Conn_01x20" H 3200 3450 50  0000 L CNN
F 2 "" H 3450 2400 50  0001 C CNN
F 3 "~" H 3450 2400 50  0001 C CNN
	1    3450 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x20 J?
U 1 1 6190757F
P 4250 2500
F 0 "J?" H 4168 1275 50  0000 C CNN
F 1 "Conn_01x20" H 4168 1366 50  0000 C CNN
F 2 "" H 4250 2500 50  0001 C CNN
F 3 "~" H 4250 2500 50  0001 C CNN
	1    4250 2500
	-1   0    0    1   
$EndComp
Text Notes 2250 750  0    79   ~ 0
Shield for the STM32 Blue Pill (FEMALE, Vertical)
Text Notes 3550 1100 0    50   ~ 0
USB Micro-B Side
$Comp
L power:GND #PWR?
U 1 1 61922F09
P 4550 3500
F 0 "#PWR?" H 4550 3250 50  0001 C CNN
F 1 "GND" H 4555 3327 50  0000 C CNN
F 2 "" H 4550 3500 50  0001 C CNN
F 3 "" H 4550 3500 50  0001 C CNN
	1    4550 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1600 4550 1600
Wire Wire Line
	4450 1500 4550 1500
Wire Wire Line
	4550 1500 4550 1600
Connection ~ 4550 1600
Wire Wire Line
	4550 1600 4550 3500
$Comp
L power:+3.3V #PWR?
U 1 1 6192CFBF
P 4650 1500
F 0 "#PWR?" H 4650 1350 50  0001 C CNN
F 1 "+3.3V" V 4650 1750 50  0000 C CNN
F 2 "" H 4650 1500 50  0001 C CNN
F 3 "" H 4650 1500 50  0001 C CNN
	1    4650 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1700 4650 1700
Wire Wire Line
	4650 1700 4650 1500
Text Label 4950 2100 0    50   ~ 0
PB1
Text Label 4950 2200 0    50   ~ 0
PB0
Text Label 4950 2400 0    50   ~ 0
PA6(MISO)
Text Label 4950 2500 0    50   ~ 0
PA5(SCK)
Text Label 4950 2600 0    50   ~ 0
PA4(SS)
Text Label 4950 2700 0    50   ~ 0
PA3(RxD)
Text Label 4950 2800 0    50   ~ 0
PA2(TxD)
Text Label 4950 2900 0    50   ~ 0
PA1
Text Label 4950 3000 0    50   ~ 0
PA0(PWM)
Text Label 4950 3100 0    50   ~ 0
PC15(OSC32_OUT)
Text Label 4950 3200 0    50   ~ 0
PC14(OSC32_IN)
Text Label 4950 3300 0    50   ~ 0
PC13_LED
Wire Wire Line
	4450 3100 4950 3100
Wire Wire Line
	4450 3200 4950 3200
Wire Wire Line
	4450 3300 4950 3300
Text Label 4950 2300 0    50   ~ 0
PA7(MOSI)
Text Label 4950 2000 0    50   ~ 0
PB10
Text Label 4950 1900 0    50   ~ 0
PB11
Wire Wire Line
	4450 1800 4950 1800
Text Label 4950 1800 0    50   ~ 0
RESET
$Comp
L power:+BATT #PWR?
U 1 1 6193178F
P 4750 1650
F 0 "#PWR?" H 4750 1500 50  0001 C CNN
F 1 "+BATT" V 4750 1900 50  0000 C CNN
F 2 "" H 4750 1650 50  0001 C CNN
F 3 "" H 4750 1650 50  0001 C CNN
	1    4750 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61955A8A
P 3000 1450
F 0 "#PWR?" H 3000 1300 50  0001 C CNN
F 1 "+3.3V" V 3000 1700 50  0000 C CNN
F 2 "" H 3000 1450 50  0001 C CNN
F 3 "" H 3000 1450 50  0001 C CNN
	1    3000 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61957D53
P 3150 3550
F 0 "#PWR?" H 3150 3300 50  0001 C CNN
F 1 "GND" H 3155 3377 50  0000 C CNN
F 2 "" H 3150 3550 50  0001 C CNN
F 3 "" H 3150 3550 50  0001 C CNN
	1    3150 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 619589F2
P 3100 1300
F 0 "#PWR?" H 3100 1150 50  0001 C CNN
F 1 "+5V" V 3100 1500 50  0000 C CNN
F 2 "" H 3100 1300 50  0001 C CNN
F 3 "" H 3100 1300 50  0001 C CNN
	1    3100 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1450 3000 3400
Wire Wire Line
	3000 3400 3250 3400
Wire Wire Line
	3100 1300 3100 3200
Wire Wire Line
	3100 3200 3250 3200
Wire Wire Line
	3250 3300 3150 3300
Wire Wire Line
	3150 3300 3150 3550
Text Label 2850 1600 2    50   ~ 0
(SCK)PB13
Text Label 2850 1700 2    50   ~ 0
(MISO)PB14
Text Label 2850 1800 2    50   ~ 0
(MOSI)PB15
Text Label 2850 1900 2    50   ~ 0
PA8
Text Label 2850 2000 2    50   ~ 0
(TxD)PA9
Text Label 2850 2100 2    50   ~ 0
(RxD)PA10
Text Label 2850 2200 2    50   ~ 0
PA11
Text Label 2850 2300 2    50   ~ 0
PA12
Text Label 2850 2400 2    50   ~ 0
PA15
Text Label 2850 2500 2    50   ~ 0
(SWO)PB3
Text Label 2850 2600 2    50   ~ 0
PB4
Text Label 2850 2700 2    50   ~ 0
PB5
Text Label 2850 2800 2    50   ~ 0
(SCL)PB6
Text Label 2850 2900 2    50   ~ 0
(SDA)PB7
Text Label 2850 3000 2    50   ~ 0
PB8
Text Label 2850 3100 2    50   ~ 0
PB9
Wire Wire Line
	4450 3400 4750 3400
Wire Wire Line
	4750 3400 4750 1650
Text Notes 1900 6050 0    50   ~ 0
PA0 - PA7  \nPB0 - PB1\n\nPins can act as ADCs \nwith 12-bit resolution
Text Notes 1850 5750 2    50   ~ 10
Analog Pins: 
Text Notes 1850 6300 2    50   ~ 10
GPIOs: 
Text Notes 1900 6700 0    50   ~ 0
PA0 - PA15\nPB0 - PB15\nPC13 - PB15\n\nGeneral-purpose I/O pins\nNote that PC13 is the \non-board LED. 
Text Notes 1850 6950 2    50   ~ 10
PWM Capable:
Text Notes 1900 7200 0    50   ~ 0
PA0 - PA3\nPA6 - PA10\nPB0 - PB1\nPB6 - PB9
Text Notes 1850 7500 2    50   ~ 10
External Interrupts Capability:
Text Notes 1900 7650 0    50   ~ 0
PA0 – PA15\nPB0 – PB15\nPC13 – PC15
Wire Notes Line
	650  5600 650  7700
Wire Notes Line
	650  7700 2950 7700
Wire Notes Line
	2950 7700 2950 5600
Wire Notes Line
	2950 5600 650  5600
Text Notes 650  5550 0    50   ~ 10
STM32 Blue Pill Pinout
Text Notes 2400 2000 2    50   ~ 0
USART 1
Text Notes 5550 2500 2    50   ~ 0
SPI 1
Text Label 2850 1500 2    50   ~ 0
(SS)PB12
Text Notes 2450 1500 2    50   ~ 0
SPI 2
Text Notes 650  5400 0    50   ~ 0
Operating Voltage: 3.3V\nDC source/sink from I/O pins: 6mA
Text Notes 2500 2800 2    50   ~ 0
I2C 1
Text GLabel 2200 2200 0    50   Output ~ 0
MOTOR1_STEP
Text GLabel 2200 2300 0    50   Output ~ 0
MOTOR1_DIR
Text GLabel 2200 2400 0    35   Output ~ 0
MOTOR1_~EN
Text GLabel 2200 2500 0    50   Output ~ 0
MOTOR1_MS1
Text GLabel 2200 2600 0    50   Output ~ 0
MOTOR1_MS2
Text GLabel 2200 2700 0    50   Output ~ 0
MOTOR1_MS3
Text GLabel 5750 2400 2    50   Output ~ 0
MOTOR2_STEP
Text GLabel 5750 2300 2    50   Output ~ 0
MOTOR2_DIR
Text GLabel 5750 2200 2    35   Output ~ 0
MOTOR2_~EN
Text GLabel 5750 2100 2    50   Output ~ 0
MOTOR2_MS1
Text GLabel 5750 2000 2    50   Output ~ 0
MOTOR2_MS2
Text GLabel 5750 1900 2    50   Output ~ 0
MOTOR2_MS3
Wire Wire Line
	4450 2400 5750 2400
Wire Wire Line
	4450 2300 5750 2300
Wire Wire Line
	4450 2200 5750 2200
Wire Wire Line
	4450 2100 5750 2100
Wire Wire Line
	4450 2000 5750 2000
Wire Wire Line
	4450 1900 5750 1900
Wire Wire Line
	2200 3100 3250 3100
Wire Wire Line
	2200 3000 3250 3000
Text GLabel 7450 5800 2    50   Output ~ 0
MOTOR2_2B
Text GLabel 7450 5900 2    50   Output ~ 0
MOTOR2_2A
Text GLabel 7450 6000 2    50   Output ~ 0
MOTOR2_1A
Text GLabel 7450 6100 2    50   Output ~ 0
MOTOR2_1B
Wire Wire Line
	7450 6100 7250 6100
Wire Wire Line
	7450 6000 7250 6000
Wire Wire Line
	7450 5900 7250 5900
Wire Wire Line
	7450 5800 7250 5800
Text GLabel 7450 5050 2    50   Output ~ 0
MOTOR1_2B
Text GLabel 7450 5150 2    50   Output ~ 0
MOTOR1_2A
Text GLabel 7450 5250 2    50   Output ~ 0
MOTOR1_1A
Text GLabel 7450 5350 2    50   Output ~ 0
MOTOR1_1B
Wire Wire Line
	7450 5350 7250 5350
Wire Wire Line
	7450 5250 7250 5250
Wire Wire Line
	7450 5150 7250 5150
Wire Wire Line
	7450 5050 7250 5050
Text GLabel 9300 5800 2    50   Input ~ 0
X_LIMIT_SW1
Text GLabel 9300 6000 2    50   Input ~ 0
Y_LIMIT_SW1
Wire Wire Line
	9300 6100 9150 6100
Wire Wire Line
	9150 6000 9300 6000
Text GLabel 5750 2900 2    50   Output ~ 0
VALVE_CONTROL
Wire Wire Line
	9150 5900 9300 5900
$Comp
L Connector:Screw_Terminal_01x04 J?
U 1 1 61BB72E4
P 8950 6000
F 0 "J?" H 8900 5600 50  0000 L CNN
F 1 "LIMIT SWITCHES" H 8700 5700 50  0000 L CNN
F 2 "" H 8950 6000 50  0001 C CNN
F 3 "~" H 8950 6000 50  0001 C CNN
	1    8950 6000
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 61BF50ED
P 7050 5250
F 0 "J?" H 7050 4850 50  0000 C CNN
F 1 "MOTOR 1" H 7050 4950 50  0000 C CNN
F 2 "" H 7050 5250 50  0001 C CNN
F 3 "~" H 7050 5250 50  0001 C CNN
	1    7050 5250
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 61BF57D5
P 7050 6000
F 0 "J?" H 7050 5600 50  0000 C CNN
F 1 "MOTOR 2" H 7050 5700 50  0000 C CNN
F 2 "" H 7050 6000 50  0001 C CNN
F 3 "~" H 7050 6000 50  0001 C CNN
	1    7050 6000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61BF9D1C
P 9850 4450
F 0 "#PWR?" H 9850 4200 50  0001 C CNN
F 1 "GND" H 9855 4277 50  0000 C CNN
F 2 "" H 9850 4450 50  0001 C CNN
F 3 "" H 9850 4450 50  0001 C CNN
	1    9850 4450
	1    0    0    -1  
$EndComp
$Comp
L formula:F_1.1A_12V F?
U 1 1 61C1F190
P 9450 4100
F 0 "F?" V 9647 4100 50  0000 C CNN
F 1 "F_1.1A_12V" V 9556 4100 50  0000 C CNN
F 2 "Fuse_Holders_and_Fuses:Fuse_SMD1206_Reflow" V 9380 4100 50  0001 C CNN
F 3 "http://www.littelfuse.com/~/media/electronics/datasheets/resettable_ptcs/littelfuse_ptc_lorho_datasheet.pdf.pdf" V 9530 4100 50  0001 C CNN
F 4 "DK" H 9450 4100 60  0001 C CNN "MFN"
F 5 "F5764CT-ND" H 9450 4100 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/products/en?keywords=F5764CT-ND" V 9930 4500 60  0001 C CNN "PurchasingLink"
	1    9450 4100
	0    -1   -1   0   
$EndComp
Text GLabel 9350 4200 2    50   Input ~ 0
PWR_SW_ON
Text GLabel 9350 4300 2    50   Input ~ 0
PWR_SW_OFF
Wire Wire Line
	9150 4100 9300 4100
Wire Wire Line
	9150 4400 9850 4400
Wire Wire Line
	9850 4400 9850 4450
Wire Wire Line
	9150 4200 9350 4200
Wire Wire Line
	9150 4300 9350 4300
Wire Wire Line
	9600 4100 9800 4100
Text GLabel 9800 4100 2    50   Input ~ 0
PWR_IN
Text Notes 5350 2700 0    50   ~ 0
USART 2
Text GLabel 5750 3000 2    50   Output ~ 0
SERVO
Wire Wire Line
	4450 3000 5750 3000
Wire Wire Line
	4450 2900 5750 2900
Wire Wire Line
	2200 2700 3250 2700
Wire Wire Line
	2200 2600 3250 2600
Wire Wire Line
	2200 2200 3250 2200
Wire Wire Line
	2200 2300 3250 2300
Wire Wire Line
	2200 2400 3250 2400
Wire Wire Line
	2200 2500 3250 2500
Wire Wire Line
	9150 5800 9300 5800
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 61E42C7A
P 4600 7200
F 0 "J?" H 4518 6775 50  0000 C CNN
F 1 "Conn_01x04" H 4518 6866 50  0000 C CNN
F 2 "" H 4600 7200 50  0001 C CNN
F 3 "~" H 4600 7200 50  0001 C CNN
	1    4600 7200
	-1   0    0    1   
$EndComp
Text Label 5000 7100 0    50   ~ 0
(SCL)PB6
Text Label 5000 7200 0    50   ~ 0
(SDA)PB7
$Comp
L power:+5V #PWR?
U 1 1 61E50802
P 5200 6850
F 0 "#PWR?" H 5200 6700 50  0001 C CNN
F 1 "+5V" H 5215 7023 50  0000 C CNN
F 2 "" H 5200 6850 50  0001 C CNN
F 3 "" H 5200 6850 50  0001 C CNN
	1    5200 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 7000 5200 7000
Wire Wire Line
	5200 7000 5200 6850
$Comp
L power:GND #PWR?
U 1 1 61E55D74
P 5150 7350
F 0 "#PWR?" H 5150 7100 50  0001 C CNN
F 1 "GND" H 5155 7177 50  0000 C CNN
F 2 "" H 5150 7350 50  0001 C CNN
F 3 "" H 5150 7350 50  0001 C CNN
	1    5150 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 7300 5150 7300
Wire Wire Line
	5150 7300 5150 7350
Wire Wire Line
	4800 7100 5000 7100
Wire Wire Line
	5000 7200 4800 7200
Text Notes 3950 7250 0    50   ~ 0
I2C Connector \nfor LCD Screen
$Comp
L formula:Test_Point_SMD TP?
U 1 1 61E87761
P 6550 2500
F 0 "TP?" V 6550 2850 50  0000 L CNN
F 1 "PA5" V 6550 2700 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 6550 2350 50  0001 C CNN
F 3 "" H 6550 2500 50  0001 C CNN
	1    6550 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2500 6500 2500
$Comp
L formula:Test_Point_SMD TP?
U 1 1 61E8EBA9
P 6350 2600
F 0 "TP?" V 6350 2950 50  0000 L CNN
F 1 "PA4" V 6350 2800 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 6350 2450 50  0001 C CNN
F 3 "" H 6350 2600 50  0001 C CNN
	1    6350 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2600 6300 2600
Text Notes 6550 2400 0    50   ~ 0
exposed copper \nfor additional pins
$Comp
L formula:Test_Point_SMD TP?
U 1 1 61EA7FD3
P 1450 2800
F 0 "TP?" V 1450 3150 50  0000 L CNN
F 1 "PB6" V 1450 3000 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1450 2650 50  0001 C CNN
F 3 "" H 1450 2800 50  0001 C CNN
	1    1450 2800
	0    -1   -1   0   
$EndComp
$Comp
L formula:Test_Point_SMD TP?
U 1 1 61EA8958
P 1550 2900
F 0 "TP?" V 1550 3250 50  0000 L CNN
F 1 "PB7" V 1550 3100 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1550 2750 50  0001 C CNN
F 3 "" H 1550 2900 50  0001 C CNN
	1    1550 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1500 2800 3250 2800
Wire Wire Line
	1600 2900 3250 2900
Text Notes 700  2700 0    50   ~ 0
exposed copper \nfor additional pins\n(I2C pins, use ONLY \nif I2C is not used)
$Comp
L formula:Test_Point_SMD TP?
U 1 1 61F27C51
P 1500 1700
F 0 "TP?" V 1500 1900 50  0000 L CNN
F 1 "PB14" V 1500 2050 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1500 1550 50  0001 C CNN
F 3 "" H 1500 1700 50  0001 C CNN
	1    1500 1700
	0    -1   -1   0   
$EndComp
$Comp
L formula:Test_Point_SMD TP?
U 1 1 61F27E7D
P 1700 1800
F 0 "TP?" V 1700 2000 50  0000 L CNN
F 1 "PB15" V 1700 2150 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1700 1650 50  0001 C CNN
F 3 "" H 1700 1800 50  0001 C CNN
	1    1700 1800
	0    -1   -1   0   
$EndComp
$Comp
L formula:Test_Point_SMD TP?
U 1 1 61F280D7
P 1500 1900
F 0 "TP?" V 1500 2100 50  0000 L CNN
F 1 "PA8" V 1500 2250 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1500 1750 50  0001 C CNN
F 3 "" H 1500 1900 50  0001 C CNN
	1    1500 1900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1550 1700 3250 1700
Wire Wire Line
	1750 1800 3250 1800
Wire Wire Line
	1550 1900 3250 1900
Text GLabel 9300 6100 2    50   Input ~ 0
Y_LIMIT_SW2
Text GLabel 9300 5900 2    50   Input ~ 0
X_LIMIT_SW2
Wire Wire Line
	9150 5350 9300 5350
Wire Wire Line
	9300 5250 9150 5250
Text Label 9300 5150 0    50   ~ 0
PUMP_GND
Text Label 9300 5250 0    50   ~ 0
SERVO
$Comp
L Connector:Screw_Terminal_01x04 J?
U 1 1 61F77CD1
P 8950 5250
F 0 "J?" H 8900 4850 50  0000 L CNN
F 1 "SKITTLE PICKUP" H 8650 4950 50  0000 L CNN
F 2 "" H 8950 5250 50  0001 C CNN
F 3 "~" H 8950 5250 50  0001 C CNN
	1    8950 5250
	-1   0    0    1   
$EndComp
$Comp
L formula:SSM3K333R Q?
U 1 1 620F7C0F
P 9650 1900
F 0 "Q?" H 9856 1946 50  0000 L CNN
F 1 "SSM3K333R" H 9856 1855 50  0000 L CNN
F 2 "footprints:SOT-23F" H 9850 1825 50  0001 L CIN
F 3 "https://drive.google.com/drive/folders/0B-V-iZf33Y4GNzhDQTJZanJRbVk" H 9850 1975 50  0001 L CNN
F 4 "DK" H 10150 2275 60  0001 C CNN "MFN"
F 5 "SSM3K333RLFCT-ND" H 10050 2175 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/product-detail/en/toshiba-semiconductor-and-storage/SSM3K333RLF/SSM3K333RLFCT-ND/3522391" H 9950 2075 60  0001 C CNN "PurchasingLink"
	1    9650 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 620F82B5
P 9750 1300
F 0 "#PWR?" H 9750 1150 50  0001 C CNN
F 1 "+12V" H 9765 1473 50  0000 C CNN
F 2 "" H 9750 1300 50  0001 C CNN
F 3 "" H 9750 1300 50  0001 C CNN
	1    9750 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 620FAEC4
P 9750 2600
F 0 "#PWR?" H 9750 2350 50  0001 C CNN
F 1 "GND" H 9755 2427 50  0000 C CNN
F 2 "" H 9750 2600 50  0001 C CNN
F 3 "" H 9750 2600 50  0001 C CNN
	1    9750 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 2100 9750 2450
Text GLabel 8800 1900 0    50   Input ~ 0
VALVE_CONTROL
$Comp
L formula:R_10K R?
U 1 1 62101034
P 9200 2200
F 0 "R?" H 9270 2246 50  0000 L CNN
F 1 "R_10K" H 9270 2155 50  0000 L CNN
F 2 "footprints:R_0805_OEM" H 9130 2200 50  0001 C CNN
F 3 "http://www.bourns.com/data/global/pdfs/CRS.pdf" H 9280 2200 50  0001 C CNN
F 4 "DK" H 9200 2200 60  0001 C CNN "MFN"
F 5 "CRS0805-FX-1002ELFCT-ND" H 9200 2200 60  0001 C CNN "MPN"
F 6 "https://www.digikey.com/products/en?keywords=CRS0805-FX-1002ELFCT-ND" H 9680 2600 60  0001 C CNN "PurchasingLink"
	1    9200 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 1900 9200 2050
Connection ~ 9200 1900
Wire Wire Line
	9200 1900 9450 1900
Wire Wire Line
	9200 2450 9200 2350
Wire Wire Line
	9200 2450 9750 2450
Connection ~ 9750 2450
Wire Wire Line
	9750 2450 9750 2600
Wire Wire Line
	9750 1300 9750 1700
Wire Wire Line
	8800 1900 9200 1900
$Comp
L formula:Test_Point_SMD TP?
U 1 1 6213BFCC
P 6550 2700
F 0 "TP?" V 6550 3050 50  0000 L CNN
F 1 "PA3" V 6550 2900 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 6550 2550 50  0001 C CNN
F 3 "" H 6550 2700 50  0001 C CNN
	1    6550 2700
	0    1    1    0   
$EndComp
$Comp
L formula:Test_Point_SMD TP?
U 1 1 621451D4
P 6350 2800
F 0 "TP?" V 6350 3150 50  0000 L CNN
F 1 "PA2" V 6350 3000 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 6350 2650 50  0001 C CNN
F 3 "" H 6350 2800 50  0001 C CNN
	1    6350 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2700 6500 2700
Wire Wire Line
	4450 2800 6300 2800
$Comp
L formula:Test_Point_SMD TP?
U 1 1 62150427
P 1700 2000
F 0 "TP?" V 1700 2200 50  0000 L CNN
F 1 "PA9" V 1700 2350 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1700 1850 50  0001 C CNN
F 3 "" H 1700 2000 50  0001 C CNN
	1    1700 2000
	0    -1   -1   0   
$EndComp
$Comp
L formula:Test_Point_SMD TP?
U 1 1 62150879
P 1500 2100
F 0 "TP?" V 1500 2300 50  0000 L CNN
F 1 "PA10" V 1500 2450 50  0000 L CNN
F 2 "footprints:Test_Point_SMD" H 1500 1950 50  0001 C CNN
F 3 "" H 1500 2100 50  0001 C CNN
	1    1500 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1750 2000 3250 2000
Wire Wire Line
	1550 2100 3250 2100
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 6216431F
P 4650 6050
F 0 "J?" H 4568 5625 50  0000 C CNN
F 1 "Conn_01x04" H 4568 5716 50  0000 C CNN
F 2 "" H 4650 6050 50  0001 C CNN
F 3 "~" H 4650 6050 50  0001 C CNN
	1    4650 6050
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62164327
P 5250 5700
F 0 "#PWR?" H 5250 5550 50  0001 C CNN
F 1 "+5V" H 5265 5873 50  0000 C CNN
F 2 "" H 5250 5700 50  0001 C CNN
F 3 "" H 5250 5700 50  0001 C CNN
	1    5250 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5850 5250 5850
Wire Wire Line
	5250 5850 5250 5700
$Comp
L power:GND #PWR?
U 1 1 6216432F
P 5200 6200
F 0 "#PWR?" H 5200 5950 50  0001 C CNN
F 1 "GND" H 5205 6027 50  0000 C CNN
F 2 "" H 5200 6200 50  0001 C CNN
F 3 "" H 5200 6200 50  0001 C CNN
	1    5200 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 6150 5200 6150
Wire Wire Line
	5200 6150 5200 6200
Wire Wire Line
	4850 5950 5050 5950
Wire Wire Line
	5050 6050 4850 6050
Text Label 5050 5950 0    50   ~ 0
PA3(RxD)
Text Label 5050 6050 0    50   ~ 0
PA2(TxD)
Text Notes 4550 6150 1    50   ~ 0
USART 2
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 62181BC5
P 4650 4950
F 0 "J?" H 4568 4525 50  0000 C CNN
F 1 "Conn_01x04" H 4568 4616 50  0000 C CNN
F 2 "" H 4650 4950 50  0001 C CNN
F 3 "~" H 4650 4950 50  0001 C CNN
	1    4650 4950
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62181BCD
P 5250 4600
F 0 "#PWR?" H 5250 4450 50  0001 C CNN
F 1 "+5V" H 5265 4773 50  0000 C CNN
F 2 "" H 5250 4600 50  0001 C CNN
F 3 "" H 5250 4600 50  0001 C CNN
	1    5250 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4750 5250 4750
Wire Wire Line
	5250 4750 5250 4600
$Comp
L power:GND #PWR?
U 1 1 62181BD5
P 5200 5100
F 0 "#PWR?" H 5200 4850 50  0001 C CNN
F 1 "GND" H 5205 4927 50  0000 C CNN
F 2 "" H 5200 5100 50  0001 C CNN
F 3 "" H 5200 5100 50  0001 C CNN
	1    5200 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5050 5200 5050
Wire Wire Line
	5200 5050 5200 5100
Wire Wire Line
	4850 4850 5050 4850
Wire Wire Line
	5050 4950 4850 4950
Text Label 5050 4950 0    50   ~ 0
(TxD)PA9
Text Label 5050 4850 0    50   ~ 0
(RxD)PA10
Text Notes 4550 4750 3    50   ~ 0
USART 1
Text Notes 3650 4200 0    79   ~ 0
Connectors for Communication (I2C, USART)
Wire Notes Line
	3450 4000 3450 7700
Wire Notes Line
	3450 7700 6450 7700
Wire Notes Line
	6450 7700 6450 4000
Wire Notes Line
	6450 4000 3450 4000
Text GLabel 2200 3000 0    50   Input ~ 0
X_LIMIT_SW1
Text GLabel 2200 3100 0    50   Input ~ 0
X_LIMIT_SW2
Text GLabel 2200 1500 0    50   Input ~ 0
Y_LIMIT_SW1
Text GLabel 2200 1600 0    50   Input ~ 0
Y_LIMIT_SW2
Wire Wire Line
	2200 1500 3250 1500
Wire Wire Line
	3250 1600 2200 1600
Text Label 9300 5350 0    50   ~ 0
VALVE_CONTROL
$Comp
L power:GND #PWR?
U 1 1 622ED50C
P 10050 5250
F 0 "#PWR?" H 10050 5000 50  0001 C CNN
F 1 "GND" H 10055 5077 50  0000 C CNN
F 2 "" H 10050 5250 50  0001 C CNN
F 3 "" H 10050 5250 50  0001 C CNN
	1    10050 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 5150 10050 5250
Wire Wire Line
	9150 5150 10050 5150
Text Label 9300 5050 0    50   ~ 0
PUMP_PWR
$Comp
L power:+12V #PWR?
U 1 1 622F585D
P 10050 4900
F 0 "#PWR?" H 10050 4750 50  0001 C CNN
F 1 "+12V" H 10065 5073 50  0000 C CNN
F 2 "" H 10050 4900 50  0001 C CNN
F 3 "" H 10050 4900 50  0001 C CNN
	1    10050 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 5050 10050 4900
Wire Wire Line
	9150 5050 10050 5050
$Comp
L Connector:Screw_Terminal_01x04 J?
U 1 1 61C4A68E
P 8950 4300
F 0 "J?" H 8950 4000 50  0000 C CNN
F 1 "POWER" H 8950 4500 50  0000 C CNN
F 2 "" H 8950 4300 50  0001 C CNN
F 3 "~" H 8950 4300 50  0001 C CNN
	1    8950 4300
	-1   0    0    1   
$EndComp
Text Notes 8950 850  0    79   ~ 0
Valve LSD
Wire Notes Line
	7950 650  7950 2900
Wire Notes Line
	7950 2900 10450 2900
Wire Notes Line
	10450 2900 10450 650 
Wire Notes Line
	10450 650  7950 650 
$EndSCHEMATC

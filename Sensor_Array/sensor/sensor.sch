EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
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
L R_PHOTO R2
U 1 1 58DC40E9
P 5250 3350
F 0 "R2" H 5300 3400 50  0000 L CNN
F 1 "R_PHOTO" H 5300 3350 50  0000 L TNN
F 2 "" V 5300 3100 50  0000 L CNN
F 3 "" H 5250 3300 50  0000 C CNN
	1    5250 3350
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 58DC41A6
P 5250 2900
F 0 "R1" V 5330 2900 50  0000 C CNN
F 1 "4K7" V 5250 2900 50  0000 C CNN
F 2 "" V 5180 2900 50  0000 C CNN
F 3 "" H 5250 2900 50  0000 C CNN
	1    5250 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3050 5250 3200
$Comp
L VDD #PWR1
U 1 1 58DC420D
P 5250 2650
F 0 "#PWR1" H 5250 2500 50  0001 C CNN
F 1 "VDD" H 5250 2800 50  0000 C CNN
F 2 "" H 5250 2650 50  0000 C CNN
F 3 "" H 5250 2650 50  0000 C CNN
	1    5250 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 58DC4225
P 5250 3600
F 0 "#PWR2" H 5250 3350 50  0001 C CNN
F 1 "GND" H 5250 3450 50  0000 C CNN
F 2 "" H 5250 3600 50  0000 C CNN
F 3 "" H 5250 3600 50  0000 C CNN
	1    5250 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3500 5250 3600
Wire Wire Line
	5250 2650 5250 2750
Wire Wire Line
	5250 3100 5700 3100
Connection ~ 5250 3100
Text Label 5700 3100 0    60   ~ 0
ADC_PIN
$EndSCHEMATC

#!/bin/bash

MMCU=atmega328p
#MMCU=atmega168
AVR_TYPE=ATMEGA328P
#AVR_TYPE=ATMEGA168
BAUD=57600 # atmega328p
#BAUD=19200 # atmega168

echo "MMCU set to $MMCU"
echo "AVR_TYPE set to $AVR_TYPE"
echo "BAUD set to $BAUD"

rm -rf build || true
mkdir build

# compile files
avr-gcc -Os -DF_CPU=16000000UL -mmcu=$MMCU -c -o build/at28c256.o -Wall at28c256/at28c256.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=$MMCU -c -o build/servo.o -Wall servo/servo.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=$MMCU -c -o build/rf24.o -Wall rf24/rf24.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=$MMCU -c -o build/util.o -Wall ard/util.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=$MMCU -c -o build/serial.o -Wall ard/serial.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=$MMCU -c -o build/pins.o -Wall ard/pins.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=$MMCU -c -o build/main.o -Wall main.c

# compile binary
avr-gcc -mmcu=$MMCU build/*.o -o build/main

# create file to upload to arduino
avr-objcopy -O ihex -R .eeprom build/main build/main.hex

# upload to arduino
avrdude -F -V -c arduino -p $AVR_TYPE -P $1 -b $BAUD -U flash:w:build/main.hex

# Makefile to build and flash AVR C code using avr-gcc and avrdude

MCU = atmega32
F_CPU = 16000000UL
SRC = src/main.c
TARGET = main

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

all:
	avr-gcc $(CFLAGS) -o build/$(TARGET).elf $(SRC)
	avr-objcopy -O ihex build/$(TARGET).elf build/$(TARGET).hex

flash:
	avrdude -c usbasp -p m32 -U flash:w:build/$(TARGET).hex

clean:
	rm -f build/*.elf build/*.hex

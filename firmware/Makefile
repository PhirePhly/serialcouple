MCU = attiny2313
F_CPU = 8000000
AVRDUDE_PROGRAMMER = usbtiny

CFLAGS = -g -Os -funsigned-char -funsigned-bitfields -fpack-struct \
	 -fshort-enums -Wall -Wstrict-prototypes -DF_CPU=$(F_CPU) \
	 -mmcu=$(MCU) -std=gnu99 -ffreestanding
AVRDUDE_FLAGS = -p $(MCU) -c $(AVRDUDE_PROGRAMMER)


# Standard build and program target
program:	compile
	avrdude -p $(MCU) -c $(AVRDUDE_PROGRAMMER) -U flash:w:serialcouple.hex

compile:	serialcouple.c spi.c uart.c
	avr-gcc $(CFLAGS) serialcouple.c -o serialcouple.elf
	# convert elf to ihex for avrdude
	avr-objcopy -O ihex -R .eeprom serialcouple.elf serialcouple.hex

# Needed to configure AVR hardware for proper operation
# Only needs to be performed once per chip
burn-fuse:
	avrdude $(AVRDUDE_FLAGS) -u -U lfuse:w:0xe8:m -U hfuse:w:0x9f:m

clean:
	@echo
	@echo Cleaning directory...
	rm -f *.hex
	rm -f *.elf
	rm -f *~

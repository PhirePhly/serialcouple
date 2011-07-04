// Kenneth Finnegan, 2011 - GPLv3
// http://code.google.com/p/serialcouple/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.c"
#include "spi.c"

int main(void) {
	int i = 0;

	DDRB = (1<<4); // SS

	spi_init();
	uart_init();

	while (1) {
		PORTB &= ~(1<<4); // SS low
		unsigned char tempread[4];
		for (i=0; i<4; i++) {
			tempread[i] = spi_xfer(0x00);
		}
		PORTB |= (1<<4); // SS high

		if (tempread[1] & 0x01) {
			uart_print_string("ERROR ");
		} else {
			uart_print_hex(tempread[0]);
			uart_print_hex(tempread[1]);
			uart_putchar(' ');
			int ttemp = (tempread[0] << 8) | tempread[1];
			uart_print_int(ttemp / 16);
			uart_putchar('.');
			char* decimals[4] = {"00", "25", "50", "75"};
			uart_print_string(decimals[(tempread[1] >> 2) & 0x03]);
		}


		uart_putchar('\n');
		uart_putchar('\r');
		_delay_ms(500);
	}
}


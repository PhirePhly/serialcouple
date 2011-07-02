// Kenneth Finnegan, 2011 - GPLv3
// http://code.google.com/p/serialcouple/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.c"
#include "spi.c"

void print_hex (unsigned char d) {
	char vals[] = {	'0', '1', '2', '3', '4', '5', '6', '7',
			'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	uart_putchar(vals[d>>4]);
	uart_putchar(vals[d & 0xF]);
}

int main(void) {
	int i = 0;

	DDRB = (1<<4); // SS

	spi_init();
	uart_init();

	while (1) {
		PORTB &= ~(1<<4);
		for (i=0; i<4; i++) {
			unsigned char c = spi_xfer(0);
			print_hex(c);
		}
		PORTB |= (1<<4);
		uart_putchar('\n');
		uart_putchar('\r');
		_delay_ms(100);
	}
}


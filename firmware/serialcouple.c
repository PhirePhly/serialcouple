// Kenneth Finnegan, 2011 - GPLv3
// http://code.google.com/p/serialcouple/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.c"
#include "spi.c"

// Pin of PORTB with Slave Select
#define ADC_SS		(4)
// Milliseconds between readings
#define PAUSE_TIME	1000

unsigned char ADCread[4]; // 4 byte bitfield from MAX31855 ADC
unsigned int millisec_cnt; // milliseconds pass the top of the arbitrary second

// Update stored temperature readings with new readings from MAX31855 ADC
void ADCXfer (void) {
	int i;
	PORTB &= ~(1<<ADC_SS); // SS low
	for (i=0; i<4; i++) {
		ADCread[i] = spi_xfer(0x00);
	}
	PORTB |= (1<<ADC_SS); // SS high
}

// Print formatted reading on serial port
void print_reading (void) {
	if (ADCread[1] & 0x01) {
		uart_print_string("ERROR ");
	} else {
		int ttemp = (ADCread[0] << 8) | ADCread[1];
		// Print whole number part of temperature
		uart_print_int(ttemp >> 4 );
		uart_putchar('.');
		// Convert the fixed point fractions to decimal by hand
		char* decimals[4] = {"00", "25", "50", "75"};
		uart_print_string(decimals[(ADCread[1] >> 2) & 0x03]);
	}
	uart_print_CR();
}

// Timer interrupt - Expected rate of 1kHz (1ms)
SIGNAL ( SIG_OUTPUT_COMPARE0A ) {
	millisec_cnt = (millisec_cnt + 1) % PAUSE_TIME;

	// Has it been PAUSE_TIME milliseconds yet?
	if (millisec_cnt == 0) { 
		ADCXfer();
		print_reading();
	}
}


int main(void) {
	int i = 0;

	DDRB = (1<<4); // SS Output
	millisec_cnt = 0; 

	spi_init();
	uart_init();
	
	TCCR0A = (1<<WGM01); // Clear Timer on Compare mode
	TCCR0B = (1<<CS01) | (1<<CS00); //  /64 prescale 8MHz down to 125kHz
	OCR0A = 125; // overflow at 1kHz
	TIMSK = (1<<OCIE0A); // Enable OUTPUT_COMPARE0A int
	sei(); // Enable interrupts

	while (1) {
		// I should sleep here and offload heavy lifting...
	}
}


// Kenneth Finnegan, 2011 - GPLv3
// kennethfinnegan.blogspot.com
//
// Drivers for ATTiny USI-based SPI master
// Specifically developed and tested on ATTiny2313

#define SPI_SCK_L	((1<<USIWM0)|(1<<USITC))
#define SPI_SCK_H	((1<<USIWM0)|(1<<USITC)|(1<<USICLK))

void spi_init(void) {
	// Set MOSI & SCK pins as outputs
	DDRB |= (1<<5) | (1<<7);
	// Set MISO as input
	DDRB &= ~(1<<6);
}

unsigned char spi_xfer(unsigned char d) {
	unsigned char dn = 0, i;
	for (i=0; i<8; i++) {
		PORTB |= (1<<7);
		PORTB &= ~(1<<7);
		dn = (dn << 1) | !!(PINB & (1<<6));
	}
	return dn;
}

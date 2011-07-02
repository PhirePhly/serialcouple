// Kenneth Finnegan, 2011 - GPLv3
// kennethfinnegan.blogspot.com
//
// Drivers for ATTiny UART

// Setup UART Xcver
void uart_init(void) {
	UCSRA = 0x00;
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0);
	// For speeed divider at 8MHz :
	// 9600	baud	51
	// 115k baud	3
	UBRRL = 51;
}

// Output a single character
// Will spin-lock waiting for prev character to finish
void uart_putchar (char c) {
	// Spin-lock until buffer empty
	while ( ! (UCSRA & (1<<UDRE)) ) ;
	// Place character in Tx buffer
	UDR = c;
}

// Receive one character
// Will return zero when there is no character
int uart_getchar (void) {
	if (UCSRA & (1<<RXC)) {
		return UDR;
	}
	// No character available
	return -1;
}


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

/////////  HELPER FUNCTIONS /////////

void uart_print_string (char * string) {
	while (*string) {
		uart_putchar(*string++);
	}
}

void uart_print_hex (unsigned char d) {
	char vals[] = {	'0', '1', '2', '3', '4', '5', '6', '7',
			'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	uart_putchar(vals[d>>4]);
	uart_putchar(vals[d & 0xF]);
}

void uart_print_int (int i) {
	if (i < 0) {
		uart_putchar('-');
		uart_print_int(-i);
		return;
	}
	if (i > 9) {
		uart_print_int(i / 10);
	}
	if (i == 0) { // done!
		uart_putchar('0');
		return;
	}
	uart_putchar('0' + (i % 10));
	return;
}

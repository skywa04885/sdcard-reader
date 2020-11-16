#include "usart.h"

static FILE usart_stream = FDEV_SETUP_STREAM(usart_stream_put_char, NULL, _FDEV_SETUP_WRITE);

/**
 * Initializes USART
 */
void usart_init(void)
{
	UBRR0L = UBRR_VAL;
	UBRR0H = UBRR_VAL >> 8;

	UCSR0A = 0x00;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	stdout = stderr = &usart_stream;
}

/**
 * Writes an char over USART
 */
void usart_stream_put_char(char c, FILE *f)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}
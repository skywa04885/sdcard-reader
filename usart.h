#ifndef _USART_H
#define _USART_H

#include "default.h"

/**
 * Initializes USART
 */
void usart_init(void);

/**
 * Writes an char over USART
 */
void usart_stream_put_char(char c, FILE *f);

#endif
/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#ifndef _DEFAULT_H
#define _DEFAULT_H

/*********************************
 * Preprocessor
 ********************************/

#define F_CPU				16000000UL
#define USART_BAUD			38400
#define I2C_BITRATE			400000

#define UBRR_VAL			((F_CPU / (16 * USART_BAUD)) - 1)
#define TWBR_VAL			(((F_CPU / I2C_BITRATE) - 16) / 2)

/*********************************
 * C Standard Library
 ********************************/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*********************************
 * AVR
 ********************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/*********************************
 * Util
 ********************************/

#include <util/delay.h>

#endif

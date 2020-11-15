/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#ifndef _I2C_H
#define _I2C_H

#include "default.h"

/**
 * Initializes the I2C hardware
 */
void i2c_init(void);

/**
 * Sends the start bit
 */
void i2c_start(void);

/**
 * Sends the stop bit
 */
void i2c_stop();

/**
 * Writes an 8-bit byte to the I2C bus
 */
void i2c_write_byte(uint8_t b);

/**
 * Reads an 8-bit byte from the I2C bus, without ACK
 */

uint8_t i2c_read_byte_nack(void);

/**
 * Reads an 8-bit byte from the I2C bus, with ACK
 */
uint8_t i2c_read_byte_ack(void);

#endif

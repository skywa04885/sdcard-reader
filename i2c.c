/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#include "i2c.h"

/**
 * Initializes the I2C hardware
 */
void i2c_init(void)
{
    TWBR = TWBR_VAL;
	TWSR = 0x00;
	TWCR = (1 << TWEN);
}


/**
 * Sends the start bit
 */
void i2c_start(void)
{
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT)));
}

/**
 * Sends the stop bit
 */
void i2c_stop()
{
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
}

/**
 * Writes an 8-bit byte to the I2C bus
 */
void i2c_write_byte(uint8_t b)
{
	TWDR = b;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

/**
 * Reads an 8-bit byte from the I2C bus, without ACK
 */
uint8_t i2c_read_byte_nack(void)
{
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

/**
 * Reads an 8-bit byte from the I2C bus, with ACK
 */
uint8_t i2c_read_byte_ack(void)
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}
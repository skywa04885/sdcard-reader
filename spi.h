/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#ifndef _SPI_H
#define _SPI_H

#include "default.h"

/*********************************
 * Pins
 ********************************/

#define SPI_DDR				DDRB
#define SPI_PORT			PORTB
#define SPI_PIN				PINB
#define SPI_SCK				PB5
#define SPI_MISO			PB4
#define SPI_MOSI			PB3
#define SPI_SS				PB2

/*********************************
 * Prototypes
 ********************************/

/**
 * Transceives data
 */
uint8_t spi_transceive(uint8_t b);

/**
 * Initializes the SPI hardware
 */
void spi_init(void);

/**
 * Writes an series bytes over the SPI bus
 */
void spi_write_bytes(uint8_t *p, uint8_t n);

/**
 * Reads an byte from the SPI bus
 */
uint8_t spi_read_byte(void);

/**
 * Reads an series of bytes from the SPI bus
 */
void spi_read_bytes(uint8_t *ret, uint8_t n);

/**
 * Selects the device on the default SS pin
 */
void spi_select_default(void);

/**
 * Deselects the device on the default SS pin
 */
void spi_deselect_default(void);

#endif

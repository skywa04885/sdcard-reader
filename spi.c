/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#include "spi.h"

/**
 * Initializes the SPI hardware
 */

void spi_init(void)
{
	// Configures the SCK, MOSI and CS pin as output, and the MISO
	//  as  input
	SPI_DDR |= (1 << SPI_SCK) | (1 << SPI_MOSI) | (1 << SPI_SS);
	SPI_DDR |= SPI_MISO;

	// Clears the status register, and enables the SPI hardware as
	//  master and a clock prescalar of osc/128
	SPSR = 0x00;
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) << (1 << SPR0);

	// Deselects the SPI device
	spi_deselect_default();
}

/**
 * Transceives data
 */
uint8_t spi_transceive(uint8_t b)
{
	SPDR = b;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}

/**
 * Writes an series bytes over the SPI bus
 */
void spi_write_bytes(uint8_t *p, uint8_t n)
{
	for (uint8_t i = 0; i < n; ++i)
		spi_transceive(p[i]);
}

/**
 * Reads an byte from the SPI bus
 */
uint8_t spi_read_byte(void)
{
	uint8_t res, i;
	while ((res = spi_transceive(0xFF)) == 0xFF) {
		if (i++ > 16) break;
	}
	return res;
}

/**
 * Reads an series of bytes from the SPI bus
 */
void spi_read_bytes(uint8_t *ret, uint8_t n)
{
	for (uint8_t i = 0; i < n; ++i)
		ret[i] = spi_read_byte();
}

/**
 * Selects the device on the default SS pin
 */
void spi_select_default(void)
{
	SPI_PORT &= ~(1 << SPI_SS);
}

/**
 * Deselects the device on the default SS pin
 */
void spi_deselect_default(void)
{
	SPI_PORT |= (1 << SPI_SS);
}

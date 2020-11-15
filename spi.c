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
	SPI_DDR &= ~SPI_MISO;

	// Clears the status register, and enables the SPI hardware as
	//  master and a clock prescalar of osc/64
	SPSR = 0x00;
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1);
	
	// Deselects the default SS pin
	spi_deselect_default();
}

/**
 * Writes an byte over the SPI bus
 */
void spi_write_byte(uint8_t b)
{
	SPDR = b;
	while (!(SPSR & (1 << SPIF)));
}

/**
 * Reads an byte from the SPI bus
 */
uint8_t spi_read_byte(void)
{
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
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

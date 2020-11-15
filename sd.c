/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#include "sd.h"

/**
 * Calculates the CRC7 check sum for the specified data
 */
uint8_t sd_calc_crc7(uint8_t *data, uint8_t n)
{
	
}

/**
 * Gets the CID register stucture from the SD card
 */
sd_cid_register_t sd_get_cid_register(void)
{
	// Builds the command stucture, which we will later use
	//  to request the register from the SD Card
	sd_spi_command_t command = SD_SPI_COMMAND_DEFAULT;
	command.command_index = SD_SPI_SEND_CID;
	command.argument = 0x00;
	// command.crc7 = 
}

/**
 * Gets the CSD register structure from the SD card
 */
sd_csd_register_t sd_get_csd_register(void)
{
}
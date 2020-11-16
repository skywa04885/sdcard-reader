/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#include "sd.h"

static volatile uint8_t __crc7_lookup_table[256];

/*********************************
 * Prototpes ( Communication )
 ********************************/

/**
 * Sends an command and reads the R1 response
 */
sd_spi_response_r1_t sd_send_cmd_get_r1(sd_spi_command_t cmd)
{
	sd_spi_response_r1_t res;

	// Calculates the CRC7 checksum
	cmd.crc7 = crc7(__crc7_lookup_table, (uint8_t *) &cmd, 5);

	// Writes the command and reads the response from the SD card
	//  after which we check for errors
	spi_transceive(0xFF);
	spi_select_default();
	spi_transceive(0xFF);

	spi_write_bytes((uint8_t *) &cmd, sizeof (sd_spi_command_t));
	spi_read_bytes((uint8_t *) &res, sizeof (sd_spi_response_r1_t));

	spi_transceive(0xFF);
	spi_deselect_default();
	spi_transceive(0xFF);

	// Returns the result
	return res;
}

/**
 * Sends an command and reads the R7 response
 */
sd_spi_response_r7_t sd_send_cmd_get_r7(sd_spi_command_t cmd)
{
	sd_spi_response_r7_t res;

	// Calculates the CRC7 checksum
	cmd.crc7 = crc7(__crc7_lookup_table, (uint8_t *) &cmd, 5);

	// Writes the command and reads the response from the SD card
	//  after which we check for errors
	spi_transceive(0xFF);
	spi_select_default();
	spi_transceive(0xFF);

	spi_write_bytes((uint8_t *) &cmd, sizeof (sd_spi_command_t));
	spi_read_bytes((uint8_t *) &res, sizeof (sd_spi_response_r7_t));

	spi_transceive(0xFF);
	spi_deselect_default();
	spi_transceive(0xFF);

	// Returns the result
	return res;
}

/*********************************
 * Prototpes ( General )
 ********************************/

/**
 * Initializes the SDCard
 */
void sd_init(void)
{
	// Generates the CRC7 lookup table
	crc7_generate_table(__crc7_lookup_table, SD_CRC7_POLYNOMIAL_BINARY);

	_delay_ms(1);
	spi_transceive(0xFF);
	spi_select_default();

	for (uint8_t i = 0; i < 74; ++i)
		spi_transceive(0xFF);

	spi_deselect_default();
	spi_transceive(0xFF);
}

/**
 * Goes into IDLE state
 */
sd_spi_response_r1_t sd_go_idle()
{
	sd_spi_response_r1_t res;

	sd_spi_command_t cmd = SD_SPI_COMMAND_DEFAULT;
	cmd.command_index = SD_SPI_GO_IDLE_STATE;
	cmd.argument = 0x00;

	res = sd_send_cmd_get_r1(cmd);

	return res;
}

/**
 * Gets the operating conditions of the SD card
 */
sd_spi_response_r7_t sd_get_ocr(void)
{
	sd_spi_response_r7_t res;

	// Selects the device
	spi_transceive(0xFF);
	spi_select_default();
	spi_transceive(0xFF);

	// Builds the command we want to send, the argument will
	//  be zero, since it is not required
	sd_spi_command_t cmd = SD_SPI_COMMAND_DEFAULT;
	cmd.command_index = SD_SPI_SEND_IF_COND;
	cmd.argument = 0x00;

	// Sends the command and reads the response, after which
	//  we de-select the device and return the response
	res = sd_send_cmd_get_r7(cmd);

	spi_transceive(0xFF);
	spi_deselect_default();
	spi_transceive(0xFF);
	return res;
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

	// Sends the command and reads the response
	sd_spi_response_r1_t resp = sd_send_cmd_get_r1(command);

}

/**
 * Gets the CSD register structure from the SD card
 */
sd_csd_register_t sd_get_csd_register(void)
{
}

/*********************************
 * Debugging
 ********************************/

/**
 * Logs the R1 response over serial
 */
void sd_spi_log_r1(sd_spi_response_r1_t resp)
{
	printf(
		"r1 {\r\n"
		"\tpe: %c\r\n"
		"\tae: %c\r\n"
		"\tese: %c\r\n"
		"\tcce: %c\r\n"
		"\tic: %c\r\n"
		"\ter: %c\r\n"
		"\tiis: %c\r\n"
		"}\r\n",
		/* ======================= */
		resp.parameter_error ? '1' : '0',
		resp.address_error ? '1' : '0',
		resp.erase_sequence_error ? '1' : '0',
		resp.com_crc_error ? '1' : '0',
		resp.illegal_command ? '1' : '0',
		resp.erase_reset ? '1' : '0',
		resp.in_idle_state ? '1' : '0'
	);
}

/**
 * Logs the command over serial
 */
void sd_spi_log_cmd(sd_spi_command_t cmd)
{
	printf(
		"cmd {\r\n"
		"\tsb: %c\r\n"
		"\ttb: %c\r\n"
		"\tci: %d\r\n"
		"\targ: %02X\r\n"
		"\tcrc7: %02X\r\n"
		"\teb: %c\r\n"
		"}\r\n",
		/* ======================= */
		cmd.start_bit ? '1' : '0',
		cmd.transmission_bit ? '1' : '0',
		cmd.command_index,
		cmd.argument,
		cmd.crc7,
		cmd.end_bit ? '1' : '0'
	);
}

/**
 * Logs the R7 response over serial
 */
void sd_spi_log_r7(sd_spi_response_r7_t resp)
{
	printf(
		"r7 {\r\n"
		"\t r1 {\r\n"
		"\t\tpe: %c\r\n"
		"\t\tae: %c\r\n"
		"\t\tese: %c\r\n"
		"\t\tcce: %c\r\n"
		"\t\tic: %c\r\n"
		"\t\ter: %c\r\n"
		"\t\tiis: %c\r\n"
		"\t}\r\n"
		"\tv: %02X\r\n"
		"\tva: %02X\r\n"
		"\te: %02X\r\n"
		"}\r\n",
		/* ======================= */
		resp.r1.parameter_error ? '1' : '0',
		resp.r1.address_error ? '1' : '0',
		resp.r1.erase_sequence_error ? '1' : '0',
		resp.r1.com_crc_error ? '1' : '0',
		resp.r1.illegal_command ? '1' : '0',
		resp.r1.erase_reset ? '1' : '0',
		resp.r1.in_idle_state ? '1' : '0',
		/* ======================= */
		resp.command_version,
		resp.voltage_accepted,
		resp.echo
	);
}
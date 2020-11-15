/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#include "ssd1306.h"

extern uint8_t __nullchar[5];
extern uint8_t __lookup_table_misc[][5];
extern uint8_t __lookup_table_alphabet[][5];

/**
 * Initializes the ssd1306
 */
void ssd1306_init(void)
{
	// Waits some time for the SSD1306 to stabalize, after which we
	//  enable the display, and set the contrast to 128 ( max 256 )
	_delay_us(SSD1306_STARTUP_DELAY);
	ssd1306_enable();
	ssd1306_contrast_set(128);

	// Sets the memory addressing mode to page addressing, this is standard
	//  but we just do it be sure
	ssd1306_set_memory_addressing_mode(SSD1306_PAGE_ADDRESSING_MODE);
}

/**
 * Enables the SSD1306
 */
void ssd1306_enable(void)
{
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_CMD_DISPLAY_ON);
	_delay_ms(SSD1306_DISPLAY_ON_DELAY);
}

/**
 * Disables the SSD1306
 */
void ssd1306_disable(void)
{
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_CMD_DISPLAY_OFF);
	_delay_ms(SSD1306_DISPLAY_OFF_DELAY);
}

/**
 * Write to the ssd1306
 */
void ssd1306_write(uint8_t control_byte, uint8_t data_byte)
{
	// Sends the I2C start bit, and writes the slave address. Since we're
	//  writing the LSB will be zero, indicating writing... If the LSB is set
	//  it indicates writing
	i2c_start();
	i2c_write_byte(SSD1306_SLAVE_ADDRESS << 1);

	// Sends the control byte and the data byte, after which we send the stop bit
	//  indicating that we're done
	i2c_write_byte(control_byte);
	i2c_write_byte(data_byte);
	i2c_stop();
}

/**
 * Performs continious horizontal scroll
 */
void ssd1306_continous_horizontal_scroll(
	ssd1306_continous_horizontal_scroll_param_t param)
{
	// Sends the scroll command, since the LSB of the command indicates if the horizontal
	//  scroll should go left or right, we will OR the direction bit to the RIGHT scroll command
	//  since the LSB of the right scroll is zero, and if the param direction is one, the command
	//  will go left.
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_SCRLCMD_HOR_RIGHT | param.direction);

	// Writes the dummy byte A ( 0x00 )
	ssd1306_write(SSD1306_CTRL_CMD, 0x00);

	// Writes the start page, after which we write the interval between
	//  scrolling, and write the end page.
	ssd1306_write(SSD1306_CTRL_CMD, param.start_page);
	ssd1306_write(SSD1306_CTRL_CMD, param.interval_frames);
	ssd1306_write(SSD1306_CTRL_CMD, param.end_page);

	// Writes dummy byte E ( 0x00 ) and F ( 0xFF )
	ssd1306_write(SSD1306_CTRL_CMD, 0x00);
	ssd1306_write(SSD1306_CTRL_CMD, 0xFF);
}

/**
 * Performs continious vertical and horizontal scroll
 */
void ssd1306_continous_vertical_and_horizontal_scroll(
	ssd1306_continous_vertical_and_horizontal_scroll_param_t param)
{
	// Sends the scroll command, the first two bits from the LSB will contain the direction
	//  by default these both are zero in the base, so we add the 0b01, 0b10 or 0b11 from the
	//  direction parameter.
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_SCRLCMD_VH |  param.direction);	

	// Writes the dummy byte A ( 0x00 )
	ssd1306_write(SSD1306_CTRL_CMD, 000);

	// Writes the start page, after which we write the interval, after which we write
	//  the end page and finally the scrolling offset.
	ssd1306_write(SSD1306_CTRL_CMD, param.start_page);
	ssd1306_write(SSD1306_CTRL_CMD, param.interval_frames);
	ssd1306_write(SSD1306_CTRL_CMD, param.end_page);
	ssd1306_write(SSD1306_CTRL_CMD, param.vertical_scrolling_offset);
}

/**
 * Sets the vertical scroll area
 */
void ssd1306_set_vertical_scroll_area(
	ssd1306_set_vertical_scroll_area_param_t param)
{
	// Writes the command to set the vertical scroll area, after which we write
	//  the number of fixed rows from the top, and the number of scrollable rows.
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_SCRLCMD_SET_V_AREA);
	ssd1306_write(SSD1306_CTRL_CMD, param.no_fixed_rows);
	ssd1306_write(SSD1306_CTRL_CMD, param.no_scroll_rows);
}

/**
 * Sets the lower column start address for the page addressing mode
 */
void ssd1306_set_lower_column_start_addr_for_page_addr_mode(uint8_t lower_nibble)
{
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_ACMD_SET_LCSA_FPAM | (lower_nibble & 0x0F));
}

/**
 * Sets the higher column start address for the page addressing mode
 */
void ssd1306_set_higher_column_start_addr_for_page_addr_mode(uint8_t higher_nibble)
{
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_ACMD_SET_HCSA_FPAM | (higher_nibble & 0x0F));
}

/**
 * Set the memory addressing mode
 */
void ssd1306_set_memory_addressing_mode(ssd1306_memory_addressing_mode_t mode)
{
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_ACMD_SET_ADDR_MODE);
	ssd1306_write(SSD1306_CTRL_CMD, mode & 0x03);
}

/**
 * Sets the column address
 */
void ssd1306_set_column_address(ssd1306_set_column_address_param_t param)
{
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_ACMD_SET_COL_ADDR);
	ssd1306_write(SSD1306_CTRL_CMD, param.start_addr);
	ssd1306_write(SSD1306_CTRL_CMD, param.end_addr);
}

/**
 * Sets the page address
 */
void ssd1306_set_page_address(ssd1306_set_page_addess_param_t param)
{
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_ACMD_SET_PAGE_ADDR);
	ssd1306_write(SSD1306_CTRL_CMD, param.start_addr);
	ssd1306_write(SSD1306_CTRL_CMD, param.end_addr);
}

/**
 * Sets the GDDRAM Page start address for the page addressing mode
 */
void ssd1306_set_page(uint8_t page)
{
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_ACMD_SET_SADDR_PAM | (page & 0x07));
}

/**
 * Clears the display
 */
void ssd1306_clear(void)
{
	// Loops over the pages
	for (uint8_t page = 0; page < SSD1306_PAGE_COUNT; ++page) {
		// Sets the page address
		ssd1306_set_page(page);

		// Loops over the columns, and writes zeroes
		for (uint8_t col = 0; col < SSD1306_COL_COUNT; ++col)
			ssd1306_write(SSD1306_CTRL_GDRAM, 0x00);
	}
}


/**
 * Writes an char to the current page
 */
void ssd1306_write_char(char c, uint8_t pos)
{
	ssd1306_set_column_address_param_t param;
	uint8_t *font_char = NULL;

	// Goes to the specified position on the screen
	param.start_addr = pos;
	param.end_addr = 127;
	ssd1306_set_column_address(param);

	// Gets the char from the lookup table
	if (c >= 0x41 && c <= 0x5A) {
		font_char = __lookup_table_alphabet[c - 0x41];
	} else if (c == ' ' || c == '\t') {
		for (uint8_t i = 0; i < 6; ++i)
			ssd1306_write(SSD1306_CTRL_GDRAM, 0x00);
		return;
	}

	// Draws the char and a 1-pixel space between chars
	for (uint8_t i = 0; i < 5; ++i)
		ssd1306_write(SSD1306_CTRL_GDRAM, font_char[i]);
	ssd1306_write(SSD1306_CTRL_GDRAM, 0x00);
}

/**
 * Writes an string to the current page
 */
void ssd1306_write_string(const char *str)
{
	uint8_t pos = (127 - 6); // 6: width of char
	while (*str != 0) {
		ssd1306_write_char(*str++, pos);
		pos -= 6;
	}
}
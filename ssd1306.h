/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#ifndef _SSD1306_H
#define _SSD1306_H

#include "default.h"
#include "i2c.h"

/*********************************
 * Preprocessor
 ********************************/

#define SSD1306_SLAVE_ADDRESS		0x3C
#define SSD1306_CTRL_GDRAM			0b01000000
#define SSD1306_CTRL_CMD			0b10000000
#define SSD1306_PAGE_COUNT			8
#define SSD1306_COL_COUNT			128

/*********************************
 * Commands
 ********************************/

#define SSD1306_CMD_CONTRAST_SET 	0x81	 	/* Sets the contrast to the specified value */
#define SSD1306_CMD_CONTRAST_RESET	0x7F		/* Restores default contrast */
#define SSD1306_CMD_ENT_ON_RES_RAM	0xA4		/* Entire display on, resume to ram content display */
#define SSD1306_CMD_ENT_ON_IGN_RAM	0xA5		/* Entire display on, ignore ram */
#define SSD1306_CMD_SET_NORM_MODE	0xA6		/* Enabbles normal mode */
#define SSD1306_CMD_SET_INV_MODE	0xA7		/* Enables inverted mode */
#define SSD1306_CMD_DISPLAY_OFF		0xAE		/* Turns the display off */
#define SSD1306_CMD_DISPLAY_ON		0xAF		/* Turns the display on */

/*********************************
 * Scrolling Commands
 ********************************/

#define SSD1306_SCRLCMD_HOR_RIGHT	0x26		/* Horizontal scroll right */
#define SSD1306_SCRLCMD_HOR_LEFT	0x27		/* Horizontal scroll left */

#define SSD1306_SCRLCMD_VH			0x28		/* Vertical and horizontal base */
#define SSD1306_SCRLCMD_VH_VR		0x29		/* Vertical and right */
#define SSD1306_SCRLCMD_VH_VL		0x2A		/* Vertical and left */

#define SSD1306_SCRLCMD_ENABLE_CONT	0x2E		/* Enables the scrolling configured in 0x26/0x27/0x29/0x2A */
#define SSD1306_SCRLCMD_DISA_CONT	0x2F		/* Disables the scolling configued in 0x26/0x27/0x29/0x2A */

#define SSD1306_SCRLCMD_SET_V_AREA	0xA3		/* Sets the vertical scroll area */

/*********************************
 * Addresing Setting Commands
 ********************************/

#define SSD1306_ACMD_SET_LCSA_FPAM	0x00		/* Set lower column start address for page addressing mode */
#define SSD1306_ACMD_SET_HCSA_FPAM	0x10		/* Set Higher Column Start Address for Page Addressing Mode */
#define SSD1306_ACMD_SET_ADDR_MODE	0x20 		/* Sets the addressing mode */
#define SSD1306_ACMD_SET_COL_ADDR	0x21		/* Sets the column address */
#define SSD1306_ACMD_SET_PAGE_ADDR	0x22		/* Sets the page address */
#define SSD1306_ACMD_SET_SADDR_PAM	0xB0		/* Sets the page start address for page addressing mode */

/*********************************
 * Interval Frames
 ********************************/

#define SSD1306_INTERVAL_FRAMES_5	0x00
#define SSD1306_INTERVAL_FRAMES_64	0x01
#define SSD1306_INTERVAL_FRAMES_128	0x02
#define SSD1306_INTERVAL_FRAMES_256	0x03
#define SSD1306_INTERVAL_FRAMES_3	0x04
#define SSD1306_INTERVAL_FRAMES_4	0x05
#define SSD1306_INTERVAL_FRAMES_25	0x06
#define SSD1306_INTERVAL_FRAMES_2	0x07

/*********************************
 * Delays
 ********************************/

#define SSD1306_STARTUP_DELAY		30
#define SSD1306_DISPLAY_ON_DELAY	100 /* ms */
#define SSD1306_DISPLAY_OFF_DELAY	100 /* ms */

/*********************************
 * Fake prototypes
 ********************************/

// Continous scrolling
#define ssd1306_enable_continous_scrolling() \
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_SCRLCMD_ENABLE_CONT)
#define ssd1306_disable_continous_scrolling() \
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_SCRLCMD_DISA_CONT)

// Contrast setting
#define ssd1306_contrast_set(A) \
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_CMD_CONTRAST_SET); \
	ssd1306_write(SSD1306_CTRL_CMD, A)
#define ssd1306_contrast_reset() \
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_CMD_CONTRAST_RESET);

// Display ON / OFF
#define ssd1306_entire_display_on() \
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_CMD_ENT_ON_IGN_RAM);
#define ssd1306_entire_display_on_restore() \
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_CMD_ENT_ON_RES_RAM);

// Normal / Inverse mode
#define ssd1306_enable_inverse_mode() \
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_CMD_SET_INV_MODE);
#define ssd1306_enable_normal_mode() \
	ssd1306_write(SSD1306_CTRL_CMD, SSD1306_CMD_SET_NORM_MODE);

/*********************************
 * Datatypes
 ********************************/

typedef enum {
	SSD1306_HORIZONTAL_ADDRESSING_MODE = 0,
	SSD1306_VERTICAL_ADDRESSING_MODE,
	SSD1306_PAGE_ADDRESSING_MODE,
	SSD1306_INVALID
} ssd1306_memory_addressing_mode_t;

typedef struct {
	unsigned direction : 1; /* 1: Left, 0: Right */
	unsigned start_page : 3;
	unsigned interval_frames : 3;
	unsigned end_page : 3;
	unsigned reserved : 6;
} ssd1306_continous_horizontal_scroll_param_t;

typedef struct {
	unsigned direction : 2; /* 0b01: Vertical and right, 0b10: vertical and left */
	unsigned start_page: 3;
	unsigned interval_frames : 3;
	unsigned end_page : 3;
	unsigned vertical_scrolling_offset : 6;
	unsigned reserved : 7;
} ssd1306_continous_vertical_and_horizontal_scroll_param_t;

typedef struct {
	unsigned no_fixed_rows : 6;
	unsigned no_scroll_rows : 7;
	unsigned reserved : 3;
} ssd1306_set_vertical_scroll_area_param_t;

typedef struct {
	unsigned start_addr : 7;
	unsigned end_addr : 7;
	unsigned reserved : 2;
} ssd1306_set_column_address_param_t;

typedef struct {
	unsigned start_addr : 3;
	unsigned end_addr : 3;
	unsigned reserved : 2;
} ssd1306_set_page_addess_param_t;

/*********************************
 * Prototypes ( General )
 ********************************/

/**
 * Initializes the ssd1306
 */
void ssd1306_init(void);

/**
 * Enables the SSD1306
 */
void ssd1306_enable(void);

/**
 * Disables the SSD1306
 */
void ssd1306_disable(void);

/**
 * Writes to the ssd1306
 */
void ssd1306_write(uint8_t control_byte, uint8_t data_byte);

/*********************************
 * Prototypes ( Scrolling )
 ********************************/

/**
 * Performs continious horizontal scroll
 */
void ssd1306_continous_horizontal_scroll(
	ssd1306_continous_horizontal_scroll_param_t param);

/**
 * Performs continious vertical and horizontal scroll
 */
void ssd1306_continous_vertical_and_horizontal_scroll(
	ssd1306_continous_vertical_and_horizontal_scroll_param_t param);

/**
 * Sets the vertical scroll area
 */
void ssd1306_set_vertical_scroll_area(
	ssd1306_set_vertical_scroll_area_param_t param);

/*********************************
 * Prototypes ( Addressing )
 ********************************/

/**
 * Sets the lower column start address for the page addressing mode
 */
void ssd1306_set_lower_column_start_addr_for_page_addr_mode(uint8_t lower_nibble);

/**
 * Sets the higher column start address for the page addressing mode
 */
void ssd1306_set_higher_column_start_addr_for_page_addr_mode(uint8_t higher_nibble);

/**
 * Set the memory addressing mode
 */
void ssd1306_set_memory_addressing_mode(ssd1306_memory_addressing_mode_t mode);

/**
 * Sets the column address
 */
void ssd1306_set_column_address(ssd1306_set_column_address_param_t param);

/**
 * Sets the page address
 */
void ssd1306_set_page_address(ssd1306_set_page_addess_param_t param);

/**
 * Sets the GDDRAM Page start address for the page addressing mode
 */
void ssd1306_set_page(uint8_t page);

/*********************************
 * Prototypes ( Graphics )
 ********************************/

/**
 * Clears the display
 */
void ssd1306_clear(void);

/**
 * Writes an char to the current page
 */
void ssd1306_write_char(char c, uint8_t pos);

/**
 * Writes an string to the current page
 */
void ssd1306_write_string(const char *str);

#endif

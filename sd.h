/*
	Copyright Luke Rieff 2020 - SD1306 SSD1306-SSD1780 OLED Driver
*/

#ifndef _SD_H
#define _SD_H

#include "default.h"

/*********************************
 * Definitions
 ********************************/

#define SD_SPI_DATA_RESPONSE_TOKEN_ACCEPTED 		0b010 			/* Accepted */
#define SD_SPI_DATA_RESPONSE_TOKEN_REJECTED_CRC		0b101 			/* Rejected due to CRC error */
#define SD_SPI_DATA_RESPONSE_TOKEN_REJECTED_WRITE	0b110 			/* Rejected due to Write error */

#define SD_SPI_DATA_SINGLE_BLOCK_RW_START_BLOCK		0b11111110		/* Indicates start of data transmission */
#define SD_SPI_DATA_MULTI_BLOCK_RW_START_BLOCK		0b11111100		/* Indicates start of multi block RW */
#define SD_SPI_DATA_MULTI_BLOCK_RW_STOP_BLOCK		0b11111101		/* Indicates the stop of multi block RW */

/*********************************
 * Datatypes
 ********************************/

typedef enum {
	SD_SPI_OK = 0,
	SD_SPI_ERROR_SENT_WHILE_READING,
	SD_SPI_ERROR_SENT_WHILE_BUSY,
	SD_SPI_ERROR_CARD_LOCKED,
	SD_SPI_ERROR_ILLEGAL_OPCODE,
	SD_SPI_ERROR_CRC_FAILED,
	SD_SPI_ERROR_ILLEGAL_OPERAND,
	SD_SPI_ERROR_OUT_OF_SEQUENCE_DURING_ERASE
} sd_spi_resp_t;

typedef enum {
	/* 00 */ 		SD_SPI_GO_IDLE_STATE = 0,
	/* 01 */ 		SD_SPI_SEND_OP_COND,
	/* 02-04*/ 		SD_SPI_CMD2, SD_SPI_CMD3, SD_SPI_CMD4, /* Non-SPI */
	/* 05 */ 		SD_SPI_CMD5,
	/* 06 */ 		SD_SPI_SWITCH_FUNC,
	/* 07 */ 		SD_SPI_CMD7, /* Non-SPI */
	/* 08 */ 		SD_SPI_SEND_IF_COND,
	/* 09 */ 		SD_SPI_SEND_CSD,
	/* 10 */ 		SD_SPI_SEND_CID,
	/* 11 */ 		SD_SPI_CMD11, /* Non-SPI */
	/* 12 */ 		SD_SPI_STOP_TRANSMISSION,
	/* 13 */ 		SD_SPI_SEND_STATUS,
	/* 14 */ 		SD_SPI_CMD14, /* Reserved */
	/* 15 */ 		SD_SPI_CMD15, /* Non-SPI */
	/* 16 */ 		SD_SPI_SET_BLOCKLEN,
	/* 17 */ 		SD_SPI_READ_SINGLE_BLOCK,
	/* 18  */ 		SD_SPI_READ_MULTIPLE_BLOCK,
	/* 19 */ 		SD_SPI_CMD19, /* Reserved */
	/* 20 */ 		SD_SPI_CMD20, /* Non-SPI */
	/* 21 - 23 */ 	SD_SPI_CMD21, SD_SPI_CMD22, SD_SPI_CMD23, /* Reserved */
	/* 24 */ 		SD_SPI_WRITE_BLOCK,
	/* 25 */ 		SD_SPI_WRITE_MULTIPLE_BLOCK,
	/* 26 */ 		SD_SPI_CMD26, /* Non-SPI */
	/* 27 */ 		SD_SPI_PROGRAM_CSD,
	/* 28 */ 		SD_SPI_SET_WRITE_PROT,
	/* 29 */ 		SD_SPI_CLR_WRITE_PROT,
	/* 30 */ 		SD_SPI_SEND_WRITE_PROT,
	/* 31 */ 		SD_SPI_CMD31, /* Reserved */
	/* 32 */ 		SD_SPI_ERASE_WR_BLK_START_ADDR,
	/* 33 */ 		SD_SPI_ERASE_WR_BLK_END_ADDR,
	/* 34 - 37*/ 	SD_SPI_CMD34, SD_SPI_CMD35, SD_SPI_CMD36, SD_SPI_CMD37, /* Reserved */
	/* 38 */ 		SD_SPI_ERASE,
	/* 39 - 40 */ 	SD_SPI_CMD39, SD_SPI_CMD40, /* Non-SPI */
	/* 41 */ 		SD_SPI_CMD41, /* Reserved */
	/* 42 */ 		SD_SPI_LOCK_UNLOCK,
	/* 43 - 49 */ 	SD_SPI_CMD43, SD_SPI_CMD44, SD_SPI_CMD45, SD_SPI_CMD46, SD_SPI_CMD47, SD_SPI_CMD48, SD_SPI_CMD49, /* Reserved */
	/* 50 - 51 */ 	SD_SPI_CMD50, SD_SPI_CMD51, /* Reserved */
	/* 52-54 */ 	SD_SPI_CMD52, SD_SPI_CMD53, SD_SPI_CMD54, /* Reserved for IO Mode */
	/* 55 */ 		SD_SPI_APP_CMD,
	/* 56 */ 		SD_SPI_GEN_CMD,
	/* 57 */ 		SD_SPI_CMD57, /* Reserved */
	/* 58 */ 		SD_SPI_READ_OCR,
	/* 59 */ 		SD_SPI_CRC_ON_OFF,
	/* 60-63 */ 	SD_SPI_CMD60, SD_SPI_CMD61, SD_SPI_CMD62, SD_SPI_CMD63 /* Reserved for manufacuturer */
} sd_spi_cmd_index_t;

typedef enum {
	/* 6 */ 		SD_SPI_ACMD6 = 6, /* Non-SPI */
	/* 13 */ 		SD_SPI_ACMD_SD_STATUS = 13,
	/* 17 */ 		SD_SPI_ACMD17 = 17, /* Reserved */
	/* 18 */ 		SD_SPI_ACMD18, /* Reserved for security */ 
	/* 19 - 21*/ 	SD_SPI_ACMD19, SD_SPI_ACMD20, SD_SPI_ACMD21, /* Reserved */
	/* 22 */ 		SD_SPI_ACMD_SEND_NUM_WR_BLOCKS,
	/* 23 */ 		SD_SPI_ACMD_SET_WR_BLK_ERASE_COUNT,
	/* 24 */ 		SD_SPI_ACMD24, /* Reserved */
	/* 25-26,38 */ 	SD_SPI_ACMD25, SD_SPI_ACMD26, SD_SPI_ACMD38 = 38, /* Reserved for SD Security applications */
	/* 39 - 40 */ 	SD_SPI_ACMD39, SD_SPI_ACMD40, /* Reserved */
	/* 41 */ 		SD_SPI_ACMD_SD_SEND_OP_COND,
	/* 42 */ 		SD_SPI_ACMD_SET_CLR_CARD_DETECT,
	/* 43 - 49 */ 	SD_SPI_ACMD43, SD_SPI_ACMD44, SD_SPI_ACMD45, SD_SPI_ACMD46, SD_SPI_ACMD47, SD_SPI_ACMD48, SD_SPI_ACMD49, /* Reserved for security */
	/* 51 */ 		SD_SPI_ACMD_SEND_SCR = 51
} sd_spi_acmd_index_t;

typedef struct __attribute__ (( packed )) {
	unsigned start_bit 			: 1;
	unsigned transmission_bit 	: 1;
	unsigned command_index 		: 6;
	uint32_t argument;
	unsigned crc7 				: 7;
	unsigned end_bit 			: 1;
} sd_spi_command_t;

typedef struct __attribute__ (( packed )) {
	unsigned always_zero 		: 1; /* Always zero, useless bit */
	unsigned parameter_error 	: 1;
	unsigned address_error 		: 1;
	unsigned erase_sequence_error : 1;
	unsigned com_crc_error 		: 1;
	unsigned illegal_command 	: 1;
	unsigned erase_reset 		: 1;
	unsigned in_idle_state 		: 1;
} sd_spi_response_r1_t;

typedef struct __attribute__ (( packed )) {
	unsigned always_zero 		: 1; /* Always zero, useless bit */
	unsigned parameter_error 	: 1;
	unsigned address_error 		: 1;
	unsigned erase_sequence_error : 1;
	unsigned com_crc_error 		: 1;
	unsigned illegal_command 	: 1;
	unsigned erase_reset 		: 1;
	unsigned in_idle_state 		: 1;
	/* ======================== */
	unsigned out_of_range__csd_overwrite : 1;
	unsigned erase_param 		: 1;
	unsigned wp_violation 		: 1;
	unsigned card_ecc_failed 	: 1;
	unsigned cc_error 			: 1;
	unsigned error 				: 1;
	unsigned wp_erase_skip__ll_cmd_failed : 1;
	unsigned card_is_locked 	: 1;
} sd_spi_response_r2_t;

typedef struct __attribute__ (( packed )) {
	sd_spi_response_r1_t r1;
	uint32_t ocr;
} sd_spi_response_r3_t;

typedef struct __attribute__ (( packed )) {
	sd_spi_response_r1_t r1;
	unsigned command_version 	: 4;
	unsigned reserved_bits 		: 16;
	unsigned voltage_accepted 	: 4;
	unsigned echo 				: 8;
} sd_spi_response_r7_t;

typedef struct __attribute__ (( packed )) {
	uint8_t reserved 			: 3;
	unsigned always_zero 		: 1;
	unsigned status 			: 3;
	unsigned always_one 		: 1;
} sd_spi_data_response_token_t;

typedef struct __attribute__ (( packed )) {
	unsigned always_zero 		: 4;
	unsigned out_of_range 		: 1;
	unsigned card_ecc_failed 	: 1;
	unsigned cc_error 			: 1;
	unsigned error 				: 1;
} sd_spi_data_error_token_t;

#define SD_SPI_COMMAND_DEFAULT { \
	.start_bit = 0, \
	.transmission_bit = 1, \
	.end_bit = 1 \
} 

/*********************************
 * Register datatypes
 ********************************/

typedef struct __attribute__ (( packed )) {
	unsigned csd_version_10 : 1;
	unsigned csd_version_20 : 1;
	/* ======================== */
	unsigned reserved0 			: 6;
	/* ======================== */
	unsigned taac 				: 8;
	unsigned nasc 				: 8;
	unsigned tran_speed 		: 8;
	unsigned ccc 				: 12;
	unsigned read_bl_len 		: 4;
	unsigned read_bl_partial 	: 1;
	unsigned write_blk_misalign : 1;
	unsigned read_blk_misalign 	: 1;
	unsigned dsr_imp	 		: 1;
	/* ======================== */
	unsigned reserved1 			: 2;
	/* ======================== */
	unsigned c_size 			: 12;
	unsigned vdd_r_curr_min 	: 3;
	unsigned vdd_r_curr_max 	: 3;
	unsigned vdd_w_curr_min 	: 3;
	unsigned vdd_w_curr_max 	: 3;
	unsigned c_size_mult 		: 3;
	unsigned erase_blk_en 		: 1;
	unsigned sector_size 		: 7;
	unsigned wp_grp_size 		: 7;
	unsigned wp_grp_enable 		: 1;
	/* ======================== */
	unsigned reserved2 			: 2;
	/* ======================== */
	unsigned r2w_factor 		: 3;
	unsigned write_bl_len 		: 4;
	unsigned write_bl_partial 	: 1;
	/* ======================== */
	unsigned reserved3 			: 5;
	/* ======================== */
	unsigned file_format_grp	: 1;
	unsigned copy				: 1;
	unsigned perm_write_protect : 1;
	unsigned tmp_write_protect	: 1;
	unsigned file_format 		: 2;
	/* ======================== */
	unsigned reserved4			: 2;
	/* ======================== */
	unsigned crc 				: 7;
	unsigned always_one			: 1;
} sd_csd_register_t;

typedef struct __attribute__ (( packed )) {
	unsigned manufacuturer_id	: 8;
	char oem					 [2];
	char product_name			 [5];
	unsigned revision			: 8;
	uint32_t serial_number;
	unsigned reserved 			: 4;
	unsigned manufacturing_date : 12;
	unsigned crc7_checksum		: 7;
	unsigned always_one 		: 1;
} sd_cid_register_t; 

/*********************************
 * Prototpes
 ********************************/

/**
 * Calculates the CRC7 check sum for the specified data
 */
uint8_t sd_calc_crc7(uint8_t *data, uint8_t n);

/**
 * Gets the CID register stucture from the SD card
 */
sd_cid_register_t sd_get_cid_register(void);

/**
 * Gets the CSD register structure from the SD card
 */
sd_csd_register_t sd_get_csd_register(void);

#endif

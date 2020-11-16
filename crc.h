#ifndef _CRC_H
#define _CRC_H

#include "default.h"

/**
 * Generates the CRC7 lookup table
 */
void crc7_generate_table(uint8_t *target, uint8_t polynomial);

/**
 * Calculates the CRC7 of an specified array
 */
uint8_t crc7(uint8_t *table, uint8_t *p, uint8_t n);

#endif

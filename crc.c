#include "crc.h"

/**
 * Generates the CRC7 lookup table
 */
void crc7_generate_table(uint8_t *target, uint8_t polynomial)
{
	for (uint16_t i = 0; i < 256; ++i) {
		target[i] = (i & 0x80) ? i ^ polynomial : i;
		for (uint8_t j = 0; j < 8; ++j) {
			target[i] <<= 1;
			if (target[i] & 0x80)
				target[i] ^= polynomial;
		}
	}
}

/**
 * Calculates the CRC7 of an specified array
 */
uint8_t crc7(uint8_t *table, uint8_t *p, uint8_t n)
{
	uint8_t res = 0x0;
	for (uint8_t i = 0; i < n; ++i)
		res = table[(res << 1) ^ p[i]];

	return res;
}

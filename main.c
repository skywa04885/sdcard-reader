#include "main.h"

void setup(void)
{
	i2c_init();
	ssd1306_init();

	ssd1306_set_column_address_param_t param;
	param.start_addr = 0;
	param.end_addr = 127;

	ssd1306_set_column_address(param);
	ssd1306_set_page(0);

	uint8_t smiley[] = {
		0b01111110,
		0b10000001,
		0b10101001,
		0b10000101,
		0b10101001,
		0b10000001,
		0b01111110
	};

	for (uint8_t i = 0; i < sizeof (smiley); ++i) {
		ssd1306_write(SSD1306_CTRL_GDRAM, smiley[i]);
	}

	for (uint8_t i = 2; i < 8; ++i) {
		ssd1306_set_page(i);
		ssd1306_write_string("GO TO MY ONLYFANS");		
	}
}

void loop(void)
{
}

void __attribute__ (( noreturn )) main(void)
{
	setup();
	for (;;) loop();
}
#include "main.h"

void setup(void)
{
	i2c_init();
	spi_init();
	usart_init();
	sd_init();
	printf("Initialized\r\n");

	sd_spi_response_r1_t r = sd_go_idle();
	sd_spi_log_r1(r);

	sd_spi_response_r7_t resp = sd_get_ocr();
	sd_spi_log_r7(resp);
}

void loop(void)
{
}

void __attribute__ (( noreturn )) main(void)
{
	setup();
	for (;;) loop();
}
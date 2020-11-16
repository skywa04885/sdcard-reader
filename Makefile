# Other stuff
DEVICE_PATH := /dev/ttyACM0
MCU := atmega328p
PROGRAMMER := usbasp

# Files
IHEX_OUT := ./build/main.hex
GCC_OUT := build/main.o

# Programs
AVRDUDE := /bin/avrdude
AVR_GCC := /bin/avr-gcc
AVR_SIZE := /bin/avr-size
AVR_OBJCOPY := /bin/avr-objcopy

# Input files
SOURCES := main.c i2c.c ssd1306.c font.c sd.c spi.c crc.c usart.c

# Arguments
AVRDUDE_ARGS := -P $(DEVICE_PATH) -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(IHEX_OUT)
AVR_OBJCOPY_ARGS := -O ihex $(GCC_OUT) $(IHEX_OUT)
AVR_SIZE_ARGS := --format=avr --mcu=$(MCU) $(GCC_OUT)
AVR_GCC_ARGS := -mmcu=$(MCU) -Os -fdata-sections -ffunction-sections -o $(GCC_OUT) $(SOURCES) -Wl,--gc-sections

# Rules
prepare:
	mkdir -p build
all: prepare
	$(AVR_GCC) $(AVR_GCC_ARGS)
	$(AVR_SIZE) $(AVR_SIZE_ARGS)
flash: all
	$(AVR_OBJCOPY) $(AVR_OBJCOPY_ARGS)
	$(AVRDUDE) $(AVRDUDE_ARGS)
clean:
	rm -R build
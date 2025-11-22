##################################################################################
#  VARIABLES
##################################################################################

# Configuración del microcontrolador
MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
BAUD = 57600

# Herramientas
CC = avr-gcc

# Flags
CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
LDFLAGS = -mmcu=$(MCU)
FIRMWARE = imagen.hex

# Objetos
DRIVERS = $(BUILD_DIR)/gpio.o  $(BUILD_DIR)/twi-slave.o $(BUILD_DIR)/matrix-keyboard.o
UTILS = $(BUILD_DIR)/queue.o

# Misc
INCLUDE_DIR := include
BUILD_DIR := build
VPATH := src \
VPATH := src/drivers \
		 src/utils

APP = program
COMPILE = $(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
LINK = $(CC) $(LDFLAGS) -o $(BUILD_DIR)/$(APP) $^

##################################################################################
#  REGLAS
##################################################################################

all: $(BUILD_DIR)/my_queue.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/twi-slave.o $(BUILD_DIR)/matrix-keyboard.o  $(BUILD_DIR)/main.o $(BUILD_DIR)/serial.o
	$(LINK)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Objetos:
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(COMPILE)

# Misc:
flash:
	avr-objcopy -O ihex -R .eeprom $(BUILD_DIR)/$(APP) $(BUILD_DIR)/$(FIRMWARE)
	avrdude -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -D -U flash:w:$(BUILD_DIR)/$(FIRMWARE):i

clean:
	rm -rf $(BUILD_DIR)
	rm -rf cmake-build-debug
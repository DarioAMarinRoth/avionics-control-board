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

# Misc
INCLUDE_DIR = ./include
BUILD_DIR = build
APP = program
COMPILE = $(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
LINK = $(CC) $(LDFLAGS) -o $(BUILD_DIR)/$(APP) $^

##################################################################################
#  REGLAS
##################################################################################

# Apps:
all:
	@echo "Ejecute el comando 'make <app>' donde <app> es una de los siguientes opciones:"
	@echo "  - twi-master-test"
	@echo "  - twi-slave-test"
	@echo "  - matrix-keyboard-1"
	@echo "  - matrix-keyboard-2"
	@echo "  - py-serial-test"
	@echo ""
	@echo "Recordar hacer make clean antes de compilar otra app."
	@echo "Para mas información sobre cada aplicación ejecute el comando 'make help'."

help:
	@echo ""
	@printf "\033[1;36m- matrix-keyboard-1: \033[0m"
	@printf "El programa leerá el estado de una matriz de pulsadores de 2x2 y enviará el estado de cada pulsador a través de la comunicación serial. Si se presiona un pulsador, se enviará un '1', de lo contrario, se enviará un '0'. Los resultados se imprimirán en la consola en un formato de vector."
	@echo ""
	@echo ""
	@printf "\033[1;36m- matrix-keyboard-2: \033[0m"
	@printf "El programa leerá el estado de una matriz de pulsadores de 2x2 y enviará via serial el identificador de un pulsador en el momento que ocurra tanto una pulsación como una liberación sobre el mismo"
	@echo ""
	@echo ""
	@printf "\033[1;36m- twi-master-test:\033[0m"
	@printf " verifica el correcto funcionamiento de la comunicación I²C entre dispositivos. El programa espera recibir bytes de un dispositivo esclavo. Encenderá el LED de la placa si se recibe un 1 y lo apagará si recibe un 0."
	@echo ""
	@echo ""
	@printf "\033[1;36m- twi-slave-test:\033[0m"
	@printf " verifica el correcto funcionamiento de la comunicación I²C entre dispositivos. El programa envía constantemente bytes a un dispositivo maestro dependiendo del estado de un pulsador. Si el pulsador está presionado enviará un 1 y enviará un 0 si está liberado."
	@echo ""
	@echo ""
	@printf "\033[1;36m- py-serial-test: \033[0m"
	@echo "- Verifica el correcto funcionamiento de la comunicación serial entre el arduino y los scripts que corren en la PC. El programa permite imprimir un mensaje en la terminal utilizando python al accionar un pulsador conectado al arduino."

twi-master-test: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/twi-master.o $(BUILD_DIR)/twi_master_test.o
	$(LINK)

twi-slave-test: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/twi-slave.o $(BUILD_DIR)/twi_slave_test.o
	$(LINK)

matrix-keyboard-1: $(BUILD_DIR)/queue.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/matrix-keyboard.o $(BUILD_DIR)/matrix_test_1.o
	$(LINK)

matrix-keyboard-2: $(BUILD_DIR)/queue.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/matrix-keyboard.o $(BUILD_DIR)/matrix_test_2.o
	$(LINK)

py-serial-test: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/py_serial_test.o
	$(LINK)

# Objetos:
$(BUILD_DIR)/%.o: ./src/drivers/%.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

$(BUILD_DIR)/%.o: ./src/utils/%.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

$(BUILD_DIR)/twi_master_test.o: src/tests/unit/twi/twi_master_test.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

$(BUILD_DIR)/twi_slave_test.o: src/tests/unit/twi/twi_slave_test.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

$(BUILD_DIR)/%.o: src/tests/unit/%.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

$(BUILD_DIR)/py_serial_test.o: src/tests/integration/serial/py_serial_test.c
	mkdir -p $(BUILD_DIR)
	$(COMPILE)

# Misc:
flash:
	avr-objcopy -O ihex -R .eeprom $(BUILD_DIR)/$(APP) $(BUILD_DIR)/$(FIRMWARE)
	avrdude -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -D -U flash:w:$(BUILD_DIR)/$(FIRMWARE):i

clean:
	rm -rf $(BUILD_DIR)
	rm -rf cmake-build-debug
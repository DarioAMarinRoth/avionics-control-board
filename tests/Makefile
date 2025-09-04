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
DRIVERS = $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/twi-master.o $(BUILD_DIR)/twi-slave.o $(BUILD_DIR)/matrix-keyboard.o
UTILS = $(BUILD_DIR)/queue.o

# Misc
INCLUDE_DIR := include
BUILD_DIR := build
VPATH := src/drivers \
		 src/utils \
		 src/tests/unit \
		 src/tests/unit/twi \
		 src/tests/integration/serial \
		 src/tests/integration/communication

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
	@echo "  - set-py-state"
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

all:

twi-master-test: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/twi-master.o $(BUILD_DIR)/twi_master_test.o
	$(LINK)

twi-slave-test: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/twi-slave.o $(BUILD_DIR)/twi_slave_test.o
	$(LINK)

matrix-keyboard-1: $(BUILD_DIR)/my_queue.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/matrix-keyboard.o $(BUILD_DIR)/matrix_test_1.o
	$(LINK)

matrix-keyboard-2: $(BUILD_DIR)/my_queue.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/matrix-keyboard.o $(BUILD_DIR)/matrix_test_2.o
	$(LINK)

encoder-test: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/encoder_test.o
	$(LINK)

set-py-state: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/set_sim_state.o
	$(LINK)

get-py-state: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/get_sim_state.o
	$(LINK)

communication-slave: $(BUILD_DIR)/gpio.o $(BUILD_DIR)/my_queue.o $(BUILD_DIR)/twi-slave.o $(BUILD_DIR)/matrix-keyboard.o $(BUILD_DIR)/communication-slave.o
	$(LINK)

communication-master: $(BUILD_DIR)/my_queue.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/twi-master.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/matrix-keyboard.o $(BUILD_DIR)/communication-master.o
	$(LINK)

receive-queue: $(BUILD_DIR)/my_queue.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/twi-master.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/receive-queue.o
	$(LINK)

send-queue: $(BUILD_DIR)/my_queue.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/twi-slave.o $(BUILD_DIR)/send-queue.o
	$(LINK)

sync-state-1: $(BUILD_DIR)/sync_state.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o
	$(LINK)

sync-state-2: $(BUILD_DIR)/sync_state_2.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/serial.o $(BUILD_DIR)/misc.o
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
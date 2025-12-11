import serial
from time import sleep

from core.event_bus import EventBus
from arduino.protocol import ArduinoProtocol
from core.events import EventType
from src.core.config import ConnectionConfig
from src.utils.logger import Logger

class ArduinoGateway:

    _RESET_PULSE_DURATION = 0.1
    _BOOTLOADER_WAIT_TIME = 2.0
    _TRIM_ID = 35
    _ID_MAX_VALUE = 235

    def __init__(self, config: ConnectionConfig, event_bus: EventBus):
        self.config = config
        self.event_bus = event_bus
        self.serial = serial.Serial(config.port, config.baudrate) # Comentar si se va a probar sin arduino
        self.logger = Logger("arduino")
        self.inputs_state: dict[int,int] = {}
        event_bus.subscribe(EventType.ARDUINO_COMMAND, self._send_message) # Comentar si se va a probar sin arduino

    def reset_board(self):
        self.serial.dtr = False
        sleep(self._RESET_PULSE_DURATION)
        self.serial.dtr = True
        sleep(self._BOOTLOADER_WAIT_TIME)
        self.serial.reset_input_buffer()
        self.logger.info("Reset realizado")

    def reading_loop(self):
        while True:
            raw_data = self._get_byte()
            self.logger.info("Nuevo mensaje recibido")
            input_id = ArduinoProtocol.decode_message(raw_data)

            if input_id is None:
                continue

            if input_id < 0 or input_id > self._ID_MAX_VALUE:
                self.logger.error(f"El ID recibido {input_id} está fuera del rango permitido (0-{self._ID_MAX_VALUE})")
                continue

            if  input_id < self._TRIM_ID:
                input_value = self._update_input_state(input_id)
            else:
                input_value = input_id - self._TRIM_ID
                input_id = self._TRIM_ID
                self.inputs_state[input_id] = input_value

            self.event_bus.publish(EventType.ARDUINO_INPUT, input_id, input_value)

    def _get_byte(self):
        return self.serial.readline()
        # return ArduinoProtocol.encode_message(int(input("Input simulada: "))) # Descomentar para probar sin Arduino (comentar la líena de arriba en ese caso)

    def _send_byte(self, byte_data):
        self.logger.info("Enviando mensaje al Arduino")
        self.serial.write(byte_data)

    def _send_message(self, pin_id, value):
        byte_id = ArduinoProtocol.encode_message(pin_id)
        byte_value = ArduinoProtocol.encode_message(value)
        self._send_byte(byte_id)
        self._send_byte(byte_value)

    def _update_input_state(self, input_id):
        on = 1
        if input_id in self.inputs_state:
            self.inputs_state[input_id] ^= on
        else:
            self.inputs_state[input_id] = on
        current_value = self.inputs_state[input_id]
        states = ["OFF", "ON"]
        self.logger.info(f"Input {input_id} actualizada a {states[current_value]}")
        return current_value


    # TODO: Función para conectar al Arduino (con reintentos)
    # TODO: Función para reconectar al Arduino (cerrar y abrir el puerto)
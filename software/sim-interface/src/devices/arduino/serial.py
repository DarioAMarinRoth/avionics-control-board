import time
import serial
from time import sleep

from src.devices.arduino.config import ArduinoConfig
from src.utils.logger import Logger


class ArduinoSerial:

    def __init__(self):
        self.nano = serial.Serial(ArduinoConfig.port, ArduinoConfig.baudrate)
        self.logger = Logger("arduino")

    # TODO: Función para conectar al Arduino (con reintentos)
    # TODO: Función para reconectar al Arduino (cerrar y abrir el puerto)

    def reset_board(self):
        self.nano.dtr = False
        sleep(ArduinoConfig.reset_delay)
        self.nano.dtr = True
        sleep(2)
        self.nano.reset_input_buffer()
        self.logger.info("Reset done")

    def flush_serial(self):
        temp_timeout = 0.1
        self.nano.timeout = temp_timeout
        ts = 0
        tl = time.time() + ArduinoConfig.startup_flush_timeout
        while ts < tl:
            ts = time.time()
            self.nano.readline()
        self.nano.timeout = None
        self.logger.info("Serial ready")

    def get_byte(self):
        return self.nano.readline()

    def send_byte(self, byte_data):
        self.nano.write(byte_data)
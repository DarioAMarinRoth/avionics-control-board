from src.devices.arduino.serial import ArduinoSerial
from src.devices.arduino.output_controller import ArduinoOutputController
from src.devices.arduino.state_manager import ArduinoStateManager


class ArduinoManager:

    def __init__(self):
        self.serial = ArduinoSerial()
        self.state_manager = ArduinoStateManager()
        self.output_controller = ArduinoOutputController(self.serial)
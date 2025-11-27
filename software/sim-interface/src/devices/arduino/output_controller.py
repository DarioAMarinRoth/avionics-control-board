from src.devices.arduino.protocol import ArduinoProtocol


class ArduinoOutputController:
    __ON = 1
    __OFF = 0

    def __init__(self, serial):
        self.serial = serial
        self.encoder = ArduinoProtocol()

    def turn_on(self, pin_id):
        byte_id = self.encoder.encode_message(pin_id)
        byte_value = self.encoder.encode_message(self.__ON)
        self.serial.send_byte(byte_id)
        self.serial.send_byte(byte_value)

    def turn_off(self, pin_id):
        byte_id = self.encoder.encode_message(pin_id)
        byte_value = self.encoder.encode_message(self.__OFF)
        self.serial.send_byte(byte_id)
        self.serial.send_byte(byte_value)
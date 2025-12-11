from utils.logger import Logger


class ArduinoProtocol:

    EOL = '\n'
    logger = Logger("decoder")
    @staticmethod
    def decode_message(raw_data):
        data_str = raw_data.decode().strip()
        try:
            input_id = int(data_str)
            return input_id
        except ValueError:
            ArduinoProtocol.logger.error(f"El mensaje recibido \"{data_str}\" no se corresponde con un entero")
            return None




    @staticmethod
    def encode_message(command_id: int):
        return f"{command_id:02d}{ArduinoProtocol.EOL}".encode()
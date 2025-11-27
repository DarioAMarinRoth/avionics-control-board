# Define el formato de mensajes
# Codifica comandos a formato que entiende el Arduino ("05\n")
# Decodifica IDs recibidos (bytes → entero)
# NO decide qué hacer con los datos

class ArduinoProtocol:

    def __init__(self, eol='\n'):
        self.eol = eol

    @staticmethod
    def decode_message(raw_data):
        data_str = raw_data.decode().strip()
        return int(data_str) # TODO: manejo de errores

    def encode_message(self, command_id):
        return f"{command_id:02d}{self.eol}".encode()
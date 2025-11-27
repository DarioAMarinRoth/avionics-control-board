from dataclasses import dataclass

@dataclass
class ArduinoConfig:
    port: str = '/dev/ttyUSB0'
    baudrate: int = 9600
    timeout: float = 2.0
    reset_delay: float = 0.1
    startup_flush_timeout: float = 5.0
from enum import Enum, auto

class EventType(Enum):
    # Arduino
    ARDUINO_INPUT = auto()
    TRIM_ADJUST = auto()
    ARDUINO_COMMAND = auto()

    # Mapper
    BUTTON_EVENT = auto()
    AXIS_EVENT = auto()

    # Sim
    SIMVAR_UPDATE = auto()


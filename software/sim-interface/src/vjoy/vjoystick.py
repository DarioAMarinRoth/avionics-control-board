from pyvjoystick import vjoy

from core.event_bus import EventBus
from core.logic import LogicController
from core.events import EventType
from utils.logger import Logger


class VJoystick:

    _MAX_TRIM_VALUE = 200
    _MAX_AXIS_VALUE = 32768

    def __init__(self, event_bus: EventBus, device_id=1):
        self._event_bus = event_bus
        self.joystick = vjoy.VJoyDevice(device_id)
        self._event_bus.subscribe(EventType.BUTTON_EVENT, self._set_button)
        self._event_bus.subscribe(EventType.AXIS_EVENT, self._set_axis)
        self.logger = Logger("vJoy")

    def _set_button(self, button_id: int, value: int):
        states = ["OFF", "ON"]
        if button_id is None:
            self.logger.warning("El ID recibido no se corresponde a ningún botón vJoy")
            return
        self.joystick.set_button(button_id, value)
        self.logger.info(f"Botón {button_id} ajustado a {states[value]}")

    def _set_axis(self, axis_id: int, value: int):
        self.joystick.set_axis(axis_id, value)
        self.logger.info(f"{LogicController.get_input_label(axis_id)} ajustado a {LogicController.get_trim_percentage(value)}%")

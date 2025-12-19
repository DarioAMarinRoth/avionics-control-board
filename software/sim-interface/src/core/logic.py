from typing import Dict

from core.config import  InputConfig, OutputConfig
from core.event_bus import EventBus
from core.events import EventType
from utils.logger import Logger


class LogicController:

    _MAX_TRIM_VALUE = 200
    _MAX_AXIS_VALUE = 32768
    _logger = Logger("Mapper")
    _inputs: dict[int, InputConfig] = {}
    _outputs: dict[str, OutputConfig] = {}

    def __init__(self, inputs: Dict[int, InputConfig], outputs: Dict[str, OutputConfig], event_bus: EventBus):
        self._event_bus = event_bus
        self._event_bus.subscribe(EventType.ARDUINO_INPUT, self._handle_input_event)
        self._event_bus.subscribe(EventType.SIMVAR_UPDATE, self._handle_sim_event)
        LogicController._inputs = inputs
        LogicController._outputs = outputs

    def _handle_input_event(self, input_id: int, value: int):
        if input_id not in self._inputs:
            return

        input_config = self._inputs[input_id]
        if input_config.button_id is not None:
            self._event_bus.publish(EventType.BUTTON_EVENT, input_config.button_id, value)
        elif input_config.axis_id is not None:
            axis_value = self._calculate_trim_position(value)
            self._event_bus.publish(EventType.AXIS_EVENT, input_config.axis_id, axis_value)

    def _handle_sim_event(self, simvar_name: str, value):
        for output_id in LogicController._outputs[simvar_name].arduino_ids:
            self._logger.info(f"Publicando evento de salida {simvar_name} id:{output_id} con valor {value}")
            self._event_bus.publish(EventType.ARDUINO_COMMAND,output_id, value)

    def _calculate_trim_position(self, trim_value: int) -> int:
        axis_value = round((trim_value / self._MAX_TRIM_VALUE) * self._MAX_AXIS_VALUE)
        return max(0, min(self._MAX_AXIS_VALUE, axis_value))

    @staticmethod
    def get_input_label( joystick_id: int) -> str:
        if LogicController._inputs is None:
            LogicController._logger.warning("No se ha cargado ninguna configuración de mapeo.")
            return ""
        for entry in LogicController._inputs.values():
            if entry.button_id == joystick_id or entry.axis_id == joystick_id:
                return entry.label
        LogicController._logger.warning("No se encontró el id solicitado")
        return ""

    @staticmethod
    def get_trim_percentage(axis_value: int) -> int:
        percentage = round((axis_value / LogicController._MAX_AXIS_VALUE) * 100)
        return max(0, min(100, percentage))

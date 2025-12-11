from core.event_bus import EventBus
from core.events import EventType
from core.logic import LogicController

from vjoy.vjoystick import VJoystick

bus = EventBus()
mapper = LogicController(bus, "../config/config.yaml")
vjoy = VJoystick(bus)

while True:
    var_id = int(input("Input ID:"))
    value = int(input("value:"))
    bus.publish(EventType.ARDUINO_INPUT, var_id, value)
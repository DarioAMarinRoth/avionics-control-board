import logging
import threading

from arduino.gateway import ArduinoGateway
from core.config import ConfigLoader, CONFIG_FILE
from core.event_bus import EventBus
from simulator.connector import SimConnector
from core.logic import LogicController
from vjoy.vjoystick import VJoystick

logging.getLogger().setLevel(logging.CRITICAL)

config = ConfigLoader.load(CONFIG_FILE)

event_bus = EventBus()
arduino_connection = ArduinoGateway(config.connection, event_bus)
logic = LogicController(config.inputs, config.outputs, event_bus)
sim_connection = SimConnector(config.simvars, event_bus)
virtual_joystick = VJoystick(event_bus)

arduino_thread = threading.Thread(target=arduino_connection.reading_loop)
sim_thread = threading.Thread(target=sim_connection.loop)

sim_thread.start()

while not sim_connection.running:
    pass

arduino_thread.start()

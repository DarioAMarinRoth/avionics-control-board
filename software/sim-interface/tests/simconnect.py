import threading


from core.event_bus import EventBus
from simulator.connector import SimConnector

sc = SimConnector(EventBus())
sim_loop = threading.Thread(target=sc.loop)
sim_loop.daemon = True
while True:
    pass
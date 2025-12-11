import threading
import time
from typing import List

from SimConnect import SimConnect, PERIOD_SIM_FRAME
from core.event_bus import EventBus
from core.events import EventType
from src.utils.logger import Logger


class SimConnector:

    _CONNECTION_COLDOWN = 10

    def __init__(self, simvars: List[str], bus: EventBus):
        self._bus = bus
        self._logger = Logger("simconnect")
        self._sc = None
        self.running = False
        self._dataset = None
        self._latest_pointer = 0
        self._gear_transit = False
        self._simvars = simvars

    def loop(self):
        self._logger.info("Iniciando SimConnector loop")

        while True:

            while self._sc is None:  # Conexión/Reconexión
                self._connect()
            self._subscribe()

            while True:
                try:
                    self._get_frame()
                except Exception as e:
                    self._logger.warning(f"Desconexión con el simulador: {e}")
                    self._sc = None
                    self._dataset = None
                    time.sleep(1)
                    break


    def _get_frame(self):
        while self._sc.receive(timeout_seconds=0.005):
            pass

        if self._dataset and self._dataset.simdata:
            changes = self._dataset.simdata.changedsince(self._latest_pointer)

            if changes:
                self._latest_pointer = self._dataset.simdata.latest()
                for name, value in changes.items():
                    self._handle_change(name, value)

        # time.sleep(0.002)

    def _connect(self):
        self._logger.info("Intentando conectar con el simulador")
        try:
            self._sc = SimConnect()
            self._logger.success("Conexión exitosa\n")
            self.running = True
        except Exception:
            self._logger.warning("No se pudo establecer la conexión.")
            time.sleep(self._CONNECTION_COLDOWN)

    def _subscribe(self):
        self._dataset = self._sc.subscribe_simdata(
            self._simvars,
            period=PERIOD_SIM_FRAME,
            interval=1
        )
        self._latest_pointer = 0

    def _handle_change(self, name, value):
        if 'GEAR' not in name:
            self._bus.publish(EventType.SIMVAR_UPDATE, name, value)
            self._logger.debug(f"PANEL LIGHTS {value}")
            return

        if value == 1:
            self._gear_transit = False
            self._logger.debug(f"Tren abajo")
            self._bus.publish(EventType.SIMVAR_UPDATE, name, value)
            self._bus.publish(EventType.SIMVAR_UPDATE,'GEAR IN TRANSIT', 0)
            return
        elif value == 0:
            self._logger.debug(f"Tren Arriba")
            self._gear_transit = False
            self._bus.publish(EventType.SIMVAR_UPDATE, name, value)
            self._bus.publish(EventType.SIMVAR_UPDATE, 'GEAR IN TRANSIT', 0)
            return
        else:
            if not self._gear_transit:
                self._logger.debug(f"Tren en tránsito")
                self._gear_transit = True
                self._bus.publish(EventType.SIMVAR_UPDATE, 'GEAR IN TRANSIT', 1)
                return
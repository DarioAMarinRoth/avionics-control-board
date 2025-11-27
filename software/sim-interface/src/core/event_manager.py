from typing import Callable

from models.events import EventType


class EventManager:
    def __init__(self):
        self._subscribers: dict[EventType, list[Callable]] = {}

    def subscribe(self, event_type, callback):
        if event_type not in self._subscribers:
            self._subscribers[event_type] = []
        self._subscribers[event_type].append(callback)

    def publish(self, event_type):
        if event_type in self._subscribers:
            for callback in self._subscribers[event_type]:
                callback()
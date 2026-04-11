from typing import Callable

from core.events import EventType


class EventBus:
    def __init__(self):
        self._subscribers: dict[EventType, list[Callable]] = {}

    def subscribe(self, event_type: EventType, callback: Callable):
        if event_type not in self._subscribers:
            self._subscribers[event_type] = []
        self._subscribers[event_type].append(callback)

    def publish(self, event_type: EventType, var_id: int | str = None, value: int = None):
        if event_type in self._subscribers:
            for callback in self._subscribers[event_type]:
                callback(var_id, value)

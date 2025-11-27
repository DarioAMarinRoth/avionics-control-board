from core.event_manager import EventManager
from models.events import EventType



def function_1():
    print("Function 1 called")


def function_2():
    print("Function 2 called")

def function_3(manager: EventManager):
    print("Function 3 executed")
    manager.publish(EventType.TEST_EVENT)

def main():
    manager = EventManager()
    manager.subscribe(EventType.TEST_EVENT, function_1)
    manager.subscribe(EventType.TEST_EVENT, function_2)
    function_3(manager)

main()





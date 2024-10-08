import time
from SimConnect import *


aq = None

def connect_to_flight_sim():
    global aq
    connection = False
    while not connection:
        try:
            sm = SimConnect()
            aq = AircraftRequests(sm, _time=100)
            connection = True
            print("Conexión a Flight Simulator establecida.")
        except Exception as e:
            print(f"No se pudo establecer la conexión a Flight Simulator: {e}")
            time.sleep(30)

def get_gear_position(index):
    try:
        gear_position = aq.get(f"GEAR_POSITION:{index}")
        return gear_position
    except Exception as e:
        print(f"No se pudo obtener la posición del tren {index}: {e}")
        connect_to_flight_sim()
        return None

def main():
    connect_to_flight_sim()
    while True:
        gear_position = get_gear_position(0)
        if gear_position is not None:
            if gear_position == 0:
                print("Tren: arriba")
            elif gear_position == 1:
                print("Tren: abajo")
            else:
                print("Tren: en tránsito")
        time.sleep(0.2)

if __name__ == "__main__":
    main()
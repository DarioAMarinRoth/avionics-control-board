import time
from models.var import Var
from models.keyboard import get_key

import serial


def main():
    baudrate = 9600
    nano = serial.Serial('/dev/ttyUSB0', baudrate, timeout=1)
    state = {
        'a': Var(0, 0),
        's': Var(1, 0)
    }

    while True:
        key = get_key()
        if key == 'q':
            break
        else:
            try:                    # TODO: concatenar 0s para que el ID siempre tenga dos dígitos y el value siempre tenga 3.
                state[key].toggle()
                var_id = str(state[key].id) + "/n"
                var_value = str(state[key].value) + "/n"
                nano.write(var_id.encode())
                # time.sleep(0.1) # No me acuerdo por qué puse este delay.
                nano.write(var_value.encode())
                print(var_id, var_value)
            except:
                pass

# def main():
#     baudrate = 9600
#     nano = serial.Serial('/dev/ttyUSB0', baudrate, timeout=None)
#
#     while True:
#         var_id = get_data(nano)
#         print("información recibida:", flush=True)
#         print("id:", var_id, flush=True)
#
# def get_data(device):
#     data = device.readline().decode().strip()
#     return data
import serial
from models.var import Var

def main():
    baudrate = 9600
    nano = serial.Serial('/dev/ttyUSB0', baudrate, timeout=None)
    state = {
        'a' : Var(0, 0),
        's' : Var(1, 0)
    }
    while True:
        var_id = int(get_data(nano))
        value = int(get_data(nano))
        print("información recibida:", flush=True)
        print("id:", var_id, flush=True)
        print("value:", value, flush=True)

def get_data(device):
        return device.readline().decode().strip()

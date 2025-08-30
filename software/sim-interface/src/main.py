import time
from models.var import Var
from models.keyboard import get_key

import serial


baudrate = 9600
nano = serial.Serial('/dev/ttyUSB0', baudrate, timeout=1)
state = {
    'a' : Var(0, 0),
    's' : Var(1, 0)
}

while True:
    key = get_key()
    if key == 'q':
        break
    else:
        try:
            state[key].toggle()
            var_id = str(state[key].id) + "/n"
            var_value = str(state[key].value) + "/n"
            nano.write(var_id.encode())
            time.sleep(0.1)
            nano.write(var_value.encode())
        except:
            pass

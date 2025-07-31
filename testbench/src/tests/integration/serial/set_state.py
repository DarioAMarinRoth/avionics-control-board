import time

import serial
baudrate = 9600
nano = serial.Serial('/dev/ttyUSB0', baudrate, timeout=1)

while True:
    nano.write(b'1')
    time.sleep(1)
    nano.write(b'0')
    time.sleep(1)
# TODO: ver la forma de enviar  un entero.
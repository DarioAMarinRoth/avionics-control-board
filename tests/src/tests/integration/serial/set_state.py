import time
import serial
baudrate = 9600
nano = serial.Serial('/dev/ttyUSB0', baudrate, timeout=1)

data = 12345
msg = str(data) + "\n"
msg = msg.encode();
print(msg)
pause = 3;
while True:
    nano.write(msg)
    time.sleep(pause)
    nano.write("00000\n".encode())
    time.sleep(pause)
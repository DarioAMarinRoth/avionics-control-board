import pyvjoy
import time


j = pyvjoy.VJoyDevice(1)
button = 1
HIGH = 1
LOW = 0

print("START")

for i in range(10):
    j.set_button(button,HIGH)
    time.sleep(2)
    j.set_button(button,LOW)
    time.sleep(2)
    print(i)

print("END")
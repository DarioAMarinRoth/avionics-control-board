import serial

baudrate = 9600
nano = serial.Serial('/dev/ttyUSB0', baudrate, timeout=1)

msg = 0;
print("Comenzando")
while msg != 'q':
    msg = nano.read(1).decode('latin-1').strip();
    if msg == '1':
        print("Botón 1 presionado")

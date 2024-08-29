22/08/2024 - Primer research

# Inyección de eventos en Windows mediante software

## vJoy

Existe un controlador llamado vJoy que permite crear joysticks virtuales de hasta 16 ejes y 32 botones.

### vJoy + python

Evidentemente hay una [librería en python](https://github.com/tidzo/pyvjoy) que permite pasarle eventos a vJoy.

Posts que abordan el tema:

- [How can I emulate a joystick using a python script?](https://stackoverflow.com/questions/43483121/simulate-xbox-controller-input-with-python)

### SDK de vJoy

Paralelamente a la solución con Python, hay un kit de desarrollo pero no está en la web oficial del controlador. Pensé que estaría incluido en la propia descarga del controlador pero, por mi parte, no lo encontré (tampoco rebusqué mucho).

Hay links al SDK subidos por terceros. Todavía no lo descargué. [Download](https://sourceforge.net/projects/vjoystick/files/Beta%202.x/SDK/)

Por lo que leí, el SDK está está en C/C++, y es posible configurar una _feeder aplication_ para vJoy utilizando comunicación serial.

Algunos posts que abordan el tema son:

- [vJoySerialFeeder](https://github.com/Cleric-K/vJoySerialFeeder)
- [Arduino vJoy Feeder](https://forum.arduino.cc/t/arduino-vjoy-feeder/494968) (El proyecto que tiene este usuario es muy parecido al mío)
- [vJoy emulation using Arduino serial statements (Arduino Gamepad)](https://forum.arduino.cc/t/vjoy-emulation-using-arduino-serial-statements-arduino-gamepad/356272)

## Emular HID (V-USB)

Rafa encontró una implementación basada software de un dispositivo USB para cualquier micro AVR. También probó uno de los ejemplos y compiló directamete sin problemas.

- Requiere un poco de electrónica adicional.
- Está bien documentado.
- Requeriría además encontrar algo en C para controlar el HID.

[Link a la web oficial](https://www.obdev.at/products/vusb/index.html)

## Otras soluciones

### ~~Librería vgamepad~~ (Descartado) - Solo emula joysticks bien conocidos de consolas.

Un usuario desarrollo una [librería](https://github.com/yannbouteiller/vgamepad) para emular un joyctick de XBox360 y DualShock4 (no se lo que es) en Python.

Si bien no se si sirve directamente, en el readme del repositorio se menciona para Windows, la librería usa un framework llamado [Virtual Gamepad Emulation](https://github.com/nefarius/ViGEmBus).

### UnoJoy/MegaJoy **(no me gusta)**

Un usuario armó un [proyecto](https://github.com/AlanChatham/UnoJoy/tree/master) para que se pueda utilizar un Arduino Uno/Mega/Leonardo como un joystick.

Quizás se pueden tomar ideas para hacer lo mismo en el nano.

**Leyendo el readme del repo me tira un poco para atrás esta opción.**

## Algunos links adicionales

- [Is there any way to emulate joystick signals programmaticaly?](https://www.codeproject.com/Questions/1113553/Is-there-a-way-to-emulate-joystick-signals-program) (no dice mucho pero hay una serie de pasos muy genéricos para abordar una solución).

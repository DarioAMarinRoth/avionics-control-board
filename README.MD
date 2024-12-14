# Panel de Instrumentos para simuladores de vuelo basado en microcontroladores ATMega328p

## Introducción

Este repositorio contiene el desarrollo del proyecto final de la materia optativa "Programación de sistemas embebidos". El mismo se trata de un panel de instrumentos personalizado para su uso en simuladores de vuelo.

> [!IMPORTANT]  
> El proyecto aún se encuentra en desarrollo y actualmente no es funcional.

## Características

- Posibilidad de conectar hasta más de 36 entradas.
- Control e interacción en tiempo real con Flight Simulator.
- Respuestas basándose en eventos que sucedan en el simulador.

## Requisitos

> [!WARNING]  
> Para compilar y flahsear el código en el microcontrolador, será necesario hacerlo en un sistema operativo Linux.

### Hardware

- Arduino Nano: x2
- Resistencias varias
- Interruptores varios
- Diodos
- Cables

### Software
- **GNU Make**: Herramienta de automatización de compilación.
- **avr-gcc**: Compilador para microcontroladores AVR.
- **avrdude**: Herramienta para programar microcontroladores AVR.
- **Bibliotecas de desarrollo AVR**: Necesarias para compilar el código para el microcontrolador.
- **Python 3**: Lenguaje de programación.

#### Instalación en Linux

Se pueden instalar las herramientas necesarias en una distribución basada en Debian/Ubuntu mediante:

```sh
sudo apt install make gcc-avr avr-libc avrdude
```

## Pruebas

El proyecto incluye un conjunto de pruebas básicas para validar las capas de hardware y comunicación. Los tests disponibles son:

1. **Prueba de la Matriz de Botones**  
   Verifica la funcionalidad de la matriz de botones. [Ver instrucciones](docs/tests/matrix.md).

2. **Prueba de Comunicación I²C**  
   Verifica el correcto funcionamiento de la comunicación I²C entre dispositivos. [Ver instrucciones](docs/tests/twi.md).

3. **Prueba de Joystick Virtual**  
   Simulación de la pulsación de un botón en un joystick. [Ver instrucciones](docs/tests/pvjoy.md).

4. **Prueba de Comunicación Serial**  
   Verifica el correcto funcionamiento de la comunicación serial entre el arduino y los scripts que corren en la PC. [Ver instrucciones](docs/tests/serial.md).

5. **Prueba de la librería SimConnect**  
   Verifica el funcionamiento básico de la librería SimConnect para obtener variables del simulador. [Ver instrucciones](docs/tests/simconnect.md).

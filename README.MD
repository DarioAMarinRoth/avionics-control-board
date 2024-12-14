# Panel de Instrumentos para simuladores de vuelo basado en microcontroladores ATMega328p

## Introducción

Este repositorio contiene el desarrollo del proyecto final de la materia optativa "Programación de sistemas embebidos". El mismo se trata de un panel de instrumentos personalizado para su uso en simuladores de vuelo.

> [!IMPORTANT]  
> El proyecto aún se encuentra en desarrollo y actualmente no es funcional.

## Características

- Posibilidad de conectar hasta más de 36 entradas.
- Control e interacción en tiempo real con Flight Simulator.
- Respuestas en base a eventos que sucedan en el simulador.

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

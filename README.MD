# Avionics Control Board

## Introducción

Este repositorio contiene los archivos del trabajo final de la materia optativa "Programación de sistemas embebidos" de la carrera de Ingeniería Electrónica de la Universidad Nacional del Comahue. 

El proyecto consiste en un panel de controles para simuladores de vuelo que admite interruptores, encoders y salidas lumínicas. Si bien el periférico se puede utilizar con cualquier simulador (dado que la PC lo reconoce como un joystick cualquiera por utilizar el software **VJoy**), tiene una integración dedicada con **Microsoft Flight Simulator 2020**. Esto permite que el simulador excite las salidas lumínicas en base a eventos que ocurran en el vuelo mediante la API **SimConnect**.

Todo el sistema se diseñó alrededor del microcontrolador **ATmega328P**, usando como base una placa Arduino Nano. El firmware del sistema embebido se ejecuta utilizando **XINU OS** como sistema operativo, diseñado originalmente por Douglas E. Comer. Específicamente, se utiliza el port `xinu-avr` desarrollado por Rafael Ignacio Zurita (docente de la cátedra), el cual también integra código escrito por Michael M. Minor.

## Características principales

- Soporte para hasta **36 entradas** del tipo ON/OFF.
- Un eje rotativo mediante encoder óptico, pensado originalmente como rueda para el compensador de cabeceo (trim).
- Luces indicadoras de estado del tren de aterrizaje (abajo y en tránsito).
- Retroiluminación de cabina integrada.
- Integración bidireccional directa con Flight Simulator 2020.

## Estructura del repositorio

- `/chasis`: Modelos 3D y demás apartados referentes al gabinete y mecánica del periférico.
- `/firmware`: Código fuente para el microcontrolador.
- `/hardware`: Diseño de la placa PCB (Esquemáticos, lista de materiales y archivos Gerber).
- `/software`: Aplicación puente que gestiona la comunicación entre el panel físico y la API de MSFS 2020.

Para instrucciones sobre cómo ensamblar el chasis, flashear el firmware, configurar el software de conexión y demás detalles de implementación, por favor visita la [Wiki del proyecto](https://github.com/DarioAMarinRoth/avionics-control-board/wiki).

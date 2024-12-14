# Comunicación serial entre Arduino nano y Python

El test tiene dos partes: el programa en C que corre en el arduino y un script en Python que se ejecuta en una computadora (puede ser en Linux o Windows).

## Elementos necesarios

### Hardware

- Un Arduino Nano.
- Resistencias de 2.2 kΩ (x2).
- Pulsador normal abierto (x2).

### Software

- Python 3
- Biblioteca `pyserial` para Python. Se puede instalar con : `pip install pyserial`

## Uso

### Conexionado
El armado consiste simplemente en conectar uno de los terminales de los pulsadores a los pines D2 y D12 del arduino utilizando las resistencias en configuración de pull down y el otro terminal a +5V. A continuación se muestra un esquema de conexión:

[Conexionado](../schematics/py-serial.svg)

### Configuración del Arduino

1. Abrir una terminal y situarse en el directorio raíz del proyecto.
2. Ejecutar el comando `make py-serial-test` para compilar el programa.
3. Conectar el Arduino a la computadora.
4. Flashear el programa en el Arduino con el comando `make flash`.
5. Limpiar la carpeta de archivos generados con el comando `make clean`. _(Opcional)_

### Configurar el puerto en Python

En el script de Python, se debe configurar el puerto serial al que está conectado el Arduino en el archivo [`src/tests/integration/serial/main.py`](../../src/tests/integration/serial/main.py). Para ello, se debe establecer el primer argumento del constructor de la clase `Serial` con el puerto serial que se utilizará.

Por defecto, el argumento es `'/dev/ttyUSB0'` que debería funcionar sin problemas en Linux. En el caso de Windows, habría que cambiarlo por el puerto correspondiente, por ejemplo `COM3`.

> [!TIP]
> En caso de no saber cuál es el puerto correspondiente en Windows, se puede verificar en el administrador de dispositivos en que puerto está conectado el Arduino.

### Ejecución

Con el Arduino conectado a la computadora, correr el script de Python.

Si se presiona el pulsador conectado en D12, debería imprimirse un mensaje por consola. Presionar el pulsador conectado a D2, debería finalizar el script en Python.

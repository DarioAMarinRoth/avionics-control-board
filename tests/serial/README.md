# Comunicación serial entre Arduino nano y Python

El test tiene dos partes: el programa en C que corre en el arduino y un script en Python que se ejecuta en una computadora (puede ser en Linux o Windows).

## Elementos necesarios

### Hardware

- Un Arduino Nano.
- Resistencias de 2.2 kΩ (x2).
- Pulsador normal abierto (x2).

### Software

- Python 3
- Biblioteca `pyserial` para Python. Se puede instalar con :
  
    ```bash
    pip install pyserial.
    ```

## Uso

### Configuración del Arduino

Conectar los pulsadores a los pines D2 y D12 del arduino utilizando las resistencias en configuración de pull down.

Compilar el programa con el comando con `make` y flahsear con `make flash`.

### Configurar el puerto en Python

El primer argumento del constructor de la clase `Serial` debe ser el puerto serial al que está conectado el Arduino.

En el test el argumento es `'/dev/ttyUSB0'` que debería funcionar sin problemas en Linux. En el caso de que utilizarse en Windows, habría que cambiarlo por `'COM3'` (eso en mi caso, pero debería verificarse en el administrador de dispositivos en que puerto está conectado el Arduino).

### Ejecución

Con el Arduino conectado a la computadora, correr el script de Python.

Si se presiona el pulsador conectado en D12, debería imprimirse un mensaje por consola. Presionar el pulsador conectado a D2, debería finalizar el script en Python.
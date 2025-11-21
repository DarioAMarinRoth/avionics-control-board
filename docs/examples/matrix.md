# Prueba de la Matriz de Botones

## Conexionado

Para ejecutar el test se requerirá:

- Resistencias de 2220 Ω: 4
- Pulsadores normales abiertos: 4
- Cables varios

Las conexiones se muestran en la siguiente imagen:

![Conexionado](../schematics/matrix-test.svg)

> [!WARNING]
> Este conexionado no admite que se presionen dos botones simultáneos. Para ello, es necesario añadir un diodo por cada pulsador.

## Ejecución

### Cargar el programa

1. Abrir una terminal y posicionarse en la carpeta raíz del proyecto.
2. Compilar el programa con `make matrix-keyboard`.
3. Conectar el Arduino a la PC y flashear el programa con `make flash`.
4. Ejecutar `make clean` para borrar los archivos de build. *(Opcional)*

### Funcionamiento

El comportamiento esperado es el siguiente: El programa leerá el estado de los pulsadores conectados en una matriz de 2x2 y enviará el estado de cada pulsador a través de la comunicación serial. Si se presiona un pulsador, se enviará un '1', de lo contrario, se enviará un '0'. Los resultados se imprimirán en la consola en un formato de matriz.

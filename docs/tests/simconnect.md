# Prueba básica de la librería SimConnect

El objetivo de este script es testear el funcionamiento básico de la librería **SimConnect** para interactuar con **Microsoft Flight Simulator**. En especifico verifica la conexión con el simulador e imprime en la consola el estado del tren de aterrizaje.

## Requisitos

- **Python 3.x**
- Librería [**SimConnect**](https://github.com/odwdinc/Python-SimConnect) instalada.
- Microsoft Flight Simulator 2020

La librería SimConnect se puede instalar con:

```bash
pip install SimConnect
```

## Ejecución del script

El script intenta establecer una conexión con Microsoft Flight Simulator y, una vez conectado, monitorea la posición del tren de aterrizaje.  
Para ejecutar el script hay que correr el siguiente comando:

```bash
python main.py
```

> [!NOTE]
> Si Microsoft Flight Simulator no está ejecutándose, la conexión fallará. El script intentará conectarse automáticamente cada 30 segundos hasta que se logre la conexión.

### Ejemplo de salida

```plain
Conexión a Flight Simulator establecida.
Tren: abajo
Tren: abajo
Tren: abajo
Tren: abajo
Tren: en tránsito
Tren: en tránsito
Tren: en tránsito
Tren: arriba
Tren: arriba
```

> [!NOTE]
> Por defecto, el valor del tren de aterrizaje es **abajo**, incluso en el menú principal del juego cuando no se está volando ningún avión.

## Estructura del código

El código se divide en tres funciones:

`connect_to_flight_sim()`: Intenta establecer una conexión con el simulador. \
`get_gear_position(index)`: Obtiene la posición del tren de aterrizaje para un índice específico. \
`main()`: Punto de entrada principal del script, que se ejecuta en un bucle infinito.

Para interrumpir el script simplemente presionar `Ctrl + C`.

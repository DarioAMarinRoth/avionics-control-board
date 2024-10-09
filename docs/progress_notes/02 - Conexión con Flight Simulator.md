08/10/2024

# Conexión con Flight Simulator 2020

El simulador provee un [SDK](https://docs.flightsimulator.com/html/Introduction/SDK_Overview.htm) para desarrollar add-ons. En especial, existe una API para la comunicación con el simulador llamada **SimConnect**. En pocas palabras, permite interactuar con el simulador para **obtener datos de vuelo**, controlar aspectos del simulador, entre otros.

## Lenguajes tolerados

Según la [documentación](https://docs.flightsimulator.com/html/Programming_Tools/SimConnect/SimConnect_SDK.htm), para componentes _"Out-of-process"_, se puede utilizar C, C++ o cualquier lenguaje .NET. Existen incluso bibliotecas en python de terceros.

## SimVars

Las SimVars (Simulation Variables) son variables utilizadas en Microsoft Flight Simulator para representar diversos estados y parámetros del simulador. Se utilizan en combinación con la API SimConnect para leer y, en algunos casos, escribir valores en el simulador.

### Variables para el tren de aterrizaje

Hay muchas [variables para el tren de aterrizaje](https://docs.flightsimulator.com/html/Programming_Tools/SimVars/Aircraft_SimVars/Aircraft_Brake_Landing_Gear_Variables.htm). De toda la lista, creo que la más interesante para el trabajo es `GEAR_POSITION:index`. Esta variable es un Enum que indica la posición del tren de aterrizaje.

| Enum  | Significado           |
|-------|-----------------------|
| 0     | Posición desconocida  |
| 1     | Tren retraído         |
| 2     | Tren desplegado       |

Por otro lado, index se utiliza para identificar cada tren de aterrizaje individualmente.

| Index | Descripción                |
|-------|----------------------------|
| 0     | Tren de nariz              |
| 1     | Tren principal izquierdo   |
| 2     | Tren principal derecho     |
| ≥ 3   | Otros trenes de aterrizaje |

### Otras variables

Algunas variables que se me ocurren que podrían resultar interesantes pueden ser `BATTERY_CONNECTION_ON` o `ALTERNATOR_CONNECTION_ON` de tal forma que si el avión no tiene energía que prenda las iluminación del panel. Me parece copado para una situación en la que el avión esté en emergencia y que se apaguen las luces de golpe.

## Librería SimConnect de Python

Existe una librería en python llamada SimConnect que encapsula funcionalidades de la API SimConnect, permitiendo acceder a datos del simulador (entre otras cosas), sin la necesidad de programar directamente en C++.

> ℹ️ : Armé un test de esta librería. Se encuentra en `tests\simconnect` y funcionó perfectamente.

Se instala con el comando:

```bash
pip install SimConnect
```

### Consideraciones y cosas útiles

#### Clase SimConnect

Para usar la librería es necesario crear una instancia de la clase `SimConnect`:

```py
from SimConnect

sm = SimConnect()
```

Este objeto representa la conexión entre el script y el simulador. Por lo que **no siempre es posible crear la instancia**. Solo se logra si el simulador está en ejecución. En el caso de que el simulador no esté corriendo, el constructor arrojará una excepción.

#### Clase AircraftRequests

La clase AircraftRequests se utiliza para realizar solicitudes específicas sobre el estado del avión en el simulador de vuelo, como obtener datos sobre su posición, velocidad, altitud, y otros parámetros.

El constructor de la clase recibe dos argumentos:

- `_sm`: Un objeto de conexión de tipo SimConnect.
- `_time` (opcional): El intervalo de tiempo en milisegundos entre las solicitudes. Por defecto, se establece en 10 ms. Establecer el tiempo en 0 desactivará la caché de datos y siempre obtendrá nuevos datos del simulador
- `_attempts` (Opcional): El número de intentos que realizará la clase para obtener la información del simulador. Por defecto, se establece en 10.

Obviamente, para realizar solicitudes, sera necesario crear una instancia de la clase AircraftRequests.

```py
from SimConnect

sm = SimConnect()
aq = AircraftRequests(sm, _time=200)
```

La clase tiene dos métodos principales:

1. `get(variable_name)`: obtiene el valor de una variable específica del avión. El nombre de la variable es coincidente con el de la SimVar de la documentación de SimConnect y debe pasarse como un String.
2. `set(variable_name, value)`: Establece el valor de una variable específica del avión (no todas las variables se pueden settear, hay que fijarse en la documentación del SDK cuales sí).

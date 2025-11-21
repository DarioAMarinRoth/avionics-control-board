# Aplicación principal

## Funcionamiento general

El panel de instrumentos tiene dos funcionalidades: inyectar eventos en el simulador a través de las entradas y mostrar información asociada a eventos que ocurren en el simulador a través de las salidas.

El caso más general de una situación es aquel donde una entrada genera un evento para el cual se espera una salida. En ese caso, el flujo de ejecución es:

```mermaid
graph LR
    A[Entrada] --> B[Evento]
    B --> C[Salida]
```

>[!Important]
> Nunca una salida puede ser una consecuencia directa de una entrada. Siempre debe existir un evento que la genere. Esto porque es posible que el evento que debería generar una entrada no suceda finalmente en el simulador.

## Detalles de implementación

### Referencia técnica

- [Tareas](#tareas)
- [Semáforos](#semáforos)
- [Variables globales](#variables-globales)
- [Pendientes e implementaciones temporales](temp-imp.md)

### Explicación general

A continuación se presenta un diagrama en bloques general del sistema.

![Diagrama del sistema](misc/db.svg)

#### Entradas

Las entradas se pueden accionar de dos maneras: una mediante una matriz de botones que se comunica con el maestro vía I²C y la otra mediante un encoder conectado directamente a uno de los pines del maestro.

Todas las entradas son del tipo ON/OFF. La única excepción es la entrada del encoder que tiene asociado un valor (almacenado en la variable global [`trim`](#trim)) entre 0 y 200. Además, todas las entradas se identifican mediante un ID que va de 0 a 35, siendo 35 el ID del encoder.

El programa en Python de la PC que se comunica con el simulador, almacena el estado de todas las entradas (un par ID-Valor). Cómo casi todas las entradas son binarias, el maestro debe transmitir simplemente el ID de las entradas que hayan conmutado su estado. En el caso de la entrada el encoder, se transmitirá la suma de su ID y el valor de la entrada. De esta manera se puede distinguir esta entrada del resto y recuperar su valor luego restando 35.

La tarea periódica [`get_inputs()`](#get-inputs) recibe los IDs de las entradas que hayan conmutado su estado en la matriz de botones. Dichas IDs se almacenan temporalmente en la cola [`changed_inputs`](#changed_inputs) para ser transmitidas luego.

Por otro lado, si se activa el encoder, se generará una interrupción. Luego, en la rutina de atención de interrupciones `ISR(INT0_VECT)` se actualizará el valor de la entrada para poder ser transmitida junto con los valores de la cola.

##### Transmisión de las entradas

Periódicamente se activará la tarea [`send_inputs()`](#send-inputs) que envía la actualización de las entradas por serial. Primero se mandan todos los datos presentes en la cola y por último se envía la entrada del encoder, independientemente de si sufrió cambios.

#### Salidas

Al igual que las entradas, todas las salidas son binarias y están identificadas con un ID. En el Master, existe un array llamado [`outputs`](#outputs) que lleva el estado actual (el par ID-valor) de las salidas. Periódicamente, la tarea [`set_outputs()`](#set-outputs) barre el array para prender o apagar las salidas según lo establezca el estado.

##### Actualización del estado

El estado se actualiza cuando se recibe nueva información proveniente del simulador. Cada palabra que se recibe de la pc consta de 3 bytes que deben ser reconstruidos como un único número entero. Además, un mensaje consta de dos palabras: el ID y el valor de la salida.

Para esto, se cuentan con dos tareas; [`main()`](#main) que se encarga de recibir los tres bytes y reconstruir la palabra y [`update_outputs()`](#update-outputs) que actualiza el valor de las salidas correspondientes del vector de [`outputs`](#outputs). Ambas tareas funcionan de manera sincronizada empleando semáforos:

1. Cuando llega un nuevo byte por serial, se genera una interrupción que almacena el byte recibido en el buffer circular [`buf`](#buf) y activa el semáforo [`new_byte`](#new_byte).
2. La tarea [`main()`](#main) espera el semáforo [`new_byte`](#new_byte) y otro más (inicialmente en 1) denominado [`word_consumed`](#word_consumed).  Este segundo semáforo se explicará más adelante.
3. Cuando se activa [`new_byte`](#new_byte), [`main()`](#main) se despierta, consume el byte del buffer para realizar la conversión y vuelve a esperar por un nuevo byte. Este proceso se repite dos veces más para poder generar la palabra completa.
4. La palabra está lista se encontrará almacena en una variable global [`rx_word`](#rx_word). cuando esto suceda se activa el semáforo [`new_word`](#new_word) que despierta a la tarea [`update_outputs()`](#update-outputs) mientras que [`main()`](#main) se quedará a la espera del semáforo [`word_consumed`](#word_consumed).
5. [`update_outputs()`](#update-outputs) guardará internamente la palabra recién creada como el ID de la salida a modificar, activará el semáforo [`word_consumed`](#word_consumed) y esperará una segunda palabra correspondiente al valor de la salida.
6. Cuando la nueva palabra esté disponible, se actualizará la salida correspondiente del vector de salidas para que puedan ser actualizadas en el próximo barrido de [`set_outputs()`](#set-outputs).

### Tareas

| Tarea              | Estatus | Tipo                                                    | Descripción                                                                                                           |
| ------------------ | ------- | ------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------- |
|<span id="get-inputs">`get_inputs()`</span>    | [Implementación provisoria](temp-imp.md#get_inputs)| Periódica (13 ms)                                       | Recibe los ID de las entradas que se hayan conmutado y las añade a la cola [`changed_inputs`](#changed_inputs).                         |
| <span id="send-inputs">`send_inputs()`</span>    |Implementada| Periódica (13 ms)                                       | Envía por serial la información que se encuentre en el momento en la cola [`changed_inputs`](#changed_inputs) y el valor de la variable [`trim`](#trim). |
| <span id="set-outputs">`set_outputs()`</span>    |Implementada| Periódica (13 ms)                                       | Realiza un barrido por el array [`outputs`](#outputs) y enciende o apaga las salidas correspondientes.                           |
| <span id="main">`main()`</span>           |Implementada| Activación por semáforos: [`new_byte`](#new_byte) [`word_consumed`](#word_consumed)    | Construye una palabra a partir de bytes recibidos por serial. Activa el semáforo [`new_word`](#new_word) cuando la palabra está lista. |
| <span id="update-outputs">`update_outputs()`</span> |Implementada| Activación por semáforos: [`new_word`](#new_word)                    | Modifica el estado de una salida en vector de estados [`outputs`](#outputs) a partir de dos palabras (ID y valor de una salida). Activa el semáforo [`word_consumed`](#word_consumed). |

### Semáforos

| Semáforo         | Significado                                                                                                                          |
| ---------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| <span id="new_byte">`new_byte`</span>       | Llegó un nuevo byte por serial desde la PC. Se activa en la rutina de atención de interrupciones del serial.                        |
| <span id="new_word">`new_word`</span>       | Se procesaron tres bytes para formar una palabra. Se activa en la tarea [`main()`](#main).                                                   |
| <span id="word_consumed">`word_consumed`</span>  | Se rescató la palabra que llegó por serial de la variable [`rx_word`](#rx_word) y está disponible para almacenar una nueva. Se activa en la tarea [`update_outputs()`](#update-outputs). |

### Variables globales

| Variable | Tipo | Contenido |
| -------- | ---- | --------- |
| <span id="trim">`trim`</span> | `uint_8` | Valor de la entrada asociada al encoder [0-200]. |
| <span id="rx_word">`rx_word`</span> | `uint_8` | Última palabra recibida por serial. |
| <span id="buf">`buf`</span> | `buffer_t` | Bytes recibidos por serial. Tiene capacidad para 28 bytes. |
| <span id="changed_inputs">`changed_inputs`</span>| `* my_queue` | Puntero a la cola con los IDs de las entradas modificadas en la matriz de entradas. |
| <span id="outputs">`outputs`</span> | `var_map[]`| Vector del estado actual de las salidas. Contiene el par ID-Valor de cada una. |

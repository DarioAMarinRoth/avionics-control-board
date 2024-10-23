# Interfaz del módulo TWI (I²C)

## Constantes

- `FR_CPU`: Frecuencia del procesador: 16 MHz
- `F_I2C`: Frecuencia de comunicación: 100 kHz
- `DEFAULT_SLA`: Dirección del esclavo por defecto

## Enum `twi_status`

- `SUCCESS`: 0
- `ERR_START_FAILED`: 1
- `ERR_ARBITRATION_LOST`: 2
- `ERR_NO_ACK`: 3
- `ERR_MEMORY_ALLOCATION_FAILED`: 4

## Funciones

### `void master_init(void)`

Inicializa el TWI en modo maestro.

Configura el registro de estado TWI con un prescaler de 16, establece el registro de bit rate TWI para la frecuencia de CPU y TWI, y habilita el TWI.

### `void slave_init(void)`

Inicializa el TWI en modo esclavo.

Configura el registro de dirección TWI con la dirección del esclavo y habilita el TWI y la generación de ACK.

### `void sla_slave_init(const uint8_t sla)`

Inicializa el TWI en modo esclavo con una dirección específica.

Configura el registro de dirección TWI con la dirección del esclavo proporcionada y habilita el TWI y la generación de ACK.

- **Parámetros:**
    - `sla`: Dirección del esclavo a configurar.

### `uint8_t twi_start(void)`

Genera una condición de inicio en el bus TWI.

Configura el registro de control TWI para generar una condición de inicio y espera hasta que la transmisión se complete.

- **Retorna:** Código de estado de la operación de inicio.

### `void twi_stop(void)`

Genera una condición de parada en el bus TWI.

Configura el registro de control TWI para generar una condición de parada.

### `uint8_t transmit(const uint8_t data)`

Transmite un byte de datos en el bus TWI.

Configura el registro de datos TWI con el byte a transmitir y espera hasta que la transmisión se complete.

- **Parámetros:**
    - `data`: Byte de datos a transmitir.
- **Retorna:** Código de estado de la operación de transmisión.

### `void send_ACK(void)`

Envía una señal de reconocimiento (ACK) en el bus TWI.

Configura el registro de control TWI para enviar una señal de reconocimiento y espera hasta que la transmisión se complete.

### `void send_NACK(void)`

Envía una señal de no reconocimiento (NACK) en el bus TWI.

Configura el registro de control TWI para enviar una señal de no reconocimiento y espera hasta que la transmisión se complete.

### `uint8_t twi_master_receive(const uint8_t tx_sla, const int n)`

Recibe datos en modo maestro desde un esclavo TWI.

Inicia una condición de inicio, transmite la dirección del esclavo con el bit de lectura, y recibe los datos del esclavo.

- **Parámetros:**
    - `tx_sla`: Dirección del esclavo desde el cual recibir los datos.
    - `n`: Número de bytes a recibir.
- **Retorna:** Código de estado de la operación de recepción.

### `void free_storage(void)`

Libera la memoria asignada para el almacenamiento de datos recibidos.

### `int init_data(const size_t n)`

Inicializa el almacenamiento de datos recibidos.

Asigna memoria para almacenar los datos recibidos.

- **Parámetros:**
    - `n`: Número de bytes a almacenar.
- **Retorna:** Código de estado de la operación de inicialización.

### `uint8_t* get_received_data(void)`

Obtiene los datos recibidos.

Devuelve un puntero a los datos recibidos almacenados.

- **Retorna:** Puntero a los datos recibidos.
# Pendientes e implementaciones provisorias

## Funcionalidades pendientes

- Rutina de atención de interrupciones de la GPIO (para registrar cambios en el encoder).
- Incorporar la comunicación I²C como medio para registrar entradas.

## Implementaciones temporales

### `get_inputs()`

Como el I²C no está incluido aún en la aplicación principal, temporalmente hay un único pulsador NA conectado al pin D2 del arduino que emula la matriz de botones. La función lee periódicamente el estado del pulsador y lo compara con el último valor del que se tenía registro. Si los valores difieren, encola el ID del pulsador (arbitrariamente 0) y actualiza localmente el estado del pulsador para las siguientes comparaciones.

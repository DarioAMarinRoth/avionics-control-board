29/08/2024

# Probando vJoy

De las alternativas que busqué la semana pasada, arranqué probando vJoy junto con la librería `pyvjoy`.

Arme un script para probar la librería ( se encuentra en `tests/pyvjoy`) y funciona perfectamente, por lo que me me parece que es la solución más fácil de implementar.

**Trabajo pendiente para la próxima:**

- Establecer una comunicación serial entre el micro y el script en python.
  1. Enviar información por serial cuando ser presiona un pulsador.
  2. Recibir esa información en python.
  3. Utilizar la información para generar eventos en el dispositivo virtual.

- Probar los ejes del dispositivo virtual (comandos analógicos).

**Dudas:**

El comportamiento ideal del dispositivo debería ser *plug and play*. Por ende, al conectar el arduino debería iniciarse automáticamente el loop de python que recibe la información por serial. De la misma manera.

De la misma manera, al desconectar el arduino, el loop debería finalizar.

¿Cómo se puede implementar este comportamiento?

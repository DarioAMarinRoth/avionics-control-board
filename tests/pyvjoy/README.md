# Test librería pyvjoy

Este script utiliza la biblioteca pyvjoy para simular la pulsación de un botón en un dispositivo de joystick virtual. El script configura un dispositivo de joystick virtual y alterna el estado de un botón entre alto y bajo en intervalos de tiempo.

## Uso

### Requisitos

- Python 3
- Biblioteca `pyvjoy`
- Controlador vJoy

### Instalación

1. [Descargar](https://www.vjoy.org/download-for-windows/download) e instalar vJoy.
   - Luego de la instalación, en los dispositos de juego USB debería aparecer un nuevo dispositivo llamado vJoyDevice.
2. Instalar `pyvjoy`
   - Esto se puede hacer utilizando el siguiente comando:
  
        ```bash
        pip install pyvjoy
        ```

### Ejecución

Correr el archivo `main.py`.

Si todo está correcto, en las propiedades del dispositivo vJoyDevice debería verse cómo se alternan pulsaciones en el botón 1.

---
## Referencias

Este script se basa en la biblioteca pyvjoy, de [este respositorio](https://github.com/tidzo/pyvjoy).

# Compilar y Flashear el Master

Esta guía explica como compilar desde el código fuente y cargar el firmware del Master en el Arduino Nano
correspondiente. El Master ejecuta el kernel XINU OS y es responsable de la comunicación serial con la PC, el manejo del
encoder y el control de los LEDs indicadores. Seguir este procedimiento es necesario cada vez que se modifique el código
fuente del firmware o se configure una nueva placa desde cero.

## Antes de empezar

### Hardware requerido

- Arduino Nano (ATmega328P) que actuará como Master
- Cable USB para conectarlo a la PC

### Software requerido

<tabs group="os">
    <tab id="ubuntu" title="Linux" group-key="linux">
      Utiliza el siguiente comando para instalar todos los paquetes necesarios:
      <code-block lang="Shell">
      sudo apt update &amp;&amp; sudo apt install gcc-avr binutils-avr avr-libc avrdude make git
      </code-block>
      <table>
      <tr><td>Paquete</td><td>Uso</td></tr>
      <tr><td><code>gcc-avr</code></td><td>Compilador en C para microcontroladores AVR</td></tr>
      <tr><td><code>binutils-avr</code></td><td>Linker y utilidades para AVR</td></tr>
      <tr><td><code>avr-libc</code></td><td>Biblioteca estándar de C para AVR</td></tr>
      <tr><td><code>avrdude</code></td><td>Herramienta para flashear el .hex al Arduino</td></tr>
      <tr><td><code>make</code></td><td>Build</td></tr>
      <tr><td><code>git</code></td><td>Clonar el repositorio</td></tr>
      </table>
        <chapter title="Clonar el repositorio">
            Asegurate de tener el repositorio clonado localmente:
            <code-block lang="shell">
                git clone https://github.com/DarioAMarinRoth/avionics-control-board.git  
                cd avionics-control-board
            </code-block>
        </chapter>
    </tab>
    <tab id="windows-software" title="Windows" group-key="windows">
        <include from="install-guide.topic" element-id="windows-reqs"></include>
    </tab>
</tabs>

## Compilar y flashear

### Compilar el firmware

<tabs group="os">
    <tab id="ubuntu-comp" title="Linux" group-key="linux">
        <include from="install-guide.topic" element-id="linux-comp"></include>
    </tab>
    <tab id="windows-comp" title="Windows" group-key="windows">
        <include from="install-guide.topic" element-id="windows-comp"></include>
    </tab>
</tabs>

### Flashear el firmware

<tabs group="os">
    <tab id="ubuntu-flash" title="Linux" group-key="linux">
        <include from="install-guide.topic" element-id="linux-flash"></include>
    </tab>
    <tab id="windows-flash" title="Windows" group-key="windows">
        <include from="install-guide.topic" element-id="windows-flash"></include>
    </tab>
</tabs>
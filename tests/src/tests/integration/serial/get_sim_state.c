//
// Created by dario on 7/31/25.
//

#include "gpio.h"
#include "serial.h"

void main() {
    int led = 13;
    gpio_output(led);
    serial_init();
    while (1) {
        if (serial_get_char() == '1') { // TODO: ver la forma de recibir un entero en lugar de un char
            gpio_pin(led, ON);
        } else {
            gpio_pin(led, OFF);
        }
    }
}

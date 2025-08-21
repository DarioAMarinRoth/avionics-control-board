//
// Created by dario on 7/31/25.
//

#include "gpio.h"
#include "serial.h"

void main() {
    uint16_t msg;
    int led = 13;
    gpio_output(led);
    serial_init();

    while (1) {
        msg = serial_get_uint(5);
        if (msg == 12345) {
            gpio_pin(led, ON);
        } else {
            gpio_pin(led, OFF);
        }
    }
}

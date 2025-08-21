//
// Created by dario on 7/31/25.
//

#include "gpio.h"
#include "serial.h"

void main() {
    int led = 13;
    gpio_output(led);
    serial_init();
    serial_put_str("COMENZANDO... \n\r");

    while (1) {
        serial_put_str("Esperando mensaje \n\r");
        uint16_t msg = serial_get_uint(5);
        serial_put_str("Mensaje recibido:");
        serial_put_int(msg, 5);
        serial_put_str("\n\r");
        serial_put_str("\n\r");
        serial_put_str("\n\r");
        if (msg == 12345) {
            gpio_pin(led, ON);
        } else {
            gpio_pin(led, OFF);
        }
    }
}

//
// Created by dario on 22/11/25.
//

#include <stdint.h>

#include "gpio.h"
#include "my_queue.h"
#include "twi-slave.h"
#include "serial.h"

// #include "matrix-keyboard.h"



int main() {
    my_queue *events_queue = f_create_queue();
    serial_init();
    twi_slave_init();
    gpio_input(2);

    uint8_t prev_value = 0;
    uint8_t current_value;
    uint8_t data;
    while (1) {
        current_value = gpio_pin(2,  GET);
        if (current_value == prev_value) {
            continue;
        }
        f_add(events_queue, 0);
        serial_put_str("Transmitiendo el tamaño de la cola\n\r");
        twi_slave_transmit(f_get_size(events_queue));
        serial_put_str("Tamaño de la cola transmitido\n\r");
        while (!f_is_empty(events_queue)) {
            serial_put_str("Información a transmitir: ");
            data = f_poll(events_queue);
            serial_put_int(data, 1);
            serial_put_str("\n\r");
            twi_slave_transmit(data);
        }
    }
}
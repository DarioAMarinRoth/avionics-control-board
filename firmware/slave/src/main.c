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
        prev_value = current_value;
        f_add(events_queue, 0);
        twi_slave_transmit(f_get_size(events_queue));
        while (!f_is_empty(events_queue)) {
            data = f_poll(events_queue);
            twi_slave_transmit(data);
        }
    }
}
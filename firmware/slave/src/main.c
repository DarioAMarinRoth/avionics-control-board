//
// Created by dario on 22/11/25.
//

#include "my_queue.h"
#include "twi-slave.h"
#include "serial.h"
#include "matrix-keyboard.h"



int main() {
    uint8_t data;
    my_queue *events_queue;
    matrix_init();
    events_queue = get_toggle_events();
    twi_slave_init();
    while (1) {
        scan();
        if (f_is_empty(events_queue)) {
            continue;
        }
        twi_slave_transmit(f_get_size(events_queue));
        while (!f_is_empty(events_queue)) {
            twi_slave_transmit(f_poll(events_queue));
        }
    }
}
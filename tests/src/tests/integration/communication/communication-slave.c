//
// Created by dario on 30/12/24.
//

#include "twi-slave.h"
#include "matrix-keyboard.h"
#include "my_queue.h"

void main() {

    matrix_init();
    twi_slave_init();
    my_queue *data = get_toggle_events();

    while (1) {
        scan();
        if (f_is_empty(data)) {
            twi_slave_transmit(-1);
            continue;
        }
        do {
            twi_slave_transmit(f_poll(data));
        } while (!f_is_empty(data));

    }
}

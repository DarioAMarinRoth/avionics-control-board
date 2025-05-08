//
// Created by dario on 30/12/24.
//

#include "twi-slave.h"
#include "matrix-keyboard.h"

void main() {

    matrix_init();
    twi_slave_init();
    queue *data = get_toggle_events();

    while (1) {
        scan();
        if (is_empty(data)) {
            twi_slave_transmit(-1);
            continue;
        }
        do {
            twi_slave_transmit(pop(data));
        } while (!is_empty(data));

    }
}

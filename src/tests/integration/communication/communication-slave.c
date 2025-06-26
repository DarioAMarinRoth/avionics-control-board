//
// Created by dario on 30/12/24.
//

#include "twi-slave.h"
#include "matrix-keyboard.h"

void main() {

    matrix_init();
    twi_slave_init();
    my_queue *data = get_toggle_events();
    data.create_queue();


    while (1) {
        scan();
        if (is_empty(data)) {
            twi_slave_transmit(-1);
            continue;
        }
        do {
            twi_slave_transmit(dequeue(data));
        } while (!is_empty(data));

    }
}

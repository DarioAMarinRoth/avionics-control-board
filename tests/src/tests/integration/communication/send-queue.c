//
// Created by dario on 6/19/25.
//


#include <stdint.h>

#include "my_queue.h"
#include "twi-slave.h"

void loop(my_queue *data, uint8_t msg[], uint8_t size);

void main() {
    my_queue *data = f_create_queue();
    uint8_t msg[] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t size = 8;
    twi_slave_init();
    while (1) {
        loop(data, msg, size);
    }
}

void loop(my_queue *data, uint8_t msg[], uint8_t size) {
    for (int i = size - 1; i >= 0; --i) {
        f_add(data, msg[i]);
    }
    twi_slave_transmit(f_get_size(data));

    while (!f_is_empty(data)) {
        twi_slave_transmit(f_poll(data));
    }

    msg[0]++;
    for (int i = 0; i < size; ++i) {
        if (msg[i] == 10) {
            msg[i] = 0;
            if (msg[i + 1] < size) {
                msg[i + 1]++;
            }
        }
    }
}

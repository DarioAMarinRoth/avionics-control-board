//
// Created by dario on 6/19/25.
//


#include <stdint.h>

#include "my_queue.h"
#include "twi-slave.h"

void main() {
    my_queue *data = f_create_queue();
    f_push(data,4);
    f_push(data,0);
    f_push(data,6);
    f_push(data,1);
    f_push(data,2);
    f_push(data,5);
    f_push(data,8);
    f_push(data,9);

    twi_slave_init();
    twi_slave_transmit(f_get_size(data));
    while (!f_is_empty(data)) {
        twi_slave_transmit(f_pop(data));
    }
}
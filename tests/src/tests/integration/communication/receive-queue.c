//
// Created by dario on 6/19/25.
//

#include <stdint.h>

#include "my_queue.h"
#include "twi-master.h"
#include "serial.h"

void main() {
    my_queue *data = f_create_queue();

    serial_init();
    serial_put_str("Comenzando...\n\r");
    twi_master_init();
    twi_master_receive_byte(DEFAULT_SLA);
    serial_put_str("El tamaño de la cola se recibió correctamente.\n\r");
    const uint8_t data_size = twi_get_received_data();
    for (int i = 0; i < data_size; ++i) {
        twi_master_receive_byte(DEFAULT_SLA);
        f_add(data, twi_get_received_data());
    }


    serial_put_str("Los datos recibidos son:\n\r");
    for (int i = 0; i < data_size; ++i) {
        serial_put_int(f_poll(data), 1);
        serial_put_str("\n\r");
    }

}

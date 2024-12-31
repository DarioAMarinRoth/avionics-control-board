//
// Created by dario on 30/12/24.
//

#include <stdint.h>

#include "twi-master.h"
#include "matrix-keyboard.h"
#include "serial.h"


void main() {

    master_init();
    serial_init();

    uint8_t buttons[N_INPUTS];
    for (int i = 0; i < N_INPUTS; i++) {
        buttons[i] = 0;
    }

    while (1) {
        twi_master_receive_byte(DEFAULT_SLA);
        const uint8_t change = get_received_data();
        buttons[change] = !buttons[change];

        for (int i = 0; i < N_INPUTS; i++) {
            serial_put_int(buttons[i], 1);
            serial_put_str(" ");
        }
        serial_put_str("\r");
    }
}
//
// Created by dario on 30/12/24.
//

#include <stdint.h>
#include <xinu.h>

#include "twi-master.h"
#include "matrix-keyboard.h"
#include "serial.h"
#include "gpio.h"

void led() {
    gpio_output(13);
    while(1){
        gpio_pin(13,ON);
        sleepms(500);
        gpio_pin(13,OFF);
        sleepms(500);
    }
}

void main() {

    twi_master_init();
    serial_init();

    resume(create(led,128, 20, "led", 0));

    uint8_t buttons[N_INPUTS];
    for (int i = 0; i < N_INPUTS; i++) {
        buttons[i] = 0;
    }
    const uint8_t change = 0;
    while (1) {
        // twi_master_receive_byte(DEFAULT_SLA);
        // const uint8_t change = twi_get_received_data();
        buttons[change] = !buttons[change];

        for (int i = 0; i < N_INPUTS; i++) {
            serial_put_int(buttons[i], 1);
            serial_put_str(" ");
        }
        serial_put_str("\r");
    }
}


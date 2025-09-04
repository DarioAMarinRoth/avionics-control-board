//
// Created by dario on 9/4/25.
//

#include <stdint.h>

#include "gpio.h"
#include "models.h"
#include "serial.h"
#include "misc.h"

static void delay_us(int us);

int main() {
    var_map state[] = {
        {0, 2, 0},
        {1, 3, 0}
    };
    uint8_t current_values[2] = {0, 0};
    uint8_t n_digits = 1;

    gpio_input(state[0].pin);
    gpio_input(state[1].pin);
    gpio_output(13);

    state[0].value = gpio_pin(state[0].pin,GET);
    state[1].value = gpio_pin(state[1].pin,GET);

    serial_init();
    while (true) {
        for (int i = 0; i < 2; ++i) {
            state[i].value = gpio_pin(state[i].pin,GET);
            if (state[i].value == 1) {
                gpio_pin(13,ON);
            } else {
                gpio_pin(13,OFF);
            }
            if (state[i].value != current_values[i]) {
                delay_us(200);
                current_values[i] = state[i].value;
                serial_put_str(to_string(state[i].id));
                serial_put_str(to_string(state[i].value));
            }
        }
    }
}

static void delay_us(int us) {
    while (us--) {
        asm volatile(
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t");
    }
}

/*
 *  Situación del 04/09
 *  Python no está recibiendo bien los datos.
 *  TODO: Convertir los enteros a strings y enviar los strings.
 */

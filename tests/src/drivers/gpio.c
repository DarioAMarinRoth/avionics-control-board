//
// Created by dario on 8/9/25.
//

#include "gpio.h"

uint8_t gpio_pin(uint8_t pin, uint8_t op) {
    switch (op) {
        case OFF:
            *pinmap[pin].port &= ~(1 << pinmap[pin].bit);
            break;
        case ON:
            *pinmap[pin].port |= (1 << pinmap[pin].bit);
            break;
        case TOGGLE:
            *pinmap[pin].port ^= (1 << pinmap[pin].bit);
            break;
        case GET:
            return (*pinmap[pin].pin >> pinmap[pin].bit) & 0x01;
        default:
            break;
    }
    return 0;
}

void gpio_input(uint8_t pin) {
    *pinmap[pin].port &= ~(1 << pinmap[pin].bit);
    *pinmap[pin].ddr &= ~(1 << pinmap[pin].bit);
}

void gpio_output(uint8_t pin) {
    *pinmap[pin].ddr &= ~(1 << pinmap[pin].bit);
    *pinmap[pin].port |= (1 << pinmap[pin].bit);
}
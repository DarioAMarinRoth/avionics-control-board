//
// Created by dario on 8/9/25.
//

#ifndef GPIO_MAP_H
#define GPIO_MAP_H

#include <stdint.h>

typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    volatile uint8_t *pin;
    uint8_t bit;
} gpio_t;

#endif //GPIO_MAP_H
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "pinmap_328p.h" // TODO: automatizar la elección del pinmap

#define OFF 0x0
#define ON 	0x1
#define TOGGLE 0x2
#define GET	0x3


uint8_t gpio_pin(uint8_t pin, uint8_t op);

void gpio_input(uint8_t pin);

void gpio_output(uint8_t pin);

#endif /* GPIO_H */

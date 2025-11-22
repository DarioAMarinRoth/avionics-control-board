#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define OFF 0x0
#define ON 	0x1
#define TOGGLE 0x2
#define GET	0x3


/**
 * @brief Realiza una operación en un pin GPIO
 * @param pin El número del pin (según el label de la placa)
 * @param op la operación a realizar (OFF, ON, TOGGLE, o GET)
 * @return El estado actual del pin (0 or 1)
 */
uint8_t gpio_pin(uint8_t pin, uint8_t op);

void gpio_input(uint8_t pin);

void gpio_output(uint8_t pin);

#endif /* GPIO_H */
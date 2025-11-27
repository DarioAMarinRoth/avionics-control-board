//
// Created by dario on 27/03/25.
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "gpio.h"
#include "serial.h"

#define A 2
#define B 3
#define SCALE 20
#define MAX_VALUE 200
#define N_START_VALUE ((MAX_VALUE/2) * SCALE)

uint8_t a;
uint8_t b;
uint16_t n = N_START_VALUE;

uint8_t detect_change(void);

void enable_interrupts();

int main(void) {
    serial_init();
    serial_put_str("START\n\r");
    gpio_input(A);
    gpio_input(B);
    gpio_pin(A,ON);
    gpio_pin(B,ON);

    a = gpio_pin(A, GET);
    b = gpio_pin(B, GET);
    enable_interrupts();
    sei();
    uint16_t value = 0;
    while (1) {
        value = n / SCALE;
        serial_put_int(value, 5);
        serial_put_str("\n\r");
    }
}

uint8_t detect_change(void) {
    return a == 0 && gpio_pin(A, GET) == 1;
}

void enable_interrupts() {
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);
}

ISR(INT0_vect) {
    a = gpio_pin(A, GET);
    b = gpio_pin(B, GET);
    if (a == b) {
        if (n < MAX_VALUE * SCALE) {
            n = n + 1;
        }
    } else {
        if (n > 0) {
            n = n - 1;
        }
    }
}

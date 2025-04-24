//
// Created by dario on 27/03/25.
//

#include <stdint.h>
#include "gpio.h"
#include "serial.h"

#define A 4
#define B 5

uint8_t a;
uint8_t b;

uint8_t detect_change(void);

int main(void) {
    serial_init();
    serial_put_str("START\n\r");
    gpio_input(A);
    gpio_input(B);
    gpio_pin(A,ON);
    gpio_pin(B,ON);


    int16_t n = 0;

    a = gpio_pin(A, GET);
    b = gpio_pin(B, GET);

    while (1) {
        while (detect_change())
            ;
        a = gpio_pin(A, GET);
        b = gpio_pin(B, GET);
        if (a == b) {
            n = n + 1;
        } else {
            n = n - 1;
        }
        if (n > 600) {
            n = 0;
            serial_put_str("1");
        }
        // serial_put_int(n, 4);
        // serial_put_str("\n\r");
        while (a == gpio_pin(A, GET));
    }
}

uint8_t detect_change(void) {
    return a == 0 && gpio_pin(A, GET) == 1;
}

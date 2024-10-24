#include "twi.h"
#include "gpio.h"
#include <stdint.h>

int main(void) {
    gpio_input(13);
    slave_init();

    while (1) {
        twi_slave_transmit(1);
    }
}

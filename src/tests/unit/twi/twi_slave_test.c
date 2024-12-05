#include "twi.h"
#include "gpio.h"

int main(void) {
    gpio_input(13);
    slave_init(1);
    twi_slave_transmit(1);
    twi_slave_transmit(0);
    while (1) {
    }
}

#include "gpio.h"
#include "twi.h"
#include <stdint.h>

int main(void) {
    master_init();
    uint8_t data = 0;
    gpio_output(13);

    while (1) {
        twi_master_receive_byte(DEFAULT_SLA);
        data = get_received_data();
        if (data == 1) {
            gpio_pin(13, ON);
        } else {
            gpio_pin(13, OFF);
        }
    }
}

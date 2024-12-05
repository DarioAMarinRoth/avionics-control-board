#include <stdint.h>

#include "gpio.h"
#include "twi.h"

int main(void) {
    master_init(1);
    uint8_t data = 0;
    gpio_output(13);
    gpio_pin(13, OFF);

    twi_master_receive_byte(DEFAULT_SLA);
    data = get_received_data();
    if (data == 0) {
        gpio_pin(13, OFF);
    } else {
        gpio_pin(13, ON);
    }

    while (1)
        ;

    twi_master_receive_byte(DEFAULT_SLA);
    data = get_received_data();
    if (data == 0) {
        gpio_pin(13, OFF);
    } else {
        gpio_pin(13, ON);
    }


}

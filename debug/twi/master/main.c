#include "gpio.h"
#include "twi.h"
#include <stdint.h>
#include "serial.h"

int main(void) {
    serial_init();
    master_init();
    uint8_t data = 0;
    gpio_output(13);
    serial_put_str("Start\n\r");
    int status;

    while (1) {
        status = twi_master_receive_byte(DEFAULT_SLA);
        serial_put_str("status: ");
        serial_put_int(status, 2);
        data = get_received_data();
        if (data == 1) {
            gpio_pin(13, ON);
        } else {
            gpio_pin(13, OFF);
        }
    }
}

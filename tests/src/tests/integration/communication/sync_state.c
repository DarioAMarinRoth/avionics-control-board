//
// Created by dario on 8/14/25.
//

#include <stdint.h>

#include "models.h"
#include "gpio.h"
#include "serial.h"

void main() {

    const uint8_t digits = 2;
    uint8_t red_led = 12;
    uint8_t green_led = 13;
    uint8_t STATE_SIZE = 2;
    uint16_t target_id;
    uint16_t target_value;

    var_map state[] = {
        {0,red_led, 0 },
        {1,green_led, 0}
    };

    for (int i = 0; i < STATE_SIZE; ++i) {
        gpio_output(state[i].pin);
    }
    serial_init();

    while (true) {
        target_id = serial_get_uint(digits);
        serial_put_str("ID recibido: \r");
        serial_put_int(target_id, digits);
        serial_put_str("\n\r");
        target_value = serial_get_uint(digits);
        serial_put_str("Valor recibido: \r");
        serial_put_int(target_value, digits);
        serial_put_str("\n\r");
        state[target_id].value = target_value;
        gpio_pin(state[target_id].pin, state[target_id].value);
    }
}



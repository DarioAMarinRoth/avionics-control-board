#include <stdint.h>
#include <avr/interrupt.h>

#include "gpio.h"
#include "buffer.h"
#include "models.h"
#include "serial.h"
#include "main.h"
#include "twi-master.h"

#define TRAMA_SIZE 3
#define OUTPUTS_SIZE 6
#define ENCODER_ID 35

uint8 trim = 0; // Variable para el encoder. Todavía no está implementado.

sid32 new_byte;
buffer_t rx_buf;
buffer_t tx_buf;

var_map outputs[] = {
    {13, 0},    // Luces de cabina
    {12, 0},    // Tren abajo 1
    {11, 0},    // Tren abajo 2
    {10, 0},    // Tren abajo 3
    {9, 0},     // Tren en tránsito
    {8, 0},     // Alternador
};

int main() {
    setup();
    uint8_t value;
    uint8_t id;

    while (1) {
        id = 0;
        for (uint8_t i = 0; i < TRAMA_SIZE; i++) {
            wait(new_byte);
            cli();
            unsigned char byte = buffer_get(&rx_buf);
            sei();
            if (byte >= '0' && byte <= '9') {
                id = id * 10 + (byte - '0');
            }
        }
        value = 0;
        for (uint8_t i = 0; i < TRAMA_SIZE; i++) {
            wait(new_byte);
            cli();
            unsigned char byte = buffer_get(&rx_buf);
            sei();
            if (byte >= '0' && byte <= '9') {
                value = value * 10 + (byte - '0');
            }
        }
        outputs[id].value = value;
    }
}

void get_inputs() {
    twi_master_init();
    while(1) {
        twi_master_receive_byte(DEFAULT_SLA);
        const uint8_t data_size = twi_get_received_data();
        uint8_t data;
        twi_master_receive_byte(DEFAULT_SLA);
        data = twi_get_received_data();
        for (int i = 0; i < data_size; ++i) {
            buffer_put(&tx_buf, data);
        }
        sleepms(500);
    }
}

void send_inputs() {
    char str[4]; // Máximo 3 dígitos (encoder) + carácter nulo
    while (1) {
        while (!buffer_is_empty(&tx_buf)) {
            f_to_string(str, buffer_get(&tx_buf));
            serial_put_str(str);
        }
        // f_to_string(str, ENCODER_ID + trim); // Info del encoder después de vaciar la cola
        // serial_put_str(str);
        sleepms(13);
    }
}

void set_outputs() {
    while (1) {
        for (int i = 0; i < OUTPUTS_SIZE; ++i) {
            gpio_pin(outputs[i].pin, outputs[i].value);
        }
        sleepms(13);
    }
}

void setup() {
    resume(create(set_outputs, 64 ,20,"led",0));
    resume(create(get_inputs, 64, 20, "i2c", 0));
    resume(create(send_inputs, 64, 20, "txs", 0));

    new_byte = semcreate(0);

    buffer_init(&rx_buf);
    buffer_init(&tx_buf);

    serial_init();
    buffer_put(&tx_buf, 0); // Solución momentánea para purgar el serial
    // twi_master_init();

    for (uint8_t i = 0; i < OUTPUTS_SIZE; i++) {
        gpio_output(outputs[i].pin);
    }
    gpio_input(2); // pulsador
}

void f_to_string(char *str, uint8_t num) {
    uint8_t len = 0;
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    uint8_t n = num;
    while (n > 0) {
        len++;
        n /= 10;
    }

    str[len] = '\0';
    while (num > 0) {
        str[--len] = (char) ('0' + (num % 10));
        num /= 10;
    }
}
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "gpio.h"
#include "buffer.h"
#include "models.h"
#include "serial.h"
#include "main.h"
#include "twi-master.h"

#define TRAMA_SIZE 3
#define OUTPUTS_SIZE 6
#define ENCODER_ID 35
#define ENCODER_SCALER 20
#define TRIM_MAX_VALUE 200
#define TRIM_START_VALUE (TRIM_MAX_VALUE/2)
#define N_START_VALUE (TRIM_START_VALUE * ENCODER_SCALER)
#define ENCODER_A 2
#define ENCODER_B 3

uint8 trim = TRIM_START_VALUE; // Valor de la variable del encoder.
uint16_t n = N_START_VALUE; // Contador del encoder.
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
        sleepms(13);
    }
}

void send_inputs() {
    uint8_t old_trim = TRIM_START_VALUE;
    char str[4]; // Máximo 3 dígitos (encoder) + carácter nulo
    while (1) {
        while (!buffer_is_empty(&tx_buf)) {
            f_to_string(str, buffer_get(&tx_buf));
            serial_put_str(str);
        }
        if (old_trim != trim) {
            f_to_string(str, ENCODER_ID + trim); // Info del encoder después de vaciar el buffer
            old_trim = trim;
            serial_put_str(str);
            serial_put_str("\n\r");
        }
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
    new_byte = semcreate(0);

    buffer_init(&rx_buf);
    buffer_init(&tx_buf);


    serial_init();
    twi_master_init();
    encoder_init();
    sei();

    for (uint8_t i = 0; i < OUTPUTS_SIZE; i++) {
        gpio_output(outputs[i].pin);
    }

    resume(create(set_outputs, 64 ,20,"led",0));
    resume(create(get_inputs, 64, 20, "i2c", 0));
    resume(create(send_inputs, 64, 20, "txs", 0));
}

void encoder_init() {
    gpio_input(ENCODER_A);
    gpio_input(ENCODER_B);
    gpio_pin(2, ON);
    gpio_pin(3, ON);
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);
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

ISR(INT0_vect) {
    uint8_t a = gpio_pin(ENCODER_A, GET);
    uint8_t b = gpio_pin(ENCODER_B, GET);
    if (a == b) {
        if (n < TRIM_MAX_VALUE * ENCODER_SCALER) {
            n = n + 1;
        }
    } else {
        if (n > 0) {
            n = n - 1;
        }
    }
    trim = n / ENCODER_SCALER;
}
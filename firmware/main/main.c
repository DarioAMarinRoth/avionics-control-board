#include <stdint.h>
#include <avr/interrupt.h>

#include "gpio.h"
#include "buffer.h"
#include "models.h"
#include "serial.h"
#include "main.h"
#include "my_queue.h"

#define TRAMA_SIZE 3
#define OUTPUTS_SIZE 2
#define ENCODER_ID 35

uint8 trim = 0; // Variable para el encoder. Todavía no está implementado.
uint8_t rx_word = 0;
sid32 new_byte;
sid32 new_word;
sid32 word_consumed;
buffer_t buf;
my_queue *changed_inputs;

// MODIFICAR LA MACRO OUTPUT_SIZE SI SE AGREGAN MÁS SALIDAS
var_map outputs[] = {
    {13, 0},
    {12, 0}
};

int main() {
    setup();
    while (1) {
        wait(word_consumed);
        for (uint8_t i = 0; i < TRAMA_SIZE; i++) {
            wait(new_byte);
            cli();
            char byte = buffer_get(&buf);
            sei();
            if (byte >= '0' && byte <= '9') {
                rx_word = rx_word * 10 + (byte - '0');
            }
        }
        signal(new_word);
    }
}

void get_inputs() {
    // Cuando esté implementado el i2c simplemente se encolan las modificaciones.
    uint8_t previous_value = 0;
    uint8_t current_value;
    while (1) {
        current_value = gpio_pin(2, GET);
        if (current_value != previous_value) {
            previous_value = current_value;
            f_push(changed_inputs, 0); // 0 es el id del pulsador. Es el valor que vendría del i2c.
        }
        sleepms(13);
    }
}

void send_inputs() {
    char str[4];    // Máximo 3 dígitos (encoder) + carácter nulo
    while (1) {
        while (!f_is_empty(changed_inputs)) {
            f_to_string(str, f_pop(changed_inputs));
            serial_put_str(str);
        }
        f_to_string(str, ENCODER_ID + trim); // Info del encoder después de vaciar la cola
        serial_put_str(str);
        sleepms(13);
    }
}

void update_outputs() {
    uint8_t id;
    while (1) {
        wait(new_word);
        id = rx_word;
        rx_word = 0;
        signal(word_consumed);
        wait(new_word);
        outputs[id].value = rx_word;
        rx_word = 0;
        signal(word_consumed);
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
    buffer_init(&buf);
    changed_inputs = f_create_queue();
    serial_init();

    for (uint8_t i = 0; i < OUTPUTS_SIZE; i++) {
        gpio_output(outputs[i].pin);
    }
    gpio_input(2); // pulsador

    word_consumed = semcreate(1);
    new_word = semcreate(0);
    new_byte = semcreate(0);

    resume(create(get_inputs, 64, 20, "i2c", 0));
    resume(create(send_inputs, 64, 20, "txs", 0));
    resume(create(set_outputs, 72, 20, "led", 0));
    resume(create(update_outputs, 96, 20, "rxs", 0));
    serial_put_str("\n\rSetup finalizado\n\r");
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
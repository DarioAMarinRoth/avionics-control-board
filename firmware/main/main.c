
#include <stdint.h>
#include <avr/interrupt.h>

#include "gpio.h"
#include "buffer.h"
#include "models.h"
#include "serial.h"
#include "main.h"

#define TRAMA_SIZE 3
#define OUTPUTS_SIZE 2
#define INPUTS_SIZE 1

sid32 new_word;
sid32 word_consumed;
sid32 new_byte;
buffer_t buf;

var_map outputs[] = {     // MODIFICAR LA MARCRO OUTPUT_SIZE SI SE AGREGAN MÁS SALIDAS
    {0, 13, 0},    
    {1, 12, 0}
};

var_map inputs[] = {     // MODIFICAR LA MARCRO INPUT_SIZE SI SE AGREGAN MÁS ENTRADAS
    {0, 2, 0},    
};

uint16_t result = 0;

void set_outputs() {
    while(1){
        for (int i = 0; i < OUTPUTS_SIZE; ++i) {
            gpio_pin(outputs[i].pin, outputs[i].value);
        }
        sleepms(13);
    }
}

void update_outputs() {
    uint16_t id;
    while(1) {
        wait(new_word);
        id = result;
        result = 0;
        signal(word_consumed);
        wait(new_word);
        outputs[id].value = result;
        result = 0;
        signal(word_consumed);
    }
}

void get_inputs() {
    while(1) {
        outputs[1].value = gpio_pin(inputs[0].pin, GET);
        sleepms(13);
    }
}

void init_board() {
    word_consumed = semcreate(1);
    new_word = semcreate(0);
    new_byte = semcreate(0);

    resume(create(set_outputs, 64 ,20,"led",0));
    resume(create(update_outputs, 64, 20, "rxs",0));
    resume(create(get_inputs, 64, 20, "i2c",0));

    buffer_init(&buf);
    serial_init();

    for (uint8_t i = 0; i < OUTPUTS_SIZE; i++) {
        gpio_output(outputs[i].pin);
    }
    
    for (uint8_t i = 0; i < INPUTS_SIZE; i++) {
        gpio_input(inputs[i].pin);
    }
}

int main() {
    init_board();

    while (1) {
        wait(word_consumed);
        for (uint8_t i = 0; i < TRAMA_SIZE ; i++) {
            wait(new_byte);
            cli();
            char byte = buffer_get(&buf);
            sei();
            if (byte >= '0' && byte <= '9') {
                result = result * 10 + (byte - '0');
            }
        }
        signal(new_word);
    }
}
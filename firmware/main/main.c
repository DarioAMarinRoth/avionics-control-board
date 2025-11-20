#include <xinu.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

#include "serial.h"
#include "gpio.h"
#include "my_queue.h"
#include "buffer.h"
#include "models.h"
#include "main.h"

#define TRAMA_SIZE 3
#define OUTPUTS_SIZE 2
#define INPUTS_SIZE 1

// Semáforos

sid32 new_word;
sid32 word_consumed;
sid32 new_byte;

// Variables

buffer_t buf;
my_queue *changed_inputs;

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
    uint8_t previous_value = 0;
    uint8_t current_value;
    while (1) {
        current_value = gpio_pin(2, GET);
        if (current_value != previous_value) {
            previous_value = current_value;
            f_push(changed_inputs, 0);  // 0 es el id de la entrada que cambio.
        }
        sleepms(13);
    }
}

void send_inputs() {
    char str[4];
    while (1) {
        while (!f_is_empty(changed_inputs)) {
            f_to_string(str, f_pop(changed_inputs));
            serial_put_str(str);
        }
        sleepms(13);
    }
}

void init_board() {
    // word_consumed = semcreate(1);
    // new_word = semcreate(0);
    // new_byte = semcreate(0);

    // resume(create(set_outputs, 64 ,20,"led",0));
    // resume(create(update_outputs, 64, 20, "rxs",0));
    resume(create(get_inputs, 64, 20, "i2c",0));
    resume(create(send_inputs, 128, 20, "txs",0));

    buffer_init(&buf);
    serial_init();
    changed_inputs = f_create_queue();

    for (uint8_t i = 0; i < OUTPUTS_SIZE; i++) {
        gpio_output(outputs[i].pin);
    }
    
    for (uint8_t i = 0; i < INPUTS_SIZE; i++) {
        gpio_input(inputs[i].pin);
    }
    serial_put_str("Inicialización completada\n\r");
}

int main() {
    init_board();

    while (1) {
        // wait(word_consumed);
        // for (uint8_t i = 0; i < TRAMA_SIZE ; i++) {
        //     wait(new_byte);
        //     cli();
        //     char byte = buffer_get(&buf);
        //     sei();
        //     if (byte >= '0' && byte <= '9') {
        //         result = result * 10 + (byte - '0');
        //     }
        // }
        // signal(new_word);
    }
    return 0;
}

void f_to_string(char* str, uint8_t num) {
    snprintf(str, 4, "%u", num);
}
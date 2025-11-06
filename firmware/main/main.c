#include <xinu.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>


#include "serial.h"
#include "gpio.h"
#include "buffer.h"

#define TRAMA_SIZE 3

sid32 produced;
sid32 consumed;
sid32 new_byte;
buffer_t buf;

uint16_t result = 0;

void dummy() {
    gpio_output(13);
    while(1){
        gpio_pin(13,ON);
        sleepms(500);
        gpio_pin(13,OFF);
        sleepms(500);
    }
}

void log_data() {
    while(1) {
        wait(produced);
        serial_put_str("Nueva información recibida\n\r");
        serial_put_int(result, 2);
        serial_put_str("\n\r");
        result = 0;
        signal(consumed);
    }
}


void main() {
    consumed = semcreate(1);
    produced = semcreate(0);
    new_byte = semcreate(0);
    buffer_init(&buf);

    serial_init();
    resume(create(dummy,256,20,"led",0));
    resume(create(log_data, 256, 20, "txd",0));
    
    while (1) {
        wait(consumed);
        for (uint8_t i = 0; i < TRAMA_SIZE ; i++) {
            wait(new_byte);
            cli();
            char byte = buffer_get(&buf);
            sei();
            if (byte >= '0' && byte <= '9') {
                result = result * 10 + (byte - '0');
            }
        }
        signal(produced);
    }
}
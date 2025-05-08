//
// Created by dario on 30/12/24.
//
#include <serial.h>
#include <matrix-keyboard.h>

int main(void) {
    serial_init();
    matrix_init();

    serial_put_str("Inicialización completada \n\r");

    while (1) {
        scan();
        queue* states = get_toggle_events();

        if (is_empty(states)) {
            continue;
        }

        serial_put_int(pop(states), 1);
        serial_put_str("\n\r");
    }
}

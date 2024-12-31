
#include <serial.h>
#include <matrix-keyboard.h>

int main(void) {
    serial_init();
    matrix_init();

    serial_put_str("Inicialización completada \n\r");

    while (1) {
        scan();
        uint8_t* state = get_inputs_state();

        for (int i = 0; i < N_INPUTS; i++) {
            serial_put_int(state[i], 1);
            serial_put_str(" ");
        }
        serial_put_str("\r");
    }
}

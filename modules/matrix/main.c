

#include "gpio.h"
#include "serial.h"

#define N_INPUTS 2      // Number of rows
#define N_OUTPUTS 2     // Number of columns

void enable_row(int row);
void disable_row(int row);
void print_matrix(int matrix[N_INPUTS][N_OUTPUTS]);

int main(void) {

    serial_init();

    int inputs[N_INPUTS] = {2, 3};
    int outputs[N_OUTPUTS] = {5, 6};
    int buttons[N_INPUTS][N_OUTPUTS] = {{0, 0},
                                        {0, 0}};

    for (int i = 0; i < N_INPUTS; ++i) {
        gpio_input(inputs[i]);
    }

    for (;;) {
        for (int i = 0; i < N_OUTPUTS; ++i) {
            enable_row(outputs[i]);
            for (int j = 0; j < N_INPUTS; ++j) {
                buttons[i][j] = gpio_pin(inputs[j], GET);
            }
            disable_row(outputs[i]);
        }
        print_matrix(buttons);    // Serial output
    }
}

void enable_row(int row) {
    gpio_output(row);
    gpio_pin(row, ON);
}

void disable_row(int row) {
    gpio_write(row, OFF);
    gpio_input(row);
}

void print_matrix(int matrix[N_OUTPUTS][N_INPUTS]) {
    for (int i = 0; i < N_OUTPUTS; ++i) {
        for (int j = 0; j < N_INPUTS; ++j) {
            serial_put_int(matrix[i][j], 1);
            serial_put_char(' ');
        }
        serial_put_str("\n\r");
    }
    serial_put_str("\n");
    serial_put_str("\n");
}

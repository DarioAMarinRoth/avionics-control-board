//
// Created by dario on 30/12/24.
//

#include "matrix-keyboard.h"
#include "gpio.h"
#include "serial.h"

// VARIABLES

uint8_t rows[N_ROWS] = ROWS;
uint8_t columns[N_COLUMNS] = COLUMNS;
uint8_t inputs_state[N_INPUTS];
my_queue *toggle_events;

// uint8_t matrix[N_ROWS][N_COLUMNS];

// FUNCTIONS

void matrix_init() {
    toggle_events = f_create_queue();

    for (int i = 0; i < N_INPUTS; i++) {
        inputs_state[i] = 0;    //TODO: CONFIG 0 para NC 1 para NA
    }

    for (int i = 0; i < N_ROWS; i++) {
        gpio_input(rows[i]);
        gpio_pin(rows[i], OFF);
    }

    for (int i = 0; i < N_COLUMNS; i++) {
        gpio_input(columns[i]);
        gpio_pin(columns[i], OFF);
    }
}

void scan() {
    for (int i = 0; i < N_ROWS; i++) {
        gpio_output(rows[i]);
        gpio_pin(rows[i], OFF);
        for (int j = 0; j < N_COLUMNS; j++) {
            gpio_pin(columns[j],ON);
            const uint8_t input_value = gpio_pin(columns[j], GET);
            gpio_pin(columns[j],OFF);
            const uint8_t input = get_button(i, j);
            // matrix[i][j] = input_value;
            if (input_value == inputs_state[input]) {
                continue;
            }
            f_add(toggle_events, input);
            inputs_state[input] = input_value;
        }
        gpio_input(rows[i]);
    }
}


my_queue *get_toggle_events() {
    return toggle_events;
}

uint8_t* get_inputs_state() {
    return inputs_state;
}

static uint8_t get_button(const int row, const int col) {
    return row * N_COLUMNS + col;
}
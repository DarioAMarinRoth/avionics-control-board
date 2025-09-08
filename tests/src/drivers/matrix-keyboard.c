//
// Created by dario on 30/12/24.
//

#include "matrix-keyboard.h"
#include "gpio.h"

// VARIABLES

uint8_t rows[N_ROWS] = ROWS;
uint8_t columns[N_COLUMNS] = COLUMNS;
uint8_t inputs_state[N_INPUTS];
my_queue *toggle_events;

// FUNCTIONS

void matrix_init() {
    toggle_events = f_create_queue();

    for (int i = 0; i < N_INPUTS; i++) {
        inputs_state[i] = 0;
    }

    for (int i = 0; i < N_ROWS; i++) {
        gpio_input(columns[i]);
    }
}

void scan() {
    for (int i = 0; i < N_ROWS; i++) {
        enable_row(rows[i]);
        for (int j = 0; j < N_COLUMNS; j++) {
            const uint8_t input = get_button(i, j);
            const uint8_t input_value = gpio_pin(columns[j], GET);

            if (input_value == inputs_state[input]) {
                continue;
            }
            f_add(toggle_events, input);
            inputs_state[input] = input_value;
        }
        disable_row(rows[i]);
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

static void enable_row(const int row) {
    gpio_output(row);
    gpio_pin(row, ON);
}

static void disable_row(const int row) {
    gpio_pin(row, OFF);
    gpio_input(row);
}

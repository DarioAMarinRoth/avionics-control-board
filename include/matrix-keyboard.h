//
// Created by dario on 30/12/24.
//


#ifndef MATRIX_KEYBOARD_H
#define MATRIX_KEYBOARD_H

#include <stdint.h>
#include <queue.h>

#define N_ROWS 2                        // outputs in the scan
#define N_COLUMNS 2                     // inputs in the scan
#define N_INPUTS (N_ROWS * N_COLUMNS)   // Total number of inputs
#define ROWS {5, 6}
#define COLUMNS {8, 9}

// FUNCTIONS

void matrix_init();

void scan();

queue* get_toggle_events();

uint8_t* get_inputs_state();

// STATIC FUNCTIONS

static void enable_row(int row);
static void disable_row(int row);
static uint8_t get_button(int row, int col);



#endif //MATRIX_KEYBOARD_H


//
// Created by dario on 8/14/25.
//
#include <stdint.h>

#ifndef MODELS_H
#define MODELS_H

typedef struct {
    uint8_t pin;
    uint8_t value;
} var_map;

void set_var_map_value(var_map *state, uint8_t size, uint8_t id, uint8_t value);

#endif //MODELS_H

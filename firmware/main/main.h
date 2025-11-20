#ifndef MAIN_H
#define MAIN_H

#include <xinu.h>

#include "buffer.h"

extern buffer_t buf;
extern sid32 new_byte;

void f_to_string(char* str, uint8_t num);

#endif
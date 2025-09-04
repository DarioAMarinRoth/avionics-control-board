//
// Created by dario on 9/4/25.
//

#include "misc.h"
#include <stdio.h>

char* to_string(uint8_t num) {
    static char str[4];
    snprintf(str, sizeof(str), "%u", num);
    return str;
}

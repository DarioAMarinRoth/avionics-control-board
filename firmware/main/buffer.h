
#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#define BUF_SIZE 28

typedef struct {
    char data[BUF_SIZE];
    int8_t get_index;
    uint8_t put_index;
    uint8_t n;      // Elementos presentes dentro del buffer
} buffer_t;

void buffer_init(buffer_t buf);
void buffer_put(buffer_t buf, char n);
char buffer_get(buffer_t buf);

#endif	/* BUFFER_H */

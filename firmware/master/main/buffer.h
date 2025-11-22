
#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#define BUF_SIZE 28

typedef struct {
    unsigned char data[BUF_SIZE];
    uint8_t get_index;
    uint8_t put_index;
    uint8_t n;      // Elementos presentes dentro del buffer
} buffer_t;

void buffer_init(buffer_t *buf);
void buffer_put(buffer_t *buf, unsigned char n);
unsigned char buffer_get(buffer_t *buf);
unsigned char buffer_is_empty(const buffer_t *buf);

#endif	/* BUFFER_H */

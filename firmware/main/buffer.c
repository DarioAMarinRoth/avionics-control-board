#include "buffer.h"

void buffer_init(buffer_t *buf) {
    buf->get_index = 0;
    buf->put_index = 0;
    buf->n = 0;
}

void buffer_put(buffer_t *buf, const unsigned char n) {

    if (buf->n == BUF_SIZE) {
        return;
    }

    buf->data[buf->put_index] = n;
    buf->n++;
    buf->put_index = (buf->put_index + 1) % BUF_SIZE;
}

unsigned char buffer_get(buffer_t *buf) {

    if (buf->n == 0) {
        return -1;
    }

    const unsigned char r = buf->data[buf->get_index];
    buf->n--;
    buf->get_index = (buf->get_index + 1) % BUF_SIZE;
    return r;
}

unsigned char buffer_is_empty(const buffer_t *buf) {
    return buf->n == 0;
}
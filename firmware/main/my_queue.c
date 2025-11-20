//
// Created by dario on 12/12/24.
//

#include "my_queue.h"
#include <stdlib.h>

#define NULL ((void *)0)

my_node *f_create_node(uint8_t data) {
    my_node *n = (my_node *) malloc(sizeof(my_node));
    n->data = data;
    n->next = NULL;
    return n;
}

void f_destroy_node(my_node *n) {
    n->next = NULL;
    free(n);
}

my_queue *f_create_queue(void) {
    my_queue *q = (my_queue *) malloc(sizeof(my_queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

uint8_t f_is_empty(my_queue *q) {
    return q->head == NULL;
}

void f_push(my_queue *q, uint8_t data) {
    my_node *n = f_create_node(data);
    if (f_is_empty(q)) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
}

uint8_t f_peek(my_queue *q) {
    if (f_is_empty(q)) {
        return -1;
    }
    return q->head->data;
}

uint8_t f_pop(my_queue *q) {
    if (f_is_empty(q)) {
        return -1;
    }
    my_node *n = q->head;
    uint8_t data = n->data;
    q->head = n->next;
    f_destroy_node(n);
    return data;
}

void f_destroy_queue(my_queue *q) {
    while (!f_is_empty(q)) {
        f_pop(q);
    }
    free(q);
}
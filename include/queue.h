//
// Created by dario on 12/12/24.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

typedef struct node {
    uint8_t data;
    struct node *next;
} node;

typedef struct queue {
    node *head;
    node *tail;
} queue;

node *create_node(uint8_t data);
void destroy_node(node *n);

queue *create_queue(void);
void enqueue(queue *q, uint8_t data);
int peek(queue *q);
int dequeue(queue *q);
int is_empty(queue *q);
void destroy_queue(queue *q);

#endif //QUEUE_H

//
// Created by dario on 12/12/24.
//

#include <queue.h>
#include <stdlib.h>

node *create_node(uint8_t data) {
    node *n = (node *) malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    return n;
}

void destroy_node(node *n) {
    n->next = NULL;
    free(n);
}

queue *create_queue(void) {
    queue *q = (queue *) malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

int is_empty(queue *q) {
    return q->head == NULL;
}

void enqueue(queue *q, uint8_t data) {
    node *n = create_node(data);
    if (is_empty(q)) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
}

int peek(queue *q) {
    if (is_empty(q)) {
        return -1;
    }
    return q->head->data;
}

int dequeue(queue *q) {
    if (is_empty(q)) {
        return -1;
    }
    node *n = q->head;
    int data = n->data;
    q->head = n->next;
    destroy_node(n);
    return data;
}

void destroy_queue(queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}
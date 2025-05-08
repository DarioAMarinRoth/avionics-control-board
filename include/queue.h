//
// Created by dario on 12/12/24.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

/**
 * \brief Estructura que representa un nodo en la cola.
 */
typedef struct node {
    uint8_t data;       /**< Dato almacenado en el nodo. */
    struct node *next;  /**< Puntero al siguiente nodo en la cola. */
} node;

/**
 * \brief Estructura que representa una cola.
 */
typedef struct queue {
    node *head; /**< Puntero al primer nodo de la cola. */
    node *tail; /**< Puntero al último nodo de la cola. */
} queue;

/**
 * \brief Crea un nuevo nodo con el dato especificado.
 * \param data Dato a almacenar en el nodo.
 * \return Puntero al nodo creado.
 */
node *create_node(uint8_t data);

/**
 * \brief Destruye un nodo.
 * \param n Puntero al nodo a destruir.
 */
void destroy_node(node *n);

/**
 * \brief Crea una nueva cola.
 * \return Puntero a la cola creada.
 */
queue *create_queue(void);

/**
 * \brief Añade un dato a la cola.
 * \param q Puntero a la cola.
 * \param data Dato a añadir a la cola.
 */
void push(queue *q, uint8_t data);

/**
 * \brief Obtiene el primer dato de la cola sin eliminarlo.
 * \param q Puntero a la cola.
 * \return El primer dato de la cola.
 */
int peek(queue *q);

/**
 * \brief Elimina y obtiene el primer dato de la cola.
 * \param q Puntero a la cola.
 * \return El primer dato de la cola.
 */
int pop(queue *q);

/**
 * \brief Verifica si la cola está vacía.
 * \param q Puntero a la cola.
 * \return 1 si la cola está vacía, 0 en caso contrario.
 */
int is_empty(queue *q);

/**
 * \brief Destruye una cola y libera la memoria asociada.
 * \param q Puntero a la cola a destruir.
 */
void destroy_queue(queue *q);

#endif //QUEUE_H
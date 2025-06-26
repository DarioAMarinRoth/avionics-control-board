//
// Created by dario on 12/12/24.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

/**
 * \brief Estructura que representa un nodo en la cola.
 */
typedef struct my_node {
    uint8_t data;       /**< Dato almacenado en el nodo. */
    struct my_node *next;  /**< Puntero al siguiente nodo en la cola. */
} my_node;

/**
 * \brief Estructura que representa una cola.
 */
typedef struct my_queue {
    my_node *head; /**< Puntero al primer nodo de la cola. */
    my_node *tail; /**< Puntero al último nodo de la cola. */
    uint8_t size; /**< Tamaño de la cola (número de nodos). */
} my_queue;

/**
 * \brief Crea un nuevo nodo con el dato especificado.
 * \param data Dato a almacenar en el nodo.
 * \return Puntero al nodo creado.
 */
my_node *f_create_node(uint8_t data);

/**
 * \brief Destruye un nodo.
 * \param n Puntero al nodo a destruir.
 */
void f_destroy_node(my_node *n);

/**
 * \brief Crea una nueva cola.
 * \return Puntero a la cola creada.
 */
my_queue *f_create_queue(void);

/**
 * \brief Añade un dato a la cola.
 * \param q Puntero a la cola.
 * \param data Dato a añadir a la cola.
 */
void f_push(my_queue *q, uint8_t data);

/**
 * \brief Obtiene el primer dato de la cola sin eliminarlo.
 * \param q Puntero a la cola.
 * \return El primer dato de la cola.
 */
int f_peek(my_queue *q);

/**
 * \brief Elimina y obtiene el primer dato de la cola.
 * \param q Puntero a la cola.
 * \return El primer dato de la cola.
 */
int f_pop(my_queue *q);

/**
 * \brief Verifica si la cola está vacía.
 * \param q Puntero a la cola.
 * \return 1 si la cola está vacía, 0 en caso contrario.
 */
int f_is_empty(my_queue *q);

/**
 * \brief Destruye una cola y libera la memoria asociada.
 * \param q Puntero a la cola a destruir.
 */
void f_destroy_queue(my_queue *q);

/**
 * \brief Obtiene el tamaño de la cola.
 * \param q Puntero a la cola.
 * \return El tamaño de la cola (número de nodos).
 */
uint8_t f_get_size(my_queue *q);

#endif //QUEUE_H
#ifndef MAIN_H
#define MAIN_H

#include <xinu.h>

#include "buffer.h"

/**
 * Buffer circular donde se almacenan los bytes recibidos por serial de la PC.
 */
extern buffer_t rx_buf;

extern sid32 new_byte;


void setup();

/**
 * Punto de entrada del programa.
 *
 * Tarea por semáforos: reconstruye los bytes recibidos por serial de la PC en una palabra.
 */
int main();


/**
 * Tarea periódica: lee los estados de las entradas y encola los ID de las entradas que hayan cambiado.
 */
void get_inputs();


/**
 * Tarea periódica: envía por serial a la PC los ID de las entradas que hayan cambiado y el valor del encoder.
 */
void send_inputs();


/**
 * Tarea por semáforos: actualiza el valor de las salidas según las palabras recibidas por serial de la PC.
 */
void update_outputs();

/**
 * Tarea periódica: aplica los valores de las salidas a los pines GPIO correspondientes.
 */
void set_outputs();

/**
 * Convierte un número entero sin signo a un string.
 * @param str Puntero al string donde se almacenará el número convertido.
 * @param num Número a convertir.
 */
void f_to_string(char *str, uint8_t num);


#endif

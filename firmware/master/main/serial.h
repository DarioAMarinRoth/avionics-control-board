/**********************************************************************
*
 * serial.h: interfaz del driver serial
 *
 **********************************************************************/

#include <stdint.h>
#include <avr/io.h>

#ifndef _SERIAL_H
#define _SERIAL_H

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE  (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#define RX_E (1 << RXEN0)		         /* Habilitar la recepción */
#define TX_E (1 << TXEN0)		         /* Habilitar la transmisión */
#define PARITY_MODE (0 << UPM00)	   /* No usar bit de paridad */
#define STOP_BITS (0 << USBS0)	     /* Usar 1 bit de stop */
#define CHAR_SIZE (3 << UCSZ00)	    /* Usar 8 bits de dato de E/S */
#define READY_TO_READ (1 << RXC0)   /* Dato listo para leer */
#define READY_TO_WRITE (1 << UDRE0) /* Búfer listo para escribir */
#define RX_INT_EN (1 << RXCIE0) /* Habilitar interrupción de recepción */

#define MAX_INT_DIGITS 5
#define MAX_LONG_DIGITS 10
#define MAX_DOUBLE_PRECISION 10

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

void serial_init(void);

void serial_put_char(char c);

char serial_get_char(void);

void serial_put_str(char *str);

char *serial_get_str(char *buffer, int max_string_length);

void serial_put_int(int v, int cant_digitos);

void serial_put_long_int(long int v, int cant_digitos);

void serial_put_double(double value, int int_digits, int frac_digits);

char serial_recibido(void);

uint16_t serial_get_uint(int digits);

#endif /* _SERIAL_H */
/**********************************************************************
 *
 * serial.h: interfaz del driver serial
 *
 **********************************************************************/

#include <stdint.h>


#ifndef _SERIAL_H
#define _SERIAL_H

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE  (((F_CPU/(USART_BAUDRATE*16UL)))-1)

/* UCSR0A - USART Control and Status Register A bits */
#define UCSR0A_MPCM0 0
#define UCSR0A_U2X0 1
#define UCSR0A_UPE0 2
#define UCSR0A_DOR0 3
#define UCSR0A_FE0 4
#define UCSR0A_UDRE0 5
#define UCSR0A_TXC0 6
#define UCSR0A_RXC0 7

/* UCSR0B - USART Control and Status Register B bits */
#define UCSR0B_TXB80 0
#define UCSR0B_RXB80 1
#define UCSR0B_UCSZ02 2
#define UCSR0B_TXEN0 3
#define UCSR0B_RXEN0 4
#define UCSR0B_UDRIE0 5
#define UCSR0B_TXCIE0 6
#define UCSR0B_RXCIE0 7

/* UCSR0C - USART Control and Status Register C bits */
#define UCSR0C_UCPOL0 0
#define UCSR0C_UCSZ00 1
#define UCSR0C_UCSZ01 2
#define UCSR0C_USBS0 3
#define UCSR0C_UPM00 4
#define UCSR0C_UPM01 5
#define UCSR0C_UMSEL00 6
#define UCSR0C_UMSEL01 7

#define RX_E (1 << UCSR0B_RXEN0)		   /* Habilitar la recepción */
#define TX_E (1 << UCSR0B_TXEN0)		   /* Habilitar la transmisión */
#define PARITY_MODE (0 << UCSR0C_UPM00)	   /* No usar bit de paridad */
#define STOP_BITS (0 << UCSR0C_USBS0)	   /* Usar 1 bit de stop */
#define CHAR_SIZE (3 << UCSR0C_UCSZ00)	   /* Usar 8 bits de dato de E/S */
#define READY_TO_READ (1 << UCSR0A_RXC0)   /* Dato listo para leer */
#define READY_TO_WRITE (1 << UCSR0A_UDRE0) /* Búfer listo para escribir */

#define MAX_INT_DIGITS 5
#define MAX_LONG_DIGITS 10
#define MAX_DOUBLE_PRECISION 10

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/* Estructura de datos overlay del USART del atmega328 */
typedef struct {
    uint8_t status_control_a; /* ucsr0a USART Control and Status A */
    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* reserved */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */;
    uint8_t baud_rate_h; /* ubrr0h baud rate high */
    uint8_t data_io; /* udr0 I/O data */
}volatile uart_t;

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

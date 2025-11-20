/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/
#include "serial.h"

/* Puntero a la estructura de los registros del periférico */
uart_t *serial_port = (uart_t *) (0xc0);

void serial_init(void) {
    /* Configurar los registros High y Low con BAUD_PRESCALE */
    serial_port->baud_rate_h = (unsigned char) (BAUD_PRESCALE >> 8);
    serial_port->baud_rate_l = (unsigned char) (BAUD_PRESCALE);

    /* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
    serial_port->status_control_c = CHAR_SIZE | STOP_BITS | PARITY_MODE;

    /* Activar la recepcion y transmicion */
    serial_port->status_control_b = RX_E | TX_E;

    // Interrupciones
    SREG |= (1 << SREG_I);  // Interrupciones globales
    serial_port->status_control_b |= (1 << RXCIE0); // Interrupciones de rx
}

void serial_put_char(char c) {
    while (!(serial_port->status_control_a & READY_TO_WRITE));
    serial_port->data_io = c;
}

char serial_get_char(void) {
    while (!((serial_port->status_control_a) & (READY_TO_READ)));
    return (serial_port->data_io);
}

void serial_put_str(char *str) {
    while (*str != '\0') {
        serial_put_char(*str);
        str++;
    }
    serial_put_char('\n');
}

char *serial_get_str(char *buffer, int max_string_length) {
    int i = 0;
    char c;

    for (int i = 0; i < max_string_length; ++i) {
        c = serial_get_char();
        buffer[i] = c;
    }

    return buffer;
}

void serial_put_long_int(long int value, int num_digits) {
    char buffer[MAX_LONG_DIGITS] = {0};
    int i = 0;

    if (value == 0) {
        return serial_put_char('0');
    } else if (value < 0) {
        serial_put_char('-');
        value = -value; // Usar valor absoluto
    }

    while (value != 0) {
        buffer[i] = value % 10;
        value /= 10;
        i++;
    }

    if (num_digits < 1 || num_digits > MAX_LONG_DIGITS)
        num_digits = i;

    for (int j = num_digits - 1; j > -1; j--)
        serial_put_char(48 + buffer[j]);
}

void serial_put_int(int value, int num_digits) {
    if (num_digits > MAX_INT_DIGITS)
        num_digits = MAX_INT_DIGITS;
    return serial_put_long_int(value, num_digits);
}

uint16_t serial_get_uint(int digits) {
    const int size = digits + 1; // +1 para el carácter nulo
    char buffer[size];
    uint16_t result = 0;

    serial_get_str(buffer, size);

    for (int j = 0; j < digits; j++) {
        if (buffer[j] >= '0' && buffer[j] <= '9') {
            result = result * 10 + (buffer[j] - '0');
        }
    }
    return result;
}

ISR(USART_RX_vect) {
    buffer_put(buf, serial_port->data_io);
}
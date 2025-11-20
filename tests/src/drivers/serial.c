/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include "serial.h"


void serial_init(void) {
    /* Configurar los registros High y Low con BAUD_PRESCALE */
    UBRR0H = (unsigned char) (BAUD_PRESCALE >> 8);
    UBRR0L = (unsigned char) (BAUD_PRESCALE);

    /* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
    UCSR0C = CHAR_SIZE | STOP_BITS | PARITY_MODE;

    /* Activar la recepcion y transmicion */
    UCSR0B = RX_E | TX_E;
}

void serial_put_char(char c) {
    while (!(UCSR0A & READY_TO_WRITE));
    UDR0 = c;
}

char serial_get_char(void) {
    while (!(UCSR0A & READY_TO_READ));
    return UDR0;
}

void serial_put_str(char *str) {
    while (*str != '\0') {
        serial_put_char(*str);
        str++;
    }
    serial_put_char('\n');
}

char *serial_get_str(char *buffer, int max_string_length) {
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

void serial_put_double(double value, int int_digits, int frac_digits) {
    long int int_value = (long int) value;
    double frac_value = value - int_value;
    int frac_digit = 0;

    serial_put_long_int(int_value, int_digits);
    serial_put_char('.');

    if (frac_digits > MAX_DOUBLE_PRECISION)
        frac_digits = MAX_DOUBLE_PRECISION;
    else if (frac_digits < 1)
        frac_digits = 1;

    if (frac_value < 0)
        frac_value = -frac_value;

    for (int i = 0; i < frac_digits; i++) {
        frac_value *= 10;
        frac_digit = (int) frac_value;
        serial_put_char(48 + (char) frac_value);
        frac_value -= frac_digit;
    }
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

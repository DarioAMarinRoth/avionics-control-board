//
// Created by dario on 8/9/25.
//

#ifndef PINMAP_32U4_H
#define PINMAP_32U4_H


#include <avr/iom32u4.h> // TODO: Teóricamente es innecesario. Borrar después

#include "gpio_map.h"

#define A0 18
#define A1 19
#define A2 20
#define A3 21
#define A4 22
#define A5 23
#define A6 4
#define A7 6
#define A8 9
#define A10 12

// pinout: https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/Pro_Micro_v13b.pdf
static const gpio_t pinmap[] = {
    { &DDRD, &PORTD, &PIND, 2 }, // D0
    { &DDRD, &PORTD, &PIND, 3 }, // D1
    { &DDRD, &PORTD, &PIND, 1 }, // D2
    { &DDRD, &PORTD, &PIND, 0 }, // D3
    { &DDRD, &PORTD, &PIND, 4 }, // D4/A6
    { &DDRC, &PORTC, &PINC, 6 }, // D5
    { &DDRD, &PORTD, &PIND, 7 }, // D6/A7
    { &DDRE, &PORTE, &PINE, 6 }, // D7
    { &DDRB, &PORTB, &PINB, 4 }, // D8
    { &DDRB, &PORTB, &PINB, 5 }, // D9/A8
    { &DDRB, &PORTB, &PINB, 6 }, // D10
    { &DDRB, &PORTB, &PINB, 7 }, // D11
    { &DDRD, &PORTD, &PIND, 6 }, // D12/A10
    { &DDRC, &PORTC, &PINC, 7 }, // D13
    { &DDRB, &PORTB, &PINB, 3 }, // D14
    { &DDRB, &PORTB, &PINB, 1 }, // D15
    { &DDRB, &PORTB, &PINB, 2 }, // D16
    { &DDRB, &PORTB, &PINB, 0 }, // D17
    { &DDRF, &PORTF, &PINF, 7 }, // A0
    { &DDRF, &PORTF, &PINF, 6 }, // A1
    { &DDRF, &PORTF, &PINF, 5 }, // A2
    { &DDRF, &PORTF, &PINF, 4 }, // A3
    { &DDRF, &PORTF, &PINF, 1 }, // A4
    { &DDRF, &PORTF, &PINF, 0 }, // A5
};

#endif //PINMAP_32U4_H
//
// Created by dario on 8/9/25.
//

#ifndef PINMAP_328P_H
#define PINMAP_328P_H

#include "gpio_map.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19
static const gpio_t pinmap[] PROGMEM = {
    { &DDRD, &PORTD, &PIND, 0 },
    { &DDRD, &PORTD, &PIND, 1 },
    { &DDRD, &PORTD, &PIND, 2 },
    { &DDRD, &PORTD, &PIND, 3 },
    { &DDRD, &PORTD, &PIND, 4 },
    { &DDRD, &PORTD, &PIND, 5 },
    { &DDRD, &PORTD, &PIND, 6 },
    { &DDRD, &PORTD, &PIND, 7 },
    { &DDRB, &PORTB, &PINB, 0 }, // D8
    { &DDRB, &PORTB, &PINB, 1 },
    { &DDRB, &PORTB, &PINB, 2 },
    { &DDRB, &PORTB, &PINB, 3 },
    { &DDRB, &PORTB, &PINB, 4 },
    { &DDRB, &PORTB, &PINB, 5 }, // D13
    { &DDRC, &PORTC, &PINC, 0 },
    { &DDRC, &PORTC, &PINC, 1 },
    { &DDRC, &PORTC, &PINC, 2 },
    { &DDRC, &PORTC, &PINC, 3 },
    { &DDRC, &PORTC, &PINC, 4 },
    { &DDRC, &PORTC, &PINC, 5 },
};

#endif //PINMAP_328P_H
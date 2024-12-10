//
// Created by dario on 09/12/24.
//

#ifndef TWI_COMMON_H
#define TWI_COMMON_H

#include <avr/io.h>
#include <stdint.h>

/**********************************************************************
 * MACROS
 **********************************************************************/

// CONSTANTES
#define DEFAULT_SLA 0x10   // Dirección del esclavo por defecto

// CONFIGURACIONES
#define ENABLE_TWI (1 << TWEN)  // Habilitar TWI
#define ENABLE_ACK (1 << TWEA)  // Habilitar ACK
#define GEN_START (1 << TWSTA)  // Generar condición de inicio
#define GEN_STOP (1 << TWSTO)   // Generar condición de parada
#define CLEAR_INT (1 << TWINT)  // Limpiar interrupción

// VARIOS
#define STATUS_REG_MASK 0xF8  // Máscara del registro de estado
#define I2C_TRANSMISSION_COMPLETE (twi->twcr & (1 << TWINT))  // Verificar si la transmisión I2C está completa

/**********************************************************************
 * ESTRUCTURA TWI
 **********************************************************************/

/**
 * @brief Estructura que representa los registros TWI.
 */
typedef struct {
    uint8_t twbr;
    uint8_t twsr;
    uint8_t twar;
    uint8_t twdr;
    uint8_t twcr;
    uint8_t twamr;
} volatile twi_t;

/**********************************************************************
 * DECLARACIONES DE FUNCIONES ESTÁTICAS
 **********************************************************************/

/**
 * @brief Obtiene el estado actual del TWI.
 *
 * @return El estado actual del TWI.
 */
static uint8_t get_status(void);

/**
 * @brief Transmite un byte de datos a través del TWI.
 *
 * @param data El byte de datos a transmitir.
 * @return El valor del registro de estados luego de la transmisión.
 */
static uint8_t transmit(uint8_t data);

#endif //TWI_COMMON_H
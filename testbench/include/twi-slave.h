//
// Created by dario on 09/12/24.
//

#ifndef TWI_SLAVE_H
#define TWI_SLAVE_H

#include <stdint.h>
#include "twi-common.h"

/**********************************************************************
 * TWI FUNCTIONS
 **********************************************************************/

/**
 * @brief Inicializa el esclavo TWI con la dirección especificada.
 *
 * @param sla Dirección del esclavo TWI.
 */
void twi_sla_slave_init(uint8_t sla);

/**
 * @brief Inicializa el esclavo TWI.
 */
void twi_slave_init();

/**
 * @brief Transmite un byte de datos desde el esclavo TWI.
 *
 * @param data Byte de datos a transmitir.
 * @return uint8_t Estado de la transmisión.
 */
uint8_t twi_slave_transmit(uint8_t data);

#endif //TWI_SLAVE_H
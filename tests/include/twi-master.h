//
// Created by dario on 09/12/24.
//

#ifndef TWI_MASTER_H
#define TWI_MASTER_H

#include <stdint.h>
#include "twi-common.h"


/**********************************************************************
 * MACROS
 **********************************************************************/

/**
 * @brief Frecuencia del procesador: 16 MHz.
 */
#define F_MASTER 16000000

/**
 * @brief Frecuencia de comunicación: 100 kHz.
 */
#define F_I2C 100000

/**
 * @brief Valor del prescaler: 1.
 */
#define PRESCALER_1 ((0 << TWPS1) | (0 << TWPS0))

/**
 * @brief Valor del prescaler: 4.
 */
#define PRESCALER_4 ((0 << TWPS1) | (1 << TWPS0))

/**
 * @brief Valor del prescaler: 16.
 */
#define PRESCALER_16 ((1 << TWPS1) | (0 << TWPS0))

/**
 * @brief Valor del prescaler: 64.
 */
#define PRESCALER_64 ((1 << TWPS1) | (1 << TWPS0))

/**
 * @brief Dirección de escritura del esclavo.
 *
 * @param address Dirección del esclavo.
 */
#define SLA_W(address) (address << 1)

/**
 * @brief Dirección de lectura del esclavo.
 *
 * @param address Dirección del esclavo.
 */
#define SLA_R(address) ((address << 1) | (1 << 0))

/**********************************************************************
 * STATIC FUNCTIONS DECLARATIONS
 **********************************************************************/

static void delay_us(int us);
static uint8_t twi_start(void);
static void twi_stop(void);
static void send_ACK(void);
static void send_NACK(void);

/**********************************************************************
 * TWI MASTER FUNCTIONS
 **********************************************************************/

/**
 * @brief Inicializa el maestro TWI.
 */
void twi_master_init();

/**
 * @brief Recibe un byte de datos desde un dispositivo esclavo TWI.
 *
 * @param tx_sla Dirección del dispositivo esclavo.
 * @return uint8_t Byte de datos recibido.
 */
uint8_t twi_master_receive_byte(const uint8_t tx_sla);

/**
 * @brief Obtiene el último byte de datos recibido.
 *
 * @return uint8_t Último byte de datos recibido.
 */
uint8_t twi_get_received_data();

#endif //TWI_MASTER_H
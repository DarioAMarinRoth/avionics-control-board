//
// Created by dario on 09/12/24.
//

#include <stdint.h>
#include <util/twi.h>
#include "twi-slave.h"

twi_t *twi_slave = (twi_t *) (0xB8);

/**********************************************************************
 * TWI FUNCTIONS
 **********************************************************************/

void twi_sla_slave_init(const uint8_t sla) {
    twi_slave->twar = sla << TWA0;
    twi_slave->twcr = ENABLE_TWI | ENABLE_ACK;
}

void twi_slave_init() {
    twi_sla_slave_init(DEFAULT_SLA);
}

uint8_t twi_slave_transmit(const uint8_t data) {
    while (!I2C_TRANSMISSION_COMPLETE)
        ;

    int status = get_status();
    if (status != TW_ST_SLA_ACK)
        return status;

    status = transmit(data);
    if (status != TW_ST_DATA_NACK)
        return status;

    twi_slave->twcr = CLEAR_INT | ENABLE_TWI | ENABLE_ACK;    // Slave last action
    return 0;
}

/**********************************************************************
 * STATIC FUNCTIONS DEFINITIONS
 **********************************************************************/

static uint8_t get_status(void) {
    return twi_slave->twsr & STATUS_REG_MASK;
}

static uint8_t transmit(const uint8_t data) {
    twi_slave->twdr = data;
    twi_slave->twcr = CLEAR_INT | ENABLE_TWI;
    while (!I2C_TRANSMISSION_COMPLETE)
        ;
    return get_status();
}
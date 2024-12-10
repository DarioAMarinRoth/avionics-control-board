//
// Created by dario on 09/12/24.
//

#include <stdint.h>
#include <util/twi.h>
#include <twi-slave.h>

twi_t *twi = (twi_t *) (0xB8);

/**********************************************************************
 * TWI FUNCTIONS
 **********************************************************************/

void sla_slave_init(const uint8_t sla) {
    twi->twar = sla << TWA0;
    twi->twcr = ENABLE_TWI | ENABLE_ACK;
}

void slave_init() {
    sla_slave_init(DEFAULT_SLA);
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

    twi->twcr = CLEAR_INT | ENABLE_TWI | ENABLE_ACK;    // Slave last action
    return 0;
}

/**********************************************************************
 * STATIC FUNCTIONS DEFINITIONS
 **********************************************************************/

static uint8_t get_status(void) {
    return twi->twsr & STATUS_REG_MASK;
}

static uint8_t transmit(const uint8_t data) {
    twi->twdr = data;
    twi->twcr = CLEAR_INT | ENABLE_TWI;
    while (!I2C_TRANSMISSION_COMPLETE)
        ;
    return get_status();
}
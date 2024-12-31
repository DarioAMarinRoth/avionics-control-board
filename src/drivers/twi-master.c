//
// Created by dario on 09/12/24.
//

#include <stdint.h>
#include <util/twi.h>
#include "twi-master.h"

twi_t *twi_master = (twi_t *) (0xB8);

/**********************************************************************
 * RECEIVED DATA STORAGE
 **********************************************************************/

uint8_t twi_received_byte;

uint8_t twi_get_received_data() {
    return twi_received_byte;
}

/**********************************************************************
 * TWI FUNCTIONS
 **********************************************************************/

void twi_master_init() {
    twi_master->twsr = PRESCALER_1;
    twi_master->twbr = ((F_MASTER / F_I2C) - 16) / 2;
    twi_master->twcr = ENABLE_TWI;
}

uint8_t twi_master_receive_byte(const uint8_t tx_sla) {
    uint8_t status = 0;

    do {
        status = twi_start();
        if (status != TW_START)
            return status;

        status = transmit(SLA_R(tx_sla));
        if (status == TW_MR_SLA_ACK)
            break;
        if (status == TW_MR_ARB_LOST)
            return status;
        if (status == TW_MR_SLA_NACK)
            twi_stop();
    } while (1);

    send_NACK();
    twi_received_byte = twi_master->twdr;
    twi_stop();
    return 0;
}

/**********************************************************************
 * STATIC FUNCTIONS DEFINITIONS
 **********************************************************************/

static void delay_us(int us) {
    while (us--) {
        asm volatile(
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t");
    }
}

static uint8_t get_status(void) {
    return twi_master->twsr & STATUS_REG_MASK;
}

static uint8_t twi_start(void) {
    delay_us(10);
    twi_master->twcr = CLEAR_INT | GEN_START | ENABLE_TWI;
    while (!I2C_TRANSMISSION_COMPLETE)
        ;
    return get_status();
}

static void twi_stop(void) {
    twi_master->twcr = GEN_STOP | CLEAR_INT | ENABLE_TWI;
}

static uint8_t transmit(const uint8_t data) {
    twi_master->twdr = data;
    twi_master->twcr = CLEAR_INT | ENABLE_TWI;
    while (!I2C_TRANSMISSION_COMPLETE)
        ;
    return get_status();
}

static void send_ACK() {
    twi_master->twcr = CLEAR_INT | ENABLE_TWI | ENABLE_ACK;
    while (!I2C_TRANSMISSION_COMPLETE)
        ;
}

static void send_NACK() {
    twi_master->twcr = CLEAR_INT | ENABLE_TWI;
    while (!I2C_TRANSMISSION_COMPLETE)
        ;
}
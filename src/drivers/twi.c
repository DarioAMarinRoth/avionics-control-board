/**********************************************************************
 *
 * TWI (I²C) Atmega328p Driver
 *
 **********************************************************************/

#include <avr/io.h>
#include <stdint.h>

// CONSTANTS
#define F_MASTER 16000000  // FRECUENCIA DEL PROCESADOR: 16 MHz
#define F_I2C 100000       // FRECUENCIA DE COMUNICACIÓN: 100 kHz
#define DEFAULT_SLA 0x10   // DIRECCIÓN DEL ESCLAVO POR DEFECTO

// PRESCALER VALUES
#define PRESCALER_1 ((0 << TWPS1) | (0 << TWPS0))
#define PRESCALER_4 ((0 << TWPS1) | (1 << TWPS0))
#define PRESCALER_16 ((1 << TWPS1) | (0 << TWPS0))
#define PRESCALER_64 ((1 << TWPS1) | (1 << TWPS0))

// SETTINGS
#define SLA_W(address) (address << 1)
#define SLA_R(address) ((address << 1) | (1 << 0))
#define ENABLE_TWI (1 << TWEN)
#define ENABLE_ACK (1 << TWEA)
#define GEN_START (1 << TWSTA)
#define GEN_STOP (1 << TWSTO)
#define CLEAR_INT (1 << TWINT)

// MISC
#define STATUS_REG_MASK 0xF8

/**********************************************************************
 * STATUS CODES
 **********************************************************************/

// Status Codes from datasheet
#define START_CONDITION_TRANSMITTED 0x08
#define SLA_W_TRANSMITTED_ACK_RECEIVED 0x18
#define SLA_W_TRANSMITTED_NO_ACK_RECEIVED 0x20
#define ARBITRATION_LOST 0x38
#define SLA_R_TRANSMITTED_ACK_RECEIVED 0x40
#define SLA_R_TRANSMITTED_NO_ACK_RECEIVED 0x48
#define SLA_R_RECEIVED_ACK_TRANSMITTED 0XA8
#define I2C_TRANSMISSION_COMPLETE (twi->twcr & (1 << TWINT))

/**********************************************************************
 * TWI STRUCTURE
 **********************************************************************/

typedef struct {
  	uint8_t twbr;   // TWI Bit Rate Register
  	uint8_t twsr;   // TWI Status Register
  	uint8_t twar;   // TWI (Slave) Address Register
  	uint8_t twdr;   // TWI Data Register
  	uint8_t twcr;   // TWI Control Register
  	uint8_t twamr;  // TWI (Slave) Address Mask Register
} 	volatile twi_t;

twi_t *twi = (twi_t *)(0xB8);

/**********************************************************************
 * RECEIVED DATA STORAGE (MR MODE)
 **********************************************************************/

uint8_t twi_received_byte;

uint8_t get_received_data() { return twi_received_byte; }

/**********************************************************************
 * TWI FUNCTIONS
 **********************************************************************/

// Return Status Code
enum twi_status {
  	SUCCESS = 0,
  	ERR_START_FAILED = 1,
  	ERR_ARBITRATION_LOST = 2,
  	ERR_NO_ACK = 3,
  	ERR_MEMORY_ALLOCATION_FAILED = 4,
};

static uint8_t get_status(void) { return twi->twsr & STATUS_REG_MASK; }

void master_init(void) {
  	twi->twsr = PRESCALER_1;
  	twi->twbr = ((F_MASTER / F_I2C) - 16) / 2;
  	twi->twcr = ENABLE_TWI;
}

void sla_slave_init(const uint8_t sla) {
  	twi->twar = sla << TWA0;
  	twi->twcr = ENABLE_TWI | ENABLE_ACK;
}

void slave_init() { sla_slave_init(DEFAULT_SLA); }

static uint8_t twi_start(void) {
  	twi->twcr = CLEAR_INT | GEN_START | ENABLE_TWI;

  	while (!I2C_TRANSMISSION_COMPLETE)
    	;
  	return get_status();
}

static void twi_stop(void) {
	twi->twcr = GEN_STOP | CLEAR_INT | ENABLE_TWI;
}

static uint8_t transmit(const uint8_t data) {
	twi->twdr = data;
  	twi->twcr = CLEAR_INT | ENABLE_TWI;
  	while (!I2C_TRANSMISSION_COMPLETE)
          ;
  	return get_status();
}

static void send_ACK() {
  	twi->twcr = CLEAR_INT | ENABLE_TWI | ENABLE_ACK;
  	while (!I2C_TRANSMISSION_COMPLETE)
          ;
}

static void send_NACK() {
  	twi->twcr = CLEAR_INT | ENABLE_TWI;
  	while (!I2C_TRANSMISSION_COMPLETE);
}

uint8_t twi_master_receive_byte(const uint8_t tx_sla) {
  	uint8_t status = 0;
  	status = twi_start();
  	if (status != START_CONDITION_TRANSMITTED) {
    	return ERR_START_FAILED;
  	}

  	status = transmit(SLA_R(tx_sla));
  	if (status == ARBITRATION_LOST) {
    	return ERR_ARBITRATION_LOST;
  	}

  	if (status == SLA_R_TRANSMITTED_NO_ACK_RECEIVED) {
    	twi_stop();
    	return ERR_NO_ACK;
  	}
  	send_NACK();
  	twi_received_byte = twi->twdr;
  	twi_stop();
  	status = get_status();
  	return SUCCESS;
}

uint8_t twi_slave_transmit(const uint8_t data) {
  	uint8_t status = 0;
  	while (!I2C_TRANSMISSION_COMPLETE)
          ;
  	status = get_status();
  	if (status != SLA_R_RECEIVED_ACK_TRANSMITTED) {
    	return ERR_START_FAILED;
  	}
  	status = transmit(data);
  	return SUCCESS;
}
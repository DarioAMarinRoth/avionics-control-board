/**********************************************************************
 *
 * TWI (I²C) Atmega328p Driver
 *
 **********************************************************************/

#include <avr/io.h>
#include <stdint.h>
#include <serial.h>

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
#define DATA_RECEIVED_ACK_TRANSMITTED 0x50
#define DATA_RECEIVED_NO_ACK_TRANSMITTED 0x58
#define NO_RELEVANT_INFO 0xF8
#define I2C_TRANSMISSION_COMPLETE (twi->twcr & (1 << TWINT))

/**********************************************************************
 * TWI STRUCTURE
 **********************************************************************/

typedef struct {
    uint8_t twbr; // TWI Bit Rate Register
    uint8_t twsr; // TWI Status Register
    uint8_t twar; // TWI (Slave) Address Register
    uint8_t twdr; // TWI Data Register
    uint8_t twcr; // TWI Control Register
    uint8_t twamr; // TWI (Slave) Address Mask Register
} volatile twi_t;

twi_t *twi = (twi_t *) (0xB8);

/**********************************************************************
 * RECEIVED DATA STORAGE (MR MODE)
 **********************************************************************/

uint8_t twi_received_byte;

uint8_t get_received_data() { return twi_received_byte; }

/**********************************************************************
 * LOGGER
 **********************************************************************/

int8_t twi_logger_enabled = 0;

// Return Status Code
enum twi_status {
    SUCCESS = 0,
    ERR_START_FAILED = 1,
    ERR_ARBITRATION_LOST = 2,
    ERR_NO_ACK = 3,
};

static void twi_logger_init() {
    serial_init();
    twi_logger_enabled = 1;
}

static void log_message(char *message) {
    if (!twi_logger_enabled) {
        return;
    }
    serial_put_str(message);
    serial_put_str("\n\r");
}

static void log_start_communication() {
    log_message("");
    log_message("**********************************************************");
    log_message("RUTINA DE RECEPCIÓN INICIADA");
    log_message("");
}

static void log_end_communication() {
    log_message("");
    log_message("COMUNICACIÓN FINALIZADA");
    log_message("**********************************************************");
    log_message("");
}

static void log_status(uint8_t status) {
    if (!twi_logger_enabled) {
        return;
    }
    switch (status) {
        case START_CONDITION_TRANSMITTED:
            log_message("STATUS: Condición de START transmitida");
            break;
        case SLA_W_TRANSMITTED_ACK_RECEIVED:
            log_message("STATUS: SLA+W transmitida y ACK recibido");
            break;
        case SLA_W_TRANSMITTED_NO_ACK_RECEIVED:
            log_message("STATUS: SLA+W transmitida y NO ACK recibido");
            break;
        case SLA_R_TRANSMITTED_ACK_RECEIVED:
            log_message("STATUS: SLA+R transmitida y ACK recibido");
            break;
        case SLA_R_TRANSMITTED_NO_ACK_RECEIVED:
            log_message("STATUS: SLA+R transmitida y NO ACK recibido");
            break;
        case ARBITRATION_LOST:
            log_message("STATUS: Pérdida de arbitraje");
            break;
        case DATA_RECEIVED_ACK_TRANSMITTED:
            log_message("STATUS: Datos recibidos y ACK transmitido");
            break;
        case DATA_RECEIVED_NO_ACK_TRANSMITTED:
            log_message("STATUS: Datos recibidos y NO ACK transmitido");
            break;
        case NO_RELEVANT_INFO:
            log_message("STATUS: No hay información relevante. El bit TWINT está en 0");
            break;
        case ERR_START_FAILED:
            log_message("ERROR: Fallo al enviar condición de START");
            break;
        case ERR_NO_ACK:
            log_message("ERROR: No se recibió ACK");
            break;
        default:
            serial_put_str("WARNING: Código de estado desconocido: ");
            serial_put_int(status, 3);
            log_message("");
    }
}

/**********************************************************************
 * TWI FUNCTIONS
 **********************************************************************/

static uint8_t get_status(void) { return twi->twsr & STATUS_REG_MASK; }

void master_init(int logs) {
    if (logs)
        twi_logger_init();

    log_message("INFO: Inicializando TWI en modo maestro");
    twi->twsr = PRESCALER_1;
    twi->twbr = ((F_MASTER / F_I2C) - 16) / 2;
    twi->twcr = ENABLE_TWI;
    log_message("INFO: Inicialización completada");
}

void sla_slave_init(const uint8_t sla) {
    log_message("INFO: Inicializando TWI en modo esclavo");
    twi->twar = sla << TWA0;
    twi->twcr = ENABLE_TWI | ENABLE_ACK;
    log_message("INFO: Inicialización completada");
}

void slave_init() { sla_slave_init(DEFAULT_SLA); }

static uint8_t twi_start(void) {
    log_message("INFO: Enviando condición de START");
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
    while (!I2C_TRANSMISSION_COMPLETE);
}

static void send_NACK() {
    log_message("INFO: Enviando NACK");
    twi->twcr = CLEAR_INT | ENABLE_TWI;
    while (!I2C_TRANSMISSION_COMPLETE);
}

uint8_t twi_master_receive_byte(const uint8_t tx_sla) {

    log_start_communication();

    uint8_t status = 0;
    status = twi_start();
    log_status(status);
    if (status != START_CONDITION_TRANSMITTED) {
        log_message("INFO: interrumpiendo transmisión");
        log_end_communication();
        return ERR_START_FAILED;
    }

    log_message("INFO: enviando dirección del esclavo y bit de lectura");
    status = transmit(SLA_R(tx_sla));
    log_status(status);
    if (status == ARBITRATION_LOST) {
        log_message("INFO: interrumpiendo transmisión");
        twi_stop();
        log_end_communication();
        return ERR_ARBITRATION_LOST;
    }

    if (status == SLA_R_TRANSMITTED_NO_ACK_RECEIVED) {
        log_message("INFO: interrumpiendo transmisión");
        twi_stop();
        log_end_communication();
        return ERR_NO_ACK;
    }

    send_NACK();
    log_status(get_status());
    twi_received_byte = twi->twdr;
    twi_stop();
    log_end_communication();
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
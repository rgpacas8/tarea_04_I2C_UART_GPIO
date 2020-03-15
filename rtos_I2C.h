/*
 * rtos_I2C.h
 *
 *  Created on: 14 mar. 2020
 *      Author: David / Pacas
 */

#ifndef RTOS_I2C_H_
#define RTOS_I2C_H_

#include <stdint.h>

#define NUMBER_OF_I2C_PORTS 4	/* For the I2C0, I2C1, I2C2 e I2C3 */

typedef enum {
	rtos_i2c_portA, rtos_i2c_portB, rtos_i2c_portC,
	rtos_i2c_portD, rtos_i2c_portE
} rtos_i2c_port_t;

typedef enum {I2C_0,  I2C_1,  I2C_2,  I2C_3} i2c_channel_t;
typedef enum {Slave_mode,       Master_mode} master_or_slave_mode_t;
typedef enum {I2C_RX_mode,      I2C_TX_mode} transmit_mode_t;
typedef enum {Acknowledge,     Nacknowledge} ack_or_nack_t;
typedef enum {rtos_I2C_sucess,rtos_I2C_fail} rtos_I2C_flag_t;

typedef struct
{
	uint32_t baud_rate;
	i2c_channel_t I2C_number;
	rtos_i2c_port_t port;
	uint8_t sda_pin;
	uint8_t scl_pin;
	uint8_t pin_mux;

	master_or_slave_mode_t master_or_slave;
	transmit_mode_t mode;

} rtos_I2C_config_t;

rtos_I2C_flag_t rtos_i2c_init(rtos_I2C_config_t config);


/* It is recommended to use pin 2 and 3 of GPIOB. */
void rtos_I2C_init(rtos_I2C_config_t config);

void rtos_I2C_write_byte(i2c_channel_t i2c_number, uint8_t *buffer,
		uint16_t lenght, uint8_t slaveAddress, uint8_t subaddressSize);

uint8_t  rtos_I2C_read_byte(void);

#endif /* RTOS_I2C_H_ */

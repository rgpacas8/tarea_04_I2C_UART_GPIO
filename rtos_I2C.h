/*
 * rtos_I2C.h
 *
 *  Created on: 14 mar. 2020
 *      Author: David / Pacas
 */

#ifndef RTOS_I2C_H_
#define RTOS_I2C_H_

#include <stdint.h>

#define NUMBER_OF_I2C_CHANNELS 4	/* For the I2C0, I2C1, I2C2 e I2C3 */

typedef enum {
	rtos_i2c_portA, rtos_i2c_portB, rtos_i2c_portC,
	rtos_i2c_portD, rtos_i2c_portE
} rtos_I2C_port_t;

typedef enum {rtos_I2C_0,rtos_I2C_1,rtos_I2C_2,rtos_I2C_3} rtos_I2C_channel_t;
typedef enum {rtos_Slave_mode,           rtos_Master_mode} master_or_slave_mode_t;
typedef enum {rtos_I2C_RX_mode,          rtos_I2C_TX_mode} transmit_mode_t;
typedef enum {rtos_Acknowledge,         rtos_Nacknowledge} ack_or_nack_t;
typedef enum {rtos_I2C_sucess,               rtos_I2C_fail} rtos_I2C_flag_t;

typedef struct
{
	uint32_t baud_rate;
	rtos_I2C_channel_t I2C_number;
	rtos_I2C_port_t port;
	uint8_t sda_pin;
	uint8_t scl_pin;
	uint8_t pin_mux;

	master_or_slave_mode_t master_or_slave;
	transmit_mode_t mode;

} rtos_I2C_config_t;

rtos_I2C_flag_t rtos_i2c_init(rtos_I2C_config_t config);


/* It is recommended to use pin 2 and 3 of GPIOB. */
void rtos_I2C_init(rtos_I2C_config_t config);

void rtos_I2C_write_byte(rtos_I2C_channel_t i2c_number, uint8_t *buffer,
		uint16_t lenght, uint8_t slaveAddress, uint8_t subaddressSize);

uint8_t  rtos_I2C_read_byte(void);

#endif /* RTOS_I2C_H_ */

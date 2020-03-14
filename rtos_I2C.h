/*
 * rtos_I2C.h
 *
 *  Created on: 14 mar. 2020
 *      Author: pacas
 */

#ifndef RTOS_I2C_H_
#define RTOS_I2C_H_

#include <stdint.h>
#define NUMBER_OF_I2C_PORTS 3
typedef enum {I2C_0, I2C_1, I2C_2, I2C_3} i2c_channel_t;
typedef enum {Slave_mode, Master_mode} master_or_slave_mode_t;
typedef enum {I2C_RX_mode, I2C_TX_mode} transmit_mode_t;
typedef enum {Acknowledge, Nacknowledge} ack_or_nack_t;
typedef enum {rtos_I2C_sucess,I2C_uart_fail} rtos_I2C_flag_t;

typedef struct
{
	uint32_t  baudrate;
	i2c_channel_t I2c_number;
	master_or_slave_mode_t master_or_slave;
	transmit_mode_t mode;
}rtos_I2C_config_t;

rtos_I2C_flag_t rtos_i2c_init(rtos_I2C_config_t config);

#endif /* RTOS_I2C_H_ */

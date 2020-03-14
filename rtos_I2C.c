/*
 * rtos_I2C.c
 *
 *  Created on: 14 mar. 2020
 *      Author: pacas
 */
#include "rtos_I2C.h"

#include "fsl_I2C.h"
#include "fsl_clock.h"
#include "fsl_port.h"

#include "FreeRTOS.h"
#include "semphr.h"

#define BAUD_RATE (9600U)
static rtos_I2C_handle_t uart_handles[NUMBER_OF_I2C_PORTS] = {0};

rtos_I2C_flag_t rtos_i2c_init(rtos_I2C_config_t config){
	rtos_I2C_flag_t retval = I2C_uart_fail;
	i2c_master_config_t config;
	if(config.I2c_number < NUMBER_OF_I2C_PORTS){

	}
}


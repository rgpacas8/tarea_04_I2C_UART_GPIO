/*
 * rtos_I2C.c
 *
 *  Created on: 14 mar. 2020
 *      Author: David / Pacas
 */

#include "rtos_I2C.h"

#include "fsl_I2C.h"
#include "fsl_clock.h"
#include "fsl_port.h"

#include "FreeRTOS.h"
#include "semphr.h"

				// se usa master_handle_t o slave_handle_t ?
static void fsl_i2c_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData);
static inline void enable_port_clock(rtos_I2C_port_t port);
static inline I2C_Type * get_i2c_base(rtos_I2C_channel_t I2C_channel);
static inline PORT_Type* get_port_base(rtos_I2C_port_t port);

typedef struct
{
	uint8_t is_init;
	i2c_master_handle_t fsl_I2C_handle;
	SemaphoreHandle_t mutex_I2c;
	SemaphoreHandle_t I2C_sem;
} rtos_I2C_handle_t;

static rtos_I2C_handle_t I2C_handles[NUMBER_OF_I2C_CHANNELS] = { 0 };















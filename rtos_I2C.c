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

static void fsl_I2C_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if (kStatus_I2C_Idle == status) {
		if(I2C0==base){
			xSemaphoreGiveFromISR(I2C_handles[rtos_I2C_0].I2C_sem, &xHigherPriorityTaskWoken);
		}
		if(I2C1==base){
			xSemaphoreGiveFromISR(I2C_handles[rtos_I2C_1].I2C_sem, &xHigherPriorityTaskWoken);
		}
		if(I2C2==base){
			xSemaphoreGiveFromISR(I2C_handles[rtos_I2C_2].I2C_sem, &xHigherPriorityTaskWoken);
		}
		if(I2C3==base){
			xSemaphoreGiveFromISR(I2C_handles[rtos_I2C_3].I2C_sem, &xHigherPriorityTaskWoken);
		}

	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void rtos_I2C_init(rtos_I2C_config_t config)
{
	i2c_master_config_t fsl_config;

	if(config.I2C_number < NUMBER_OF_I2C_CHANNELS)
	{
		if(!I2C_handles[config.I2C_number].is_init){
			I2C_handles[config.I2C_number].mutex_I2c=xSemaphoreCreateMutex();
			I2C_handles[config.I2C_number].I2C_sem = xSemaphoreCreateBinary();
			enable_port_clock(config.port);
			PORT_SetPinMux(get_port_base(config.port), config.scl_pin,config.pin_mux);
			PORT_SetPinMux(get_port_base(config.port), config.sda_pin,config.pin_mux);
			I2C_MasterGetDefaultConfig(&fsl_config);
			fsl_config.baudRate_Bps = config.baud_rate;
		if(rtos_I2C_0==config.I2C_number){
			I2C_MasterInit(get_port_base(config.), masterConfig, srcClock_Hz)
		}
		}
	}
}












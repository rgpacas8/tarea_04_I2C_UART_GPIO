/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 */

/*
 * @file:			Drivers with FreeRTOS.c
 * @brief:   		Tarea4_UART_I2C_GPIO_in_FreeRTOS_OS_for_FRDM-K66F
 *
 * @company:			  ITESO
 * @Engineer Team:	 D.F.R. / R.G.P.
 * @contact:		ie717807@iteso.mx
 * @contact:		ie706818@iteso.mx
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */
#include "FreeRTOS.h"
#include "task.h"
#include "rtos_uart.h"
#include "rtos_I2C.h"

/* TODO: insert other definitions and declarations here. */


/* TODO: insert the prototypes of functions here. */
void uart_echo_task(void *args);
void I2C_write_task(void *args);

int main(void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	PRINTF("Hello World\n");

	/* xTaskCreate uses:
	 * 		- Pointer to the function that implements the task.
	 * 		- Text name for the task.  This is to facilitate debugging only.
	 * 		- Stack depth - most small microcontrollers will use much less stack than this.
	 * 		- Task parameter, Pasamos una cadena de texto para DEBUG
	 *
	 * 		- Priority
	 * 		- We are not using the task handle.
	 * 		*/

//	xTaskCreate(uart_echo_task, "uart_echo_task", 110, NULL,	// ok!
//			configMAX_PRIORITIES, NULL);						// ok!

	xTaskCreate(I2C_write_task, "I2C_write_task",  110, NULL,
			configMAX_PRIORITIES, NULL);

	vTaskStartScheduler();

	while (1) {
		/* Your Application never comes here :) */
		__asm volatile ("nop");
	}
	return 0;
}



/* TODO: insert the body (implementation) of the functions here. */


void uart_echo_task(void *args)
{
	rtos_uart_config_t config;
	config.baudrate = 115200;
	config.rx_pin = 16;
	config.tx_pin = 17;
	config.pin_mux = kPORT_MuxAlt3;
	config.uart_number = rtos_uart0;
	config.port = rtos_uart_portB;
	rtos_uart_init(config);
	uint8_t data;

	for (;;) {
		rtos_uart_receive(rtos_uart0, &data, 1);
		rtos_uart_send(rtos_uart0, &data, 1);
	}
}

void I2C_write_task(void *args)
{
	rtos_I2C_config_t config;
//	config.baud_rate = 100000; /* Standard mode: 100k bit/s */
	config.scl_pin = 2; /* PTB2 - SCL */
	config.sda_pin = 3; /* PTB3 - SDA */
	config.pin_mux = kPORT_MuxAlt2; /* ALT2 Consult Pinout K66F y Signal Multiplexing */
	config.I2C_number = rtos_I2C0;	/* I2C0 */
	config.port = rtos_i2c_portB;	/* PTB	*/

	config.master_or_slave = rtos_Master_mode; /* Doesn't use */
	config.mode = rtos_I2C_WRITE_mode;  	   /* Doesn't use */

	rtos_I2C_init(config);
	uint8_t dataToWrite   = 0x0A;	/* Random value */
	uint8_t slaveAddress  = 0x50;	/* 1010 + 000 = 101 0000 */
	uint16_t writeAddress = 0x0000;	/* Memory location to write */

	for (;;) {
		rtos_I2C_write_byte(rtos_I2C0, &dataToWrite, 1, slaveAddress,
				writeAddress, 2);
	}
}

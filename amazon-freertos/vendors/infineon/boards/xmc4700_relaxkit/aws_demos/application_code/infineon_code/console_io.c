/* 
 * Copyright (C) 2021 Infineon Technologies AG.
 *
 * Licensed under the EVAL_XMC47_PREDMAIN_AA Evaluation Software License
 * Agreement V1.0 (the "License"); you may not use this file except in
 * compliance with the License.
 *
 * For receiving a copy of the License, please refer to:
 *
 * https://github.com/Infineon/pred-main-xmc4700-kit/LICENSE.txt
 *
 * Licensee acknowledges that the Licensed Items are provided by Licensor free
 * of charge. Accordingly, without prejudice to Section 9 of the License, the
 * Licensed Items provided by Licensor under this Agreement are provided "AS IS"
 * without any warranty or liability of any kind and Licensor hereby expressly
 * disclaims any warranties or representations, whether express, implied,
 * statutory or otherwise, including but not limited to warranties of
 * workmanship, merchantability, fitness for a particular purpose, defects in
 * the Licensed Items, or non-infringement of third parties' intellectual
 * property rights.
 *
 */

#include <stdio.h>

#include "console_io.h"

#include "xmc_uart.h"
#include "xmc_gpio.h"


#define CONSOLE_IO_UART_BAUDRATE 			115200

#define CONSOLE_IO_DEBUG_USB_HEADER 		1

#if defined( CONSOLE_IO_X2_HEADER )
/* UART log to X2 pin header */
	#define CONSOLE_IO_UART_CH 				XMC_UART2_CH1
	#define CONSOLE_IO_UART_TX_PIN 			P3_11
	#define CONSOLE_IO_UART_TX_PIN_AF 		P3_11_AF_U2C1_DOUT0
	#define CONSOLE_IO_UART_RX_PIN 			P3_12
	#define CONSOLE_IO_UART_INPUT 			USIC2_C1_DX0_P3_12
#elif defined( CONSOLE_IO_DEBUG_USB_HEADER )
/* Debug USB - UART log */
	#define CONSOLE_IO_UART_CH 				XMC_UART0_CH0
	#define CONSOLE_IO_UART_TX_PIN 			P1_5
	#define CONSOLE_IO_UART_TX_PIN_AF 		P1_5_AF_U0C0_DOUT0
	#define CONSOLE_IO_UART_RX_PIN 			P1_4
	#define CONSOLE_IO_UART_INPUT 			USIC0_C0_DX0_P1_4
#else
/* mBus header pins UART */
	#define CONSOLE_IO_UART_CH				XMC_UART1_CH0
	#define CONSOLE_IO_UART_TX_PIN			P2_14
	#define CONSOLE_IO_UART_TX_PIN_AF		P2_14_AF_U1C0_DOUT0
	#define CONSOLE_IO_UART_RX_PIN			P2_15
	#define CONSOLE_IO_UART_INPUT			USIC1_C0_DX0_P2_15
#endif


static const XMC_UART_CH_CONFIG_t uart_config =
{
	.baudrate = CONSOLE_IO_UART_BAUDRATE,
	.data_bits = 8,
	.stop_bits = 1,
};


int _write( int fd, const void *buf, size_t count )
{
	( void )fd;

	for( int i = 0; i < count; ++i )
	{
	XMC_UART_CH_Transmit( CONSOLE_IO_UART_CH, *(const uint8_t *)buf );
	buf++;
	}
	return count;
}


int _read( int fd, void *buf, size_t count )
{
	int char_cnt = 0;
	(void)fd;

	while( ( XMC_UART_CH_GetStatusFlag( CONSOLE_IO_UART_CH ) & ( XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION | XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION ) ) == 0 );

	char_cnt++;
	*(uint8_t *)buf = XMC_UART_CH_GetReceivedData( CONSOLE_IO_UART_CH );

	XMC_UART_CH_ClearStatusFlag( CONSOLE_IO_UART_CH, XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
												XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION );

	return char_cnt;
}


void _putchar( char c )
{
	XMC_UART_CH_Transmit( CONSOLE_IO_UART_CH, c );
}


void CONSOLE_IO_vInit( void )
{
	XMC_UART_CH_Init( CONSOLE_IO_UART_CH, &uart_config );

	XMC_GPIO_SetMode( CONSOLE_IO_UART_RX_PIN, XMC_GPIO_MODE_INPUT_PULL_UP );
	XMC_UART_CH_SetInputSource( CONSOLE_IO_UART_CH, XMC_UART_CH_INPUT_RXD, CONSOLE_IO_UART_INPUT );

	XMC_UART_CH_Start (CONSOLE_IO_UART_CH );

	XMC_GPIO_SetMode( CONSOLE_IO_UART_TX_PIN, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | CONSOLE_IO_UART_TX_PIN_AF );
}

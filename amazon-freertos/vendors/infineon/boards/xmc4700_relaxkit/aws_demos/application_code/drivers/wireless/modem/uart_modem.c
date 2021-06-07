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

#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"

#include "xmc_gpio.h"
#include "xmc_dma.h"
#include "xmc_uart.h"
#include "xmc_scu.h"

#include "uart_modem.h"
#include "aws_nbiot_config.h"

#if NBIOT_ENABLED

typedef struct {
    uint8_t           ucRxBuf[UART_MODEM_RX_BUFFER_SIZE];   /* RX buffer, DMA copy values into this buffer          */
	uint16_t          ulRxBufIndexRd;			   	        /* Last readed item by user 					    	*/
	uint16_t          ulRxBufIndexWr;			            /* Last written item by DMA 				        	*/
} UartModemCxt_t __attribute__ ((aligned (16)));


static volatile  UartModemCxt_t xUartModemCxt =
{
	.ulRxBufIndexRd		= 0,
	.ulRxBufIndexWr		= 0,
};


/*
 * @brief Custom UART Receive interrupt handler. By default generated function is not weak, so for redefining this function you need to follow instructions below
 */
#warning "In case of regenerating DAVE APPs you need to add __WEAK attribute for UART_lReceiveHandler function (DAVE/GENERATED/UART/uart.c line 96)"
void UART_lReceiveHandler(const UART_t * const handle)
{
    if( xUartModemCxt.ulRxBufIndexWr == UART_MODEM_RX_BUFFER_SIZE )
    {
        xUartModemCxt.ulRxBufIndexWr = 0;
    }
    xUartModemCxt.ucRxBuf[xUartModemCxt.ulRxBufIndexWr] = (uint8_t)XMC_UART_CH_GetReceivedData(handle->channel);
    xUartModemCxt.ulRxBufIndexWr++;
}


/*
 * @brief Custom UART initialization.
 */
void UART_MODEM_vInit( void )
{
    /* Enable receive events to start data receiving */
    XMC_USIC_CH_EnableEvent(UART_MODEM_INSTANCE.channel, (uint32_t)((uint32_t)XMC_USIC_CH_EVENT_STANDARD_RECEIVE | (uint32_t)XMC_USIC_CH_EVENT_ALTERNATIVE_RECEIVE));
}

/*
 * @brief Check if UART is transmitting
 */
bool UART_MODEM_bTxIsBusy( void )
{
    return UART_MODEM_INSTANCE.runtime->tx_busy;
}


/*
 * @brief Copy data to buffer and then send in background
 *
 * @param[in]  uint8_t* Pointer to data
 * @param[in]  uint16_t Total bytes to be transmitted.
 *
 */
int32_t UART_MODEM_lTransmitData( uint8_t *pucData, uint16_t usLength )
{
	if( usLength > UART_MODEM_TX_BUFFER_SIZE )
	{
		return -1;
	}

	if( UART_MODEM_bTxIsBusy())
	{
		return -1;
	}

    if ( UART_Transmit(&UART_MODEM_INSTANCE, pucData, usLength) != UART_STATUS_SUCCESS )
    {
        return -1;
    }

    return 0;
}


bool UART_MODEM_bRxDataAvaliable( void )
{
	return ( xUartModemCxt.ulRxBufIndexRd != xUartModemCxt.ulRxBufIndexWr ? true : false );
}


uint16_t UART_MODEM_usRxDataCount( void )
{
	uint16_t rx_len = 0;

	if( UART_MODEM_bRxDataAvaliable() )
	{
		if( xUartModemCxt.ulRxBufIndexRd < xUartModemCxt.ulRxBufIndexWr )
		{
			rx_len = xUartModemCxt.ulRxBufIndexWr - xUartModemCxt.ulRxBufIndexRd;
		}
		else
		{
			rx_len = UART_MODEM_RX_BUFFER_SIZE - xUartModemCxt.ulRxBufIndexRd + xUartModemCxt.ulRxBufIndexWr;
		}
	}

	return rx_len;
}


uint16_t UART_MODEM_usReceiveData( uint8_t *pucData, uint16_t usLength )
{
	uint16_t rx_len = 0;

	if( UART_MODEM_bRxDataAvaliable() )
	{
		if( xUartModemCxt.ulRxBufIndexRd < xUartModemCxt.ulRxBufIndexWr )
		{
			rx_len = xUartModemCxt.ulRxBufIndexWr - xUartModemCxt.ulRxBufIndexRd;
			if( rx_len > usLength )
			{
				rx_len = usLength;
			}
		    memcpy( pucData, (const void*)&xUartModemCxt.ucRxBuf[xUartModemCxt.ulRxBufIndexRd], rx_len );
		    xUartModemCxt.ulRxBufIndexRd += rx_len;
		}
		else
		{
			rx_len = UART_MODEM_RX_BUFFER_SIZE - xUartModemCxt.ulRxBufIndexRd;

			/* check overhead */
			if( rx_len > usLength )
			{
				rx_len = usLength;
				memcpy( pucData, (const void*)&xUartModemCxt.ucRxBuf[xUartModemCxt.ulRxBufIndexRd], rx_len );
				xUartModemCxt.ulRxBufIndexRd += rx_len;
			}
			else
			{
				/* copy data until end of buffer */
				memcpy( pucData, (const void*)&xUartModemCxt.ucRxBuf[xUartModemCxt.ulRxBufIndexRd], rx_len );

				/* copy data until current position on top of buffer */
				uint16_t len_to_copy = xUartModemCxt.ulRxBufIndexWr;

				/* check overhead */
				if( len_to_copy > usLength - rx_len )
				{
					len_to_copy = usLength - rx_len;
				}
				memcpy( (pucData + rx_len), (const void*)&xUartModemCxt.ucRxBuf[0], len_to_copy ); /* Process input data in linear buffer phase */
				rx_len += len_to_copy;
				xUartModemCxt.ulRxBufIndexRd = len_to_copy;
			}
		}
	}

	return rx_len;
}

/**
 * UART_MODEM End of Transmission callback
 */
void UART_MODEM_EoT_cb(void)
{

}

/**
 * UART_MODEM End of Receive callback
 */
void UART_MODEM_EoR_cb(void)
{

}

#endif // #if NBIOT_ENABLED


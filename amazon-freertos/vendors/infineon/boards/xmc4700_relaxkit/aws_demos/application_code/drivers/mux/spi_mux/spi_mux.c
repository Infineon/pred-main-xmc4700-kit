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

#include "spi_mux.h"

#include "DAVE.h"


static volatile SpiMux_t xSpiMuxCxt;

/* APP SPI_MASTER semaphores used in callback's */
SemaphoreHandle_t xSpiRxSemaphore;
SemaphoreHandle_t xSpiTxSemaphore;


static void SPI_MUX_prvSetCsLow( void )
{
    switch( xSpiMuxCxt.xType )
    {
    	case SPI_MUX_TYPE_LTC:
			DIGITAL_IO_SetOutputLow( &LTC_CS );
			break;
        case SPI_MUX_TYPE_DPS368_1:
            DIGITAL_IO_SetOutputLow( &DPS368_CS1 );
            break;
        case SPI_MUX_TYPE_DPS368_2:
            DIGITAL_IO_SetOutputLow( &DPS368_CS2 );
            break;
        case SPI_MUX_TYPE_DPS368_3:
            DIGITAL_IO_SetOutputLow( &DPS368_CS3 );
            break;
        case SPI_MUX_TYPE_WIFI:
            DIGITAL_IO_SetOutputLow( &ISM_CS );
            break;
        default: 
            break;
    }

}


static void SPI_MUX_prvSetCsHigh( void )
{
    switch( xSpiMuxCxt.xType )
    {
    	case SPI_MUX_TYPE_LTC:
			DIGITAL_IO_SetOutputHigh( &LTC_CS );
			break;
        case SPI_MUX_TYPE_DPS368_1:
            DIGITAL_IO_SetOutputHigh( &DPS368_CS1 );
            break;
        case SPI_MUX_TYPE_DPS368_2:
            DIGITAL_IO_SetOutputHigh( &DPS368_CS2 );
            break;
        case SPI_MUX_TYPE_DPS368_3:
            DIGITAL_IO_SetOutputHigh( &DPS368_CS3 );
            break;
        case SPI_MUX_TYPE_WIFI:
            DIGITAL_IO_SetOutputHigh( &ISM_CS );
            break;
        default:
            break;
    }

}


bool SPI_MUX_bInit( void )
{
    bool bRet = false;

    if( xSpiRxSemaphore == NULL )
	{
		xSpiRxSemaphore = xSemaphoreCreateBinary();
	}
	if( xSpiTxSemaphore == NULL )
	{
		xSpiTxSemaphore = xSemaphoreCreateBinary();
	}


    if( !xSpiMuxCxt.xSemaphore )
    {
//        xSpiMuxCxt.xSemaphore = xSemaphoreCreateBinary();
        xSpiMuxCxt.xSemaphore = xSemaphoreCreateRecursiveMutex();
    }

    if( xSpiMuxCxt.xSemaphore )
    {
//        xSemaphoreGive( xSpiMuxCxt.xSemaphore );
        xSemaphoreGiveRecursive( xSpiMuxCxt.xSemaphore );

        xSpiMuxCxt.bSpiInited = true;
        xSpiMuxCxt.xType = SPI_MUX_TYPE_UNKNOWN;

        bRet = true;
    }
    else
    {
        configPRINTF( ("ERROR: SPI Semaphore Create Binary\r\n") );
    }

    return bRet;
}


bool SPI_MUX_bSpecificInit( SpiMuxType_t xMuxType, SpiMuxCb_t xTxCb, SpiMuxCb_t xRxCb )
{
    if( xMuxType >= SPI_MUX_TYPE_MAX ) 
    {
        return false;
    }

    xSpiMuxCxt.pxCh[xMuxType].xTxCb = xTxCb;
    xSpiMuxCxt.pxCh[xMuxType].xRxCb = xRxCb;

    xSpiMuxCxt.pxCh[xMuxType].bInited = true;

    return true;
}


bool SPI_MUX_bSpecificDeinit( SpiMuxType_t xMuxType )
{
    if( xMuxType >= SPI_MUX_TYPE_MAX ) 
    {
        return false;
    }

    xSpiMuxCxt.pxCh[xMuxType].xTxCb = NULL;
    xSpiMuxCxt.pxCh[xMuxType].xRxCb = NULL;

    xSpiMuxCxt.pxCh[xMuxType].bInited = false;

    return true;
}


bool SPI_MUX_bCpolSet( SpiMuxType_t xMuxType, uint8_t ucClockPolarity )
{
    if( xMuxType >= SPI_MUX_TYPE_MAX) 
    {
        return false;
    }
    xSpiMuxCxt.pxCh[xMuxType].ucCpol = ucClockPolarity;
 
    return true;
}


/*
 * Auto set chip select to low
 * return true if acquire is successful
 */
bool SPI_MUX_bAcquire( SpiMuxType_t xMuxType, uint32_t ulTimeout )
{
    bool bRet = false;

    if( ( xMuxType >= SPI_MUX_TYPE_MAX ) || ( xSpiMuxCxt.pxCh[xMuxType].bInited != true ) )
    {
        return false;
    }


//    bRet = xSemaphoreTake( xSpiMuxCxt.xSemaphore, ( TickType_t ) ulTimeout );
    bRet = xSemaphoreTakeRecursive( xSpiMuxCxt.xSemaphore, ( TickType_t ) ulTimeout );
    if( bRet )
    {

        /* Configure the clock polarity and clock delay */
        XMC_SPI_CH_ConfigureShiftClockOutput( SPI_MASTER_0.channel,
                xSpiMuxCxt.pxCh[xMuxType].ucCpol ? XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED : XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_ENABLED,
                                             XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);

		if( xSpiMuxCxt.xType != xMuxType )
		{
			xSpiMuxCxt.xType = xMuxType;
			SPI_MUX_prvSetCsLow();
		}

    }

    return bRet;
}


/*
 * Auto set chip select to high
 */
bool SPI_MUX_bRelease( SpiMuxType_t xMuxType )
{

    bool bRet = false;

	if( xMuxType >= SPI_MUX_TYPE_MAX )
	{
		return false;
	}

	SPI_MUX_prvSetCsHigh();

    xSpiMuxCxt.xType = SPI_MUX_TYPE_UNKNOWN;

//    bRet = xSemaphoreGive( xSpiMuxCxt.xSemaphore );
	bRet = xSemaphoreGiveRecursive( xSpiMuxCxt.xSemaphore );

    return bRet;
}


static bool SPI_MUX_prvAvailable( void )
{
	return uxSemaphoreGetCount( xSpiMuxCxt.xSemaphore ) ? true : false;
}


int8_t SPI_MUX_cWait( uint32_t ulTimeout )
{
	uint32_t ulTickStart = xTaskGetTickCount();
	while( !SPI_MUX_prvAvailable() )
	{
		if( ( xTaskGetTickCount() - ulTickStart ) > ulTimeout )
		{
			return -1;
		}
	}

	return 0;
}


bool SPI_MUX_bTransmit( uint8_t *pucTransmitData, uint32_t ulCountBytesTransmit )
{
    SPI_MASTER_STATUS_t SPI_MASTER_xStatus = SPI_MASTER_Transmit( &SPI_MASTER_0, pucTransmitData, ulCountBytesTransmit );
    if( SPI_MASTER_xStatus != SPI_MASTER_STATUS_SUCCESS ) 
    { 
        return false;
    }

    return true;
}


bool SPI_MUX_bReceive( uint8_t *pucReceiveData, uint32_t ulCountBytesReceive )
{
    SPI_MASTER_STATUS_t SPI_MASTER_xStatus = SPI_MASTER_Receive( &SPI_MASTER_0, pucReceiveData, ulCountBytesReceive );
    if( SPI_MASTER_xStatus != SPI_MASTER_STATUS_SUCCESS) 
    {
        return false;
    }
    
    return true;
}


bool SPI_MUX_bTransfer( uint8_t *pucTransmitData, uint8_t *pucReceiveData, uint32_t ulCountBytesTransfer )
{
    SPI_MASTER_STATUS_t SPI_MASTER_xStatus = SPI_MASTER_Transfer( &SPI_MASTER_0, pucTransmitData, pucReceiveData, ulCountBytesTransfer );
    if( SPI_MASTER_xStatus != SPI_MASTER_STATUS_SUCCESS ) 
    { 
        return false;
    }
   
    return true;
}


bool SPI_MUX_bIsRxBusy( void )
{
    return SPI_MASTER_IsRxBusy( &SPI_MASTER_0 );
}


bool SPI_MUX_bIsTxBusy( void )
{
    return SPI_MASTER_IsTxBusy( &SPI_MASTER_0 );
}


void SPI_MUX_vEndTransmitCb( void )
{
    if( !xSpiMuxCxt.xType ) 
    {
        return;
    }

    if( ( xSpiMuxCxt.xType ) && ( xSpiMuxCxt.pxCh[xSpiMuxCxt.xType].xTxCb ) )
    {
        xSpiMuxCxt.pxCh[xSpiMuxCxt.xType].xTxCb();
    }
}


void SPI_MUX_vEndReceiveCb( void )
{
    if( !xSpiMuxCxt.xType ) 
    {
        return;
    }

    if( ( xSpiMuxCxt.xType ) && ( xSpiMuxCxt.pxCh[xSpiMuxCxt.xType].xRxCb ) )
    {
        xSpiMuxCxt.pxCh[xSpiMuxCxt.xType].xRxCb();
    }
}





void on_end_spi_transmit( void )
{
  static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  xSemaphoreGiveFromISR( xSpiTxSemaphore, &xHigherPriorityTaskWoken );

  if( xHigherPriorityTaskWoken == pdTRUE ) 
  {
	  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
  }

}


void on_end_spi_receive(void)
{
  static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  xSemaphoreGiveFromISR( xSpiRxSemaphore, &xHigherPriorityTaskWoken );

  if( xHigherPriorityTaskWoken == pdTRUE ) 
  {
	  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
  }

}

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

#include "i2c_mux.h"

#include "DAVE.h"


static volatile I2cMux_t xI2cMuxCxt;

static void I2C_MUX_prvError( void );


bool I2C_MUX_bInit( void )
{
	bool bRet = false;

    if( !xI2cMuxCxt.xSemaphore )
    {
        xI2cMuxCxt.xSemaphore = xSemaphoreCreateBinary();
    }

    if( xI2cMuxCxt.xSemaphore )
    {
        xSemaphoreGive( xI2cMuxCxt.xSemaphore );
        xI2cMuxCxt.bI2cInited = true;
        xI2cMuxCxt.xType = I2C_MUX_TYPE_UNKNOWN;

        bRet = true;
    }
    else
    {
        configPRINTF( ("ERROR: I2C Semaphore Create Binary\r\n") );
    }

    return bRet;
}


bool I2C_MUX_bSpecificInit( I2cMuxType_t xMuxType, I2cMuxCb_t xTxCb, I2cMuxCb_t xRxCb, I2cMuxCb_t xErrorCb, I2cMuxCb_t xNackCb, I2cMuxCb_t xArbitLostCb )
{
    if( xMuxType >= I2C_MUX_TYPE_MAX )
    {
    	return false;
    }

    xI2cMuxCxt.pxCh[xMuxType].xTxCb = xTxCb;
    xI2cMuxCxt.pxCh[xMuxType].xRxCb = xRxCb;
    xI2cMuxCxt.pxCh[xMuxType].xErrorCb = xErrorCb;
    xI2cMuxCxt.pxCh[xMuxType].xNackCb = xNackCb;
    xI2cMuxCxt.pxCh[xMuxType].xArbitLostCb = xArbitLostCb;

    xI2cMuxCxt.pxCh[xMuxType].bInited = true;

    return true;
}


bool I2C_MUX_bSpecificDeinit( I2cMuxType_t xMuxType )
{
    if( xMuxType >= I2C_MUX_TYPE_MAX )
    {
    	return false;
    }

    xI2cMuxCxt.pxCh[xMuxType].xTxCb = NULL;
    xI2cMuxCxt.pxCh[xMuxType].xRxCb = NULL;
    xI2cMuxCxt.pxCh[xMuxType].xErrorCb = NULL;
    xI2cMuxCxt.pxCh[xMuxType].xNackCb = NULL;
    xI2cMuxCxt.pxCh[xMuxType].xArbitLostCb = NULL;

    xI2cMuxCxt.pxCh[xMuxType].bInited = false;

    return true;
}

/*
 * return true if acquire is successful
 */
bool I2C_MUX_bAcquire( I2cMuxType_t xMuxType, uint32_t ulTimeout )
{
	bool bRet = false;

    if( ( xMuxType >= I2C_MUX_TYPE_MAX ) || ( xI2cMuxCxt.pxCh[xMuxType].bInited != true ) )
    {
    	return false;
    }


    if( xMuxType == I2C_MUX_TYPE_OPTIGA )
    {
    	 BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    	 bRet = xSemaphoreTakeFromISR( xI2cMuxCxt.xSemaphore, &xHigherPriorityTaskWoken );
    }
    else
    {
    	bRet = xSemaphoreTake( xI2cMuxCxt.xSemaphore, ( TickType_t ) ulTimeout );
    }

    if( bRet )
    {
        xI2cMuxCxt.xType = xMuxType;
        xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].bNack = false;
    }

   return bRet;
}


bool I2C_MUX_bRelease( I2cMuxType_t xMuxType )
{

	if( xMuxType >= I2C_MUX_TYPE_MAX )
	{
		return false;
	}

	if( xMuxType == I2C_MUX_TYPE_OPTIGA )
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xI2cMuxCxt.xSemaphore, &xHigherPriorityTaskWoken);
	}
	else
	{
		xSemaphoreGive( xI2cMuxCxt.xSemaphore );
	}

    xI2cMuxCxt.xType = I2C_MUX_TYPE_UNKNOWN;

    return true;
}


static bool I2C_MUX_bAvailable( void )
{
	return uxSemaphoreGetCount( xI2cMuxCxt.xSemaphore ) ? true : false;
}


int8_t I2C_MUX_cWait( uint32_t ulTimeout )
{
	uint32_t ulTickStart = xTaskGetTickCount();
	while( !I2C_MUX_bAvailable() )
	{
		if( ( xTaskGetTickCount() - ulTickStart ) > ulTimeout )
		{
			return -1;
		}
	}

	return 0;
}


bool I2C_MUX_bReceive( bool bSendStart, const uint32_t ulSlaveAddress, uint8_t *pucReceiveData, const uint32_t ulCountBytesReceive, bool bSendStop, bool bSendNack )
{
    xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].bNack = false;

    I2C_MASTER_STATUS_t I2C_MASTER_xStatus = I2C_MASTER_Receive( &I2C_MASTER_0, bSendStart, ulSlaveAddress, pucReceiveData, ulCountBytesReceive, bSendStop, bSendNack );
    if( I2C_MASTER_xStatus != I2C_MASTER_STATUS_SUCCESS )
    {
    	return false;
    }

    return true;
}


bool I2C_MUX_bTransmit( bool bSendStart, const uint32_t ulSlaveAddress, uint8_t *pucTransmitData, const uint32_t ulCountBytesTransmit, bool bSendStop )
{
    xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].bNack = false;

    I2C_MASTER_STATUS_t I2C_MASTER_xStatus = I2C_MASTER_Transmit( &I2C_MASTER_0, bSendStart, ulSlaveAddress, pucTransmitData, ulCountBytesTransmit, bSendStop );
    if( I2C_MASTER_xStatus != I2C_MASTER_STATUS_SUCCESS )
    {
    	return false;
    }

    return true;
}


bool I2C_MUX_bIsRxBusy( void )
{
    return I2C_MASTER_IsRxBusy( &I2C_MASTER_0 );
}


bool I2C_MUX_bIsTxBusy( void )
{
    return I2C_MASTER_IsTxBusy( &I2C_MASTER_0 );
}


bool I2C_MUX_bIsNack( void )
{
    return xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].bNack;
}


void I2C_MUX_vNackReceivedCb( void )
{
	I2C_MUX_prvError();
    if( !xI2cMuxCxt.xType )
    {
    	return;
    }
    xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].bNack = true;
    if( ( xI2cMuxCxt.xType ) && ( xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xNackCb ) )
    {
        xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xNackCb();
    }
}


void I2C_MUX_vArbitrationLostCb( void )
{
	I2C_MUX_prvError();
    if( !xI2cMuxCxt.xType )
    {
    	return;
    }
    if( ( xI2cMuxCxt.xType ) && ( xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xArbitLostCb ) )
    {
        xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xArbitLostCb();
    }
}


void I2C_MUX_vErrorDetectedCb( void )
{
	I2C_MUX_prvError();
    if( !xI2cMuxCxt.xType )
    {
    	return;
    }
    if( ( xI2cMuxCxt.xType ) && ( xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xErrorCb ) )
    {
        xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xErrorCb();
    }
}


void I2C_MUX_vEndTransmitCb( void )
{
    if( !xI2cMuxCxt.xType )
    {
    	return;
    }
    if( ( xI2cMuxCxt.xType ) && ( xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xTxCb ) )
    {
        xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xTxCb();
    }
}


void I2C_MUX_vEndReceiveCb( void )
{
    if( !xI2cMuxCxt.xType )
    {
    	return;
    }
    if( ( xI2cMuxCxt.xType ) && ( xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xRxCb ) )
    {
        xI2cMuxCxt.pxCh[xI2cMuxCxt.xType].xRxCb();
    }
}


static void I2C_MUX_prvError( void )
{

	if( 0 != I2C_MASTER_IsTxBusy( &I2C_MASTER_0 ) )
	{
		//lint --e{534} suppress "Error handling is not required so return value is not checked"
		I2C_MASTER_AbortTransmit( &I2C_MASTER_0 );
		while( I2C_MASTER_IsTxBusy( &I2C_MASTER_0 ) )
		{

		}
	}

	if( 0 != I2C_MASTER_IsRxBusy( &I2C_MASTER_0 ) )
	{
		//lint --e{534} suppress "Error handling is not required so return value is not checked"
		I2C_MASTER_AbortReceive( &I2C_MASTER_0 );
		while (I2C_MASTER_IsRxBusy( &I2C_MASTER_0 ) )
		{

		}
	}

}

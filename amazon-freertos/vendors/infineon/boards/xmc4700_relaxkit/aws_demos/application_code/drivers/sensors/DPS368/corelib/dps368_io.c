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

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "dps368_io.h"

#include "spi_mux.h"
#include "i2c_mux.h"
#include "delay.h"


static int16_t  DPS368_prvInterfaceInitI2C( void *pvBusContext );
static int16_t  DPS368_prvReadByteI2C( void *pvBusContext, uint8_t ucRegAddress );
static int16_t  DPS368_prvReadBlockI2C( void *pvBusContext, uint8_t ucRegAddress, uint8_t ucLength, uint8_t *pucReadBuffer );
static int16_t  DPS368_prvWriteByteI2C( void *pvBusContext, uint8_t ucRegAddress, uint8_t ucData );

static bool		DPS368_prvSwitchI2CtoSPI( void *pvBusContext );

static int16_t  DPS368_prvInterfaceInitSPI( void *pvBusContext );
static int16_t  DPS368_prvReadByteSPI( void *pvBusContext, uint8_t ucRegAddress );
static int16_t  DPS368_prvReadBlockSPI( void *pvBusContext, uint8_t ucRegAddress, uint8_t ucLength, uint8_t *pucReadBuffer );
static int16_t  DPS368_prvWriteByteSPI( void *pvBusContext, uint8_t ucRegAddress, uint8_t ucData );




/*****************************I2C*********************************/

dps368_bus_context_t xDps368ContextI2C_1 =
{
	.address = DPS368_API_I2C_ADDRESS_0,
	.mux_type = I2C_MUX_TYPE_DPS368_1
};

dps368_bus_context_t xDps368ContextI2C_2 =
{
	.address = DPS368_API_I2C_ADDRESS_1,
	.mux_type = I2C_MUX_TYPE_DPS368_2
};

dps368_bus_connection xDps368FunctionsI2C_1 =
{
	.init        = DPS368_prvInterfaceInitI2C,
	.bus_context = &xDps368ContextI2C_1,
	.read_byte   = DPS368_prvReadByteI2C,
	.read_block  = DPS368_prvReadBlockI2C,
	.write_byte  = DPS368_prvWriteByteI2C,
	.delayms     = vDelayMs
};


dps368_bus_connection xDps368FunctionsI2C_2 =
{
	.init        = DPS368_prvInterfaceInitI2C,
	.bus_context = &xDps368ContextI2C_2,
	.read_byte   = DPS368_prvReadByteI2C,
	.read_block  = DPS368_prvReadBlockI2C,
	.write_byte  = DPS368_prvWriteByteI2C,
	.delayms     = vDelayMs
};

static int16_t DPS368_prvInterfaceInitI2C( void *pvBusContext )
{
    dps368_bus_context_t *pxCxt = pvBusContext;

    bool bRet = I2C_MUX_bSpecificInit( (I2cMuxType_t)pxCxt->mux_type, NULL, NULL, NULL, NULL, NULL );

    return bRet ? 0 : -1;
}

static int16_t DPS368_prvReadByteI2C( void *pvBusContext, uint8_t ucRegAddress )
{
    uint8_t ucData = 0;

    bool bRet = false;
    bool bAcquired = false;

    dps368_bus_context_t *pxCxt = pvBusContext;

    while( 1 )
    {
        bRet = I2C_MUX_bAcquire( (I2cMuxType_t)pxCxt->mux_type, DPS368_API_I2C_ACQUIRE_TIMEOUT );
        if( !bRet )
        {
        	break;
        }
        bAcquired = true;

		bRet = I2C_MUX_bTransmit( true, pxCxt->address, &ucRegAddress, 1, false );
		if( !bRet )
        {
        	break;
        }

        if( bWaitBusBusy( I2C_MUX_bIsTxBusy, DPS368_API_DATA_TIMEOUT ) != true )
        {
            bRet = false;
            break;
        }

        if( I2C_MUX_bIsNack() )
        {
            bRet = false;
            break;
        }

        bRet = I2C_MUX_bReceive( true, pxCxt->address, &ucData, 1, true, true );
        if( !bRet )
        {
        	break;
        }

        if( bWaitBusBusy( I2C_MUX_bIsRxBusy, DPS368_API_DATA_TIMEOUT ) != true )
        {
            bRet = false;
            break;
        }

        if( I2C_MUX_bIsNack() )
        {
            bRet = false;
            break;
        }

        bRet = true;
        break;

    }
    if( bAcquired )
    {
        bool bRetRelease = I2C_MUX_bRelease( (I2cMuxType_t)pxCxt->mux_type );
        if( bRet )
        {
        	bRet = bRetRelease;
        }
    }

    return bRet ? ucData : -1;
}

/* Should return -1 or negative value in case of failure otherwise length of
* read contents in read_buffer
* and shall place read contents in read_buffer
*/
static int16_t DPS368_prvReadBlockI2C( void *pvBusContext, uint8_t ucRegAddress, uint8_t ucLength, uint8_t *pucReadBuffer )
{
    bool bRet = false;
    bool bAcquired = false;

    dps368_bus_context_t *pxCxt = pvBusContext;

    while( 1 )
    {
        if( !ucLength )
        {
        	break;
        }
        bRet = I2C_MUX_bAcquire( (I2cMuxType_t)pxCxt->mux_type, DPS368_API_I2C_ACQUIRE_TIMEOUT );
        if( !bRet )
        {
        	break;
        }
        bAcquired = true;

        bRet = I2C_MUX_bTransmit(true, pxCxt->address, &ucRegAddress, 1, false);
        if( !bRet )
        {
        	break;
        }

        if( bWaitBusBusy( I2C_MUX_bIsTxBusy, DPS368_API_DATA_TIMEOUT ) != true )
        {
            bRet = false;
            break;
        }

        if( I2C_MUX_bIsNack() )
        {
            bRet = false;
            break;
        }

        bRet = I2C_MUX_bReceive(true, pxCxt->address, pucReadBuffer, ucLength, true, true);
        if( !bRet )
        {
        	break;
        }

        if( bWaitBusBusy( I2C_MUX_bIsRxBusy, DPS368_API_DATA_TIMEOUT ) != true )
        {
            bRet = false;
            break;
        }

        if( I2C_MUX_bIsNack() )
        {
            bRet = false;
            break;
        }

        bRet = true;
        break;
    }

    if( bAcquired )
    {
        bool bRetRelease = I2C_MUX_bRelease( (I2cMuxType_t)pxCxt->mux_type );
        if( bRet )
        {
        	bRet = bRetRelease;
        }
    }

    return bRet ? ucLength : -1;
}

/* Should return -1 in case of failure otherwise non negative number*/
static int16_t DPS368_prvWriteByteI2C( void *pvBusContext, uint8_t ucRegAddress, uint8_t ucData )
{
    bool bRet = false;
    bool bAcquired = false;

    dps368_bus_context_t *pxCxt = pvBusContext;

    while( 1 )
    {
        bRet = I2C_MUX_bAcquire( (I2cMuxType_t)pxCxt->mux_type, DPS368_API_I2C_ACQUIRE_TIMEOUT );
        if( !bRet )
        {
        	break;
        }
        bAcquired = true;

        uint8_t ucTxBuffer[2] = { ucRegAddress, ucData };

        bRet = I2C_MUX_bTransmit( true, pxCxt->address, ucTxBuffer, 2, true );
        if( !bRet )
        {
        	break;
        }

        if( bWaitBusBusy( I2C_MUX_bIsTxBusy, DPS368_API_DATA_TIMEOUT) != true )
        {
            bRet = false;
            break;
        }

        if( I2C_MUX_bIsNack() )
        {
            bRet = false;
            break;
        }

        bRet = true;
        break;
    }

    if( bAcquired )
    {
        bool bRetRelease = I2C_MUX_bRelease( (I2cMuxType_t)pxCxt->mux_type );
        if( bRet )
        {
        	bRet = bRetRelease;
        }
    }

    return bRet ? 1 : -1;
}

/*****************************SPI*********************************/


/* dps368
 * I2C -> SPI switch
 * CSB pin -> low state when power on sensor is on
 * delay for sensor will be ready (need 52ms)
 */
static bool DPS368_prvSwitchI2CtoSPI( void *pvBusContext )
{
    bool bRet = false;

    while( 1 )
    {
         /** reset CS pin for change interface to spi */
        bRet = SPI_MUX_bAcquire( (SpiMuxType_t)pvBusContext, DPS368_API_SPI_ACQUIRE_TIMEOUT );
        if( !bRet )
        {
        	break;
        }

        vDelayMs( 60 );

        bRet = SPI_MUX_bRelease( (SpiMuxType_t)pvBusContext );

        vDelayMs( 60 );

        break;
    }

    return bRet;
}

int32_t DPS368_lConnect( DPS368_t *pxDrvState, dps368_bus_connection *pxBusIO )
{
	int32_t lRet = -1;

    uint8_t ucRetInit = 0;
    uint32_t ulInitCount = DPS368_API_SPI_CONNECT_TRYES;

    while( ulInitCount > 0 )
    {
        /* initialize dps368 sensors */
        if( dps368_init( pxDrvState, pxBusIO ) == 0 )
        {
            ucRetInit = 1;
            break;
        }
        ulInitCount--;
    }

    if( ucRetInit )
    {
    	lRet = 0;

        while( 1 )
        {
        	lRet = dps368_standby( pxDrvState );
            if( lRet != 0 )
            {
            	break;
            }

            lRet = dps368_config( pxDrvState,
                    OSR_8,
                    TMP_MR_32,
                    OSR_128,
                    PM_MR_128,
                    pxDrvState->tmp_ext);
            if( lRet != 0 )
            {
            	break;
            }

            lRet = dps368_resume( pxDrvState );
            if( lRet != 0 )
            {
            	break;
            }

            break;
        }
    }

    return lRet;
}

/* DPS368 Bus SPI communication */

/* DPS368 sensor #1 */
dps368_bus_connection xDps368FunctionsSPI_1 =
{
	.bus_context = (void*)SPI_MUX_TYPE_DPS368_1,
	.init        = DPS368_prvInterfaceInitSPI,
	.read_byte   = DPS368_prvReadByteSPI,
	.read_block  = DPS368_prvReadBlockSPI,
	.write_byte  = DPS368_prvWriteByteSPI,
	.delayms     = vDelayMs
};

/* DPS368 sensor #2 */
dps368_bus_connection xDps368FunctionsSPI_2 =
{
	.bus_context = (void*)SPI_MUX_TYPE_DPS368_2,
	.init        = DPS368_prvInterfaceInitSPI,
	.read_byte   = DPS368_prvReadByteSPI,
	.read_block  = DPS368_prvReadBlockSPI,
	.write_byte  = DPS368_prvWriteByteSPI,
	.delayms     = vDelayMs
};

/* DPS368 sensor #3 */
dps368_bus_connection xDps368FunctionsSPI_3 =
{
	.bus_context = (void*)SPI_MUX_TYPE_DPS368_3,
	.init        = DPS368_prvInterfaceInitSPI,
	.read_byte   = DPS368_prvReadByteSPI,
	.read_block  = DPS368_prvReadBlockSPI,
	.write_byte  = DPS368_prvWriteByteSPI,
	.delayms     = vDelayMs
};

static int16_t DPS368_prvInterfaceInitSPI( void *pvBusContext )
{
    bool bRet = false;

    while( 1 )
    {
        bRet = SPI_MUX_bSpecificInit( (SpiMuxType_t) pvBusContext, NULL, NULL );
        if( !bRet )
        {
        	break;
        }
        SPI_MUX_bCpolSet( (SpiMuxType_t) pvBusContext, 1 );

        bRet = DPS368_prvSwitchI2CtoSPI( pvBusContext );
        break;
    }

    return bRet ? 0 : -1;
}

/* Return spi receive byte */
static int16_t DPS368_prvReadByteSPI( void *pvBusContext, uint8_t ucRegAddress )
{
    uint32_t ulCountBytes;
#if USING_LTC4332_SPI_EXT == 1
    ulCountBytes = 3;
#else
    ulCountBytes = 2;
#endif

    /* Read command ( RW = bit7 = 1 ) */
    uint8_t ucControlByte = ucRegAddress |= 0x80;

    uint8_t ucTxBuffer[ulCountBytes];
    memset( ucTxBuffer, 0, ulCountBytes * sizeof(uint8_t) );
    ucTxBuffer[0] = ucControlByte;

    uint8_t ucRxBuffer[ulCountBytes];
    memset( ucRxBuffer, 0, ulCountBytes * sizeof(uint8_t) );

	if( SPI_MUX_bAcquire( (SpiMuxType_t)pvBusContext, DPS368_API_SPI_ACQUIRE_TIMEOUT ) != true )
	{
		return -1;
	}

	/* SPI transfer function */
	if( SPI_MUX_bTransfer( ucTxBuffer, ucRxBuffer, ulCountBytes ) != true )
	{
		SPI_MUX_bRelease( (SpiMuxType_t)pvBusContext );
		return -1;
	}

	/* Wait end of receive */
	if( bWaitBusBusy( SPI_MUX_bIsRxBusy, DPS368_API_DATA_TIMEOUT ) != true )
	{
		SPI_MUX_bRelease( (SpiMuxType_t)pvBusContext );
		return -1;
	}

	SPI_MUX_bRelease( (SpiMuxType_t)pvBusContext );
//	vTaskDelay( 1 );

    /* Return error or received byte */
    return ucRxBuffer[ulCountBytes - 1];
}


static int16_t DPS368_prvWriteByteSPI( void *pvBusContext, uint8_t ucRegAddress, uint8_t ucData )
{
    /* Write command ( RW = bit7 = 0 ) */
    uint8_t ucTxBuffer[2] = { ucRegAddress, ucData };

	/* Turn chip select at active-low state */
    if( SPI_MUX_bAcquire( (SpiMuxType_t)pvBusContext, DPS368_API_SPI_ACQUIRE_TIMEOUT ) != true )
	{
		return -1;
	}

	/* SPI write function */
    if( SPI_MUX_bTransmit( ucTxBuffer, 2 ) != true )
	{
    	SPI_MUX_bRelease( (SpiMuxType_t)pvBusContext );
    	return -1;
	}

	/* Wait end of tx */
	if( bWaitBusBusy( SPI_MUX_bIsTxBusy, DPS368_API_DATA_TIMEOUT ) != true )
	{
		SPI_MUX_bRelease( (SpiMuxType_t)pvBusContext );
		return -1;
	}

    /* Turn chip select at inactive-high state */
    SPI_MUX_bRelease( (SpiMuxType_t)pvBusContext );
  //  vTaskDelay( 1 );

    return 1;
}

/* Should return -1 or negative value in case of failure otherwise length of
* read contents in read_buffer
* and shall place read contents in read_buffer
*/
static int16_t DPS368_prvReadBlockSPI( void *pvBusContext, uint8_t ucRegAddress, uint8_t ucLength, uint8_t *pucReadBuffer )
{
    if( ucLength == 0 )
    {
    	return -1;
    }

    int16_t lRetLen = ucLength;

    for( uint32_t i = 0; i < ucLength; i++ )
    {
        int16_t cRx = DPS368_prvReadByteSPI( pvBusContext, ucRegAddress + i );
        /* Check rx error */
        if( cRx < 0 )
        {
            lRetLen = -1;
            break;
        }
        *(pucReadBuffer + i) = cRx;
    }

    return lRetLen;
}


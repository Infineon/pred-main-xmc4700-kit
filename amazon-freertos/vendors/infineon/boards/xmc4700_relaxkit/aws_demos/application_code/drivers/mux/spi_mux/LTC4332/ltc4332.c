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

#include "FreeRTOS.h"
#include "semphr.h"

#include "ltc4332.h"
#include "ltc4332_loc.h"

#include "spi_mux/spi_mux.h"
#include "delay.h"

#include "DAVE.h"


static bool LTC4332_prvCsInit( LTC4332_CS_t xCs );
static void LTC4332_prvCsSetLow( LTC4332_CS_t xCs );
static void LTC4332_prvCsSetHigh( LTC4332_CS_t xCs );

static bool LTC4332_prvWriteByteWithCheck( uint8_t ucReg, uint8_t ucData );
static bool LTC4332_prvReadByte( uint8_t ucRegAddr, uint8_t *pucData );
static bool LTC4332_prvWriteByte( uint8_t ucRegAddr, uint8_t ucData );


bool LTC4332_bInit( void )
{
    bool bRet = false;

    if( SPI_MUX_bSpecificInit( SPI_MUX_TYPE_DPS368_READ, NULL, NULL ) != true )
    {
    	return false;
    }

    bRet = SPI_MUX_bSpecificInit( SPI_MUX_TYPE_LTC, NULL, NULL );
    if( bRet )
    {
    	/* Set CPOL = CPHA = 1 for 1..3 channels */
         bRet = LTC4332_prvWriteByteWithCheck( LTC4332_REGISTER_CONFIG, 0x3F );
    }

    return bRet;
}

void LTC4332_vDeInit( void )
{
	SPI_MUX_bSpecificDeinit( SPI_MUX_TYPE_DPS368_READ );
	SPI_MUX_bSpecificDeinit( SPI_MUX_TYPE_LTC );
}

bool LTC4332_bReceive( uint8_t *pucReceiveData, uint32_t ulCount )
{
    SPI_MASTER_STATUS_t SPI_xStatus = SPI_MASTER_Receive( &SPI_MASTER_0, pucReceiveData, ulCount );
    if( SPI_xStatus != SPI_MASTER_STATUS_SUCCESS )
    {
    	return false;
    }

    return true;
}

bool LTC4332_bTransmit( uint8_t *pucTransmitData, uint32_t ulCount )
{
    SPI_MASTER_STATUS_t SPI_xStatus = SPI_MASTER_Transmit( &SPI_MASTER_0, pucTransmitData, ulCount );
    if( SPI_xStatus != SPI_MASTER_STATUS_SUCCESS )
	{
    	return false;
	}

	return true;
}

bool LTC4332_bTransfer( uint8_t *pucTransmitData, uint8_t *pucReceiveData, uint32_t ulCount )
{

	if( ulCount + 1 >= LTC4332_RX_BUF_SIZE )
	{
		return false;
	}

	uint8_t rx[LTC4332_RX_BUF_SIZE];

	SPI_MASTER_STATUS_t SPI_xStatus = SPI_MASTER_Transfer( &SPI_MASTER_0, pucTransmitData, &rx[0], ulCount + 1 );
	if( SPI_xStatus != SPI_MASTER_STATUS_SUCCESS )
	{
		return false;
	}

	if( bWaitBusBusy( SPI_MUX_bIsRxBusy, LTC_SPI_TIMEOUT ) != true )
	{
		return false;
	}

	memcpy( pucReceiveData, &rx[1], ulCount );

	return true;
}

__attribute__((unused))
static bool LTC4332_prvCsInit( LTC4332_CS_t xCs )
{
    bool bRet = true;

    /** Declaration statuses returned by interfaces during initialization */
    DIGITAL_IO_STATUS_t DIGITAL_IO_xInitStatus = DIGITAL_IO_STATUS_OK;

    switch( xCs )
    {
    	case LTC4332_CS:
    		DIGITAL_IO_xInitStatus = DIGITAL_IO_Init( &LTC_CS );
        	break;
        case LTC4332_CS1:
        	DIGITAL_IO_xInitStatus = DIGITAL_IO_Init( &DPS368_CS1 );
        	break;
        case LTC4332_CS2:
        	DIGITAL_IO_xInitStatus = DIGITAL_IO_Init( &DPS368_CS2 );
        	break;
        case LTC4332_CS3:
        	DIGITAL_IO_xInitStatus = DIGITAL_IO_Init( &DPS368_CS3 );
        	break;
        default:
        	break;
    }

    if( DIGITAL_IO_xInitStatus != DIGITAL_IO_STATUS_OK )
    {
    	bRet = false;
    }

    return bRet;
}

__attribute__((unused))
static void LTC4332_prvCsSetLow( LTC4332_CS_t xCs )
{
    switch( xCs )
	{
		case LTC4332_CS:
			DIGITAL_IO_SetOutputLow( &LTC_CS );
			break;
		case LTC4332_CS1:
			DIGITAL_IO_SetOutputLow( &DPS368_CS1 );
			break;
		case LTC4332_CS2:
			DIGITAL_IO_SetOutputLow( &DPS368_CS2 );
			break;
		case LTC4332_CS3:
			DIGITAL_IO_SetOutputLow( &DPS368_CS3 );
			break;
		default:
			break;
	}

}

__attribute__((unused))
static void LTC4332_prvCsSetHigh( LTC4332_CS_t xCs )
{
    switch( xCs )
	{
		case LTC4332_CS:
			DIGITAL_IO_SetOutputHigh( &LTC_CS );
			break;
		case LTC4332_CS1:
			DIGITAL_IO_SetOutputHigh( &DPS368_CS1 );
			break;
		case LTC4332_CS2:
			DIGITAL_IO_SetOutputHigh( &DPS368_CS2 );
			break;
		case LTC4332_CS3:
			DIGITAL_IO_SetOutputHigh( &DPS368_CS3 );
			break;
		default:
			break;
	}

}

static bool LTC4332_prvWriteByteWithCheck( uint8_t ucReg, uint8_t ucData )
{
    bool bRet = false;

    uint8_t ucReceiveData;

    if( LTC4332_prvWriteByte( ucReg, ucData ) )
    {
    	vTaskDelay( 1 );
    	if( LTC4332_prvReadByte( ucReg, &ucReceiveData ) )
        {
            if( ucData == ucReceiveData )
            {
            	bRet = true;
            }
        }
    }

    return bRet;
}


static bool LTC4332_prvReadByte(uint8_t ucRegAddr, uint8_t *pucData)
{
	/* Read command ( RW = bit0 = 1 ) */
	uint8_t ucControlByte = ucRegAddr <<= 1;
	ucControlByte |= 0x01;

	uint8_t tx[2] = { ucControlByte, 0x00 };
	uint8_t rx[2] = { 0x00 };

	/* Turn chip select at active-low state */
	if( SPI_MUX_bAcquire( SPI_MUX_TYPE_LTC, LTC_SPI_TIMEOUT ) != true )
	{
		return false;
	}

	/* SPI transfer function */
	if( SPI_MUX_bTransfer( tx, rx, 2 ) != true )
	{
		SPI_MUX_bRelease( SPI_MUX_TYPE_LTC );
		return false;
	}

	/* Wait end of receive */
	if( bWaitBusBusy( SPI_MUX_bIsRxBusy, LTC_SPI_TIMEOUT ) != true )
	{
		SPI_MUX_bRelease( SPI_MUX_TYPE_LTC );
		return false;
	}

	*pucData = rx[1];

	SPI_MUX_bRelease( SPI_MUX_TYPE_LTC );

	return true;
}


static bool LTC4332_prvWriteByte( uint8_t ucRegAddr, uint8_t ucData)
{
	/* Write command ( RW = bit0 = 0 ) */
	uint8_t ucControlByte = ucRegAddr <<= 1;

	uint8_t tx[2] = { ucControlByte, ucData };

	/* Turn chip select at active-low state */
	if( SPI_MUX_bAcquire( SPI_MUX_TYPE_LTC, LTC_SPI_TIMEOUT ) != true )
	{
		return false;
	}

	/* SPI write function */
	if( SPI_MUX_bTransmit( tx, 2 ) != true )
	{
		SPI_MUX_bRelease( SPI_MUX_TYPE_LTC );
		return false;
	}

	/* Wait end of transmit */
	if( bWaitBusBusy( SPI_MUX_bIsTxBusy, LTC_SPI_TIMEOUT ) != true )
	{
		SPI_MUX_bRelease( SPI_MUX_TYPE_LTC );
		return false;
	}

	vTaskDelay( 1 );

	/* Turn chip select at inactive-high state */
	SPI_MUX_bRelease( SPI_MUX_TYPE_LTC );

	return true;
}

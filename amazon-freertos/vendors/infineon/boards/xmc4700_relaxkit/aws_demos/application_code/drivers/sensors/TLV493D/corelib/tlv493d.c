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
#include <math.h>

#include "tlv493d.h"
#include "util/RegMask.h"
#include "util/BusInterface2.h"
#include "util/tlv493d_conf.h"

#include "i2c_mux.h"


static void prvResetSensor( uint8_t ucAddress );
static void prvSetRegBits( Tlv493d_t *pxCxt, uint8_t ucRegMaskIndex, uint8_t ucData );
static uint8_t prvGetRegBits( Tlv493d_t *pxCxt, uint8_t ucRegMaskIndex );
static void prvCalcParity( Tlv493d_t *pxCxt );
static int16_t prvConcatResults( uint8_t ucUpperByte, uint8_t ucLowerByte, bool bUpperFull );


bool TLV493D_bInit( void **ppvHandle, Tlv493dAddress_t xSlaveAddress, bool bReset )
{
    bool bRet = false;

    while( 1 )
    {
    	*ppvHandle = pvPortMalloc( sizeof( Tlv493d_t ) );
		if(! (*ppvHandle))
		{
			break;
		}

		Tlv493d_t *pxCxt = *ppvHandle;

        bRet = TLV493D_bInitInterface( &pxCxt->mInterface, xSlaveAddress );
        if( !bRet )
        {
        	break;
        }

        vTaskDelay( TLV493D_STARTUP_DELAY );

        if( bReset == true )
        {
        	prvResetSensor( pxCxt->mInterface.adress );
        }

        /* get all register data from sensor */
        TLV493D_bReadOut( &pxCxt->mInterface );
        /* copy factory settings to write registers */
        prvSetRegBits( pxCxt, W_RES1, prvGetRegBits( pxCxt, R_RES1 ) );
        prvSetRegBits( pxCxt, W_RES1, prvGetRegBits( pxCxt, R_RES1 ) );
        prvSetRegBits( pxCxt, W_RES1, prvGetRegBits( pxCxt, R_RES1 ) );
        /* enable parity detection */
        prvSetRegBits( pxCxt, W_PARITY_EN, 1 );
        /* configure sensor to low power mode */
        /* also contains parity calculation and write out to sensor */
        TLV493D_bSetAccessMode( pxCxt, TLV493D_DEFAULTMODE );

        bRet = true;
        break;
    }

    if( bRet != true )
	{
		vPortFree( *ppvHandle );
	}

    return bRet;
}


void TLV493D_vDeInit( void **ppvHandle )
{
	vPortFree( *ppvHandle );
}


void TLV493D_vEnd( Tlv493d_t *pxCxt )
{
    TLV493D_vDisableInterrupt (pxCxt );
    TLV493D_bSetAccessMode( pxCxt, POWER_DOWN_MODE );
}


bool TLV493D_bSetAccessMode( Tlv493d_t *pxCxt, AccessMode_e xMode )
{
	bool bRet = false;

	const AccessMode_t *pxModeConfig = &( accModes[xMode] );

	prvSetRegBits( pxCxt, W_FAST, pxModeConfig->fast );
	prvSetRegBits( pxCxt, W_LOWPOWER, pxModeConfig->lp );
	prvSetRegBits( pxCxt, W_LP_PERIOD, pxModeConfig->lpPeriod );
	prvCalcParity( pxCxt );

	bRet = TLV493D_bWriteOut( &pxCxt->mInterface );
	if( bRet )
	{
		pxCxt->mMode = xMode;
	}

	return bRet;
}


void TLV493D_vEnableInterrupt( Tlv493d_t *pxCxt )
{
	prvSetRegBits( pxCxt, W_INT, 1 );
	prvCalcParity( pxCxt );
	TLV493D_bWriteOut( &pxCxt->mInterface );
}


void TLV493D_vDisableInterrupt( Tlv493d_t *pxCxt )
{
	prvSetRegBits( pxCxt, W_INT, 0 );
	prvCalcParity( pxCxt );
	TLV493D_bWriteOut( &pxCxt->mInterface );
}


void TLV493D_vEnableTemp( Tlv493d_t *pxCxt )
{
	prvSetRegBits( pxCxt, W_TEMP_NEN, 0 );
	prvCalcParity( pxCxt );
	TLV493D_bWriteOut( &pxCxt->mInterface );
}


void TLV493D_vDisableTemp( Tlv493d_t *pxCxt )
{
	prvSetRegBits( pxCxt, W_TEMP_NEN, 1 );
	prvCalcParity( pxCxt );
	TLV493D_bWriteOut( &pxCxt->mInterface );
}


uint16_t TLV493D_usGetMeasurementDelay( Tlv493d_t *pxCxt )
{
	return accModes[pxCxt->mMode].measurementTime;
}


Tlv493dError_t TLV493D_xUpdateData( Tlv493d_t *pxCxt )
{
	Tlv493dError_t xRet = TLV493D_NO_ERROR;

	/* in POWER_DOWN_MODE, sensor has to be switched on for one measurement */
	uint8_t powerdown = 0;

	if( pxCxt->mMode == POWER_DOWN_MODE )
	{
		if( !TLV493D_bSetAccessMode( pxCxt, MASTER_CONTROLLED_MODE ) )
		{
			xRet = TLV493D_BUS_ERROR;
		}
		vTaskDelay( TLV493D_usGetMeasurementDelay( pxCxt ) );
		powerdown = 1;
	}

	if( xRet == TLV493D_NO_ERROR )
	{
#ifdef TLV493D_ACCELERATE_READOUT
		/* just read the most important results in FAST_MODE, if this behavior is desired */
		if( pxCxt->mMode == FAST_MODE )
		{
			if( !TLV493D_bReadOutCount( &pxCxt->mInterface, TLV493D_FAST_READOUT ) )
			{
				xRet = TLV493D_BUS_ERROR;
			}
		}
		else
		{
			if( !TLV493D_bReadOutCount( &pxCxt->mInterface, TLV493D_MEASUREMENT_READOUT ) )
			{
				xRet = TLV493D_BUS_ERROR;
			}
		}
#else
		if( !TLV493D_bReadOutCount( &pxCxt->mInterface, TLV493D_MEASUREMENT_READOUT) )
		{
			xRet = TLV493D_BUS_ERROR;
		}
#endif
		if (xRet == TLV493D_NO_ERROR)
		{
			/* construct results from registers */
			pxCxt->mXdata = prvConcatResults( prvGetRegBits( pxCxt, R_BX1 ), prvGetRegBits( pxCxt, R_BX2 ), true );
			pxCxt->mYdata = prvConcatResults( prvGetRegBits( pxCxt, R_BY1 ), prvGetRegBits( pxCxt, R_BY2 ), true );
			pxCxt->mZdata = prvConcatResults( prvGetRegBits( pxCxt, R_BZ1 ), prvGetRegBits( pxCxt, R_BZ2 ), true );
			pxCxt->mTempdata = prvConcatResults( prvGetRegBits( pxCxt, R_TEMP1 ), prvGetRegBits( pxCxt, R_TEMP2 ), false );
			/* switch sensor back to POWER_DOWN_MODE, if it was in POWER_DOWN_MODE before */
			if( powerdown )
			{
				if( !TLV493D_bSetAccessMode( pxCxt, POWER_DOWN_MODE ) )
				{
					xRet = TLV493D_BUS_ERROR;
				}
			}
			if( xRet == TLV493D_NO_ERROR )
			{
				/* if the return value is 0, all results are from the same frame otherwise some results may be out dated */
				if( prvGetRegBits( pxCxt, R_CHANNEL ) != 0 )
				{
					xRet = TLV493D_FRAME_ERROR;
				}
			}
		}
	}

	pxCxt->mExpectedFrameCount = prvGetRegBits( pxCxt, R_FRAMECOUNTER ) + 1;

	return xRet;
}


float TLV493D_fGetX( Tlv493d_t *pxCxt )
{
	return (float)(pxCxt->mXdata) * TLV493D_B_MULT;
}


float TLV493D_fGetY( Tlv493d_t *pxCxt )
{
	return (float)(pxCxt->mYdata) * TLV493D_B_MULT;
}


float TLV493D_fGetZ( Tlv493d_t *pxCxt )
{
	return (float)(pxCxt->mZdata) * TLV493D_B_MULT;
}


float TLV493D_fGetTemp( Tlv493d_t *pxCxt )
{
	return (float)(pxCxt->mTempdata-TLV493D_TEMP_OFFSET) * TLV493D_TEMP_MULT;
}


float TLV493D_fGetAmount( Tlv493d_t *pxCxt )
{
	/* sqrt(x^2 + y^2 + z^2) */
	return TLV493D_B_MULT * sqrt( pow( (float)(pxCxt->mXdata), 2 ) + pow( (float)(pxCxt->mYdata), 2 ) + pow( (float)(pxCxt->mZdata), 2 ) );
}


float TLV493D_fGetAzimuth( Tlv493d_t *pxCxt )
{
	/* arctan(y/x) */
	return atan2( (float)(pxCxt->mYdata), (float)(pxCxt->mXdata) );
}


float TLV493D_fGetPolar( Tlv493d_t *pxCxt )
{
	/* arctan(z/(sqrt(x^2+y^2))) */
	return atan2( (float)(pxCxt->mZdata), sqrt( pow( (float)(pxCxt->mXdata), 2 ) + pow( (float)(pxCxt->mYdata), 2 ) ) );
}


/* internal function called by begin()
 * The sensor has a special reset sequence which allows to change its i2c address by setting SDA to high or low during a reset. 
 * As some i2c peripherals may not cope with this, the simplest way is to use for this very few bytes bitbanging on the SCL/SDA lines.
 * Furthermore, as the uC may be stopped during a i2c transmission, a special recovery sequence allows to bring the bus back to
 * an operating state.
 */
/* Recovery & Reset - this can be handled by any uC as it uses bitbanging */
static void prvResetSensor( uint8_t ucAddress )
{
#if 0
	mInterface.bus->beginTransmission(0x00);

	if (adr == TLV493D_ADDRESS1) {
		/* if the sensor shall be initialized with i2c address 0x1F */
		mInterface.bus->write(0xFF);
	} else {
		/* if the sensor shall be initialized with address 0x5E */
		mInterface.bus->write((uint8_t)0x00);
	}

	mInterface.bus->endTransmission(true);
#endif
}


static void prvSetRegBits( Tlv493d_t *pxCxt, uint8_t ucRegMaskIndex, uint8_t ucData )
{
	if( ucRegMaskIndex < TLV493D_NUM_OF_REGMASKS )
	{
		ucSetToRegs( &(regMasks[ucRegMaskIndex]), pxCxt->mInterface.regWriteData, ucData );
	}
}


static uint8_t prvGetRegBits( Tlv493d_t *pxCxt, uint8_t ucRegMaskIndex )
{
	if( ucRegMaskIndex < TLV493D_NUM_OF_REGMASKS )
	{
		const RegMask_t *pxMask = &(regMasks[ucRegMaskIndex]);
		if( pxMask->rw == REGMASK_READ )
		{
			return ucGetFromRegs( pxMask, pxCxt->mInterface.regReadData );
		}
		else
		{
			return ucGetFromRegs( pxMask, pxCxt->mInterface.regWriteData );
		}
	}

	return 0;
}


static void prvCalcParity( Tlv493d_t *pxCxt )
{
	uint8_t i;
	uint8_t y = 0x00;

	/* set parity bit to 1
	* algorithm will calculate an even parity and replace this bit,
	* so parity becomes odd
	*/
	prvSetRegBits( pxCxt, W_PARITY, 1 );
	/* combine array to one byte first */
	for( i = 0; i < TLV493D_BUSIF_WRITESIZE; i++ )
	{
		y ^= pxCxt->mInterface.regWriteData[i];
	}
	/* combine all bits of this byte */
	y = y ^ ( y >> 1 );
	y = y ^ ( y >> 2 );
	y = y ^ ( y >> 4 );
	/* parity is in the LSB of y */
	prvSetRegBits( pxCxt, W_PARITY, y&0x01 );
}


static int16_t prvConcatResults( uint8_t ucUpperByte, uint8_t ucLowerByte, bool bUpperFull )
{
	/* 16-bit signed integer for 12-bit values of sensor */
	int16_t sValue = 0x0000;

	if( bUpperFull )
	{
		sValue = ucUpperByte << 8;
		sValue |=( ucLowerByte & 0x0F ) << 4;
	}
	else
	{
		sValue = ( ucUpperByte & 0x0F ) << 12;
		sValue |= ucLowerByte << 4;
	}
	/* shift left so that value is a signed 12 bit integer */
	sValue >>= 4;

	return sValue;
}

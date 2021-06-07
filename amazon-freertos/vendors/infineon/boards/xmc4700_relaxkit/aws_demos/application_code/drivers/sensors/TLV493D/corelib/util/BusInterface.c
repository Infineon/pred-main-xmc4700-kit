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

#include "BusInterface2.h"

#include "i2c_mux.h"
#include "delay.h"


bool TLV493D_bInitInterface( BusInterface_t *pxInterface, uint8_t ucAdress )
{
	uint8_t i;

	pxInterface->adress = ucAdress;

	for( i = 0; i < TLV493D_BUSIF_READSIZE; i++ )
	{
		pxInterface->regReadData[i] = 0x00;
	}

	for( i = 0; i < TLV493D_BUSIF_WRITESIZE; i++ )
	{
		pxInterface->regWriteData[i] = 0x00;
	}

	return I2C_MUX_bSpecificInit( I2C_MUX_TYPE_TLV493D, NULL, NULL, NULL, NULL, NULL );
}


bool TLV493D_bReadOut( BusInterface_t *pxInterface )
{
	return TLV493D_bReadOutCount( pxInterface, TLV493D_BUSIF_READSIZE );
}


bool TLV493D_bReadOutCount( BusInterface_t *pxInterface, uint8_t ucCount )
{
	bool bRet = false;

	if( ucCount > TLV493D_BUSIF_READSIZE )
	{
		ucCount = TLV493D_BUSIF_READSIZE;
	}

    if (!I2C_MUX_bAcquire( I2C_MUX_TYPE_TLV493D, 50 ) )
    {
        bRet = I2C_MUX_bReceive( true, pxInterface->adress, &pxInterface->regReadData[0], ucCount, true, true );
        if( bWaitBusBusy( I2C_MUX_bIsRxBusy, TLV493D_Data_tIMEOUT ) != true )
		{
			bRet = false;
		}

        I2C_MUX_bRelease( I2C_MUX_TYPE_TLV493D );
    }

	return bRet;
}


bool TLV493D_bWriteOut( BusInterface_t *pxInterface )
{
	return TLV493D_bWriteOutCount( pxInterface, TLV493D_BUSIF_WRITESIZE );
}


bool TLV493D_bWriteOutCount( BusInterface_t *pxInterface, uint8_t ucCount )
{
	bool bRet = false;

	if( ucCount > TLV493D_BUSIF_WRITESIZE )
	{
		ucCount = TLV493D_BUSIF_WRITESIZE;
	}

    if( !I2C_MUX_bAcquire( I2C_MUX_TYPE_TLV493D, 50 ) )
    {
        bRet = I2C_MUX_bTransmit( true, pxInterface->adress, &pxInterface->regWriteData[0], ucCount, true );
        if( bWaitBusBusy( I2C_MUX_bIsTxBusy, TLV493D_Data_tIMEOUT ) != true )
		{
			bRet = false;
		}

        I2C_MUX_bRelease( I2C_MUX_TYPE_TLV493D );
    }

	return bRet;
}

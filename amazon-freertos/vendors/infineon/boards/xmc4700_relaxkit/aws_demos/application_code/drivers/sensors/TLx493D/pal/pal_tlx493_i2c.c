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

#include "pal_TLx493_i2c.h"
#include "../TLE_AW2B6/driver/tle_aw2b6_defines.h"

#include "i2c_mux.h"
#include "delay.h"


/* reset address */
#define TLE493D_AW2B6_I2C_RESET_ADDR    ( 0x00U )
/* recovery address */
#define TLE493D_AW2B6_I2C_RECOV_ADDR    ( 0xFFU )


static I2cMuxType_t xConvertSlaveAddrToMux( uint8_t ucAddr )
{
    switch( ucAddr )
    {
        case TLE493D_AW2B6_I2C_A0_ADDR:
            return I2C_MUX_TYPE_TLI493D_1;
        case TLE493D_AW2B6_I2C_A1_ADDR:
            return I2C_MUX_TYPE_TLI493D_1;
        default :
        	return -1;
    }
}


I2C_INT_State_t I2C_INT_xInit( uint8_t ucAddr )
{
    I2cMuxType_t xMux = xConvertSlaveAddrToMux( ucAddr );
    if( xMux < 0 )
    {
    	return I2C_INT_ERR_PROTOCOL;
    }

    bool bRet = I2C_MUX_bSpecificInit( xMux, NULL, NULL, NULL, NULL, NULL );
    if( !bRet )
    {
    	return I2C_INT_ERR_PROTOCOL;
    }

    return I2C_INT_SUCCESS;
}


I2C_INT_State_t I2C_INT_xWriteBlock( uint8_t ucAddr, const uint8_t *pucData, uint8_t ucCount )
{
	I2C_INT_State_t xState = I2C_INT_SUCCESS;
	bool bRet = false;

    I2cMuxType_t xMux = xConvertSlaveAddrToMux( ucAddr );
    if( xMux < 0 )
    {
    	return I2C_INT_ERR_PROTOCOL;
    }

    if( I2C_MUX_bAcquire( xMux, PAL_TLX493_I2C_ACQUIRE_TIMEOUT ) )
    {
        bRet = I2C_MUX_bTransmit( true, ucAddr, (uint8_t*)pucData, ucCount, true );
        if( !bRet )
        {
        	return I2C_INT_ERR_PROTOCOL;
        }

        if( bWaitBusBusy( I2C_MUX_bIsTxBusy, PAL_TLX493_DATA_TIMEOUT ) != true )
		{
        	return I2C_INT_ERR_PROTOCOL;
		}

        if( I2C_MUX_bIsNack() )
        {
        	xState = I2C_INT_NACK;
        }

        bRet = I2C_MUX_bRelease( xMux );
        if( !bRet )
        {
        	return I2C_INT_ERR_PROTOCOL;
        }

    }

    return xState;
}


I2C_INT_State_t I2C_INT_xReadBlock( uint8_t ucAddr, uint8_t *pucData, uint8_t ucCount )
{
	bool bRet = false;
	I2C_INT_State_t xState = I2C_INT_SUCCESS;

    I2cMuxType_t xMux = xConvertSlaveAddrToMux( ucAddr );
    if( xMux < 0 )
    {
    	return I2C_INT_ERR_PROTOCOL;
    }

    if( I2C_MUX_bAcquire( xMux, PAL_TLX493_I2C_ACQUIRE_TIMEOUT ) )
    {
        bRet = I2C_MUX_bReceive( true, ucAddr, pucData, ucCount, true, true );
        if( !bRet )
        {
        	return I2C_INT_ERR_PROTOCOL;
        }

        if( bWaitBusBusy( I2C_MUX_bIsRxBusy, PAL_TLX493_DATA_TIMEOUT ) != true )
		{
			return I2C_INT_ERR_PROTOCOL;
		}

        if( I2C_MUX_bIsNack() )
        {
        	xState = I2C_INT_NACK;
        }

        bRet = I2C_MUX_bRelease( xMux );
        if( !bRet )
        {
        	return I2C_INT_ERR_PROTOCOL;
        }

    }

    return xState;
}



void I2C_INT_vWriteReset( void )
{
#if 0
    NVIC_DisableIRQ(USIC0_0_IRQn);
    NVIC_DisableIRQ(USIC0_2_IRQn);

    _protect_off();

    XMC_I2C_CH_MasterStart(
        XMC_USIC0_CH1,
        TLE493D_AW2B6_I2C_RESET_ADDR,
        XMC_I2C_CH_CMD_WRITE
    );
    wait(10);
    XMC_I2C_CH_MasterStop(XMC_USIC0_CH1);

    // wait for stop
    int count = 0;
    while (XMC_USIC_CH_TBUF_STATUS_BUSY == XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C0_CH1)) {
        if (++ count > 100000) {
            break;
        }
    }

    _protect_on();

    NVIC_ClearPendingIRQ(USIC0_0_IRQn);
    NVIC_ClearPendingIRQ(USIC0_2_IRQn);
    NVIC_EnableIRQ(USIC0_0_IRQn);
    NVIC_EnableIRQ(USIC0_2_IRQn);
#endif
}


void I2C_INT_vWriteRecover( void )
{
#if 0
    NVIC_DisableIRQ(USIC0_0_IRQn);
    NVIC_DisableIRQ(USIC0_2_IRQn);

    _protect_off();

    XMC_I2C_CH_MasterStart(
        XMC_USIC0_CH1,
        TLE493D_AW2B6_I2C_RECOV_ADDR,
        XMC_I2C_CH_CMD_READ
    );
    wait(10);

    XMC_I2C_CH_MasterStop(XMC_USIC0_CH1);

    // wait for stop
    int count = 0;
    while (XMC_USIC_CH_TBUF_STATUS_BUSY == XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C0_CH1)) {
        if (++ count > 100000) {
            break;
        }
    }

    _protect_on();

    NVIC_ClearPendingIRQ(USIC0_0_IRQn);
    NVIC_ClearPendingIRQ(USIC0_2_IRQn);
    NVIC_EnableIRQ(USIC0_0_IRQn);
    NVIC_EnableIRQ(USIC0_2_IRQn);
#endif
}

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

#include "tle_aw2b6.h"
#include "driver/tle_aw2b6_defines.h"
#include "driver/tle_aw2b6_driver.h"
#include "TLx493D/tlx493d.h"
#include "TLx493D/tlx493d_interface.h"

#include "iot_demo_logging.h"


static struct {
	TLE493D_Data_t data;

} LocalData;


/* Internals */


uint8_t TLE493D_AW2B6_ucGetBitFP( TLE493D_Data_t *pxData )
{
	uint8_t ucParity;

	/* compute parity of MOD1 register */
	ucParity = MISC_get_parity( pxData->regmap.MOD1 & ~(TLE493D_AW2B6_MOD1_FP_MSK) );
	/* add parity of MOD2:PRD register bits */
	ucParity ^= MISC_get_parity( pxData->regmap.MOD2 & (TLE493D_AW2B6_MOD2_PRD_MSK) );
	/* compute ODD parity */
	ucParity ^= 1;

	return ucParity & 1;
}


uint8_t TLE493D_AW2B6_ucGetBitCP( TLE493D_Data_t *pxData )
{
	uint8_t *pucRegs, ucParity, i;

	pucRegs = (uint8_t *)&(pxData->regmap);
	ucParity = 0;
	/* even parity for registers XL to ZH */
	for( i = TLE493D_AW2B6_XL_REG; i <= TLE493D_AW2B6_ZH_REG; i++ )
	{
		ucParity ^= pucRegs[i];
	}
	/* include WU */
	ucParity ^= pucRegs[TLE493D_AW2B6_WU_REG] & ~(TLE493D_AW2B6_WU_WA_MSK);
	/* include TMode */
	ucParity ^= pucRegs[TLE493D_AW2B6_TMode_REG] & ~(TLE493D_AW2B6_TMode_TST_MSK);
	/* include TPhase */
	ucParity ^= pucRegs[TLE493D_AW2B6_TPhase_REG] & ~(TLE493D_AW2B6_TPhase_PH_MSK);
	/* include Config */
	ucParity ^= pucRegs[TLE493D_AW2B6_Config_REG] & ~(TLE493D_AW2B6_Config_CP_MSK);
	/* compute parity bit */
	ucParity = MISC_get_parity( ucParity );
	/* convert to ODD parity */
	ucParity ^= 1U;

	return ucParity & 1U;
}


static int32_t prvSetOperationModeMCM( TLE493D_Data_t *pxData )
{
	int32_t lError;

	/* clear bits */
	pxData->regmap.MOD1 &= ~(TLE493D_AW2B6_MOD1_CA_MSK
				| TLE493D_AW2B6_MOD1_INT_MSK
				| TLE493D_AW2B6_MOD1_MODE_MSK
				| TLE493D_AW2B6_MOD1_FP_MSK
	);
	/* set protocol and parity bits */
	pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_CA_ENABLE
				| TLE493D_AW2B6_MOD1_INT_DISABLE
				| TLE493D_AW2B6_MOD1_MODE_MCM;
	pxData->regmap.MOD1 |= TLE493D_AW2B6_ucGetBitFP( pxData ) << TLE493D_AW2B6_MOD1_FP_POS;
	/* write register */
	lError = TLE493D_AW2B6_lWriteReg(pxData->IIC_addr, TLE493D_AW2B6_MOD1_REG, pxData->regmap.MOD1 );

	if( !lError )
	{
		/* clear and set trigger bits */
		pxData->regmap.Config &= ~TLE493D_AW2B6_Config_TRIG_MSK;
		pxData->regmap.Config |= TLE493D_AW2B6_Config_TRIG_R6;
		lError = TLE493D_AW2B6_lWriteReg( pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );
	}

	return lError;
}


static int32_t _set_operation_mode_low_power( TLE493D_Data_t *pxData )
{
	int32_t lError;

	/* clear bits */
	pxData->regmap.MOD1 &= ~(TLE493D_AW2B6_MOD1_CA_MSK
				| TLE493D_AW2B6_MOD1_INT_MSK
				| TLE493D_AW2B6_MOD1_MODE_MSK
				| TLE493D_AW2B6_MOD1_FP_MSK
	);
	/* set protocol and parity bits */
	pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_CA_ENABLE
				| TLE493D_AW2B6_MOD1_INT_ENABLE
				| TLE493D_AW2B6_MOD1_MODE_LOW_POWER;
	pxData->regmap.MOD1 |= TLE493D_AW2B6_ucGetBitFP( pxData ) << TLE493D_AW2B6_MOD1_FP_POS;
	/* write register */
	lError = TLE493D_AW2B6_lWriteReg(pxData->IIC_addr, TLE493D_AW2B6_MOD1_REG, pxData->regmap.MOD1 );

	/* disable ADC trigger */
	if( !lError )
	{
		pxData->regmap.Config &= ~TLE493D_AW2B6_Config_TRIG_MSK;
		pxData->regmap.Config |= TLE493D_AW2B6_Config_TRIG_NONE;
		lError = TLE493D_AW2B6_lWriteReg( pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );
	}

	return lError;
}


static int32_t _set_operation_mode_fast( TLE493D_Data_t *pxData )
{
	int32_t lError;

	/* clear bits */
	pxData->regmap.MOD1 &=
				~(TLE493D_AW2B6_MOD1_CA_MSK
				| TLE493D_AW2B6_MOD1_FP_MSK
				| TLE493D_AW2B6_MOD1_INT_MSK
				| TLE493D_AW2B6_MOD1_MODE_MSK
	);
	/* set protocol and parity bits */
	pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_CA_ENABLE
				| TLE493D_AW2B6_MOD1_INT_ENABLE
				| TLE493D_AW2B6_MOD1_MODE_FAST_MODE;
	pxData->regmap.MOD1 |= TLE493D_AW2B6_ucGetBitFP( pxData ) << TLE493D_AW2B6_MOD1_FP_POS;
	/* write register */
	lError = TLE493D_AW2B6_lWriteReg(pxData->IIC_addr, TLE493D_AW2B6_MOD1_REG, pxData->regmap.MOD1 );

	/* disable ADC trigger */
	if( !lError )
	{
		pxData->regmap.Config &= ~TLE493D_AW2B6_Config_TRIG_MSK;
		pxData->regmap.Config |= TLE493D_AW2B6_Config_TRIG_NONE;
		lError = TLE493D_AW2B6_lWriteReg( pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );
	}

	return lError;
}


/* Public */


int32_t TLE493D_AW2B6_lInit( TLE493D_Data_t *pxData, TLE493D_Address_t ucSlaveAddressI2C )
{
	int32_t lError = 0;

	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	I2C_INT_xInit( ucSlaveAddressI2C );

	pxData->IIC_addr = ucSlaveAddressI2C;
	/* prepare register */
	pxData->regmap.MOD1 = 0;
	/* needed to compute the FP bit */
	pxData->regmap.MOD2 = 0;
	/* set address bits to maintain current address */
	switch( ucSlaveAddressI2C )
	{
		case TLE493D_AW2B6_I2C_A0_ADDR:
			pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_IICadr_A0;
			break;
		case TLE493D_AW2B6_I2C_A1_ADDR:
			pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_IICadr_A1;
			break;
		case TLE493D_AW2B6_I2C_A2_ADDR:
			pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_IICadr_A2;
			break;
		case TLE493D_AW2B6_I2C_A3_ADDR:
			pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_IICadr_A3;
			break;
		default:
			break;
	}
	/* Initial settings:
	 * 1-Byte read protocol
	 * Collision avoidance
	 * Interrupt disabled
	 * Master Control Mode
	 * */
	pxData->regmap.MOD1 = TLE493D_AW2B6_MOD1_PR_1BYTE
					 | TLE493D_AW2B6_MOD1_CA_ENABLE
					 | TLE493D_AW2B6_MOD1_INT_DISABLE
					 | TLE493D_AW2B6_MOD1_MODE_MCM;
	pxData->regmap.MOD1 |= ( TLE493D_AW2B6_ucGetBitFP( pxData ) << TLE493D_AW2B6_MOD1_FP_POS );

	/* write registers */
	lError = TLE493D_AW2B6_lWriteReg(pxData->IIC_addr, TLE493D_AW2B6_MOD1_REG, pxData->regmap.MOD1 );
	if( !lError )
	{
		/* write config reg, set trigger */
		pxData->regmap.Config = TLE493D_AW2B6_Config_TRIG_R6;
		lError = TLE493D_AW2B6_lWriteReg( pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );
	}

	if( !lError )
	{
		/* read entire register map */
		lError = TLE493D_AW2B6_lReadRegs( pxData->IIC_addr, &(pxData->regmap), ( TLE493D_AW2B6_REGS_COUNT - 1 ) );
	}

	return lError;
}


void TLE493D_AW2B6_vResetAll( void )
{
	_I2C_recover();
	_I2C_recover();
	_I2C_reset();
	_I2C_reset();
}


int32_t TLE493D_AW2B6_lSetOperationMode( TLE493D_Data_t *pxData, TLV493D_OpMode_t xMode )
{
	int32_t lError;

	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	switch( xMode )
	{
		case TLx493D_OP_MODE_MCM:
			lError = prvSetOperationModeMCM( pxData );
			break;
		case TLx493D_OP_MODE_LOW_POWER:
			lError = _set_operation_mode_low_power( pxData );
			break;
		case TLx493D_OP_MODE_FAST:
			lError = _set_operation_mode_fast( pxData );
			break;
		default:
			lError = -1;
			break;
	}

	return lError;
}


int32_t TLE493D_AW2B6_lReadFrame( TLE493D_Data_t *pxData, TLx493D_DataFrame_t *pxFrame )
{
    TLx493D_DataFrameRaw_t xFrameRaw = { 0 };
    int32_t lRet = -1;

    if( TLE493D_AW2B6_lReadFrameRaw( pxData, &xFrameRaw ) == 0 )
    {
        pxFrame->x = (float)xFrameRaw.x * TLE493D_W2B6_B_MULT;
        pxFrame->y = (float)xFrameRaw.y * TLE493D_W2B6_B_MULT;
        pxFrame->z = (float)xFrameRaw.z * TLE493D_W2B6_B_MULT;

        pxFrame->temp = ( (float)xFrameRaw.temp - TLE493D_W2B6_TEMP_OFFSET ) * TLE493D_W2B6_TEMP_MULT + TLE493D_W2B6_TEMP_25;
        lRet = 0;
    }

    return lRet;
}


int32_t TLE493D_AW2B6_lReadFrameRaw( TLE493D_Data_t *pxData, TLx493D_DataFrameRaw_t *pxFrame )
{
	int16_t sXTemp, sYTemp, sZTemp, sTTemp;
	bool bFastMode;
	int32_t lError;
	uint8_t *pucRegs;

	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}

	/* check if in fast mode */
	bFastMode = ( TLx493D_OP_MODE_FAST == TLx493D_xGetOperationMode() );
	/* Read registers to local registers copy using the driver */
	if( bFastMode )
	{
		lError = TLE493D_AW2B6_lReadRegs(pxData->IIC_addr, &(pxData->regmap), TLE493D_AW2B6_Temp_REG );
	}
	else
	{
		lError = TLE493D_AW2B6_lReadRegs(pxData->IIC_addr, &(pxData->regmap), TLE493D_AW2B6_XL_REG );
	}
	/* convert data to frame if no error encountered */
	if( !lError )
	{
		pucRegs = (uint8_t *)&(pxData->regmap);
		/* extract data */
		sXTemp = (uint16_t)pucRegs[0] << 4;
		sYTemp = (uint16_t)pucRegs[1] << 4;
		sZTemp = (uint16_t)pucRegs[2] << 4;
		sTTemp = 0;
		/* also append the least significant bits */
		if( !bFastMode )
		{
			sXTemp |= (pucRegs[4] & 0xF0) >> 4;
			sYTemp |= (pucRegs[4] & 0x0F);
			sZTemp |= (pucRegs[5] & 0x0F);
			sTTemp = (uint16_t)( (uint16_t)pucRegs[3] << 4 ) | ( ( pucRegs[5] & ( 0x3U << 6 ) ) >> 4 );
		}
		/* Extend Bits for Signed Values */
		if( sXTemp & 0x800 )
		{
			sXTemp |= 0xF000;
		}
		if( sYTemp & 0x800 )
		{
			sYTemp |= 0xF000;
		}
		if( sZTemp & 0x800 )
		{
			sZTemp |= 0xF000;
		}
		/* copy data to frame */
		pxFrame->x = sXTemp;
		pxFrame->y = sYTemp;
		pxFrame->z = sZTemp;
		pxFrame->temp = sTTemp;
	}

	return lError;
}


int32_t TLE493D_AW2B6_lEnableWU( TLE493D_Data_t *pxData, uint16_t usWuXl, uint16_t usWuXh, uint16_t usWuYl, uint16_t usWuYh, uint16_t usWuZl, uint16_t usWuZh )
{
	int32_t lErrRd, lErrWr;

	/* use local data if none provided */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}

	/* prepare registers */
	pxData->regmap.XL = usWuXl >> 4;
	pxData->regmap.XH = usWuXh >> 4;
	pxData->regmap.YL = usWuYl >> 4;
	pxData->regmap.YH = usWuYh >> 4;
	pxData->regmap.ZL = usWuZl >> 4;
	pxData->regmap.ZH = usWuZh >> 4;
	/* set values and enable WU */
	pxData->regmap.WU = ((usWuXh << 2) & TLE493D_AW2B6_WU_XH_MSK)
			| ((usWuXl >> 1)  & TLE493D_AW2B6_WU_XL_MSK)
			| TLE493D_AW2B6_WU_WU_ENABLE;
	pxData->regmap.TMode  = ((usWuYh << 2) & TLE493D_AW2B6_TMode_YH_MSK)
			    | ((usWuYl >> 1)  & TLE493D_AW2B6_TMode_YL_MSK);
	pxData->regmap.TPhase = ((usWuZh << 2) & TLE493D_AW2B6_TPhase_ZH_MSK)
			    | ((usWuZl >> 1)  & TLE493D_AW2B6_TPhase_ZL_MSK);
	pxData->regmap.Config &= ~TLE493D_AW2B6_Config_CP_MSK;
	pxData->regmap.Config |= TLE493D_AW2B6_ucGetBitCP( pxData );

	/* write registers XL to Config from pxData->regmap */
	lErrWr = TLE493D_AW2B6_lWriteRegMulti(pxData->IIC_addr, TLE493D_AW2B6_XL_REG, (uint8_t*)&(pxData->regmap) + TLE493D_AW2B6_XL_REG, TLE493D_AW2B6_Config_REG - TLE493D_AW2B6_XL_REG + 1 );
	if( lErrWr )
	{
		return lErrWr;
	}

	lErrRd = TLE493D_AW2B6_lReadRegs( pxData->IIC_addr, &(pxData->regmap), TLE493D_AW2B6_Config_REG );

	if( lErrRd )
	{
		return lErrRd;
	}
	if( !(pxData->regmap.WU & TLE493D_AW2B6_WU_WA_MSK) )
	{
		return TLx493D_WU_ENABLE_FAIL;
	}

	return TLx493D_OK;
}


int32_t TLE493D_AW2B6_lDisableWU( TLE493D_Data_t *pxData )
{
	/* use local data if none provided */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* disable WU */
	pxData->regmap.WU &= ~TLE493D_AW2B6_WU_WU_MSK;
	pxData->regmap.WU |= TLE493D_AW2B6_WU_WU_DISABLE;
	/* set parity bit */
	pxData->regmap.Config &= TLE493D_AW2B6_Config_CP_MSK;
	pxData->regmap.Config |= TLE493D_AW2B6_ucGetBitCP(pxData);

	/* write registers WU and Config */
	TLE493D_AW2B6_lWriteRegMulti( pxData->IIC_addr, TLE493D_AW2B6_WU_REG, (uint8_t*)&(pxData->regmap) + TLE493D_AW2B6_WU_REG, TLE493D_AW2B6_Config_REG - TLE493D_AW2B6_WU_REG + 1 );
	/* optimized reading */
	_I2C_read( pxData->IIC_addr, (uint8_t*)&(pxData->regmap), TLE493D_AW2B6_Config_REG + 1 );

	/* read all registers up to TPhase */
	//TLE493D_AW2B6_lReadRegs(pxData->IIC_addr, &(pxData->regmap), TLE493D_AW2B6_Config_REG );

	return TLx493D_OK;
}


int32_t TLE493D_AW2B6_lSetSlaveAddressI2C( TLE493D_Data_t *pxData, TLE493D_Address_t ucSlaveAddressI2C )
{
	int32_t lError;

	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear I2C addr bits */
	pxData->regmap.MOD1 &= ~TLE493D_AW2B6_MOD1_IICadr_MSK;
	/* set new bit values */
	switch( ucSlaveAddressI2C )
	{
		case TLE493D_AW2B6_I2C_A0_ADDR:
			pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_IICadr_A0;
			break;
		case TLE493D_AW2B6_I2C_A1_ADDR:
			pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_IICadr_A1;
			break;
		case TLE493D_AW2B6_I2C_A2_ADDR:
			pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_IICadr_A2;
			break;
		case TLE493D_AW2B6_I2C_A3_ADDR:
			pxData->regmap.MOD1 |= TLE493D_AW2B6_MOD1_IICadr_A3;
			break;
		default:
			break;
	}
	/* get parity bit */
	pxData->regmap.MOD1 &= ~TLE493D_AW2B6_MOD1_FP_MSK;
	pxData->regmap.MOD1 |= ( TLE493D_AW2B6_ucGetBitFP( pxData ) ) << TLE493D_AW2B6_MOD1_FP_POS;
	/* write changes */
	lError = TLE493D_AW2B6_lWriteReg(pxData->IIC_addr, TLE493D_AW2B6_MOD1_REG, pxData->regmap.MOD1 );
	pxData->IIC_addr = ucSlaveAddressI2C;

	return lError;
}


int32_t TLE493D_AW2B6_lMagneticTmpComp( TLE493D_Data_t *pxData, TLE493D_MagneticComp_t xSens )
{
	int32_t lError;

	/* no sensor data provided, use local data */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear bits */
	pxData->regmap.Config &= ~(TLE493D_AW2B6_Config_TL_mag_MSK | TLE493D_AW2B6_Config_CP_MSK);
	/* set new value */
	pxData->regmap.Config |= (uint8_t)xSens;
	/* set parity */
	pxData->regmap.Config |= TLE493D_AW2B6_ucGetBitCP( pxData );
	/* write to sensor */
	lError = TLE493D_AW2B6_lWriteReg( pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );

	return lError;
}


int32_t TLE493D_AW2B6_lSetHighSensitivity( TLE493D_Data_t *pxData, bool bOn )
{
	int32_t lError;

	/* no sensor data provided, use local data */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear bits */
	pxData->regmap.Config &= ~(TLE493D_AW2B6_Config_X2_MSK | TLE493D_AW2B6_Config_CP_MSK);
	/* set new value */
	pxData->regmap.Config |= (uint8_t)( bOn ? TLE493D_AW2B6_Config_X2_DOUBLE : TLE493D_AW2B6_Config_X2_SIMPLE );
	/* set parity */
	pxData->regmap.Config |= TLE493D_AW2B6_ucGetBitCP( pxData );
	/* write to sensor */
	lError = TLE493D_AW2B6_lWriteReg( pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );

	return lError;
}


int32_t TLE493D_AW2B6_lSetAngleMode( TLE493D_Data_t *pxData, bool bOn )
{
	int32_t lError;

	/* no sensor data provided, use local data */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* check if the DT bit is set */
	if( 0U == ( pxData->regmap.Config & TLE493D_AW2B6_Config_DT_MSK ) )
	{
		/* DT bit not set (Temperature measurement not disabled) */
		return TLx493D_INVALID_SENSOR_STATE;
	}
	/* clear bits */
	pxData->regmap.Config &= ~(TLE493D_AW2B6_Config_AM_MSK | TLE493D_AW2B6_Config_CP_MSK);
	/* set new value */
	pxData->regmap.Config |= (uint8_t)( bOn ? TLE493D_AW2B6_Config_AM_DISABLE_BZ_MEASURE : TLE493D_AW2B6_Config_AM_ENABLE_BZ_MEASURE );
	/* set parity */
	pxData->regmap.Config |= TLE493D_AW2B6_ucGetBitCP( pxData );
	/* write to sensor */
	lError = TLE493D_AW2B6_lWriteReg(pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );
	if( !lError )
	{
		lError = TLE493D_AW2B6_lReadRegs(pxData->IIC_addr, &(pxData->regmap), TLE493D_AW2B6_Config_REG );
	}

	return lError;
}


int32_t TLE493D_AW2B6_lSetTempMeasure( TLE493D_Data_t *pxData, bool bOn )
{
	int32_t lError;

	/* no sensor data provided, use local data */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear bits */
	pxData->regmap.Config &= ~(TLE493D_AW2B6_Config_DT_MSK | TLE493D_AW2B6_Config_CP_MSK);
	/* set new value */
	pxData->regmap.Config |= (uint8_t)( bOn ? TLE493D_AW2B6_Config_DT_ENABLE : TLE493D_AW2B6_Config_DT_DISABLE );
	/* set parity */
	pxData->regmap.Config |= TLE493D_AW2B6_ucGetBitCP( pxData );
	/* write to sensor */
	lError = TLE493D_AW2B6_lWriteReg( pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );
	if( !lError )
	{
		lError = TLE493D_AW2B6_lReadRegs( pxData->IIC_addr, &(pxData->regmap), TLE493D_AW2B6_Config_REG );
	}

	return lError;
}


int32_t TLV493D_A1B6_lSetLPUpdateFrequency( TLE493D_Data_t *pxData, TLE493D_LpUpdateFreq_t xFreq )
{
	int32_t lError;

	/* no sensor data provided, use local data */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear parity bit */
	pxData->regmap.MOD1 &= ~(TLE493D_AW2B6_MOD1_FP_MSK);
	/* clear frequency bits */
	pxData->regmap.MOD2 &= ~(TLE493D_AW2B6_MOD2_PRD_MSK);
	/* set new value */
	pxData->regmap.MOD2 |= xFreq & TLE493D_AW2B6_MOD2_PRD_MSK;
	/* set parity bit */
	pxData->regmap.MOD1 |= TLE493D_AW2B6_ucGetBitFP( pxData ) << TLE493D_AW2B6_MOD1_FP_POS;
	/* write to sensor */
	lError = TLE493D_AW2B6_lWriteRegMulti( pxData->IIC_addr, TLE493D_AW2B6_MOD1_REG, (uint8_t*)&(pxData->regmap.MOD1), TLE493D_AW2B6_MOD2_REG - TLE493D_AW2B6_MOD1_REG + 1 );
	/* update local register copy */
	if( !lError )
	{
		lError = TLE493D_AW2B6_lReadRegs( pxData->IIC_addr, &(pxData->regmap), TLE493D_AW2B6_MOD2_REG );
	}

	return lError;
}


int32_t TLV493D_A1B6_lSetTriggerMode( TLE493D_Data_t *pxData, TLE493D_ConfigTriggerMode_t xMode )
{
	int32_t lError;

	/* no sensor data provided, use local data */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear bits */
	pxData->regmap.Config &= ~(TLE493D_AW2B6_Config_TRIG_MSK | TLE493D_AW2B6_Config_CP_MSK);
	/* set new value */
	pxData->regmap.Config |= (uint8_t)xMode;
	/* set parity */
	pxData->regmap.Config |= TLE493D_AW2B6_ucGetBitCP( pxData );
	/* write to sensor */
	lError = TLE493D_AW2B6_lWriteReg( pxData->IIC_addr, TLE493D_AW2B6_Config_REG, pxData->regmap.Config );
	if( !lError )
	{
		lError = TLE493D_AW2B6_lReadRegs( pxData->IIC_addr, &(pxData->regmap), TLE493D_AW2B6_Config_REG );
	}


	if( ( ( pxData->regmap.Config & TLE493D_AW2B6_Config_TRIG_MSK ) ) == xMode )
	{
		dbg_log("-- bits OK --\r\n");
	}
	else
	{
		dbg_log("-- bits FAIL --\r\n");
	}

	if( ( ( pxData->regmap.Diag & TLE493D_AW2B6_Diag_CF_MSK ) >> TLE493D_AW2B6_Diag_CF_POS ) == 1U )
	{
		dbg_log("-- parity OK --\r\n");
	}
	else
	{
		dbg_log("-- parity FAIL --\r\n");
	}


	return lError;
}


TLV493D_SensorType_t TLE493D_xGetHwVersion( TLE493D_Data_t *pxData )
{
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}

	/* identify HW version */
	if( ( pxData->regmap.Ver & TLE493D_AW2B6_Ver_HWV_MSK ) == TLE493D_AW2B6_Ver_HWV_B21 )
	{
		if( ( pxData->regmap.Ver & TLE493D_AW2B6_Ver_TYPE_MSK ) == 0 )
		{
		    dbg_log( ("HW: W2B6\r\n"));
			return TLx493D_TYPE_TLE_W2B6;
		}
		else
		{
		    dbg_log( ("HW: A2B6\r\n") );
			return TLx493D_TYPE_TLE_A2B6;
		}
	}

	dbg_log( ("HW: UNKNOWN\r\n") );

	return TLx493D_TYPE_UNKNOWN;
}


void TLE493D_AW2B6_vGetData( TLE493D_Data_t *pxDest )
{
	/* sanity check */
	if( NULL == pxDest )
	{
		return;
	}

	/* get data */
	*pxDest = LocalData.data;
}


int32_t TLE493D_AW2B6_lSetData( TLE493D_Data_t *pxSrc )
{
	int32_t lError;

	/* sanity check */
	if( NULL == pxSrc )
	{
		return TLx493D_INVALID_ARGUMENT;
	}

	/* write to sensor */
	lError = TLE493D_AW2B6_lWriteRegMulti( LocalData.data.IIC_addr, TLE493D_AW2B6_XL_REG, (uint8_t*)&(pxSrc->regmap.XL), TLE493D_AW2B6_MOD2_REG - TLE493D_AW2B6_XL_REG + 1 );
	if( 0 != lError )
	{
		return lError;
	}
	/* set data */
	LocalData.data = *pxSrc;

	/* no error */
	return TLx493D_OK;
}

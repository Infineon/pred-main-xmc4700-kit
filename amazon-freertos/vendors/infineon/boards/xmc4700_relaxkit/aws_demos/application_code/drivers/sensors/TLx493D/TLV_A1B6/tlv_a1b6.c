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

#include <stdint.h>

#include "tlv_a1b6.h"
#include "driver/tlv_a1b6_defines.h"
#include "driver/tlv_a1b6_driver.h"

#include "TLx493D/tlx493d.h"


#ifndef NULL
#define NULL ((void*) 0)
#endif

/* Local Data */

static struct {
	TLV493D_Data_t data;
} LocalData = {
	.data = { 0 },
};


/* Public */

int32_t TLV493D_A1B6_init( TLV493D_Data_t *pxData, bool bAddressHigh, TLV493D_Address_t xAddressType )
{
	int32_t lError;
	uint8_t ucAddressTemp = 0;

	/* use local data if no data struct provided */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}

	/* determine the sensor initial address */
	if( bAddressHigh )
	{
		pxData->IIC_addr = TLV493D_A1B6_I2C_DEFAULT_ADDR_HIGH;
	}
	else
	{
		pxData->IIC_addr = TLV493D_A1B6_I2C_DEFAULT_ADDR_LOW;
	}

	pxData->ADDR_high = bAddressHigh;
	pxData->frame_count = 10;
	/* copy state of read registers in local memory (used for write registers) */
	lError = TLV493D_A1B6_lReadRegs( pxData->IIC_addr, &(pxData->regmap_read), TLV493D_A1B6_READ_REGS_COUNT-1 );
	if( !lError )
	{
		/* prepare register values to be written
		 * initial configuration for POWER DOWN mode, INT disabled
		 * */
		pxData->regmap_write.MOD1 &= ~(TLV493D_A1B6_MOD1_IICAddr_MSK
						| TLV493D_A1B6_MOD1_INT_MSK
						| TLV493D_A1B6_MOD1_FAST_MSK
						| TLV493D_A1B6_MOD1_LOW_MSK);
		pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_INT_DISABLE
					   | TLV493D_A1B6_MOD1_FAST_DISABLE
					   | TLV493D_A1B6_MOD1_LOW_DISABLE;
		/* add address bits */
		pxData->addr_type = xAddressType;
		switch( xAddressType )
		{
			case TLV493D_A1B6_ADDR_3E_BC:
				pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_IICAddr_3E_BC;
				ucAddressTemp = (!bAddressHigh ? 0x3EU : 0xBCU);
				break;

			case TLV493D_A1B6_ADDR_36_B4:
				pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_IICAddr_36_B4;
				ucAddressTemp = (!bAddressHigh ? 0x36U : 0xB4U);
				break;

			case TLV493D_A1B6_ADDR_1E_9C:
				pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_IICAddr_1E_9C;
				ucAddressTemp = (!bAddressHigh ? 0x1EU : 0x9CU);
				break;

			case TLV493D_A1B6_ADDR_16_94:
				pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_IICAddr_16_94;
				ucAddressTemp = (!bAddressHigh ? 0x16U : 0x94U);
				break;
			default:
				return TLx493D_INVALID_ARGUMENT;
		}

		/* temperature measurement enabled
		 * low power mode instead of ultra-low power mode
		 * Parity test disabled for future writes
		 * */
		pxData->regmap_write.MOD2 &= ~(TLV493D_A1B6_MOD2_T_MSK
					 | TLV493D_A1B6_MOD2_LP_MSK
					 | TLV493D_A1B6_MOD2_PT_MSK);
		pxData->regmap_write.MOD2 |= TLV493D_A1B6_MOD2_T_ENABLE
					 | TLV493D_A1B6_MOD2_LP_LOW_POWER
					 | TLV493D_A1B6_MOD2_PT_DISABLE;
		/* write changes to sensor */
		lError = TLV493D_A1B6_lWriteRegs(pxData->IIC_addr, &(pxData->regmap_write), &(pxData->regmap_read) );
	}
	/* mark initialization as completed successfully */
	if( !lError )
	{
		pxData->IIC_addr = ucAddressTemp;
	}

	return lError;
}


int32_t TLV493D_A1B6_set_operation_mode( TLV493D_Data_t *pxData, TLV493D_OpMode_t xMode )
{
	int32_t lError = 0;

	/* use local data if no data struct provided */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear the mode bits */
	pxData->regmap_write.MOD1 &= ~(TLV493D_A1B6_MOD1_INT_MSK
					| TLV493D_A1B6_MOD1_FAST_MSK
					| TLV493D_A1B6_MOD1_LOW_MSK);
	/* set bits and enable/disable interrupt handing */
	switch( xMode )
	{
		case TLx493D_OP_MODE_MCM:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_INT_DISABLE
						  | TLV493D_A1B6_MOD1_FAST_ENABLE
						  | TLV493D_A1B6_MOD1_LOW_ENABLE;
			break;
		case TLx493D_OP_MODE_ULTRA_LOW_POWER:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_INT_ENABLE
						  | TLV493D_A1B6_MOD1_FAST_DISABLE
						  | TLV493D_A1B6_MOD1_LOW_ENABLE;
			pxData->regmap_write.MOD2 &= ~(TLV493D_A1B6_MOD2_LP_MSK);
			pxData->regmap_write.MOD2 |= TLV493D_A1B6_MOD2_LP_ULTRA_LOW_POWER;
			break;
		case TLx493D_OP_MODE_LOW_POWER:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_INT_ENABLE
						  | TLV493D_A1B6_MOD1_FAST_DISABLE
						  | TLV493D_A1B6_MOD1_LOW_ENABLE;
			pxData->regmap_write.MOD2 &= ~(TLV493D_A1B6_MOD2_LP_MSK);
			pxData->regmap_write.MOD2 |= TLV493D_A1B6_MOD2_LP_LOW_POWER;
			break;
		case TLx493D_OP_MODE_FAST:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_INT_ENABLE
						  | TLV493D_A1B6_MOD1_FAST_ENABLE
						  | TLV493D_A1B6_MOD1_LOW_DISABLE;
			break;
		case TLx493D_OP_MODE_POWER_DOWN:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_INT_DISABLE
						  | TLV493D_A1B6_MOD1_FAST_DISABLE
						  | TLV493D_A1B6_MOD1_LOW_DISABLE;
			break;
		default:
			/* execute the error sequence */
			return lError;
	}
	/* write registers (do not correct reserved data,
	 * already corrected on initialization) */
	lError = TLV493D_A1B6_lWriteRegs(pxData->IIC_addr, &(pxData->regmap_write), NULL );
	if( lError )
	{
		return lError;
	}

	/* EXIT function - success */
	return 0;
}


void TLV493D_A1B6_hard_reset_reconfigure( TLV493D_Data_t *pxData )
{
	/* use local data if no data struct provided */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* power-cycle the sensor on kit */
	_POWER_DISABLE();
	_POWER_ENABLE();
	/* set desired logic level on ADDR pin and wait at least 200us */
	_SET_ADDR_AND_WAIT( pxData->ADDR_high );
	/* reinitialize sensor */
	TLV493D_A1B6_init( pxData, pxData->ADDR_high, pxData->addr_type );
}


int32_t TLV493D_A1B6_read_frame( TLV493D_Data_t *pxData, TLx493D_DataFrame_t *pxFrame )
{
	return 0;
}


int32_t TLV493D_A1B6_read_frame_raw( TLV493D_Data_t *pxData, TLx493D_DataFrameRaw_t *pxFrame )
{
	uint8_t ucNewFrameCount;
	int16_t sXTemp, sYTemp, sZTemp, sTemperature;
	uint8_t *pucRegs;
	bool bFastMode;
	int32_t lError;

	/* use local data if no data struct provided  */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* is fast mode? */
	bFastMode = ( TLx493D_OP_MODE_FAST == TLx493D_xGetOperationMode() );
	/* read registers */
	lError = TLV493D_A1B6_lReadRegs(pxData->IIC_addr, &(pxData->regmap_read), TLV493D_A1B6_Temp2_REG );
	if( lError )
	{
		return lError;
	}
	/* cast register map to uint8_t array */
	pucRegs = (uint8_t *)&(pxData->regmap_read);
	/* extract data */
	//ucNewFrameCount = (pucRegs[3] & 0xC) >> 2;
	sXTemp = ((uint16_t)pucRegs[0] << 4);
	sYTemp = ((uint16_t)pucRegs[1] << 4);
	sZTemp = ((uint16_t)pucRegs[2] << 4);
	/* if not in fast mode, include supplementary data */
	if( !bFastMode )
	{
		sXTemp |= (pucRegs[4] & 0xF0) >> 4;
		sYTemp |= pucRegs[4] & 0x0F;
		sZTemp |= pucRegs[5] & 0x0F;
		sTemperature = ((uint16_t)(pucRegs[3] & 0xF0) << 4) + pucRegs[6];
	}
	/* Method for detecting an lock of the IC according to Early Problem Notification */
	/* if framecounter has not incremented -> reset sensor */
	ucNewFrameCount = (pucRegs[TLV493D_A1B6_Temp_REG] & TLV493D_A1B6_Temp_FRM_MSK) >> TLV493D_A1B6_Temp_FRM_POS;
	if( ucNewFrameCount == pxData->frame_count )
	{
		/* reset and reconfigure the sensor */
		TLV493D_A1B6_hard_reset_reconfigure( pxData );
		pxData->frame_count = 10;
		/* invalidate frame */
		return TLx493D_INVALID_FRAME;
	}
	else
	{
		/* save new frame counter */
		pxData->frame_count = ucNewFrameCount;
	}
	/* Extend Bits for Signed Values  */
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
	pxFrame->temp = sTemperature;

	/* change with a define NO_ERROR */
	return 0;
}


int32_t TLV493D_A1B6_set_temp_measure( TLV493D_Data_t *pxData, bool bEnabled )
{
	int32_t lError;

	/* use local data if no data struct provided */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear bit */
	pxData->regmap_write.MOD2 &= ~TLV493D_A1B6_MOD2_T_MSK;
	/* set bit value */
	if( bEnabled )
	{
		pxData->regmap_write.MOD2 |= TLV493D_A1B6_MOD2_T_ENABLE;
	}
	else
	{
		pxData->regmap_write.MOD2 |= TLV493D_A1B6_MOD2_T_DISABLE;
	}
	/* write changes to the sensor */
	lError = TLV493D_A1B6_lWriteRegs(pxData->IIC_addr, &(pxData->regmap_write), NULL );

	return lError;
}


int32_t TLV493D_A1B6_set_parity_test( TLV493D_Data_t *pxData, bool bEnabled )
{
	int32_t lError;

	/* use local data if no data struct provided */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	/* clear bit */
	pxData->regmap_write.MOD2 &= ~TLV493D_A1B6_MOD2_T_MSK;
	/* set bit value */
	if( bEnabled )
	{
		pxData->regmap_write.MOD2 |= TLV493D_A1B6_MOD2_PT_ENABLE;
	}
	else
	{
		pxData->regmap_write.MOD2 |= TLV493D_A1B6_MOD2_PT_DISABLE;
	}
	/* write changes to the sensor */
	lError = TLV493D_A1B6_lWriteRegs(pxData->IIC_addr, &(pxData->regmap_write), NULL );

	return lError;
}


int32_t TLV493D_A1B6_set_IIC_address( TLV493D_Data_t *pxData, TLV493D_Address_t xNewAddressType )
{
	uint8_t ucAddressTemp;
	int32_t lError;

	/* use local data if no data structure provided */
	if( NULL == pxData )
	{
		pxData = &(LocalData.data);
	}
	pxData->regmap_write.MOD1 &= ~TLV493D_A1B6_MOD1_IICAddr_MSK;
	/* add address bits */
	switch( xNewAddressType )
	{
		case TLV493D_A1B6_ADDR_3E_BC:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_IICAddr_3E_BC;
			ucAddressTemp = (!pxData->ADDR_high ? 0x3EU : 0xBCU);
			break;
		case TLV493D_A1B6_ADDR_36_B4:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_IICAddr_36_B4;
			ucAddressTemp = (!pxData->ADDR_high ? 0x36U : 0xB4U);
			break;
		case TLV493D_A1B6_ADDR_1E_9C:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_IICAddr_1E_9C;
			ucAddressTemp = (!pxData->ADDR_high ? 0x1EU : 0x9CU);
			break;
		case TLV493D_A1B6_ADDR_16_94:
			pxData->regmap_write.MOD1 |= TLV493D_A1B6_MOD1_IICAddr_16_94;
			ucAddressTemp = (!pxData->ADDR_high ? 0x16U : 0x94U);
			break;
		default:
			return TLx493D_INVALID_ARGUMENT;
	}

	/* write changes to sensor */
	lError = TLV493D_A1B6_lWriteRegs(pxData->IIC_addr, &(pxData->regmap_write), NULL );
	/* mark update process as completed successfully */
	if( !lError )
	{
		pxData->IIC_addr = ucAddressTemp;
	}

	return lError;
}


void TLV493D_A1B6_get_data( TLV493D_Data_t *pxDest )
{
	/* sanity check */
	if( NULL == pxDest )
	{
		return;
	}

	/* get data */
	*pxDest = LocalData.data;
}


int32_t TLV493D_A1B6_set_data( TLV493D_Data_t *pxSrc )
{
	int32_t lError;

	/* sanity check */
	if( NULL == pxSrc )
	{
		return TLx493D_INVALID_ARGUMENT;
	}

	/* write to sensor */
	lError = TLV493D_A1B6_lWriteRegs(LocalData.data.IIC_addr, &(pxSrc->regmap_write), &(pxSrc->regmap_read) );
	if( 0 != lError )
	{
		return lError;
	}
	/* set data */
	LocalData.data = *pxSrc;
	LocalData.data.frame_count = 10;

	return TLx493D_OK;
}

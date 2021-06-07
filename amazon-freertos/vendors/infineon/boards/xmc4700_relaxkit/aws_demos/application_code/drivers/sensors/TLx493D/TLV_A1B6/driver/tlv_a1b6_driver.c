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

#include "TLV_A1B6_driver.h"
#include "TLx493D/tlx493d.h"


#ifndef NULL
#define NULL ( (void*) 0 )
#endif


int32_t TLV493D_A1B6_lReadRegs( uint8_t ucAddress, TLV493D_RegMapRead_t *pxRegMap, uint8_t ucUpTo )
{
	int32_t lError;

	/* read the registers from the sensor */
	lError = _I2C_read( ucAddress, (uint8_t*)pxRegMap, ucUpTo + 1 );

	return lError;
}


int32_t TLV493D_A1B6_lWriteRegs( uint8_t ucAddress, TLV493D_RegMapWrite_t *pxRegMap, const TLV493D_RegMapRead_t *pxRegMapCheck )
{
	int32_t lError;
	uint8_t ucParity;

	/* sanity check */
	if( NULL == pxRegMap )
	{
		return TLx493D_INVALID_ARGUMENT;
	}
	/* correct reserved data */
	if( NULL != pxRegMapCheck )
	{
		/* Reg should be 0 */
		((uint8_t *)pxRegMap)[TLV493D_A1B6_Res_REG] = 0U;
		/* MOD1 Reserved data should contain bits 4:3 or register */
		((uint8_t *)pxRegMap)[TLV493D_A1B6_MOD1_REG]
					= (((uint8_t *)pxRegMap)[TLV493D_A1B6_MOD1_REG] & ~TLV493D_A1B6_MOD1_Reserved_MSK)
					| (((uint8_t *)pxRegMapCheck)[TLV493D_A1B6_FactSet1_REG] & TLV493D_A1B6_MOD1_Reserved_MSK);
		((uint8_t *)pxRegMap)[TLV493D_A1B6_Res2_REG] = ((uint8_t *)pxRegMapCheck)[TLV493D_A1B6_FactSet2_REG];
		((uint8_t *)pxRegMap)[TLV493D_A1B6_MOD2_REG] = (((uint8_t *)pxRegMap)[TLV493D_A1B6_MOD2_REG] & ~TLV493D_A1B6_MOD2_Reserved_MSK)
							   | (((uint8_t *)pxRegMapCheck)[TLV493D_A1B6_FactSet3_REG] & TLV493D_A1B6_MOD2_Reserved_MSK);
	}
	/* reset parity bit */
	((uint8_t *)pxRegMap)[TLV493D_A1B6_MOD1_REG] &= ~ TLV493D_A1B6_MOD1_P_MSK;
	/* compute EVEN parity bit */
	ucParity = MISC_get_parity( ((uint8_t *)pxRegMap)[TLV493D_A1B6_Res_REG] );
	ucParity ^= MISC_get_parity( ((uint8_t *)pxRegMap)[TLV493D_A1B6_MOD1_REG] );
	ucParity ^= MISC_get_parity( ((uint8_t *)pxRegMap)[TLV493D_A1B6_Res2_REG] );
	ucParity ^= MISC_get_parity( ((uint8_t *)pxRegMap)[TLV493D_A1B6_MOD2_REG] );
	/* compute ODD parity */
	ucParity ^= 1;
	/* add parity to register */
	((uint8_t *)pxRegMap)[TLV493D_A1B6_MOD1_REG] |= ( ucParity << TLV493D_A1B6_MOD1_P_POS ) & TLV493D_A1B6_MOD1_P_MSK;
	/* write data to sensor */
	lError = _I2C_write( ucAddress, (uint8_t*)pxRegMap, TLV493D_A1B6_WRITE_REGS_COUNT );

	return lError;
}

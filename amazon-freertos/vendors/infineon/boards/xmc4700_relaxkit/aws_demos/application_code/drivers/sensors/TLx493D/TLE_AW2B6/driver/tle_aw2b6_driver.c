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
#include <string.h>

#include "TLx493D/tlx493d_interface.h"
#include "TLE_AW2B6_defines.h"
#include "TLE_AW2B6_driver.h"
#include "TLx493D/tlx493d.h"


#ifndef NULL
#define NULL ( (void*)0 )
#endif


int32_t TLE493D_AW2B6_lReadRegs( uint8_t ucSlaveAddressI2C, TLE493D_Regmap_t *pxRegMap, uint8_t ucUpTo )
{
	int32_t lError;

	/* sanity checks */
	if( NULL == pxRegMap )
	{
		return TLx493D_INVALID_ARGUMENT;
	}
	if( ucUpTo > ( TLE493D_AW2B6_REGS_COUNT - 1 ) )
	{
		return TLx493D_INVALID_ARGUMENT;
	}
	/* read all registers */
	lError = _I2C_read( ucSlaveAddressI2C, (uint8_t*)pxRegMap, ucUpTo + 1 );

	return lError;
}


int32_t TLE493D_AW2B6_lWriteReg( uint8_t ucSlaveAddressI2C, uint8_t ucRegAddr, uint8_t ucData )
{
	int32_t lError;
	uint8_t ucBuffer[2];

	ucBuffer[0] = ucRegAddr;
	ucBuffer[1] = ucData;
	/* send register address and new value */
	lError = _I2C_write( ucSlaveAddressI2C, ucBuffer, 2U );

	return lError;
}


int32_t TLE493D_AW2B6_lWriteRegMulti( uint8_t ucSlaveAddressI2C, uint8_t ucRegAddrStart, uint8_t *pucData, uint8_t ucCount )
{
	int32_t lError;
	uint8_t ucBuffer[TLE493D_AW2B6_REGS_COUNT + 1];

	/* copy data to buffer */
	ucBuffer[0] = ucRegAddrStart;
	memcpy( ucBuffer + 1, pucData, ucCount );

	lError = _I2C_write( ucSlaveAddressI2C, ucBuffer, ucCount + 1 );

	return lError;
}

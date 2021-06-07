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

#include "RegMask.h"


uint8_t ucGetFromRegs( const RegMask_t *pxMask, uint8_t *pucRegData )
{
	return ( pucRegData[pxMask->byteAdress] & pxMask->bitMask ) >> pxMask->shift;
}


uint8_t ucSetToRegs( const RegMask_t *pxMask, uint8_t *pucRegData, uint8_t ucToWrite )
{
	if( pxMask->rw == REGMASK_WRITE )
	{
		uint8_t regValue = pucRegData[pxMask->byteAdress];

		regValue &= ~ ( pxMask->bitMask );
		regValue |= ( ucToWrite << pxMask->shift ) & pxMask->bitMask;
		pucRegData[pxMask->byteAdress] = regValue;
	}

	return 0;
}

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

#ifndef TLV493D_REGMASK_H
#define TLV493D_REGMASK_H

#include <stdbool.h>
#include <stdint.h>

#define REGMASK_READ	( 0 )
#define REGMASK_WRITE	( 1 )


typedef struct RegMask_ {
	uint8_t rw;
	uint8_t byteAdress;
	uint8_t bitMask;
	uint8_t shift;

} RegMask_t;


uint8_t ucGetFromRegs( const RegMask_t *pxMask, uint8_t *pucRegData );
uint8_t ucSetToRegs( const RegMask_t *pxMask, uint8_t *pucRegData, uint8_t ucToWrite );


#endif /* TLV493D_REGMASK_H */

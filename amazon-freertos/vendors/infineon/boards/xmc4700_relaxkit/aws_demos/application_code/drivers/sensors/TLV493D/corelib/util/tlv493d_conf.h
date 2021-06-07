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

#ifndef TLV493D_CONF_H
#define TLV493D_CONF_H

#include "RegMask.h"


#define TLV493D_DEFAULTMODE				( FAST_MODE )

#define TLV493D_STARTUP_DELAY			( 40 )
#define TLV493D_RESET_DELAY				( 60 )

#define TLV493D_NUM_OF_REGMASKS			( 25 )
#define TLV493D_NUM_OF_ACCMODES			( 5 )

#define TLV493D_MEASUREMENT_READOUT		( 7 )
#define TLV493D_FAST_READOUT			( 3 )

#define TLV493D_B_MULT 					( 0.098 )
#define TLV493D_TEMP_MULT 				( 1.1 )
#define TLV493D_TEMP_OFFSET 			( 315 )


typedef struct {
	uint8_t fast;
	uint8_t lp;
	uint8_t lpPeriod;
	uint16_t measurementTime;

} AccessMode_t;


enum Registers_e {
	R_BX1 = 0,
	R_BX2, 
	R_BY1, 
	R_BY2, 
	R_BZ1, 
	R_BZ2, 
	R_TEMP1, 
	R_TEMP2, 
	R_FRAMECOUNTER, 
	R_CHANNEL,
	R_POWERDOWNFLAG, 
	R_RES1,
	R_RES2,
	R_RES3,
	W_PARITY,
	W_ADDR,
	W_INT,
	W_FAST,
	W_LOWPOWER,
	W_TEMP_NEN,
	W_LP_PERIOD,
	W_PARITY_EN,
	W_RES1,
	W_RES2,
	W_RES3
};


extern const AccessMode_t accModes[];
extern const RegMask_t regMasks[];


#endif /* TLV493D_CONF_H */

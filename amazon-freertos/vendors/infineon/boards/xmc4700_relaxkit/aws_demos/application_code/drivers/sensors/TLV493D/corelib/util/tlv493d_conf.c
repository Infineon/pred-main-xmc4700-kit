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

#include "tlv493d_conf.h"


const AccessMode_t accModes[] = {
		{ 0, 0, 0, 1000 },				/* POWER_DOWN_MODE */
		{ 1, 0, 0, 0 },					/* FAST_MODE */
		{ 0, 1, 1, 10 },				/* LOW_POWER_MODE */
		{ 0, 1, 0, 100 },				/* ULTRA_LOW_POWER_MODE */
		{ 1, 1, 1, 10 }					/* MASTER_CONTROLLED_MODE */
};


const RegMask_t regMasks[] = {
	{ REGMASK_READ, 0, 0xFF, 0 },		/* R_BX1 */
	{ REGMASK_READ, 4, 0xF0, 4 },		/* R_BX2 */
	{ REGMASK_READ, 1, 0xFF, 0 },		/* R_BY1 */
	{ REGMASK_READ, 4, 0x0F, 0 },		/* R_BY2 */
	{ REGMASK_READ, 2, 0xFF, 0 },		/* R_BZ1 */
	{ REGMASK_READ, 5, 0x0F, 0 },		/* R_BZ2 */
	{ REGMASK_READ, 3, 0xF0, 4 },		/* R_TEMP1 */
	{ REGMASK_READ, 6, 0xFF, 0 },		/* R_TEMP2 */
	{ REGMASK_READ, 3, 0x0C, 2 },		/* R_FRAMECOUNTER */
	{ REGMASK_READ, 3, 0x03, 0 },		/* R_CHANNEL */
	{ REGMASK_READ, 5, 0x10, 4 },		/* R_POWERDOWNFLAG */
	{ REGMASK_READ, 7, 0x18, 3 },		/* R_RES1 */
	{ REGMASK_READ, 8, 0xFF, 0 },		/* R_RES2 */
	{ REGMASK_READ, 9, 0x1F, 0 },		/* R_RES3 */
	{ REGMASK_WRITE, 1, 0x80, 7 },		/* W_PARITY */
	{ REGMASK_WRITE, 1, 0x60, 5 },		/* W_ADDR */
	{ REGMASK_WRITE, 1, 0x04, 2 },		/* W_INT */
	{ REGMASK_WRITE, 1, 0x02, 1 },		/* W_FAST */
	{ REGMASK_WRITE, 1, 0x01, 0 },		/* W_LOWPOWER */
	{ REGMASK_WRITE, 3, 0x80, 7 },		/* W_TEMP_EN */
	{ REGMASK_WRITE, 3, 0x40, 6 },		/* W_LOWPOWER */
	{ REGMASK_WRITE, 3, 0x20, 5 },		/* W_POWERDOWN */
	{ REGMASK_WRITE, 1, 0x18, 3 },		/* W_RES1 */
	{ REGMASK_WRITE, 2, 0xFF, 0 },		/* W_RES2 */
	{ REGMASK_WRITE, 3, 0x1F, 0 }		/* W_RES3 */
};

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

#ifndef TLV_A1B6_DEFINES_H
#define TLV_A1B6_DEFINES_H

#include <stdint.h>


/* Sensor I2C addresses */
#define TLV493D_A1B6_I2C_RESET_ADDR				( 0x00U )
#define TLV493D_A1B6_I2C_RECOV_ADDR				( 0xFFU )
#define TLV493D_A1B6_I2C_DEFAULT_ADDR_HIGH		( 0xBCU )
#define TLV493D_A1B6_I2C_DEFAULT_ADDR_LOW		( 0x3EU )

/* Read registers */

/* the number of readable registers of the TLV493D-A1B6 sensor */
#define TLV493D_A1B6_READ_REGS_COUNT 			( 0x0AU )

/* Bx */
#define TLV493D_A1B6_Bx_REG						( 0x0U )

/* By */
#define TLV493D_A1B6_By_REG						( 0x1U )

/* Bz */
#define TLV493D_A1B6_Bz_REG						( 0x2U )

/* Temp Register */
#define TLV493D_A1B6_Temp_REG					( 0x3U )
#define TLV493D_A1B6_Temp_Temp_POS				( 0x4U )
#define TLV493D_A1B6_Temp_Temp_MSK				( 0xFU << 4 )
#define TLV493D_A1B6_Temp_FRM_POS				( 0x2U )
#define TLV493D_A1B6_Temp_FRM_MSK				( 0x3U << 2 )
#define TLV493D_A1B6_Temp_CH_POS				( 0x0U )
#define TLV493D_A1B6_Temp_CH_MSK				( 0x3U )

/* Bx2 Register */
#define TLV493D_A1B6_Bx2_REG					( 0x4U )

#define TLV493D_A1B6_Bx2_Bx_POS					( 0x4U )
#define TLV493D_A1B6_Bx2_Bx_MSK					( 0xFU << 4 )

#define TLV493D_A1B6_Bx2_By_POS					( 0x0U )
#define TLV493D_A1B6_Bx2_By_MSK					( 0xFU )

/* Bz2 Register */
#define TLV493D_A1B6_Bz2_REG					( 0x5U )

#define TLV493D_A1B6_Bz2_Reserved_POS			( 0x7U )
#define TLV493D_A1B6_Bz2_Reserved_MSK			( 0x1U << 7 )

#define TLV493D_A1B6_Bz2_T_POS					( 0x6U )
#define TLV493D_A1B6_Bz2_T_MSK					( 0x1U << 6 )
#define TLV493D_A1B6_Bz2_F_POS					( 0x5U )
#define TLV493D_A1B6_Bz2_F_MSK					( 0x1U << 5 )

#define TLV493D_A1B6_Bz2_PD_POS					( 0x4U )
#define TLV493D_A1B6_Bz2_PD_MSK					( 0x1U << 4 )

#define TLV493D_A1B6_Bz2_Bz_POS					( 0x0U )
#define TLV493D_A1B6_Bz2_Bz_MSK					( 0xFU )

/* Temp2 Register */
#define TLV493D_A1B6_Temp2_REG					( 0x6U )
#define TLV493D_A1B6_Temp2_Temp_POS				( 0x0U )
#define TLV493D_A1B6_Temp2_Temp_MSK				( 0xFF )

/* FactSet1 Register */
#define TLV493D_A1B6_FactSet1_REG				( 0x7U )
#define TLV493D_A1B6_FaceSet1_Reserved_POS		( 0x0U )
#define TLV493D_A1B6_FaceSet1_Reserved_MSK		( 0xFF )

/* FactSet2 Register */
#define TLV493D_A1B6_FactSet2_REG				( 0x8U )
#define TLV493D_A1B6_FaceSet2_Reserved_POS		( 0x0U )
#define TLV493D_A1B6_FaceSet2_Reserved_MSK		( 0xFF )

/* FactSet3 Register */
#define TLV493D_A1B6_FactSet3_REG				( 0x9U )
#define TLV493D_A1B6_FaceSet3_Reserved_POS		( 0x0U )
#define TLV493D_A1B6_FaceSet3_Reserved_MSK		( 0xFF )


/* Write registers */

/* the number of writable registers of the TLV493D-A1B6 sensor */
#define TLV493D_A1B6_WRITE_REGS_COUNT			( 0x04U )

/* Res Register */
#define TLV493D_A1B6_Res_REG					( 0x0U )
#define TLV493D_A1B6_Res_Reserved_POS			( 0x0U )
#define TLV493D_A1B6_Res_Reserved_MSK			( 0xFF )

/* MOD1 Register */
#define TLV493D_A1B6_MOD1_REG					( 0x1U )

#define TLV493D_A1B6_MOD1_P_POS					( 0x7U )
#define TLV493D_A1B6_MOD1_P_MSK					( 0x1U << 7 )

#define TLV493D_A1B6_MOD1_IICAddr_POS			( 0x5U )
#define TLV493D_A1B6_MOD1_IICAddr_MSK			( 0x3U << 5 )
#define TLV493D_A1B6_MOD1_IICAddr_16_94			( 0x3U << 5 )
#define TLV493D_A1B6_MOD1_IICAddr_1E_9C			( 0x2U << 5 )
#define TLV493D_A1B6_MOD1_IICAddr_36_B4			( 0x1U << 5 )
#define TLV493D_A1B6_MOD1_IICAddr_3E_BC			( 0x0U << 5 )

#define TLV493D_A1B6_MOD1_Reserved_POS			( 0x3U )
#define TLV493D_A1B6_MOD1_Reserved_MSK			( 0x3U << 3 )

#define TLV493D_A1B6_MOD1_INT_POS				( 0x2U )
#define TLV493D_A1B6_MOD1_INT_MSK				( 0x1U << 2 )
#define TLV493D_A1B6_MOD1_INT_ENABLE			( 0x1U << 2 )
#define TLV493D_A1B6_MOD1_INT_DISABLE			( 0x0U << 2 )

#define TLV493D_A1B6_MOD1_FAST_POS				( 0x1U )
#define TLV493D_A1B6_MOD1_FAST_MSK				( 0x1U << 1 )
#define TLV493D_A1B6_MOD1_FAST_ENABLE			( 0x1U << 1 )
#define TLV493D_A1B6_MOD1_FAST_DISABLE			( 0x0U << 1 )

#define TLV493D_A1B6_MOD1_LOW_POS				( 0x0U )
#define TLV493D_A1B6_MOD1_LOW_MSK				( 0x1U )
#define TLV493D_A1B6_MOD1_LOW_ENABLE			( 0x1U )
#define TLV493D_A1B6_MOD1_LOW_DISABLE			( 0x0U )

/* Res2 Register */
#define TLV493D_A1B6_Res2_REG					( 0x2U )
#define TLV493D_A1B6_Res2_Reserved_POS			( 0x0U )
#define TLV493D_A1B6_Res2_Reserved_MSK			( 0xFF )

/* MOD2 Register */
#define TLV493D_A1B6_MOD2_REG					( 0x3U )

#define TLV493D_A1B6_MOD2_T_POS					( 0x7U )
#define TLV493D_A1B6_MOD2_T_MSK					( 0x1U << 7 )
#define TLV493D_A1B6_MOD2_T_DISABLE				( 0x1U << 7 )
#define TLV493D_A1B6_MOD2_T_ENABLE				( 0x0U << 7 )

#define TLV493D_A1B6_MOD2_LP_POS				( 0x6U )
#define TLV493D_A1B6_MOD2_LP_MSK				( 0x1U << 6 )
#define TLV493D_A1B6_MOD2_LP_ULTRA_LOW_POWER	( 0x0U << 6 )
#define TLV493D_A1B6_MOD2_LP_LOW_POWER			( 0x1U << 6 )

#define TLV493D_A1B6_MOD2_PT_POS				( 0x5U )
#define TLV493D_A1B6_MOD2_PT_MSK				( 0x1U << 5 )
#define TLV493D_A1B6_MOD2_PT_DISABLE			( 0x0U << 5 )
#define TLV493D_A1B6_MOD2_PT_ENABLE				( 0x1U << 5 )

#define TLV493D_A1B6_MOD2_Reserved_POS			( 0x0U )
#define TLV493D_A1B6_MOD2_Reserved_MSK			( 0x1FU )


#endif /* TLV_A1B6_DEFINES_H */

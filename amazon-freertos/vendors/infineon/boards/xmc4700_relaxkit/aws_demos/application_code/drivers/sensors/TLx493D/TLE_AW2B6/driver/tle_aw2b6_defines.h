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

#ifndef TLE_AW2B6_DEFINES_H
#define TLE_AW2B6_DEFINES_H


/* TLE493D AW2B6 Registers */

/* the number of readable registers of the TLE493D-A2B6 or -W2B6 sensor */
#define TLE493D_AW2B6_REGS_COUNT 		( 0x16U + 1U )
/* Bx */
#define TLE493D_AW2B6_Bx_REG			( 0x00U )
/* By */
#define TLE493D_AW2B6_By_REG			( 0x01U )
/* Bz */
#define TLE493D_AW2B6_Bz_REG			( 0x02U )
/* Temp */
#define TLE493D_AW2B6_Temp_REG			( 0x03U )
/* Bx2 */
#define TLE493D_AW2B6_Bx2_REG			( 0x04U )
/* Temp2 */
#define TLE493D_AW2B6_Temp2_REG			( 0x05U )
/* Diag */
#define TLE493D_AW2B6_Diag_REG			( 0x06U )
#define TLE493D_AW2B6_Diag_P_MSK		( 1U << 7 )
#define TLE493D_AW2B6_Diag_P_POS		( 7U )
#define TLE493D_AW2B6_Diag_FF_MSK		( 1U << 6 )
#define TLE493D_AW2B6_Diag_FF_POS		( 6U )
#define TLE493D_AW2B6_Diag_CF_MSK		( 1U << 5 )
#define TLE493D_AW2B6_Diag_CF_POS		( 5U )
#define TLE493D_AW2B6_Diag_T_MSK		( 1U << 4 )
#define TLE493D_AW2B6_Diag_T_POS		( 4U )
#define TLE493D_AW2B6_Diag_PD3_MSK		( 1U << 3 )
#define TLE493D_AW2B6_Diag_PD3_POS		( 3U )
#define TLE493D_AW2B6_Diag_PD0_MSK		( 1U << 2 )
#define TLE493D_AW2B6_Diag_PD0_POS		( 2U )
#define TLE493D_AW2B6_Diag_FRM_MSK		( 3U << 0 )
#define TLE493D_AW2B6_Diag_FRM_POS		( 0U )
/* XL */
#define TLE493D_AW2B6_XL_REG			( 0x07U )
/* XH */
#define TLE493D_AW2B6_XH_REG			( 0x08U )
/* YL */
#define TLE493D_AW2B6_YL_REG			( 0x09U )
/* YH */
#define TLE493D_AW2B6_YH_REG			( 0x0AU )
/* ZL */
#define TLE493D_AW2B6_ZL_REG			( 0x0BU )
/* ZH */
#define TLE493D_AW2B6_ZH_REG			( 0x0CU )
/* WU */
#define TLE493D_AW2B6_WU_REG			( 0x0DU )
#define TLE493D_AW2B6_WU_WA_POS			( 0x7U )
#define TLE493D_AW2B6_WU_WA_MSK			( 0x1U << 7 )
#define TLE493D_AW2B6_WU_WU_POS			( 0x6U )
#define TLE493D_AW2B6_WU_WU_ENABLE		( 0x1U << 6 )
#define TLE493D_AW2B6_WU_WU_DISABLE		( 0x0U << 6 )
#define TLE493D_AW2B6_WU_WU_MSK			( 0x1U << 6 )
#define TLE493D_AW2B6_WU_XH_POS			( 0x3U )
#define TLE493D_AW2B6_WU_XH_MSK			( 0x7U << 3 )
#define TLE493D_AW2B6_WU_XL_POS			( 0x3U )
#define TLE493D_AW2B6_WU_XL_MSK			( 0x7U << 0 )

/* TMode */
#define TLE493D_AW2B6_TMode_REG			( 0x0EU )
#define TLE493D_AW2B6_TMode_TST_POS		( 6U )
#define TLE493D_AW2B6_TMode_TST_MSK		( 3U << 6 )
#define TLE493D_AW2B6_TMode_TST_NORMAL		( 0U << 6 )
#define TLE493D_AW2B6_TMode_TST_Vhall		( 1U << 6 )
#define TLE493D_AW2B6_TMode_TST_Spintest	( 2U << 6 )
#define TLE493D_AW2B6_TMode_TST_SAT		( 3U << 6 )
#define TLE493D_AW2B6_TMode_YH_POS		( 3U )
#define TLE493D_AW2B6_TMode_YH_MSK		( 7U << 3 )
#define TLE493D_AW2B6_TMode_YL_POS		( 0U )
#define TLE493D_AW2B6_TMode_YL_MSK		( 7U << 0 )

/* TPhase */
#define TLE493D_AW2B6_TPhase_REG		( 0x0FU )
#define TLE493D_AW2B6_TPhase_PH_POS		( 6U )
#define TLE493D_AW2B6_TPhase_PH_MSK		( 3U << 6 )
#define TLE493D_AW2B6_TPhase_ZH_POS		( 3U )
#define TLE493D_AW2B6_TPhase_ZH_MSK		( 7U << 3 )
#define TLE493D_AW2B6_TPhase_ZL_POS		( 0U )
#define TLE493D_AW2B6_TPhase_ZL_MSK		( 7U << 0 )

/* Config */
#define TLE493D_AW2B6_Config_REG		( 0x10U )

#define TLE493D_AW2B6_Config_DT_POS		( 0x7U )
#define TLE493D_AW2B6_Config_DT_MSK		( 0x1U << 7 )
#define TLE493D_AW2B6_Config_DT_ENABLE		( 0x0U << 7 )
#define TLE493D_AW2B6_Config_DT_DISABLE		( 0x1U << 7 )

#define TLE493D_AW2B6_Config_AM_POS		( 0x6U )
#define TLE493D_AW2B6_Config_AM_MSK		( 0x1U << 6 )
#define TLE493D_AW2B6_Config_AM_ENABLE_BZ_MEASURE	( 0x0U << 6 )
#define TLE493D_AW2B6_Config_AM_DISABLE_BZ_MEASURE	( 0x1U << 6 )

#define TLE493D_AW2B6_Config_TRIG_POS		( 0x4U )
#define TLE493D_AW2B6_Config_TRIG_MSK		( 0x30U )


/* Register-configurable trigger modes */
typedef enum {
	TLE493D_AW2B6_Config_TRIG_NONE	= ( 0x0U << 4 ),
	// FIXME: R0 mode seems to cause errors: SDA outputs 1s on BUS
	TLE493D_AW2B6_Config_TRIG_R0	= ( 0x1U << 4 ),
	TLE493D_AW2B6_Config_TRIG_R6	= ( 0x2U << 4 )

} TLE493D_ConfigTriggerMode_t;


#define TLE493D_AW2B6_Config_X2_POS			( 0x3U )
#define TLE493D_AW2B6_Config_X2_MSK			( 1U << 3 )
#define TLE493D_AW2B6_Config_X2_DOUBLE		( 1U << 3 )
#define TLE493D_AW2B6_Config_X2_SIMPLE		( 0U << 3 )

#define TLE493D_AW2B6_Config_TL_mag_POS		( 0x1U )
#define TLE493D_AW2B6_Config_TL_mag_MSK		( 3U << 1 )


/* Sensitivity for magnetic compensation */
typedef enum {
	TLE493D_AW2B6_Config_TL_mag_TC0	= ( 0U << 1 ),
	TLE493D_AW2B6_Config_TL_mag_TC1 = ( 1U << 1 ),
	TLE493D_AW2B6_Config_TL_mag_TC2 = ( 2U << 1 ),
	TLE493D_AW2B6_Config_TL_mag_TC3 = ( 3U << 1 )

} TLE493D_MagneticComp_t;


#define TLE493D_AW2B6_Config_CP_POS		( 0x0U )
#define TLE493D_AW2B6_Config_CP_MSK		( 0x1U )

/* MOD1 Register */
#define TLE493D_AW2B6_MOD1_REG			( 0x11U )
#define TLE493D_AW2B6_MOD1_FP_POS		( 0x7U )
#define TLE493D_AW2B6_MOD1_FP_MSK		( 1 << 0x7U )

#define TLE493D_AW2B6_MOD1_IICadr_POS		( 0x5U )
#define TLE493D_AW2B6_MOD1_IICadr_MSK		( 0x3U << 0x5U )


#define TLE493D_AW2B6_MOD1_IICadr_A0		( 0x0U << 0x5U )
#define TLE493D_AW2B6_MOD1_IICadr_A1		( 0x1U << 0x5U )
#define TLE493D_AW2B6_MOD1_IICadr_A2		( 0x2U << 0x5U )
#define TLE493D_AW2B6_MOD1_IICadr_A3		( 0x3U << 0x5U )

#define TLE493D_AW2B6_MOD1_PR_POS		( 0x4U )
#define TLE493D_AW2B6_MOD1_PR_MSK		( 0x1U << 0x4U )
#define TLE493D_AW2B6_MOD1_PR_2BYTE		( 0x0U << 0x4U )
#define TLE493D_AW2B6_MOD1_PR_1BYTE		( 0x1U << 0x4U )

#define TLE493D_AW2B6_MOD1_CA_POS		( 0x3U )
#define TLE493D_AW2B6_MOD1_CA_MSK		( 1 << 0x3U )
#define TLE493D_AW2B6_MOD1_CA_ENABLE		( 0U << 0x3U )
#define TLE493D_AW2B6_MOD1_CA_DISABLE		( 1U << 0x3U )

#define TLE493D_AW2B6_MOD1_INT_POS		( 0x2U )
#define TLE493D_AW2B6_MOD1_INT_MSK		( 0x1U << 0x2U )
#define TLE493D_AW2B6_MOD1_INT_ENABLE		( 0x0U << 0x2U )
#define TLE493D_AW2B6_MOD1_INT_DISABLE		( 0x1U << 0x2U )

#define TLE493D_AW2B6_MOD1_MODE_POS		( 0x0U )
#define TLE493D_AW2B6_MOD1_MODE_MSK		( 0x3U )
#define TLE493D_AW2B6_MOD1_MODE_LOW_POWER	( 0U )
#define TLE493D_AW2B6_MOD1_MODE_MCM		( 0x1U )
#define TLE493D_AW2B6_MOD1_MODE_FAST_MODE	( 0x3U )


/* Trigger bits for I2C Write commands */
typedef enum {
	TLE493D_AW2B6_I2C_NOTRIG   				= ( 0x00U << 5 ),
	TLE493D_AW2B6_I2C_TRIG_AFTER_WRITE  	= ( 0x01U << 5 ),
	TLE493D_AW2B6_I2C_TRIG_BEFORE_READ  	= ( 0x02U << 5 ),
	TLE493D_AW2B6_I2C_TRIG_AFTER_READ_R06 	= ( 0x04U << 5 )

} TLE493D_I2cTriggerMode_t;


/* Reserved */
#define TLE493D_AW2B6_Reserved_REG		( 0x12U )
/* MOD2 */
#define TLE493D_AW2B6_MOD2_REG			( 0x13U )

#define TLE493D_AW2B6_MOD2_PRD_POS		( 0x5U )
#define TLE493D_AW2B6_MOD2_PRD_MSK		( 0x7U << 5 )


/* Low power mode update frequencies */
typedef enum {
	TLE493D_AW2B6_MOD2_PRD_770 	= ( 0x0U << 5 ),
	TLE493D_AW2B6_MOD2_PRD_97 	= ( 0x1U << 5 ),
	TLE493D_AW2B6_MOD2_PRD_24 	= ( 0x2U << 5 ),
	TLE493D_AW2B6_MOD2_PRD_12 	= ( 0x3U << 5 ),
	TLE493D_AW2B6_MOD2_PRD_6 	= ( 0x4U << 5 ),
	TLE493D_AW2B6_MOD2_PRD_3 	= ( 0x5U << 5 ),
	TLE493D_AW2B6_MOD2_PRD_04 	= ( 0x6U << 5 ),
	TLE493D_AW2B6_MOD2_PRD_005	= ( 0x7U << 5 )

} TLE493D_LpUpdateFreq_t;


/* Reserved */
#define TLE493D_AW2B6_Reserved2_REG		( 0x14U )
/* Reserved */
#define TLE493D_AW2B6_Reserved3_REG		( 0x15U )
/* Version */
#define TLE493D_AW2B6_Ver_REG			( 0x16U )

#define TLE493D_AW2B6_Ver_HWV_POS		( 0x00U )
#define TLE493D_AW2B6_Ver_HWV_MSK		( 0x0FU )
#define TLE493D_AW2B6_Ver_HWV_B21		( 0x09U )

#define TLE493D_AW2B6_Ver_TYPE_POS		( 0x4U )
#define TLE493D_AW2B6_Ver_TYPE_MSK		( 0x3U << 4 )


/*-----------------------------------------------------------------------------------------------------------*/

/* Sensor bus addresses */
typedef enum {
	TLE493D_AW2B6_I2C_A0_ADDR = 0x6AU,
	TLE493D_AW2B6_I2C_A1_ADDR = 0x44U,
	TLE493D_AW2B6_I2C_A2_ADDR = 0xF0U,
	TLE493D_AW2B6_I2C_A3_ADDR = 0x88U

} TLE493D_Address_t;

/* Internal registers of the TLE493D sensor family*/
typedef struct {
	uint8_t Bx, By, Bz, Temp;
	uint8_t Bx2, Temp2;
	uint8_t Diag;
	uint8_t XL, XH;
	uint8_t YL, YH;
	uint8_t ZL, ZH;
	uint8_t WU, TMode, TPhase;
	uint8_t Config, MOD1;
	uint8_t Reserved;
	uint8_t MOD2;
	uint8_t Reserved2, Reserved3;
	uint8_t Ver;

} TLE493D_Regmap_t;


#define TLE493D_W2B6_B_MULT             ( 0.13 )
/* for 8 bit resolution */
#define TLE493D_W2B6_B_MULT_LOW         ( 2.08 )
/* range 0.21 to 0.27 */
#define TLE493D_W2B6_TEMP_MULT          ( 0.24 )
/* for 8 bit resolution */
#define TLE493D_W2B6_TEMP_MULT_LOW      ( 3.84 )
/* range 1000 to 1360 */
#define TLE493D_W2B6_TEMP_OFFSET        ( 1180 )
/* room temperature offset */
#define TLE493D_W2B6_TEMP_25            ( 25 )


#endif /* TLE_AW2B6_DEFINES_H */

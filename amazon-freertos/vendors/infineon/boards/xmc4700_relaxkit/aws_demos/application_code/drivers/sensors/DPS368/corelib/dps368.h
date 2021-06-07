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

#ifndef DPS368_H
#define DPS368_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/* Attributes: Product identification and version */

#define     VENDOR_NAME                                 "Infineon"
#define     DRIVER_NAME                                 "IFXDD"
#define     DEVICE_NAME                                 "Digital Barometric Pressure Sensor"
#define     DEVICE_MODEL_NAME                           "DPS368"
#define     DEVICE_HW_VERSION                           1.0
#define     DRIVER_VERSION                              1.0
#define     DEVICE_PROD_REV_ID                          0x10

/* Attributes: Device performance :Pressure Sensing */
#define     IFX_DPS368_PROD_REV_ID_REG_ADDR             0x0D
#define     IFX_DPS368_PROD_REV_ID_LEN                  1
#define     IFX_DPS368_PROD_REV_ID_VAL                  DEVICE_PROD_REV_ID

#define     IFX_DPS368_SOFT_RESET_REG_ADDR              0x0C
#define     IFX_DPS368_SOFT_RESET_REG_DATA              0x09
#define     IFX_DPS368_SOFT_RESET_REG_LEN               1
#define     IFX_DPS368_SOFT_RESET_VERIFY_REG_ADDR       0x06

#define     IFX_DPS368_COEF_REG_ADDR                    0x10

/* Length in bytes */
#define     IFX_DPS368_COEF_LEN                         18

#define     IFX_DPS368_TMP_COEF_SRCE_REG_ADDR           0x28

/* Length in bytes */
#define     IFX_DPS368_TMP_COEF_SRCE_REG_LEN            1

/* Length in bytes */
#define     IFX_DPS368_TMP_COEF_SRCE_REG_POS_MASK       7

#define     IFX_DPS368_PSR_TMP_READ_REG_ADDR            0x00
#define     IFX_DPS368_PSR_TMP_READ_LEN                 6

#define     IFX_DPS368_PRS_CFG_REG_ADDR                 0x06
#define     IFX_DPS368_PRS_CFG_REG_LEN                  1

#define     IFX_DPS368_TMP_CFG_REG_ADDR                 0x07
#define     IFX_DPS368_TMP_CFG_REG_LEN                  1

#define     IFX_DPS368_MEAS_CFG_REG_ADDR                0x08
#define     IFX_DPS368_MEAS_CFG_REG_LEN                 1

#define 	IFX_DPS368_MEAS_PRS_RDY_POS					( 1 << 4 )
#define 	IFX_DPS368_MEAS_TMP_RDY_POS					( 1 << 5 )


#define     IFX_DPS368_CFG_REG_ADDR                     0x09
#define     IFX_DPS368_CFG_REG_LEN                      1

#define     IFX_DPS368_CFG_INT_HL_EN_SET_VAL         	( 1 << 7 )
#define     IFX_DPS368_CFG_INT_FIFO_EN_SET_VAL         	( 1 << 6 )
#define     IFX_DPS368_CFG_INT_TMP_EN_SET_VAL         	( 1 << 5 )
#define     IFX_DPS368_CFG_INT_PRS_EN_SET_VAL         	( 1 << 4 )
#define     IFX_DPS368_CFG_TMP_SHIFT_EN_SET_VAL         0x08
#define     IFX_DPS368_CFG_PRS_SHIFT_EN_SET_VAL         0x04
#define     IFX_DPS368_CFG_FIFO_ENABLE_EN_SET_VAL       ( 1 << 1 )
#define     IFX_DPS368_CFG_SPI_MODE_EN_SET_VAL         	( 1 << 0 )

#define     IFX_DPS368_FIFO_READ_REG_ADDR               0x00
#define     IFX_DPS368_FIFO_REG_READ_LEN                3
#define     IFX_DPS368_FIFO_BYTES_PER_ENTRY             3

#define     IFX_DPS368_FIFO_FLUSH_REG_ADDR              0x0C
#define     IFX_DPS368_FIFO_FLUSH_REG_VAL               0b1000000U

#define     IFX_DPS368_CFG_SPI_MODE_POS                 0
#define     IFX_DPS368_CFG_SPI_MODE_3_WIRE_VAL          1
#define     IFX_DPS368_CFG_SPI_MODE_4_WIRE_VAL          0

#define     IFX_DPS368_CFG_FIFO_ENABLE_POS              1
#define     IFX_DPS368_CFG_FIFO_ENABLE_VAL              1
#define     IFX_DPS368_CFG_FIFO_DISABLE_VAL             0

#define     IFX_DPS368_CFG_INTR_PRS_ENABLE_POS          4
#define     IFX_DPS368_CFG_INTR_PRS_ENABLE_VAL          1U
#define     IFX_DPS368_CFG_INTR_PRS_DISABLE_VAL         0U

#define     IFX_DPS368_CFG_INTR_TEMP_ENABLE_POS         5
#define     IFX_DPS368_CFG_INTR_TEMP_ENABLE_VAL         1U
#define     IFX_DPS368_CFG_INTR_TEMP_DISABLE_VAL        0U

#define     IFX_DPS368_CFG_INTR_FIFO_FULL_ENABLE_POS    6
#define     IFX_DPS368_CFG_INTR_FIFO_FULL_ENABLE_VAL    1U
#define     IFX_DPS368_CFG_INTR_FIFO_FULL_DISABLE_VAL   0U

#define     IFX_DPS368_CFG_INTR_LEVEL_TYP_SEL_POS       7
#define     IFX_DPS368_CFG_INTR_LEVEL_TYP_ACTIVE_H      1U
#define     IFX_DPS368_CFG_INTR_LEVEL_TYP_ACTIVE_L      0U

#define     IFX_DPS368_INTR_SOURCE_PRESSURE             0
#define     IFX_DPS368_INTR_SOURCE_TEMPERATURE          1
#define     IFX_DPS368_INTR_SOURCE_BOTH                 2

#define     IFX_DPS368_INTR_STATUS_REG_ADDR             0x0A
#define     IFX_DPS368_INTR_STATUS_REG_LEN              1
#define     IFX_DPS368_INTR_DISABLE_ALL                (uint8_t)0b10001111




#define     EINVAL                                      1
#define     EIO                                         2


/* Implies 2^23-1 */
#define POW_2_23_MINUS_1	0x7FFFFF

#define POW_2_24			0x1000000
#define POW_2_15_MINUS_1	0x7FFF
#define POW_2_16			0x10000
#define POW_2_11_MINUS_1	0x7FF
#define POW_2_12			0x1000
#define POW_2_20			0x100000
#define POW_2_19_MINUS_1	524287


/* Structure to hold calibration coefficients read from device */
typedef struct {
	/* calibration registers */

	/* 12bit */
	int16_t 	C0;
	/* 12bit */
	int16_t 	C1;
	/* 20bit */
	int32_t	   C00;
	/* 20bit */
	int32_t    C10;
	/* 16bit */
	int16_t    C01;
	/* 16bit */
	int16_t	   C11;
	/* 16bit */
	int16_t	   C20;
	/* 16bit */
	int16_t	   C21;
	/* 16bit */
	int16_t	   C30;

} dps368_cal_coeff_regs_s;


/* Enumerate for setting/getting device operating mode */
typedef enum {
  DPS368_MODE_IDLE                   =  0b00000000,
  DPS368_MODE_COMMAND_PRESSURE       =  0b00000001,
  DPS368_MODE_COMMAND_TEMPERATURE    =  0b00000010,
  DPS368_MODE_BACKGROUND_PRESSURE    =  0b00000101,
  DPS368_MODE_BACKGROUND_TEMPERATURE =  0b00000110,
  DPS368_MODE_BACKGROUND_ALL         =  0b00000111,

}dps368_operating_modes_e;


/* Enumerate of scaling coefficients either Kp or Kt */
typedef enum {
    OSR_SF_1   = 524288,
    OSR_SF_2   = 1572864,
    OSR_SF_4   = 3670016,
    OSR_SF_8   = 7864320,
    OSR_SF_16  = 253952,
    OSR_SF_32  = 516096,
    OSR_SF_64  = 1040384,
    OSR_SF_128 = 2088960,

} dps368_scaling_coeffs_e;


/* Enumerate of over sampling rates for pressure and temperature */
typedef enum {
    OSR_1   = 0b00000000,
    OSR_2   = 0b00000001,
    OSR_4   = 0b00000010,
    OSR_8   = 0b00000011,
    OSR_16  = 0b00000100,
    OSR_32  = 0b00000101,
    OSR_64  = 0b00000110,
    OSR_128 = 0b00000111,

} dps368_osr_e;


/* Enumerate of measurement rates for pressure */
typedef enum {
    PM_MR_1   = 0b00000000,
    PM_MR_2   = 0b00010000,
    PM_MR_4   = 0b00100000,
    PM_MR_8   = 0b00110000,
    PM_MR_16  = 0b01000000,
    PM_MR_32  = 0b01010000,
    PM_MR_64  = 0b01100000,
    PM_MR_128 = 0b01110000,

} dps368_pm_rate_e;


/* Enumerate of measurement rates for temperature*/
typedef enum {
    TMP_MR_1   = 0b00000000,
    TMP_MR_2   = 0b00010000,
    TMP_MR_4   = 0b00100000,
    TMP_MR_8   = 0b00110000,
    TMP_MR_16  = 0b01000000,
    TMP_MR_32  = 0b01010000,
    TMP_MR_64  = 0b01100000,
    TMP_MR_128 = 0b01110000,

} dps368_tmp_rate_e;


/* Enumerate of over sampling and measurement rates*/
typedef enum {
    TMP_EXT_ASIC = 0x00,
    TMP_EXT_MEMS = 0x80,

} dps368_temperature_src_e;


typedef struct {
	uint8_t  address;
    uint32_t mux_type;

} dps368_bus_context_t;

/* Please update callbacks for bus communication
* callbacks are protocol agnostic/abstract so
* as to wrap around I2C or SPI low level protocols
*/

typedef struct {

	/* Provide a wrapper for single byte read/write and multi byte read
	* all callbacks return negative values to indicate error
	* however, read_byte must return the content in case of successful read
	* and read_block shall return number of bytes read successfully
	* For write_byte non zero return value shall indicate successful write
	*/
	void*  bus_context;          /* bus specific context: SPI - spi mux type
														  I2C - i2c mux type, address */

	int16_t (*init)     ( void* bus_context );

	int16_t (*read_byte)( void* bus_context, uint8_t address );

	int16_t (*read_block)( void* bus_context, uint8_t address, uint8_t length, uint8_t *read_buffer );

	int16_t (*write_byte)( void* bus_context, uint8_t address, uint8_t data );

	/*It is expected to provide a wrapper for incorporating delay
	* the delay shall be in milliseconds. This is required as
	* after powering up the sensor, it takes 40ms until fused
	* calibration coefficients are ready to read.
	* in case this delay is handled appropriately by caller by other mechanism
	* please set this callback to NULL
	*/
	void (*delayms)( uint32_t duration );

} dps368_bus_connection;


typedef struct {

	uint8_t unit_name;

	dps368_scaling_coeffs_e   tmp_osr_scale_coeff;      /* Temperature scaling coefficient*/
	dps368_scaling_coeffs_e   prs_osr_scale_coeff;      /* Pressure scaling coefficient*/
	dps368_cal_coeff_regs_s   calib_coeffs;             /* Calibration coefficients index */
	dps368_operating_modes_e  dev_mode;                 /* Current operating mode of device */
	dps368_pm_rate_e	      press_mr;					/* Current measurement readout rate (ODR) for pressure */
	dps368_tmp_rate_e         temp_mr;				  	/* Current measurement readout rate (ODR) for temperature */
	dps368_osr_e		      temp_osr;				  	/* Current over sampling rate (OSR) for temperature */
	dps368_osr_e		      press_osr;				/* Current over sampling rate (OSR) for pressure */
	dps368_temperature_src_e  tmp_ext;                  /* Temperature ASIC or MEMS. Should always be set MEMS*/
	uint8_t                   cfg_word;                 /* Keep the contents of CFG register as it gets configured
														to avoid excessive bus transactions */
	uint8_t 			      enable;
	dps368_bus_connection     *io;                      /*To access bus communication call backs */

} DPS368_t;


/* Public function prototypes */
int16_t dps368_init( DPS368_t *drv_state, dps368_bus_connection *io );


int32_t DPS368_lGetProcessedData( DPS368_t *drv_state, float *pressure, float *temperature );


int dps368_config(
        DPS368_t *drv_state,
        dps368_osr_e osr_temp,
        dps368_tmp_rate_e mr_temp,
        dps368_osr_e osr_press,
        dps368_pm_rate_e mr_press,
        dps368_temperature_src_e temp_src );

int dps368_is_prs_tmp_rdy( DPS368_t *drv_state );

int dps368_standby( DPS368_t *drv_state );

int dps368_resume( DPS368_t *drv_state );


#endif /* DPS368_H */

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

#ifndef TLV_A1B6_H
#define TLV_A1B6_H

#include "TLx493D/tlx493d.h"
#include "driver/tlv_a1b6_driver.h"


/*! \brief I2C addresses supported by the TLV493D-A1B6
 * sensor.
 *
 * The left side addresses from the define
 * names (3E, 36, 1E, 16) are relevant when the sensor
 * is powered up with the ADDR pin LOW. The right side
 * addresses can be used when the sensor is powered up
 * with the ADDR pin HIGH.
 * All values are in hexadecimal representation. */
typedef enum {
	TLV493D_A1B6_ADDR_3E_BC,
	TLV493D_A1B6_ADDR_36_B4,
	TLV493D_A1B6_ADDR_1E_9C,
	TLV493D_A1B6_ADDR_16_94

} TLV493D_Address_t;


/*! \brief Data structure containing information about the internal
 * state of a sensor. Also used to identify a sensor on a bus. */
typedef struct {
	//! I2C address to be written on the bus for sensor addressing
	uint8_t IIC_addr;
	//! Last frame value from the sensor ADC used to detect a stuck ADC
	uint8_t frame_count;
	//! Type of I2C address (addr bit unspecified)
	TLV493D_Address_t addr_type;
	//! Address bit, representing state of ADDR line at power up
	bool ADDR_high;
	//! Last known state of the Read registers
	TLV493D_RegMapRead_t regmap_read;
	//! Last known state of the Write registers
	TLV493D_RegMapWrite_t regmap_write;

} TLV493D_Data_t;


/*! \brief Initialize the sensor.
 *
 *
 * \param pxData parameter is optional (can be replaced with NULL) and specifies a
 * 	data structure that should store the state of the sensor. If no data structure is
 * 	sepcifiec, an internal data structure will be used. This parameter should be used in
 * 	a bus configuration to easily identify sensors and also to manually inspect the
 * 	internal state of the sensor.
 * \param bAddressHigh indicates the level of ADDR at the time the sensor was powered up.
 * 	bAddressHigh=true indicates that the sensor was powered up with ADDR=HIGH
 * 	bAddressHigh=false indicates that the sensor was powered up with ADDR=LOW
 * \param xAddressType indicates the desired address after initialization while keeping in mind the
 * value of bAddressHigh and the ADDR pin logic value at startup.
 *
 *
 * 	\code{.c}
 * 	// ========================= Example =============================
 * 	// NULL -> store sensor information internally inside the library
 * 	//	This mode supports only one sensor at a time
 * 	// true -> At startup the ADDR pin was HIGH so the internal sensor
 * 	// address pin is set to 1
 * 	// TLV493D_A1B6_ADDR_1E_9C -> the desired sensor address is either
 * 	// 1E or 9C. Since the ADDR pin was HIGH at startup, the address will
 * 	// always be 9C
 * 	TLV493D_A1B6_init(NULL, true, TLV493D_A1B6_ADDR_1E_9C);
 * 	\endcode
 * 	*/
int32_t TLV493D_A1B6_init( TLV493D_Data_t *pxData, bool bAddressHigh, TLV493D_Address_t xAddressType );

/*! \brief Hard reset the sensor by executing a power cycle and reinitialize using
 * the settings from the data structure. Will only set the address.
 * \param pxData Sensor data structure. By passing NULL, local data will be used.
 * */
void TLV493D_A1B6_hard_reset_reconfigure( TLV493D_Data_t *pxData );

/*! \brief Read the registers of the TLx493D sensor and create a data frame */
int32_t TLV493D_A1B6_read_frame_raw( TLV493D_Data_t *pxData, TLx493D_DataFrameRaw_t *pxFrame );
int32_t TLV493D_A1B6_read_frame( TLV493D_Data_t *pxData, TLx493D_DataFrame_t *pxFrame );

/*! \brief Change the operation mode of the sensor */
int32_t TLV493D_A1B6_set_operation_mode( TLV493D_Data_t *pxData, TLV493D_OpMode_t xMode );

/*! \brief Enable or disable the temperature measurement */
int32_t TLV493D_A1B6_set_temp_measure( TLV493D_Data_t *pxData, bool bEnabled );

/*! \brief Enable or disable the parity test */
int32_t TLV493D_A1B6_set_parity_test( TLV493D_Data_t *pxData, bool bEnabled );

/*! \brief Set a new I2C address for the sensor, considering the ADDR pin level at startup */
int32_t TLV493D_A1B6_set_IIC_address( TLV493D_Data_t *pxData, TLV493D_Address_t xNewAddressType );

/*! \brief Copy the data stored in the library to the dest structure */
void TLV493D_A1B6_get_data( TLV493D_Data_t *pxDest );

/*! \brief Copy the data from src to the library */
int32_t TLV493D_A1B6_set_data( TLV493D_Data_t *pxSrc );


#endif /* TLV_A1B6_H */

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

#ifndef TLX493D_H
#define TLX493D_H

#include <stdbool.h>
#include <stdint.h>

/*!
 * \brief Generic data frame, common to all supported hardware version
 * */
typedef struct {
	//! Magnetic field intensity raw value on the X axis
	int16_t x;
	//! Magnetic field intensity raw value on the Y axis
	int16_t y;
	//! Magnetic field intensity raw value on the Z axis
	int16_t z;
	//! Raw Temperature value
	int16_t temp;

} TLx493D_DataFrameRaw_t;


typedef struct {
    //! Magnetic field intensity value on the X axis
    float x;
    //! Magnetic field intensity value on the Y axis
    float y;
    //! Magnetic field intensity value on the Z axis
    float z;
    //! Raw Temperature value
    float temp;

} TLx493D_DataFrame_t;


/*! \brief Error codes returned by the TLx493D library */
enum {
	//! No error encountered
	TLx493D_OK = 0,
	//! Function called with invalid argument
	TLx493D_INVALID_ARGUMENT = -1,
	//! The returned frame is invalid and should be discarded
	TLx493D_INVALID_FRAME = -2,
	//! The called method has not been implemented yet
	TLx493D_NOT_IMPLEMENETED = -3,
	//! One or mode sensor registers are set incorrectly
	TLx493D_INVALID_SENSOR_STATE = -4,
	//!The WU feature failed to activate; unknown error
	TLx493D_WU_ENABLE_FAIL 	= -5,
};


/*! \brief Type of sensor on board */
typedef enum {
	TLx493D_TYPE_UNKNOWN,
	TLx493D_TYPE_TLV_A1B6,
	TLx493D_TYPE_TLE_A2B6,
	TLx493D_TYPE_TLE_W2B6,
	TLx493D_TYPE_TLI_W2BW

} TLV493D_SensorType_t;


/*! \brief Operating Mode*/
typedef enum {
	TLx493D_OP_MODE_NOT_INITIALIZED,
	TLx493D_OP_MODE_POWER_DOWN,
	TLx493D_OP_MODE_MCM,
	TLx493D_OP_MODE_FAST,
	TLx493D_OP_MODE_LOW_POWER,
	TLx493D_OP_MODE_ULTRA_LOW_POWER

} TLV493D_OpMode_t;



/*! \brief Detect and initialize the connected sensor.
 *
 *  Automatically detect the sensor hardware version and call the appropriate
 * initialization sequences. Must be called prior to any other call to
 * a TLx493D_* method.
 * \return Error code.*/
int32_t TLx493D_lInit( void );

/*! \brief Return the type of sensor present on the board. */
TLV493D_SensorType_t TLx493D_xGetSensorType( void );

/*! \brief Set the operation mode of the sensors, if supported.
 * \return Error code.*/
int32_t TLx493D_lSetOperationMode( TLV493D_OpMode_t xMode );

/*! \brief Get the operation mode of the sensors */
TLV493D_OpMode_t TLx493D_xGetOperationMode( void );

/*! \brief Read a data frame from the sensor
 * \return Error code. */
int32_t TLx493D_lReadFrame( TLx493D_DataFrame_t *pxFrame );
int32_t TLx493D_lReadFrameRaw( TLx493D_DataFrameRaw_t *pxFrame );

/*! \brief Compute the EVEN parity of a byte of data
 *
 *  \return Even parity of the data, either the value 0 or 1. */
uint8_t MISC_get_parity( uint8_t ucData );


#endif /* TLX493D_H */

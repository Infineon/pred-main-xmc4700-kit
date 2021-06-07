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

#ifndef TLE_AW2B6_H
#define TLE_AW2B6_H

#include <stdint.h>
#include <stdbool.h>
#include "TLx493D/tlx493d.h"
#include "driver/tle_aw2b6_defines.h"


/*! \brief Data structure containing information about the internal
 * state of a sensor. Also used to identify a sensor on a bus. */
typedef struct {
	//! I2C address to be written on the bus
	TLE493D_Address_t IIC_addr;
	//! Last known state of the internal sensor registers
	TLE493D_Regmap_t regmap;

} TLE493D_Data_t;


/*! \brief Initialize the sensor having the specified I2C address by reading the
 * internal registers and disabling periodic interrupt pulses.
 *
 * \param data Structure to copy the values of the internal registers to.
 * 	If data is NULL, the internal library data structure will be used
 * 	instead. This approach support only one sensor, and for a bus of
 * 	several sensors, a different data structure should be used for each
 * 	one of them.
 * \param ucSlaveAddressI2C The initial address of the sensor. Sensors may
 * have different fused default addresses.
 * */
int32_t TLE493D_AW2B6_lInit( TLE493D_Data_t *pxData, uint8_t ucSlaveAddressI2C );

/*! \brief Compute the value of the FP bit using the internal register state of the sensor */
uint8_t TLE493D_AW2B6_ucGetBitFP( TLE493D_Data_t *pxData );

/*! \brief Compute the value of the CP bit using the internal register state of the sensor */
uint8_t TLE493D_AW2B6_ucGetBitCP( TLE493D_Data_t *pxData );

/*! \brief Write the reset sequence on the I2C bus */
void TLE493D_AW2B6_vResetAll( void );

/*! \brief Set the operation mode of the sensor */
int32_t TLE493D_AW2B6_lSetOperationMode( TLE493D_Data_t *pxData, TLV493D_OpMode_t xMode );


/*! \brief Read a data frame from the sensor. An ADC sampling must
 * be completed before calling this method */
int32_t TLE493D_AW2B6_lReadFrameRaw( TLE493D_Data_t *pxData, TLx493D_DataFrameRaw_t *pxFrame );
int32_t TLE493D_AW2B6_lReadFrame( TLE493D_Data_t *pxData, TLx493D_DataFrame_t *pxFrame );

/*! \brief Enable the Wake Up mode ( available only on the -W2B6 hardware version ) with the
 * provided upper and lower limits */
int32_t TLE493D_AW2B6_lEnableWU( TLE493D_Data_t *pxData, uint16_t usWuXl, uint16_t usWuXh, uint16_t usWuYl, uint16_t usWuYh, uint16_t usWuZl, uint16_t usWuZh );

/*! \brief Disable the Wake Up mode */
int32_t TLE493D_AW2B6_lDisableWU( TLE493D_Data_t *pxData );

/*! \brief Set a new I2C address for the sensor */
int32_t TLE493D_AW2B6_lSetSlaveAddressI2C( TLE493D_Data_t *pxData, TLE493D_Address_t ucSlaveAddressI2C );

/*! \brief Set the magnetic temperature compensation mode */
int32_t TLE493D_AW2B6_lMagneticTmpComp( TLE493D_Data_t *pxData, TLE493D_MagneticComp_t xSens );

/*! \brief Double the measurement sensitivity( when on=true ). This will decrease the ADC integration speed */
int32_t TLE493D_AW2B6_lSetHighSensitivity( TLE493D_Data_t *pxData, bool bOn );

/*! \brief Enable/Disable angle mode. In order to enable angle mode, the temperature
 * measurement must be disabled */
int32_t TLE493D_AW2B6_lSetAngleMode( TLE493D_Data_t *pxData, bool bOn );

/*! \brief Enable/Disable temperature measurement */
int32_t TLE493D_AW2B6_lSetTempMeasure( TLE493D_Data_t *pxData, bool bOn );

/*! \brief Set the update frequency while in LOW POWER Mode */
int32_t TLV493D_A1B6_lSetLPUpdateFrequency( TLE493D_Data_t *pxData, TLE493D_LpUpdateFreq_t xFreq );

/*! \brief Set trigger mode.
 * Note that the TLE493D_AW2B6_Config_TRIG_R0 mode is momentarily not
 * safe to use in this software implementation */
int32_t TLV493D_A1B6_lSetTriggerMode( TLE493D_Data_t *pxData, TLE493D_ConfigTriggerMode_t xMode );

/*! \brief Return hardware version of the TLE493D */
TLV493D_SensorType_t TLE493D_xGetHwVersion( TLE493D_Data_t *pxData );

/*! \brief Copy the data stored in the library to the dest structure */
void TLE493D_AW2B6_vGetData( TLE493D_Data_t *pxDest );

/*! \brief Copy the data from src to the library and the sensor */
int32_t TLE493D_AW2B6_lSetData( TLE493D_Data_t *pxSrc );


#endif /* TLE_AW2B6_H */

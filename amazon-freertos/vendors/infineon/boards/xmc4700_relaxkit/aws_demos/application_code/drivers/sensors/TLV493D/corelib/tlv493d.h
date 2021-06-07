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

#ifndef TLV493D_H
#define TLV493D_H

#include <stdbool.h>
#include <stdint.h>

#include "util/BusInterface.h"


/*
 * TLV493D_ACCELERATE_READOUT lets the controller just read out the first 3 bytes when in fast mode.
 * This makes the readout faster (half of usual transfer duration), but there is no way to get
 * temperature, current channel or high precision (only 8 instead of 12 bits for x, y, z)
 * It is necessary for slow I2C busses to read the last result before the new measurement is completed.
 * It only takes effect in FAST_MODE, not in other modes.
 *
 * Feel free to undefine this and increase your I2C bus speed if you need to.
 */
#define TLV493D_ACCELERATE_READOUT


typedef enum {
    POWER_DOWN_MODE = 0,
    FAST_MODE,
    LOW_POWER_MODE,
    ULTRA_LOW_POWER_MODE,
    MASTER_CONTROLLED_MODE,

} AccessMode_e;


typedef struct {
	BusInterface_t mInterface;
    AccessMode_e mMode;
    int16_t mXdata;
    int16_t mYdata;
    int16_t mZdata;
    int16_t mTempdata;
    uint8_t mExpectedFrameCount;

} Tlv493d_t;


typedef enum {
	TLV493D_ADDRESS_1	=	0xBC,
	TLV493D_ADDRESS_2	=	0x3E

} Tlv493dAddress_t;


typedef enum Tlv493d_Error {
	TLV493D_NO_ERROR	=	0,
	TLV493D_BUS_ERROR	=	1,
	TLV493D_FRAME_ERROR	=	2

} Tlv493dError_t;


bool TLV493D_bInit( void **ppvHandle, Tlv493dAddress_t xSlaveAddress, bool bReset );
void TLV493D_vDeInit( void **ppvHandle );

void TLV493D_vEnd( Tlv493d_t *pxCxt );

/* sensor configuration */

/* sets the data access mode for TLE493D
 * Tle493d is initially in POWER_DOWN_MODE
 * use POWER_DOWN_MODE for rare and infrequent measurements
 * 	Tle493d will automatically switch to MASTER_CONTROLLED_MODE for one measurement if on a readout
 *	measurements are quite slow in this mode. The power consumption is very low between measurements.
 * use MASTER_CONTROLLED_MODE for low measurement frequencies where results do not have to be up-to-date
 *	In this mode a new measurement starts directly after the last result has been read out.
 * use LOW_POWER_MODE and ULTRA_LOW_POWER_MODE for continuous measurements
 *	each readout returns the latest measurement results
 * use FAST_MODE for for continuous measurements on high frequencies
 *	measurement time might be higher than the time necessary for I2C-readouts in this mode.
 *	Note: Thus, this mode requires a non-standard 1MHz I2C clock to be used to read the data fast enough.
 */

bool TLV493D_bSetAccessMode( Tlv493d_t *pxCxt, AccessMode_e xMode );
/* interrupt is disabled by default
* it is recommended for FAST_MODE, LOW_POWER_MODE and ULTRA_LOW_POWER_MODE
* the interrupt is indicated with a short(1.5 us) low pulse on SCL
* you need to capture and react(read the new results) to it by yourself
*/
void TLV493D_vEnableInterrupt( Tlv493d_t *pxCxt );
void TLV493D_vDisableInterrupt( Tlv493d_t *pxCxt );
/* temperature measurement is enabled by default
* it can be disabled to reduce power consumption
*/
void TLV493D_vEnableTemp( Tlv493d_t *pxCxt );
void TLV493D_vDisableTemp( Tlv493d_t *pxCxt );

/* returns the recommended time between two readouts for the sensor's current configuration */
uint16_t TLV493D_usGetMeasurementDelay( Tlv493d_t *pxCxt );
/* read measurement results from sensor */
Tlv493dError_t TLV493D_xUpdateData( Tlv493d_t *pxCxt );

/* field vector in Cartesian coordinates */
float TLV493D_fGetX( Tlv493d_t *pxCxt );
float TLV493D_fGetY( Tlv493d_t *pxCxt );
float TLV493D_fGetZ( Tlv493d_t *pxCxt );

/* temperature */
float TLV493D_fGetTemp( Tlv493d_t *pxCxt );

/* field vector in spherical coordinates */
float TLV493D_fGetAmount( Tlv493d_t *pxCxt );
float TLV493D_fGetAzimuth( Tlv493d_t *pxCxt );
float TLV493D_fGetPolar( Tlv493d_t *pxCxt );


#endif /* TLV493D_H */

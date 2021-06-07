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

#include <stdbool.h>

#include "tlx493d.h"
#include "tlx493d_interface.h"

#include "TLV_A1B6/tlv_a1b6.h"
#include "TLE_AW2B6/tle_aw2b6.h"
#include "TLE_AW2B6/driver/tle_aw2b6_defines.h"

#include "delay.h"


/* Local data */
static struct {
	TLV493D_SensorType_t sensor_type;
	TLV493D_OpMode_t op_mode;

} LocalData;


/* Public method */

int32_t TLx493D_lInit( void )
{
	int32_t lError;

	/* initial state */
	LocalData.sensor_type = TLx493D_TYPE_UNKNOWN;
	LocalData.op_mode = TLx493D_OP_MODE_NOT_INITIALIZED;

	/* power up the sensor */
	_POWER_DISABLE();
	_POWER_ENABLE();

	/* attempt to init TLE493D-A2B6 or W2B6 */
	lError = TLE493D_AW2B6_lInit( NULL, TLE493D_AW2B6_I2C_A0_ADDR );

	/* A/W2B6 communication was successful */
	if( !lError )
	{
		LocalData.op_mode = TLx493D_OP_MODE_MCM;

		/* the HW version is either A2B6 or W2B6, detect which one */
		dbg_log("SENSOR TYPE: TLE493D\r\n");
		LocalData.sensor_type = TLE493D_xGetHwVersion( NULL );

		/* check if TLI actually */
		/* Set to Fast mode to receive interrupt */
		TLx493D_lSetOperationMode( TLx493D_OP_MODE_FAST );

		/* wait 10ms for interrupt */
		vDelayMs( 10 );

		/* set version to TLI if detected */
		LocalData.sensor_type = TLx493D_TYPE_TLI_W2BW;
	}

	return lError;
}


TLV493D_SensorType_t TLx493D_xGetSensorType( void )
{
	return LocalData.sensor_type;
}


int32_t TLx493D_lSetOperationMode( TLV493D_OpMode_t xMode )
{
	int32_t lError;

	if( TLx493D_TYPE_TLV_A1B6 == LocalData.sensor_type )
	{
		lError = TLV493D_A1B6_set_operation_mode( NULL, xMode );
	}
	else
	{
		lError = TLE493D_AW2B6_lSetOperationMode( NULL, xMode );
	}
	if( !lError )
	{
		LocalData.op_mode = xMode;
	}

	return lError;
}


TLV493D_OpMode_t TLx493D_xGetOperationMode( void )
{
	return LocalData.op_mode;
}


int32_t TLx493D_lReadFrame( TLx493D_DataFrame_t *pxFrame )
{
	if( TLx493D_TYPE_TLV_A1B6 == TLx493D_xGetSensorType() )
	{
		return TLV493D_A1B6_read_frame( NULL, pxFrame );
	}
	else
	{
		return TLE493D_AW2B6_lReadFrame( NULL, pxFrame );
	}
}


int32_t TLx493D_lReadFrameRaw( TLx493D_DataFrameRaw_t *pxFrame )
{
    if( TLx493D_TYPE_TLV_A1B6 == TLx493D_xGetSensorType() )
    {
        return TLV493D_A1B6_read_frame_raw( NULL, pxFrame );
    }
    else
    {
        return TLE493D_AW2B6_lReadFrameRaw( NULL, pxFrame );
    }
}


uint8_t MISC_get_parity( uint8_t ucData )
{
	ucData ^= ucData >> 4;
	ucData ^= ucData >> 2;
	ucData ^= ucData >> 1;

	return ucData & 1U;
}

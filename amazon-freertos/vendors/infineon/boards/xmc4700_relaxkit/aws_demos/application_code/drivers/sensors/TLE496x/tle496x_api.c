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

#include "FreeRTOS.h"

#include "TLE496X_api.h"
#include "TLx4966/corelib/TLx4966.h"
#include "TLE4964/corelib/hall_switch.h"
#include "TLx4966/pal/TLx4966_pal_xmc.h"

#include "DAVE.h"


static TLE496x_t xTLE496x[TLE496x_API_SENSOR_ID_MAX];


int32_t TLE496x_lInit( void **ppvHandle, TLE496xSensorNumber_t xSensorNumber )
{
    int32_t lRetCode = 0;

    while( 1 )
    {
        *ppvHandle = pvPortMalloc( sizeof(TLE496x_t) );
        if( ! (*ppvHandle) )
        {
        	lRetCode = -1;
        	break;
        }

        TLE496x_t *pxCxt = *ppvHandle;
        pxCxt->xSensorNumber = xSensorNumber;

        switch( xSensorNumber )
        {
            case TLE496x_API_SENSOR_ID_ONE:
            {
            	pxCxt->pvCxt = pvPortMalloc( sizeof(HallSwitch_t) );
                if( !pxCxt->pvCxt )
                {
                	lRetCode = -1;
                	break;
                }

                xTLE496x[TLE496x_API_SENSOR_ID_ONE].xSensorNumber = xSensorNumber;
                xTLE496x[TLE496x_API_SENSOR_ID_ONE].pvCxt = pxCxt->pvCxt;

                HallSwitch_t *pxHall = pxCxt->pvCxt;
                pxHall->input_pin.context    = (void*)&TLE4964_DATA_1;
                pxHall->input_pin.init       = (void*)DIGITAL_IO_Init;
                pxHall->input_pin.read       = (void*)DIGITAL_IO_GetInput;
                pxHall->input_pin.write_high = (void*)DIGITAL_IO_SetOutputHigh;
                pxHall->input_pin.write_low  = (void*)DIGITAL_IO_SetOutputLow;
                pxHall->measMode             = HALL_MEAS_MODE_POLLING;
                pxHall->powerMode            = HALL_POWER_MODE_MAIN;
                pxHall->cBack                = NULL;
                HallError_t hall_error = HALL_SWITCH_xInit( pxHall );
                if( hall_error != HALL_ERROR_NONE )
                {
                	lRetCode = -1;
                }
                break;
            }
            case TLE496x_API_SENSOR_ID_TWO:
            {
            	pxCxt->pvCxt = pvPortMalloc( sizeof(HallSwitch_t) );
				if( !pxCxt->pvCxt )
				{
					lRetCode = -1;
					break;
				}

                xTLE496x[TLE496x_API_SENSOR_ID_TWO].xSensorNumber = xSensorNumber;
                xTLE496x[TLE496x_API_SENSOR_ID_TWO].pvCxt = pxCxt->pvCxt;

                HallSwitch_t *pxHall = pxCxt->pvCxt;
                pxHall->input_pin.context    = (void*)&TLE49613K_DATA_1;
                pxHall->input_pin.init       = (void*)DIGITAL_IO_Init;
                pxHall->input_pin.read       = (void*)DIGITAL_IO_GetInput;
                pxHall->input_pin.write_high = (void*)DIGITAL_IO_SetOutputHigh;
                pxHall->input_pin.write_low  = (void*)DIGITAL_IO_SetOutputLow;
                pxHall->measMode             = HALL_MEAS_MODE_POLLING;
                pxHall->powerMode            = HALL_POWER_MODE_MAIN;
                pxHall->cBack                = NULL;
                HallError_t hall_error = HALL_SWITCH_xInit( pxHall );
                if( hall_error != HALL_ERROR_NONE )
                {
                	lRetCode = -1;
                }
                break;
            }
            case TLE496x_API_SENSOR_ID_THREE:
            {
            	pxCxt->pvCxt = pvPortMalloc( sizeof(HallSwitch_t) );
				if( !pxCxt->pvCxt )
				{
					lRetCode = -1;
					break;
				}

                xTLE496x[TLE496x_API_SENSOR_ID_TWO].xSensorNumber = xSensorNumber;
                xTLE496x[TLE496x_API_SENSOR_ID_TWO].pvCxt = pxCxt->pvCxt;

                HallSwitch_t *pxHall = pxCxt->pvCxt;
                pxHall->input_pin.context    = (void*)&TLE4913_DATA_1;
                pxHall->input_pin.init       = (void*)DIGITAL_IO_Init;
                pxHall->input_pin.read       = (void*)DIGITAL_IO_GetInput;
                pxHall->input_pin.write_high = (void*)DIGITAL_IO_SetOutputHigh;
                pxHall->input_pin.write_low  = (void*)DIGITAL_IO_SetOutputLow;
                pxHall->measMode             = HALL_MEAS_MODE_POLLING;
                pxHall->powerMode            = HALL_POWER_MODE_MAIN;
                pxHall->cBack                = NULL;
                HallError_t hall_error = HALL_SWITCH_xInit( pxHall );
                if( hall_error != HALL_ERROR_NONE )
                {
                	lRetCode = -1;
                }
                break;
            }
            case TLE496x_API_SENSOR_ID_FOUR:
            {
            	pxCxt->pvCxt = pvPortMalloc( sizeof(HallSwitch_t) );
				if( !pxCxt->pvCxt )
				{
					lRetCode = -1;
					break;
				}

                xTLE496x[TLE496x_API_SENSOR_ID_TWO].xSensorNumber = xSensorNumber;
                xTLE496x[TLE496x_API_SENSOR_ID_TWO].pvCxt = pxCxt->pvCxt;

                HallSwitch_t *pxHall = pxCxt->pvCxt;
                pxHall->input_pin.context    = (void*)&TLE49611K_DATA_1;
                pxHall->input_pin.init       = (void*)DIGITAL_IO_Init;
                pxHall->input_pin.read       = (void*)DIGITAL_IO_GetInput;
                pxHall->input_pin.write_high = (void*)DIGITAL_IO_SetOutputHigh;
                pxHall->input_pin.write_low  = (void*)DIGITAL_IO_SetOutputLow;
                pxHall->measMode             = HALL_MEAS_MODE_POLLING;
                pxHall->powerMode            = HALL_POWER_MODE_MAIN;
                pxHall->cBack                = NULL;
                HallError_t hall_error = HALL_SWITCH_xInit( pxHall );
                if( hall_error != HALL_ERROR_NONE )
                {
                	lRetCode = -1;
                }
                break;
            }
            case TLE496x_API_SENSOR_ID_FIVE:
            {
            	pxCxt->pvCxt = pvPortMalloc( sizeof(HallSwitch_t) );
				if( !pxCxt->pvCxt )
				{
					lRetCode = -1;
					break;
				}

                TLx4966_Handle_t *tl4966_cxt = pxCxt->pvCxt;
                TLx4966_Config( tl4966_cxt, 1, TLx4966_POWMODE_MAIN, TLx4966_MEASMODE_TIMER,
                        TLx4966_SPEED_HERTZ, &TLx4966_release_pinout );
                TLx4966_Error_t err = TLx4966_Init( tl4966_cxt );
                if( err != TLx4966_OK )
                {
                	lRetCode = -1;
                	break;
                }
                err = TLx4966_Enable( tl4966_cxt );
                if( err != TLx4966_OK )
                {
                	lRetCode = -1;
                	break;
                }
                break;
            }
            default:
                lRetCode = -1;
                break;
        }
        break;
    }
    if( lRetCode < 0)
    {
        vPortFree(*ppvHandle);
    }

    return lRetCode;
}


int32_t TLE496x_lGetData( void *pvHandle, TLE496xData_t *pxSensorData )
{
    int32_t lRet = 0;
    TLE496x_t *pxTle = pvHandle;

    switch( pxTle->xSensorNumber )
    {
        case TLE496x_API_SENSOR_ID_ONE:
        case TLE496x_API_SENSOR_ID_TWO:
        case TLE496x_API_SENSOR_ID_THREE:
        case TLE496x_API_SENSOR_ID_FOUR:
        	HALL_SWITCH_xBFieldUpdate( (HallSwitch_t*)pxTle->pvCxt );
        	pxSensorData->lMagneticFieldValue = HALL_SWITCH_xBFieldGet( (HallSwitch_t*)pxTle->pvCxt );
            break;
        case TLE496x_API_SENSOR_ID_FIVE:
            TLx4966_UpdateValues( (TLx4966_Handle_t*)pxTle->pvCxt );
            pxSensorData->fSpeed = TLx4966_GetSpeed( (TLx4966_Handle_t*)pxTle->pvCxt );
            pxSensorData->lDirection = TLx4966_GetDirection( (TLx4966_Handle_t*)pxTle->pvCxt );
            break;
        default:
        	lRet = -1;
        	break;
    }

    return lRet;
}


void TLE496x_vDeInit( void **ppvHandle )
{
	vPortFree( *ppvHandle );
}


void TLE496x_vReset( void *pvHandle )
{

}

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

#include "dps368_api.h"

#include "corelib/dps368_io.h"
#include "spi_mux/spi_mux.h"


int32_t DPS368_lInit( void **ppvHandle, DPS368SensorNumber_t xSensorNumber )
{
	int32_t lRetCode = -1;

    while( 1 )
    {
        *ppvHandle = pvPortMalloc( sizeof(DPS368_t) );
        if( !(*ppvHandle) )
        {
        	lRetCode = -1;
        	break;
        }

        DPS368_t *pxCxt = *ppvHandle;
        switch( xSensorNumber )
        {
            case DPS368_API_SENSOR_ID_1:
            	lRetCode = DPS368_lConnect( pxCxt, &xDps368FunctionsSPI_1 );
                break;
            case DPS368_API_SENSOR_ID_2:
            	lRetCode = DPS368_lConnect( pxCxt, &xDps368FunctionsSPI_2 );
                break;
            case DPS368_API_SENSOR_ID_3:
            	lRetCode = DPS368_lConnect( pxCxt, &xDps368FunctionsSPI_3 );
                break;
            case DPS368_API_SENSOR_ID_4:
            	lRetCode = DPS368_lConnect( pxCxt, &xDps368FunctionsI2C_1 );
                break;
            case DPS368_API_SENSOR_ID_5:
            	lRetCode = DPS368_lConnect( pxCxt, &xDps368FunctionsI2C_2 );
                break;
            default:
            	lRetCode = -1;
                break;

        }
        break;
    }
    if( lRetCode < 0 )
    {
        vPortFree( *ppvHandle );
    }
    return lRetCode;
}


int32_t DPS368_lGetData( void *pvHandle, DPS368Data_t *pxSensorData )
{
	int32_t lRet = 0;

	lRet = DPS368_lGetProcessedData( pvHandle, &pxSensorData->fPressure,  &pxSensorData->fTemperature );

	if( (uint32_t)pxSensorData->fTemperature >= 110 && (uint32_t)pxSensorData->fTemperature <= 114 )
	{
		return -1;
	}

    return lRet;
}


void DPS368_vDeInit( void **ppvHandle )
{
	if( !(*ppvHandle) )
	{
	    return;
	}
	else
	{
		vPortFree( *ppvHandle );
	}

}


void DPS368_vReset( void *pvHandle )
{

}

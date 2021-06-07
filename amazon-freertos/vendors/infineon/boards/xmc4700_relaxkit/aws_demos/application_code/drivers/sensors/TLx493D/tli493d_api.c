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

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "TLE_AW2B6/tle_aw2b6.h"
#include "tli493d_api.h"

#include "tlx493d_interface.h"


int32_t TLI493D_lInit( void **ppvHandle, TLI493DSensorNumber_t xSensorNumber )
{
	int32_t lRetCode = -1;

    while( 1 )
    {
        *ppvHandle = pvPortMalloc( sizeof(TLE493D_Data_t) );
        if(! (*ppvHandle))
        {
        	break;
        }

        TLE493D_Data_t *pxCxt = *ppvHandle;
        uint8_t ucAddr;

        switch( xSensorNumber )
        {
            case TLI493D_API_SENSOR_ID_ONE:
                ucAddr = TLE493D_AW2B6_I2C_A0_ADDR;
                break;
            case TLI493D_API_SENSOR_ID_TWO:
                ucAddr = TLE493D_AW2B6_I2C_A1_ADDR;
                break;
            default:
            	ucAddr = 0;
            	break;
        }

        if( !ucAddr )
        {
        	break;
        }

        /* attempt to init TLE493D-A2B6 or W2B6 */
        int32_t lError = TLE493D_AW2B6_lInit( pxCxt, ucAddr );

        /* A/W2B6 communication was successful */
        if( lError )
        {
        	break;
        }

        /* the HW version is either A2B6 or W2B6, detect which one */
        dbg_log( ("SENSOR TYPE: TLI493D\r\n") );
        TLE493D_xGetHwVersion( pxCxt );

        /* check if TLI actually */
        /* Set to Fast mode */
        lError = TLE493D_AW2B6_lSetOperationMode( pxCxt, TLx493D_OP_MODE_FAST );
        vTaskDelay( 10 );
        if( lError )
        {
        	break;
        }

        lRetCode = 0;
        break;
    }

    if( lRetCode < 0 )
    {
        vPortFree( *ppvHandle );
    }

    return lRetCode;
}


void TLI493D_vDeInit( void **ppvHandle )
{
	vPortFree( *ppvHandle );
}


int32_t TLI493D_lGetData( void *pvHandle, TLI493DData_t *pxSensorData )
{
    TLE493D_Data_t *pxCxt = pvHandle;
    return TLE493D_AW2B6_lReadFrame( pxCxt, (TLx493D_DataFrame_t*)pxSensorData );
}


void TLI493D_vReset( void *pvHandle )
{

}

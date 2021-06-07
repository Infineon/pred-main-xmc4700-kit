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

#include "dps368_test.h"
#include "DPS368/dps368_api.h"

#include "console_io.h"
#include "iot_demo_logging.h"

bool DPS368_bTest( void )
{
    void *pxCxt;

    int32_t lRetCode = DPS368_lInit( &pxCxt, DPS368_API_SENSOR_ID_1 );

    while( lRetCode == 0 )
    {
        DPS368Data_t xData = { 0 };
        lRetCode = DPS368_lGetData( pxCxt, &xData );
        configPRINTF( ("DPS368 Temp: %.2f, Press: %.2f\n",xData.fTemperature, xData.fPressure) );
        vTaskDelay( 1 );
    }

    return lRetCode == 0 ? true : false;
}

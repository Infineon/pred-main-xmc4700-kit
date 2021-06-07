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

#define TLI493D_TEST_A  1
#define TLI493D_TEST_B  1

#include "FreeRTOS.h"
#include "task.h"
#include "TLx493D/TLI493D_api.h"


bool TLI493D_bTest( void )
{
#if ( TLI493D_TEST_A > 0 )

    void *pvCxt_1;
    TLI493D_lInit( &pvCxt_1, TLI493D_API_SENSOR_ID_ONE );

    while( 1 )
    {
        TLI493DData_t xFrame = { 0 };
        if( TLI493D_lGetData( pvCxt_1, &xFrame ) == 0 )
        {
            configPRINTF( ("TLI493D x: %.4f, y: %.4f, z: %.4f, \n", xFrame.fMagneticFieldIntensityX, xFrame.fMagneticFieldIntensityY, xFrame.fMagneticFieldIntensityZ) );
        }
        vTaskDelay( 200 );
    }

#endif

#if ( TLI493D_TEST_B > 0 )

    TLx493D_lInit();

    while( 1 )
    {
        TLx493D_DataFrame_t xFrame = { 0 };
        if( TLx493D_lReadFrame(&xFrame) == 0 )
        {
            configPRINTF( ("TLI493D x: %.4f, y: %.4f, z: %.4f, \n",xFrame.x, xFrame.y, xFrame.z) );
        }
        vTaskDelay( 200 );
    }

#endif
}

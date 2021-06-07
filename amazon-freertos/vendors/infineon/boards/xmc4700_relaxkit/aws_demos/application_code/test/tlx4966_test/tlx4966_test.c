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

#include "TLx4966_test.h"
#include "TLE496x/TLx4966/corelib/tlx4966.h"
#include "TLE496x/TLx4966/pal/tlx4966_pal_xmc.h"


bool TLx4966_bTest( void )
{
	TLx4966_Handle_t xCxt;

    TLx4966_Config( &xCxt, 1, TLx4966_POWMODE_MAIN, TLx4966_MEASMODE_POLLING,
            TLx4966_SPEED_HERTZ, &TLx4966_Shield2Go_poll );
    TLx4966_Init( &xCxt );
    TLx4966_Enable( &xCxt );

    while( 1 )
    {
        TLx4966_UpdateValues( &xCxt );
        configPRINTF( ("TLx4966: speed = %4.1f, dir = %2d \n", TLx4966_GetSpeed( &xCxt ), TLx4966_GetDirection( &xCxt )) );
        vTaskDelay( 250 );
    }
}

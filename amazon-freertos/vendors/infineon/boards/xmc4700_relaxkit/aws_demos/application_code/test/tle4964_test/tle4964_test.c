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
#include "tle4964_test.h"
#include "TLE496x/TLE4964/corelib/hall_switch.h"
#include "DAVE.h"


static HallSwitch_t xHallTle4964_1;


static void prvTle4964Interrupt_1( HallResult_t xVal )
{

}

bool TLE4964_bTest( void )
{
    xHallTle4964_1.input_pin.context    = (void*)&TLE4964_DATA_1;
    xHallTle4964_1.input_pin.init       = (void*)DIGITAL_IO_Init;
    xHallTle4964_1.input_pin.read       = (void*)DIGITAL_IO_GetInput;
    xHallTle4964_1.input_pin.write_high = (void*)DIGITAL_IO_SetOutputHigh;
    xHallTle4964_1.input_pin.write_low  = (void*)DIGITAL_IO_SetOutputLow;
    xHallTle4964_1.measMode             = HALL_MEAS_MODE_POLLING;
    xHallTle4964_1.powerMode            = HALL_POWER_MODE_MAIN;
    xHallTle4964_1.cBack                = prvTle4964Interrupt_1;

    HALL_SWITCH_xInit( &xHallTle4964_1 );

    while( 1 )
    {
    	HALL_SWITCH_xBFieldUpdate( &xHallTle4964_1 );
        HallResult_t xR1 = HALL_SWITCH_xBFieldGet( &xHallTle4964_1 );

        configPRINTF( ("TLE4964: %d\n", xR1) );
    }

}

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

#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"

#include "../corelib/TLx4966_types.h"
#include "TLx4966_pal_xmc.h"

#include "DAVE.h"


/* Current time */
static uint32_t ulCurrentTime = 0;


static TLx4966_Error_t GPIO_Speed_Init( void )
{
    /* Capture pin is already initialized in DAVE_Itint(); */
    return TLx4966_OK;
};

static TLx4966_GPIOLevel_t GPIO_Speed_Read( void )
{
	return XMC_GPIO_GetInput(CAPTURE_TLI4966G_SPEED.input->port, CAPTURE_TLI4966G_SPEED.input->pin);
}

TLx4966_GPIO_t speed =
{
    &GPIO_Speed_Init,
    NULL,
    NULL,
    NULL,
    &GPIO_Speed_Read,
    NULL,
    NULL
};

static TLx4966_Error_t GPIO_Dir_Init( void )
{
    //DIGITAL_IO_Init( &TLI4966G_DIRECTION_Q1 );
	/* TLI4966G_DIRECTION_Q1 pin is already initialized in DAVE_Itint(); */
    return TLx4966_OK;
};

static TLx4966_GPIOLevel_t GPIO_Dir_Read( void )
{
    return DIGITAL_IO_GetInput(&TLI4966G_DIRECTION_Q1);
}

TLx4966_GPIO_t direction =
{
    GPIO_Dir_Init,
    NULL,
    NULL,
    NULL,
    GPIO_Dir_Read,
    NULL,
    NULL
};

static TLx4966_Error_t Timer_Init( void )
{
    /**  Initialization of CAPTURE APP instance CAPTURE_TLI4966G_SPEED */
    CAPTURE_STATUS_t xInitStatus = CAPTURE_Init(&CAPTURE_TLI4966G_SPEED);

    return xInitStatus == CAPTURE_STATUS_SUCCESS ? TLx4966_OK : TLx4966_INTF_ERROR;
}

static void Timer_Start( void )
{
    ulCurrentTime = xTaskGetTickCount();
}

static double Timer_Elapsed( void )
{
    double fElapsedTime;
    uint32_t ulSignalPeriod = 0;

    if( CAPTURE_GetPeriodInNanoSec( &CAPTURE_TLI4966G_SPEED, &ulSignalPeriod ) == CAPTURE_STATUS_NEW_VAL_NOT_CAPTURED )
    {
        fElapsedTime = ( xTaskGetTickCount() - ulCurrentTime );
    }
    else
    {
        Timer_Start();
        fElapsedTime = (double)ulSignalPeriod / 1000000.0;
    }

    return fElapsedTime;
}

static void Timer_Stop( void )
{

}

static TLx4966_Error_t Timer_Delay( uint32_t ulTimeout )
{
    vTaskDelay( ulTimeout );
    return TLx4966_OK;
}

TLx4966_Timer_t timer = 
{
    &Timer_Init,
    &Timer_Start,
    &Timer_Elapsed,
    &Timer_Stop,
    &Timer_Delay
};

TLx4966_HwIntf_t TLx4966_Shield2Go_poll =
{
    NULL,
    &direction,
    &speed,
    &timer
};


TLx4966_HwIntf_t TLx4966_release_pinout =
{
    NULL,
    &direction,
    NULL,
    &timer
};

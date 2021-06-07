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
#include "semphr.h"
#include "task.h"

#include "xmc_gpio.h"
#include "xmc_dma.h"
#include "xmc_uart.h"
#include "xmc_scu.h"


/*
 * Static function for delay
 *
 */
static uint8_t prvSysSemCreate( SemaphoreHandle_t *pxSem, uint8_t ucCnt )
{
    *pxSem = xSemaphoreCreateBinary();

    if( *pxSem != NULL && ucCnt )
    {
        xSemaphoreGive( *pxSem );
    }

    return *pxSem != NULL;
}

static uint8_t prvSysSemDelete( SemaphoreHandle_t *pxSem )
{
    vSemaphoreDelete( *pxSem );

    return 1;
}

static uint32_t prvSysSemWait( SemaphoreHandle_t *pxSem, uint32_t ulTimeout )
{
    uint32_t ulTime = xTaskGetTickCount();
    BaseType_t xRet = xSemaphoreTake( *pxSem, !ulTimeout ? portMAX_DELAY : ulTimeout ) == pdPASS ? ( xTaskGetTickCount() - ulTime ) : ( (TickType_t)portMAX_DELAY );

    return xRet;
}

static uint8_t prvSysSemRelease( SemaphoreHandle_t *pxSem )
{
    return xSemaphoreGive( *pxSem ) == pdPASS;
}


/**
  * @brief  Delay
  * @param  Delay in ms
  * @retval None
  */
void vDelayMs( uint32_t ulMs )
{
	SemaphoreHandle_t xSem;

    if( ulMs == 0 )
    {
        return;
    }

    if( prvSysSemCreate( &xSem, 0 ) )
    {
    	prvSysSemWait( &xSem, ulMs );
        prvSysSemRelease( &xSem );
        prvSysSemDelete( &xSem );
    }
}


void vDelayTicks( uint32_t ulCycles )
{
	while( --ulCycles )
	{
		__NOP();
	}
}


bool bWaitBusBusy( bool (*INTERFACE_IsBusy)( void ), uint32_t ulTimeout )
{
	uint32_t ulTickStart = xTaskGetTickCount();

	while( INTERFACE_IsBusy() )
	{
		if( ( xTaskGetTickCount() - ulTickStart ) > ulTimeout )
		{
			return false;
		}
	}

	return true;
}

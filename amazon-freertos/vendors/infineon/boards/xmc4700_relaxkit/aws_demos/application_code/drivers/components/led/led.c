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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "DAVE.h"

#include "led.h"



static QueueHandle_t xLedStateQueue;


/**
  * @brief  LED0 turn on.
  */
static void LED_0_prvOn( void )
{
	DIGITAL_IO_SetOutputHigh( &LED_YELLOWISH_GREEN );
}


/**
  * @brief  LED0 turn off.
  */
static void LED_0_prvOff( void )
{
	DIGITAL_IO_SetOutputLow( &LED_YELLOWISH_GREEN );
}


/**
  * @brief  Toggles the LED0.
  */
void LED_0_prvToggle( void )
{
	DIGITAL_IO_ToggleOutput( &LED_YELLOWISH_GREEN );
}


/**
  * @brief  LED1 turn on.
  */
void LED_1_prvOn( void )
{
	DIGITAL_IO_SetOutputHigh( &LED_YELLOW );
}


/**
  * @brief  LED1 turn off.
  */
void LED_1_prvOff( void )
{
	DIGITAL_IO_SetOutputLow( &LED_YELLOW );
}


/**
  * @brief  Toggles the LED1.
  */
void LED_1_prvToggle( void )
{
	DIGITAL_IO_ToggleOutput( &LED_YELLOW );
}


/**
  * @brief  LED2 turn on.
  */
void LED_2_prvOn( void )
{
	DIGITAL_IO_SetOutputHigh( &LED_RED );
}


/**
  * @brief  LED2 turn off.
  */
void LED_2_prvOff( void )
{
	DIGITAL_IO_SetOutputLow( &LED_RED );
}


/**
  * @brief  Toggles the LED2.
  */
void LED_2_prvToggle( void )
{
	DIGITAL_IO_ToggleOutput( &LED_RED );
}


LED_STATUS_t LED_xInit( void )
{
    xLedStateQueue = xQueueCreate( 10, sizeof( LedState_t ) );
    if( xLedStateQueue == NULL )
    {
    	return LED_STATUS_FAILURE;
    }

    return LED_STATUS_SUCCESS;
}


void LED_vOn( LedType_t xType )
{
    switch( xType )
    {
        case LED0_YELLOWISH_GREEN:
            LED_0_prvOn();
            break;
        case LED1_YELLOW:
        	LED_1_prvOn();
            break;
        case LED2_RED:
        	LED_2_prvOn();
            break;
        default:
            break;
    }
}


void LED_vOff( LedType_t xType )
{
    switch( xType )
    {
        case LED0_YELLOWISH_GREEN:
            LED_0_prvOff();
            break;
        case LED1_YELLOW:
        	LED_1_prvOff();
            break;
        case LED2_RED:
        	LED_2_prvOff();
            break;
        default:
            break;
    }
}


void LED_vToggle( LedType_t xType )
{
    switch( xType )
    {
        case LED0_YELLOWISH_GREEN:
            LED_0_prvToggle();
            break;
        case LED1_YELLOW:
        	LED_1_prvToggle();
        	break;
        case LED2_RED:
        	LED_2_prvToggle();
            break;
        default:
            break;
    }
}


LED_STATUS_t LED_xQueueSend( LedType_t xType, LedMode_t xMode, LedBlinkTime_t xBlinkTime )
{
	LED_STATUS_t xRc = LED_STATUS_SUCCESS;

    LedState_t xLedState;

    xLedState.type = xType;
    xLedState.mode = xMode;
    xLedState.blinkTime = ( uint32_t )xBlinkTime;

    if( xLedStateQueue != NULL )
    {
    	if( xQueueSend( xLedStateQueue, &xLedState, ( TickType_t )0 ) != pdTRUE ) 
		{
			xRc = LED_STATUS_FAILURE;
		}
    }
    else
    {
    	xRc = LED_STATUS_FAILURE;
    }

    return xRc;
}


LED_STATUS_t LED_xQueueReceive( LedState_t *pxLedState )
{
	LED_STATUS_t xRc = LED_STATUS_SUCCESS;

    if( xLedStateQueue != NULL )
	{
    	if( xQueueReceive( xLedStateQueue, pxLedState, ( TickType_t ) 0 ) != pdTRUE )
		{
			xRc = LED_STATUS_FAILURE;
		}
	}
	else
	{
		xRc = LED_STATUS_FAILURE;
	}

	return xRc;
}


LED_STATUS_t LED_xStatus( LedOperation_t xOperation, LedOperationStatus_t xStatusOperation )
{
	LED_STATUS_t xRc = LED_STATUS_SUCCESS;

	switch( xOperation )
	{
		case HEARTBEAT:
		{
			switch( xStatusOperation )
			{
				case START:
					xRc = LED_xQueueSend( LED0_YELLOWISH_GREEN, LED_STATE_BLINK, BLINK_TIME_HEARTBEAT );
					break;
				default:
					break;
			}
			break;
		}
		case KEY_PROV:
		{
			switch( xStatusOperation )
			{
				case START:
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_ON, 0 );
					break;
				case SUCCESS:
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_OFF, 0 );
					break;
				case FAILED:
					xRc = LED_xQueueSend( LED2_RED, LED_STATE_ON, 0 );
					break;
				default:
					break;
			}
			break;
		}
		case WIFI:
		{
			switch( xStatusOperation )
			{
				case START:
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_BLINK, BLINK_TIME_WIFI );
					break;
				case SUCCESS:
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_OFF, 0 );
					break;
				case FAILED:
					xRc = LED_xQueueSend( LED2_RED, LED_STATE_BLINK, BLINK_TIME_WIFI );
					break;
				default:
					break;
			}
			break;
		}
		case MQTT:
		{
			switch( xStatusOperation )
			{
				case START:
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_BLINK, BLINK_TIME_MQTT );
					break;
				case SUCCESS:
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_OFF, 0 );
					break;
				case FAILED:
					xRc = LED_xQueueSend( LED2_RED, LED_STATE_BLINK, BLINK_TIME_MQTT );
					break;
				default:
					break;
			}
			break;
		}
		case MESSAGE:
		{
			switch( xStatusOperation )
			{
				case START:
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_OFF, 0 );
					break;
				case SUCCESS:
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_BLINK, BLINK_TIME_MESSAGE );
					if( xRc != pdTRUE )
					{
						break;
					}
					xRc = LED_xQueueSend( LED2_RED, LED_STATE_OFF, 0 );
					break;
				case FAILED:
					xRc = LED_xQueueSend( LED2_RED, LED_STATE_BLINK, BLINK_TIME_MESSAGE );
					if( xRc != pdTRUE )
					{
						break;
					}
					xRc = LED_xQueueSend( LED1_YELLOW, LED_STATE_OFF, 0  );
					break;
				default:
					break;
			}
			break;
		}
		default:
			break;

	}


	return xRc;
}


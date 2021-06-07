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

#ifndef LED_H
#define LED_H

#include "FreeRTOS.h"
#include "queue.h"


typedef enum {
  LED_STATUS_SUCCESS = 0U,              /**< Initialization is success */
  LED_STATUS_FAILURE = 1U         		/**< Initialization is failure */

} LED_STATUS_t;


/* blink periodic time for status indication in ms */
typedef enum {
	/* used YELLOW LED */
	BLINK_TIME_WIFI = 100,
	BLINK_TIME_MQTT = 300,
	BLINK_TIME_MESSAGE = 1000,
	/* used YELLOW_GREEN LED */
	BLINK_TIME_HEARTBEAT = 1000

} LedBlinkTime_t;

typedef enum {
	HEARTBEAT = 0,
    KEY_PROV,
    WIFI,
    MQTT,
    MESSAGE

} LedOperation_t;

typedef enum {
	START = 0,
	SUCCESS,
	FAILED

} LedOperationStatus_t;

typedef enum {
    LED0_YELLOWISH_GREEN = 0,
    LED1_YELLOW,
    LED2_RED,
    LEDS_NUM

} LedType_t;


typedef enum {
    LED_STATE_OFF = 0,
    LED_STATE_ON,
    LED_STATE_BLINK,
    LED_STATES_NUM

} LedMode_t;


typedef struct {
	LedType_t type;
    LedMode_t mode;
    uint32_t blinkTime;

} LedState_t;


LED_STATUS_t LED_xInit( void );
LED_STATUS_t LED_xQueueSend( LedType_t xType, LedMode_t xMode, LedBlinkTime_t xBlinkTime );
LED_STATUS_t LED_xQueueReceive( LedState_t *pxLedState );
void LED_vOn( LedType_t xType );
void LED_vOff( LedType_t xType );
void LED_vToggle( LedType_t xType );

LED_STATUS_t LED_xStatus( LedOperation_t xOperation, LedOperationStatus_t xStatusOperation );


#endif /* LED_H */

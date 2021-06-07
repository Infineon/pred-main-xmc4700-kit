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

#ifndef MQTT_TASK_H
#define MQTT_TASK_H

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"

#include "app_error.h"
#include "app_types.h"

#include "statistic.h"
#include "base64.h"
#include "iot_network_manager_private.h"

/* Defining message format */
#define MQTT_OUTPUT_FORMAT_JSON                         1

/** Timeout for the TLS negotiation */
#define mqtttaskMQTT_ECHO_TLS_NEGOTIATION_TIMEOUT       pdMS_TO_TICKS( 15000 )
/** Timeout for MQTT operations */
#define mqtttaskMQTT_TIMEOUT                            pdMS_TO_TICKS( 3000 )
/** The number of items in the receive queue */
#define mqtttaskRECEIVE_QUEUE_LENGTH                    ( 2 )
/** Size of the buffer in which messages to the broker will be generated */
#define mqtttaskSEND_BUFFER_SIZE                        ( 4096 )
/** Stack allocated for the task */
#define mqtttaskSTACK_SIZE                              ( 4096 )
/** Priority of the task */
#define mqtttaskPRIORITY                                ( tskIDLE_PRIORITY + 4 )

/** Stack allocated for the task */
#define robusttaskPRIORITY                              ( tskIDLE_PRIORITY + 3 )
/** Priority of the task */
#define ROBUST_TASK_STACK_SIZE                   	    ( 1024 )
/** Robust Task ping period */
#if NBIOT_ENABLED
#define ROBUST_DELAY                              	    ( 5000 )
#else
#define ROBUST_DELAY                              	    ( 3000 )
#endif
/** ping timeout */
#define PING_TIMEOUT                            	    ( 100 )
/** ping retries */
#define PING_COUNT                            	 	    ( 3 )

/** Network connection reestablishing retries period */
#define RECONNECT_DELAY							 	    ( 10 )

/* Number of ping attempt */
#define ATTEMPTS_COUNT									( 3 )


typedef enum {
	eConnEstablished = 0,	/* Connection established. */
	eNetworkError,			/* Network error. */
	eMqttError				/* MQTT error. */

} eConnectionState_t;


typedef enum {
	ePingSuccess = 0,	/* Ping Success. */
	ePingFail			/* Ping Fail. */

} ePingStatus_t;


/* Queue for messages between sensors and mqtt tasks */
extern QueueHandle_t xMQTTMessageQueueHandle;


/** @brief Starts the MQTT task */
void vMqttTaskStart( void );
/** @brief Deletes the MQTT task */
void vMqttTaskDelete( void );

/* Initialize network, manager and libraries */
uint8_t ucNetworkInitialize( void );


#endif /* MQTT_TASK_H */

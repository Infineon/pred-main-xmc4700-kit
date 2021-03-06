/*
 * FreeRTOS V1.4.7
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 *
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

#ifndef _AWS_DEMO_CONFIG_H_
#define _AWS_DEMO_CONFIG_H_

/* To run a particular demo you need to define one of these.
 * Only one demo can be configured at a time
 *
 *          CONFIG_MQTT_DEMO_ENABLED
 *          CONFIG_SHADOW_DEMO_ENABLED
 *          CONFIG_GREENGRASS_DISCOVERY_DEMO_ENABLED
 *          CONFIG_TCP_ECHO_CLIENT_DEMO_ENABLED
 *          CONFIG_DEFENDER_DEMO_ENABLED
 *          CONFIG_POSIX_DEMO_ENABLED
 *          CONFIG_HTTPS_SYNC_DOWNLOAD_DEMO_ENABLED
 *          CONFIG_HTTPS_ASYNC_DOWNLOAD_DEMO_ENABLED
 *          CONFIG_HTTPS_SYNC_UPLOAD_DEMO_ENABLED
 *          CONFIG_HTTPS_ASYNC_UPLOAD_DEMO_ENABLED
 *
 *  These defines are used in iot_demo_runner.h for demo selection */

#define CONFIG_MQTT_DEMO_ENABLED

/* Default configuration for all demos. Individual demos can override these below */
#define democonfigDEMO_STACKSIZE                        ( configMINIMAL_STACK_SIZE * 12 )
#define democonfigDEMO_PRIORITY                         ( tskIDLE_PRIORITY + 5 )
#define democonfigNETWORK_TYPES                         ( AWSIOT_NETWORK_TYPE_NBIOT )

#define democonfigSHADOW_DEMO_NUM_TASKS                 ( 2 )
#define democonfigSHADOW_DEMO_TASK_STACK_SIZE           ( configMINIMAL_STACK_SIZE * 4 )
#define democonfigSHADOW_DEMO_TASK_PRIORITY             ( tskIDLE_PRIORITY )
#define shadowDemoUPDATE_TASK_STACK_SIZE                ( configMINIMAL_STACK_SIZE * 5 )

#define democonfigMQTT_ECHO_TLS_NEGOTIATION_TIMEOUT     pdMS_TO_TICKS( 12000 )
#define democonfigMQTT_ECHO_TASK_STACK_SIZE             ( configMINIMAL_STACK_SIZE * 4)
#define democonfigMQTT_ECHO_TASK_PRIORITY               ( tskIDLE_PRIORITY )

/* Number of sub pub tasks that connect to a broker that is not using TLS. */
#define democonfigMQTT_SUB_PUB_NUM_UNSECURE_TASKS       ( 1 )
/* Number of sub pub tasks that connect to a broker that is using TLS. */
#define democonfigMQTT_SUB_PUB_NUM_SECURE_TASKS         ( 1 )

#define democonfigMQTT_SUB_PUB_TASK_STACK_SIZE          ( configMINIMAL_STACK_SIZE * 5 )
#define democonfigMQTT_SUB_PUB_TASK_PRIORITY            ( tskIDLE_PRIORITY )

/* Greengrass discovery example task parameters. */
#define democonfigGREENGRASS_DISCOVERY_TASK_STACK_SIZE  ( configMINIMAL_STACK_SIZE * 16 )
#define democonfigGREENGRASS_DISCOVERY_TASK_PRIORITY    ( tskIDLE_PRIORITY )

/* Timeout used when performing MQTT operations that do not need extra time
 * to perform a TLS negotiation. */
#define democonfigMQTT_TIMEOUT                         pdMS_TO_TICKS( 3000 )

/* Send AWS IoT MQTT traffic encrypted to destination port 443. */
#define democonfigMQTT_AGENT_CONNECT_FLAGS             ( mqttagentREQUIRE_TLS | mqttagentUSE_AWS_IOT_ALPN_443 )

#define democonfigMEMORY_ANALYSIS

#ifdef democonfigMEMORY_ANALYSIS
    #define democonfigMEMORY_ANALYSIS_STACK_DEPTH_TYPE    UBaseType_t
    #define democonfigMEMORY_ANALYSIS_MIN_EVER_HEAP_SIZE()        xPortGetMinimumEverFreeHeapSize()
    #if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 )
        /* Convert from stack words to bytes */
        #define democonfigMEMORY_ANALYSIS_STACK_WATERMARK( x )    uxTaskGetStackHighWaterMark( x ) * ( uint32_t ) sizeof( StackType_t ); /*lint !e961 Casting is not redundant on smaller architectures. */
    #else
        #define democonfigMEMORY_ANALYSIS_STACK_WATERMARK( x )    NULL
    #endif /* if( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
#endif /* democonfigMEMORY_ANALYSIS */

#endif /* _AWS_DEMO_CONFIG_H_ */

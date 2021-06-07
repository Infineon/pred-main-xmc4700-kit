/*
 * FreeRTOS Common V1.1.1
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

/**
 * @file iot_network_types.h
 * @brief Header file contains the network types shared by both low level networking drivers
 * and upper level applications.
 */

#ifndef IOT_NETWORK_TYPES_H_
#define IOT_NETWORK_TYPES_H_

/**
 * @brief Network types supported by FreeRTOS.
 */
#define AWSIOT_NETWORK_TYPE_NONE      0x00000000
#define AWSIOT_NETWORK_TYPE_WIFI      0x00000001
#define AWSIOT_NETWORK_TYPE_BLE       0x00000002
#define AWSIOT_NETWORK_TYPE_ETH       0x00000004
#define AWSIOT_NETWORK_TYPE_NBIOT     0x00000008
#define AWSIOT_NETWORK_TYPE_ALL       ( AWSIOT_NETWORK_TYPE_WIFI | AWSIOT_NETWORK_TYPE_BLE | AWSIOT_NETWORK_TYPE_ETH | AWSIOT_NETWORK_TYPE_NBIOT )
#define AWSIOT_NETWORK_TYPE_TCP_IP    ( AWSIOT_NETWORK_TYPE_WIFI | AWSIOT_NETWORK_TYPE_ETH | AWSIOT_NETWORK_TYPE_NBIOT )

/**
 * @brief Enum types representing states for different networks.
 */
typedef enum AwsIotNetworkState
{
    eNetworkStateUnknown = 0, /*!< eNetworkStateUnknown State of the network is unknown */
    eNetworkStateDisabled,    /*!< eNetworkStateDisabled State of the network is disabled/disconnected */
    eNetworkStateEnabled      /*!< eNetworkStateEnabled  State of the network is enabled and connected. */
} AwsIotNetworkState_t;


/**
 * @brief Callback invoked by a driver to post network state change events.
 */
typedef void ( * IotNetworkStateChangeEventCallback_t ) ( uint32_t ulNetworkType,
                                                          AwsIotNetworkState_t xState );

#endif /* IOT_NETWORK_TYPES_H_ */

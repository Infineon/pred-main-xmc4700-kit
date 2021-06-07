/*
* FreeRTOS
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
 * @file aws_iot_network_config.h
 * @brief Configuration file which enables different network types.
 */
#ifndef AWS_IOT_NETWORK_CONFIG_H_
#define AWS_IOT_NETWORK_CONFIG_H_

/**
 * @brief Configuration flag used to specify all supported network types by the board.
 *
 * The configuration is fixed per board and should never be changed.
 * More than one network interfaces can be enabled by using 'OR' operation with flags for
 * each network types supported. Flags for all supported network types can be found
 * in "aws_iot_network.h"
 */

#define configSUPPORTED_NETWORKS    ( AWSIOT_NETWORK_TYPE_WIFI | AWSIOT_NETWORK_TYPE_NBIOT )

/**
 * @brief Configuration flag which is used to enable one or more network interfaces for a board.
 *
 * The configuration can be changed any time to keep one or more network enabled or disabled.
 * More than one network interfaces can be enabled by using 'OR' operation with flags for
 * each network types supported. Flags for all supported network types can be found
 * in "aws_iot_network.h"
 *
 */

#define configENABLED_NETWORKS      ( AWSIOT_NETWORK_TYPE_WIFI )

#endif /* CONFIG_FILES_AWS_IOT_NETWORK_CONFIG_H_ */

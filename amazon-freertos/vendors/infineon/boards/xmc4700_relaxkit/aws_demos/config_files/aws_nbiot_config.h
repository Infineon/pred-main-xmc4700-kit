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

#ifndef _AWS_NBIOT_CONFIG_H_
#define _AWS_NBIOT_CONFIG_H_

#include "iot_network_manager_private.h"

#if NBIOT_ENABLED
/* 'LTE IoT 2 Click' module can work in one of next modes:
 * eMODEM_MODE_GSM 	 (GSM/GPRS/EDGE mode)
 * eMODEM_MODE_NBIOT (LTE Cat NB1 mode)
 * eMODEM_MODE_CATM1 (LTE Cat M1 mode)
 */
#define LTE_MODEM_MODE 						eMODEM_MODE_GSM

#endif /* AWSIOT_NETWORK_TYPE_NBIOT */


/**
 * @brief If your SIM card is not contain pre-loaded EF-ACL (4.2.48 ETSI TS 131 102), this feature is not activated
 * or you want to use specific APN then set USE_APN_SETTINGS to 1 and configure APN parameters
 */
#define USE_APN_SETTINGS					( 0 )

#if USE_APN_SETTINGS
/**
 * @brief APN Network Name
 */
#define NBIOT_APN_NAME 						""

/**
 * @brief APN Network User Name
 */
#define NBIOT_APN_USER 						""

/**
 * @brief APN Network User Password
 */
#define NBIOT_APN_PWD  						""

/**
 * @brief APN Protocol type
 */
#define NBIOT_PROTOCOL_TYPE					PROTOCOL_TYPE_IPv4

/**
 * @brief APN Authentication method
 */
#define NBIOT_AUTH_METHOD					AUTH_METHOD_NONE

#endif /* USE_APN_SETTINGS */

#endif /* _AWS_NBIOT_CONFIG_H_ */

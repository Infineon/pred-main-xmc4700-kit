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

#ifndef ISM43340_WIFI_CONF_H
#define ISM43340_WIFI_CONF_H


#define ISM43340_WIFI_MAX_SSID_NAME_SIZE      		( 32 )
#define ISM43340_WIFI_MAX_PSWD_NAME_SIZE      		( 32 )
#define ISM43340_WIFI_PRODUCT_ID_SIZE         		( 32 )
#define ISM43340_WIFI_PRODUCT_NAME_SIZE       		( 32 )
#define ISM43340_WIFI_FW_REV_SIZE             		( 16 )
#define ISM43340_WIFI_API_REV_SIZE            		( 16 )
#define ISM43340_WIFI_STACK_REV_SIZE          		( 16 )
#define ISM43340_WIFI_RTOS_REV_SIZE           		( 16 )

#ifndef ISM43340_WIFI_DATA_SIZE
#define ISM43340_WIFI_DATA_SIZE               		( 1400 )
#endif

#ifndef ISM43340_WIFI_MAX_DETECTED_AP
#define ISM43340_WIFI_MAX_DETECTED_AP         		( 10 )
#endif

#ifndef ISM43340_WIFI_TIMEOUT
#define ISM43340_WIFI_TIMEOUT                 		( 0xFFFF )
#endif

#ifndef ISM43340_WIFI_PAYLOAD_SIZE
#define ISM43340_WIFI_PAYLOAD_SIZE            		( 1200 )
#endif


#endif /* ISM43340_WIFI_CONF_H */

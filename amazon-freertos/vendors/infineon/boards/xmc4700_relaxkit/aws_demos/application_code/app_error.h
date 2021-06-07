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

#ifndef APP_ERROR_H
#define APP_ERROR_H


/** Table with errors due to reboot  */
typedef enum {

    APP_ERROR_NONE = 0,

    APP_ERROR_UNIDENTIFIED           	= 100,
    APP_ERROR_SYSTEM_INIT            	= 101,
    APP_ERROR_NETWORK_COMM_LIB_INIT  	= 102,
    APP_ERROR_DEV_PROV               	= 103,

	NETWORK_INIT_ERROR					= 111,
	MQTT_AGENT_INIT_ERROR				= 112,
	MQTT_AGENT_PUBLISH_ERROR			= 113,

	OPTIGA_TRUST_M_ERROR				= 121,

	DPS368_COMPRESSOR_INIT_ERROR		= 130,
	DPS368_COLD_OUT_INIT_ERROR			= 131,
	DPS368_HOT_OUT_INIT_ERROR			= 132,
	DPS368_ID_4_INIT_ERROR				= 133,
	DPS368_ID_5_INIT_ERROR				= 134,

	DPS368_COMPRESSOR_TRANSFER_ERROR	= 135,
	DPS368_COLD_OUT_TRANSFER_ERROR		= 136,
	DPS368_HOT_OUT_TRANSFER_ERROR		= 137,
	DPS368_ID_4_TRANSFER_ERROR			= 138,
	DPS368_ID_5_TRANSFER_ERROR			= 139,

	TLI4970_COMPRESSOR_INIT_ERROR		= 141,
	TLI4970_FAN_TOP_INIT_ERROR			= 142,
	TLI4970_FAN_BOTTOM_INIT_ERROR		= 143,
	TLI4970_COMPRESSOR_TRANSFER_ERROR	= 144,
	TLI4970_FAN_TOP_TRANSFER_ERROR		= 145,
	TLI4970_FAN_BOTTOM_TRANSFER_ERROR	= 146,

	APP_ERROR_SENSORS_INIT            	= 150,
	APP_ERROR_SENSORS_READ            	= 151,

	APP_ERROR_I2C_MUX_NOT_RELEASED		= 200,
    APP_ERROR_I2C_MUX_ACQUIRE			= 201,

} AppError_t;


#endif /* APP_ERROR_H */

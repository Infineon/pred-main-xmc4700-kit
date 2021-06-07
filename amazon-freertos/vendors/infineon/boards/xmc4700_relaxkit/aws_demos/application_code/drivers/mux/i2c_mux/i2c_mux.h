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

#ifndef I2C_MUX_H
#define I2C_MUX_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


#define I2C_MUX_TIMEOUT_FOREVER 	( portMAX_DELAY )
#define I2C_MUX_TIMEOUT				( 1000 )


typedef enum {
    I2C_MUX_TYPE_UNKNOWN = 0,
    I2C_MUX_TYPE_OPTIGA,
    I2C_MUX_TYPE_TLV493D,
    I2C_MUX_TYPE_TLI493D_1,
    I2C_MUX_TYPE_TLI493D_2,
    I2C_MUX_TYPE_DPS368_1,      /* Pressure and temperature sensor #1 */
    I2C_MUX_TYPE_DPS368_2,      /* Pressure and temperature sensor #2 */

    I2C_MUX_TYPE_MAX

} I2cMuxType_t;


typedef void ( *I2cMuxCb_t )( void );


typedef struct {
    bool       bInited;
    bool       bNack;
    I2cMuxCb_t xTxCb;
    I2cMuxCb_t xRxCb;
    I2cMuxCb_t xErrorCb;
    I2cMuxCb_t xNackCb;
    I2cMuxCb_t xArbitLostCb;

} I2cMuxChannel_t;


typedef struct {
    bool            	bI2cInited;
    SemaphoreHandle_t 	xSemaphore;
    I2cMuxChannel_t 	pxCh[I2C_MUX_TYPE_MAX];
    I2cMuxType_t    	xType;

} I2cMux_t;


bool I2C_MUX_bInit( void );

bool I2C_MUX_bSpecificInit( I2cMuxType_t xMuxType, I2cMuxCb_t xTxCb, I2cMuxCb_t xRxCb, I2cMuxCb_t xErrorCb, I2cMuxCb_t xNackCb, I2cMuxCb_t xArbitLostCb );
bool I2C_MUX_bSpecificDeinit( I2cMuxType_t xMuxType );

bool I2C_MUX_bAcquire( I2cMuxType_t xMuxType, uint32_t ulTimeout );
int8_t I2C_MUX_cWait( uint32_t ulTimeout );
bool I2C_MUX_bRelease( I2cMuxType_t xMuxType );

bool I2C_MUX_bTransmit( bool bSendStart, const uint32_t ulSlaveAddress, uint8_t *pucTransmitData, const uint32_t ulCountBytesTransmit, bool bSendStop );
bool I2C_MUX_bReceive( bool bSendStart, const uint32_t ulSlaveAddress, uint8_t *pucReceiveData, const uint32_t ulCountBytesReceive, bool bSendStop, bool bSendNack );

bool I2C_MUX_bIsTxBusy( void );
bool I2C_MUX_bIsRxBusy( void );
bool I2C_MUX_bIsNack( void );


/* Callback from I2C */
void I2C_MUX_vEndTransmitCb( void );
void I2C_MUX_vEndReceiveCb( void );
void I2C_MUX_vNackReceivedCb( void );
void I2C_MUX_vArbitrationLostCb( void );
void I2C_MUX_vErrorDetectedCb( void );


#endif /* I2C_MUX_H */

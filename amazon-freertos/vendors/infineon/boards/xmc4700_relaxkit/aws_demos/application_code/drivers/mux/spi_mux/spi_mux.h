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

#ifndef SPI_MUX_H
#define SPI_MUX_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


#define SPI_MUX_TIMEOUT_FOREVER     ( portMAX_DELAY )
#define SPI_MUX_TIMEOUT			    ( 5000 )


typedef enum {
    SPI_MUX_TYPE_UNKNOWN = 0,
	SPI_MUX_TYPE_LTC,
	SPI_MUX_TYPE_DPS368_READ,
    SPI_MUX_TYPE_DPS368_1,
    SPI_MUX_TYPE_DPS368_2,
    SPI_MUX_TYPE_DPS368_3,
    SPI_MUX_TYPE_WIFI,

    SPI_MUX_TYPE_MAX

} SpiMuxType_t;


typedef void ( *SpiMuxCb_t )( void );


typedef struct {
    bool       bInited;
    uint8_t    ucCpol;        /* clock polarity */
    SpiMuxCb_t xTxCb;
    SpiMuxCb_t xRxCb;
    
} SpiMuxChannel_t;


typedef struct {
    bool                bSpiInited;
    SemaphoreHandle_t   xSemaphore;
    SpiMuxChannel_t     pxCh[SPI_MUX_TYPE_MAX];
    SpiMuxType_t        xType;

} SpiMux_t;


bool SPI_MUX_bInit( void );

bool SPI_MUX_bSpecificInit( SpiMuxType_t xMuxType, SpiMuxCb_t xTxCb, SpiMuxCb_t xRxCb );
bool SPI_MUX_bSpecificDeinit( SpiMuxType_t xMuxType );

bool SPI_MUX_bCpolSet( SpiMuxType_t xMuxType, uint8_t ucClockPolarity );

bool SPI_MUX_bAcquire( SpiMuxType_t xMuxType, uint32_t ulTimeout );
int8_t SPI_MUX_cWait( uint32_t ulTimeout );
bool SPI_MUX_bRelease( SpiMuxType_t xMuxType );

bool SPI_MUX_bTransmit( uint8_t *pucTransmitData, uint32_t ulCountBytesTransmit );
bool SPI_MUX_bReceive( uint8_t *pucReceiveData, uint32_t ulCountBytesReceive );
bool SPI_MUX_bTransfer( uint8_t *pucTransmitData, uint8_t *pucReceiveData, uint32_t ulCountBytesTransfer );

bool SPI_MUX_bIsTxBusy( void );
bool SPI_MUX_bIsRxBusy( void );

/* Callback from SPI*/
void SPI_MUX_vEndTransmitCb( void );
void SPI_MUX_vEndReceiveCb( void );

/* APP SPI_MASTER semaphores used in callback's */
extern SemaphoreHandle_t xSpiRxSemaphore;
extern SemaphoreHandle_t xSpiTxSemaphore;

void on_end_spi_receive( void );
void on_end_spi_transmit( void );


#endif /* SPI_MUX_H */

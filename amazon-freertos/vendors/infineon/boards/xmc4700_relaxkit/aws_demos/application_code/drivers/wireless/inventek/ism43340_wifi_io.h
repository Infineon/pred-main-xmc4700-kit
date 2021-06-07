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

#ifndef ES_WIFI_IO_H
#define ES_WIFI_IO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"

#include "spi_mux.h"
#include "delay.h"


#define WAIT_CMDDATA_RDY_HIGH_TICKS     ( 5 )


extern SemaphoreHandle_t xEsWifiMutex;

#define SPI_ACQUIRE_TIMEOUT      		( 100 )

#define LOCK_WIFI()             xSemaphoreTakeRecursive( xEsWifiMutex, (TickType_t) 1 )
#define UNLOCK_WIFI()           xSemaphoreGiveRecursive( xEsWifiMutex )


int8_t SPI_WIFI_cInit( uint16_t ucWifiMode );
int8_t SPI_WIFI_cDeInit( void );
void    SPI_WIFI_vDelay( uint32_t ulDelayMs );
int16_t SPI_WIFI_sReceiveData( uint8_t *pData, uint16_t usLength, uint32_t ulTimeout );
int16_t SPI_WIFI_sTransmitData( uint8_t *pData, uint16_t usLength, uint32_t ulTimeout );
int8_t SPI_WIFI_cResetModule( void );


#ifdef __cplusplus
}
#endif

#endif /* ES_WIFI_IO_H */

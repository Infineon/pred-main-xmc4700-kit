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

#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"

#include "ism43340_wifi.h"
#include "ism43340_wifi_io.h"
#include "ism43340_wifi_conf.h"

#include "spi_mux.h"

#include "DAVE.h"

#define ISM43340_FW_6_2_1_X_DEBUG   0

SemaphoreHandle_t xEsWifiMutex;

/* Data to send */
static uint8_t pucBufTx[ISM43340_WIFI_DATA_SIZE] = { 0 };
static bool prvbIsRdyFallen = false;

static uint32_t prvWifiIsCmdDataRdy( void );
static void prvWifiResetModule( void );
static int8_t prvWaitCmdDataRdyHigh( uint32_t ulTimeout );
static int8_t prvWaitCmdDataRdyFalling( uint32_t ulTimeout );


int8_t SPI_WIFI_cInit( uint16_t ucWifiMode )
{
    int8_t cRet = 0;

    if( ucWifiMode == ISM43340_WIFI_INIT )
    {
        if( xEsWifiMutex == NULL )
        {
            xEsWifiMutex = xSemaphoreCreateRecursiveMutex();
        }

        SPI_MUX_bSpecificInit( SPI_MUX_TYPE_WIFI, on_end_spi_transmit, on_end_spi_receive );

        SPI_MUX_bCpolSet( SPI_MUX_TYPE_WIFI, 0 );

        vTaskDelay( 1 );
    }

    cRet = SPI_WIFI_cResetModule();

    return cRet;
}


int8_t SPI_WIFI_cResetModule( void )
{
    uint32_t ulTimeout = 0x0FFF;
    uint8_t pucPrompt[256] = { 0 };
    uint8_t pucRx[2] = { 0 };

    /* Data to feed the clock */
    uint8_t pucDummySend[2] = { 0x0A, 0x0A };

    const char pcInitiateSpiResponce[] = { 0x15 , 0x15, '\r', '\n', '>', ' ', 0x00 };

    uint16_t usLength = 0;
    bool bResult = false;

    configPRINTF( ( "Resetting WIFI Module.. \r\n" ) );
    prvWifiResetModule();
    vTaskDelay( pdMS_TO_TICKS( 5 ) );

    configPRINTF( ( "WIFI Module reset done. \r\n" ) );
    configPRINTF( ( "Waiting for WIFI Module is ready.. \r\n" ) );

    if( SPI_MUX_bAcquire( SPI_MUX_TYPE_WIFI, SPI_ACQUIRE_TIMEOUT ) )
    {
        uint8_t cCount = 50; /* 50*100ms = 5sec max */
        /* Waiting while RDY line become to HIGH state. */
        while( !prvWifiIsCmdDataRdy() && cCount )
        {
            vTaskDelay( pdMS_TO_TICKS( 100 ) );
            cCount--;
        }
        if( cCount <= 0 )
        {
            SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
            configPRINTF( ( "WIFI RDY line is not going to HIGH state. Initialization error! \r\n" ) );
            return ISM43340_WIFI_ERROR_WAITING_DRDY_RISING;
        }

        prvbIsRdyFallen = false;
        do
        {
            if( ( usLength < 256 ) )
            {
                if( SPI_MASTER_Transfer( &SPI_MASTER_0, pucDummySend, pucRx, 2 ) != SPI_MASTER_STATUS_SUCCESS )
                {
                    SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
                    configPRINTF( ( "WIFI Module initialization error! \r\n" ) );
                    return ISM43340_WIFI_ERROR_SPI_INIT;
                }

                /* loop until MSLS is low; this means that data is not available */
                while(SPI_MASTER_GetFlagStatus(&SPI_MASTER_0, XMC_SPI_CH_STATUS_FLAG_MSLS));

                pucPrompt[usLength] = pucRx[1];
                pucPrompt[usLength + 1] = pucRx[0];
                usLength += 2;
                if( strstr( (const char *)pucPrompt, pcInitiateSpiResponce ) != NULL )
                {
                    bResult = true;
                    break;
                }
            }
            else
            {
                bResult = false;
                break;
            }

        } while( prvWifiIsCmdDataRdy() );


        if( prvWaitCmdDataRdyFalling( ulTimeout ) < 0 )
        {
            SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
            configPRINTF( ( "RDY line is not going to LOW state. WIFI Module initialization error! \r\n" ) );
            return ISM43340_WIFI_ERROR_WAITING_DRDY_FALLING;
        }

        SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
    }

    if( !bResult )
    {
        configPRINTF( ( "WIFI Module initialization error! \r\n" ) );
        return ISM43340_WIFI_ERROR_SPI_INIT;
    }

    configPRINTF( ("WIFI Module is ready. \r\n") );
    return 0;
}


int8_t SPI_WIFI_cDeInit( void )
{
    return 0;
}


void SPI_WIFI_vDelay( uint32_t ulDelayMs )
{
    vDelayMs( ulDelayMs );
}


int16_t SPI_WIFI_sReceiveData(uint8_t *pData, uint16_t usReceiveLength, uint32_t ulTimeout)
{
    int16_t sLength = 0;
    uint8_t pucRx[2] = { 0 };

    /* Data to feed the clock */
    uint8_t ucDummySend[2] = { 0x0A, 0x0A };

    if( prvWaitCmdDataRdyHigh( 10000 + ulTimeout ) < 0)
    {
        return ISM43340_WIFI_ERROR_WAITING_DRDY_RISING;
    }

    if ( SPI_MUX_bAcquire( SPI_MUX_TYPE_WIFI, SPI_ACQUIRE_TIMEOUT ) )
    {
        while( prvWifiIsCmdDataRdy() )
        {
            if( ( sLength < usReceiveLength ) || ( !usReceiveLength ) )
            {
                if( SPI_MASTER_Transfer( &SPI_MASTER_0, ucDummySend, pucRx, 2 ) != SPI_MASTER_STATUS_SUCCESS )
                {
                    SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
                    return ISM43340_WIFI_ERROR_SPI_FAILED;
                }

                /* loop until MSLS is low; this means that data is not available */
                while(SPI_MASTER_GetFlagStatus(&SPI_MASTER_0, XMC_SPI_CH_STATUS_FLAG_MSLS));

                if( pucRx[0] == 0x15 )
                {
                    vTaskDelay( 1 );
                }

                /* This the last data */
                if( !prvWifiIsCmdDataRdy() )
                {
                    if (pucRx[0] == 0x15)
                    {
                        /* Only 1 byte of data, the other one is padding */
                        if( pucRx[1] != 0x15 )
                        {
                            pData[0] = pucRx[1];
                            sLength++;
                        }
                        break;
                    }
                }

                pData[0] = pucRx[1];
                pData[1] = pucRx[0];
                sLength += 2;
                pData  += 2;

                if( sLength >= ISM43340_WIFI_DATA_SIZE * 10 )
                {
                    SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
                    return ISM43340_WIFI_ERROR_STUFFING_FOREVER;
                }
            }
            else
            {
                break;
            }
        }
        SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
    }
    else
    {
        return ISM43340_WIFI_ERROR_SPI_FAILED;
    }

    return sLength;
}


int16_t SPI_WIFI_sTransmitData( uint8_t *pData,  uint16_t usTransmitLength, uint32_t ulTimeout )
{
    if( prvWaitCmdDataRdyHigh( 10000 ) < 0)
    {
        return ISM43340_WIFI_ERROR_WAITING_DRDY_RISING;
    }

    if( SPI_MUX_bAcquire( SPI_MUX_TYPE_WIFI, SPI_ACQUIRE_TIMEOUT ) )
    {
        memcpy(pucBufTx, pData, usTransmitLength);

#if( ISM43340_FW_6_2_1_X_DEBUG )

        /* Prepending by '\n' according to "ISM43340_4343_SPI_Errata_C6.2.1.X" */
        for( int16_t i = usTransmitLength - 1; i >= 0; i-- )
        {
            pucBufTx[i+1] = pData[i];
        }
        pucBufTx[0] = '\n';
        usTransmitLength++;
#endif

        /* Padding: make it even-numbered */
        if( usTransmitLength & 1 )
        {
            pucBufTx[usTransmitLength] = '\n';
            usTransmitLength++;
        }

        /* Byte Swapping */
        for( uint16_t i = 0; i < usTransmitLength; i += 2 )
        {
            uint8_t tmp = pucBufTx[i];
            pucBufTx[i] = pucBufTx[i + 1];
            pucBufTx[i + 1] = tmp;
        }

        prvbIsRdyFallen = false;

        if( SPI_MASTER_Transmit( &SPI_MASTER_0, pucBufTx, usTransmitLength ) != SPI_MASTER_STATUS_SUCCESS )
        {
            SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
            return ISM43340_WIFI_ERROR_SPI_FAILED;
        }

        /* loop until MSLS is low; this means that data is not available */
        while(SPI_MASTER_GetFlagStatus(&SPI_MASTER_0, XMC_SPI_CH_STATUS_FLAG_MSLS));

        SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );

        while( !prvbIsRdyFallen )
        {
            uint32_t ulTickStart = xTaskGetTickCount();
            if( ( xTaskGetTickCount() - ulTickStart ) > 10000 )
            {
                SPI_MUX_bRelease( SPI_MUX_TYPE_WIFI );
                return ISM43340_WIFI_ERROR_WAITING_DRDY_FALLING;
            }
        }
    }
    return usTransmitLength;
}


uint32_t prvWifiIsCmdDataRdy( void )
{
    return PIN_INTERRUPT_GetPinValue( &ISM43340_RDY_PIN_INTERRUPT );
}


void prvWifiResetModule( void )
{
    DIGITAL_IO_SetOutputLow( &ISM_RST );
    vDelayMs( 20 );
    DIGITAL_IO_SetOutputHigh( &ISM_RST );
    vDelayMs( 50 );
}


int8_t prvWaitCmdDataRdyHigh( uint32_t ulTimeout )
{
    uint32_t ulMs = 1;
    TickType_t xTicks = ulMs / portTICK_PERIOD_MS;
    uint32_t ulTickStart = xTaskGetTickCount();

    while( !prvWifiIsCmdDataRdy() )
    {
        if( ( xTaskGetTickCount() - ulTickStart ) > WAIT_CMDDATA_RDY_HIGH_TICKS )
        {
            /* Minimum delay = 1 tick */
            vTaskDelay( xTicks ? xTicks : 1 );
        }

        if( ( xTaskGetTickCount() - ulTickStart ) > ulTimeout )
        {
            return -1;
        }
    }
    return 0;
}


int8_t prvWaitCmdDataRdyFalling( uint32_t ulTimeout )
{
    uint32_t ulMs = 1;
    TickType_t xTicks = ulMs / portTICK_PERIOD_MS;
    uint32_t ulTickStart = xTaskGetTickCount();

    while( prvbIsRdyFallen != true )
    {
        if( ( xTaskGetTickCount() - ulTickStart ) > WAIT_CMDDATA_RDY_HIGH_TICKS )
        {
            /* Minimum delay = 1 tick */
            vTaskDelay( xTicks ? xTicks : 1 );
        }
        if( ( xTaskGetTickCount() - ulTickStart ) > ulTimeout )
        {
            return -1;
        }
    }
    return 0;
}


/* ISM43340 Ready pin Falling Interrupt */
void ISM43340_RDY_IRQHandler( void )
{
    prvbIsRdyFallen = true;
}

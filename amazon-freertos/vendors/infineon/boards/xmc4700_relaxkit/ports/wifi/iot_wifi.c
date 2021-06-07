/*
 * FreeRTOS Wi-Fi ISM43340 V1.0
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
 * @file iot_wifi.c
 * @brief Wi-Fi Interface.
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Wi-Fi driver includes. */
#include "ISM43340_wifi.h"
#include "ISM43340_wifi_io.h"

/* Socket and Wi-Fi interface includes. */
#include "iot_wifi.h"

/**
 * @brief The credential set to use for TLS on the Inventek module.
 *
 * @note This is hard-coded to 3 because we are using re-writable
 * credential slot.
 */
#define wifiOFFLOAD_SSL_CREDS_SLOT      ( 3 )

/*-----------------------------------------------------------*/

/**
 * @brief Represents the Wi-Fi module.
 */
typedef struct WiFiModule
{
    ISM43340_WIFIObject_t xWifiObject;        /**< Internal Wi-Fi object. */
    SemaphoreHandle_t xSemaphoreHandle; /**< Semaphore used to serialize all the operations on the Wi-Fi module. */
} WiFiModule_t;

WiFiModule_t xWiFiModule;

/**
 * @brief Wi-Fi initialization status.
 */
static BaseType_t xWIFIInitDone;

/**
 * @brief Maximum time to wait in ticks for obtaining the Wi-Fi semaphore
 * before failing the operation.
 */

static const TickType_t xSemaphoreWaitTicks = pdMS_TO_TICKS( wificonfigMAX_SEMAPHORE_WAIT_TIME_MS );

/**
 * @brief Maps the given abstracted security type to ISM43340 specific one.
 *
 * @param[in] xSecurity The given abstracted security type.
 *
 * @return Corresponding ISM43340 specific security type.
 */
static ISM43340_WIFI_SecurityType_t prvConvertSecurityFromAbstractedToISM43340( WIFISecurity_t xSecurity )
{
    ISM43340_WIFI_SecurityType_t xConvertedSecurityType = ISM43340_WIFI_SEC_UNKNOWN;

    switch( xSecurity )
    {
        case eWiFiSecurityOpen:
            xConvertedSecurityType = ISM43340_WIFI_SEC_OPEN;
            break;

        case eWiFiSecurityWEP:
            xConvertedSecurityType = ISM43340_WIFI_SEC_WEP;
            break;

        case eWiFiSecurityWPA:
            xConvertedSecurityType = ISM43340_WIFI_SEC_WPA;
            break;

        case eWiFiSecurityWPA2:
            xConvertedSecurityType = ISM43340_WIFI_SEC_WPA2;
            break;

        case eWiFiSecurityNotSupported:
            xConvertedSecurityType = ISM43340_WIFI_SEC_UNKNOWN;
            break;
    }

    return xConvertedSecurityType;
}

/*-----------------------------------------------------------*/

/**
 * @brief Maps the ISM43340 security type to abstracted security type.
 *
 * @param[in] xSecurity The ISM43340 security type.
 *
 * @return Corresponding abstracted security type.
 */
static WIFISecurity_t prvConvertSecurityToAbstracted( ISM43340_WIFI_SecurityType_t xSecurity )
{
    WIFISecurity_t xConvertedSecurityType = eWiFiSecurityNotSupported;

    switch( xSecurity )
    {
        case ISM43340_WIFI_SEC_OPEN:
            xConvertedSecurityType = eWiFiSecurityOpen;
            break;

        case ISM43340_WIFI_SEC_WEP:
            xConvertedSecurityType = eWiFiSecurityWEP;
            break;

        case ISM43340_WIFI_SEC_WPA:
            xConvertedSecurityType = eWiFiSecurityWPA;
            break;

        case ISM43340_WIFI_SEC_WPA2:
            xConvertedSecurityType = eWiFiSecurityWPA2;
            break;

        default:
            xConvertedSecurityType = eWiFiSecurityNotSupported;
            break;
    }

    return xConvertedSecurityType;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_On( void )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    ISM43340_WIFI_Status_t xWiFiStatus = ISM43340_WIFI_STATUS_ERROR;

    /* One time Wi-Fi initialization */
    if( xWIFIInitDone == pdFALSE )
    {
        /* This buffer is used to store the semaphore's data structure
         * and therefore must be static. */
        static StaticSemaphore_t xSemaphoreBuffer;

        /* Start with all the zero. */
        memset( &( xWiFiModule ), 0, sizeof( xWiFiModule ) );

        /* Create the semaphore used to serialize Wi-Fi module operations. */
        xWiFiModule.xSemaphoreHandle = xSemaphoreCreateMutexStatic( &( xSemaphoreBuffer ) );

        /* Initialize semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );

        /* Wi-Fi init done*/
        xWIFIInitDone = pdTRUE;
    }

    /* Register function pointers for carrying out SPI operations. */
    if( ISM43340_WIFI_RegisterBusIO( &( xWiFiModule.xWifiObject ),
                               &( SPI_WIFI_cInit ),
                               &( SPI_WIFI_cDeInit ),
                               &( SPI_WIFI_vDelay ),
                               &( SPI_WIFI_sTransmitData ),
                               &( SPI_WIFI_sReceiveData ) ) == ISM43340_WIFI_STATUS_OK )
    {
        /* Initialize the Wi-Fi module. */
    	xWiFiStatus =  ISM43340_WIFI_Init( &( xWiFiModule.xWifiObject ) );
        if( xWiFiStatus == ISM43340_WIFI_STATUS_OK )
        {
            /* Initialization successful. */
            xRetVal = eWiFiSuccess;
        }
        else
        {
            configPRINTF(("WIFI Error! STATUS = %d\r\n", xWiFiStatus));
        }
    }

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Off( void )
{
    /*command not implemented in ES Wi-Fi drivers. */
    WIFIReturnCode_t xRetVal = eWiFiSuccess;

    if( xWIFIInitDone == pdTRUE )
    {
        xWIFIInitDone = pdFALSE;

        /* give ability to prvNetworkReceive to stop its activities.*/
        vTaskDelay(100);

        /* Try to acquire the semaphore. */
        if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, portMAX_DELAY) == pdTRUE )
        {
		   vSemaphoreDelete( xWiFiModule.xSemaphoreHandle );
        }

        xWiFiModule.xSemaphoreHandle = NULL;

        /* DeInitialize the Wi-Fi module. */
        if( ISM43340_WIFI_DeInit( &( xWiFiModule.xWifiObject ) ) == ISM43340_WIFI_STATUS_OK )
        {
            /* Initialization successful. */
            xRetVal = eWiFiSuccess;
        }
    }

    return xRetVal;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_ConnectAP( const WIFINetworkParams_t * const pxNetworkParams )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    uint32_t x;

    configASSERT( pxNetworkParams != NULL );
    configASSERT( pxNetworkParams->pcSSID != NULL );

    if ( pxNetworkParams->xSecurity != eWiFiSecurityOpen )
    {
        configASSERT( pxNetworkParams->pcPassword != NULL );
    }

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        /* Disconnect first if we are connected, to connect to the input network. */
        if( ISM43340_WIFI_IsConnected( &xWiFiModule.xWifiObject ) )
        {
            if( ISM43340_WIFI_Disconnect( &( xWiFiModule.xWifiObject ) ) ==  ISM43340_WIFI_STATUS_OK )
            {
                xRetVal = eWiFiSuccess;
            }
        }
        else
        {
            xRetVal = eWiFiSuccess;
        }

        if ( xRetVal == eWiFiSuccess )
        {
            /* Reset the return value to failure to catch errors in connection. */
            xRetVal = eWiFiFailure;

            /* Keep trying to connect until all the retries are exhausted. */
            for( x = 0 ; x < wificonfigNUM_CONNECTION_RETRY ; x++ )
            {
                /* Try to connect to Wi-Fi. */
                if( ISM43340_WIFI_Connect( &( xWiFiModule.xWifiObject ),
                                        pxNetworkParams->pcSSID,
                                        pxNetworkParams->pcPassword,
                                        prvConvertSecurityFromAbstractedToISM43340( pxNetworkParams->xSecurity ) ) == ISM43340_WIFI_STATUS_OK )
                {
                    /* Store network settings. */
                    if( ISM43340_WIFI_GetNetworkSettings( &( xWiFiModule.xWifiObject ) ) == ISM43340_WIFI_STATUS_OK )
                    {
                        /* Connection successful. */
                        xRetVal = eWiFiSuccess;

                        /* No more retries needed. */
                        break;
                    }
                }
            }
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Disconnect( void )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        if( ISM43340_WIFI_Disconnect( &( xWiFiModule.xWifiObject ) ) == ISM43340_WIFI_STATUS_OK )
        {
            /* This variable is not updated by the driver after a disconnect. */
        	xWiFiModule.xWifiObject.NetSettings.IsConnected = 0;

            /* Store network settings. After a disconnect the IP address under NetSettings becomes 0.0.0.0 */
            if( ISM43340_WIFI_GetNetworkSettings( &( xWiFiModule.xWifiObject ) ) == ISM43340_WIFI_STATUS_OK )
            {
                /* Disconnection successful. */
                xRetVal = eWiFiSuccess;
            }
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Reset( void )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        /* Reset command gives error so hard resetting */
        ISM43340_WIFI_Init( &( xWiFiModule.xWifiObject ) );
        xRetVal = eWiFiSuccess;

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}


/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_SetMode( WIFIDeviceMode_t xDeviceMode )
{
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}

/*-----------------------------------------------------------*/
WIFIReturnCode_t WIFI_GetMode( WIFIDeviceMode_t * pxDeviceMode )
{
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}
/*-----------------------------------------------------------*/


WIFIReturnCode_t WIFI_NetworkAdd( const WIFINetworkProfile_t * const pxNetworkProfile,
                                  uint16_t * pusIndex )
{
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_NetworkGet( WIFINetworkProfile_t * pxNetworkProfile,
                                  uint16_t usIndex )

{
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_NetworkDelete( uint16_t usIndex )
{
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_Ping( uint8_t * pucIPAddr,
                            uint16_t usCount,
                            uint32_t ulIntervalMS )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;

    if( ( NULL == pucIPAddr ) || ( 0 == usCount ) )
    {
        return eWiFiFailure;
    }

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        if( ISM43340_WIFI_Ping( &xWiFiModule.xWifiObject, pucIPAddr, usCount, ulIntervalMS ) == ISM43340_WIFI_STATUS_OK )
        {
            xRetVal = eWiFiSuccess;
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetIP( uint8_t * pucIPAddr )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;

    configASSERT( pucIPAddr != NULL );

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        if( xWiFiModule.xWifiObject.NetSettings.IsConnected )
        {
            memcpy( pucIPAddr, xWiFiModule.xWifiObject.NetSettings.IP_Addr, 4 );
            xRetVal = eWiFiSuccess;
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetMAC( uint8_t * pucMac )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;

    configASSERT( pucMac != NULL );

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        if( ISM43340_WIFI_GetMACAddress( &xWiFiModule.xWifiObject, pucMac ) == ISM43340_WIFI_STATUS_OK )
        {
            xRetVal = eWiFiSuccess;
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetHostIP( char * pcHost,
                                 uint8_t * pucIPAddr )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;

    configASSERT( pcHost != NULL );
    configASSERT( pucIPAddr != NULL );

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        if( ISM43340_WIFI_DNS_LookUp( &xWiFiModule.xWifiObject, pcHost, pucIPAddr ) == ISM43340_WIFI_STATUS_OK )
        {
            xRetVal = eWiFiSuccess;
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}

/*-----------------------------------------------------------*/

/*Scan fails if the command buffer is too small to fit in scan result and it returns
 * IO error, see ISM43340_wifi_conf.h*/
WIFIReturnCode_t WIFI_Scan( WIFIScanResult_t * pxBuffer,
                            uint8_t ucNumNetworks )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    uint32_t x;

    ISM43340_WIFI_APs_t xESWifiAPs;

    configASSERT( pxBuffer != NULL );

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        if( ISM43340_WIFI_ListAccessPoints( &xWiFiModule.xWifiObject, &xESWifiAPs ) == ISM43340_WIFI_STATUS_OK )
        {
            for( x = 0 ; x < ucNumNetworks ; x++ )
            {
                pxBuffer[ x ].xSecurity = prvConvertSecurityToAbstracted( xESWifiAPs.AP[ x ].Security );

                strncpy( ( char * ) pxBuffer[ x ].cSSID,
                         ( char * ) xESWifiAPs.AP[ x ].SSID,
                         wificonfigMAX_SSID_LEN );

                pxBuffer[ x ].cRSSI = xESWifiAPs.AP[ x ].RSSI;

                memcpy( pxBuffer[ x ].ucBSSID,
                		xESWifiAPs.AP[ x ].MAC,
                        wificonfigMAX_BSSID_LEN );
            }

            xRetVal = eWiFiSuccess;
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}

/*-----------------------------------------------------------*/
WIFIReturnCode_t WIFI_StartAP( void )
{
    /*WIFI_ConfigureAP configures and start the soft AP . */
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}

/*-----------------------------------------------------------*/
WIFIReturnCode_t WIFI_StopAP( void )
{
    /*SoftAP mode stops after a timeout. */
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}

/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_ConfigureAP( const WIFINetworkParams_t * const pxNetworkParams )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;
    ISM43340_WIFI_APConfig_t xApConfig;

    configASSERT( pxNetworkParams != NULL );
    configASSERT( pxNetworkParams->pcSSID != NULL );

    strncpy( ( char * ) xApConfig.SSID,
             ( char * ) pxNetworkParams->pcSSID,
             ISM43340_WIFI_MAX_SSID_NAME_SIZE );

    if ( pxNetworkParams->xSecurity != eWiFiSecurityOpen )
    {
        configASSERT( pxNetworkParams->pcPassword != NULL );

        strncpy( ( char * ) xApConfig.Pass,
                 ( char * ) pxNetworkParams->pcPassword,
                 ISM43340_WIFI_MAX_PSWD_NAME_SIZE );
    }

    xApConfig.Channel = pxNetworkParams->cChannel;
    xApConfig.MaxConnections = wificonfigMAX_CONNECTED_STATIONS;
    xApConfig.Security = prvConvertSecurityFromAbstractedToISM43340( pxNetworkParams->xSecurity );

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        /* Activate Soft AP. */
        if( ISM43340_WIFI_ActivateAP( &xWiFiModule.xWifiObject, &xApConfig ) == ISM43340_WIFI_STATUS_OK )
        {
            xRetVal = eWiFiSuccess;
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_SetPMMode( WIFIPMMode_t xPMModeType,
                                 const void * pvOptionValue )
{
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}
/*-----------------------------------------------------------*/

WIFIReturnCode_t WIFI_GetPMMode( WIFIPMMode_t * pxPMModeType,
                                 void * pvOptionValue )
{
    WIFIReturnCode_t xRetVal = eWiFiNotSupported;

    return xRetVal;
}
/*-----------------------------------------------------------*/

BaseType_t WIFI_GetRssi( void )
{
    int32_t rssi = 0;
    /* Expected result from ISM43340_WIFI_IsConnected() when the board is connected to Wi-Fi. */

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        /* Check whether or not the WiFi module is connected to any AP. */
        rssi = ISM43340_WIFI_GetRssi( &xWiFiModule.xWifiObject );

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }

    return rssi;
}
/*-----------------------------------------------------------*/

BaseType_t WIFI_IsConnected( void )
{
    BaseType_t xIsConnected = pdFALSE;
    /* Expected result from ISM43340_WIFI_IsConnected() when the board is connected to Wi-Fi. */
    const uint8_t uConnected = 1;

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        /* Check whether or not the WiFi module is connected to any AP. */
        if ( ISM43340_WIFI_IsConnected( &xWiFiModule.xWifiObject ) == uConnected )
        {
            xIsConnected = pdTRUE;
        }

        /* Return the semaphore. */
        xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }

    return xIsConnected;
}
/*-----------------------------------------------------------*/

#ifdef USE_OFFLOAD_SSL

    /**
     * @brief Stores the provided certificate to the re-writable slot in
     * the Inventak module.
     *
     * @param pucCertificate[in] The ceritificate to store.
     * @param usCertificateLength[in] The length of the above certificate.
     *
     * @return If certificate is stored successfully, eWiFiSuccess is
     * returned. Otherwise an error code indicating the reason of the error
     * is returned.
     */
    WIFIReturnCode_t  WIFI_StoreCertificate( uint8_t * pucCertificate, uint16_t usCertificateLength )
    {
        WIFIReturnCode_t xRetVal = eWiFiFailure;

        /* Try to acquire the semaphore. */
        if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
        {
            /* Store Certificate. */
            if( ISM43340_WIFI_StoreCertificate( &xWiFiModule.xWifiObject,
                                          ISM43340_WIFI_FUNCTION_TLS,
                                          wifiOFFLOAD_SSL_CREDS_SLOT,
                                          pucCertificate,
                                          usCertificateLength ) == ISM43340_WIFI_STATUS_OK )
            {
                xRetVal = eWiFiSuccess;
            }

            /* Return the semaphore. */
            ( void ) xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
        }
        else
        {
            xRetVal = eWiFiTimeout;
        }

        return xRetVal;
    }

#endif /* USE_OFFLOAD_SSL */
/*-----------------------------------------------------------*/

#ifdef USE_OFFLOAD_SSL

    /**
     * @brief Stores the provided key to the re-writable slot in the
     * Inventak module.
     *
     * @param pucKey[in] The key to store.
     * @param usKeyLength The length of the above key.
     *
     * @return If key is stored successfully, eWiFiSuccess is returned.
     * Otherwise an error code indicating the reason of the error is
     * returned.
     */
    WIFIReturnCode_t  WIFI_StoreKey( uint8_t * pucKey, uint16_t usKeyLength )
    {
        WIFIReturnCode_t xRetVal = eWiFiFailure;

        /* Try to acquire the semaphore. */
        if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
        {
            /* Store Certificate. */
            if( ISM43340_WIFI_StoreKey( &xWiFiModule.xWifiObject,
                                  ISM43340_WIFI_FUNCTION_TLS,
                                  wifiOFFLOAD_SSL_CREDS_SLOT,
                                  pucKey,
                                  usKeyLength ) == ISM43340_WIFI_STATUS_OK )
            {
                xRetVal = eWiFiSuccess;
            }

            /* Return the semaphore. */
            ( void ) xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
        }
        else
        {
            xRetVal = eWiFiTimeout;
        }

        return xRetVal;
    }

#endif /* USE_OFFLOAD_SSL */
/*-----------------------------------------------------------*/

/**
 * @brief Gets the Inventek module's firmware revision number.
 *
 * @param pucBuffer[out] The output buffer to return the firmware version.
 *
 * @return If firmware version is retrieved successfully, eWiFiSuccess
 * is returned. Otherwise an error code indicating the reason of the
 * error is returned.
 */
WIFIReturnCode_t WIFI_GetFirmwareVersion( uint8_t * pucBuffer )
{
    WIFIReturnCode_t xRetVal = eWiFiFailure;

    /* Try to acquire the semaphore. */
    if( xSemaphoreTake( xWiFiModule.xSemaphoreHandle, xSemaphoreWaitTicks ) == pdTRUE )
    {
        /* Get the firmware version. */
        if( ISM43340_WIFI_GetFWRevID( &xWiFiModule.xWifiObject, pucBuffer ) == ISM43340_WIFI_STATUS_OK )
        {
            xRetVal = eWiFiSuccess;
        }

        /* Return the semaphore. */
        ( void ) xSemaphoreGive( xWiFiModule.xSemaphoreHandle );
    }
    else
    {
        xRetVal = eWiFiTimeout;
    }

    return xRetVal;
}


WIFIReturnCode_t WIFI_RegisterNetworkStateChangeEventCallback( IotNetworkStateChangeEventCallback_t xCallback  )
{
    /** Needs to implement dispatching network state change events **/
    return eWiFiNotSupported;
}
/*-----------------------------------------------------------*/

/*
 * Amazon FreeRTOS Secure Sockets for FreeRTOS+TCP V1.1.5
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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

/* Define _SECURE_SOCKETS_WRAPPER_NOT_REDEFINE to prevent secure sockets functions
 * from redefining in iot_secure_sockets_wrapper_metrics.h */
#define _SECURE_SOCKETS_WRAPPER_NOT_REDEFINE

#include <string.h>

#include "FreeRTOS.h"
#include "FreeRTOSIPConfig.h"
#include "list.h"
#include "task.h"

#include "iot_secure_sockets.h"
#include "aws_nbiot.h"
#include "aws_nbiot_config.h"

#include "iot_pkcs11_config.h"
#ifdef AMAZON_FREERTOS_ENABLE_UNIT_TESTS
#include "iot_test_pkcs11_config.h"
#endif
#include "iot_crypto.h"
#include "iot_pkcs11.h"
#include "iot_pkcs11_pal.h"
#include "iot_tls.h"

/* IOT config */
#include "iot_network_manager_private.h"

#if NBIOT_ENABLED

#undef _SECURE_SOCKETS_WRAPPER_NOT_REDEFINE

/**
 * @brief A flag to indicate whether or not a socket is closed
 * for receive.
 */
#define securesocketsSOCKET_READ_CLOSED_FLAG     ( 1UL << 1 )

/**
 * @brief A flag to indicate whether or not a socket is closed
 * for send.
 */
#define securesocketsSOCKET_WRITE_CLOSED_FLAG    ( 1UL << 2 )

/**
 * @brief The maximum timeout accepted by the module.
 *
 * This value is dictated by the hardware and should not be
 * modified.
 */
#define securesocketsMAX_TIMEOUT                 ( 30000 )

#define NBIOT_SOCKET_CLOSED             -50


/* Internal context structure. */
typedef struct SSOCKETContext
{
    char * pcDestination;
    void * pvTLSContext;
    BaseType_t xRequireTLS;
    char * pcServerCertificate;
    uint32_t ulServerCertificateLength;
    char ** ppcAlpnProtocols;
    uint32_t ulAlpnProtocolsCount;
    BaseType_t xConnectAttempted;
    uint32_t ulSendTimeout; /**< Send timeout. */
    uint32_t ulReceiveTimeout; /**< Receive timeout. */
    uint32_t ulFlags; /**< Various properties of the socket (secured etc.). */
    uint8_t usNBIoTSocketNumber;
} SSOCKETContext_t, * SSOCKETContextPtr_t;

/*
 * Helper routines.
 */
static uint32_t ulSocketBitMap = 0;
/*
 * @brief Network send callback.
 */
static BaseType_t prvNetworkSend( void * pvContext,
                                  const unsigned char * pucData,
                                  size_t xDataLength )
{
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) pvContext; /*lint !e9087 cast used for portability. */

    if (pucData == NULL) {
        return -1;
    }
#if NBIOT_MODE_TRANSPARENT
    int uStatus = nbiot_tcp_send_transparent(pucData, xDataLength);
#else
    int uStatus = 1;
    int retStatus = 0;
    int tryes_to_send = NBIOT_SEND_TRYES_IF_FAIL;
    while ((tryes_to_send) && (xDataLength > retStatus))
    {
    	uStatus = NBIOT_lTcpSendSocket(pxContext->usNBIoTSocketNumber, (pucData+retStatus), MIN((xDataLength-retStatus), MAX_PKT_LEN));
    	if (uStatus > 0)
    	{
    	    retStatus += uStatus;
    	    tryes_to_send = NBIOT_SEND_TRYES_IF_FAIL;
    	} else if (uStatus == NBIOT_ERROR_SENDING_BUFFER_FULL)
    	{
    	    /* sending fail, try to resend */
    	    tryes_to_send--;
    	    vTaskDelay(NBIOT_SEND_DELAY_IF_FAIL);
    	} else
    	{
    	    /* sending error, no way to continue */
    	    retStatus = uStatus;
    	    break;
    	}
    }
    //int uStatus = nbiot_tcp_send_socket(pxContext->usNBIoTSocketNumber, pucData, xDataLength);
#endif
    if (uStatus == NBIOT_ERROR_NO_CONNECTION){
        uStatus = SOCKETS_ENOTCONN;
    } else if (uStatus == NBIOT_ERROR_MUTEX) {
        uStatus = SOCKETS_EWOULDBLOCK;
    }
    return retStatus;
}
/*-----------------------------------------------------------*/

/*
 * @brief Network receive callback.
 */
static BaseType_t prvNetworkRecv( void * pvContext,
                                  unsigned char * pucReceiveBuffer,
                                  size_t xReceiveLength )
{
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) pvContext; /*lint !e923 cast is needed for portability. */
    int usReceivedBytes = 0;
    BaseType_t xRetVal = 0;
    /* Receive the data. */
#if NBIOT_MODE_TRANSPARENT
    usReceivedBytes = nbiot_tcp_recv_transparent(pxContext->usNBIoTSocketNumber, pucReceiveBuffer, xReceiveLength, pxContext->ulReceiveTimeout);
#else
    usReceivedBytes = NBIOT_lTcpRecvSocket(pxContext->usNBIoTSocketNumber, pucReceiveBuffer, xReceiveLength, pxContext->ulReceiveTimeout);
#endif
    if ((usReceivedBytes > 0)) {
        /* Success, return the number of bytes received. */
        xRetVal = (BaseType_t) usReceivedBytes;
    } else {
        /* The socket read has timed out too. Returning
             * SOCKETS_EWOULDBLOCK will cause mBedTLS to fail
             * and so we must return zero. */
        if (usReceivedBytes == NBIOT_ERROR_NO_CONNECTION) {
            xRetVal = SOCKETS_ENOTCONN;
        } else if (usReceivedBytes == NBIOT_SOCKET_CLOSED){
            xRetVal = SOCKETS_ECLOSED;
        } else if (usReceivedBytes == NBIOT_ERROR_MUTEX) {
            xRetVal = SOCKETS_EWOULDBLOCK;
        }
        else {
            xRetVal = 0;
        }
    }

    return xRetVal;
}
/*-----------------------------------------------------------*/

/*
 * Interface routines.
 */

int32_t SOCKETS_Close( Socket_t xSocket )
{
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket; /*lint !e9087 cast used for portability. */
    uint32_t ulProtocol;
    int32_t lReturn;

    if( ( xSocket != SOCKETS_INVALID_SOCKET ) && ( NULL != pxContext ) )
    {
        /* Clean-up destination string. */
        if( NULL != pxContext->pcDestination )
        {
            vPortFree( pxContext->pcDestination );
        }

        /* Clean-up server certificate. */
        if( NULL != pxContext->pcServerCertificate )
        {
            vPortFree( pxContext->pcServerCertificate );
        }

        /* Clean-up application protocol array. */
        if( NULL != pxContext->ppcAlpnProtocols )
        {
            for( ulProtocol = 0;
                 ulProtocol < pxContext->ulAlpnProtocolsCount;
                 ulProtocol++ )
            {
                if( NULL != pxContext->ppcAlpnProtocols[ ulProtocol ] )
                {
                    vPortFree( pxContext->ppcAlpnProtocols[ ulProtocol ] );
                }
            }

            vPortFree( pxContext->ppcAlpnProtocols );
        }

        /* Clean-up TLS context. */
        if( pdTRUE == pxContext->xRequireTLS )
        {
            TLS_Cleanup( pxContext->pvTLSContext );
        }

        /* Set the according bit in bitmap to zero */
        ulSocketBitMap &= ~(1 << pxContext->usNBIoTSocketNumber);
        /* Close the underlying socket handle. */
#if NBIOT_MODE_TRANSPARENT
        ( void ) nbiot_tcp_close_transparent(pxContext->usNBIoTSocketNumber);
#else
        ( void ) NBIOT_lTcpCloseSocket(pxContext->usNBIoTSocketNumber);
#endif

        /* Free the context. */
        vPortFree( pxContext );
        lReturn = SOCKETS_ERROR_NONE;
    }
    else
    {
        lReturn = SOCKETS_EINVAL;
    }

    return lReturn;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_Connect( Socket_t xSocket,
                         SocketsSockaddr_t * pxAddress,
                         Socklen_t xAddressLength )
{
    int32_t lStatus = SOCKETS_ERROR_NONE;
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket; /*lint !e9087 cast used for portability. */
    TLSParams_t xTLSParams = { 0 };

    if( ( xSocket != SOCKETS_INVALID_SOCKET ) && ( pxAddress != NULL ) )
    {
        /* A connection was attempted. If this function fails, then the socket is invalid and the user
         * must call SOCKETS_Close(), on this socket, and SOCKETS_Socket() to get a new socket. */
        pxContext->xConnectAttempted = pdTRUE;

        /* Setup connection parameters. */
        char pcAddress[16];
        SOCKETS_inet_ntoa(SOCKETS_ntohl(pxAddress->ulAddress), pcAddress);

        uint16_t remote_port = SOCKETS_htons(pxAddress->usPort); /* NBIOT Module expects the port number in host byte order. */
#if NBIOT_MODE_TRANSPARENT
        lStatus = nbiot_tcp_open_transparent(NBIOT_CONTEXT_ID,
                                        pxContext->usNBIoTSocketNumber,
                                        pcAddress,
                                        remote_port);

#else
        lStatus = NBIOT_lTcpOpenSocket(NBIOT_CONTEXT_ID,
                                        pxContext->usNBIoTSocketNumber,
                                        pcAddress,
                                        remote_port);
#endif
        if (lStatus == 0 ) {
            lStatus = SOCKETS_ERROR_NONE;
        }
        /* Negotiate TLS if requested. */
        if( ( SOCKETS_ERROR_NONE == lStatus ) && ( pdTRUE == pxContext->xRequireTLS ) )
        {
            xTLSParams.ulSize = sizeof( xTLSParams );
            xTLSParams.pcDestination = pxContext->pcDestination;
            xTLSParams.pcServerCertificate = pxContext->pcServerCertificate;
            xTLSParams.ulServerCertificateLength = pxContext->ulServerCertificateLength;
            xTLSParams.ppcAlpnProtocols = ( const char ** ) pxContext->ppcAlpnProtocols;
            xTLSParams.ulAlpnProtocolsCount = pxContext->ulAlpnProtocolsCount;
            xTLSParams.pvCallerContext = pxContext;
            xTLSParams.pxNetworkRecv = prvNetworkRecv;
            xTLSParams.pxNetworkSend = prvNetworkSend;
            lStatus = TLS_Init( &pxContext->pvTLSContext, &xTLSParams );

            if( SOCKETS_ERROR_NONE == lStatus )
            {
                lStatus = TLS_Connect( pxContext->pvTLSContext );

                if( lStatus < 0 )
                {
                    lStatus = SOCKETS_TLS_HANDSHAKE_ERROR;
                }
            }
        }
    }
    else
    {
        lStatus = SOCKETS_SOCKET_ERROR;
    }

    return lStatus;
}
/*-----------------------------------------------------------*/

uint32_t SOCKETS_GetHostByName( const char * pcHostName )
{
    char ip[16] = {0};

    uint32_t i;
    uint32_t ulIPAddres = 0;
    uint32_t num_dot = 0;
    uint32_t num_byte = 3;

    NBIOT_lGetIpFromName(NBIOT_CONTEXT_ID, pcHostName, ip);

    char byte[3];
    uint32_t len = strlen(ip);

    for (i = 0; i < len + 1; i++) {
        if ((ip[i] == '.') || (i == len)) {
            memset(byte, 0, 3);
            strncpy(byte, &ip[num_dot], i - num_dot);
            num_dot = i + 1;
            ulIPAddres |= ((atoi(byte) & 0xFF) << (num_byte * 8));
            num_byte--;
        }
    }

    return ulIPAddres;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_Recv( Socket_t xSocket,
                      void * pvBuffer,
                      size_t xBufferLength,
                      uint32_t ulFlags )
{
    int32_t lStatus = SOCKETS_SOCKET_ERROR;
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket; /*lint !e9087 cast used for portability. */

    if( ( xSocket != SOCKETS_INVALID_SOCKET ) &&
            ( pvBuffer != NULL ) )
    {
        if (pxContext->ulFlags & securesocketsSOCKET_READ_CLOSED_FLAG) {
            lStatus = SOCKETS_ECLOSED;
        }
        else {
            if( pdTRUE == pxContext->xRequireTLS )
            {
                /* Receive through TLS pipe, if negotiated. */
                lStatus = TLS_Recv( pxContext->pvTLSContext, pvBuffer, xBufferLength );
            }
            else
            {
                /* Receive unencrypted. */
                lStatus = prvNetworkRecv( pxContext, pvBuffer, xBufferLength );
            }
        }
    }
    else
    {
        lStatus = SOCKETS_EINVAL;
    }

    return lStatus;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_Send( Socket_t xSocket,
                      const void * pvBuffer,
                      size_t xDataLength,
                      uint32_t ulFlags )
{
    int32_t lStatus = SOCKETS_SOCKET_ERROR;
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket; /*lint !e9087 cast used for portability. */

    if( ( xSocket != SOCKETS_INVALID_SOCKET ) &&
            ( pvBuffer != NULL ) )
    {
        if (pxContext->ulFlags & securesocketsSOCKET_WRITE_CLOSED_FLAG) {
            lStatus = SOCKETS_ECLOSED;
        }
        else {
            if( pdTRUE == pxContext->xRequireTLS )
            {
                /* Send through TLS pipe, if negotiated. */
                lStatus = TLS_Send( pxContext->pvTLSContext, pvBuffer, xDataLength );
            }
            else
            {
                /* Send unencrypted. */
                lStatus = prvNetworkSend( pxContext, pvBuffer, xDataLength );
            }
        }
    }
    else
    {
        lStatus = SOCKETS_EINVAL;
    }

    return lStatus;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_SetSockOpt( Socket_t xSocket,
                            int32_t lLevel,
                            int32_t lOptionName,
                            const void * pvOptionValue,
                            size_t xOptionLength )
{
    int32_t lStatus = SOCKETS_ERROR_NONE;
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket; /*lint !e9087 cast used for portability. */
    char ** ppcAlpnIn = ( char ** ) pvOptionValue;
    size_t xLength = 0;
    uint32_t ulProtocol;
    uint32_t lTimeout;

    if( ( xSocket != SOCKETS_INVALID_SOCKET ) && ( xSocket != NULL ) )
    {
        switch( lOptionName )
        {
        case SOCKETS_SO_SERVER_NAME_INDICATION:

            /* Do not set the SNI options if the socket is possibly already connected. */
            if( pxContext->xConnectAttempted == pdTRUE )
            {
                lStatus = SOCKETS_EISCONN;
            }

            /* Non-NULL destination string indicates that SNI extension should
                 * be used during TLS negotiation. */
            else if( NULL == ( pxContext->pcDestination =
                               ( char * ) pvPortMalloc( 1U + xOptionLength ) ) )
            {
                lStatus = SOCKETS_ENOMEM;
            }
            else
            {
                memcpy( pxContext->pcDestination, pvOptionValue, xOptionLength );
                pxContext->pcDestination[ xOptionLength ] = '\0';
            }

            break;

        case SOCKETS_SO_TRUSTED_SERVER_CERTIFICATE:

            /* Do not set the trusted server certificate if the socket is possibly already connected. */
            if( pxContext->xConnectAttempted == pdTRUE )
            {
                lStatus = SOCKETS_EISCONN;
            }

            /* Non-NULL server certificate field indicates that the default trust
                 * list should not be used. */
            else if( NULL == ( pxContext->pcServerCertificate =
                               ( char * ) pvPortMalloc( xOptionLength ) ) )
            {
                lStatus = SOCKETS_ENOMEM;
            }
            else
            {
                memcpy( pxContext->pcServerCertificate, pvOptionValue, xOptionLength );
                pxContext->ulServerCertificateLength = xOptionLength;
            }

            break;

        case SOCKETS_SO_REQUIRE_TLS:

            /* Do not set the TLS option if the socket is possibly already connected. */
            if( pxContext->xConnectAttempted == pdTRUE )
            {
                lStatus = SOCKETS_EISCONN;
            }
            else
            {
                pxContext->xRequireTLS = pdTRUE;
            }

            break;

        case SOCKETS_SO_ALPN_PROTOCOLS:

            /* Do not set the ALPN option if the socket is already connected. */
            if( pxContext->xConnectAttempted == pdTRUE )
            {
                lStatus = SOCKETS_EISCONN;
                break;
            }

            /* Allocate a sufficiently long array of pointers. */
            pxContext->ulAlpnProtocolsCount = 1 + xOptionLength;

            if( NULL == ( pxContext->ppcAlpnProtocols =
                          ( char ** ) pvPortMalloc( pxContext->ulAlpnProtocolsCount * sizeof( char * ) ) ) )
            {
                lStatus = SOCKETS_ENOMEM;
            }
            else
            {
                /* Zero out the pointers. */
                memset( pxContext->ppcAlpnProtocols,
                        0,
                        pxContext->ulAlpnProtocolsCount * sizeof( char * ) );
            }

            /* Copy each protocol string. */
            for( ulProtocol = 0;
                 ( ulProtocol < pxContext->ulAlpnProtocolsCount - 1 ) &&
                 ( pdFREERTOS_ERRNO_NONE == lStatus );
                 ulProtocol++ )
            {
                xLength = strlen( ppcAlpnIn[ ulProtocol ] );

                if( NULL == ( pxContext->ppcAlpnProtocols[ ulProtocol ] =
                              ( char * ) pvPortMalloc( 1 + xLength ) ) )
                {
                    lStatus = SOCKETS_ENOMEM;
                }
                else
                {
                    memcpy( pxContext->ppcAlpnProtocols[ ulProtocol ],
                            ppcAlpnIn[ ulProtocol ],
                            xLength );
                    pxContext->ppcAlpnProtocols[ ulProtocol ][ xLength ] = '\0';
                }
            }

            break;

        case SOCKETS_SO_NONBLOCK:

            pxContext->ulReceiveTimeout = 1;
            pxContext->ulSendTimeout = 1;

            break;

        case SOCKETS_SO_SNDTIMEO:

            lTimeout = *((const uint32_t *) pvOptionValue); /*lint !e9087 pvOptionValue is passed in as an opaque value, and must be casted for setsockopt. */

            /* Valid timeouts are 0 (no timeout) or 1-30000ms. */
            if (lTimeout < securesocketsMAX_TIMEOUT) {
                /* Store send timeout. */
                pxContext->ulSendTimeout = lTimeout;
            } else {
                lStatus = SOCKETS_EINVAL;
            }

            break;

        case SOCKETS_SO_RCVTIMEO:

            lTimeout = *((const uint32_t *) pvOptionValue); /*lint !e9087 pvOptionValue is passed in as an opaque value, and must be casted for setsockopt. */

            /* Valid timeouts are 0 (no timeout) or 1-30000ms. */
            if (lTimeout < securesocketsMAX_TIMEOUT) {
                /* Store receive timeout. */
                pxContext->ulReceiveTimeout = lTimeout;
            } else {
                lStatus = SOCKETS_EINVAL;
            }

            break;
        }
    }
    else
    {
        lStatus = SOCKETS_EINVAL;
    }

    return lStatus;
}
/*-----------------------------------------------------------*/

int32_t SOCKETS_Shutdown( Socket_t xSocket,
                          uint32_t ulHow )
{
    SSOCKETContextPtr_t pxContext = ( SSOCKETContextPtr_t ) xSocket; /*lint !e9087 cast used for portability. */
    int32_t lRetVal = SOCKETS_EINVAL;

    /* Ensure that a valid socket was passed. */
    if( ( xSocket != SOCKETS_INVALID_SOCKET ) && ( xSocket != NULL ) ) {
        /* Shortcut for easy access. */

        switch (ulHow) {
        case SOCKETS_SHUT_RD:
            /* Further receive calls on this socket should return error. */
            pxContext->ulFlags |= securesocketsSOCKET_READ_CLOSED_FLAG;

            /* Return success to the user. */
            lRetVal = SOCKETS_ERROR_NONE;
            break;

        case SOCKETS_SHUT_WR:
            /* Further send calls on this socket should return error. */
            pxContext->ulFlags |= securesocketsSOCKET_WRITE_CLOSED_FLAG;

            /* Return success to the user. */
            lRetVal = SOCKETS_ERROR_NONE;
            break;

        case SOCKETS_SHUT_RDWR:
            /* Further send or receive calls on this socket should return error. */
            pxContext->ulFlags |= securesocketsSOCKET_READ_CLOSED_FLAG;
            pxContext->ulFlags |= securesocketsSOCKET_WRITE_CLOSED_FLAG;

            /* Return success to the user. */
            lRetVal = SOCKETS_ERROR_NONE;
            break;

        default:
            /* An invalid value was passed for ulHow. */
            lRetVal = SOCKETS_EINVAL;
            break;
        }
    }

    return lRetVal;
}
/*-----------------------------------------------------------*/

Socket_t SOCKETS_Socket( int32_t lDomain,
                         int32_t lType,
                         int32_t lProtocol )
{
    SSOCKETContextPtr_t pxContext = NULL;
    uint8_t usSocketNumber = NBIOTconfigMAX_SOCKETS;
    /* Ensure that only supported values are supplied. */
    configASSERT( lDomain == SOCKETS_AF_INET );
    configASSERT( lType == SOCKETS_SOCK_STREAM );
    configASSERT( lProtocol == SOCKETS_IPPROTO_TCP );

    /* Find the free socket */
    for (uint8_t i = 0; i < NBIOTconfigMAX_SOCKETS; ++i){
        if (((1 << i) & ulSocketBitMap) == 0) {
            usSocketNumber = i;
            break;
        }
    }

    /* Create the wrapped socket. */
    if( usSocketNumber  != NBIOTconfigMAX_SOCKETS )
    {
        /* Allocate the internal context structure. */
        if( NULL == ( pxContext = pvPortMalloc( sizeof( SSOCKETContext_t ) ) ) )
        {
            /* Need to close socket. */
            /* Set the according bit in bitmap to zero */
            ulSocketBitMap &= ~(1 << usSocketNumber);
            return  SOCKETS_INVALID_SOCKET;
        }
        else
        {
            /* Set the according bit in bitmap to one */
            ulSocketBitMap |= (1 << usSocketNumber);
            memset( pxContext, 0, sizeof( SSOCKETContext_t ) );
            pxContext->ulFlags = 0;
            pxContext->usNBIoTSocketNumber = usSocketNumber;
            pxContext->ulSendTimeout = socketsconfigDEFAULT_SEND_TIMEOUT;
            pxContext->ulReceiveTimeout = socketsconfigDEFAULT_RECV_TIMEOUT;
        }
    }
    else
    {
        return SOCKETS_INVALID_SOCKET;
    }

    return (Socket_t)pxContext;
}
/*-----------------------------------------------------------*/

BaseType_t SOCKETS_Init( void )
{
    /* Empty initialization for this port. */
    return pdPASS;
}
/*-----------------------------------------------------------*/

static CK_RV prvSocketsGetCryptoSession( CK_SESSION_HANDLE * pxSession,
                                         CK_FUNCTION_LIST_PTR_PTR ppxFunctionList )
{
    CK_RV xResult = 0;
    CK_C_GetFunctionList pxCkGetFunctionList = NULL;
    static CK_SESSION_HANDLE xPkcs11Session = 0;
    static CK_FUNCTION_LIST_PTR pxPkcs11FunctionList = NULL;
    CK_ULONG ulCount = 1;
    CK_SLOT_ID xSlotId = 0;

    portENTER_CRITICAL();

    if( 0 == xPkcs11Session )
    {
        /* One-time initialization. */

        /* Ensure that the PKCS#11 module is initialized. */
        if( 0 == xResult )
        {
            pxCkGetFunctionList = C_GetFunctionList;
            xResult = pxCkGetFunctionList( &pxPkcs11FunctionList );
        }

        if( 0 == xResult )
        {
            xResult = pxPkcs11FunctionList->C_Initialize( NULL );
        }

        /* Get the default slot ID. */
        if( ( 0 == xResult ) || ( CKR_CRYPTOKI_ALREADY_INITIALIZED == xResult ) )
        {
            xResult = pxPkcs11FunctionList->C_GetSlotList( CK_TRUE,
                                                           &xSlotId,
                                                           &ulCount );
        }

        /* Start a session with the PKCS#11 module. */
        if( 0 == xResult )
        {
            xResult = pxPkcs11FunctionList->C_OpenSession( xSlotId,
                                                           CKF_SERIAL_SESSION,
                                                           NULL,
                                                           NULL,
                                                           &xPkcs11Session );
        }
    }

    portEXIT_CRITICAL();

    /* Output the shared function pointers and session handle. */
    *ppxFunctionList = pxPkcs11FunctionList;
    *pxSession = xPkcs11Session;

    return xResult;
}
/*-----------------------------------------------------------*/

uint32_t ulRand( void )
{
    CK_RV xResult = 0;
    CK_SESSION_HANDLE xPkcs11Session = 0;
    CK_FUNCTION_LIST_PTR pxPkcs11FunctionList = NULL;
    uint32_t ulRandomValue = 0;

    xResult = prvSocketsGetCryptoSession( &xPkcs11Session,
                                          &pxPkcs11FunctionList );

    if( 0 == xResult )
    {
        /* Request a sequence of cryptographically random byte values using
         * PKCS#11. */
        xResult = pxPkcs11FunctionList->C_GenerateRandom( xPkcs11Session,
                                                          ( CK_BYTE_PTR ) &ulRandomValue,
                                                          sizeof( ulRandomValue ) );
    }

    /* Check if any of the API calls failed. */
    if( 0 != xResult )
    {
        ulRandomValue = 0;
    }

    return ulRandomValue;
}
/*-----------------------------------------------------------*/

/**
 * @brief Generate a TCP Initial Sequence Number that is reasonably difficult
 * to predict, per https://tools.ietf.org/html/rfc6528.
 */
uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort )
{
    CK_RV xResult = 0;
    CK_SESSION_HANDLE xPkcs11Session = 0;
    CK_FUNCTION_LIST_PTR pxPkcs11FunctionList = NULL;
    CK_MECHANISM xMechSha256 = { 0 };
    uint8_t ucSha256Result[ cryptoSHA256_DIGEST_BYTES ];
    CK_ULONG ulLength = sizeof( ucSha256Result );
    uint32_t ulNextSequenceNumber = 0;
    static uint64_t ullKey = 0;

    /* Acquire a crypto session handle. */
    xResult = prvSocketsGetCryptoSession( &xPkcs11Session,
                                          &pxPkcs11FunctionList );

    if( 0 == xResult )
    {
        if( 0 == ullKey )
        {
            /* One-time initialization, per boot, of the random seed. */
            xResult = pxPkcs11FunctionList->C_GenerateRandom( xPkcs11Session,
                                                              ( CK_BYTE_PTR ) &ullKey,
                                                              sizeof( ullKey ) );
        }
    }

    /* Lock the shared crypto session. */
    portENTER_CRITICAL();

    /* Start a hash. */
    if( 0 == xResult )
    {
        xMechSha256.mechanism = CKM_SHA256;
        xResult = pxPkcs11FunctionList->C_DigestInit( xPkcs11Session, &xMechSha256 );
    }

    /* Hash the seed. */
    if( 0 == xResult )
    {
        xResult = pxPkcs11FunctionList->C_DigestUpdate( xPkcs11Session,
                                                        ( CK_BYTE_PTR ) &ullKey,
                                                        sizeof( ullKey ) );
    }

    /* Hash the source address. */
    if( 0 == xResult )
    {
        xResult = pxPkcs11FunctionList->C_DigestUpdate( xPkcs11Session,
                                                        ( CK_BYTE_PTR ) &ulSourceAddress,
                                                        sizeof( ulSourceAddress ) );
    }

    /* Hash the source port. */
    if( 0 == xResult )
    {
        xResult = pxPkcs11FunctionList->C_DigestUpdate( xPkcs11Session,
                                                        ( CK_BYTE_PTR ) &usSourcePort,
                                                        sizeof( usSourcePort ) );
    }

    /* Hash the destination address. */
    if( 0 == xResult )
    {
        xResult = pxPkcs11FunctionList->C_DigestUpdate( xPkcs11Session,
                                                        ( CK_BYTE_PTR ) &ulDestinationAddress,
                                                        sizeof( ulDestinationAddress ) );
    }

    /* Hash the destination port. */
    if( 0 == xResult )
    {
        xResult = pxPkcs11FunctionList->C_DigestUpdate( xPkcs11Session,
                                                        ( CK_BYTE_PTR ) &usDestinationPort,
                                                        sizeof( usDestinationPort ) );
    }

    /* Get the hash. */
    if( 0 == xResult )
    {
        xResult = pxPkcs11FunctionList->C_DigestFinal( xPkcs11Session,
                                                       ucSha256Result,
                                                       &ulLength );
    }

    portEXIT_CRITICAL();

    /* Use the first four bytes of the hash result as the starting point for
     * all initial sequence numbers for connections based on the input 4-tuple. */
    if( 0 == xResult )
    {
        memcpy( &ulNextSequenceNumber,
                ucSha256Result,
                sizeof( ulNextSequenceNumber ) );

        /* Add the tick count of four-tick intervals. In theory, per the RFC
         * (see above), this approach still allows server equipment to optimize
         * handling of connections from the same device that haven't fully timed out. */
        ulNextSequenceNumber += xTaskGetTickCount() / 4;
    }

    return ulNextSequenceNumber;
}
/*-----------------------------------------------------------*/
#endif

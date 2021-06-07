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

#ifndef AWS_NBIOT_H
#define AWS_NBIOT_H

#include <stdint.h>
#include <stdbool.h>

#include "DAVE.h"

#define NBIOT_CONTEXT_ID            1

#define BG96_MODEM_PIN_PWRKEY       mBUS1_RESET
#define BG96_MODEM_PIN_STATUS       mBUS1_AN

#define vModemPinSetHigh( x )       DIGITAL_IO_SetOutputHigh( x )
#define vModemPinSetLow( x )        DIGITAL_IO_SetOutputLow( x )
#define ulModemPinGet( x )          DIGITAL_IO_GetInput( x )


#define MAX_PKT_LEN                 ( 1400 )
#define MIN( a, b )                 ( ( a ) < ( b ) ? ( a ) : ( b ) )

typedef enum {
    eMODEM_MODE_GSM,
    eMODEM_MODE_NBIOT,
    eMODEM_MODE_CATM1,
    eMODEM_MODES_NUM

} ModemMode_t;

#define MODEM_MODE_GSM_STR          '0'
#define MODEM_MODE_NBIOT_STR        '9'
#define MODEM_MODE_CATM1_STR        '8'

#define PROTOCOL_TYPE_IPv4          1
#define PROTOCOL_TYPE_IPv6          2
#define PROTOCOL_TYPE_IPv4_IPv6     3

#define AUTH_METHOD_NONE            0
#define AUTH_METHOD_PAP             1
#define AUTH_METHOD_CHAP            2
#define AUTH_METHOD_PAP_OR_CHAP     3

/**
 * @brief BG96 modem buffers sizes
 */
#define MODEM_BUFFER_SIZE           2048
#define MODEM_STATUS_BUFFER_SIZE    512
#define MODEM_STATUS_COUNT_LEN      8

/**
 * @brief Secure Sockets send settings
 */
#define NBIOT_SEND_TRYES_IF_FAIL    (5)
#define NBIOT_SEND_DELAY_IF_FAIL    (200)

/**
 * @brief Maximum number of sockets that can be created simultaneously.
 */
#define NBIOTconfigMAX_SOCKETS      ( 5 )

/**
 * @brief Assigned to an Socket_t variable when the socket is not valid.
 */
#define SOCKETS_INVALID_SOCKET      ( ( Socket_t ) ~0U )

/**
 * @brief NBIOT errors initialization.
 */
#define NBIOT_ERROR_OK                     0
#define NBIOT_ERROR_TEST_AT               -1
#define NBIOT_ERROR_PUT_ONLINE            -2
#define NBIOT_ERROR_SIM_PIN               -3
#define NBIOT_ERROR_CHECK_SIM             -4
#define NBIOT_ERROR_SIGNAL_QUALITY        -5
#define NBIOT_ERROR_ATTACH                -6
#define NBIOT_ERROR_ATTACH_STATUS         -7
#define NBIOT_ERROR_NETWORK_REGISTER      -8
#define NBIOT_ERROR_NETWORK_STATUS        -9
#define NBIOT_ERROR_SET_APN               -10
#define NBIOT_ERROR_CONTEXT_ACTIVATE      -11
#define NBIOT_ERROR_CONTEXT_DEACTIVATE    -12
#define NBIOT_ERROR_CONTEXT_STATUS        -13
#define NBIOT_ERROR_CODE_RESULT           -14
#define NBIOT_ERROR_ECHO_MODE             -15
#define NBIOT_ERROR_INFO                  -16
#define NBIOT_ERROR_CURRENT_OPERATOR      -17
#define NBIOT_ERROR_SET_NBIOT             -18
#define NBIOT_ERROR_MUTEX                 -19
#define NBIOT_ERROR_NO_CONNECTION         -20
#define NBIOT_ERROR_SENDING_BUFFER_FULL   -21

enum
{
    eStatus_Success              =  0,
    eStatus_Fail                 =  1,
    eStatus_ReadOnly             =  2,
    eStatus_OutOfRange           =  3,
    eStatus_InvalidArgument      =  4,
    eStatus_Timeout              =  5,
    eStatus_NoTransferInProgress =  6,
};

typedef int32_t status_t;


/**
 * @brief NBIOT timings.
 */
#define NBIOT_TIMING_MSEC_250           250
#define NBIOT_TIMING_SEC_1              1000
#define NBIOT_TIMING_SEC_2              2000
#define NBIOT_TIMING_SEC_3              3000
#define NBIOT_TIMING_SEC_4              4000
#define NBIOT_TIMING_SEC_5              5000
#define NBIOT_TIMING_SEC_10             10000
#define NBIOT_TIMING_SEC_20             20000
#define NBIOT_TIMING_SEC_30             30000
#define NBIOT_TIMING_SEC_50             50000
#define NBIOT_TIMING_SEC_60             60000
#define NBIOT_TIMING_SEC_80             80000
#define NBIOT_TIMING_SEC_100            100000
#define NBIOT_TIMING_SEC_150            150000

#define NBIOT_MAX_SIZE_COMMAND          256
#define SSL_SOCKET_CHUNK_SIZE           128
#define NBIOT_IP_CHUNK_SIZE             128

void vMBus_5V_On( void );
void vMBus_5V_Off( void );
bool NBIOT_bInit( void );
bool NBIOT_bDisable( void );
status_t NBIOT_xTcpPing( uint8_t ucContextID, uint8_t * pcAddress );
status_t NBIOT_xGetRssi( int16_t * psRSSIdBm );
int NBIOT_lGetIpFromName( int lContextID, const char *pcName, char *pcIp );

/* Work with configure SSL */
int NBIOT_lConfigSsl( int lSslCtxID, int lSslVersion, int lSecLevel, char *pcCaCertPath, char *pcClientCertPath, char *pcClientKeyPath );

/* Work with sockets */
int NBIOT_lSslSocketState( int lSocket );
int NBIOT_lSslOpenSocket( int lPdpCtxID, int lSslCtxID, int lSocket, char *pcServerAddres, int lRemotePort );
int NBIOT_lSslSendSocket( int lSocket, unsigned char *pucData, int lLength );
int NBIOT_lSslRecvSocket( int lSocket, unsigned char *pucData, int lMaxLength );
int NBIOT_lSslCloseSocket( int lSocket );

/* Work with files */
int NBIOT_lWriteFile( char *pcName, const char *pcData, int lLength );
int NBIOT_lStorageSize( void );
int NBIOT_lStorageSizeUFS( void );
int NBIOT_lListFile( void );
int NBIOT_lDeleteFile( char *pcName );
int NBIOT_lDeleteAll( void );
void NBIOT_vInitFreeMemory( void );

int NBIOT_lTcpCloseSocket( uint8_t ucSocket );
int NBIOT_lTcpCloseTransparent( uint8_t ucSocket );
int NBIOT_lTcpOpenSocket( uint8_t ucContextID, uint8_t ucSocket, char * pcServerAddres, uint16_t usRemotePort );
int NBIOT_lTcpOpenTransparent( uint8_t usContextID, uint8_t usSocketNumber, char* pcServerAddress, uint16_t usRemotePort );
int NBIOT_lTcpRecvSocket( uint8_t ucSocket, unsigned char * pucData, size_t xMaxLength, uint32_t ulTimeoutMs );
int NBIOT_lTcpRecvTransparent( uint8_t ucSocket, unsigned char * pucData, size_t xMaxLength, uint32_t ulTimeoutMs );
int NBIOT_lTcpSendSocket( uint8_t ucSocket, const unsigned char * pucData, size_t xLength );
int NBIOT_lTcpSendTransparent( unsigned char * pucData, size_t xLength );


#endif /* AWS_NBIOT_H */

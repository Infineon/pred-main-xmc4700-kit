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

#ifndef ISM43340_WIFI_H
#define ISM43340_WIFI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "ism43340_wifi_conf.h"
#include "ism43340_wifi_io.h"


#define ISM43340_WIFI_PAYLOAD_SIZE     	( 1200 )

#define MIN(a, b)  						( (a) < (b) ? (a) : (b) )

typedef int8_t (*IO_Init_Func)(uint16_t );
typedef int8_t (*IO_DeInit_Func)( void);
typedef void (*IO_Delay_Func)(uint32_t);
typedef int16_t (*IO_Receive_Func)(uint8_t *, uint16_t len, uint32_t);
typedef int16_t (*IO_Send_Func)( uint8_t *, uint16_t len, uint32_t);


typedef enum {
    ISM43340_WIFI_INIT                  = 0,
    ISM43340_WIFI_RESET                 = 1,
    ISM43340_WIFI_DEINIT                = 2
} ISM43340_WIFI_InitMode_t;


typedef enum {
    ISM43340_WIFI_STATUS_OK                               = 0,
    ISM43340_WIFI_STATUS_REQ_DATA_STAGE                   = 1,
    ISM43340_WIFI_STATUS_ERROR                            = 2,
    ISM43340_WIFI_STATUS_TIMEOUT                          = 3,
    ISM43340_WIFI_STATUS_IO_ERROR                         = 4,
    ISM43340_WIFI_STATUS_UNEXPECTED_CLOSED_SOCKET         = 5,
    ISM43340_WIFI_STATUS_MODULE_CRASH                     = 6
} ISM43340_WIFI_Status_t;

#define ISM43340_WIFI_ERROR_SPI_FAILED                    -1
#define ISM43340_WIFI_ERROR_WAITING_DRDY_RISING           -2
#define ISM43340_WIFI_ERROR_WAITING_DRDY_FALLING          -3
#define ISM43340_WIFI_ERROR_STUFFING_FOREVER              -4
#define ISM43340_WIFI_ERROR_SPI_INIT                      -5

typedef enum {
    ISM43340_WIFI_MODE_SINGLE           = 0,
    ISM43340_WIFI_MODE_MULTI            = 1,
} ISM43340_WIFI_ConnMode_t;

typedef enum {
    ISM43340_WIFI_TCP_CONNECTION        = 0,
    ISM43340_WIFI_UDP_CONNECTION        = 1,
    ISM43340_WIFI_UDP_LITE_CONNECTION   = 2,
    ISM43340_WIFI_TCP_SSL_CONNECTION    = 3,
    ISM43340_WIFI_MQTT_CONNECTION       = 4,
} ISM43340_WIFI_ConnType_t;

/* Security settings for wifi network */
typedef enum {
    ISM43340_WIFI_SEC_OPEN = 0x00,          /*!< Wifi is open */
    ISM43340_WIFI_SEC_WEP  = 0x01,          /*!< Wired Equivalent Privacy option for wifi security. \note This mode can't be used when setting up ISM43340_WIFI wifi */
    ISM43340_WIFI_SEC_WPA  = 0x02,          /*!< Wi-Fi Protected Access */
    ISM43340_WIFI_SEC_WPA2 = 0x03,          /*!< Wi-Fi Protected Access 2 */
    ISM43340_WIFI_SEC_WPA_WPA2= 0x04,       /*!< Wi-Fi Protected Access with both modes */
    ISM43340_WIFI_SEC_WPA2_TKIP= 0x05,      /*!< Wi-Fi Protected Access with both modes */
    ISM43340_WIFI_SEC_UNKNOWN = 0xFF,       /*!< Wi-Fi Unknown Security mode */
} ISM43340_WIFI_SecurityType_t;

typedef enum {
    ISM43340_WIFI_IPV4 = 0x00,
    ISM43340_WIFI_IPV6 = 0x01,
} ISM43340_WIFI_IPVer_t;

typedef enum {
    ISM43340_WIFI_AP_NONE     = 0x00,
    ISM43340_WIFI_AP_ASSIGNED = 0x01,
    ISM43340_WIFI_AP_JOINED   = 0x02,
    ISM43340_WIFI_AP_ERROR    = 0xFF,
} ISM43340_WIFI_APState_t;

typedef enum {
    ISM43340_WIFI_FUNCTION_TLS = 0x00,
    ISM43340_WIFI_FUNCTION_AWS = 0x01,
} ISM43340_WIFI_CredsFunction_t;

/* Network Auto Connect settings for wifi */
typedef enum {
    ISM43340_WIFI_AUTO_DISABLE = 0x00,			    /*!< Disable Network Auto-Join and Auto Reconnect */
    ISM43340_WIFI_AUTO_JOIN  = 0x01,          	    /*!< Enable Network Auto-Join  */
    ISM43340_WIFI_AUTO_RECONNECT  = 0x02,       	/*!< Enable Auto-Reconnect */
    ISM43340_WIFI_AUTO_JOIN_RECONNECT = 0x03,   	/*!< Enable Both Auto-Join and Auto Reconnect */
} ISM43340_WIFI_NetworkAutoConnect_t;


typedef struct {
    uint32_t Port;
    uint32_t BaudRate;
    uint32_t DataWidth;
    uint32_t Parity;
    uint32_t StopBits;
    uint32_t Mode;
} ISM43340_WIFI_UARTConfig_t;

typedef struct {
    uint32_t Configuration;
    uint32_t WPSPin;
    uint32_t VID;
    uint32_t PID;
    uint8_t  MAC[6];
    uint8_t  AP_IPAddress[4];
    uint32_t PS_Mode;
    uint32_t RadioMode;
    uint32_t CurrentBeacon;
    uint32_t PrevBeacon;
    uint32_t ProductName;
} ISM43340_WIFI_SystemConfig_t;

typedef struct {
    uint8_t* Address;                                   /*!< Pointer to domain or IP to ping */
    uint32_t Time;                                      /*!< Time in milliseconds needed for pinging */
    uint8_t Success;                                    /*!< Status indicates if ping was successful */
} ISM43340_WIFI_Ping_t;

typedef struct {
    uint8_t SSID[ISM43340_WIFI_MAX_SSID_NAME_SIZE + 1]; /*!< Service Set Identifier value.Wi-Fi spot name */
    ISM43340_WIFI_SecurityType_t Security;              /*!< Security of Wi-Fi spot.  */
    int16_t RSSI;                                       /*!< Signal strength of Wi-Fi spot */
    uint8_t MAC[6];                                     /*!< MAC address of spot */
    uint8_t Channel;                                    /*!< Wi-Fi channel */
} ISM43340_WIFI_AP_t;

/* Access point configuration */
typedef struct {
    uint8_t SSID[ISM43340_WIFI_MAX_SSID_NAME_SIZE + 1];   /*!< Network public name for AP mode */
    uint8_t Pass[ISM43340_WIFI_MAX_PSWD_NAME_SIZE + 1];   /*!< Network password for AP mode */
    ISM43340_WIFI_SecurityType_t Security;                /*!< Security of Wi-Fi spot */
    uint8_t Channel;                                      /*!< Channel Wi-Fi is operating at */
    uint8_t MaxConnections;                               /*!< Max number of stations that are allowed to connect to AP, between 1 and 4 */
    uint8_t Hidden;                                       /*!< Set to 1 if network is hidden (not broadcast) or zero if noz */
} ISM43340_WIFI_APConfig_t;

typedef struct {
    uint8_t SSID[ISM43340_WIFI_MAX_SSID_NAME_SIZE + 1];   /*!< Network public name for AP mode */
    uint8_t IP_Addr[4];                                   /*!< IP Address */
    uint8_t MAC_Addr[6];                                  /*!< MAC address */
} ISM43340_WIFI_APSettings_t;

typedef struct {
    ISM43340_WIFI_AP_t AP[ISM43340_WIFI_MAX_DETECTED_AP];
    uint8_t nbr;
} ISM43340_WIFI_APs_t;

typedef struct {
    uint8_t          SSID[ISM43340_WIFI_MAX_SSID_NAME_SIZE + 1];
    uint8_t          pswd[ISM43340_WIFI_MAX_PSWD_NAME_SIZE + 1];
    ISM43340_WIFI_SecurityType_t Security;
    uint8_t          DHCP_IsEnabled;
    uint8_t          JoinRetries;
    uint8_t          IsConnected;
    uint8_t          AutoConnect;
    ISM43340_WIFI_IPVer_t  IP_Ver;
    uint8_t          IP_Addr[4];
    uint8_t          IP_Mask[4];
    uint8_t          Gateway_Addr[4];
    uint8_t          DNS1[4];
    uint8_t          DNS2[4];
} ISM43340_WIFI_Network_t;

typedef struct {
    ISM43340_WIFI_ConnType_t  Protocol;
    uint8_t          Local_IP_Addr[4];
    uint16_t         Local_Port;
    uint8_t          Remote_IP_Addr[4];
    uint16_t         Remote_Port;
    uint8_t          TCP_Server;
    uint8_t          UDP_Server;
    uint8_t          TCP_Backlogs;
    uint8_t          Accept_Loop;
    uint8_t          Read_Mode;
} ISM43340_WIFI_Transport_t;

typedef struct {
    ISM43340_WIFI_ConnType_t Type;
    uint8_t            Number;
    uint16_t           RemotePort;
    uint16_t           LocalPort;
    uint8_t            RemoteIP[4];
    char*              Name;
    uint8_t            Backlog;
} ISM43340_WIFI_Conn_t;

typedef struct {
    IO_Init_Func       IO_Init;
    IO_DeInit_Func     IO_DeInit;
    IO_Delay_Func      IO_Delay;
    IO_Send_Func       IO_Send;
    IO_Receive_Func    IO_Receive;
} ISM43340_WIFI_IO_t;

typedef struct {
    uint8_t           Product_ID[ISM43340_WIFI_PRODUCT_ID_SIZE];
    uint8_t           FW_Rev[ISM43340_WIFI_FW_REV_SIZE];
    uint8_t           API_Rev[ISM43340_WIFI_API_REV_SIZE];
    uint8_t           Stack_Rev[ISM43340_WIFI_STACK_REV_SIZE];
    uint8_t           RTOS_Rev[ISM43340_WIFI_RTOS_REV_SIZE];
    uint8_t           Product_Name[ISM43340_WIFI_PRODUCT_NAME_SIZE];
    uint32_t          CPU_Clock;
    ISM43340_WIFI_SecurityType_t Security;
    ISM43340_WIFI_Network_t NetSettings;
    ISM43340_WIFI_APSettings_t APSettings;
    ISM43340_WIFI_IO_t fops;
    uint8_t            RxTxData[ISM43340_WIFI_DATA_SIZE];
    uint32_t           RxTxDataLength;
    uint32_t           Timeout;
} ISM43340_WIFIObject_t;


/* Exported functions --------------------------------------------------------*/
ISM43340_WIFI_Status_t  ISM43340_WIFI_Init( ISM43340_WIFIObject_t *Obj );
ISM43340_WIFI_Status_t  ISM43340_WIFI_DeInit( ISM43340_WIFIObject_t *Obj );
ISM43340_WIFI_Status_t  ISM43340_WIFI_SetTimeout( ISM43340_WIFIObject_t *Obj, uint32_t Timeout );
ISM43340_WIFI_Status_t  ISM43340_WIFI_ListAccessPoints( ISM43340_WIFIObject_t *Obj, ISM43340_WIFI_APs_t *APs );
ISM43340_WIFI_Status_t  ISM43340_WIFI_Connect( ISM43340_WIFIObject_t *Obj, const char* SSID, const char* Password, ISM43340_WIFI_SecurityType_t SecType );
ISM43340_WIFI_Status_t  ISM43340_WIFI_Disconnect( ISM43340_WIFIObject_t *Obj );
uint8_t                 ISM43340_WIFI_IsConnected( ISM43340_WIFIObject_t *Obj );
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetNetworkSettings( ISM43340_WIFIObject_t *Obj );
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetMACAddress( ISM43340_WIFIObject_t *Obj, uint8_t *mac );
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetFWRevID( ISM43340_WIFIObject_t *Obj, uint8_t *FWRev );
ISM43340_WIFI_Status_t  ISM43340_WIFI_Ping( ISM43340_WIFIObject_t *Obj, uint8_t *address, uint16_t count, uint16_t interval_ms );
ISM43340_WIFI_Status_t  ISM43340_WIFI_DNS_LookUp( ISM43340_WIFIObject_t *Obj, const char *url, uint8_t *ipaddress );
ISM43340_WIFI_Status_t  ISM43340_WIFI_StartClientConnection( ISM43340_WIFIObject_t *Obj, ISM43340_WIFI_Conn_t *conn );
ISM43340_WIFI_Status_t  ISM43340_WIFI_StopClientConnection( ISM43340_WIFIObject_t *Obj, ISM43340_WIFI_Conn_t *conn );
ISM43340_WIFI_Status_t  ISM43340_WIFI_SendData( ISM43340_WIFIObject_t *Obj, uint8_t Socket, uint8_t *pdata, uint16_t Reqlen , uint16_t *SentLen, uint32_t Timeout );
ISM43340_WIFI_Status_t  ISM43340_WIFI_ReceiveData( ISM43340_WIFIObject_t *Obj, uint8_t Socket, uint8_t *pdata, uint16_t Reqlen, uint16_t *Receivedlen, uint32_t Timeout );
ISM43340_WIFI_Status_t  ISM43340_WIFI_ActivateAP( ISM43340_WIFIObject_t *Obj, ISM43340_WIFI_APConfig_t *ApConfig );
int32_t                 ISM43340_WIFI_GetRssi( ISM43340_WIFIObject_t *Obj );
ISM43340_WIFI_Status_t  ISM43340_WIFI_RegisterBusIO( ISM43340_WIFIObject_t *Obj, IO_Init_Func    IO_Init,
                                                                                IO_DeInit_Func  IO_DeInit,
                                                                                IO_Delay_Func   IO_Delay,
                                                                                IO_Send_Func    IO_Send,
                                                                                IO_Receive_Func IO_Receive );

#ifdef __cplusplus
}
#endif

#endif /* ISM43340_WIFI_H */

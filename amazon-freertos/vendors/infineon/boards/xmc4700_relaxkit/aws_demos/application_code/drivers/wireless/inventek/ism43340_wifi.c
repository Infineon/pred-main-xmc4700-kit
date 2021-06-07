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

#include <stdlib.h>

#include "ism43340_wifi.h"


#define AT_OK_STRING            "\r\nOK\r\n> "
#define INIT_OK_STRING          "> "
#define AT_OK_STRING_LEN        (sizeof(AT_OK_STRING) - 1)

#define AT_ERROR_STRING         "\r\nERROR"

#define AT_DELIMETER_STRING     "\r\n> "
#define AT_DELIMETER_LEN        4

/* This is version 3.5.2.5, with the byte order reversed for easy comparison */
#define UPDATED_SCAN_PARAMETERS_FW_REV (0x05020503)

#define CHARISHEXNUM(x)                 (((x) >= '0' && (x) <= '9') || \
                                         ((x) >= 'a' && (x) <= 'f') || \
                                         ((x) >= 'A' && (x) <= 'F'))

#define CHARISNUM(x)                    ((x) >= '0' && (x) <= '9')
#define CHAR2NUM(x)                     ((x) - '0')

static uint8_t prvHex2Num( char cHex );
static uint32_t prvParseHexNumber( char* pcPtr, uint8_t* pucCnt );
static int32_t prvParseNumber( char* pcPtr, uint8_t* pucCnt );
static void prvParseMAC( char* pcPtr, uint8_t* pucArr );
static void prvParseIP( char* pcPtr, uint8_t* pucArr );
static ISM43340_WIFI_SecurityType_t prvParseSecurity( char* pcPtr );
static void prvAT_ParseConnSettings( char *pcData, ISM43340_WIFI_Network_t *pxNetSettings );
static void prvAT_ParseIsConnected( char *pcData, uint8_t *pucIsConnected );
static ISM43340_WIFI_Status_t prvAT_ExecuteCommand( ISM43340_WIFIObject_t *pxObj );



/**
  * @brief  Convert char in Hex format to integer.
  * @param  cHex: character to convert
  * @retval uint8_t value.
  */
static  uint8_t prvHex2Num( char cHex )
{
    if( cHex >= '0' && cHex <= '9' ) /* Char is num */
    {
        return cHex - '0';
    }
    else if( cHex >= 'a' && cHex <= 'f' ) /* Char is lowercase character A - Z (hex) */
    {
        return ( cHex - 'a' ) + 10;
    }
    else if( cHex >= 'A' && cHex <= 'F' ) /* Char is uppercase character A - Z (hex) */
    {
        return ( cHex - 'A' ) + 10;
    }

    return 0;
}

/**
  * @brief  Extract a hex number from a string.
  * @param  pcPtr: pointer to string
  * @param  pucCnt: pointer to the number of parsed digit
  * @retval uint32_t Hex value.
  */
static uint32_t prvParseHexNumber( char* pcPtr, uint8_t* pucCnt )
{
    uint32_t ulSum = 0;
    uint8_t ucI = 0;

    while( CHARISHEXNUM(*pcPtr) )      /* Parse number */
    {
        ulSum <<= 4;
        ulSum += prvHex2Num(*pcPtr);
        pcPtr++;
        ucI++;
    }

    if( pucCnt != NULL )               /* Save number of characters used for number */
    {
        *pucCnt = ucI;
    }

    return ulSum;                       /* Return number */
}

/**
  * @brief  Parses and returns number from string.
  * @param  pcPtr: pointer to string
  * @param  pucCnt: pointer to the number of parsed digit
  * @retval int32_t value.
  */
static int32_t prvParseNumber( char* pcPtr, uint8_t* pucCnt )
{
    uint8_t ucMinus = 0, ucI = 0;
    int32_t lSum = 0;

    if( *pcPtr == '-' )         /* Check for minus character */
    {
        ucMinus = 1;
        pcPtr++;
        ucI++;
    }
    while( CHARISNUM( *pcPtr ) ) /* Parse number */
    {
        lSum = 10 * lSum + CHAR2NUM( *pcPtr );
        pcPtr++;
        ucI++;
    }
    if( pucCnt != NULL )         /* Save number of characters used for number */
    {
        *pucCnt = ucI;
    }
    if( ucMinus )                 /* Minus detected */
    {
        return 0 - lSum;
    }
    return lSum;             /* Return number */
}

/**
  * @brief  Parses and returns MAC address.
  * @param  pcPtr: pointer to string
  * @param  pucArr: pointer to MAC array
  * @retval None.
  */
static void prvParseMAC( char* pcPtr, uint8_t* pucArr )
{
    uint8_t ucHexnum = 0, ucHexcnt;

    while( * pcPtr )
    {
        ucHexcnt = 1;
        if( *pcPtr != ':' )
        {
            pucArr[ucHexnum++] = prvParseHexNumber( pcPtr, &ucHexcnt );
        }
        pcPtr = pcPtr + ucHexcnt;
    }
}

/**
  * @brief  Parses and returns IP address.
  * @param  pcPtr: pointer to string
  * @param  pucArr: pointer to IP array
  * @retval None.
  */
static  void prvParseIP( char* pcPtr, uint8_t* pucArr )
{
    uint8_t ucHexnum = 0, ucHexcnt;

    while( * pcPtr )
    {
        ucHexcnt = 1;
        if(*pcPtr != '.')
        {
            pucArr[ucHexnum++] = prvParseNumber( pcPtr, &ucHexcnt );
        }
        pcPtr = pcPtr + ucHexcnt;
    }
}

/**
  * @brief  Parses Security type.
  * @param  pcPtr: pointer to string
  * @retval Encryption type.
  */
static ISM43340_WIFI_SecurityType_t prvParseSecurity( char* pcPtr )
{
  if( strstr(pcPtr,"Open") )            return ISM43340_WIFI_SEC_OPEN;
  else if( strstr(pcPtr,"WEP") )        return ISM43340_WIFI_SEC_WEP;
  else if( strstr(pcPtr,"WPA WPA2") )   return ISM43340_WIFI_SEC_WPA_WPA2;
  else if( strstr(pcPtr,"WPA2 TKIP") )  return ISM43340_WIFI_SEC_WPA2_TKIP;
  else if( strstr(pcPtr,"WPA2") )       return ISM43340_WIFI_SEC_WPA2;
  else if( strstr(pcPtr,"WPA") )        return ISM43340_WIFI_SEC_WPA;
  else                                  return ISM43340_WIFI_SEC_UNKNOWN;
}

/**
  * @brief  Parses ES module informations and save them in the handle.
  * @param  xObj: pointer to module handle
  * @param  pData: pointer to string
  * @retval None.
  */
static void AT_ParseInfo( ISM43340_WIFIObject_t *xObj,uint8_t *pData )
{
    char *pcPtr;
    uint8_t ucNum = 0;

    pcPtr = strtok( (char *)pData + 2, "," );

    while( pcPtr != NULL )
    {
        switch( ucNum++ )
        {
            case 0:
                strncpy( (char *)xObj->Product_ID,  pcPtr, ISM43340_WIFI_PRODUCT_ID_SIZE );
                break;

            case 1:
                strncpy( (char *)xObj->FW_Rev,  pcPtr, ISM43340_WIFI_FW_REV_SIZE );
                break;

            case 2:
                strncpy( (char *)xObj->API_Rev,  pcPtr, ISM43340_WIFI_API_REV_SIZE );
                break;

            case 3:
                strncpy( (char *)xObj->Stack_Rev,  pcPtr, ISM43340_WIFI_STACK_REV_SIZE );
                break;

            case 4:
                strncpy( (char *)xObj->RTOS_Rev,  pcPtr, ISM43340_WIFI_RTOS_REV_SIZE );
                break;

            case 5:
                xObj->CPU_Clock = prvParseNumber( pcPtr, NULL );
                break;

            case 6:
                pcPtr = strtok( pcPtr, "\r" );
                strncpy( (char *)xObj->Product_Name,  pcPtr, ISM43340_WIFI_PRODUCT_NAME_SIZE );
                break;

            default: break;
        }
        pcPtr = strtok( NULL, "," );
    }
}

/**
  * @brief  Parses Access point configuration.
  * @param  pxAPs: Access points structure
  * @param  pcData: pointer to string
  * @retval None.
  */
static void prvAT_ParseAP( char *pcData, ISM43340_WIFI_APs_t *pxAPs )
{
    uint8_t ucNum = 0;
    char *pcPtr;
    pxAPs->nbr = 0;

    pcPtr = strtok( pcData + 2, "," );

    while( (pcPtr != NULL) && (pxAPs->nbr < ISM43340_WIFI_MAX_DETECTED_AP) )
    {
        switch (ucNum++)
        {
            case 0: /* Ignore index */
            case 4: /* Ignore Max Rate */
            case 5: /* Ignore Network Type */
            case 7: /* Ignore Radio Band */
                break;

            case 1:
                pcPtr[strlen(pcPtr) - 1] = 0;
                strncpy( (char *)pxAPs->AP[pxAPs->nbr].SSID,  pcPtr+ 1, ISM43340_WIFI_MAX_SSID_NAME_SIZE + 1 );
                break;

            case 2:
                prvParseMAC( pcPtr, pxAPs->AP[pxAPs->nbr].MAC );
                break;

            case 3:
                pxAPs->AP[pxAPs->nbr].RSSI = prvParseNumber( pcPtr, NULL );
                break;

            case 6:
                pxAPs->AP[pxAPs->nbr].Security = prvParseSecurity( pcPtr );
                break;

            case 8:
                pxAPs->AP[pxAPs->nbr].Channel = prvParseNumber( pcPtr, NULL );
                pxAPs->nbr++;
                ucNum = 1;
                break;

            default:
                break;
        }
        pcPtr = strtok( NULL, "," );
    }
}

/**
  * @brief  Reverse 32 bit value byte order
  * @param  pucBuf: pointer to value
  * @retval uint32_t reversed value.
  */
static uint32_t prvReverseByteOrder32bit( uint8_t * pucBuf )
{
    return ((pucBuf[0] << 0) | (pucBuf[1] << 8) | (pucBuf[2] << 16) | (pucBuf[3] << 24));
}

/**
  * @brief  Parses FW revision
  * @param  pucVer: version array (4 position 8-bit array)
  * @param  pcData: pointer to string
  * @retval None.
  */
static void prvAT_ParseFWRev(char *pcData, uint8_t *pucVer)
{
    uint8_t ucNum = 0;
    char *pucPtr;

    pucPtr = strtok( pcData + 1, "." );

    while( (pucPtr != NULL) && (ucNum < 4) )
    {
        switch( ucNum )
        {
            case 0:
            case 1:
            case 2:
            case 3:
                pucVer[ucNum] = atoi( pucPtr );
                break;

            default:
                break;
        }
        ucNum++;
        pucPtr = strtok( NULL, "." );
    }
}

/**
  * @brief  Parses Access point configuration.
  * @param  pxAP: Access points structure
  * @param  pcData: pointer to string
  * @retval None.
  */
static void prvAT_ParseSingleAP( char *pcData, ISM43340_WIFI_AP_t *pxAP )
{
    uint8_t ucNum = 0;
    char *pcPtr;

    pcPtr = strtok( pcData + 2, "," );

    while( pcPtr != NULL )
    {
        switch( ucNum++ )
        {
            case 0: /* Ignore index */
            case 4: /* Ignore Max Rate */
            case 5: /* Ignore Network Type */
            case 7: /* Ignore Radio Band */
                break;

            case 1:
                pcPtr[strlen(pcPtr) - 1] = 0;
                strncpy( (char *)pxAP->SSID,  pcPtr+ 1, ISM43340_WIFI_MAX_SSID_NAME_SIZE + 1 );
                break;

            case 2:
                prvParseMAC( pcPtr, pxAP->MAC );
                break;

            case 3:
                pxAP->RSSI = prvParseNumber( pcPtr, NULL );
                break;

            case 6:
                pxAP->Security = prvParseSecurity( pcPtr );
                break;

            case 8:
                pxAP->Channel = prvParseNumber( pcPtr, NULL );
                ucNum = 1;
                break;

            default:
                break;
        }
        pcPtr = strtok( NULL, "," );
    }
}

/**
  * @brief  Parses WIFI connection settings.
  * @param  pxNetSettings: settings
  * @param  pcData: pointer to data
  * @retval None.
  */
static void prvAT_ParseConnSettings(char *pcData, ISM43340_WIFI_Network_t *pxNetSettings)
{
    uint8_t ucNum = 0;
    char *pcPtr;

    pcPtr = strtok( pcData + 2, "," );

    while( pcPtr != NULL )
    {
        switch( ucNum++ )
        {
            case 0:
                strncpy( (char *)pxNetSettings->SSID,  pcPtr, ISM43340_WIFI_MAX_SSID_NAME_SIZE + 1 );
                break;

            case 1:
                strncpy( (char *)pxNetSettings->pswd,  pcPtr, ISM43340_WIFI_MAX_PSWD_NAME_SIZE + 1 );
                break;

            case 2:
                pxNetSettings->Security = (ISM43340_WIFI_SecurityType_t)prvParseNumber( pcPtr, NULL );
                break;

            case 3:
                pxNetSettings->DHCP_IsEnabled = prvParseNumber( pcPtr, NULL );
                break;

            case 4:
                pxNetSettings->IP_Ver = (ISM43340_WIFI_IPVer_t)prvParseNumber( pcPtr, NULL );
                break;

            case 5:
                prvParseIP( pcPtr, pxNetSettings->IP_Addr );
                break;

            case 6:
                prvParseIP( pcPtr, pxNetSettings->IP_Mask );
                break;

            case 7:
                prvParseIP( pcPtr, pxNetSettings->Gateway_Addr );
                break;

            case 8:
                prvParseIP( pcPtr, pxNetSettings->DNS1 );
                break;

            case 9:
                prvParseIP( pcPtr, pxNetSettings->DNS2 );
                break;

            case 10:
                pxNetSettings->JoinRetries = prvParseNumber( pcPtr, NULL );
                break;

            case 11:
                pxNetSettings->AutoConnect = prvParseNumber( pcPtr, NULL );
                break;

            default:
                break;
        }
        pcPtr = strtok( NULL, "," );
        if( ( pcPtr != NULL ) && ( pcPtr[-1] == ',' ) )
        { /* Ignore empty fields */
            ucNum++;
        }
    }
}

/**
  * @brief  Parses the connection status
  * @param  pcData: pointer to data
  * @param  plRssi: pointer to RSSI value
  * @retval None.
  */
static void prvAT_ParseRssi( char *pcData, int32_t *plRssi )
{
    *plRssi = prvParseNumber( pcData + 2, NULL );
}


/**
  * @brief  Parses the connection status
  * @param  pData: pointer to data
  * @param  usIsConnected: pointer to result
  * @retval None.
  */
static void prvAT_ParseIsConnected( char *pcData, uint8_t *usIsConnected)
{
    *usIsConnected = ( pcData[2] == '1' ) ? 1 : 0;
}

/**
  * @brief  Execute AT command.
  * @param  pxObj: pointer to module handle
  * @retval Operation Status.
  */
static ISM43340_WIFI_Status_t prvAT_ExecuteCommand( ISM43340_WIFIObject_t *pxObj )
{
    int16_t sRet = 0;
    int16_t sRecvLen = 0;

    LOCK_WIFI();  

    sRet = pxObj->fops.IO_Send( pxObj->RxTxData, pxObj->RxTxDataLength, pxObj->Timeout );

    if( sRet > 0 )
    {
        sRecvLen = pxObj->fops.IO_Receive( pxObj->RxTxData, ISM43340_WIFI_DATA_SIZE, pxObj->Timeout );
        pxObj->RxTxDataLength = sRecvLen;
        if( (sRecvLen > 0) && ( sRecvLen < ISM43340_WIFI_DATA_SIZE) )
        {
            *(pxObj->RxTxData + sRecvLen) = 0;
            if( strstr( (char *)pxObj->RxTxData, AT_OK_STRING ) )
            {
                UNLOCK_WIFI();
                return ISM43340_WIFI_STATUS_OK;
            }
            else if( strstr( (char *)pxObj->RxTxData, AT_ERROR_STRING ) )
            {
                UNLOCK_WIFI();
                return ISM43340_WIFI_STATUS_UNEXPECTED_CLOSED_SOCKET;
            }
        }
        if(sRecvLen == ISM43340_WIFI_ERROR_STUFFING_FOREVER )
        {
            UNLOCK_WIFI();
            return ISM43340_WIFI_STATUS_MODULE_CRASH;
        }
    }
    UNLOCK_WIFI();  
    return ISM43340_WIFI_STATUS_IO_ERROR;
}



/**
  * @brief  Parses Received data.
  * @param  pxObj: pointer to module handle
  * @param  pucCmd:command formatted string
  * @param  pcData: payload
  * @param  usReqlen : requested Data length.
  * @param  pusReadData : pointer to received data length.
  * @retval Operation Status.
  */
static ISM43340_WIFI_Status_t AT_RequestReceiveData( ISM43340_WIFIObject_t *pxObj, uint8_t* pucCmd, char *pcData, uint16_t usReqlen, uint16_t *pusReadData )
{
    int16_t sLen;
    uint8_t *pucData = pxObj->RxTxData;

    LOCK_WIFI();

    if( pxObj->fops.IO_Send( pucCmd, strlen( (char*)pucCmd ), pxObj->Timeout ) > 0 )
    {
        sLen = pxObj->fops.IO_Receive(pucData, 0 , pxObj->Timeout);
        if( (pucData[0]!='\r') || (pucData[1]!='\n') )
        {
            UNLOCK_WIFI();
            return  ISM43340_WIFI_STATUS_IO_ERROR;
        }
        sLen-=2;
        pucData+=2;
        if( sLen >= AT_OK_STRING_LEN )
        {
            while( sLen && ( pucData[sLen-1]==0x15 ) ) 
            {
                sLen--;
            }
            pucData[sLen] = '\0';
            if( strstr( (char*) pucData + sLen - AT_OK_STRING_LEN, AT_OK_STRING) )
            {
                *pusReadData = sLen - AT_OK_STRING_LEN;
                if( *pusReadData > usReqlen )
                {
                    *pusReadData = usReqlen;
                }
                memcpy( pcData, pucData, *pusReadData );
                UNLOCK_WIFI();
                return ISM43340_WIFI_STATUS_OK;
            }
            else if( memcmp( (char *)pucData + sLen - AT_DELIMETER_LEN , AT_DELIMETER_STRING, AT_DELIMETER_LEN ) == 0 )
            {
                *pusReadData = 0;
                UNLOCK_WIFI();
                return ISM43340_WIFI_STATUS_UNEXPECTED_CLOSED_SOCKET;
            }

            *pusReadData = 0;
            UNLOCK_WIFI();
            return ISM43340_WIFI_STATUS_UNEXPECTED_CLOSED_SOCKET;
        }
        if( sLen == ISM43340_WIFI_ERROR_STUFFING_FOREVER )
        {
            UNLOCK_WIFI();
            return ISM43340_WIFI_STATUS_MODULE_CRASH;
        }
    }
    UNLOCK_WIFI();
    return ISM43340_WIFI_STATUS_IO_ERROR;
}


/**
  * @brief  Initialize WIFI module.
  * @param  pxObj: pointer to module handle
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_Init( ISM43340_WIFIObject_t *pxObj )
{
    ISM43340_WIFI_Status_t xRet = ISM43340_WIFI_STATUS_ERROR;

    pxObj->Timeout = ISM43340_WIFI_TIMEOUT;

    if( pxObj->fops.IO_Init(ISM43340_WIFI_INIT) == 0 )
    {
        LOCK_WIFI();

        sprintf( (char *)pxObj->RxTxData, "I?\r" );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData);
        xRet = prvAT_ExecuteCommand( pxObj );

        if(xRet == ISM43340_WIFI_STATUS_OK)
        {
            AT_ParseInfo (pxObj, pxObj->RxTxData);
            configPRINTF( ("WiFi Module info: \r\n") );
            configPRINTF( ("    Product ID:      %s\r\n",pxObj->Product_ID) );
            configPRINTF( ("    FW Revision:     %s\r\n",pxObj->FW_Rev) );
            configPRINTF( ("    API Revision:    %s\r\n",pxObj->API_Rev) );
            configPRINTF( ("    Stack Revision:  %s\r\n",pxObj->Stack_Rev) );
            configPRINTF( ("    RTOS Revision:   %s\r\n",pxObj->RTOS_Rev) );
            configPRINTF( ("    CPU Clock:       %.1f MHz\r\n\r\n",(double)pxObj->CPU_Clock/1000000) );
        }

        UNLOCK_WIFI();
    }
    return xRet;
}

/**
  * @brief  DeInitialize WIFI module.
  * @param  pxObj: pointer to module handle
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_DeInit( ISM43340_WIFIObject_t *pxObj )
{
    ISM43340_WIFI_Status_t xRet = ISM43340_WIFI_STATUS_OK;

    pxObj->Timeout = ISM43340_WIFI_TIMEOUT;

    pxObj->fops.IO_DeInit();
    return xRet;
}

/**
  * @brief  Return ProductID.
  * @param  pxObj: pointer to module handle
  * @param  pucPoductID: pointer productID
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetProductID( ISM43340_WIFIObject_t *pxObj, uint8_t *pucPoductID )
{
    strncpy( (char *)pucPoductID, (char *)pxObj->Product_ID, ISM43340_WIFI_PRODUCT_ID_SIZE );
    return ISM43340_WIFI_STATUS_OK;
}

/**
  * @brief  Return Firmware Revision.
  * @param  pxObj: pointer to module handle
  * @param  pucFWRev: pointer FW Revision
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetFWRevID( ISM43340_WIFIObject_t *pxObj, uint8_t *pucFWRev )
{
    strncpy( (char *)pucFWRev, (char *)pxObj->FW_Rev, ISM43340_WIFI_FW_REV_SIZE );
    return ISM43340_WIFI_STATUS_OK;
}

/**
  * @brief  Return product Name.
  * @param  pxObj: pointer to module handle
  * @param  pucProductName: pointer product Name
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetProductName( ISM43340_WIFIObject_t *pxObj, uint8_t *pucProductName )
{
    strncpy((char *)pucProductName, (char *)pxObj->Product_Name, ISM43340_WIFI_PRODUCT_NAME_SIZE);
    return ISM43340_WIFI_STATUS_OK;
}

/**
  * @brief  Return API revision.
  * @param  pxObj: pointer to module handle
  * @param  pucAPIRev: pointer API revision.
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetAPIRev( ISM43340_WIFIObject_t *pxObj, uint8_t *pucAPIRev )
{
    strncpy( (char *)pucAPIRev, (char *)pxObj->API_Rev, ISM43340_WIFI_API_REV_SIZE );
    return ISM43340_WIFI_STATUS_OK;
}

/**
  * @brief  Return Stack Revision.
  * @param  pxObj: pointer to module handle
  * @param  pucStackRev: pointer Stack Revision
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetStackRev( ISM43340_WIFIObject_t *pxObj, uint8_t *pucStackRev )
{
    strncpy( (char *)pucStackRev, (char *)pxObj->Stack_Rev, ISM43340_WIFI_STACK_REV_SIZE );
    return ISM43340_WIFI_STATUS_OK;
}

/**
  * @brief  Return RTOS Revision
  * @param  pxObj: pointer to module handle
  * @param  pucRTOSRev: pointer RTOS Revision
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_GetRTOSRev( ISM43340_WIFIObject_t *pxObj, uint8_t *pucRTOSRev )
{
    strncpy( (char *)pucRTOSRev, (char *)pxObj->RTOS_Rev, ISM43340_WIFI_RTOS_REV_SIZE );
    return ISM43340_WIFI_STATUS_OK;
}


/**
  * @brief  Initialize WIFI module.
  * @param  pxObj: pointer to module handle
  * @param  pcIO_Init: pointer to Init function
  * @param  pcIO_DeInit: pointer to DeInit function
  * @param  pvIO_Delay: pointer to Delay function
  * @param  psIO_Send: pointer to Send function
  * @param  psIO_Receive: pointer Receive function
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_RegisterBusIO( ISM43340_WIFIObject_t *pxObj, IO_Init_Func pcIO_Init,
                                                              IO_DeInit_Func  pcIO_DeInit,
                                                              IO_Delay_Func   pvIO_Delay,
                                                              IO_Send_Func    psIO_Send,
                                                              IO_Receive_Func  psIO_Receive )
{
    if(!pxObj || !pcIO_Init || !pcIO_DeInit || !psIO_Send || !psIO_Receive)
    {
        return ISM43340_WIFI_STATUS_ERROR;
    }

    pxObj->fops.IO_Init = pcIO_Init;
    pxObj->fops.IO_DeInit = pcIO_DeInit;
    pxObj->fops.IO_Send = psIO_Send;
    pxObj->fops.IO_Receive = psIO_Receive;
    pxObj->fops.IO_Delay = pvIO_Delay;

    return ISM43340_WIFI_STATUS_OK;
}

/**
  * @brief  Change default Timeout.
  * @param  pxObj: pointer to module handle
  * @param  ulTimeout: Timeout in mS
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_SetTimeout( ISM43340_WIFIObject_t *pxObj, uint32_t ulTimeout )
{
    pxObj->Timeout = ulTimeout;
    return ISM43340_WIFI_STATUS_OK;
}

/**
  * @brief  List all detected APs.
  * @param  pxObj: pointer to module handle
  * @param  pxAPs: pointer Access points structure
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t  ISM43340_WIFI_ListAccessPoints( ISM43340_WIFIObject_t *pxObj, ISM43340_WIFI_APs_t *pxAPs )
{
    ISM43340_WIFI_Status_t xRet;
    int16_t sSendLen;
    int16_t sRecvLen = 0;
    uint8_t pucVersion[4] = { 0 };

    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData, (const char*)pxObj->FW_Rev );

    prvAT_ParseFWRev( (char*)pxObj->RxTxData, pucVersion );

    if( prvReverseByteOrder32bit(pucVersion) >= UPDATED_SCAN_PARAMETERS_FW_REV )
    {
        pxAPs->nbr = 0;

        sprintf( (char*)pxObj->RxTxData,"F0=2\r" );

        sSendLen = pxObj->fops.IO_Send( pxObj->RxTxData, strlen((char*)pxObj->RxTxData), pxObj->Timeout );

        if( sSendLen == 5 )
        {
            do
            {
                sRecvLen = pxObj->fops.IO_Receive( pxObj->RxTxData, ISM43340_WIFI_DATA_SIZE, pxObj->Timeout );

                if( (sRecvLen > 0) && (sRecvLen < ISM43340_WIFI_DATA_SIZE) )
                {
                    *( pxObj->RxTxData + sRecvLen ) = 0;

                    if( strstr((char *)pxObj->RxTxData, AT_OK_STRING) )
                    {
                        UNLOCK_WIFI();
                        return ISM43340_WIFI_STATUS_OK;
                    }
                    else if( strstr((char *)pxObj->RxTxData, AT_ERROR_STRING) )
                    {
                        UNLOCK_WIFI();
                        return ISM43340_WIFI_STATUS_UNEXPECTED_CLOSED_SOCKET;
                    }
                }
                if( sRecvLen == ISM43340_WIFI_ERROR_STUFFING_FOREVER )
                {
                    UNLOCK_WIFI();
                    return ISM43340_WIFI_STATUS_MODULE_CRASH;
                }

                if( pxAPs->nbr < ISM43340_WIFI_MAX_DETECTED_AP )
                {
                    prvAT_ParseSingleAP( (char *)pxObj->RxTxData, &(pxAPs->AP[pxAPs->nbr]) );
                    pxAPs->nbr++;
                }

                sprintf( (char*)pxObj->RxTxData,"MR\r" );

                sSendLen = pxObj->fops.IO_Send( pxObj->RxTxData, strlen( (char*)pxObj->RxTxData ), pxObj->Timeout );
            } while ( sSendLen == 3 );
        }

        UNLOCK_WIFI();
        return ISM43340_WIFI_STATUS_IO_ERROR;
    }
    else
    {
        sprintf( (char *)pxObj->RxTxData, "F0\r" );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
        if( xRet == ISM43340_WIFI_STATUS_OK )
        {
            prvAT_ParseAP( (char *)pxObj->RxTxData, pxAPs );
        }
        UNLOCK_WIFI();
        return xRet;
    }
}

/**
  * @brief  Join an Access point.
  * @param  pxObj: pointer to module handle
  * @param  pcSSID: the access point id.
  * @param  pcPassword: the Access point password.
  * @param  xSecType: Security type.
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_Connect( ISM43340_WIFIObject_t *pxObj, const char* pcSSID,
                                         const char* pcPassword,
                                         ISM43340_WIFI_SecurityType_t xSecType )
{
    ISM43340_WIFI_Status_t xRet;
    ISM43340_WIFI_NetworkAutoConnect_t auto_mode = ISM43340_WIFI_AUTO_JOIN_RECONNECT;

    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"C1=%s\r", pcSSID );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );
    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"C2=%s\r", pcPassword );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );

        if( xRet == ISM43340_WIFI_STATUS_OK )
        {
            pxObj->Security = xSecType;
            sprintf( (char*)pxObj->RxTxData,"C3=%d\r", (uint8_t)xSecType );
            pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData);
            xRet = prvAT_ExecuteCommand( pxObj );

            if( xRet == ISM43340_WIFI_STATUS_OK )
            {
                sprintf( (char*)pxObj->RxTxData,"C0\r" );
                pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                xRet = prvAT_ExecuteCommand( pxObj );
                if( xRet == ISM43340_WIFI_STATUS_OK )
                {
                    sprintf( (char*)pxObj->RxTxData,"CC=%d\r", (uint8_t)auto_mode );
                    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                    xRet = prvAT_ExecuteCommand( pxObj );
                    pxObj->NetSettings.IsConnected = 1;
                }
            }
        }
    }
    UNLOCK_WIFI();
    return xRet;
}

/**
  * @brief  Check RSSI.
  * @param  pxObj: pointer to module handle
  * @retval Operation Status.
  */
int32_t ISM43340_WIFI_GetRssi( ISM43340_WIFIObject_t *pxObj )
{
    ISM43340_WIFI_Status_t xRet ;
    LOCK_WIFI();
    int32_t slRssi = 0;

    sprintf( (char*)pxObj->RxTxData,"CR\r" );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );
    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        prvAT_ParseRssi( (char *)pxObj->RxTxData, &slRssi );
    }
    UNLOCK_WIFI();
    return slRssi;
}

/**
  * @brief  Check whether the module is connected to an access point.
  * @param  pxObj: pointer to module handle
  * @retval Operation Status.
  */
uint8_t ISM43340_WIFI_IsConnected( ISM43340_WIFIObject_t *pxObj )
{
    ISM43340_WIFI_Status_t xRet ;
    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"CS\r" );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );
    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        prvAT_ParseIsConnected( (char *)pxObj->RxTxData, &(pxObj->NetSettings.IsConnected) );
    }
    UNLOCK_WIFI();
    return pxObj->NetSettings.IsConnected;
}
/**
  * @brief  Disconnect from a network.
  * @param  pxObj: pointer to module handle
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_Disconnect( ISM43340_WIFIObject_t *pxObj )
{
    ISM43340_WIFI_Status_t xRet;

    LOCK_WIFI();
    sprintf( (char*)pxObj->RxTxData,"CD\r" );

    ISM43340_WIFI_SetTimeout( pxObj, 1000 );// don't wait for disconnect too much.

    xRet = prvAT_ExecuteCommand( pxObj );
    UNLOCK_WIFI();
    return  xRet;
}
/**
  * @brief  Return network settings.
  * @param  pxObj: pointer to module handle
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_GetNetworkSettings( ISM43340_WIFIObject_t *pxObj )
{
    ISM43340_WIFI_Status_t xRet;

    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"C?\r" );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );

    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        prvAT_ParseConnSettings( (char *)pxObj->RxTxData, &pxObj->NetSettings );
    }

    UNLOCK_WIFI();
    return xRet;
}

/**
  * @brief  Configure and activate SoftAP.
  * @param  pxObj: pointer to module handle
  * @param  pxApConfig : Pointer to AP config structure.
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_ActivateAP( ISM43340_WIFIObject_t *pxObj, ISM43340_WIFI_APConfig_t *pxApConfig )
{
    ISM43340_WIFI_Status_t xRet;

    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"AS=0,%s\r", pxApConfig->SSID );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData  );
    xRet = prvAT_ExecuteCommand( pxObj );
    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"A1=%c\r", (int)pxApConfig->Security + '0' );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
        if( xRet == ISM43340_WIFI_STATUS_OK )
        {
            sprintf( (char*)pxObj->RxTxData,"A2=%s\r", pxApConfig->Pass );
            pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
            xRet = prvAT_ExecuteCommand( pxObj );
            if( xRet == ISM43340_WIFI_STATUS_OK )
            {
                sprintf( (char*)pxObj->RxTxData,"AC=%d\r", pxApConfig->Channel );
                pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                xRet = prvAT_ExecuteCommand( pxObj );
                if( xRet == ISM43340_WIFI_STATUS_OK )
                {
                    sprintf( (char*)pxObj->RxTxData,"AT=%d\r", pxApConfig->MaxConnections );
                    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                    xRet = prvAT_ExecuteCommand( pxObj );
                    if( xRet == ISM43340_WIFI_STATUS_OK )
                    {
                        sprintf( (char*)pxObj->RxTxData,"A0\r" );
                        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                        xRet = prvAT_ExecuteCommand( pxObj );
                        if( xRet == ISM43340_WIFI_STATUS_OK )
                        {
                            if( strstr((char *)pxObj->RxTxData, "[AP     ]") )
                            {
                                xRet = ISM43340_WIFI_STATUS_OK;
                            }
                        }
                    }
                }
            }
        }
    }
    UNLOCK_WIFI();
    return xRet;
}

/**
  * @brief  Return the MAC address of the ES module.
  * @param  pxObj: pointer to module handle
  * @param  pucMac: pointer to the MAC address array.
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_GetMACAddress(ISM43340_WIFIObject_t *pxObj, uint8_t *pucMac)
{
    ISM43340_WIFI_Status_t xRet ;
    char *pcPtr;
    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"Z5\r" );
    xRet = prvAT_ExecuteCommand( pxObj );
    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        pcPtr = strtok( (char *)(pxObj->RxTxData + 2), "\r\n" );
        prvParseMAC( pcPtr, pucMac );
    }
    UNLOCK_WIFI();
    return xRet;
}

/**
  * @brief  Ping an IP address.
  * @param  pxObj: pointer to module handle
  * @param  pucAddress: pointer IP address
  * @param  usCount: ping retries
  * @param  usIintervalMs: ping timeout
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_Ping( ISM43340_WIFIObject_t *pxObj, uint8_t *pucAddress, uint16_t usCount, uint16_t usIintervalMs )
{
    ISM43340_WIFI_Status_t xRet;
    uint8_t pucResponseIpAddress[4];
    int16_t sValuesRead = 0, sResponseStart = 0;
    int sRtt;
    uint16_t usResponsesParsed = 0;

    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"T1=%d.%d.%d.%d\r", pucAddress[0],pucAddress[1], pucAddress[2],pucAddress[3] );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );
    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"T2=%d\r", usCount );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
        if( xRet == ISM43340_WIFI_STATUS_OK )
        {
            sprintf( (char*)pxObj->RxTxData,"T3=%d\r", usIintervalMs );
            pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
            xRet = prvAT_ExecuteCommand( pxObj );
            if( xRet == ISM43340_WIFI_STATUS_OK )
            {
                sprintf( (char*)pxObj->RxTxData,"T0=\r" );
                pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                xRet = prvAT_ExecuteCommand( pxObj );
                if( xRet == ISM43340_WIFI_STATUS_OK )
                {
                        /* If the T0 command is successfully executed, the Inventek module
                        * returns one of the following:
                        *
                        * Success - \r\nIP0.IP1.IP2.IP3,RTT\r\nOK\r\n>
                        * Timeout - \r\nIP0.IP1.IP2.IP3,Timeout\r\nOK\r\n>
                        *
                        * Where IP0..IP3 are the octacts of the IP address pinged and RTT is
                        * the round trip time.
                        *
                        * Example success response - \r\n8.8.8.8,48\r\nOK\r\n>
                        * Example timeout response - \r\n192.168.1.1,Timeout\r\nOK\r\n>
                        *
                        * The "\r\nIP0.IP1.IP2.IP3,RTT" part is repeated in the response
                        * the number of ping count times (specified with the T2 command).
                        *
                        * The following check tries to read the 4 IP octacts and the RTT
                        * value from the response - if we are able to successfully read all
                        * the 5 values (i.e. sscanf returns 5), it is a success response. We
                        * will not be able to read the RTT value in case of timeout as sscanf
                        * will not be able to parse "Timeout" as integer. As a result,
                        * valuesRead will not be 5 and it will be detected as timeout.
                        */
                        /* Assume timeout unless we find a successful response. */
                        xRet = ISM43340_WIFI_STATUS_TIMEOUT;
                        do
                        {
                            /* Parse the first response. */
                            sValuesRead = sscanf( (char*)&( pxObj->RxTxData[sResponseStart] ),
                                           "\r\n%hhu.%hhu.%hhu.%hhu,%d",
                                           &pucResponseIpAddress[0],
                                           &pucResponseIpAddress[1],
                                           &pucResponseIpAddress[2],
                                           &pucResponseIpAddress[3],
                                           &sRtt );

                            if( sValuesRead == 5 &&
                                pucResponseIpAddress[0] == pucAddress[0] &&
                                pucResponseIpAddress[1] == pucAddress[1] &&
                                pucResponseIpAddress[2] == pucAddress[2] &&
                                pucResponseIpAddress[3] == pucAddress[3] )
                            {
                                /* We found a successful ping response and so we can stop. */
                                xRet = ISM43340_WIFI_STATUS_OK;
                                break;
                            }
                            else
                            {
                                /* Move past the \r at the beginning of the current response so
                                * that the loop below gets to the next \r which marks the start
                                * of the next response. */
                                sResponseStart++;

                                /* Current ping response was not a successful ping - move to the
                                * beginning of the next response. */
                                while( pxObj->RxTxData[sResponseStart] != '\0' && pxObj->RxTxData[sResponseStart] != '\r' )
                                {
                                    sResponseStart++;
                                }
                            }
                            usResponsesParsed++;
                        } while( usResponsesParsed < usCount );
                    }
            }
        }
    }
    UNLOCK_WIFI();
    return xRet;
}

/**
  * @brief  DNS Lookup to get IP address .
  * @param  pxObj: pointer to module handle
  * @param  pcUrl: Domain Name.
  * @param  pucIpAddress: IP address.
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_DNS_LookUp( ISM43340_WIFIObject_t *pxObj, const char *pcUrl, uint8_t *pucIpAddress )
{
    ISM43340_WIFI_Status_t xRet;
    char *pcPtr;

    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"D0=%s\r", pcUrl );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );

    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        pcPtr = strtok( (char *)pxObj->RxTxData + 2, "\r" );
        prvParseIP( pcPtr, pucIpAddress );
    }
    UNLOCK_WIFI();
    return xRet;
}


/**
  * @brief  Configure and Start a Client connection.
  * @param  pxObj: pointer to module handle
  * @param  pxConn: pointer to the connection structure
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_StartClientConnection( ISM43340_WIFIObject_t *pxObj, ISM43340_WIFI_Conn_t *pxConn )
{
    ISM43340_WIFI_Status_t xRet = ISM43340_WIFI_STATUS_OK;

    if( pxConn->RemotePort == 0 )
    {
        return ISM43340_WIFI_STATUS_ERROR;
    }

    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"P0=%d\r", pxConn->Number );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );

    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"P1=%d\r", pxConn->Type );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
    }

    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"P2=%d\r", pxConn->LocalPort );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
    }

    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"P4=%d\r", pxConn->RemotePort );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
    }

    if( ( xRet == ISM43340_WIFI_STATUS_OK ) && ( ( pxConn->Type == ISM43340_WIFI_TCP_CONNECTION ) || ( pxConn->Type == ISM43340_WIFI_TCP_SSL_CONNECTION ) ) )
    {
        sprintf( (char*)pxObj->RxTxData,"P3=%d.%d.%d.%d\r", pxConn->RemoteIP[0],pxConn->RemoteIP[1],
            pxConn->RemoteIP[2],pxConn->RemoteIP[3] );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
    }

    if( ( xRet == ISM43340_WIFI_STATUS_OK ) && ( pxConn->Type == ISM43340_WIFI_TCP_SSL_CONNECTION ) )
    {
        sprintf( (char*)pxObj->RxTxData,"P9=2\r" );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
    }

    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"P6=1\r" );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
    }

    UNLOCK_WIFI();
    return xRet;
}


/**
  * @brief  Stop Client connection.
  * @param  pxObj: pointer to module handle
  * @param  pxConn: pointer to the connection structure
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_StopClientConnection( ISM43340_WIFIObject_t *pxObj, ISM43340_WIFI_Conn_t *pxConn )
{
    ISM43340_WIFI_Status_t xRet;

    LOCK_WIFI();

    sprintf( (char*)pxObj->RxTxData,"P0=%d\r", pxConn->Number );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );

    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"P6=0\r" );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
    }
    UNLOCK_WIFI();
    return xRet;
}

/**
  * @brief  Configure and Start a Server.
  * @param  pxObj: pointer to module handle
  * @param  pxConn: pointer to the connection structure
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_StartServerSingleConn( ISM43340_WIFIObject_t *pxObj, ISM43340_WIFI_Conn_t *pxConn )
{
    ISM43340_WIFI_Status_t xRet = ISM43340_WIFI_STATUS_OK;

    LOCK_WIFI();
    
    sprintf( (char*)pxObj->RxTxData,"P0=%d\r", pxConn->Number );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );
    if( xRet != ISM43340_WIFI_STATUS_OK )
    {
        UNLOCK_WIFI();
        return xRet;
    }

    if( ( pxConn->Type != ISM43340_WIFI_UDP_CONNECTION ) && ( pxConn->Type != ISM43340_WIFI_UDP_LITE_CONNECTION ) )
    {
        sprintf( (char*)pxObj->RxTxData,"PK=1,3000\r" );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
    }

    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char*)pxObj->RxTxData,"P1=%d\r", pxConn->Type );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );
        if( xRet == ISM43340_WIFI_STATUS_OK )
        {
            sprintf( (char*)pxObj->RxTxData,"P8=%d\r", pxConn->Backlog );
            pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
            xRet = prvAT_ExecuteCommand( pxObj );
            if( xRet == ISM43340_WIFI_STATUS_OK )
            {
                sprintf( (char*)pxObj->RxTxData,"P2=%d\r", pxConn->LocalPort );
                pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                xRet = prvAT_ExecuteCommand( pxObj );
                if( xRet == ISM43340_WIFI_STATUS_OK )
                {
                    // multi accept mode
                    sprintf( (char*)pxObj->RxTxData,"P5=11\r" );
                    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                    xRet = prvAT_ExecuteCommand( pxObj );
                }
            }
        }
    }
    UNLOCK_WIFI();
    return xRet;
}

/**
  * @brief  Send an amount data over WIFI.
  * @param  pxObj: pointer to module handle
  * @param  ucSocket: number of the socket
  * @param  pucData: pointer to data
  * @param  usReqlen : pointer to the length of the data to be sent
  * @param  pusSentLen : pointer to the length of the sent data
  * @param  ulTimeout : send timeout
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_SendData( ISM43340_WIFIObject_t *pxObj, uint8_t ucSocket, uint8_t *pucData, uint16_t usReqlen , uint16_t *pusSentLen , uint32_t ulTimeout )
{
    ISM43340_WIFI_Status_t xRet = ISM43340_WIFI_STATUS_ERROR;

    LOCK_WIFI();

    if( usReqlen >= ISM43340_WIFI_PAYLOAD_SIZE )
    {
        usReqlen = ISM43340_WIFI_PAYLOAD_SIZE;
    }

    *pusSentLen = usReqlen;
    sprintf( (char *)pxObj->RxTxData,"P0=%d\r", ucSocket );
    pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
    xRet = prvAT_ExecuteCommand( pxObj );
    if( xRet == ISM43340_WIFI_STATUS_OK )
    {
        sprintf( (char *)pxObj->RxTxData,"S2=%lu\r", ulTimeout );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );

        if( xRet == ISM43340_WIFI_STATUS_OK )
        {
            sprintf( (char *)pxObj->RxTxData,"S3=%04d\r", usReqlen );
            pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
            memcpy( pxObj->RxTxData + pxObj->RxTxDataLength, pucData, usReqlen );
            pxObj->RxTxDataLength += usReqlen;
            xRet = prvAT_ExecuteCommand( pxObj );

            if( xRet == ISM43340_WIFI_STATUS_OK )
            {
                if( strstr( (char *)pxObj->RxTxData,"-1\r\n" ) )
                {
                    configPRINTF( ("Send Data detect error %s\n", (char *)pxObj->RxTxData) );
                    xRet = ISM43340_WIFI_STATUS_ERROR;
                }
            }
            else
            {
                configPRINTF( ("Send Data command failed = %d\n", xRet) );
            }
        }
        else
        {
            configPRINTF( ("S2 command failed\n") );
        }
    }
    else
    {
        configPRINTF( ("P0 command failed\n") );
    }

    if( xRet == ISM43340_WIFI_STATUS_ERROR )
    {
        *pusSentLen = 0;
    }

    UNLOCK_WIFI();
    return xRet;
}

/**
  * @brief  Receive an amount data over WIFI.
  * @param  pxObj: pointer to module handle
  * @param  ucSocket: number of the socket
  * @param  pucData: pointer to data
  * @param  usReqlen : pointer to the length of the data to be received
  * @param  pusReceivedlen : pointer to the length of the received data
  * @param  ulTimeout : receive timeout
  * @retval Operation Status.
  */
ISM43340_WIFI_Status_t ISM43340_WIFI_ReceiveData( ISM43340_WIFIObject_t *pxObj, uint8_t ucSocket, uint8_t *pucData, uint16_t usReqlen, uint16_t *pusReceivedlen, uint32_t ulTimeout )
{
    ISM43340_WIFI_Status_t xRet = ISM43340_WIFI_STATUS_ERROR;

    LOCK_WIFI();

    if( usReqlen <= ISM43340_WIFI_PAYLOAD_SIZE )
    {
        sprintf( (char*)pxObj->RxTxData,"P0=%d\r", ucSocket );
        pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
        xRet = prvAT_ExecuteCommand( pxObj );

        if( xRet == ISM43340_WIFI_STATUS_OK )
        {
            sprintf( (char*)pxObj->RxTxData,"R1=%d\r", usReqlen );
            pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData);
            xRet = prvAT_ExecuteCommand( pxObj );

            if( xRet == ISM43340_WIFI_STATUS_OK )
            {
                sprintf( (char*)pxObj->RxTxData,"R2=%lu\r", ulTimeout );
                pxObj->RxTxDataLength = strlen( (char*)pxObj->RxTxData );
                xRet = prvAT_ExecuteCommand( pxObj );

                if( xRet == ISM43340_WIFI_STATUS_OK )
                {
                    sprintf( (char*)pxObj->RxTxData,"R0\r" );
                    xRet = AT_RequestReceiveData( pxObj, pxObj->RxTxData, (char *)pucData, usReqlen, pusReceivedlen );

                    if( xRet != ISM43340_WIFI_STATUS_OK )
                    {
                        configPRINTF( ("ISM43340_WIFI_ReceiveData failed\n") );
                    }
                }
                else
                {
                    configPRINTF( ("setting timeout failed\n") );
                }
            }
            else
            {
                configPRINTF( ("setting requested len failed\n") );
                *pusReceivedlen = 0;
            }
        }
        else
        {
            configPRINTF( ("setting socket for read failed\n") );
        }
    }

    UNLOCK_WIFI();
    return xRet;
}

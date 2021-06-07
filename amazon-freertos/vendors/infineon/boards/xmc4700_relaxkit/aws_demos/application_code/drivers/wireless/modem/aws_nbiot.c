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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "aws_nbiot.h"
#include "aws_iot_network_config.h"
#include "aws_nbiot_config.h"
#include "iot_secure_sockets.h"

#include "../fifo/fifo.h"
#include "uart_modem.h"
#include "circular_buffer.h"


#if NBIOT_ENABLED

#define PRINT_STATUS_MODEM			0
#define PRINT_SEND_AT_COMMANDS		0

#define PRINT_RX_STATISTICS         0
#define PRINT_TX_STATISTICS         0

#define TRANSPARENT_MODE_EXIT_STRING "+++"


#ifndef LTE_MODEM_MODE
#warning "LTE_MODEM_MODE is not defined! Please specify needed mode of LTE modem at 'aws_nbiot_config.h'. Default mode is set to \"MODEM_MODE_NBIOT\""

#define LTE_MODEM_MODE eMODEM_MODE_NBIOT

#endif /* LTE_MODEM_MODE */


static fifo_t xSsockRcvFifo[NBIOTconfigMAX_SOCKETS];
static SemaphoreHandle_t xReceiveMutex = NULL;
static SemaphoreHandle_t xSslSockSemaphore = NULL;
static SemaphoreHandle_t xModemSemaphore = NULL;

static uint8_t pucExtraDataBuffer[ 256 ];
static CircularBuf_t xRecvExtraData =
{
    pucExtraDataBuffer,
    0,
    0,
    sizeof pucExtraDataBuffer,
    false
};

/* Work with context */
static int prvModemContextActivate( int lContextID );
static int prvModemContextDeactivate( int lContextID );
static int prvModemContextDeactivateAll( void );
static int prvModemContextStatus( int lContextID );

/* Work with init modem */
static int prvModemTestAT( void );
static int prvModemErrorCodeResultOn( void );
static int prvModemEchoModeOff( void );
static int prvModemAttach( void );
static int prvModemDeattach( void );
static int prvModemAttachStatus( void );
static int prvModemSignalQuality( void );
static int prvModemNetworkRegistrationStatus( void );
static int prvModemCurrentOperator( void );
static int prvModemPutOnline( void );
static int prvModemPutOffline( void );
static int prvModemSimPinStatus( void );
static int prvModemCheckSim( void );
static int prvModemInfo( void );
static int prvModemSetMode( ModemMode_t xMode );
static int prvModemSetAPN( int lContextID, char *pcApn, char *pcUserName, char *pcPass, int lProtocolType, int lAuthMethod );
static int prvModemInit( int lMode );
static int prvModemConnect( int lContextID, char *pcApn, char *pcUserName, char *pcPass, int lProtocolType, int lAuthMethod );
static void prvModemPrintStatus( void );
static void prvModemClearStatus( void );

static bool  prvCompareTimeval( TickType_t xTime, int lThresholdTick );

static int prvATComSet( int (*func)(), uint32_t ulCount, uint32_t ulTimeout );
static status_t prvAT_Send( char *pcBufPtr, int lLength, int lTimeout );

static int prvAT_RecvData( char *pcBufPtr, int lLineSizeLimit, int lTimeout );
static int prvAT_RecvLine( char *pcBufPtr, int lLineSizeLimit, int lTimeout );
static int prvAT_Recv    ( char *pcBufPtr, int lLineSizeLimit, int lTimeout );

typedef struct
{
	int lCount;
    unsigned char pucValue[MODEM_STATUS_COUNT_LEN][MODEM_STATUS_BUFFER_SIZE];
} ModemStatus_t;

ModemStatus_t xModemStatus;


/**
  * @brief  5V power on for mBUS
  */
void vMBus_5V_On( void )
{
    configPRINTF( ("SWITCHING mBUS 5V ON...\r\n") );
    DIGITAL_IO_SetOutputHigh( &MBUS_PWR_RST );
}

/**
  * @brief  5V power off for mBUS
  */
void vMBus_5V_Off( void )
{
    configPRINTF( ("SWITCHING mBUS 5V OFF...\r\n") );
    DIGITAL_IO_SetOutputLow( &MBUS_PWR_RST );
}

/**
  * @brief  Function turn OFF LTE modem
  * @retval status_t result status
  */
status_t prvNBIOT_xModemTurnOff( void )
{
	int8_t cCount;

	configPRINTF( ( "Turning OFF the LTE modem \r\n" ) );
	/* Try to turn OFF module using PWRKEY Pin */
	/* Pulling down PWRKEY pin (MCU pin set to High because of inverting signal by open-collector transistor in "LTE 2 Click module") */
	vModemPinSetHigh( &BG96_MODEM_PIN_PWRKEY );
	configPRINTF( ( "Waiting for power down procedure complete" ) );
	vTaskDelay( 650 );
	/* Releasing the PWRKEY line*/
	vModemPinSetLow( &BG96_MODEM_PIN_PWRKEY );
	cCount = NBIOT_TIMING_SEC_1/NBIOT_TIMING_MSEC_250 * 10;
	/* Waiting for power down procedure complete. STATUS should change to LOW state*/
	while( ulModemPinGet( &BG96_MODEM_PIN_STATUS ) && cCount )
	{
		vTaskDelay( NBIOT_TIMING_MSEC_250 );
		configPRINT( ( "." ) );
		cCount--;
	}
	configPRINTF( ("\r\n") );
	if( cCount <= 0 )
	{
		configPRINTF( ( "ERROR: Can't switch OFF LTE modem \r\n" ) );
		return eStatus_Fail;
	}
	configPRINTF( ( "LTE modem switched OFF \r\n" ) );
	return eStatus_Success;
}


/**
  * @brief  Function turn ON LTE modem
  * @retval status_t result status
  */
status_t prvNBIOT_xModemTurnOn( void )
{
	int8_t cCount;

    /* Check if modem is powered*/
	if( ulModemPinGet( &BG96_MODEM_PIN_STATUS ) )
	{
		/* Turning OFF the LTE modem */
		if( prvNBIOT_xModemTurnOff() != eStatus_Success )
		{
			return eStatus_Fail;
		}
	}

	configPRINTF( ( "Turning ON LTE modem \r\n" ) );
	/* Try to turn on module using PWRKEY Pin */
	vModemPinSetLow( &BG96_MODEM_PIN_PWRKEY );
	/* Make sure that VBAT is stable before pulling down PWRKEY pin */
	vTaskDelay( 30 );
	/* Pulling down PWRKEY pin (MCU pin set to High because of inverting signal by open-collector transistor in "LTE 2 Click module") */
	vModemPinSetHigh( &BG96_MODEM_PIN_PWRKEY );
	configPRINTF( ( "Waiting for LTE modem power up" ) );
	vTaskDelay( 500 );
	/* Releasing the PWRKEY line*/
	vModemPinSetLow( &BG96_MODEM_PIN_PWRKEY );
	cCount = NBIOT_TIMING_SEC_1/NBIOT_TIMING_MSEC_250 * 15;
	/* Waiting for power down procedure complete*/
	while( !ulModemPinGet( &BG96_MODEM_PIN_STATUS ) && cCount )
	{
		vTaskDelay( NBIOT_TIMING_MSEC_250 );
		configPRINT( ( "." ) );
		cCount--;
	}
	configPRINTF( ("\r\n") );
	if( cCount <= 0 )
	{
		configPRINTF( ( "ERROR: Can't switch ON LTE modem \r\n" ) );
		return eStatus_Fail;
	}
	configPRINTF( ( "LTE modem is turned ON \r\n" ) );
	return eStatus_Success;
}



/**
  * @brief  Function initialize LTE modem
  * @retval bool result status
  */
bool NBIOT_bInit( void )
{
	bool bRet = false;

    /* Create semaphore for modem communication */
	if( xModemSemaphore == NULL )
	{
		xModemSemaphore = xSemaphoreCreateMutex();
	}

    if( xModemSemaphore == NULL )
    {
        return false;
    }
    /* Initialize semaphore. */
    xSemaphoreGive( xModemSemaphore );

    if(xSemaphoreTake( xModemSemaphore, NBIOT_TIMING_SEC_150 ) != pdTRUE)
    {
        return false;
    }

    UART_MODEM_vInit();

	if( prvNBIOT_xModemTurnOn() == eStatus_Success)
	{
		if( prvModemInit(LTE_MODEM_MODE) == NBIOT_ERROR_OK )
		{
			configPRINTF( ( "LTE modem configuration successful. \r\n" ) );
			bRet = true;
		}
		else
		{
			configPRINTF( ( "ERROR: LTE modem module failed to initialize.\r\n" ) );
			bRet = false;
		}
	}
	xSemaphoreGive( xModemSemaphore );
	return bRet;
}


/**
  * @brief  Function deinitialize LTE modem
  * @retval bool result status
  */
bool NBIOT_bDisable( void )
{
	return prvNBIOT_xModemTurnOff() == eStatus_Success ? true : false;
}


/**
  * @brief  Function sends data to modem
  * @param  pcBufPtr pointer to data buffer
  * @param  lLength length data
  * @param  lTimeout timeout to send line
  * @retval status error
  */
static status_t prvAT_Send( char *pcBufPtr, int lLength, int lTimeout )
{
    status_t xErr = eStatus_Success;

#if PRINT_SEND_AT_COMMANDS
    if( lLength < 32)
    {
        configPRINTF( ("AT send: %.*s\r\n", lLength, pcBufPtr) );
    }
    else
    {
        configPRINTF( ("AT send: %.32s ...\r\n", pcBufPtr) );
    }

#endif /* PRINT_SEND_AT_COMMANDS */

    TickType_t xTick = xTaskGetTickCount();

    if( UART_MODEM_lTransmitData( (uint8_t*)pcBufPtr, lLength ) == 0 )
    {
        /* Wait send finished or timeout*/
        while( !prvCompareTimeval( xTick, lTimeout ) && UART_MODEM_bTxIsBusy() )
        {
        	vTaskDelay( 2 );
        }
        xErr = eStatus_Success;
    }
    else
    {
    	xErr = eStatus_Fail;
    }
    return xErr;
}

/**
  * @brief  Function reads data from modem
  * @param  pcBufPtr buffer to read in
  * @param  lLineSizeLimit line size limit
  * @param  lTimeout timeout to read line
  * @retval size of line or negative in case of error
  */
static int prvAT_Recv( char *pcBufPtr, int lLineSizeLimit, int lTimeout )
{
    int lResult = -1;
    int lPos = 0;
    TickType_t xTick;
    size_t xReceivedBytes;
    size_t xPrevRecBytes;
    size_t cCurrRecBytes;

    /* read characters into our string buffer until we get a CR or NL */

    xTick = xTaskGetTickCount();

    if( xSemaphoreTake( xReceiveMutex, lTimeout ) == pdTRUE )
    {
        while( !prvCompareTimeval( xTick, lTimeout ) )
        {
        	/* wait last byte and time pause after it */
            do
            {
                /* Wait next symbol */
                vTaskDelay(2);
                xReceivedBytes = UART_MODEM_usRxDataCount();
                cCurrRecBytes = xReceivedBytes - xPrevRecBytes;
                xPrevRecBytes = xReceivedBytes;
            } while( cCurrRecBytes > 0 );

            lPos = xReceivedBytes;
            if( lPos == 0 )
            {
                continue;
            }

            memset( pcBufPtr, 0, lLineSizeLimit );
            lPos = MIN( xReceivedBytes, lLineSizeLimit );
            xReceivedBytes = UART_MODEM_usReceiveData( (uint8_t*)pcBufPtr, lPos );
            if( xReceivedBytes != lPos )
            {
                lResult = -1;
                break;
            }
            if( ((lPos > 2) && ((pcBufPtr[lPos-2] == '\r') && (pcBufPtr[lPos-1] == '\n'))) ||
                          (strncmp(&pcBufPtr[0], "\r\n> ", sizeof("\r\n> ")) == 0) )
            {
                pcBufPtr[lPos] = 0;
                lResult = lPos;
                break;
            }

            if( lPos == lLineSizeLimit )
            {
                lResult = -1;
                break;
            }
        }
        xSemaphoreGive( xReceiveMutex );
    }

    return lResult;
}

/**
 * @brief  Reads one line from the modem
 * @param  pcBufPtr buffer to read in
 * @param  lLineSizeLimit line size limit
 * @param  lTimeout timeout to read line in ticks
 * @retval size of line or negative in case of error
 *
 * Line in the BG-96 is something between a pair of \r\n characters.
 * This function strips these characters and returns only the contents of the line
 */
static int prvAT_RecvLine( char *pcBufPtr, int lLineSizeLimit, int lTimeout )
{
    int lPos = 0;
    long int lTick = xTaskGetTickCount();

    /* read characters into our string buffer until we get a CR or NL */
    if( xSemaphoreTake(xReceiveMutex, lTimeout) == pdTRUE )
    {
        bool bFirstCrlfEncountered = false;
        while( (xTaskGetTickCount() - lTick) <= lTimeout )
        {
            if( !UART_MODEM_bRxDataAvaliable() )
            {
                vTaskDelay(1);
            }
            while( (UART_MODEM_bRxDataAvaliable()) && (lPos < lLineSizeLimit) )
            {
                UART_MODEM_usReceiveData( (uint8_t*)(pcBufPtr + lPos), 1 );
                lPos++;
                if( lPos >= 2 )
                {
                    if( ((pcBufPtr[lPos - 2] == '>') && (pcBufPtr[lPos - 1] == ' ')) ) /* A special case which can be encountered when we send data */
                    {
                        pcBufPtr[lPos] = 0;
                        xSemaphoreGive( xReceiveMutex );
                        return lPos;
                    }
                    if(((pcBufPtr[lPos - 2] == '\r') && (pcBufPtr[lPos - 1] == '\n')))
                    {
                        if(!bFirstCrlfEncountered) /* We have found the first crlf sequence. Thus we start the actual receiving */
                        {
                            bFirstCrlfEncountered = true;
                            lPos = 0;
                        }
                        else
                        {
                            pcBufPtr[lPos - 2] = 0; /* Strip the last crlf */
                            xSemaphoreGive( xReceiveMutex );
                            return lPos - 2;
                        }
                    }
                    else /* We roll off the buffer to prevent the case when there is too much (garbage?) data before the first crlf */
                    {
                        if( !bFirstCrlfEncountered )
                        {
                        	pcBufPtr[0] = pcBufPtr[1];
                            lPos = 1;
                        } /* Else we do nothing as we've just added data to the buffer */
                    }
                }
            }
        }
        xSemaphoreGive( xReceiveMutex );
        return -1;
    } else {
        /* Semaphore cannot be taken */
        return -2;
    }
}

/**
 * @brief  Reads a specified amount of data from the modem
 * @param  pcBufPtr buffer to read in
 * @param  lLineSizeLimit line size limit
 * @param  lTimeout timeout to read line in ticks
 * @retval size of read data or negative in case of error
 *
 * Reads the specified amount of data without stripping anything.
 * If timeout is reached then the read amount will be less than specified
 * but it will not be considered an error. It is up to the user to check this.
 * The zero-terminator is not added to the data.
 *
 * You should deal with crlfs outside of this function, but if a command returns crlf after the data,
 * it must be read to prevent breaking the further code.
 */
static int prvAT_RecvData( char *pcBufPtr, int lLineSizeLimit, int lTimeout )
{
    int lPos = 0;
    long int lTick = xTaskGetTickCount();

    if( xSemaphoreTake(xReceiveMutex, lTimeout ) == pdTRUE)
    {
        while( ((xTaskGetTickCount() - lTick) <= lTimeout) && (lPos < lLineSizeLimit) )
        {
            if( !UART_MODEM_bRxDataAvaliable() )
            {
                vTaskDelay(1);
            }
            while( (UART_MODEM_bRxDataAvaliable()) && (lPos < lLineSizeLimit) )
            {
                UART_MODEM_usReceiveData( (uint8_t*)(pcBufPtr + lPos), 1 );
                lPos++;
            }
        }
        xSemaphoreGive( xReceiveMutex );
        return lPos;
    }
    else
    {
        return 0;
    }
}

/**
  * @brief  Function parses text for modem answers extraction. Search starts from start position
  * @param  pcText to search in
  * @param  plStart [in][out] start postion
  * @param  lTextLen length parsing data
  * @retval length of the answer found
  */
static int prvParseAnswer( char * pcText, int * plStart, int lTextLen )
{
   int i;

   for (; ((*plStart)<lTextLen) && ((pcText[*plStart] == '\r') || (pcText[*plStart] == '\n')); (*plStart)++)
   {
   }

   if( *plStart == lTextLen )
   {// no more answer is found
        return 0;
   }

   for ( i=*plStart ; (i<lTextLen) && (pcText[i] != '\r') && (pcText[i] != '\n'); i++ )
   {
   }

   return  ( i - (*plStart) );
}

/**
  * @brief  Function looks for usolicited code and stores it in memory
  * @param  pcLine to search for
  * @param  lLength length parsing data
  * @retval unsolicited code found
  */
static uint32_t prvLookForUnsolicited( char * pcLine, int lLength )
{
	int lStart = 0;
	int lLen;
	uint32_t ulRet = 0;

	prvModemClearStatus();
	while( (lLen = prvParseAnswer(pcLine, &lStart, lLength)) > 0 )
	{
		if( strncmp((char*)&pcLine[lStart], "OK", strlen("OK")) != 0 )
		{
			memcpy( &xModemStatus.pucValue[xModemStatus.lCount][0], &pcLine[lStart], lLen );
			xModemStatus.lCount++;
			ulRet = 1;
		}
		lStart += lLen;
	}

	return ulRet;
}

/**
  * @brief  Function compares time for two rtime values against threshold in ticks
  * @param  xTime start time
  * @param  lThresholdTick threshold time
  * @retval nonzero in case of threshold is reached
  */
static bool  prvCompareTimeval( TickType_t xTime, int lThresholdTick )
{
    TickType_t xDiffTick;
    TickType_t xTick;

	xTick = xTaskGetTickCount();

	xDiffTick = xTick - xTime;

	return ( xDiffTick > lThresholdTick );
}

/**
  * @brief  Function used to print modem status
  * @param  none
  * @retval none
  */
static void prvModemPrintStatus( void )
{
#if PRINT_STATUS_MODEM == 1
	uint32_t lCount;

	if( xModemStatus.lCount > 0 )
	{
	    configPRINTF( ( "Modem's unsolicited messages:\r\n") );

        for (lCount = 0; lCount < xModemStatus.lCount; ++lCount)
        {
            configPRINTF( ( "     %s \r\n", &xModemStatus.pucValue[lCount][0]) );
        }
	}
#endif
}

/**
  * @brief  Function used to clear modem status
  * @param  none
  * @retval none
  */
static void prvModemClearStatus( void )
{
	xModemStatus.lCount = 0;
	memset(xModemStatus.pucValue, 0, sizeof(xModemStatus.pucValue));
}

/**
  * @brief  Function find result command
  * @param  line pointer to line
  * @param  length length of line
  * @param  results pointer to array results
  * @param  results_num number of results
  * @retval return position result in line or negative if didn't find result
  */
static int prvFindCommandResult( char * pcLine, int lLength, const char ** ppcResults, int lResultsNum )
{
	int lStart = 0, lLen;
	int i;

	while( (lLen = prvParseAnswer(pcLine, &lStart, lLength)) > 0 )
	{
		for ( i = 0; i < lResultsNum; i++ )
		{
			/* Check for expected result */
			if( (strlen( ppcResults[i]) <= lLen )
				&& (strncmp((char*)pcLine + lStart, ppcResults[i], strlen(ppcResults[i])) == 0) )
			{
				return i;
			}
		}
		lStart += lLen;
	}

	return -1;
}

/**
  * @brief  Function tries to start command and parse results
  * @param  pcCommand pointer to command
  * @param  ppcResults pointer to array of results
  * @param  lResultsNum number of results
  * @param  lTimeout timeout to wait return line
  * @retval nonzero in case of parsable answer and negative in case of error
  */
static int prvPperformCommand(const char *pcCommand, const char **ppcResults, int lResultsNum, int lTimeout)
{
	char pcLine[ MODEM_BUFFER_SIZE ];
	int lRet;
	int lLen;
	uint32_t ulUnsolicitedFound;
	TickType_t xTick;

	int i = 0;
	char pcOut[16] = {0};

	while( (pcCommand[i] != '=') && (pcCommand[i] != '?') && (i != strlen(pcCommand)) )
	{
		pcOut[i] = pcCommand[i];
		i++;
	}

	snprintf( pcLine, sizeof(pcLine)-1, "%s\r\n", pcCommand );

	if( (lRet = prvAT_Send( pcLine, strlen(pcLine), NBIOT_TIMING_SEC_1) ) != eStatus_Success )
	{
		configPRINTF( ( "ERROR: %d: writing to modem \"%s\"\r\n", lRet, pcCommand ) );
		return -1;
	}

	vTaskDelay( 1 );

	xTick = xTaskGetTickCount();

	if( (lLen = prvAT_Recv(pcLine, sizeof(pcLine)-1, lTimeout)) < 0 )
	{
		configPRINTF( ( "ERROR: %d: reading from modem \"%s\"\r\n", lRet, pcCommand ) );
		return -1;
	}

	ulUnsolicitedFound = prvLookForUnsolicited( pcLine, lLen );

	if( ulUnsolicitedFound )
	{
		prvModemPrintStatus();
	}

	lRet = prvFindCommandResult( pcLine, lLen, ppcResults, lResultsNum );

	while( (lRet < 0) && !prvCompareTimeval( xTick, lTimeout ) )
	{
		if( (lLen = prvAT_Recv(pcLine, sizeof(pcLine)-1, NBIOT_TIMING_SEC_1)) > 0 )
		{

			ulUnsolicitedFound = prvLookForUnsolicited( pcLine, lLen );

			if( ulUnsolicitedFound )
			{
				prvModemPrintStatus();
			}

			lRet = prvFindCommandResult( pcLine, lLen, ppcResults, lResultsNum );
		}
	}

	if( lRet == -1 )
	{
		configPRINTF( ( "%s: unknown response..\r\n", pcOut ) );
	}
	else
	{
		configPRINTF( ( "Command \"%s\" is finished \"%s\"\r\n", pcOut, ppcResults[lRet]) );
	}

	return lRet;
}

/**
  * @brief  Function test that modem may response
  * @param  none
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemTestAT( void )
{
	const char * ppcResponses[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "AT", ppcResponses, sizeof(ppcResponses)/sizeof(ppcResponses[0]), NBIOT_TIMING_SEC_1 );
}

/**
  * @brief  Function switch on return modem error code
  * @param  none
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemErrorCodeResultOn( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "AT+CMEE=2", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}

/**
  * @brief  Function switch off modem echo
  * @param  none
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemEchoModeOff( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "ATE0", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}

/**
  * @brief  Function read modem info
  * @param  none
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemInfo( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "ATI", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}


/**
  * @brief  Function get modem mode code
  * @param  ModemMode_t mode
  * @retval char modem mode code
  */
char get_mode_code( ModemMode_t xMode )
{
	switch( xMode )
	{
		case eMODEM_MODE_GSM:
			return MODEM_MODE_GSM_STR;
		case eMODEM_MODE_NBIOT:
			return MODEM_MODE_NBIOT_STR;
		case eMODEM_MODE_CATM1:
			return MODEM_MODE_CATM1_STR;
		default:
			configPRINTF( ( "ERROR: Unknown LTE modem mode: %d \r\n", xMode ) );
			vTaskDelay( 100 );
			configASSERT( xMode < eMODEM_MODES_NUM );
	}
	return eStatus_InvalidArgument;
}

/**
  * @brief  Function set modem in needed mode
  * @param  ModemMode_t mode
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemSetMode( ModemMode_t xMode )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};
	int lRet;

	lRet = prvPperformCommand( "AT+QCFG=\"band\",0000000F,400A0E189F,A0E189F", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );

	switch ( xMode )
	{
		case eMODEM_MODE_GSM:
			if( lRet == 0 )
			{
				lRet = prvPperformCommand( "AT+QCFG=\"nwscanmode\",1", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
			}
			if( lRet == 0 )
			{
				lRet = prvPperformCommand( "AT+QCFG=\"nwscanseq\",010203", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
			}
			break;
		case eMODEM_MODE_NBIOT:
			if( lRet == 0 )
			{
				lRet = prvPperformCommand( "AT+QCFG=\"nwscanmode\",3", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
			}
			if( lRet == 0 )
			{
				lRet = prvPperformCommand( "AT+QCFG=\"iotopmode\",1", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
			}
			if( lRet == 0 )
			{
				lRet = prvPperformCommand( "AT+QCFG=\"nwscanseq\",030201", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
			}
			break;
		case eMODEM_MODE_CATM1:
			if( lRet == 0 )
			{
				lRet = prvPperformCommand( "AT+QCFG=\"nwscanmode\",3", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
			}
			if( lRet == 0 )
			{
				lRet = prvPperformCommand( "AT+QCFG=\"nwscanseq\",020301", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
			}
			break;
		default:
			configPRINTF( ( "Unknown mode: %d \r\n", xMode ) );
			return eStatus_InvalidArgument;
	}
	if( lRet == 0 )
	{
		int lRetryCounter = 30;
		while( lRetryCounter )
		{
			lRet = prvPperformCommand( "AT+COPS?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
			if( lRet == 0 )
			{
				if( xModemStatus.pucValue[0][ strlen( (char*)&xModemStatus.pucValue[0][0] )-1 ] == get_mode_code(xMode) )
				{
					break;
				}
			}
			vTaskDelay( NBIOT_TIMING_SEC_1 );
			lRetryCounter--;
		}
	}
	if( lRet == 0 )
	{
		lRet = prvPperformCommand( "AT+QNWINFO", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
	}

	return lRet;
}

/**
  * @brief  Function attach modem
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int prvModemAttach( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	int lRet = prvPperformCommand( "AT+CGATT?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_30 );

	if( lRet == 0 )
	{
		if( strncmp((char*)&xModemStatus.pucValue[0][0], "+CGATT: 1", strlen("+CGATT: 1") ) == 0 )
		{
			return 0;
		}
		else
		{
			lRet = prvPperformCommand( "AT+CGATT=1", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_100 );
			return 0;
		}
	}
	return -1;
}

/**
  * @brief  Function deattach modem
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
__attribute__((unused))
static int prvModemDeattach( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	int lRet = prvPperformCommand( "AT+CGATT?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_30 );

	if( lRet == 0 )
	{
		if( strncmp((char*)&xModemStatus.pucValue[0][0], "+CGATT: 0", strlen("+CGATT: 0") ) == 0 )
		{
			return 0;
		}
		else
		{
			lRet = prvPperformCommand( "AT+CGATT=0", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_100 );
			return 0;
		}
	}
	return -1;
}

/**
  * @brief  Function read attach modem status
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int prvModemAttachStatus( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	int lRet = prvPperformCommand( "AT+CGATT?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_30 );

	if( lRet == 0 )
	{
		if( strncmp( (char*)&xModemStatus.pucValue[0][0], "+CGATT: 1", strlen("+CGATT: 1") ) == 0 )
		{
			return 0;
		}
	}
	return -1;
}

/**
  * @brief  Function read modem signal quality
  * @param  none
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemSignalQuality( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "AT+CSQ", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}


/**
  * @brief  Function enable modem network registration
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int modem_network_registration_enable( void )
{
    const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

    int lRet = prvPperformCommand( "AT+CREG?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );

    if( lRet == 0 )
    {
        if( (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CREG: 0,1", strlen("+CREG: 0,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CREG: 1,1", strlen("+CREG: 1,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CREG: 2,1", strlen("+CREG: 2,1")) == 0 ) )
        {
            return 0;
        }
        else
        {
            lRet = prvPperformCommand( "AT+CREG=1", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
        }
    }
    return -1;
}

/**
  * @brief  Function read modem network registration status
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int prvModemNetworkRegistrationStatus( void )
{
    const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

    int lRet = prvPperformCommand( "AT+CREG?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );

    if( lRet == 0 )
    {
        if( (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CREG: 0,1", strlen("+CREG: 0,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CREG: 1,1", strlen("+CREG: 1,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CREG: 2,1", strlen("+CREG: 2,1")) == 0 ) )
        {
            return 0;
        }
    }
    return -1;
}

/**
  * @brief  Function enable modem network
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int modem_network_enable( void )
{
    const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

    int lRet = prvPperformCommand("AT+CGREG?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1);

    if( lRet == 0 )
    {
        if( (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CGREG: 0,1", strlen("+CGREG: 0,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CGREG: 1,1", strlen("+CGREG: 1,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CGREG: 2,1", strlen("+CGREG: 2,1")) == 0 ) )
        {
            return 0;
        }
        else
        {
            lRet = prvPperformCommand( "AT+CGREG=1", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
        }
    }
    return -1;
}

/**
  * @brief  Function enable evolved packet system
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int modem_eps_enable( void )
{
    const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

    int lRet = prvPperformCommand("AT+CEREG?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1);

    if( lRet == 0 )
    {
        if( (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CEREG: 0,1", strlen("+CEREG: 0,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CEREG: 1,1", strlen("+CEREG: 1,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CEREG: 2,1", strlen("+CEREG: 2,1")) == 0 ) )
        {
            return 0;
        }
        else
        {
            lRet = prvPperformCommand( "AT+CEREG=1", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
        }
    }
    return -1;
}

/**
  * @brief  Function read modem network status
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int modem_network_status( void )
{
    const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

    int lRet = prvPperformCommand( "AT+CGREG?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );

    if( lRet == 0 )
    {
        if( (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CGREG: 0,1", strlen("+CGREG: 0,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CGREG: 1,1", strlen("+CGREG: 1,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CGREG: 2,1", strlen("+CGREG: 2,1")) == 0 ) )
        {
            return 0;
        }
    }
    return -1;
}

/**
  * @brief  Function read modem network status
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int modem_eps_status( void )
{
    const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

    int lRet = prvPperformCommand( "AT+CEREG?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );

    if(lRet == 0)
    {
        if( (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CEREG: 0,1", strlen("+CEREG: 0,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CEREG: 1,1", strlen("+CEREG: 1,1")) == 0 ) ||
            (strncmp( (char*)&xModemStatus.pucValue[0][0], "+CEREG: 2,1", strlen("+CEREG: 2,1")) == 0 ) )
        {
            return 0;
        }
    }
    return -1;
}

/**
  * @brief  Function read modem current operator name
  * @param  none
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemCurrentOperator( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "AT+COPS?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_100 );
}

/**
  * @brief  Function put modem online
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int prvModemPutOnline( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	int lRet = prvPperformCommand("AT+CFUN?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_20);

	if( lRet == 0)
	{
		if( strncmp( (char*)&xModemStatus.pucValue[0][0], "+CFUN: 1", strlen("+CFUN: 1") ) == 0 )
		{
			return 0;
		}
		else
		{
			lRet = prvPperformCommand( "AT+CFUN=1", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_20 );
		}
	}
	return -1;
}

/**
  * @brief  Function put modem offline
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
__attribute__((unused))
static int prvModemPutOffline( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	int lRet = prvPperformCommand( "AT+CFUN?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_20 );

	if( lRet == 0 )
	{
		if( strncmp( (char*)&xModemStatus.pucValue[0][0], "+CFUN: 0", strlen("+CFUN: 0") ) == 0 )
		{
			return lRet;
		}
		else
		{
			lRet = prvPperformCommand( "AT+CFUN=0,1", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_20 );
		}
	}
	return -1;
}

/**
  * @brief  Function read pin status of SIM card
  * @param  none
  * @retval zero in case of parsable responses and negative in case of error
  */
static int prvModemSimPinStatus( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	int ret = prvPperformCommand( "AT+CPIN?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_5 );

	if(ret == 0)
	{
		if( strncmp( (char*)&xModemStatus.pucValue[0][0], "+CPIN: READY", strlen("+CPIN: READY") ) == 0 )
		{
			return 0;
		}
	}
	return -1;
}

/**
  * @brief  Function check that SIM is initialized
  * @param  none
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemCheckSim( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "AT+CIMI", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}

/**
  * @brief  Function connect modem to APN
  * @param  llContextID the context ID. The range is 1-16.
  * @param  apn pointer to APN addres
  * @param  username pointer to username APN point
  * @param  pass pointer to password APN point
  * @param  protocol_type
  * @param  auth_method
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemSetAPN( int llContextID, char *pcApn, char *pcUserName, char *pcPass, int lProtocolType, int lAuthMethod )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};
	char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];

	snprintf( pcCommand, sizeof(pcCommand)-1, "AT+QICSGP=%d,%d,\"%s\",\"%s\",\"%s\",%d", llContextID, lProtocolType, pcApn, pcUserName, pcPass, lAuthMethod );

	return prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_2 );
}

/**
  * @brief  Function initialize modem
  * @param  lMode modem mode(0 - GSM, 1 - NBIOT)
  * @retval zero in case of nonerror and negative in case of error
  */
static int prvModemInit( int lMode )
{
    /* Create for uart receive */
    if( xReceiveMutex == NULL)
    {
    	xReceiveMutex = xSemaphoreCreateMutex();
    }
    if( xReceiveMutex == NULL )
    {
        return NBIOT_ERROR_MUTEX;
    }
    /* Initialize semaphore. */
    xSemaphoreGive( xReceiveMutex );

    /* Create for ssl socket */
    if( xSslSockSemaphore == NULL )
    {
    	xSslSockSemaphore = xSemaphoreCreateMutex();
    }
    if( xSslSockSemaphore == NULL )
    {
        return NBIOT_ERROR_MUTEX;
    }
    /* Initialize semaphore. */
    xSemaphoreGive( xSslSockSemaphore );

	if( prvATComSet( &prvModemTestAT, 10, NBIOT_TIMING_SEC_1) )
	{
		return NBIOT_ERROR_TEST_AT;
	}

	if( prvATComSet( &prvModemEchoModeOff, 10, NBIOT_TIMING_SEC_1) )
	{
		return NBIOT_ERROR_ECHO_MODE;
	}

	if( prvATComSet( &prvModemErrorCodeResultOn, 10, NBIOT_TIMING_SEC_1) )
	{
		return NBIOT_ERROR_CODE_RESULT;
	}

	if( prvATComSet( &prvModemInfo, 10, NBIOT_TIMING_SEC_1 ) )
	{
		return NBIOT_ERROR_INFO;
	}

	if( prvATComSet( &prvModemSimPinStatus, 5, NBIOT_TIMING_SEC_1 ) )
	{
		return NBIOT_ERROR_SIM_PIN;
	}

	if( prvModemSetMode( lMode ) )
	{
		return NBIOT_ERROR_NETWORK_STATUS;
	}

	if( lMode != eMODEM_MODE_NBIOT )
    {
        if( prvATComSet( &prvModemNetworkRegistrationStatus, 60, NBIOT_TIMING_SEC_1 ) )
        {
            return NBIOT_ERROR_NETWORK_STATUS;
        }

        if( prvATComSet( &modem_network_status, 60, NBIOT_TIMING_SEC_1 ) )
        {
            return NBIOT_ERROR_NETWORK_STATUS;
        }
    }
    else
    {
        if( prvATComSet( &modem_eps_status, 15, NBIOT_TIMING_SEC_1 ) )
        {
            return NBIOT_ERROR_NETWORK_STATUS;
        }
    }

	if( prvATComSet( &prvModemPutOnline, 15, NBIOT_TIMING_SEC_1 ) )
	{
		return NBIOT_ERROR_PUT_ONLINE;
	}

	if( prvATComSet( &prvModemCheckSim, 10, NBIOT_TIMING_SEC_1 ) )
	{
		return NBIOT_ERROR_CHECK_SIM;
	}

	if( prvATComSet( &prvModemSignalQuality, 10, NBIOT_TIMING_SEC_1 ) )
	{
		return NBIOT_ERROR_SIGNAL_QUALITY;
	}

	if( prvATComSet( &prvModemAttach, 30, NBIOT_TIMING_SEC_1 ) )
	{
		return NBIOT_ERROR_ATTACH;
	}

	if( prvATComSet( &prvModemAttachStatus, 30, NBIOT_TIMING_SEC_2 ) )
	{
		return NBIOT_ERROR_ATTACH_STATUS;
	}

    if( lMode != eMODEM_MODE_NBIOT )
    {
        if( prvATComSet( &modem_network_registration_enable, 10, NBIOT_TIMING_SEC_1 ) )
        {
            return NBIOT_ERROR_NETWORK_REGISTER;
        }

        if( prvATComSet( &modem_network_enable, 10, NBIOT_TIMING_SEC_1 ) )
        {
            return NBIOT_ERROR_NETWORK_REGISTER;
        }
    }
    else
    {
        if( prvATComSet( &modem_eps_enable, 10, NBIOT_TIMING_SEC_1 ) )
        {
            return NBIOT_ERROR_NETWORK_REGISTER;
        }
    }

	if( prvATComSet( &prvModemCurrentOperator, 10, NBIOT_TIMING_SEC_1 ) )
	{
		return NBIOT_ERROR_CURRENT_OPERATOR;
	}

	if( prvATComSet( &prvModemSignalQuality, 10, NBIOT_TIMING_SEC_1 ) )
	{
		return NBIOT_ERROR_SIGNAL_QUALITY;
	}

#if USE_APN_SETTINGS
	return prvModemConnect( NBIOT_CONTEXT_ID, NBIOT_APN_NAME, NBIOT_APN_USER, NBIOT_APN_PWD, NBIOT_PROTOCOL_TYPE, NBIOT_AUTH_METHOD );
#endif /* USE_APN_SETTINGS */

	return NBIOT_ERROR_OK;
}

/**
  * @brief  Function connect modem to APN and adjust context
  * @param  lContextID the context ID. The range is 1-16.
  * @param  pcApn pointer to APN addres
  * @param  pcUserName pointer to username APN point
  * @param  pcPass pointer to password APN point
  * @param  lProtocolType protocol type
  * @param  lAuthMethod authentication method
  * @retval zero in case of nonerror and negative in case of error
  */
__attribute__((unused))
static int prvModemConnect( int lContextID, char *pcApn, char *pcUserName, char *pcPass, int lProtocolType, int lAuthMethod )
{
	if(prvModemContextDeactivateAll() != NBIOT_ERROR_OK)
	{
		return NBIOT_ERROR_CONTEXT_DEACTIVATE;
	}

	if(prvModemSetAPN(lContextID, pcApn, pcUserName, pcPass, lProtocolType, lAuthMethod) != NBIOT_ERROR_OK)
	{
		return NBIOT_ERROR_SET_APN;
	}

	if(prvModemContextActivate(lContextID) != NBIOT_ERROR_OK)
	{
		return NBIOT_ERROR_CONTEXT_ACTIVATE;
	}

	if(prvModemContextStatus(lContextID) != NBIOT_ERROR_OK)
	{
		return NBIOT_ERROR_CONTEXT_STATUS;
	}

	return NBIOT_ERROR_OK;
}

/**
  * @brief  Function periodic function call
  * @param  lFunc pointer to call function
  * @param  ulCount max number of call function
  * @param  ulTimeout timeout between calls
  * @retval zero in case of nonerror and negative in case of error
  */
static int prvATComSet( int (*lFunc)(), uint32_t ulCount, uint32_t ulTimeout )
{
	while( (lFunc() != 0) && ulCount )
	{
		ulCount--;
		vTaskDelay(ulTimeout);
	}
	if( !ulCount )
	{
		return -1;
	}
	return NBIOT_ERROR_OK;
}

/**
  * @brief  Function activate context modem
  * @param  lContextID the context ID. The range is 1-16.
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemContextActivate( int lContextID )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};
	char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];

	snprintf( pcCommand, sizeof(pcCommand), "AT+QIACT=%d", lContextID );

	return prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_100 );
}

/**
  * @brief  Function deactivate context modem
  * @param  lContextID the context ID. The range is 1-16.
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemContextDeactivate( int lContextID )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};
	char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];
	snprintf( pcCommand, sizeof(pcCommand), "AT+QIDEACT=%d", lContextID );

	if( prvModemContextStatus( lContextID ) == NBIOT_ERROR_OK )
	{
		return prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_60 );
	}

	return NBIOT_ERROR_OK;
}

/**
  * @brief  Function deactivate all context modem
  * @param  none
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
static int prvModemContextDeactivateAll( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};
	char pcCommand[NBIOT_MAX_SIZE_COMMAND];
	char pcNum[2];
	int lContextID[16];
	int lCount;
	int lRet;
	int i, k;

	lRet = prvPperformCommand( "AT+QIACT?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_100 );

	if( lRet == NBIOT_ERROR_OK )
	{
		lCount = xModemStatus.lCount;

		for ( i = 0; i < lCount; i++ )
		{
			k = 0;
			memset( pcNum, 0, sizeof(pcNum) );

			while( (xModemStatus.pucValue[i][strlen("+QIACT: ") + k] != ',') && (k < sizeof(pcNum)) )
			{
				pcNum[k] = xModemStatus.pucValue[i][strlen("+QIACT: ") + k];
				k++;
			}
			lContextID[i] = atoi(pcNum);
		}

		for ( i = 0; i < lCount; i++ )
		{
			memset( pcCommand, 0, sizeof(pcCommand) );

			snprintf( pcCommand, sizeof(pcCommand), "AT+QIDEACT=%d", lContextID[i] );

			k = 5;
			while( (prvPperformCommand(pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_60) != 0) && k )
			{
				k--;
				vTaskDelay( NBIOT_TIMING_SEC_1 );
			}
			if( k == 0 )
			{
				return -1;
			}
		}
	}

	return lRet;
}

/**
  * @brief  Function read activate context modem status
  * @param  lContextID the context ID. The range is 1-16.
  * @retval zero in case of parsable responses and negative in case of error
  */
static int prvModemContextStatus( int lContextID )
{
	int i;
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};
	char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];
	snprintf( pcCommand, sizeof(pcCommand), "%d,1", lContextID );

	int ret = prvPperformCommand( "AT+QIACT?", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_100 );

	if( ret == NBIOT_ERROR_OK )
	{
		for ( i = 0; i < xModemStatus.lCount; i++ )
		{
			if( strncmp((char*)&xModemStatus.pucValue[i][strlen("+QIACT: ")], pcCommand, strlen(pcCommand)) == 0 )
			{
				return NBIOT_ERROR_OK;
			}
		}
	}
	return -1;
}

/**
  * @brief  Function get ip from hostname
  * @param  lContextID the context ID. The range is 1-16.
  * @param  pcName pointer to hostname.
  * @param  pcIp pointer to IP.
  * @retval zero in case of parsable responses and negative in case of error
  */
int NBIOT_lGetIpFromName( int llContextID, const char *pcName, char *pcIp )
{
	const char * ppcResponces[] = {"+QIURC: \"pdpdeact\"", "+QIURC:", "+CME ERROR:", "ERROR"};
	char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];

	if( xSemaphoreTake( xModemSemaphore, NBIOT_TIMING_SEC_150 ) != pdTRUE )
	{
		return NBIOT_ERROR_MUTEX;
	}
	snprintf( pcCommand, sizeof(pcCommand), "AT+QIDNSGIP=%d,\"%s\"", llContextID, pcName );

	int ret = prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_60 );

	if( ret == 1 )
	{
		strncpy( pcIp, (char*)&xModemStatus.pucValue[1][strlen("+QIURC: \"dnsgip\",\"")],
				strlen((char*)&xModemStatus.pucValue[1][0])-strlen("+QIURC: \"dnsgip\",\"")-1 );

		ret = NBIOT_ERROR_OK;
	}
	xSemaphoreGive( xModemSemaphore );
	return ret;
}

/**
  * @brief  Function configuration SSL connection
  * @param  lSslCtxID index of the SSL context. The range is 0-5.
  * @param  lSslVersion SSL Version. (0 - SSL3.0; 1 - TLS1.0; 2 - TLS1.1; 3 - TLS1.2; 4 - All)
  * @param  lSecLevel the authentication mode. (0 - No authentication; 1 - Manage server authentication; 2 - Manage server and client authentication)
  * @param  pcCaCertPath pointer to the path of the trusted CA certificate.
  * @param  pcClientCertPath pointer to the path of client certificate.
  * @param  pcClientKeyPath pointer to the path of client private key.
  * @retval zero in case of nonerror and negative in case of error
  */
int NBIOT_lConfigSsl( int lSslCtxID, int lSslVersion, int lSecLevel, char *pcCaCertPath, char *pcClientCertPath, char *pcClientKeyPath )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};
	char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];
	int lRet;

	snprintf( pcCommand, sizeof(pcCommand), "AT+QSSLCFG=\"sslversion\",%d,%d", lSslCtxID, lSslVersion );

	lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );

	if(lRet == NBIOT_ERROR_OK)
	{
		memset( pcCommand, 0, sizeof(pcCommand) );

		snprintf( pcCommand, sizeof(pcCommand), "AT+QSSLCFG=\"ciphersuite\",%d,0X0035", lSslCtxID );

		lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
	}

	if( lRet == NBIOT_ERROR_OK )
	{
		memset( pcCommand, 0, sizeof(pcCommand) );

		snprintf( pcCommand, sizeof(pcCommand), "AT+QSSLCFG=\"seclevel\",%d,%d", lSslCtxID, lSecLevel );

		lRet = prvPperformCommand(pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
	}

	if( (lRet == NBIOT_ERROR_OK) && (pcCaCertPath != NULL) )
	{
		memset( pcCommand, 0, sizeof(pcCommand) );

		snprintf( pcCommand, sizeof(pcCommand), "AT+QSSLCFG=\"cacert\",%d,\"%s\"", lSslCtxID, pcCaCertPath );

		lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
	}

	if( (lRet == NBIOT_ERROR_OK) && (pcClientCertPath != NULL) )
	{
		memset( pcCommand, 0, sizeof(pcCommand) );

		snprintf( pcCommand, sizeof(pcCommand), "AT+QSSLCFG=\"clientcert\",%d,\"%s\"", lSslCtxID, pcClientCertPath );

		lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
	}

	if( (lRet == NBIOT_ERROR_OK) && (pcClientKeyPath != NULL) )
	{
		memset( pcCommand, 0, sizeof(pcCommand) );

		snprintf( pcCommand, sizeof(pcCommand), "AT+QSSLCFG=\"clientkey\",%d,\"%s\"", lSslCtxID, pcClientKeyPath );

		lRet = prvPperformCommand(pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
	}

	return lRet;
}

/**
  * @brief  Function open socket SSL connection
  * @param  lPdpCtxID PDP context ID. The range is 1-16.
  * @param  lSslCtxID index of the SSL context. The range is 0-5.
  * @param  lSocket number of socket. The range is 0-11.
  * @param  pcServerAddres pointer to server address.
  * @param  lRemotePort remote port.
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
int NBIOT_lSslOpenSocket( int lPdpCtxID, int lSslCtxID, int lSocket, char *pcServerAddres, int lRemotePort )
{
	char pcResp[ 32 ] = { 0 };
	snprintf( pcResp, sizeof(pcResp), "+QSSLOPEN: %d,0", lSocket );

	const char * ppcResponces[] = {pcResp, "+CME ERROR:", "ERROR"};
	int lRet = 0;
	char pcCommand[NBIOT_MAX_SIZE_COMMAND];

	snprintf(pcCommand, sizeof(pcCommand), "AT+QSSLOPEN=%d,%d,%d,\"%s\",%d,0", lPdpCtxID, lSslCtxID, lSocket, pcServerAddres, lRemotePort);

	lRet = prvPperformCommand(pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_150);

	return lRet;
}

/**
  * @brief  Function read status open socket SSL connection
  * @param  lSocket number of socket. The range is 0-11.
  * @retval zero if this socket is free and negative if socket busy
  */
int NBIOT_lSslSocketState( int lSocket )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	char command[ NBIOT_MAX_SIZE_COMMAND ];
	int ret;

	snprintf( command, sizeof(command), "AT+QSSLSTATE=%d",lSocket );

	ret = prvPperformCommand( command, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_10 );

	if(ret == NBIOT_ERROR_OK)
	{
		if( xModemStatus.lCount )
		{
			return -1;
		}
	}

	return NBIOT_ERROR_OK;
}

/**
  * @brief  Function send data to socket SSL connection
  * @param  lSocket number of socket. The range is 0-11.
  * @param  pucData pointer to data.
  * @param  lLength length of data.
  * @retval length of sent data and negative if error
  */
int NBIOT_lSslSendSocket( int lSocket, unsigned char *pucData, int lLength )
{
	if( lLength > MAX_PKT_LEN )
	{
		return -1;
	}

	const char * ppcResponces[] = {"SEND OK", "SEND FAIL", "ERROR"};
	int lRet = 0;
	int lLen;
	char pcCommand[ NBIOT_MAX_SIZE_COMMAND ] = { 0 };
	uint32_t ulUnsolicitedFound;

	snprintf( pcCommand, sizeof(pcCommand)-1, "AT+QSSLSEND=%d,%d\r\n", lSocket, lLength );

	if( (lRet = prvAT_Send( pcCommand, strlen(pcCommand), NBIOT_TIMING_SEC_1)) != eStatus_Success )
	{
		configPRINTF( ( "ERROR: %d: writing to modem \"%s\"\r\n", lRet, pcCommand ) );
		return -1;
	}

	if( (lRet = prvAT_Recv( pcCommand, sizeof(pcCommand)-1, NBIOT_TIMING_SEC_1 ) ) < 0 )
	{
		configPRINTF( ( "ERROR: %d: reading from modem \"%s\"\r\n", lRet, pcCommand ) );
		return -1;
	}

	if(strncmp(pcCommand, "\r\n> ", sizeof("\r\n> ")) == 0)
	{
		if( (lRet = prvAT_Send( (char*)pucData, lLength, NBIOT_TIMING_SEC_1) ) != eStatus_Success )
		{
			configPRINTF( ( "ERROR: %d: writing to modem \"%s\"\r\n", lRet, pcCommand ) );
			return -1;
		}

		if( (lLen = prvAT_Recv( pcCommand, sizeof(pcCommand)-1, NBIOT_TIMING_SEC_1 ) ) < 0 )
		{
			configPRINTF( ( "ERROR: %d: reading from modem \"%s\"\r\n", lRet, pcCommand ) );
			return -1;
		}

		ulUnsolicitedFound = prvLookForUnsolicited( pcCommand, lLen );

		if( ulUnsolicitedFound )
		{
			prvModemPrintStatus();
		}

		lRet = prvFindCommandResult( pcCommand, lLen, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]) );

		if(lRet == 0)
		{
			return lLength;
		}
	}

	return -1;
}

/**
  * @brief  Function receive data from socket SSL connection
  * @param  lSocket number of socket. The range is 0-11.
  * @param  lMaxLength max length which can receive.
  * @param  xTimeoutTicks timeout to receive in ticks.
  * @retval length of receive data and zero if nothing receive
  */
static int prvNbiot_SslNextRecvSocket( int lSocket, int lMaxLength, TickType_t xTimeoutTicks )
{
    char pcBuffer[ MAX_PKT_LEN ];
    int lRet = NBIOT_ERROR_OK;
    int lRecvBytes;
    const char * ppcResp[] = { "OK", "+QSSLURC: \"recv\"", "+QSSLURC: \"closed\"", "ERROR" };
    char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];
    TickType_t xTick = xTaskGetTickCount();
    int lLenRcvData = 0;

    snprintf( pcCommand, sizeof(pcCommand), "AT+QSSLRECV=%d,%d\r\n", lSocket, lMaxLength );
    if( prvAT_Send( pcCommand, strlen(pcCommand), xTimeoutTicks - ( xTaskGetTickCount() - xTick ) ) != eStatus_Success )
    {
        configPRINTF( ( "ERROR: %d: writing to modem \"%s\"\r\n", lRet, pcCommand ) );
        return -1;
    }

    vTaskDelay( 3 );

    memset( pcBuffer, 0, sizeof(pcBuffer) );
    if( ( lRecvBytes = prvAT_RecvLine( pcBuffer, sizeof(pcBuffer) - 1, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) ) ) < 0 )
    {
        configPRINTF( ( "ERROR: %d %d: reading from modem \"%s\",\r\n", lRecvBytes, sizeof(pcBuffer), pcBuffer ) );
        return -1;
    }

    if( memcmp( pcBuffer, ppcResp[ 1 ], strlen( ppcResp[ 1 ] ) ) == 0 ) /* We have got URC that data has been received so we just ignore it */
    {
        vTaskDelay( 3 );

        if( ( lRecvBytes = prvAT_RecvLine( pcBuffer, sizeof(pcBuffer) - 1, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) ) ) < 0 )
        {
            configPRINTF( ( "ERROR: %d %d: reading from modem \"%s\",\r\n", lRecvBytes, sizeof(pcBuffer), pcBuffer ) );
            return -1;
        }
    }
    else if( memcmp( pcBuffer, ppcResp[ 3 ], strlen( ppcResp[ 3 ] ) ) == 0 ) /* ERROR, connection does not exist */
    {
        configPRINTF( ( "ERROR: nbiot_tcp_recv_socket_next, no connection,\r\n", lRecvBytes, sizeof(pcBuffer), pcBuffer ) );
        return NBIOT_ERROR_NO_CONNECTION;
    }

    /* Here we succesfully received a QUIRD string with the necessary amount of data. Now extract this amount */
    if( sscanf( pcBuffer, "+QSSLRECV: %u", &lLenRcvData ) != 1 )
    {
        if( memcmp( pcBuffer, "+QSSLURC: closed", strlen("+QSSLURC: closed") ) == 0 )
        {
            configPRINTF( ( "ERROR: nbiot_tcp_recv_socket_next, cannot extract the amount of data r\n" ) );
            return NBIOT_ERROR_NO_CONNECTION;
        }
    }

    if( lLenRcvData != 0 )
    {
        lRecvBytes = prvAT_RecvData( pcBuffer, lLenRcvData + 2, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) );

        if( lRecvBytes != lLenRcvData + 2 )
        {
            configPRINTF( ( "ERROR: nbiot_tcp_recv_socket_next, desired: %d, read: %d\r\n", lLenRcvData + 2, lRecvBytes ) );
        }

        fifo_send_from_buf( &xSsockRcvFifo[lSocket], pcBuffer, lLenRcvData );
    }

    prvAT_RecvLine( pcBuffer, sizeof(pcBuffer) - 1, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) ); /* Reading the OK answer */

    return lLenRcvData;
}

/**
  * @brief  Function receive data from socket SSL connection
  * @param  lSocket number of socket. The range is 0-11.
  * @param  pucData pointer to data.
  * @param  lMaxLength max length which can receive.
  * @retval length of receive data and zero if nothing receive
  */
int NBIOT_lSslRecvSocket( int lSocket, unsigned char *pucData, int lMaxLength )
{
    int lRes;
    TickType_t xTick = xTaskGetTickCount();
    TickType_t xTimeoutTicks = NBIOT_TIMING_SEC_150;

    if(xSemaphoreTake( xSslSockSemaphore, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) ) != pdTRUE)
    {
        return NBIOT_ERROR_MUTEX;
    }

    if( fifo_is_empty( &xSsockRcvFifo[lSocket] ) )
    {
        do
        {
            lRes = prvNbiot_SslNextRecvSocket( lSocket, SSL_SOCKET_CHUNK_SIZE, xTimeoutTicks );
        }
        while(lRes > 0);
    }

    if(lRes < 0)
    {
        return lRes;
    }

    int count = fifo_count( &xSsockRcvFifo[lSocket] );
    int len_data = fifo_read_to_buf( &xSsockRcvFifo[lSocket], (char*)pucData, (lMaxLength > count) ? count : lMaxLength );
    xSemaphoreGive( xSslSockSemaphore );

    return len_data;
}

/**
  * @brief  Function close socket SSL connection
  * @param  lSocket number of socket. The range is 0-11.
  * @retval zero in case nonerror and negative in case of error
  */
int NBIOT_lSslCloseSocket( int lSocket )
{
	return prvModemContextDeactivate( lSocket + 1 );
}


/**
 * @brief  Function open socket for TCP connection
 * @param  llContextID PDP context ID. The range is 1-16.
 * @param  ucSocket number of socket. The range is 0-11.
 * @param  pcServerAddres pointer to server address.
 * @param  usRemotePort remote port.
 * @retval zero or positive in case of parsable responses and negative in case of error
 */
int NBIOT_lTcpOpenSocket( uint8_t uclContextID,
                           uint8_t ucSocket,
                           char * pcServerAddres,
                           uint16_t usRemotePort )
{
    char pcResp[ 32 ] = { 0 };

    snprintf( pcResp, sizeof( pcResp ), "+QIOPEN: %d,0", ucSocket );

    const char * ppcResponces[] = { pcResp, "+CME ERROR:", "ERROR" };
    int lRet = 0;
    char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];

    snprintf( pcCommand, sizeof( pcCommand ), "AT+QIOPEN=%d,%d,\"TCP\",\"%s\",%d,0", uclContextID, ucSocket, pcServerAddres, usRemotePort );

    lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof( ppcResponces ) / sizeof( ppcResponces[ 0 ] ), NBIOT_TIMING_SEC_100 );

    return lRet;
}

/**
 * @brief  Read status of an TCP socket
 * @param  ucSocket number of socket. The range is 0-11.
 * @retval zero if this socket is free and negative if socket busy
 */
int nbiot_tcp_socket_state( uint8_t ucSocket )
{
    const char * ppcResponces[] = { "OK", "+CME ERROR:", "ERROR" };

    char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];
    int lRet;

    snprintf( pcCommand, sizeof( pcCommand ), "AT+QISTATE=1,%d", ucSocket );

    lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof( ppcResponces ) / sizeof( ppcResponces[ 0 ] ), NBIOT_TIMING_SEC_10 );

    if( lRet == NBIOT_ERROR_OK )
    {
        if( xModemStatus.lCount )
        {
            return -1;
        }
    }

    return NBIOT_ERROR_OK;
}

/**
 * @brief  Function send data to TCP socket
 * @param  ucSocket number of socket. The range is 0-11.
 * @param  pucData pointer to data.
 * @param  xLength length of data.
 * @retval length of sent data and negative if error
 */
int NBIOT_lTcpSendSocket( uint8_t ucSocket,
                           const unsigned char * pucData,
                           size_t xLength )
{
    int lResult = 0;

    if(xSemaphoreTake( xModemSemaphore, NBIOT_TIMING_SEC_150 ) != pdTRUE)
    {
        return NBIOT_ERROR_MUTEX;
    }

    while( true)
    {
        if( xLength > MAX_PKT_LEN )
        {
            lResult = -1;
            break;
        }

        const char * ppcResponces[] = { "SEND OK", "SEND FAIL", "ERROR", "+QIURC:" };
        int lRet = 0;
        int lLen;
        char pcCommand[ NBIOT_MAX_SIZE_COMMAND ] = { 0 };
        uint32_t ulUnsolicitedFound;

        snprintf( pcCommand, sizeof( pcCommand ) - 1, "AT+QISEND=%d,%d\r\n", ucSocket, xLength );

        if( ( lRet = prvAT_Send( pcCommand, strlen( pcCommand ), NBIOT_TIMING_SEC_1 ) ) != NBIOT_ERROR_OK )
        {
            configPRINTF( ( "ERROR: %d: writing to modem \"%s\"\r\n", lRet, pcCommand ) );
            lResult = -1;
            break;
        }
        vTaskDelay( 1 );

        memset( pcCommand, 0, sizeof( pcCommand ) );

        if( ( lRet = prvAT_RecvLine( pcCommand, sizeof( pcCommand ) - 1, NBIOT_TIMING_SEC_1 ) ) < 0 )
        {
            configPRINTF( ( "ERROR: %d: reading from modem \"%s\"\r\n", lRet, pcCommand ) );
            lResult = -1;
            break;
        }

        if( memcmp( pcCommand, ppcResponces[ 3 ], strlen( ppcResponces[ 3 ] ) ) == 0 ) /* We have got some URC that can prevent us from working correctly */
        {
            vTaskDelay( 3 );
            if( ( lRet = prvAT_RecvLine( pcCommand, sizeof( pcCommand ) - 1, NBIOT_TIMING_SEC_1 ) ) < 0 )
            {
                configPRINTF( ( "ERROR: %d %d: reading from modem \"%s\",\r\n", lRet, sizeof( pcCommand ) - 1, pcCommand ) );
                lResult = -1;
                break;
            }
        }

        if( strncmp( pcCommand, ppcResponces[ 2 ], strlen( ppcResponces[ 2 ] ) ) == 0 ) /* Connection does not exist */
        {
            lResult = NBIOT_ERROR_NO_CONNECTION;
            break;
        }
        else if(( strncmp( pcCommand, "> ", sizeof( "> " ) ) == 0 ) ||
                 ( strncmp( pcCommand, "\r\n> ", sizeof( "\r\n> " ) ) == 0 ))
        {
            if( ( lRet = prvAT_Send( ( char * ) pucData, xLength, NBIOT_TIMING_SEC_1 ) ) != NBIOT_ERROR_OK )
            {
                configPRINTF( ( "ERROR: %d: writing to modem \"%s\"\r\n", lRet, pcCommand ) );
                lResult = -1;
                break;
            }

            memset( pcCommand, 0, sizeof( pcCommand ) );

            TickType_t tick_st = xTaskGetTickCount();

            while( tick_st + 100 > xTaskGetTickCount())
            {
                if( ( lLen = prvAT_Recv( pcCommand, sizeof( pcCommand ) - 1, NBIOT_TIMING_SEC_1 ) ) > 0 )
                {
                    break;
                }
            }

            if( lLen < 0 )
            {
                configPRINTF( ( "ERROR: %d: reading from modem \"%s\"\r\n", lRet, pcCommand ) );
                lResult = -1;
                break;
            }

            ulUnsolicitedFound = prvLookForUnsolicited( pcCommand, lLen );

            if( ulUnsolicitedFound )
            {
                prvModemPrintStatus();
            }

            lRet = prvFindCommandResult( pcCommand, lLen, ppcResponces, sizeof( ppcResponces ) / sizeof( ppcResponces[ 0 ] ) );

            /* Send OK */
            if( lRet == 0 )
            {
                lResult = xLength;
                break;
            }

            /* Send Fail, buffer is full */
            if( lRet == 1 )
            {
                lResult = NBIOT_ERROR_SENDING_BUFFER_FULL;
                break;
            }
        }
        lResult = -1;
        break;
    }
#if PRINT_TX_STATISTICS == 1
    configPRINTF( ( "TCP TX: start %dms, durance %dms, %dBytes\r\n", tick_start, xTaskGetTickCount() - tick_start, lResult ) );
#endif
    xSemaphoreGive( xModemSemaphore );

    return lResult;
}

/**
 * @brief  Function receive next data from TCP socket
 * @param  ucSocket number of socket. The range is 0-11.
 * @param  pcBuffer pointer to data.
 * @param  xBufferSize length of data.
 * @param  pcData pointer to data.
 * @param  xMaxLength maximum length.
 * @param  xTimeoutTicks timeout.
 * @retval length of sent data and negative if error
 */
static int nbiot_tcp_recv_socket_next( uint8_t usSocket,
                                       unsigned char * pcBuffer,
                                       size_t xBufferSize,
                                       unsigned char * pcData,
                                       size_t xMaxLength,
                                       TickType_t xTimeoutTicks )
{
    const char * pcResp[] = { "OK", "+QIURC: \"recv\"", "+QIURC: \"closed\"", "ERROR" };

    memset( pcBuffer, 0, xBufferSize );
    char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];
    int lRecvBytes = 0;
    int lRet = 0;
    int lLenRcvData = 0;
    TickType_t xTick = xTaskGetTickCount();
    int32_t lReadFromExtra = 0;

    if( xMaxLength == 0 )
    {
        return 0;
    }

    /* Check if we have any data in the extra data buffer */
    while( ( xMaxLength != 0 ) && ( !CircularBuffer_bEmpty( &xRecvExtraData ) ) )
    {
        CircularBuffer_lGet( &xRecvExtraData, &pcData[ 0 ] );
        pcData++;
        lReadFromExtra++;
        xMaxLength--;

        if( xMaxLength == 0 )
        {
            return lReadFromExtra;
        }
    }

    snprintf( pcCommand, sizeof( pcCommand ), "AT+QIRD=%d,%d\r\n", usSocket, xMaxLength );
    lRet = prvAT_Send( pcCommand, strlen( pcCommand ), xTimeoutTicks );

    if( lRet != NBIOT_ERROR_OK )
    {
        configPRINTF( ( "ERROR: %d: writing to modem \"%s\"\r\n", lRet, pcCommand ) );
        return -1;
    }

    vTaskDelay( 3 );

    if( ( lRecvBytes = prvAT_RecvLine( (char*)pcBuffer, xBufferSize - 1, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) ) ) < 0 )
    {
        configPRINTF( ( "ERROR: %d %d: reading from modem \"%s\",\r\n", lRecvBytes, xBufferSize, pcCommand ) );
        return -1;
    }

    if( memcmp( pcBuffer, pcResp[ 1 ], strlen( pcResp[ 1 ] ) ) == 0 ) /* We have got URC that data has been received so we just ignore it */
    {
        vTaskDelay( 3 );
        configPRINTF( ( "INFO:nbiot_tcp_recv_socket_next, UIRC!!! \r\n") );
        if( ( lRecvBytes = prvAT_RecvLine( (char*)pcBuffer, xBufferSize - 1, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) ) ) < 0 )
        {
            configPRINTF( ( "ERROR: %d %d: reading from modem \"%s\",\r\n", lRecvBytes, xBufferSize, pcCommand ) );
            return -1;
        }
    }
    else if( memcmp( pcBuffer, pcResp[ 3 ], strlen( pcResp[ 3 ] ) ) == 0 ) /* ERROR, connection does not exist */
    {
        configPRINTF( ( "ERROR: nbiot_tcp_recv_socket_next, no connection,\r\n", lRecvBytes, xBufferSize, pcCommand ) );
        return NBIOT_ERROR_NO_CONNECTION;
    }

    /* Here we succesfully received a QUIRD string with the necessary amount of data. Now extract this amount */

    if( sscanf( (char*)pcBuffer, "+QIRD: %u", &lLenRcvData ) != 1 )
    {
        configPRINTF( ( "ERROR: nbiot_tcp_recv_socket_next, cannot extract the amount of data:%s \r\n", pcBuffer ) );
        return -1;
    }

    if( lLenRcvData != 0 )
    {
        lRecvBytes = prvAT_RecvData( (char*)pcBuffer, lLenRcvData + 2, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) );

        if( lRecvBytes != lLenRcvData + 2 )
        {
            configPRINTF( ( "ERROR: nbiot_tcp_recv_socket_next, desired: %d, read: %d\r\n", lLenRcvData + 2, lRecvBytes ) );
        }

        if( lLenRcvData > xMaxLength )
        {
            configPRINTF( ( "WARNING: nbiot_tcp_recv_socket_next overflowed, desired: %d, read: %d\r\n", xMaxLength, lLenRcvData ) );

            for( int i = xMaxLength; i < lLenRcvData; ++i )
            {
                CircularBuffer_xPut( &xRecvExtraData, pcBuffer[ i ] );
            }
        }

        memcpy( pcData, pcBuffer, MIN( lLenRcvData, xMaxLength ) );
    }

    prvAT_RecvLine( (char*)pcBuffer, xBufferSize - 1, xTimeoutTicks - ( xTaskGetTickCount() - xTick ) ); /* Reading the OK answer */

    return MIN( xMaxLength, lLenRcvData ) + lReadFromExtra;
}

/**
 * @brief  Function receive data from TCP connection
 * @param  lSocket number of socket. The range is 0-11.
 * @param  pucData pointer to data.
 * @param  lMaxLength max length which can receive.
 * @param  ulTimeoutMs receiving timeout
 * @retval length of receive data and zero if nothing was received
 */
int NBIOT_lTcpRecvSocket( uint8_t ucSocket,
                           unsigned char * pucData,
                           size_t xMaxLength,
                           uint32_t ulTimeoutMs )
{

    char pcLine[ MAX_PKT_LEN ];
    TickType_t xTick = xTaskGetTickCount();
    TickType_t xTimeoutTicks = pdMS_TO_TICKS(ulTimeoutMs);
    int32_t lReadData = 0;
    int lResult = 0;

    while( ( lReadData < xMaxLength ) && ( ( xTaskGetTickCount() - xTick ) < xTimeoutTicks ) )
    {
        if( xSemaphoreTake( xModemSemaphore, NBIOT_TIMING_SEC_150 ) != pdTRUE )
        {
            return NBIOT_ERROR_MUTEX;
        }
        int32_t lCurrentReadData = 0;
        lCurrentReadData = nbiot_tcp_recv_socket_next( ucSocket, (uint8_t*)pcLine, MAX_PKT_LEN, pucData + lReadData,
                                                        MIN( NBIOT_IP_CHUNK_SIZE, xMaxLength - lReadData ), xTimeoutTicks - ( xTaskGetTickCount() - xTick ) );

#if PRINT_RX_STATISTICS == 1
        if( lCurrentReadData > 0 )
        {
        	configPRINTF( ( "TCP RX: start %dms, durance %dms, %dBytes\r\n", tick_start, xTaskGetTickCount() - tick_start , lCurrentReadData ) );
        }
#endif
        xSemaphoreGive( xModemSemaphore );

        if( lCurrentReadData < 0 )
        {
            lResult =  lCurrentReadData;
            break;
        }

        lReadData += lCurrentReadData;

        if(xMaxLength <= lReadData)
        {
            lResult = lReadData;
            break;
        };

        if(( xTaskGetTickCount() - xTick ) >= xTimeoutTicks )
        {
            lResult = lReadData;
            break;
        }

        vTaskDelay( lCurrentReadData == 0 ? 100 : 15 );
    }
    return lResult;
}

/**
 * @brief  Function close TCP socket connection
 * @param  ucSocket number of socket. The range is 0-11.
 * @retval zero in case nonerror and negative in case of error
 */
int NBIOT_lTcpCloseSocket( uint8_t ucSocket )
{
    const char * ppcResponces[] = { "OK", "+CME ERROR:", "ERROR" };
    int lRet = 0;
    char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];

    snprintf( pcCommand, sizeof( pcCommand ), "AT+QICLOSE=%d", ucSocket );

    lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof( ppcResponces ) / sizeof( ppcResponces[ 0 ] ), NBIOT_TIMING_SEC_100 );

    return lRet;
}

/**
 * @brief Connects via TCP to the remote server in the transparent access mode
 * @param uslContextID PDP context ID. The range is 1-16.
 * @param usSocketNumber Socket number (0-11)
 * @param pcServerAddress Remote server address or IP
 * @param usRemotePort Remote server port
 * @return 0 in the case of succes, 1 in the case of error or negative numbers in the case of internal errors
 */
int NBIOT_lTcpOpenTransparent( uint8_t uslContextID, uint8_t usSocketNumber, char* pcServerAddress, uint16_t usRemotePort )
{
    const char * ppcResponces[] = { "CONNECT", "ERROR" };
    int8_t cReturnCode = 0;
    char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];

    snprintf( pcCommand, sizeof( pcCommand ), "AT+QIOPEN=%d,%d,\"TCP\",\"%s\",%d,0,2", uslContextID, usSocketNumber, pcServerAddress, usRemotePort );

    cReturnCode = prvPperformCommand( pcCommand, ppcResponces, sizeof( ppcResponces ) / sizeof( ppcResponces[ 0 ] ), NBIOT_TIMING_SEC_100 );

    return cReturnCode;
}

/**
 * @brief  Function closes TCP socket connection
 * @param  ucSocket number of socket. The range is 0-11.
 * @retval zero in case nonerror, negative in case of internal error error, and positive in case of logic error
 */
int NBIOT_lTcpCloseTransparent( uint8_t ucSocket )
{
    int cReturnCode = 0;
    char pcReceiveBuffer[MODEM_BUFFER_SIZE];
    /* Exiting from transparent mode sequence */
    vTaskDelay( NBIOT_TIMING_SEC_1 );
    cReturnCode = prvAT_Send( TRANSPARENT_MODE_EXIT_STRING, strlen(TRANSPARENT_MODE_EXIT_STRING), NBIOT_TIMING_SEC_1 );
    if( cReturnCode == NBIOT_ERROR_OK )
    {
        vTaskDelay( NBIOT_TIMING_SEC_1 );
        do
        {
            prvAT_RecvLine( pcReceiveBuffer, MODEM_BUFFER_SIZE, NBIOT_TIMING_SEC_10 );
        } while(  strncmp(pcReceiveBuffer, "OK", strlen("OK")) != 0 &&
                  strncmp(pcReceiveBuffer, "NO CARRIER", strlen("NO CARRIER")) != 0 );
        NBIOT_lTcpCloseSocket( ucSocket );
        return NBIOT_ERROR_OK;
    }
    return cReturnCode;
}

/**
 * @brief  Function receive data from TCP connection
 * @param  ucSocket Socket number
 * @param  pucData pointer to data.
 * @param  xMaxLength max length which can receive.
 * @param  ulTimeoutMs time out.
 * @retval length of receive data and zero if nothing was received
 */
int NBIOT_lTcpRecvTransparent( uint8_t ucSocket,
                           unsigned char * pucData,
                           size_t xMaxLength,
                           uint32_t ulTimeoutMs )
{
    long lReturnCode = prvAT_RecvData( (char*)pucData, xMaxLength, ulTimeoutMs );
    return lReturnCode;
}

/**
 * @brief  Function send data to TCP socket
 * @param  pucData pointer to data.
 * @param  xLength length of data.
 * @retval length of sent data and negative if error
 */
int NBIOT_lTcpSendTransparent( unsigned char * pucData, size_t xLength )
{
    return prvAT_Send( (char*)pucData, xLength, NBIOT_TIMING_SEC_1 );
}

/**
 * Pings a remote host
 * @param ucContextID Context ID
 * @param pcAddress Remote host address
 * @return status_t kStatus_Success if ping is successful and value >0 in the case of error
 */
status_t NBIOT_xTcpPing( uint8_t ucContextID, uint8_t * pcAddress )
{
    const char * ppcResponces[] = { "OK", "ERROR" };
    const char * pcFormat = "+QPING: %3[0-9],\"%16[0-9.]\",%4[0-9],%4[0-9],%4[0-9]";
    int lRet = 0;
    char pcCommand[ NBIOT_MAX_SIZE_COMMAND ];
    char pcLine[ 200 ];
    uint32_t ulUnsolicitedFound;
    char pcRes[4] = { 0 };
    char pcIpAddr[17] = { 0 };
    char pcBytes[5] = { 0 };
    char pcTime[5] = { 0 };
    char pcTtl[5] = { 0 };

	if(xSemaphoreTake( xModemSemaphore, NBIOT_TIMING_SEC_150 ) != pdTRUE)
	{
		return eStatus_Fail;
	}

	/* PING command. 2sec timeout, 1 packet */
    snprintf( pcCommand, sizeof( pcCommand )-1, "AT+QPING=%d,\"%d.%d.%d.%d\",2,1", ucContextID, pcAddress[0], pcAddress[1], pcAddress[2], pcAddress[3] );

    lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof( ppcResponces ) / sizeof( ppcResponces[ 0 ] ), NBIOT_TIMING_SEC_1 );

	if( lRet == 0 )
	{
		TickType_t xTick = xTaskGetTickCount();
		int lTimeout = NBIOT_TIMING_SEC_4;

		while( !prvCompareTimeval(xTick, lTimeout) )
		{
			if( (lRet = prvAT_Recv(pcLine, sizeof( pcLine ) / sizeof( pcLine[ 0 ] ), NBIOT_TIMING_SEC_3)) < 0 )
			{
				configPRINTF( ( "ERROR: %d: reading from modem \"%s\"\r\n", lRet, pcLine ) );
			}

			ulUnsolicitedFound = prvLookForUnsolicited(pcLine, lRet);

			if( ulUnsolicitedFound )
			{
				prvModemPrintStatus();
			}

			for( int i=0; i< xModemStatus.lCount; i++ )
			{
				if( sscanf((const char*)&xModemStatus.pucValue[i][0], pcFormat, pcRes, pcIpAddr, pcBytes, pcTime, pcTtl) == 5 )
				{
					configPRINTF( ( "PING reply from %s: bytes=%s time=%sms TTL=%s\r\n", pcIpAddr, pcBytes, pcTime, pcTtl) );
					lRet = eStatus_Success;
					xSemaphoreGive( xModemSemaphore );
					return lRet;
				}
			}
		}
		lRet = eStatus_Timeout;
	}
	else
	{
		lRet = eStatus_Fail;
	}
    xSemaphoreGive( xModemSemaphore );

    return lRet;
}

/**
 * Returns quality of signal (RSSI) in dBm
 * @param pointer to psRSSIdBm for value return. Value 0 - if not known or not detectable.
 * @return status_t kStatus_Success in case of successful and value >0 in the case of error
 */
status_t NBIOT_xGetRssi( int16_t *psRSSIdBm )
{
	const char * pcFormat = "+CSQ: %3[0-9],%3[0-9]";
    int lRet = 0;
    char pcRssi[4]= { 0 };
    char pcBer[4] = { 0 };

    if( psRSSIdBm == NULL) return eStatus_InvalidArgument;
    *psRSSIdBm = 0;

	if( xSemaphoreTake( xModemSemaphore, NBIOT_TIMING_SEC_150 ) != pdTRUE )
	{
		return eStatus_Fail;
	}

    lRet = prvModemSignalQuality();
	if( lRet == 0 )
	{
		for( int i=0; i< xModemStatus.lCount; i++ )
		{
			if( sscanf((const char*)&xModemStatus.pucValue[i][0], pcFormat, pcRssi, pcBer) == 2 )
			{
				/* 3GPP TS 27.007 */
				unsigned char tmp = atoi( pcRssi );
				if( tmp == 99 )
				{
					*psRSSIdBm = 0;
				}
				else
				{
					*psRSSIdBm = 2*atoi( pcRssi ) - 113;
				}
				lRet = eStatus_Success;
				xSemaphoreGive( xModemSemaphore );
				return lRet;
			}
		}
		lRet = eStatus_Timeout;
	}
	else
	{
		lRet = eStatus_Fail;
	}
    xSemaphoreGive( xModemSemaphore );

    return lRet;
}

/**
  * @brief  Function write file to the modem UFS
  * @param  pcName pointer to the name file.
  * @param  pcData pointer to the data file.
  * @param  lLength length of file.
  * @retval zero in case nonerror and negative in case of error
  */
int NBIOT_lWriteFile( char *pcName, const char *pcData, int lLength )
{
	const char * ppcResponces[] = {"CONNECT", "+CME ERRORR:", "ERROR"};
	int lRet = 0;
	char pcCommand[NBIOT_MAX_SIZE_COMMAND];
	uint32_t ulUnsolicitedFound;

	snprintf( pcCommand, sizeof(pcCommand)-1, "AT+QFUPL=\"%s\",%d,5", pcName, lLength );

	lRet = prvPperformCommand( pcCommand, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );

	if( lRet == NBIOT_ERROR_OK )
	{
		memset( pcCommand, 0, sizeof(pcCommand) );

		if( (lRet = prvAT_Send((char*)pcData, lLength, NBIOT_TIMING_SEC_5)) != eStatus_Success )
		{
			configPRINTF( ( "ERROR!!!!!!!!!!\r\n" ) );
		}
	}

	if( lRet == NBIOT_ERROR_OK )
	{
		const char * ppcRespons[] = {"OK", "ERROR"};

		if( (lRet = prvAT_Recv( pcCommand, sizeof(pcCommand)-1, NBIOT_TIMING_SEC_10) ) < 0 )
		{
			configPRINTF( ( "ERROR: %d: reading from modem \"%s\"\r\n", lRet, pcCommand ) );
		}

		ulUnsolicitedFound = prvLookForUnsolicited( pcCommand, lRet );

		if( ulUnsolicitedFound )
		{
			prvModemPrintStatus();
		}

		lRet = prvFindCommandResult( pcCommand, lRet, ppcRespons, sizeof(ppcRespons)/sizeof(ppcRespons[0]) );
	}

	return lRet;
}

/**
  * @brief  Function read storage size of the modem
  * @param  none.
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
int NBIOT_lStorageSize( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "AT+QFLDS", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}

/**
  * @brief  Function read storage size of the modem UFS
  * @param  none.
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
int NBIOT_lStorageSizeUFS( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "AT+QFLDS=\"UFS\"", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}

/**
  * @brief  Function read list files in the modem UFS
  * @param  none.
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
int NBIOT_lListFile( void )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	return prvPperformCommand( "AT+QFLST=\"*\"", ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}

/**
  * @brief  Function delete file from the modem UFS
  * @param  pcName name of the file.
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
int NBIOT_lDeleteFile( char *pcName )
{
	const char * ppcResponces[] = {"OK", "+CME ERROR:", "ERROR"};

	char command[ NBIOT_MAX_SIZE_COMMAND ];

	snprintf( command, sizeof(command)-1, "AT+QFDEL=\"%s\"", pcName );

	return prvPperformCommand( command, ppcResponces, sizeof(ppcResponces)/sizeof(ppcResponces[0]), NBIOT_TIMING_SEC_1 );
}

/**
  * @brief  Function delete all files from the modem UFS
  * @param  none.
  * @retval zero or positive in case of parsable responses and negative in case of error
  */
int NBIOT_lDeleteAll( void )
{
	return NBIOT_lDeleteFile( "*" );
}

/**
  * @brief  Function initialize UFS and erase it
  * @param  none.
  * @retval none
  */
void NBIOT_vInitFreeMemory( void )
{
    NBIOT_lStorageSize();
    NBIOT_lStorageSizeUFS();
    NBIOT_lListFile();
    NBIOT_lDeleteAll();
    NBIOT_lListFile();
}

#endif /* #if NBIOT_ENABLED */

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
#include <stdio.h>

#include "mqtt_task.h"

#include "iot_config.h"
#include "iot_wifi.h"
#include "iot_mqtt_agent.h" 
#include "types/iot_mqtt_types.h"

#include "iot_demo_logging.h"
#include "iot_network_manager_private.h"
#include "platform/iot_threads.h"
#include "iot_init.h"

#include "app_types.h"
#include "json/json_sensor.h"
#include "converting.h"
#include "base64.h"
#include "float_to_string.h"
#include "led.h"

#include "i2c_mux.h"
#include "DAVE.h"

#include "aws_nbiot.h"
#include "iot_secure_sockets.h"

/* Credentials includes. */

/** Topic to which messages will be published */
#ifdef PATCH
	#define mqttTOPIC_BUFFER_LENGTH    	( 128 )
	static const char pcTopic[] = "$aws/rules/redirect_metrics/infn/dev/";
	static const char *pcThingName = clientcredentialIOT_THING_NAME;
#else
	static const char pcTopic[] = "$aws/rules/redirect_metrics/infn/dev/"clientcredentialIOT_THING_NAME"";
#endif

/** Buffer in which messages to the brocker will be generated */
static uint8_t pcMQTTBuffer[ mqtttaskSEND_BUFFER_SIZE ];

/* Package for MQTT */
static InfineonSensorsMessage_t xSensorsMessage;

static IotNetworkManagerSubscription_t subscription = IOT_NETWORK_MANAGER_SUBSCRIPTION_INITIALIZER;

static IotSemaphore_t xNetworkSemaphore;

static uint32_t ulConnectedNetwork = AWSIOT_NETWORK_TYPE_NONE;
/**
 * @ brief The handle of the MQTT client object used by the MQTT echo demo.
 */
static MQTTAgentHandle_t xMQTTHandle = NULL;

/** Handle for the sensors queue */
QueueHandle_t xMQTTMessageQueueHandle = NULL;

/** Handle for the task */
TaskHandle_t xMQTTTaskHandle = NULL;
TaskHandle_t xRobustTaskHandle = NULL;

/* Variables used to indicate the connected network. */
static IotMqttError_t xIotMqttState = IOT_MQTT_SUCCESS;

static eConnectionState_t eConnStatus = eNetworkError;
static IotMutex_t xNetworkMutex;

static uint8_t ucPingErrorCount = 0;
static uint8_t ucPublishErrorCount = 0;


static void prvMqttTask( void *pvParameters );

static BaseType_t prvCreateRobustTask ( void );
static void prvDeleteRobustTask( void );
static BaseType_t prvNetworkConnectionRestart( void );
static BaseType_t prvMqttAgentRestart( void );
static ePingStatus_t prvPing( uint8_t *pucIPAddr, uint16_t usCount, uint32_t ulIntervalMS );

/** @brief Start the MQTT agent and connects to the broker */
static BaseType_t prvMqttAgentStartAndConnect( void );


void vMqttTaskStart( void )
{
    if( xMQTTTaskHandle == NULL )
    {
        xTaskCreate( prvMqttTask, "MQTTTask", mqtttaskSTACK_SIZE, NULL, mqtttaskPRIORITY, &xMQTTTaskHandle );
    }
}


void vMqttTaskDelete( void )
{
    configPRINTF( ("Deleting the MQTT task") );
    if( xMQTTTaskHandle != NULL )
    {
        vTaskSuspend( xMQTTTaskHandle );
    }
    if( xMQTTHandle != NULL )
    {
        /* Disconnect from the MQTT broker */
        MQTT_AGENT_Disconnect( xMQTTHandle, mqtttaskMQTT_TIMEOUT );
        MQTT_AGENT_Delete( xMQTTHandle );
        xMQTTHandle = NULL;
        /** Delete the queue. We need to do that atomically since the sensor task could try to send to the invalidated queue */
        taskENTER_CRITICAL();
        vQueueDelete( xMQTTMessageQueueHandle );
        xMQTTMessageQueueHandle = NULL;
        taskEXIT_CRITICAL();
    }
    /* Delete the task */
    if( xMQTTTaskHandle != NULL )
    {
        vTaskDelete( xMQTTTaskHandle );
        xMQTTTaskHandle = NULL;
    }
}


void prvMqttTask( void *pvParameters )
{
    ( void )pvParameters;

    if( I2C_MUX_cWait( I2C_MUX_TIMEOUT ) < 0 )
    {
    	vFullReset( APP_ERROR_I2C_MUX_NOT_RELEASED );
    }

    LED_xStatus( MQTT, START );
    /* Create an MQTT agent and connect to the broker */
    BaseType_t xStatus = prvMqttAgentStartAndConnect();
    if( xStatus == pdPASS )
    {
    	LED_xStatus( MQTT, SUCCESS );
    }
    else
    {
    	LED_xStatus( MQTT, FAILED );
    	vFullReset( MQTT_AGENT_INIT_ERROR );
    }

    MQTTAgentPublishParams_t xMQTTAgentPublishParams;

#ifdef PATCH
	char ucTopicString[ mqttTOPIC_BUFFER_LENGTH ] = { 0 };

	strcat( ucTopicString, pcTopic );
	strcat( ucTopicString, pcThingName );

    xMQTTAgentPublishParams.pucTopic = (uint8_t*)ucTopicString;
    xMQTTAgentPublishParams.usTopicLength = strlen( ucTopicString );

    configPRINTF( ("MQTT Thing Name: %s.\r\n", pcThingName) );

#else
    xMQTTAgentPublishParams.pucTopic = (uint8_t*)pcTopic;
    xMQTTAgentPublishParams.usTopicLength = strlen( pcTopic );
#endif

    configPRINTF( ("MQTT Topic: %s.\r\n", xMQTTAgentPublishParams.pucTopic) );

    xMQTTAgentPublishParams.xQoS = eMQTTQoS1;

    if( xStatus == pdPASS )
    {
        /** Initialize the Sensors Data Queue */
        xMQTTMessageQueueHandle = xQueueCreate( mqtttaskRECEIVE_QUEUE_LENGTH, sizeof( InfineonSensorsMessage_t ) );

        if( xMQTTMessageQueueHandle == NULL )
        {
            xStatus = pdFAIL;
        }
    }

    if( xStatus == pdPASS )
    {
		/** Create non-recursive mutex */
		if( IotMutex_Create( &xNetworkMutex, false ) != true )
		{
			IotLogError( "Failed to create semaphore to wait for a network connection." );
			xStatus = pdFAIL;
		}
    }

    if( xStatus == pdPASS )
    {
    	eConnStatus = eConnEstablished;
    	xStatus = prvCreateRobustTask();
    }

    if( xStatus == pdPASS )
    {
    	vSensorsTaskStart();

        for( ;; )
        {

        	if( eConnStatus == eConnEstablished )
        	{
				/** Receive the sensors data from the data gathering task*/
				if( xQueueReceive( xMQTTMessageQueueHandle, &xSensorsMessage, portMAX_DELAY ) )
				{
					configPRINTF( ("Queue Receive\r\n") );
					/** Fill the buffer to send */
#if MQTT_OUTPUT_FORMAT_JSON
						bool bRet = JSON_bGenerateToSend( &xSensorsMessage, (char*)pcMQTTBuffer, sizeof(pcMQTTBuffer) );
						if( !bRet )
						{
							configPRINTF( ("Generate JSON failed\r\n") );
						}
#else
						CSV_vGenerateToSend( &xSensorsMessage, pcMQTTBuffer );
#endif

						/** Publish the sensors data */
						xMQTTAgentPublishParams.pvData = pcMQTTBuffer;
						xMQTTAgentPublishParams.ulDataLength = strlen( (char*) pcMQTTBuffer );
						if( xIotMqttState == IOT_MQTT_SUCCESS )
						{
							IotMutex_Lock( &xNetworkMutex );

							xStatus = MQTT_AGENT_Publish( xMQTTHandle, &xMQTTAgentPublishParams, mqtttaskMQTT_TIMEOUT );

							if( xStatus == eMQTTAgentSuccess )
							{
								/* If we use quality of service with response then after success sending ucPingErrorCount will be cleared */
								if( xMQTTAgentPublishParams.xQoS > 0)
								{
									ucPingErrorCount = 0;
								}
								LED_xStatus( MESSAGE, SUCCESS );
								configPRINTF( ("Message sent successfully \r\n") );

								ucPublishErrorCount = 0;
							}
							else
							{
								LED_xStatus( MESSAGE, FAILED );
								configPRINTF( ("Message was not sent: %d \r\n", xStatus) );

								if( ++ucPublishErrorCount >= ATTEMPTS_COUNT )
								{
									xIotMqttState = IOT_MQTT_NETWORK_ERROR;
									eConnStatus = eMqttError;

									ucPublishErrorCount = 0;
								}
							}

							IotMutex_Unlock( &xNetworkMutex );

						} /* if( xIotMqttState == IOT_MQTT_SUCCESS ) */

					} /* if( xQueueReceive() ) */
					else
					{
						configPRINTF( ("Stop MQTT task \r\n") );
						break;
					}

        	} /* if( eConnStatus == eConnEstablished ) */
        	else
        	{
        		/* We should not try to Ping during reconnection, thats why Mutex used */
        		IotMutex_Lock( &xNetworkMutex );

        		switch( eConnStatus )
        		{

					case eNetworkError:
						configPRINTF( ("eNetworkError \r\n") );
						/* In case of network error - try to reestablish network connection */
						if( prvNetworkConnectionRestart() == pdPASS )
						{
							eConnStatus = eConnEstablished;
						}
						else
						{
							/* We shouldn't try reestablish MQTT connection while WiFi is not connected */
							vFullReset( NETWORK_INIT_ERROR );
						}
						break;
					case eMqttError:
						/* In case of MQTT connection error - try to reestablish MQTT connection */
						if( prvMqttAgentRestart() == pdPASS )
						{
							xIotMqttState = IOT_MQTT_SUCCESS;
							eConnStatus = eConnEstablished;
						}
						else
						{
							eConnStatus = eNetworkError;
						}
						break;
					default:
						/* eConnStatus. */
						configASSERT( false );

				} /* switch( eConnStatus ) */

        		vTaskDelay( pdMS_TO_TICKS(RECONNECT_DELAY) );

        		IotMutex_Unlock( &xNetworkMutex );

        	}
        }

        prvDeleteRobustTask();
        IotMutex_Destroy( &xNetworkMutex );
    }

    /** Something went wrong, delete the task */
    vTaskDelete( NULL );
}

/*-----------------------------------------------------------*/

/**
 * @brief Called by the MQTT library when an MQTT disconnect received.
 *
 */
BaseType_t prvDisconnectCallback( void *pvParam1, MQTTAgentCallbackParams_t * const pCallbackParam )
{
    ( void ) pvParam1;
    if( pCallbackParam->xMQTTEvent == eMQTTAgentDisconnect )
    {
		xIotMqttState = IOT_MQTT_NETWORK_ERROR;
    }
    configPRINTF( ( "Callback, %d.\r\n", pCallbackParam->xMQTTEvent) );
    /* pdFALSE is returned - The ownership of the buffer passed in the callback (xBuffer
	 * in MQTTPublishData_t) remains with the library and it is recycled as soon as
	 * the callback returns.*/
    return pdFALSE;
}


BaseType_t prvMqttAgentStartAndConnect( void )
{
	BaseType_t xRet = pdFAIL;
    MQTTAgentReturnCode_t xMqttRC;

    MQTTAgentConnectParams_t xConnectParameters =
    {
        clientcredentialMQTT_BROKER_ENDPOINT,         /* The URL of the MQTT broker to connect to. */
        ( mqttagentREQUIRE_TLS ),                     /* Connection flags. */
        pdFALSE,                                      /* Deprecated. */
        clientcredentialMQTT_BROKER_PORT,             /* Port number on which the MQTT broker is listening. Can be overridden by ALPN connection flag. */
        ( uint8_t * ) clientcredentialIOT_THING_NAME, /* Client Identifier of the MQTT client. It should be unique per broker. */
        0,                                            /* The length of the client Id, filled in later as not const. */
        pdFALSE,                                      /* Deprecated. */
		NULL,                          				  /* User data supplied to the callback. Can be NULL. */
		( MQTTAgentCallback_t ) prvDisconnectCallback,                        /* Callback used to report various events. Can be NULL. */
        NULL,                                         /* Certificate used for secure connection. Can be NULL. */
        0                                             /* Size of certificate used for secure connection. */
    };

    /** Check this function has not already been executed. */
    configASSERT( xMQTTHandle == NULL );

    /* The MQTT client object must be created before it can be used.  The
     * maximum number of MQTT client objects that can exist simultaneously
     * is set by mqttconfigMAX_BROKERS. */
    xMqttRC = MQTT_AGENT_Create( &xMQTTHandle );

    if( xMqttRC == eMQTTAgentSuccess )
    {
        /* Fill in the MQTTAgentConnectParams_t member that is not const,
         * and therefore could not be set in the initializer (where
         * xConnectParameters is declared in this function). */
        xConnectParameters.usClientIdLength = ( uint16_t ) strlen( ( const char * ) clientcredentialIOT_THING_NAME );

        /* Connect to the broker. */
        configPRINTF( ("MQTT echo attempting to connect to %s.\r\n", clientcredentialMQTT_BROKER_ENDPOINT) );
        xMqttRC = MQTT_AGENT_Connect( xMQTTHandle,
                                        &xConnectParameters,
                                        mqtttaskMQTT_ECHO_TLS_NEGOTIATION_TIMEOUT );

        if( xMqttRC != eMQTTAgentSuccess )
        {
            /** Could not connect, so delete the MQTT client. */
            ( void ) MQTT_AGENT_Delete( xMQTTHandle );
            xMQTTHandle = NULL;
            configPRINTF( ( "ERROR:  MQTT echo failed to connect with error %d.\r\n", xMqttRC ) );
        }
        else
        {
            configPRINTF( ( "MQTT echo connected.\r\n" ) );
            xRet = pdPASS;
            xIotMqttState = IOT_MQTT_SUCCESS;
        }
    }

    return xRet;
}


/* Reestablish MQTT connection - delete old Agent, Create and Connect new agent */
BaseType_t prvMqttAgentRestart( void )
{
	configPRINTF( ("Restart MQTT connection\r\n") );

	MQTTAgentReturnCode_t xMqttRC = eMQTTAgentSuccess;
	if( xMQTTHandle != NULL )
	{
		/* Disconnect from the MQTT brocker */
		xMqttRC = MQTT_AGENT_Disconnect( xMQTTHandle, mqtttaskMQTT_TIMEOUT );

		if( xMqttRC == eMQTTAgentSuccess )
		{
			xMqttRC = MQTT_AGENT_Delete( xMQTTHandle );
		}

		if( xMqttRC == eMQTTAgentSuccess )
		{
			xMQTTHandle = NULL;
		}
	}


	/* Try to connect */
	if( xMqttRC == eMQTTAgentSuccess )
	{
		/* Create an MQTT agent and connect to the broker */
		BaseType_t xStatus = prvMqttAgentStartAndConnect();
		vTaskDelay( 1 );

		return xStatus;
	}

	return pdFALSE;
}


BaseType_t prvNetworkConnectionRestart( void )
{
	int status = EXIT_SUCCESS;
	ulConnectedNetwork = AWSIOT_NETWORK_TYPE_NONE;

	if( WIFI_ENABLED ) configPRINTF( ("Restart WiFi connection\r\n") );
	else if( NBIOT_ENABLED ) configPRINTF( ("Restart NB-IoT connection\r\n") );

	/** Disable networks. */
	vTaskDelay( 1 );

	MQTTAgentReturnCode_t xMqttRC = eMQTTAgentSuccess;
	if( xMQTTHandle != NULL )
	{
		/* Disconnect from the MQTT broker */
		xMqttRC = MQTT_AGENT_Disconnect( xMQTTHandle, mqtttaskMQTT_TIMEOUT );

		if( xMqttRC == eMQTTAgentSuccess )
		{
			configPRINTF( ("MQTT Agent disconnected.\r\n") );
			xMqttRC = MQTT_AGENT_Delete( xMQTTHandle );
		}

		if( xMqttRC == eMQTTAgentSuccess )
		{
			configPRINTF( ("MQTT Agent deleted.\r\n") );
			xMQTTHandle = NULL;
		}
	}

	if( xMqttRC == eMQTTAgentSuccess )
	{
		configPRINTF( ("Disabling network\r\n") );
		if( AwsIotNetworkManager_DisableNetwork( configENABLED_NETWORKS ) != configENABLED_NETWORKS )
		{
			IotLogError( "Failed to disable network.\r\n" );
			status = EXIT_FAILURE;
//			vFullReset(NETWORK_INIT_ERROR);
		}
		else
		{
			configPRINTF( ("Network disabled.\r\n") );
			status = EXIT_SUCCESS;
		}
	}

	/** Initialize all the  networks configured for the device. */
	if( status == EXIT_SUCCESS )
	{
		configPRINTF( ("Connecting to network\r\n") );
		if( AwsIotNetworkManager_EnableNetwork( configENABLED_NETWORKS ) != configENABLED_NETWORKS )
		{
			IotLogError( "Failed to initialize all the networks configured for the device." );
			status = EXIT_FAILURE;
//			vFullReset(NETWORK_INIT_ERROR);
		}
	}

	if( status == EXIT_SUCCESS )
	{
		/** Wait for network configured for the demo to be initialized. */
		ulConnectedNetwork = AwsIotNetworkManager_GetConnectedNetworks() & configENABLED_NETWORKS;

		if( ulConnectedNetwork == AWSIOT_NETWORK_TYPE_NONE )
		{
			/* Network not yet initialized. Block for a network to be intialized. */
			configPRINTF( ("No networks connected for the demo. Waiting for a network connection. \r\n") );
			IotLogInfo( "No networks connected for the demo. Waiting for a network connection. " );
			IotSemaphore_Wait( &xNetworkSemaphore );
			ulConnectedNetwork = AwsIotNetworkManager_GetConnectedNetworks() & configENABLED_NETWORKS;
		}

		/* Try to connect */
		{
			/* Create an MQTT agent and connect to the broker */
			BaseType_t xStatus = prvMqttAgentStartAndConnect();
			vTaskDelay( 1 );

			return xStatus;
		}
	}

	return ( status == EXIT_SUCCESS ) ? pdPASS : pdFAIL;
}


ePingStatus_t prvPing( uint8_t * pucIPAddr, uint16_t usCount, uint32_t ulIntervalMS )
{
#if WIFI_ENABLED
	BaseType_t xRssi = WIFI_GetRssi();

	if( WIFI_IsConnected() && xRssi < 0 )
	{
		configPRINTF( ("WIFI RSSI = %d dBm \r\n", xRssi) );
		if ( WIFI_Ping( pucIPAddr, usCount, ulIntervalMS ) == eWiFiSuccess )
		{
			return ePingSuccess;
		}
		else
		{
			return ePingFail;
		}
	}
	else
	{
		configPRINTF( ( "WIFI is NOT connected to Access Point \r\n" ));
		return ePingFail;
	}

#endif /* WIFI_ENABLED */

#if NBIOT_ENABLED
	int16_t sRssi = 0;
	NBIOT_xGetRssi(&sRssi);

	if( sRssi < 0)
	{
		configPRINTF( ("LTE RSSI= %d dBm \r\n", sRssi) );
		if( NBIOT_xTcpPing( NBIOT_CONTEXT_ID, pucIPAddr ) == eStatus_Success )
		{
			return ePingSuccess;
		}
		else
		{
			return ePingFail;
		}
	}
	else
	{
		configPRINTF( ("LTE RSSI is not known or not detectable \r\n") );
		return ePingFail;
	}
#endif /* NBIOT_ENABLED */
}




static void vRobustTask( void *pvParameters )
{
    uint8_t ipbuf[] = { 1, 1, 1, 1 };
    ePingStatus_t xRet = ePingSuccess;

    for( ;; )
    {
    	configPRINTF( ("vRobustTask \r\n") );
    	configPRINTF( ("HEAP free size = %d\r\n", xPortGetFreeHeapSize()) );
    	configPRINTF( ("HEAP MIN ever free size = %d\r\n", xPortGetMinimumEverFreeHeapSize()) );

    	/* We should not try to Ping during reconnection, thats why mutex used */
    	IotMutex_Lock( &xNetworkMutex );

    	configPRINTF( ("eConnStatus = %d\r\n", eConnStatus) );

    	if( eConnStatus != eNetworkError )
    	{
    		/* Ping */
    	    xRet = prvPing( ipbuf, PING_COUNT, PING_TIMEOUT );
    		configPRINTF( ("PING = %d\r\n", xRet) );

    		if( xRet != ePingSuccess )
    		{
    			if( ++ucPingErrorCount >= ATTEMPTS_COUNT )
    			{
    				/* Problems with network has higher priority than MQTT connection issues */
					configPRINTF( ("Network ping error \r\n") );
					eConnStatus = eNetworkError;

    				ucPingErrorCount = 0;
    			}
    		}
			else
			{
				ucPingErrorCount = 0;

				if( xIotMqttState != IOT_MQTT_SUCCESS )
				{
					/* If network is good - check MQTT connection */
					configPRINTF( ("Something wrong with MQTT connection. MQTT Agent will be reconnected \r\n") );
					eConnStatus = eMqttError;
				}
			}

		} /* if( eConnStatus != eNetworkError ) */

    	IotMutex_Unlock( &xNetworkMutex );

        vTaskDelay( pdMS_TO_TICKS(ROBUST_DELAY) );
    }

    vTaskSuspend( NULL );
}


BaseType_t prvCreateRobustTask( void )
{
    BaseType_t xRet;

    /* Create the test task */
    xRet = xTaskCreate(
    				vRobustTask,
                    "RobustTask",
					ROBUST_TASK_STACK_SIZE,
                    ( void * ) 1,
					robusttaskPRIORITY,
                    &xRobustTaskHandle );
    return xRet;
}


void prvDeleteRobustTask( void )
{
    if( xRobustTaskHandle != NULL)
    {
        vTaskDelete( xRobustTaskHandle );
    }
}


void vNetworkChangedCB( uint32_t ulNetworkType, AwsIotNetworkState_t xNetworkState, void * pvContext )
{
	configPRINTF( ("vNetworkChangedCB = %d\r\n", xNetworkState) );
	if( ( xNetworkState == eNetworkStateEnabled ) && ( ulConnectedNetwork == AWSIOT_NETWORK_TYPE_NONE ) )
	{
		ulConnectedNetwork = ulNetworkType;
		IotSemaphore_Post( &xNetworkSemaphore );
	}


}


uint8_t ucNetworkInitialize( void )
{
	uint8_t status = EXIT_SUCCESS;
	bool commonLibrariesInitialized = false;
	bool semaphoreCreated = false;

	/** Initialize common libraries required by network manager and demo. */
	if( IotSdk_Init() == true )
	{
		commonLibrariesInitialized = true;
	}
	else
	{
		IotLogInfo( "Failed to initialize the common library." );
		status = EXIT_FAILURE;
	}

	if( status == EXIT_SUCCESS )
	{
		if( AwsIotNetworkManager_Init() != pdTRUE )
		{
			IotLogError( "Failed to initialize network manager library." );
			status = EXIT_FAILURE;
		}
	}

	if( status == EXIT_SUCCESS )
	{
		/** Create semaphore to signal that a network is available for the demo. */
		if( IotSemaphore_Create( &xNetworkSemaphore, 0, 1 ) != true )
		{
			IotLogError( "Failed to create semaphore to wait for a network connection." );
			status = EXIT_FAILURE;
		}
		else
		{
			semaphoreCreated = true;
		}
	}

	if( status == EXIT_SUCCESS )
	{
		/** Subscribe for network state change from Network Manager. */
		if( AwsIotNetworkManager_SubscribeForStateChange( configENABLED_NETWORKS,
														  vNetworkChangedCB,
														  NULL,
														  &subscription ) != pdTRUE )
		{
			IotLogError( "Failed to subscribe network state change callback." );
			status = EXIT_FAILURE;
		}
	}

	/** Initialize all the  networks configured for the device. */
	if( status == EXIT_SUCCESS )
	{
		configPRINTF( ("Connecting to network\r\n") );
		if( AwsIotNetworkManager_EnableNetwork( configENABLED_NETWORKS ) != configENABLED_NETWORKS )
		{
			IotLogError( "Failed to initialize all the networks configured for the device." );
			status = EXIT_FAILURE;
			vFullReset( NETWORK_INIT_ERROR );
		}
	}

	if( status == EXIT_SUCCESS )
	{
		/** Wait for network configured for the demo to be initialized. */
		ulConnectedNetwork = AwsIotNetworkManager_GetConnectedNetworks() & configENABLED_NETWORKS;

		if( ulConnectedNetwork == AWSIOT_NETWORK_TYPE_NONE )
		{
			/* Network not yet initialized. Block for a network to be intialized. */
			IotLogInfo( "No networks connected for the demo. Waiting for a network connection. " );
			IotSemaphore_Wait( &xNetworkSemaphore );
			ulConnectedNetwork = AwsIotNetworkManager_GetConnectedNetworks() & configENABLED_NETWORKS;
		}
	}

	if( status == EXIT_FAILURE )
	{
		vFullReset( NETWORK_INIT_ERROR );

		if( semaphoreCreated == true )
		{
			IotSemaphore_Destroy( &xNetworkSemaphore );
		}

		if( commonLibrariesInitialized == true )
		{
			IotSdk_Cleanup();
		}
	}

	return status == 0 ? pdPASS : pdFAIL  ;
}

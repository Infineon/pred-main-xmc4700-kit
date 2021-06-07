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

#include "sensors_task.h"

#include "console_io.h"
#include "iot_demo_logging.h"

#include "mqtt_task.h"
#include "statistic.h"
#include "converting.h"
#include "app_error.h"

#include "DAVE.h"

#include "i2c_mux.h"
#include "spi_mux.h"
#include "LTC4332/ltc4332.h"


/* Package for MQTT */
static InfineonSensorsMessage_t xSensorsMessage;
/* Current sensor statistics and raw value buffers */
static InfineonSensorsData_t xSensorsData;


/** Handle for the Sensors Task */
TaskHandle_t xSENSORSTaskHandle = NULL;


static void prvSensorsTask( void *pvParameters );


typedef enum {
	PROCESS_IN_PROGRESS = 0,
	PROCESS_COMPLETED = 1

} SensorsProcessStatus_t;


static SensorsProcessStatus_t xSensorsProcess( InfineonSensorsData_t *pxSensorsData );


void vSensorsTaskStart( void )
{

	if( xSENSORSTaskHandle == NULL ) 
	{
		xTaskCreate( prvSensorsTask, "SENSORSTask", sensorstaskSTACK_SIZE, NULL, sensorstaskPRIORITY, &xSENSORSTaskHandle );
		configPRINTF( ("SENSORS TASK CREATE...\r\n") );

	}

}


void vSensorsTaskDelete( void )
{
    configPRINTF( ("Deleting the Sensors task") );

    if( xSENSORSTaskHandle != NULL ) 
	{
        vTaskSuspend( xSENSORSTaskHandle );
    }

    /* Delete the task */
    if( xSENSORSTaskHandle != NULL ) 
	{
        vTaskDelete( xSENSORSTaskHandle );
        xSENSORSTaskHandle = NULL;
    }

}


void prvSensorsTask( void *pvParameters )
{
	SensorsProcessStatus_t xProcessCompleteFlag = PROCESS_IN_PROGRESS;

	/* Restore serial interfaces buses, needed to stabilize */
	vSerialInterfaceRestore();

	/* Sensors power-on */
	vSensorsOn();
	vTaskDelay( 100 );

	/* SPI Extender initialization */
    bool LTC4332_bInitStatus = LTC4332_bInit();
	if( LTC4332_bInitStatus != true )
	{
		configPRINTF( ("ERROR: LTC4332_bInit\r\n") );
	}

	/* Sensors initialization */
	vSensorsPreInit();
	vSensorsInit();

	/* Delay is necessary to stabilize the sensors after power-on and initialization */
    vTaskDelay( 1000 );

    for( ;; ) 
	{
    	/* Reading data from sensors and processing */
    	xProcessCompleteFlag = xSensorsProcess( &xSensorsData );

		if( xProcessCompleteFlag && xMQTTMessageQueueHandle )
		{
			/* Converting */
			vSensorsDataToMessage( &xSensorsData, &xSensorsMessage );

			/* Don't wait, in case it is busy - skip */
			if( xQueueSend( xMQTTMessageQueueHandle, &xSensorsMessage, ( TickType_t )1 ) != pdTRUE )
			{
				configPRINTF( ("ERROR: Send Sensors Data to Message Queue\r\n") );
			}

			xProcessCompleteFlag = PROCESS_IN_PROGRESS;
		}

		vTaskDelay( 1 );
    }

}

/* Reading data in time and post-processing */
static SensorsProcessStatus_t xSensorsProcess( InfineonSensorsData_t *pxSensorsData )
{
	SensorsProcessStatus_t xRet = PROCESS_IN_PROGRESS;
	int32_t lReadError = 0;

	static uint32_t ulTick = 0;
	static TickType_t prevStamp = 0;

	/* Reading data from sensors directly per tick */
	if( ulTick < SENSORS_VECTOR_LEN )
	{
		vSensorsRead( pxSensorsData, ulTick );
		ulTick++;
	}

	/* Perform post-processing after the vector is filled and the period time has passed */
    if( ( xTaskGetTickCount() - prevStamp ) > SEND_PERIOD_MS )
    {
    	if( prevStamp != 0 )
    	{
    		/* Read data from the buffer non-tick sensors - microphone */
    		vNonTickSensorsRead( pxSensorsData );

    		/* Check for the number of errors in read loop */
    		lReadError = lSensorsReadErrorCheck( ulTick );

    		/* Console output headline */
			if( SHOW_SENSOR_OUTPUT )
			{

				configPRINTF( ("\e[1;1H\e[2J") );
				configPRINTF( ("--------------------------------------------------\r\n") );
				configPRINTF( ("timestamp %5d\r\n", xTaskGetTickCount()) );
				configPRINTF( ("--------------------------------------------------\r\n") );

				/* delay for logging */
				vTaskDelay( 15 );
				configPRINTF( ("length = %d, sensors = %d, vector len = %d\r\n", 6, ( PARAMETERS_NUMBER ), ulTick) );
			}

			/* Calculating and console printing statistics */
			vSensorsStatCalculation( pxSensorsData, ulTick );

			/* Console output new empty line */
			if( SHOW_SENSOR_OUTPUT )
			{
				configPRINTF( ("\r\n") );
			}

			if( lReadError == 0 )
			{
				/* Checking availability of sensors before sending data */
				vSensorsAvailability( pxSensorsData );
				xRet = PROCESS_COMPLETED;
			}

    	}

    	/* Reset and start the time counter */
        ulTick = 0;
        prevStamp = xTaskGetTickCount();

    }

    return xRet;
}

/*
 * FreeRTOS V1.4.7
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

/* C Standard Library header files includes */
#include <stdlib.h>
#include <string.h>

/* FreeRTOS headers includes */
#include "FreeRTOS.h"
#include "task.h"

/* Demo headers includes */
#include "aws_demo.h"

/* AWS library includes */
#include "iot_system_init.h"
#include "iot_logging_task.h"
#include "iot_wifi.h"
#include "aws_clientcredential.h"
#include "aws_iot_network_config.h"
#include "aws_application_version.h"
#include "aws_dev_mode_key_provisioning.h"

/* Infineon Interfaces headers includes */
#include "DAVE.h"
#include "console_io.h"
#include "entropy_hardware.h"

/* Main Threads headers includes */
#include "mqtt_task.h"
#include "sensors_task.h"

/* Application Definitions headers includes */
#include "app_error.h"

/* Networking and Security headers includes */
#include "optiga/pal/pal_os_event.h"
#include "optiga/include/optiga/pal/pal_logger.h"
#include "modem/aws_nbiot.h"
#include "ism43340_wifi_io.h"
#include "get_optiga_certificate.h"

/* Hardware Peripherals headers includes */
#include "sensors.h"
#include "led.h"

/* Expanders headers includes */
#include "i2c_mux.h"
#include "spi_mux.h"

/*-----------------------------------------------------------
 * Application Mode selection define
 */
#define 	TEST_MODE 		false
/*-----------------------------------------------------------*/

/* Test headers includes */
#if TEST_MODE
#include "test_task/test_task.h"
#include "json_sensor_test/json_sensor_test.h"
#include "tle4964_test/tle4964_test.h"
#include "dps368_test/dps368_test.h"
#include "tli493d_test/tli493d_test.h"
#include "tlx4966_test/tlx4966_test.h"
#endif

/* Logging Task Defines */
#define mainLOGGING_MESSAGE_QUEUE_LENGTH    ( 15 )
#define mainLOGGING_TASK_STACK_SIZE         ( configMINIMAL_STACK_SIZE * 8 )

/* The task delay for allowing the lower priority logging task to print out WiFi
 * failure status before blocking indefinitely. */
#define mainLOGGING_WIFI_STATUS_DELAY       pdMS_TO_TICKS( 1000 )

/* The name of the devices for xApplicationDNSQueryHook */
#define mainDEVICE_NICK_NAME                "XMC4700_HVAC"

/* Firmware release version */
#define releaseFIRMWARE_VERSION				"1.2.0"

/**
 * @brief Application task startup hook for applications using WiFi. If you are not
 * using WiFi, then start network dependent applications in the vApplicationIPNetorkEventHook
 * function. If you are not using WiFi, this hook can be disabled by setting
 * configUSE_DAEMON_TASK_STARTUP_HOOK to 0.
 */
void vApplicationDaemonTaskStartupHook( void );
void vApplicationTickHook( void );

/**
 * @brief Initializes the board
 */
static void prvMiscInitialization( void );

/**
 * @brief Initializes MUXes for SPI and I2C
 */
static void prvMuxInitialization( void );

/**
 * @brief Initializes queue for board LEDs states
 */
static void prvLedsInitialization( void );

/* Ensure the FreeRTOS heap is not crossing SRAM boundaries. */
__attribute__((section("ETH_RAM"))) uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];




/**
 * @brief Application runtime entry point
 */
int main( void )
{
    /* Perform any hardware initialization that does not require the RTOS to be
     * running.  */
    prvMiscInitialization();

    /* Create tasks that are not dependent on the WiFi being initialized. */
    xLoggingTaskInitialize( mainLOGGING_TASK_STACK_SIZE,
                            tskIDLE_PRIORITY,
                            mainLOGGING_MESSAGE_QUEUE_LENGTH );

    /* Clear terminal screen */
    configPRINTF( ("\e[1;1H\e[2J") );
    configPRINTF( ("--------------------------------------------------\r\n") );
    configPRINTF( ("FW.VER. %s\r\n", releaseFIRMWARE_VERSION) );
    configPRINTF( ("--------------------------------------------------\r\n") );

    /* Initialize all hardware interfaces and GPIOs */
    DAVE_Init();

    /* Initialization of MUXes for SPI and I2C */
    prvMuxInitialization();

    /* Initialization of queue for board LEDs states */
    prvLedsInitialization();

    configPRINTF( ("Initialization misc OK\r\n") );

    /* Start the scheduler.  Initialization that requires the OS to be running,
     * including the WiFi initialization, is performed in the RTOS daemon task
     * startup hook. */
    vTaskStartScheduler();

    return 0;
}


/* PAL logger output definition */
pal_logger_t logger_console;
uint16_t pal_logger_write( void * p_logger_context, const uint8_t * p_log_data, uint32_t log_data_length )
{
	_write( 5, p_log_data, log_data_length );
	return 0;
}


/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	pal_os_event_trigger_registered_callback();
}


static void prvMiscInitialization( void )
{
    /* UART LOG console initialize */
    CONSOLE_IO_vInit();

    /* Pseudo-random number initializer */
    ENTROPY_HARDWARE_Init();
}


static void prvMuxInitialization( void )
{
    /** Declaration statuses returned by interfaces during initialization */
    bool I2C_bInitStatus = true;
    bool SPI_bInitStatus = true;

    /*
     * SPI MUX initialize
     * used by DPS310/368 Pressure Temperature sensors 3x
     */
    SPI_bInitStatus = SPI_MUX_bInit();
    if( SPI_bInitStatus != true )
    {
        configPRINTF( ("ERROR: SPI_MUX_bInit\r\n") );
    }

    /*
     * I2C MUX initialize
     * used by Optiga Trust M
     * used by DPS310/368 Pressure Temperature sensors 2x
     * used by TLI493D 3D Magnetic Hall sensors 2x
     */
    I2C_bInitStatus = I2C_MUX_bInit();
    if( I2C_bInitStatus != true )
    {
        configPRINTF( ("ERROR: I2C_MUX_bInit\r\n") );
    }
}


static void prvLedsInitialization( void )
{
    LED_STATUS_t LED_xInitStatus = LED_STATUS_SUCCESS;

    /** LED initialize */
    LED_xInitStatus = LED_xInit();
    if( LED_xInitStatus != LED_STATUS_SUCCESS )
    {
        configPRINTF( ("ERROR: LED_xInit\r\n") );
    }
}

/*-----------------------------------------------------------*/


void vApplicationDaemonTaskStartupHook( void )
{
    /* Switch on board power supply */
    vBoardOn();

#if NBIOT_ENABLED
    /* Switch on mBUS 5V power supply */
    vMBus_5V_On();
#endif

#if TEST_MODE

	/* testing FreeRTOS functional */
	vTestTaskStart();
	/* testing JSON */
 	JSON_bSensorsShortTest();
 	JSON_bSensorsFullTest();
 	/* Switch on sensors power supply */
 	vSensorsOn();
 	/* testing Sensors */
 	vSensorsInit();
 	TLI493D_bTest();
 	DPS368_bTest();
 	TLx4966_bTest();
 	TLE4964_bTest();
 	/* Switch off sensors power supply */
 	vSensorsOff();
#else

 	LED_xStatus( HEARTBEAT, START );

    taskENABLE_INTERRUPTS();

    /** Key Provisioning */
	LED_xStatus( KEY_PROV, START );

	/* Deal with the error "Failed to generate key pair" CKR_GENERAL_ERROR */
	if( vDevModeKeyProvisioning() /*== CKR_OK*/ )
	{
		LED_xStatus( KEY_PROV, SUCCESS );
	}
	else
	{
		LED_xStatus( KEY_PROV, FAILED );
		vFullReset( APP_ERROR_DEV_PROV );
	}
	/** Print OptigaTrustM Public Key Certificate 1 (IFX provisioned) to console */
	if( vGetOptigaCertificate() != CKR_OK )
	{
		configPRINTF( ("ERROR: Can't print  OptigaTrustM Public Key Certificate 1 (IFX provisioned)\r\n") );
	}

	/** Initialize the AWS Libraries system. */
	if( SYSTEM_Init() == pdPASS )
	{
		LED_xStatus( WIFI, START );
		/* Connect to network */
		if( ucNetworkInitialize() == pdPASS )
		{
			LED_xStatus( WIFI, SUCCESS );
			configPRINTF( ("Connected to the network\r\n") );
			/* Sensors Task Start inside */
			vMqttTaskStart();

		}
		else
		{
			LED_xStatus( WIFI, FAILED );
			vFullReset( APP_ERROR_NETWORK_COMM_LIB_INIT );
		}
	}
	else
	{
		vFullReset( APP_ERROR_SYSTEM_INIT );
	}

#endif

}

/*-----------------------------------------------------------*/

/**
 * @brief User defined Idle task function.
 *
 * @note Do not make any blocking operations in this function.
 */
void vApplicationIdleHook( void )
{
/**
 * Status indication
 *
 */
    /* Set default values */
    static LedMode_t xLedModes[LEDS_NUM] = { LED_STATE_OFF, LED_STATE_OFF, LED_STATE_OFF };
	static uint32_t ulLedBlinkTimes[LEDS_NUM] = { 500, 500, 500 };

	static uint32_t ulPrevLedBlinkTimes[LEDS_NUM];

	TickType_t xCurrentTick = xTaskGetTickCount();

	LedState_t xLedStateQueue;
	if( LED_xQueueReceive( &xLedStateQueue ) == LED_STATUS_SUCCESS )
	{

		if( (xLedModes[xLedStateQueue.type] != xLedStateQueue.mode) || (ulLedBlinkTimes[xLedStateQueue.type] != xLedStateQueue.blinkTime) )
		{
			xLedModes[xLedStateQueue.type] = xLedStateQueue.mode;
			ulLedBlinkTimes[xLedStateQueue.type] = xLedStateQueue.blinkTime;
			switch( xLedStateQueue.mode )
			{
				case LED_STATE_OFF:
					LED_vOff( xLedStateQueue.type );
					break;
				case LED_STATE_ON:
				case LED_STATE_BLINK:
					LED_vOn( xLedStateQueue.type );
					break;
				default:
					break;
			}
		}
	}

	for( LedType_t i = 0; i < LEDS_NUM; i++ )
	{
		if( xCurrentTick - ulPrevLedBlinkTimes[i] > ulLedBlinkTimes[i] )
		{
			ulPrevLedBlinkTimes[i] = xCurrentTick;
			if( xLedModes[i] == LED_STATE_BLINK )
			{
				LED_vToggle( i );
			}
		}
	}

}
/*-----------------------------------------------------------*/

/**
* @brief User defined application hook to process names returned by the DNS server.
*/
#if ( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 )
    BaseType_t xApplicationDNSQueryHook( const char * pcName )
    {
        /* FIX ME. If necessary, update to applicable DNS name lookup actions. */

        BaseType_t xReturn;

        /* Determine if a name lookup is for this node.  Two names are given
         * to this node: that returned by pcApplicationHostnameHook() and that set
         * by mainDEVICE_NICK_NAME. */
        if( strcmp( pcName, pcApplicationHostnameHook() ) == 0 )
        {
            xReturn = pdPASS;
        }
        else if( strcmp( pcName, mainDEVICE_NICK_NAME ) == 0 )
        {
            xReturn = pdPASS;
        }
        else
        {
            xReturn = pdFAIL;
        }

        return xReturn;
    }
	
#endif /* if ( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 ) */
/*-----------------------------------------------------------*/

/**
 * @brief User defined assertion call. This function is plugged into configASSERT.
 * See FreeRTOSConfig.h to define configASSERT to something different.
 */
void vAssertCalled(const char * pcFile,
	uint32_t ulLine)
{
    /* FIX ME. If necessary, update to applicable assertion routine actions. */

	const uint32_t ulLongSleep = 1000UL;
	volatile uint32_t ulBlockVariable = 0UL;
	volatile char * pcFileName = (volatile char *)pcFile;
	volatile uint32_t ulLineNumber = ulLine;

	(void)pcFileName;
	(void)ulLineNumber;

	printf("vAssertCalled %s, %ld\n", pcFile, (long)ulLine);
	fflush(stdout);

	/* Setting ulBlockVariable to a non-zero value in the debugger will allow
	* this function to be exited. */
	taskDISABLE_INTERRUPTS();
	{
		while (ulBlockVariable == 0UL)
		{
			vTaskDelay( pdMS_TO_TICKS( ulLongSleep ) );
		}
	}
	taskENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

/**
 * @brief User defined application hook need by the FreeRTOS-Plus-TCP library.
 */
#if ( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 ) || ( ipconfigDHCP_REGISTER_HOSTNAME == 1 )
    const char * pcApplicationHostnameHook(void)
    {
        /* FIX ME: If necessary, update to applicable registration name. */

        /* This function will be called during the DHCP: the machine will be registered 
         * with an IP address plus this name. */
        return clientcredentialIOT_THING_NAME;
    }

#endif

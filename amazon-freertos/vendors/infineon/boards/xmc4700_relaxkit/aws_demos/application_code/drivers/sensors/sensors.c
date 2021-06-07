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

#include "sensors.h"

#include "DAVE.h"

#include "LTC4332/ltc4332.h"
#include "TLV493D/corelib/tlv493d.h"
#include "DPS368/dps368_api.h"
#include "IM69D/im69d_api.h"
#include "TLE496x/tle496x_api.h"
#include "TLx493D/tli493d_api.h"
#include "TLI4971/tli4971.h"
#include "TLE4997/tle4997_api.h"

#include "statistic.h"
#include "aws_nbiot.h"

/* Parameter HEADERS for printing to log */
static const char * pcFeatures[PARAMETERS_NUMBER] = {

/* Temperature and Pressure sensors */

#if( SENSOR_DPS368_1_ENABLE > 0 )
    "DPS368 Temperature #1",
    "DPS368 Pressure #1",
#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )
    "DPS368 Temperature #2",
    "DPS368 Pressure #2",
#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )
    "DPS368 Temperature #3",
    "DPS368 Pressure #3",
#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )
    "DPS368 Temperature #4",
    "DPS368 Pressure #4",
#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )
    "DPS368 Temperature #5",
    "DPS368 Pressure #5",
#endif

/* Magnetic Current sensors */

#if( SENSOR_TLI4971_1_ENABLE > 0 )
    "TLI4971 Current #1",
#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )
    "TLI4971 Current #2",
#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )
    "TLI4971 Current #3",
#endif

/* Linear Hall sensors */

#if( SENSOR_TLE4997_1_ENABLE > 0 )
    "TLE4997 Linear Hall #1",
#endif

#if( SENSOR_TLE4997_2_ENABLE > 0 )
    "TLE4997 Linear Hall #2",
#endif

/* Hall sensors */

#if( SENSOR_TLE4964_1_ENABLE > 0 )
    "TLE4964 Hall #1",
#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )
    "TLE4961-3K Hall #1",
#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )
    "TLE4913 Hall #1",
#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )
    "TLE4961-1K Hall #1",
#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )
    "TLI4966G Double Hall SPEED #1",
	"TLI4966G Double Hall DIR #1",
#endif

/* Microphone */

#if( SENSOR_IM69D130_ENABLE > 0 )
    "IM69D Microphone #1",
#endif

/* 3D Magnetic sensors */

#if( SENSOR_TLI493D_1_ENABLE > 0 )
    "TLI493D Magnetic X-Axis #1",
	"TLI493D Magnetic Y-Axis #1",
	"TLI493D Magnetic Z-Axis #1",
#endif

};


static SensorContext_t xSensor[SENSORS_NUMBER];

/* Global error number of initialize or read sensors operations in sensors.c file
 * When power turned on, is equal to the number of sensors ( NOT NUMBER OF SENSORS PARAMETERS! )
 */
static uint8_t ucErrorNumber;

void vBoardOn( void )
{
	configPRINTF( ("SWITCHING BOARD ON...\r\n") );
	DIGITAL_IO_SetOutputLow( &BOARD_POWER );
}


void vBoardOff( void )
{
	configPRINTF( ("SWITCHING BOARD OFF...\r\n") );
	DIGITAL_IO_SetOutputHigh( &BOARD_POWER );
}


void vSensorsOn( void )
{
	configPRINTF( ("SWITCHING SENSORS ON...\r\n") );
	DIGITAL_IO_SetOutputLow( &SENSORS_POWER );

	vTaskDelay( 1 );
	vCsPowerSafety( 1 );
}


void vSensorsOff( void )
{
	vCsPowerSafety( 0 );
	vTaskDelay( 1 );

	configPRINTF( ("SWITCHING SENSORS OFF...\r\n") );
	DIGITAL_IO_SetOutputHigh( &SENSORS_POWER );
}


void vSensorsPreInit( void )
{
    /* Initially believe that all predefined sensors are not initialized */
    ucErrorNumber = SENSORS_NUMBER;

     /* All predefined sensors in configure are On by default, uninitialized and without error */
    for( uint8_t i = 0; i < SENSORS_NUMBER; i++ )
    {
        xSensor[i].bOn = true;
        xSensor[i].bInited = false;
        xSensor[i].ucErrorCount = NONE_ATTEMPT;
    }
}


void vSensorsInit( void )
{
    configPRINTF(("INITIALIZING SENSORS...\r\n"));

    /* Perform the cycle until all sensors are initialized, or until the number of unsuccessful attempts ends */
    while( ucErrorNumber > 0 )
    {

/* Initialize DPS368 Temperature and Pressure sensors */

#if( SENSOR_DPS368_1_ENABLE > 0 )

        /* If the sensor has not yet been initialized, try to initialize */
        if( xSensor[DPS368_1].bOn == true && xSensor[DPS368_1].bInited != true )
        {
            /* Both temperature and pressure are initialized, so we specify one thing */
            if( DPS368_lInit( &xSensor[DPS368_1].pvCxt, DPS368_API_SENSOR_ID_1 ) < 0 )
            {
                /* An error has occurred, increase the number of attempts to initialize this sensor */
                xSensor[DPS368_1].ucErrorCount++;
            }
            else 
            {
                /* Set flag that the sensor has been initialized */
                xSensor[DPS368_1].bInited = true;
                /* Clear up attempt count if sensor has been initialized */
                xSensor[DPS368_1].ucErrorCount = NONE_ATTEMPT;
                /* Decrease the number of not-initialized sensors from the predefined scope */
                --ucErrorNumber;
            }
        }
#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )

        if( xSensor[DPS368_2].bOn == true && xSensor[DPS368_2].bInited != true )
        {
            if( DPS368_lInit( &xSensor[DPS368_2].pvCxt, DPS368_API_SENSOR_ID_2 ) < 0 )
            {
                xSensor[DPS368_2].ucErrorCount++;
            }
            else 
            {
                xSensor[DPS368_2].bInited = true;
                xSensor[DPS368_2].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;
            }
        }
#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )

        if( xSensor[DPS368_3].bOn == true && xSensor[DPS368_3].bInited != true )
        {
            if( DPS368_lInit( &xSensor[DPS368_3].pvCxt, DPS368_API_SENSOR_ID_3 ) < 0 )
            {
                xSensor[DPS368_3].ucErrorCount++;
            }
            else 
            {
                xSensor[DPS368_3].bInited = true;
                xSensor[DPS368_3].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;
            }
        }
#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )

        if( xSensor[DPS368_4].bOn == true && xSensor[DPS368_4].bInited != true )
        {
            if( DPS368_lInit( &xSensor[DPS368_4].pvCxt, DPS368_API_SENSOR_ID_4 ) < 0 )
            {
                xSensor[DPS368_4].ucErrorCount++;
            }
            else 
            {
                xSensor[DPS368_4].bInited = true;
                xSensor[DPS368_4].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;
            }
        }
#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )

        if( xSensor[DPS368_5].bOn == true && xSensor[DPS368_5].bInited != true )
        {
            if( DPS368_lInit( &xSensor[DPS368_5].pvCxt, DPS368_API_SENSOR_ID_5 ) < 0 )
            {
                xSensor[DPS368_5].ucErrorCount++;
            }
            else 
            {
                xSensor[DPS368_5].bInited = true;
                xSensor[DPS368_5].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;
            }
        }
#endif

/* Initialize TLI4971 Magnetic Current sensors */

#if( SENSOR_TLI4971_1_ENABLE > 0 )

        if( xSensor[TLI4971_1].bOn == true && xSensor[TLI4971_1].bInited != true )
        {
        	 if( TLI4971_lInit( &xSensor[TLI4971_1].pvCxt, TLI4971_SENSOR_ID_1 ) < 0 )
             {
                 xSensor[TLI4971_1].ucErrorCount++;
             }
             else
             {
                 xSensor[TLI4971_1].bInited = true;
                 xSensor[TLI4971_1].ucErrorCount = NONE_ATTEMPT;
                 --ucErrorNumber;
             }
        }
#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )

        if( xSensor[TLI4971_2].bOn == true && xSensor[TLI4971_2].bInited != true )
        {
        	 if( TLI4971_lInit( &xSensor[TLI4971_2].pvCxt, TLI4971_SENSOR_ID_2 ) < 0 )
             {
                 xSensor[TLI4971_2].ucErrorCount++;
             }
             else
             {
                 xSensor[TLI4971_2].bInited = true;
                 xSensor[TLI4971_2].ucErrorCount = NONE_ATTEMPT;
                 --ucErrorNumber;
             }
        }
#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )

        if( xSensor[TLI4971_3].bOn == true && xSensor[TLI4971_3].bInited != true )
        {
        	 if( TLI4971_lInit( &xSensor[TLI4971_3].pvCxt, TLI4971_SENSOR_ID_3 ) < 0 )
             {
                 xSensor[TLI4971_3].ucErrorCount++;
             }
             else
             {
                 xSensor[TLI4971_3].bInited = true;
                 xSensor[TLI4971_3].ucErrorCount = NONE_ATTEMPT;
                 --ucErrorNumber;
             }
        }
#endif

/* Initialize TLE4997E2 Linear Hall sensors */

#if( SENSOR_TLE4997_1_ENABLE > 0 )

        if( xSensor[TLE4997_1].bOn == true && xSensor[TLE4997_1].bInited != true )
        {
        	 if( TLE4997_lInit( &xSensor[TLE4997_1].pvCxt, TLE4997_API_SENSOR_ID_ONE ) < 0 )
             {
                 xSensor[TLE4997_1].ucErrorCount++;
             }
             else
             {
                 xSensor[TLE4997_1].bInited = true;
                 xSensor[TLE4997_1].ucErrorCount = NONE_ATTEMPT;
                 --ucErrorNumber;
             }
        }
#endif

#if( SENSOR_TLE4997_2_ENABLE > 0 )

        if( xSensor[TLE4997_2].bOn == true && xSensor[TLE4997_2].bInited != true )
        {
        	 if( TLE4997_lInit( &xSensor[TLE4997_2].pvCxt, TLE4997_API_SENSOR_ID_TWO ) < 0 )
             {
                 xSensor[TLE4997_2].ucErrorCount++;
             }
             else
             {
                 xSensor[TLE4997_2].bInited = true;
                 xSensor[TLE4997_2].ucErrorCount = NONE_ATTEMPT;
                 --ucErrorNumber;
             }
        }
#endif

/* Initialize TLE49XX Hall sensors */

#if( SENSOR_TLE4964_1_ENABLE > 0 )

        if( xSensor[TLE4964_1].bOn == true && xSensor[TLE4964_1].bInited != true )
        {
            if( TLE496x_lInit( &xSensor[TLE4964_1].pvCxt, TLE496x_API_SENSOR_ID_ONE ) < 0 )
            {
                xSensor[TLE4964_1].ucErrorCount++;
            }
            else 
            {
                xSensor[TLE4964_1].bInited = true;
                xSensor[TLE4964_1].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;  
            }
        }
#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )

        if( xSensor[TLE49613K_1].bOn == true && xSensor[TLE49613K_1].bInited != true )
        {
            if( TLE496x_lInit( &xSensor[TLE49613K_1].pvCxt, TLE496x_API_SENSOR_ID_TWO ) < 0 )
            {
                xSensor[TLE49613K_1].ucErrorCount++;
            }
            else 
            {
                xSensor[TLE49613K_1].bInited = true;
                xSensor[TLE49613K_1].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;
            }
        }
#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )

        if( xSensor[TLE4913_1].bOn == true && xSensor[TLE4913_1].bInited != true )
        {
            if( TLE496x_lInit( &xSensor[TLE4913_1].pvCxt, TLE496x_API_SENSOR_ID_THREE ) < 0 )
            {
                xSensor[TLE4913_1].ucErrorCount++;
            }
            else
            {
                xSensor[TLE4913_1].bInited = true;
                xSensor[TLE4913_1].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;
            }
        }
#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )

        if( xSensor[TLE49611K_1].bOn == true && xSensor[TLE49611K_1].bInited != true )
        {
            if( TLE496x_lInit( &xSensor[TLE49611K_1].pvCxt, TLE496x_API_SENSOR_ID_FOUR ) < 0 )
            {
                xSensor[TLE49611K_1].ucErrorCount++;
            }
            else
            {
                xSensor[TLE49611K_1].bInited = true;
                xSensor[TLE49611K_1].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;
            }
        }
#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )

        if( xSensor[TLI4966G_1].bOn == true && xSensor[TLI4966G_1].bInited != true )
        {
            if( TLE496x_lInit( &xSensor[TLI4966G_1].pvCxt, TLE496x_API_SENSOR_ID_FIVE ) < 0 )
            {
                xSensor[TLI4966G_1].ucErrorCount++;
            }
            else 
            {
                xSensor[TLI4966G_1].bInited = true;
                xSensor[TLI4966G_1].ucErrorCount = NONE_ATTEMPT;
                --ucErrorNumber;
            }
        }
#endif

/* Initialize IM69D130 Microphone */

#if( SENSOR_IM69D130_ENABLE > 0 )

        if( xSensor[IM69D_1].bOn == true && xSensor[IM69D_1].bInited != true )
        {
        	 if( IM69D_lInit( &xSensor[IM69D_1].pvCxt, IM69D_API_MIC_ID_LEFT ) < 0 )
             {
                 xSensor[IM69D_1].ucErrorCount++;
             }
             else
             {
                 xSensor[IM69D_1].bInited = true;
                 xSensor[IM69D_1].ucErrorCount = NONE_ATTEMPT;
                 --ucErrorNumber;
             }
        }
#endif

/* Initialize TLI493D 3D magnetic sensor */

#if( SENSOR_TLI493D_1_ENABLE > 0 )

        if( xSensor[TLI493D_1].bOn == true && xSensor[TLI493D_1].bInited != true )
        {
            if( TLI493D_lInit( &xSensor[TLI493D_1].pvCxt, TLI493D_API_SENSOR_ID_ONE ) < 0 )
            {
                xSensor[TLI493D_1].ucErrorCount++;
            }
            else 
            {
                xSensor[TLI493D_1].bInited = true;
                xSensor[TLI493D_1].ucErrorCount = NONE_ATTEMPT;
				--ucErrorNumber;
            }
        }
#endif

        /* Check for errors */
        for( uint8_t i = 0; i < SENSORS_NUMBER; i++ )
        {
            if( xSensor[i].bOn && ( xSensor[i].bInited != true ) )
            {
            	if( xSensor[i].ucErrorCount < ATTEMPTS_LIMIT_EXCEEDED )
				{
            		/* Do sensors re-power only once for sensors cycle initialization */
            		vSensorsRestore( APP_ERROR_SENSORS_INIT );
				}
            	else
                {
            		xSensor[i].bOn = false;
            		xSensor[i].ucErrorCount = NONE_ATTEMPT;
            		--ucErrorNumber;
                }
            } 
        }

    } /* while */

} /* vSensorsInit */


/* Read non-background sensors, using tick count */
void vSensorsRead( InfineonSensorsData_t *pxSensorsData, uint32_t ulTicks )
{

/* Read DPS368 Temperature and Pressure */

#if( SENSOR_DPS368_1_ENABLE > 0 )

    if( xSensor[DPS368_1].bInited && xSensor[DPS368_1].bOn )
    {
    	DPS368Data_t xData;
        if( DPS368_lGetData( xSensor[DPS368_1].pvCxt, &xData ) == 0 )
        {
			pxSensorsData->fSensorsVector.vector[DPS368_TEMP_1][ulTicks] = xData.fTemperature;
			pxSensorsData->fSensorsVector.vector[DPS368_PRESS_1][ulTicks] = xData.fPressure;
#if( SENSOR_DPS368_1_ENABLE > 1 )
			configPRINTF( ("DPS368-1 Temp: %.2f, Press: %.2f\r\n", xData.fTemperature, xData.fPressure) );
#endif
        }
        else
        {
            xSensor[DPS368_1].ucErrorCount++;
        }

    }

#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )

    if( xSensor[DPS368_2].bInited && xSensor[DPS368_2].bOn )
    {
    	DPS368Data_t xData;
        if( DPS368_lGetData( xSensor[DPS368_2].pvCxt, &xData ) == 0 )
        {
        	pxSensorsData->fSensorsVector.vector[DPS368_TEMP_2][ulTicks] = xData.fTemperature;
        	pxSensorsData->fSensorsVector.vector[DPS368_PRESS_2][ulTicks] = xData.fPressure;
#if( SENSOR_DPS368_2_ENABLE > 1 )
        	configPRINTF( ("DPS368-2 Temp: %.2f, Press: %.2f\r\n", xData.fTemperature, xData.fPressure) );
#endif
        }
        else
        {
            xSensor[DPS368_2].ucErrorCount++;
        }

    }

#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )

    if( xSensor[DPS368_3].bInited && xSensor[DPS368_3].bOn )
    {
    	DPS368Data_t xData;
        if( DPS368_lGetData( xSensor[DPS368_3].pvCxt, &xData ) == 0 )
        {
        	pxSensorsData->fSensorsVector.vector[DPS368_TEMP_3][ulTicks] = xData.fTemperature;
        	pxSensorsData->fSensorsVector.vector[DPS368_PRESS_3][ulTicks] = xData.fPressure;
#if( SENSOR_DPS368_3_ENABLE > 1 )
        	configPRINTF( ("DPS368-3 Temp: %.2f, Press: %.2f\r\n", xData.fTemperature, xData.fPressure) );
#endif
        }
        else
        {
            xSensor[DPS368_3].ucErrorCount++;
        }

    }

#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )

    if( xSensor[DPS368_4].bInited && xSensor[DPS368_4].bOn )
    {
    	DPS368Data_t xData;
        if( DPS368_lGetData( xSensor[DPS368_4].pvCxt, &xData ) == 0 )
        {
            pxSensorsData->fSensorsVector.vector[DPS368_TEMP_4][ulTicks] = xData.fTemperature;
            pxSensorsData->fSensorsVector.vector[DPS368_PRESS_4][ulTicks] = xData.fPressure;
#if( SENSOR_DPS368_4_ENABLE > 1 )
            configPRINTF( ("DPS368-4 Temp: %.2f, Press: %.2f\r\n", xData.fTemperature, xData.fPressure) );
#endif
        }
        else
        {
            xSensor[DPS368_4].ucErrorCount++;
        }

    }

#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )

    if( xSensor[DPS368_5].bInited && xSensor[DPS368_5].bOn )
    {
        DPS368Data_t xData;
        if( DPS368_lGetData( xSensor[DPS368_5].pvCxt, &xData ) == 0 )
        {
            pxSensorsData->fSensorsVector.vector[DPS368_TEMP_5][ulTicks] = xData.fTemperature;
            pxSensorsData->fSensorsVector.vector[DPS368_PRESS_5][ulTicks] = xData.fPressure;
#if( SENSOR_DPS368_5_ENABLE > 1 )
            configPRINTF( ("DPS368-5 Temp: %.2f, Press: %.2f\r\n", xData.fTemperature, xData.fPressure) );
#endif
        }
        else
        {
            xSensor[DPS368_5].ucErrorCount++;
        }

    }

#endif

/* Read TLI4971 Current */

#if( SENSOR_TLI4971_1_ENABLE > 0 )

	if( xSensor[TLI4971_1].bInited && xSensor[TLI4971_1].bOn )
	{
		TLI4971Data_t xData;
		if( TLI4971_lGetData( xSensor[TLI4971_1].pvCxt, &xData ) == 0 )
		{
			pxSensorsData->fSensorsVector.vector[TLI4971_CURRENT_1][ulTicks] = xData.fCurrent;
#if( SENSOR_TLI4971_1_ENABLE > 1 )
			configPRINTF( ("TLI4971-1: %.4f\r\n", xData.fCurrent) );
#endif
		}
		else
		{
			xSensor[TLI4971_1].ucErrorCount++;
		}
	}

#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )

	if( xSensor[TLI4971_2].bInited && xSensor[TLI4971_2].bOn )
	{
		TLI4971Data_t xData;
		if( TLI4971_lGetData( xSensor[TLI4971_2].pvCxt, &xData ) == 0 )
		{
			pxSensorsData->fSensorsVector.vector[TLI4971_CURRENT_2][ulTicks] = xData.fCurrent;
#if( SENSOR_TLI4971_2_ENABLE > 1 )
			configPRINTF( ("TLI4971-2: %.4f\r\n", xData.fCurrent) );
#endif
		}
		else
		{
			xSensor[TLI4971_2].ucErrorCount++;
		}
	}

#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )

	if( xSensor[TLI4971_3].bInited && xSensor[TLI4971_3].bOn )
	{
		TLI4971Data_t xData;
		if( TLI4971_lGetData( xSensor[TLI4971_3].pvCxt, &xData ) == 0 )
		{
			pxSensorsData->fSensorsVector.vector[TLI4971_CURRENT_3][ulTicks] = xData.fCurrent;
#if( SENSOR_TLI4971_3_ENABLE > 1 )
			configPRINTF( ("TLI4971-3: %.4f\r\n", xData.fCurrent) );
#endif
		}
		else
		{
			xSensor[TLI4971_3].ucErrorCount++;
		}
	}

#endif

/* Read TLE4997 Hall */

#if( SENSOR_TLE4997_1_ENABLE > 0 )

	if( xSensor[TLE4997_1].bInited && xSensor[TLE4997_1].bOn )
	{
		TLE4997Data_t xData;
		if( TLE4997_lGetData( xSensor[TLE4997_1].pvCxt, &xData ) == 0 )
		{
			pxSensorsData->fSensorsVector.vector[TLE4997_LINEAR_HALL_1][ulTicks] = xData.fHallRatiometry;
#if( SENSOR_TLE4997_1_ENABLE > 1 )
			configPRINTF( ("TLE4997-1: %.2f\r\n", xData.fHallRatiometry) );
#endif
		}
		else
		{
			 xSensor[TLE4997_1].ucErrorCount++;
		}
	}

#endif

#if( SENSOR_TLE4997_2_ENABLE > 0 )

	if( xSensor[TLE4997_2].bInited && xSensor[TLE4997_2].bOn )
	{
		TLE4997Data_t xData;
		if( TLE4997_lGetData( xSensor[TLE4997_2].pvCxt, &xData ) == 0 )
		{
			pxSensorsData->fSensorsVector.vector[TLE4997_LINEAR_HALL_2][ulTicks] = xData.fHallRatiometry;
#if( SENSOR_TLE4997_2_ENABLE > 1 )
			configPRINTF( ("TLE4997-2: %.2f\r\n", xData.fHallRatiometry) );
#endif
		}
		else
		{
			 xSensor[TLE4997_2].ucErrorCount++;
		}
	}

#endif

/* Read TLx49xx Hall */

#if( SENSOR_TLE4964_1_ENABLE > 0 )

    if( xSensor[TLE4964_1].bInited && xSensor[TLE4964_1].bOn )
    {
    	TLE496xData_t xData;
        if( TLE496x_lGetData( xSensor[TLE4964_1].pvCxt, &xData ) == 0 )
        {
            pxSensorsData->fSensorsVector.vector[TLE4964_HALL_SWITCH_1][ulTicks] = (float)xData.lMagneticFieldValue;
#if( SENSOR_TLE4964_1_ENABLE > 1 )
            configPRINTF( ("TLE4964-1: %.0f\r\n", (float)xData.lMagneticFieldValue) );
#endif
        }
        else
        {
             xSensor[TLE4964_1].ucErrorCount++;
        }
    }

#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )

    if( xSensor[TLE49613K_1].bInited && xSensor[TLE49613K_1].bOn )
    {
    	TLE496xData_t xData;
        if( TLE496x_lGetData( xSensor[TLE49613K_1].pvCxt, &xData ) == 0 )
        {
            pxSensorsData->fSensorsVector.vector[TLE49613K_HALL_LATCH_1][ulTicks] = (float)xData.lMagneticFieldValue;
#if( SENSOR_TLE4961_3K_1_ENABLE > 1 )
            configPRINTF( ("TLE4961-3K-1: %.0f\r\n", (float)xData.lMagneticFieldValue) );
#endif
        }
        else
        {
            xSensor[TLE49613K_1].ucErrorCount++;
        }
    }

#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )

    if( xSensor[TLE4913_1].bInited && xSensor[TLE4913_1].bOn )
    {
    	TLE496xData_t xData;
        if( TLE496x_lGetData( xSensor[TLE4913_1].pvCxt, &xData ) == 0 )
        {
            pxSensorsData->fSensorsVector.vector[TLE4913_HALL_SWITCH_1][ulTicks] = (float)xData.lMagneticFieldValue;
#if( SENSOR_TLE4913_1_ENABLE > 1 )
            configPRINTF( ("TLE4913-1: %.0f\r\n", (float)xData.lMagneticFieldValue) );
#endif
        }
        else
        {
             xSensor[TLE4913_1].ucErrorCount++;
        }
    }

#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )

    if( xSensor[TLE49611K_1].bInited && xSensor[TLE49611K_1].bOn )
    {
    	TLE496xData_t xData;
        if( TLE496x_lGetData( xSensor[TLE49611K_1].pvCxt, &xData ) == 0 )
        {
            pxSensorsData->fSensorsVector.vector[TLE49611K_HALL_LATCH_1][ulTicks] = (float)xData.lMagneticFieldValue;
#if( SENSOR_TLE4961_1K_1_ENABLE > 1 )
            configPRINTF( ("TLE49611K-1: %.0f\r\n", (float)xData.lMagneticFieldValue) );
#endif
        }
        else
        {
            xSensor[TLE49611K_1].ucErrorCount++;
        }
    }

#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )

    if( xSensor[TLI4966G_1].bInited && xSensor[TLI4966G_1].bOn )
    {
        static TLE496xData_t xData;
        static int32_t lRet = -1;

        /* update values once in ~1second */
        if( ulTicks == 0 || lRet != 0 )
        {
        	lRet = TLE496x_lGetData( xSensor[TLI4966G_1].pvCxt, &xData );
            if( lRet == 0 )
            {
                pxSensorsData->fSensorsVector.vector[TLI4966G_DOUBLE_HALL_SPEED_1][ulTicks] = (float)xData.fSpeed;
                pxSensorsData->fSensorsVector.vector[TLI4966G_DOUBLE_HALL_DIR_1][ulTicks] = (float)xData.lDirection;
#if( SENSOR_TLI4966_1_ENABLE > 1 )
                configPRINTF( ("TLI4966G-1: Speed %.0f, Dir %.0f\r\n", (float)xData.fSpeed, (float)xData.lDirection) );
#endif
            }
            else
            {
                xSensor[TLI4966G_1].ucErrorCount++;
            }
        }
        else
        {
            pxSensorsData->fSensorsVector.vector[TLI4966G_DOUBLE_HALL_SPEED_1][ulTicks] = (float)xData.fSpeed;
            pxSensorsData->fSensorsVector.vector[TLI4966G_DOUBLE_HALL_DIR_1][ulTicks] = (float)xData.lDirection;
        }
    }

#endif

/* Read TLI493D Magnetic */

#if( SENSOR_TLI493D_1_ENABLE > 0 )

    if( xSensor[TLI493D_1].bInited && xSensor[TLI493D_1].bOn )
    {
    	TLI493DData_t xData;
        if( TLI493D_lGetData( xSensor[TLI493D_1].pvCxt, &xData ) == 0 )
        {
            pxSensorsData->fSensorsVector.vector[TLI493D_MAGNETIC_X_1][ulTicks] = xData.fMagneticFieldIntensityX;
            pxSensorsData->fSensorsVector.vector[TLI493D_MAGNETIC_Y_1][ulTicks] = xData.fMagneticFieldIntensityY;
            pxSensorsData->fSensorsVector.vector[TLI493D_MAGNETIC_Z_1][ulTicks] = xData.fMagneticFieldIntensityZ;
#if( SENSOR_TLI493D_1_ENABLE > 1 )
            configPRINTF( ("TLI493D-1 x: %.4f, y: %.4f, z: %.4f\r\n", xData.fMagneticFieldIntensityX, xData.fMagneticFieldIntensityY, xData.fMagneticFieldIntensityZ) );
#endif
        }
        else
        {
            xSensor[TLI493D_1].ucErrorCount++;
        }
    }

#endif

} /* vSensorsRead */


/* Read sensors, using background mode */
void vNonTickSensorsRead( InfineonSensorsData_t *pxSensorsData )
{

/* Get data from I2S Microphone */

#if( SENSOR_IM69D130_ENABLE > 0 )

    if( xSensor[IM69D_1].bInited && xSensor[IM69D_1].bOn )
    {
        if( IM69D_lGetData( pxSensorsData, IM69D_MIC_1, SENSORS_VECTOR_LEN ) == 0 )
        {
#if( SENSOR_IM69D130_ENABLE > 1 )
        	configPRINTF( ("IM69D-1\r\n") );
#warning "'loggingDONT_BLOCK' should be set to non-zero value (about 15ms) because a big amount of data will be sent over the serial port"
        	IM69D_vPrintData( pxSensorsData, IM69D_MIC_1, SENSORS_VECTOR_LEN );
#endif
        }
        else
        {
            xSensor[IM69D_1].ucErrorCount++;
        }
    }

#endif

} /* vNonTickSensorsRead */


int32_t lSensorsReadErrorCheck( uint32_t ulTicks )
{
	int32_t lRet = 0;

	uint32_t ulRefErrorNumber;

	/* Reference number of sensor errors is taken as half the vector length, but not less than one */
	if( ulTicks > ATTEMPTS_LIMIT_EXCEEDED )
	{
		ulRefErrorNumber = ulTicks / 3;
	}
	else
	{
		ulRefErrorNumber = ONE_ATTEMPT;
	}

    /* check for errors */
    for( uint8_t i = 0; i < SENSORS_NUMBER; i++ )
    {
        if( xSensor[i].bInited && xSensor[i].bOn )
        {
            /* Resetting non-working sensors */
            if( xSensor[i].ucErrorCount >= ulRefErrorNumber )
            {
                xSensor[i].bInited = false;
                xSensor[i].ucErrorCount = NONE_ATTEMPT;
                ++ucErrorNumber;
            }
            else
            {
            	xSensor[i].ucErrorCount = NONE_ATTEMPT;
            }
        }
    }
    /* If at least one sensor is reset, we perform sensor(s) recovery */
    if( ucErrorNumber > 0 )
    {
        /* Do sensors recovery */
        vSensorsRestore( APP_ERROR_SENSORS_READ );
        lRet = -1;
    }

    return lRet;
}


void vSensorsDeInit( void )
{
    configPRINTF( ("DEINITIALIZING SENSORS...\r\n") );

/* DeInit DPS368 Temperature and Pressure sensors */

#if( SENSOR_DPS368_1_ENABLE > 0 )

    if( xSensor[DPS368_1].bOn && (xSensor[DPS368_1].bInited != true) )
    {
    	DPS368_vDeInit( &xSensor[DPS368_1].pvCxt );
    }

#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )

    if( xSensor[DPS368_2].bOn && (xSensor[DPS368_2].bInited != true) )
	{
		DPS368_vDeInit( &xSensor[DPS368_2].pvCxt );
	}

#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )

    if( xSensor[DPS368_3].bOn && (xSensor[DPS368_3].bInited != true) )
	{
		DPS368_vDeInit( &xSensor[DPS368_3].pvCxt );
	}

#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )

    if( xSensor[DPS368_4].bOn && (xSensor[DPS368_4].bInited != true) )
	{
		DPS368_vDeInit( &xSensor[DPS368_4].pvCxt );
	}

#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )

    if( xSensor[DPS368_5].bOn && (xSensor[DPS368_5].bInited != true) )
	{
		DPS368_vDeInit( &xSensor[DPS368_5].pvCxt );
	}

#endif

/* DeInit TLI4971 Magnetic Current sensors */

#if( SENSOR_TLI4971_1_ENABLE > 0 )

    if( xSensor[TLI4971_1].bOn && (xSensor[TLI4971_1].bInited != true) )
	{
    	TLI4971_vDeInit( &xSensor[TLI4971_1].pvCxt );
	}

#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )

    if( xSensor[TLI4971_2].bOn && (xSensor[TLI4971_2].bInited != true) )
	{
    	TLI4971_vDeInit( &xSensor[TLI4971_2].pvCxt );
	}

#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )

    if( xSensor[TLI4971_3].bOn && (xSensor[TLI4971_3].bInited != true) )
	{
    	TLI4971_vDeInit( &xSensor[TLI4971_3].pvCxt );
	}

#endif

/* DeInit TLE4997E2 Linear Hall sensors */

#if( SENSOR_TLE4997_1_ENABLE > 0 )

    if( xSensor[TLE4997_1].bOn && (xSensor[TLE4997_1].bInited != true) )
	{
    	TLE4997_vDeInit( &xSensor[TLE4997_1].pvCxt );
	}

#endif

#if( SENSOR_TLE4997_2_ENABLE > 0 )

    if( xSensor[TLE4997_2].bOn && (xSensor[TLE4997_2].bInited != true) )
	{
    	TLE4997_vDeInit( &xSensor[TLE4997_2].pvCxt );
	}

#endif

/* DeInit TLE4964 Hall sensors */

#if( SENSOR_TLE4964_1_ENABLE > 0 )

    if( xSensor[TLE4964_1].bOn && (xSensor[TLE4964_1].bInited != true) )
	{
    	TLE496x_vDeInit( &xSensor[TLE4964_1].pvCxt );
	}

#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )

    if( xSensor[TLE49613K_1].bOn && (xSensor[TLE49613K_1].bInited != true) )
	{
    	TLE496x_vDeInit( &xSensor[TLE49613K_1].pvCxt );
	}

#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )

    if( xSensor[TLE4913_1].bOn && (xSensor[TLE4913_1].bInited != true) )
	{
    	TLE496x_vDeInit( &xSensor[TLE4913_1].pvCxt );
	}

#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )

    if( xSensor[TLE49611K_1].bOn && (xSensor[TLE49611K_1].bInited != true) )
	{
    	TLE496x_vDeInit( &xSensor[TLE49611K_1].pvCxt );
	}

#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )

    if( xSensor[TLI4966G_1].bOn && (xSensor[TLI4966G_1].bInited != true) )
	{
    	TLE496x_vDeInit( &xSensor[TLI4966G_1].pvCxt );
	}

#endif

/* DeInit IM69D130 Microphone */

#if( SENSOR_IM69D130_ENABLE > 0 )

    if( xSensor[IM69D_1].bOn && (xSensor[IM69D_1].bInited != true) )
	{
    	IM69D_vDeInit();
	}

#endif

/* DeInit TLI493D 3D magnetic sensor */

#if( SENSOR_TLI493D_1_ENABLE > 0 )

    if( xSensor[TLI493D_1].bOn && (xSensor[TLI493D_1].bInited != true) )
	{
    	TLI493D_vDeInit( &xSensor[TLI493D_1].pvCxt );
	}

#endif

} /* vSensorsDeInit */


void vSensorsStatCalculation( InfineonSensorsData_t *pxSensorsData, uint32_t ulTicks )
{

/** Delay vTaskDelay( 20 ) is used as time needed for logTask to receive and print log message
	    number of messages are huge and some could be lost without a delay */

/* Statistic DPS368 Temperature and Pressure */

#if( SENSOR_DPS368_1_ENABLE > 0 )

    if( xSensor[DPS368_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_TEMP_1]) ); }
        STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_TEMP_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_TEMP_1]), &(pxSensorsData->Min.stat_buf[DPS368_TEMP_1]), &(pxSensorsData->Mean.stat_buf[DPS368_TEMP_1]), &(pxSensorsData->Rms.stat_buf[DPS368_TEMP_1]), &(pxSensorsData->StdDev.stat_buf[DPS368_TEMP_1]), &(pxSensorsData->Variance.stat_buf[DPS368_TEMP_1]) );

        vTaskDelay( 20 );

    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_PRESS_1]) ); }
	    STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_PRESS_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_PRESS_1]), &(pxSensorsData->Min.stat_buf[DPS368_PRESS_1]), &(pxSensorsData->Mean.stat_buf[DPS368_PRESS_1]), &(pxSensorsData->Rms.stat_buf[DPS368_PRESS_1]), &(pxSensorsData->StdDev.stat_buf[DPS368_PRESS_1]), &(pxSensorsData->Variance.stat_buf[DPS368_PRESS_1]) );

	    vTaskDelay( 20 );
	}

#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )

    if( xSensor[DPS368_2].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_TEMP_2]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_TEMP_2][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_TEMP_2]), &(pxSensorsData->Min.stat_buf[DPS368_TEMP_2]), &(pxSensorsData->Mean.stat_buf[DPS368_TEMP_2]), &(pxSensorsData->Rms.stat_buf[DPS368_TEMP_2]), &(pxSensorsData->StdDev.stat_buf[DPS368_TEMP_2]), &(pxSensorsData->Variance.stat_buf[DPS368_TEMP_2]) );

    	vTaskDelay( 20 );

    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_PRESS_2]) ); }
		STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_PRESS_2][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_PRESS_2]), &(pxSensorsData->Min.stat_buf[DPS368_PRESS_2]), &(pxSensorsData->Mean.stat_buf[DPS368_PRESS_2]), &(pxSensorsData->Rms.stat_buf[DPS368_PRESS_2]), &(pxSensorsData->StdDev.stat_buf[DPS368_PRESS_2]), &(pxSensorsData->Variance.stat_buf[DPS368_PRESS_2]) );

		vTaskDelay( 20 );
	}

#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )

    if( xSensor[DPS368_3].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_TEMP_3]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_TEMP_3][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_TEMP_3]), &(pxSensorsData->Min.stat_buf[DPS368_TEMP_3]), &(pxSensorsData->Mean.stat_buf[DPS368_TEMP_3]), &(pxSensorsData->Rms.stat_buf[DPS368_TEMP_3]), &(pxSensorsData->StdDev.stat_buf[DPS368_TEMP_3]), &(pxSensorsData->Variance.stat_buf[DPS368_TEMP_3]) );

    	vTaskDelay( 20 );

    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_PRESS_3]) ); }
		STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_PRESS_3][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_PRESS_3]), &(pxSensorsData->Min.stat_buf[DPS368_PRESS_3]), &(pxSensorsData->Mean.stat_buf[DPS368_PRESS_3]), &(pxSensorsData->Rms.stat_buf[DPS368_PRESS_3]), &(pxSensorsData->StdDev.stat_buf[DPS368_PRESS_3]), &(pxSensorsData->Variance.stat_buf[DPS368_PRESS_3]) );

		vTaskDelay( 20 );
	}

#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )

    if( xSensor[DPS368_4].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_TEMP_4]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_TEMP_4][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_TEMP_4]), &(pxSensorsData->Min.stat_buf[DPS368_TEMP_4]), &(pxSensorsData->Mean.stat_buf[DPS368_TEMP_4]), &(pxSensorsData->Rms.stat_buf[DPS368_TEMP_4]), &(pxSensorsData->StdDev.stat_buf[DPS368_TEMP_4]), &(pxSensorsData->Variance.stat_buf[DPS368_TEMP_4]) );

    	vTaskDelay( 20 );

    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_PRESS_4]) ); }
		STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_PRESS_4][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_PRESS_4]), &(pxSensorsData->Min.stat_buf[DPS368_PRESS_4]), &(pxSensorsData->Mean.stat_buf[DPS368_PRESS_4]), &(pxSensorsData->Rms.stat_buf[DPS368_PRESS_4]), &(pxSensorsData->StdDev.stat_buf[DPS368_PRESS_4]), &(pxSensorsData->Variance.stat_buf[DPS368_PRESS_4]) );

		vTaskDelay( 20 );
	}

#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )

    if( xSensor[DPS368_5].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_TEMP_5]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_TEMP_5][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_TEMP_5]), &(pxSensorsData->Min.stat_buf[DPS368_TEMP_5]), &(pxSensorsData->Mean.stat_buf[DPS368_TEMP_5]), &(pxSensorsData->Rms.stat_buf[DPS368_TEMP_5]), &(pxSensorsData->StdDev.stat_buf[DPS368_TEMP_5]), &(pxSensorsData->Variance.stat_buf[DPS368_TEMP_5]) );

    	vTaskDelay( 20 );

    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[DPS368_PRESS_5]) ); }
		STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[DPS368_PRESS_5][0]), ulTicks, &(pxSensorsData->Max.stat_buf[DPS368_PRESS_5]), &(pxSensorsData->Min.stat_buf[DPS368_PRESS_5]), &(pxSensorsData->Mean.stat_buf[DPS368_PRESS_5]), &(pxSensorsData->Rms.stat_buf[DPS368_PRESS_5]), &(pxSensorsData->StdDev.stat_buf[DPS368_PRESS_5]), &(pxSensorsData->Variance.stat_buf[DPS368_PRESS_5]) );

		vTaskDelay( 20 );
	}

#endif

/* Statistic TLI4971 Magnetic Current sensors */

#if( SENSOR_TLI4971_1_ENABLE > 0 )

    if( xSensor[TLI4971_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLI4971_CURRENT_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLI4971_CURRENT_1][0]), SENSORS_VECTOR_LEN, &(pxSensorsData->Max.stat_buf[TLI4971_CURRENT_1]), &(pxSensorsData->Min.stat_buf[TLI4971_CURRENT_1]), &(pxSensorsData->Mean.stat_buf[TLI4971_CURRENT_1]), &(pxSensorsData->Rms.stat_buf[TLI4971_CURRENT_1]), &(pxSensorsData->StdDev.stat_buf[TLI4971_CURRENT_1]), &(pxSensorsData->Variance.stat_buf[TLI4971_CURRENT_1]) );

    	vTaskDelay( 20 );
    }

#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )

    if( xSensor[TLI4971_2].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLI4971_CURRENT_2]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLI4971_CURRENT_2][0]), SENSORS_VECTOR_LEN, &(pxSensorsData->Max.stat_buf[TLI4971_CURRENT_2]), &(pxSensorsData->Min.stat_buf[TLI4971_CURRENT_2]), &(pxSensorsData->Mean.stat_buf[TLI4971_CURRENT_2]), &(pxSensorsData->Rms.stat_buf[TLI4971_CURRENT_2]), &(pxSensorsData->StdDev.stat_buf[TLI4971_CURRENT_2]), &(pxSensorsData->Variance.stat_buf[TLI4971_CURRENT_2]) );

    	vTaskDelay( 20 );
    }

#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )

    if( xSensor[TLI4971_3].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLI4971_CURRENT_3]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLI4971_CURRENT_3][0]), SENSORS_VECTOR_LEN, &(pxSensorsData->Max.stat_buf[TLI4971_CURRENT_3]), &(pxSensorsData->Min.stat_buf[TLI4971_CURRENT_3]), &(pxSensorsData->Mean.stat_buf[TLI4971_CURRENT_3]), &(pxSensorsData->Rms.stat_buf[TLI4971_CURRENT_3]), &(pxSensorsData->StdDev.stat_buf[TLI4971_CURRENT_3]), &(pxSensorsData->Variance.stat_buf[TLI4971_CURRENT_3]) );

    	vTaskDelay( 20 );
    }

#endif

/* Statistic TLE4997E2 Linear Hall sensor */

#if( SENSOR_TLE4997_1_ENABLE > 0 )

    if( xSensor[TLE4997_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLE4997_LINEAR_HALL_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLE4997_LINEAR_HALL_1][0]), SENSORS_VECTOR_LEN, &(pxSensorsData->Max.stat_buf[TLE4997_LINEAR_HALL_1]), &(pxSensorsData->Min.stat_buf[TLE4997_LINEAR_HALL_1]), &(pxSensorsData->Mean.stat_buf[TLE4997_LINEAR_HALL_1]), &(pxSensorsData->Rms.stat_buf[TLE4997_LINEAR_HALL_1]), &(pxSensorsData->StdDev.stat_buf[TLE4997_LINEAR_HALL_1]), &(pxSensorsData->Variance.stat_buf[TLE4997_LINEAR_HALL_1]) );

    	vTaskDelay( 20 );
    }

#endif

#if( SENSOR_TLE4997_2_ENABLE > 0 )

    if( xSensor[TLE4997_2].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLE4997_LINEAR_HALL_2]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLE4997_LINEAR_HALL_2][0]), SENSORS_VECTOR_LEN, &(pxSensorsData->Max.stat_buf[TLE4997_LINEAR_HALL_2]), &(pxSensorsData->Min.stat_buf[TLE4997_LINEAR_HALL_2]), &(pxSensorsData->Mean.stat_buf[TLE4997_LINEAR_HALL_2]), &(pxSensorsData->Rms.stat_buf[TLE4997_LINEAR_HALL_2]), &(pxSensorsData->StdDev.stat_buf[TLE4997_LINEAR_HALL_2]), &(pxSensorsData->Variance.stat_buf[TLE4997_LINEAR_HALL_2]) );

    	vTaskDelay( 20 );
    }

#endif

/* Statistic TLE4964 Hall sensors */

#if( SENSOR_TLE4964_1_ENABLE > 0 )

    if( xSensor[TLE4964_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLE4964_HALL_SWITCH_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLE4964_HALL_SWITCH_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLE4964_HALL_SWITCH_1]), &(pxSensorsData->Min.stat_buf[TLE4964_HALL_SWITCH_1]), &(pxSensorsData->Mean.stat_buf[TLE4964_HALL_SWITCH_1]), &(pxSensorsData->Rms.stat_buf[TLE4964_HALL_SWITCH_1]), &(pxSensorsData->StdDev.stat_buf[TLE4964_HALL_SWITCH_1]), &(pxSensorsData->Variance.stat_buf[TLE4964_HALL_SWITCH_1]) );

    	vTaskDelay( 20 );
    }

#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )

    if( xSensor[TLE49613K_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLE49613K_HALL_LATCH_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLE49613K_HALL_LATCH_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLE49613K_HALL_LATCH_1]), &(pxSensorsData->Min.stat_buf[TLE49613K_HALL_LATCH_1]), &(pxSensorsData->Mean.stat_buf[TLE49613K_HALL_LATCH_1]), &(pxSensorsData->Rms.stat_buf[TLE49613K_HALL_LATCH_1]), &(pxSensorsData->StdDev.stat_buf[TLE49613K_HALL_LATCH_1]), &(pxSensorsData->Variance.stat_buf[TLE49613K_HALL_LATCH_1]) );

    	vTaskDelay( 20 );
    }

#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )

    if( xSensor[TLE4913_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLE4913_HALL_SWITCH_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLE4913_HALL_SWITCH_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLE4913_HALL_SWITCH_1]), &(pxSensorsData->Min.stat_buf[TLE4913_HALL_SWITCH_1]), &(pxSensorsData->Mean.stat_buf[TLE4913_HALL_SWITCH_1]), &(pxSensorsData->Rms.stat_buf[TLE4913_HALL_SWITCH_1]), &(pxSensorsData->StdDev.stat_buf[TLE4913_HALL_SWITCH_1]), &(pxSensorsData->Variance.stat_buf[TLE4913_HALL_SWITCH_1]) );

    	vTaskDelay( 20 );
    }

#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )

    if( xSensor[TLE49611K_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLE49611K_HALL_LATCH_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLE49611K_HALL_LATCH_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLE49611K_HALL_LATCH_1]), &(pxSensorsData->Min.stat_buf[TLE49611K_HALL_LATCH_1]), &(pxSensorsData->Mean.stat_buf[TLE49611K_HALL_LATCH_1]), &(pxSensorsData->Rms.stat_buf[TLE49611K_HALL_LATCH_1]), &(pxSensorsData->StdDev.stat_buf[TLE49611K_HALL_LATCH_1]), &(pxSensorsData->Variance.stat_buf[TLE49611K_HALL_LATCH_1]) );

    	vTaskDelay( 20 );
    }

#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )

    if( xSensor[TLI4966G_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLI4966G_DOUBLE_HALL_SPEED_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLI4966G_DOUBLE_HALL_SPEED_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLI4966G_DOUBLE_HALL_SPEED_1]), &(pxSensorsData->Min.stat_buf[TLI4966G_DOUBLE_HALL_SPEED_1]), &(pxSensorsData->Mean.stat_buf[TLI4966G_DOUBLE_HALL_SPEED_1]), &(pxSensorsData->Rms.stat_buf[TLI4966G_DOUBLE_HALL_SPEED_1]), &(pxSensorsData->StdDev.stat_buf[TLI4966G_DOUBLE_HALL_SPEED_1]), &(pxSensorsData->Variance.stat_buf[TLI4966G_DOUBLE_HALL_SPEED_1]) );

    	vTaskDelay( 20 );

    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLI4966G_DOUBLE_HALL_DIR_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLI4966G_DOUBLE_HALL_DIR_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLI4966G_DOUBLE_HALL_DIR_1]), &(pxSensorsData->Min.stat_buf[TLI4966G_DOUBLE_HALL_DIR_1]), &(pxSensorsData->Mean.stat_buf[TLI4966G_DOUBLE_HALL_DIR_1]), &(pxSensorsData->Rms.stat_buf[TLI4966G_DOUBLE_HALL_DIR_1]), &(pxSensorsData->StdDev.stat_buf[TLI4966G_DOUBLE_HALL_DIR_1]), &(pxSensorsData->Variance.stat_buf[TLI4966G_DOUBLE_HALL_DIR_1]) );

    	vTaskDelay( 20 );
    }

#endif

/* Statistic IM69D130 Microphone */

#if( SENSOR_IM69D130_ENABLE > 0 )

    if( xSensor[IM69D_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[IM69D_MIC_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[IM69D_MIC_1][0]), SENSORS_VECTOR_LEN, &(pxSensorsData->Max.stat_buf[IM69D_MIC_1]), &(pxSensorsData->Min.stat_buf[IM69D_MIC_1]), &(pxSensorsData->Mean.stat_buf[IM69D_MIC_1]), &(pxSensorsData->Rms.stat_buf[IM69D_MIC_1]), &(pxSensorsData->StdDev.stat_buf[IM69D_MIC_1]), &(pxSensorsData->Variance.stat_buf[IM69D_MIC_1]) );

    	vTaskDelay( 20 );
    }

#endif

/* Statistic TLI493D 3D magnetic sensor */

#if( SENSOR_TLI493D_1_ENABLE > 0 )

    if( xSensor[TLI493D_1].bOn )
    {
    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLI493D_MAGNETIC_X_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLI493D_MAGNETIC_X_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLI493D_MAGNETIC_X_1]), &(pxSensorsData->Min.stat_buf[TLI493D_MAGNETIC_X_1]), &(pxSensorsData->Mean.stat_buf[TLI493D_MAGNETIC_X_1]), &(pxSensorsData->Rms.stat_buf[TLI493D_MAGNETIC_X_1]), &(pxSensorsData->StdDev.stat_buf[TLI493D_MAGNETIC_X_1]), &(pxSensorsData->Variance.stat_buf[TLI493D_MAGNETIC_X_1]) );

    	vTaskDelay( 20 );

    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLI493D_MAGNETIC_Y_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLI493D_MAGNETIC_Y_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLI493D_MAGNETIC_Y_1]), &(pxSensorsData->Min.stat_buf[TLI493D_MAGNETIC_Y_1]), &(pxSensorsData->Mean.stat_buf[TLI493D_MAGNETIC_Y_1]), &(pxSensorsData->Rms.stat_buf[TLI493D_MAGNETIC_Y_1]), &(pxSensorsData->StdDev.stat_buf[TLI493D_MAGNETIC_Y_1]), &(pxSensorsData->Variance.stat_buf[TLI493D_MAGNETIC_Y_1]) );

    	vTaskDelay( 20 );

    	if( SHOW_SENSOR_OUTPUT ) { configPRINTF( ("\r\n%s: ", pcFeatures[TLI493D_MAGNETIC_Z_1]) ); }
    	STAT_vCalcAndPrint( &(pxSensorsData->fSensorsVector.vector[TLI493D_MAGNETIC_Z_1][0]), ulTicks, &(pxSensorsData->Max.stat_buf[TLI493D_MAGNETIC_Z_1]), &(pxSensorsData->Min.stat_buf[TLI493D_MAGNETIC_Z_1]), &(pxSensorsData->Mean.stat_buf[TLI493D_MAGNETIC_Z_1]), &(pxSensorsData->Rms.stat_buf[TLI493D_MAGNETIC_Z_1]), &(pxSensorsData->StdDev.stat_buf[TLI493D_MAGNETIC_Z_1]), &(pxSensorsData->Variance.stat_buf[TLI493D_MAGNETIC_Z_1]) );

    	vTaskDelay( 20 );
    }

#endif

} /* vSensorsStatCalculation */

/* Сheck the availability of the sensors to be included in the package */
void vSensorsAvailability( InfineonSensorsData_t *pxSensorsData )
{
	/* Translation sensor availability */
	for( uint8_t i = 0; i < SENSORS_NUMBER; i++ )
	{
		pxSensorsData->bSensorsOn.on_buf[i] = xSensor[i].bOn;
	}
}

/* Reset secure element Optiga TrustM */
void vOptigaReset( void )
{
	configPRINTF( ("SWITCHING OPTIGA RESET...\r\n") );
	DIGITAL_IO_SetOutputLow( &OPTIGA_RESET );
	vTaskDelay( 100 );
	DIGITAL_IO_SetOutputHigh( &OPTIGA_RESET );
}

/** Restore I2C0 bus without use NVIC_SystemReset */
void I2C_MASTER_0_vRestore( void )
{
	/* Disable SDA and SCL output pin functions */
	I2C_MASTER_DisableIO( &I2C_MASTER_0 );

	/* Invalidate the internal transmit buffer */
	XMC_USIC_CH_SetTransmitBufferStatus( I2C_MASTER_0.channel, XMC_USIC_CH_TBUF_STATUS_SET_IDLE );

	I2C_MASTER_AbortTransmit( &I2C_MASTER_0 );
	I2C_MASTER_AbortReceive( &I2C_MASTER_0 );

	vTaskDelay( 100 );

	/* Re-enable the SDA and SCL output pin functions following the recovery sequence */
	I2C_MASTER_EnableIO( &I2C_MASTER_0 );

	I2C_MASTER_Init( &I2C_MASTER_0 );
}

/** Restore SPI0 bus without use NVIC_SystemReset */
void SPI_MASTER_0_vRestore( void )
{
	/* Invalidate the internal transmit buffer */
	XMC_USIC_CH_SetTransmitBufferStatus( SPI_MASTER_0.channel, XMC_USIC_CH_TBUF_STATUS_SET_IDLE );

	SPI_MASTER_AbortTransmit( &SPI_MASTER_0 );
	SPI_MASTER_AbortReceive( &SPI_MASTER_0 );

	vTaskDelay( 100 );

	SPI_MASTER_Init( &SPI_MASTER_0 );
}

/** Restore SPI and I2C bus */
void vSerialInterfaceRestore( void )
{
	I2C_MASTER_0_vRestore();
	SPI_MASTER_0_vRestore();
}

/* Safe power setting LTC4332 CS pins */
void vCsPowerSafety( uint8_t ucState )
{
	XMC_GPIO_MODE_t xGpioMode;

    /* After sensors power-on */
    if( ucState == 1 )
    {
    	xGpioMode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
    }
    /* Before sensors power-off */
    else
    {
    	xGpioMode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN;
    }

    XMC_GPIO_SetMode( LTC_CS.gpio_port, LTC_CS.gpio_pin, xGpioMode );
    XMC_GPIO_SetMode( DPS368_CS1.gpio_port, DPS368_CS1.gpio_pin, xGpioMode );
    XMC_GPIO_SetMode( DPS368_CS2.gpio_port, DPS368_CS2.gpio_pin, xGpioMode );
    XMC_GPIO_SetMode( DPS368_CS3.gpio_port, DPS368_CS3.gpio_pin, xGpioMode );
}

/* Power off and processor core reboot */
void vFullReset( AppError_t xErrorReason )
{
	/** switch reset */
	configPRINTF( ("RESETTING SYSTEM...ERROR NUMBER = %d\r\n", (uint8_t)xErrorReason) );

	vOptigaReset();

	vSensorsOff();
#if NBIOT_ENABLED
    vMBus_5V_Off();
#endif
	vBoardOff();

	vTaskDelay( 1000 );
	NVIC_SystemReset();
}

/* Trying to restore communication with the sensors if a failure occurs */
void vSensorsRestore( AppError_t xErrorReason )
{
	/** trying to restore sensors */
	configPRINTF( ("RESETTING SENSORS...ERROR NUMBER = %d\r\n", (uint8_t)xErrorReason) );

	if( xErrorReason == APP_ERROR_SENSORS_READ )
	{
		for( uint8_t i = 0; i < SENSORS_NUMBER; i++ )
		{
			if( xSensor[i].bInited && xSensor[i].bOn )
			{
				xSensor[i].bInited = false;
				xSensor[i].ucErrorCount = NONE_ATTEMPT;
				++ucErrorNumber;
			}
		}
		vSensorsDeInit();
		LTC4332_vDeInit();
		vSensorsOff();
	}

	vTaskDelay( 100 );
	/** delay inside optiga_reset */
	vOptigaReset();
	vTaskDelay( 100 );
	vSerialInterfaceRestore();

	if( xErrorReason == APP_ERROR_SENSORS_READ )
	{
		vSensorsOn();
		vTaskDelay( 100 );
		LTC4332_bInit();
		vSensorsInit();
		vTaskDelay( 100 );
	}
}

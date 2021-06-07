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
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "converting.h"

#include "statistic.h"
#include "sensors.h"
#include "app_error.h"
#include "float_to_string.h"


void vSensorsDataToMessage( InfineonSensorsData_t *pxSensorsData, InfineonSensorsMessage_t *pxSensorsMessage )
{

    StatData_t *pxSensorsStat[] = {
#if( SENSOR_DPS368_1_ENABLE > 0 )
    		&pxSensorsMessage->fDPS368Temperature_1,
			&pxSensorsMessage->fDPS368Pressure_1,
#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )
			&pxSensorsMessage->fDPS368Temperature_2,
			&pxSensorsMessage->fDPS368Pressure_2,
#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )
			&pxSensorsMessage->fDPS368Temperature_3,
			&pxSensorsMessage->fDPS368Pressure_3,
#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )
			&pxSensorsMessage->fDPS368Temperature_4,
			&pxSensorsMessage->fDPS368Pressure_4,
#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )
			&pxSensorsMessage->fDPS368Temperature_5,
			&pxSensorsMessage->fDPS368Pressure_5,
#endif

#if( SENSOR_TLI4971_1_ENABLE > 0 )
			&pxSensorsMessage->fTLI4971Current_1,
#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )
			&pxSensorsMessage->fTLI4971Current_2,
#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )
			&pxSensorsMessage->fTLI4971Current_3,
#endif

#if( SENSOR_TLE4997_1_ENABLE > 0 )
			&pxSensorsMessage->fTLE4997LinearHall_1,
#endif

#if( SENSOR_TLE4964_1_ENABLE > 0 )
			&pxSensorsMessage->fTLE4964Hall_1,
#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )
			&pxSensorsMessage->fTLE49613kHall_1,
#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )
			&pxSensorsMessage->fTLE4913Hall_1,
#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )
			&pxSensorsMessage->fTLE49611kHall_1,
#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )
			&pxSensorsMessage->fTLI4966gDoubleHall_Speed_1,
			&pxSensorsMessage->fTLI4966gDoubleHall_Dir_1,
#endif

#if( SENSOR_IM69D130_ENABLE > 0 )
			&pxSensorsMessage->fIM69dMic_1,
#endif

#if( SENSOR_TLI493D_1_ENABLE > 0 )
			&pxSensorsMessage->fTLI493dMagnetic_X_1,
			&pxSensorsMessage->fTLI493dMagnetic_Y_1,
			&pxSensorsMessage->fTLI493dMagnetic_Z_1,
#endif

    };

    bool *pbSensorsOn[] = {
#if( SENSOR_DPS368_1_ENABLE > 0 )
    		 &pxSensorsMessage->bDPS368On_1,
#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )
    		 &pxSensorsMessage->bDPS368On_2,
#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )
    		 &pxSensorsMessage->bDPS368On_3,
#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )
    		 &pxSensorsMessage->bDPS368On_4,
#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )
    		 &pxSensorsMessage->bDPS368On_5,
#endif

#if( SENSOR_TLI4971_1_ENABLE > 0 )
			 &pxSensorsMessage->bTLI4971On_1,
#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )
			 &pxSensorsMessage->bTLI4971On_2,
#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )
			 &pxSensorsMessage->bTLI4971On_3,
#endif

#if( SENSOR_TLE4997_1_ENABLE > 0 )
			 &pxSensorsMessage->bTLE4997On_1,
#endif

#if( SENSOR_TLE4964_1_ENABLE > 0 )
			 &pxSensorsMessage->bTLE4964On_1,
#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )
			 &pxSensorsMessage->bTLE49613KOn_1,
#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )
			 &pxSensorsMessage->bTLE4913On_1,
#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )
			 &pxSensorsMessage->bTLE49611KOn_1,
#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )
			 &pxSensorsMessage->bTLI4966gOn_1,
#endif

#if( SENSOR_IM69D130_ENABLE > 0 )
			 &pxSensorsMessage->bIM69dOn_1,
#endif

#if( SENSOR_TLI493D_1_ENABLE > 0 )
			 &pxSensorsMessage->bTLI493dOn_1,
#endif

    };


    for( int i = 0; i < SENSORS_NUMBER; ++i )
    {
    	*pbSensorsOn[i] = pxSensorsData->bSensorsOn.on_buf[i];
    }

    for( int i = 0; i < PARAMETERS_NUMBER; ++i )
    {
    	pxSensorsStat[i]->fMin = pxSensorsData->Min.stat_buf[i];
    	pxSensorsStat[i]->fMax = pxSensorsData->Max.stat_buf[i];
    	pxSensorsStat[i]->fMean = pxSensorsData->Mean.stat_buf[i];
    	pxSensorsStat[i]->fRMS = pxSensorsData->Rms.stat_buf[i];
    	pxSensorsStat[i]->fStdDev = pxSensorsData->StdDev.stat_buf[i];
    }

    memcpy( pxSensorsMessage->fIM69dMicSpectra_1.data, pxSensorsData->fMicBuffer.mic_fft_buf, sizeof( pxSensorsMessage->fIM69dMicSpectra_1.data ) );
    memcpy( pxSensorsMessage->fTLE4997HallSpectra_1.data, pxSensorsData->fHallBuffer.adc_raw_buf, sizeof( pxSensorsMessage->fTLE4997HallSpectra_1.data ) );

}


static void prvStatDataToJSONStat( bool bSensorsOn, StatData_t *pxStatData, SensorContext_t *pxSensorCxt, JsonSensorsStatistic_t xJsonSensorStat )
{
	pxSensorCxt->pxStat->fMin = pxStatData->fMin;
	pxSensorCxt->pxStat->fMax = pxStatData->fMax;
	pxSensorCxt->pxStat->fRMS = pxStatData->fRMS;
	pxSensorCxt->pxStat->fStdDev = pxStatData->fStdDev;
	pxSensorCxt->pxStat->fMean = pxStatData->fMean;
	pxSensorCxt->pcName = pcJsonSensorsStatString[xJsonSensorStat];
	pxSensorCxt->bOn = bSensorsOn;
}


bool JSON_bGenerateToSend( InfineonSensorsMessage_t *pxSensorsMessage, char* pucJsonBuf, uint32_t ulMaxSize )
{
	bool bRet = false;

	JsonContext_t xJsonCxt;

	static const SensorContext_t xSensorCxtEmpty;
    SensorContext_t xSensorCxt = xSensorCxtEmpty;

    StatData_t xStatData;
    xSensorCxt.pxStat = &xStatData;

    while( 1 )
    {
        bRet = JSON_bCreate( &xJsonCxt, pucJsonBuf, ulMaxSize );
        if( !bRet ) break;

        prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_1, &pxSensorsMessage->fDPS368Temperature_1, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_TEMP_1 );
        bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
        if (!bRet) break;


        prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_1, &pxSensorsMessage->fDPS368Pressure_1, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_PRESS_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

        prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_2, &pxSensorsMessage->fDPS368Temperature_2, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_TEMP_2 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_2, &pxSensorsMessage->fDPS368Pressure_2, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_PRESS_2 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_3, &pxSensorsMessage->fDPS368Temperature_3, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_TEMP_3 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_3, &pxSensorsMessage->fDPS368Pressure_3, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_PRESS_3 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_4, &pxSensorsMessage->fDPS368Temperature_4, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_TEMP_4 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_4, &pxSensorsMessage->fDPS368Pressure_4, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_PRESS_4 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_5, &pxSensorsMessage->fDPS368Temperature_5, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_TEMP_5 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bDPS368On_5, &pxSensorsMessage->fDPS368Pressure_5, &xSensorCxt, JSON_STATISTIC_SENSOR_DPS368_PRESS_5 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLI4971On_1, &pxSensorsMessage->fTLI4971Current_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLI4971_CURRENT_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLI4971On_2, &pxSensorsMessage->fTLI4971Current_2, &xSensorCxt, JSON_STATISTIC_SENSOR_TLI4971_CURRENT_2 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLI4971On_3, &pxSensorsMessage->fTLI4971Current_3, &xSensorCxt, JSON_STATISTIC_SENSOR_TLI4971_CURRENT_3 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		xSensorCxt.pxFft = &pxSensorsMessage->fTLE4997HallSpectra_1;
		prvStatDataToJSONStat( pxSensorsMessage->bTLE4997On_1, &pxSensorsMessage->fTLE4997LinearHall_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLE4997_LINEAR_HALL_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( bRet == true )
		{
			xSensorCxt.pxFft = NULL;
		}
		else
		{
			break;
		}

		prvStatDataToJSONStat( pxSensorsMessage->bTLE4964On_1, &pxSensorsMessage->fTLE4964Hall_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLE4964_HALL_SWITCH_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLE49613KOn_1, &pxSensorsMessage->fTLE49613kHall_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLE49613K_HALL_LATCH_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLE4913On_1, &pxSensorsMessage->fTLE4913Hall_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLE4913_HALL_SWITCH_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLE49611KOn_1, &pxSensorsMessage->fTLE49611kHall_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLE49611K_HALL_LATCH_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLI4966gOn_1, &pxSensorsMessage->fTLI4966gDoubleHall_Speed_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLI4966G_DOUBLE_HALL_SPEED_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLI4966gOn_1, &pxSensorsMessage->fTLI4966gDoubleHall_Dir_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLI4966G_DOUBLE_HALL_DIR_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		xSensorCxt.pxFft = &pxSensorsMessage->fIM69dMicSpectra_1;
		prvStatDataToJSONStat( pxSensorsMessage->bIM69dOn_1, &pxSensorsMessage->fIM69dMic_1, &xSensorCxt, JSON_STATISTIC_SENSOR_IM69D_MIC_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( bRet == true )
		{
			xSensorCxt.pxFft = NULL;
		}
		else
		{
			break;
		}

		prvStatDataToJSONStat( pxSensorsMessage->bTLI493dOn_1, &pxSensorsMessage->fTLI493dMagnetic_X_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLI493D_MAGNETIC_X_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLI493dOn_1, &pxSensorsMessage->fTLI493dMagnetic_Y_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLI493D_MAGNETIC_Y_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

		prvStatDataToJSONStat( pxSensorsMessage->bTLI493dOn_1, &pxSensorsMessage->fTLI493dMagnetic_Z_1, &xSensorCxt, JSON_STATISTIC_SENSOR_TLI493D_MAGNETIC_Z_1 );
		bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
		if( !bRet ) break;

        bRet = JSON_bFinish( &xJsonCxt, NULL );
        if( !bRet ) break;

        bRet = true;
        break;
    }

    if( bRet )
    {
    	if( JSON_MESSAGE_PRINT )
    	{
    		 configPRINTF( ( pucJsonBuf ) );
    		 vTaskDelay( 10 );
    	}

        return true;
    }
    else
    {
        configPRINTF( ("JSON Failed") );
        return false;
    }

}


void CSV_vGenerateToSend( InfineonSensorsMessage_t *pxSensorsMessage, uint8_t* pucBuffer )
{
	int i;
    StatData_t *pxCurrentStatData[] = {
        &pxSensorsMessage->fDPS368Temperature_1,
		&pxSensorsMessage->fDPS368Pressure_1,
		&pxSensorsMessage->fDPS368Temperature_2,
		&pxSensorsMessage->fDPS368Pressure_2,
		&pxSensorsMessage->fDPS368Temperature_3,
		&pxSensorsMessage->fDPS368Pressure_3,
		&pxSensorsMessage->fDPS368Temperature_4,
		&pxSensorsMessage->fDPS368Pressure_4,
		&pxSensorsMessage->fDPS368Temperature_5,
        &pxSensorsMessage->fDPS368Pressure_5,
        &pxSensorsMessage->fTLI4971Current_1,
        &pxSensorsMessage->fTLI4971Current_2,
        &pxSensorsMessage->fTLI4971Current_3,
		&pxSensorsMessage->fTLE4997LinearHall_1,
		&pxSensorsMessage->fTLE4964Hall_1,
		&pxSensorsMessage->fTLE49613kHall_1,
		&pxSensorsMessage->fTLE4913Hall_1,
		&pxSensorsMessage->fTLE49611kHall_1,
		&pxSensorsMessage->fTLI4966gDoubleHall_Speed_1,
		&pxSensorsMessage->fTLI4966gDoubleHall_Dir_1,
		&pxSensorsMessage->fIM69dMic_1,
		&pxSensorsMessage->fTLI493dMagnetic_X_1,
		&pxSensorsMessage->fTLI493dMagnetic_Y_1,
		&pxSensorsMessage->fTLI493dMagnetic_Z_1,
    };
    for( i = 0; i < BUF_LEN( pxCurrentStatData ); ++i )
    {
        pucBuffer = STAT_pcPrintStatData( pxCurrentStatData[i], pucBuffer );
    }


    char pcFloatToStringBuffer[10];

    for( i = 0; i < BUF_LEN( pxSensorsMessage->fIM69dMicSpectra_1.data ); ++i )
    {
    	ftoa( pxSensorsMessage->fIM69dMicSpectra_1.data[i], pcFloatToStringBuffer );
        pucBuffer += sprintf( (char *)pucBuffer, "%s,", pcFloatToStringBuffer );
    }

    for( i = 0; i < BUF_LEN( pxSensorsMessage->fTLE4997HallSpectra_1.data ); ++i )
    {
    	ftoa( pxSensorsMessage->fTLE4997HallSpectra_1.data[i], pcFloatToStringBuffer );
        pucBuffer += sprintf( (char *)pucBuffer, "%s,", pcFloatToStringBuffer );
    }

    /** Erase the excessive comma at the end */
    *( pucBuffer - 1 ) = 0;
}

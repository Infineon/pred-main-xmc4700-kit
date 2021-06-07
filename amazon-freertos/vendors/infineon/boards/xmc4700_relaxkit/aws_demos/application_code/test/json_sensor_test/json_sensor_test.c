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

#include "json/json_sensor.h"
#include "converting.h"
#include "mqtt_task.h"


static char cBufferJSON[4096];
static InfineonSensorsMessage_t xSensorsMessage;


bool JSON_bSensorsShortTest( void )
{
	bool bRet = false;

	StatData_t xStat;
    JsonContext_t xJsonCxt;
    FFTData_t xFft;

    SensorContext_t xSensorCxt = { 0 };
    xSensorCxt.pxStat = &xStat;
    xSensorCxt.bOn = 1;

    while( 1 )
    {
        bRet = JSON_bCreate( &xJsonCxt, cBufferJSON, 4096 );
        if( !bRet )
        {
        	break;
        }

        xStat.fMax  = 1.0001;
        xStat.fMin  = 2.0002;
        xStat.fMean = 3.0003;
        xStat.fRMS  = 4.0004;
        xStat.fStdDev  = 5.0005;
        xStat.fVariance  = 6.0006;
        xSensorCxt.pcName = pcJsonSensorsStatString[JSON_STATISTIC_SENSOR_DPS368_TEMP_1];
        bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
        if( !bRet )
        {
        	break;
       	}

        xStat.fMax  = 11.0001;
        xStat.fMin  = 12.0002;
        xStat.fMean = 13.0003;
        xStat.fRMS  = 14.0004;
        xStat.fStdDev  = 15.0005;
        xStat.fVariance  = 16.0006;
        xSensorCxt.pcName = pcJsonSensorsStatString[JSON_STATISTIC_SENSOR_DPS368_TEMP_2];
        bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt );
        if( !bRet )
        {
        	break;
        }

        xSensorCxt.pxFft = &xFft;
        for( int i = 0; i < ( sizeof(xFft.data) / sizeof(xFft.data[0]) ); i++ )
        {
            xFft.data[i] = i;
        }
        xSensorCxt.pcName = pcJsonSensorsStatString[JSON_STATISTIC_SENSOR_TLE4997_LINEAR_HALL_1];

        bRet = JSON_bSensorAdd( &xJsonCxt, &xSensorCxt) ;
        if( !bRet )
        {
        	break;
        }

        bRet = JSON_bFinish( &xJsonCxt, NULL );
        if( !bRet )
        {
        	break;
        }

        bRet = true;
        break;
    }

    if( bRet )
    {
        configPRINT( (cBufferJSON) );
        return true;
    }
    else
    {
        configPRINT( ("JSON Short test Failed") );
        return false;
    }

}


bool JSON_bSensorsFullTest( void )
{
	bool bRet;

	bRet = JSON_bGenerateToSend( &xSensorsMessage, (char*)cBufferJSON, sizeof(cBufferJSON) );

    if( bRet )
    {
        configPRINT( (cBufferJSON) );
        return true;
    }
    else
    {
        configPRINT( ("JSON Full test Failed") );
        return false;
    }
}

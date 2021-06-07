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
#include "FreeRTOS.h"
#include "json/json_sensor.h"


static bool JSON_prvSensorFFTAdd( JsonContext_t* pxJsonCxt, SensorContext_t* pxSensorCxt );


bool JSON_bSensorAdd( JsonContext_t *pxJsonCxt, SensorContext_t *pxSensorCxt )
{
    const size_t STR_BUF_MAX = 256;
    const size_t STR_FORMAT_MAX = 64;

    if( !pxSensorCxt )
	{
    	return false;
	}
    bool bRet = false;

    char *pcStrBuf = pvPortMalloc( STR_BUF_MAX );
    char *pcStrFormat = pvPortMalloc( STR_FORMAT_MAX );

    int32_t lLen = 0;

    while( 1 )
    {
        if( ( !pcStrBuf ) || ( !pcStrFormat ) )
        {
        	bRet = false;
        	break;
        }

        bRet = JSON_bSubstringCreate( pxJsonCxt, pxSensorCxt->pcName );
        if( !bRet )
        {
        	break;
        }

        /* Sensor state */
        lLen = snprintf( pcStrBuf, STR_BUF_MAX, "%d",pxSensorCxt->bOn );
        if( ( lLen <= 0 ) || ( lLen >= STR_BUF_MAX ) )
        {
        	break;
        }
        bRet = JSON_bStringAdd( pxJsonCxt, JSON_SENSOR_ON_STRING, pcStrBuf );
        if( !bRet )
		{
        	break;
		}

        if( pxSensorCxt->bOn )
        {
            /* Sensor statistic */
            if( pxSensorCxt->pxStat )
            {
                int32_t lLen = snprintf( pcStrFormat, STR_FORMAT_MAX, "[%s,%s%s,%s%s,%s%s,%s%s,%s%s]",
                        JSON_STATISTIC_FORMAT_FLOAT,
                        JSON_STRING_SPACE, JSON_STATISTIC_FORMAT_FLOAT,
                        JSON_STRING_SPACE, JSON_STATISTIC_FORMAT_FLOAT,
                        JSON_STRING_SPACE, JSON_STATISTIC_FORMAT_FLOAT,
                        JSON_STRING_SPACE, JSON_STATISTIC_FORMAT_FLOAT,
                        JSON_STRING_SPACE, JSON_STATISTIC_FORMAT_FLOAT);
                if( ( lLen <= 0 ) || ( lLen >= STR_FORMAT_MAX ) )
                {
                	break;
                }
                lLen = snprintf( pcStrBuf, STR_BUF_MAX, pcStrFormat,
                        pxSensorCxt->pxStat->fMin, pxSensorCxt->pxStat->fMax, pxSensorCxt->pxStat->fMean, pxSensorCxt->pxStat->fRMS, pxSensorCxt->pxStat->fStdDev, pxSensorCxt->pxStat->fVariance );
                if( ( lLen <= 0 ) || ( lLen >= STR_BUF_MAX ) )
                {
                	break;
                }
                bRet = JSON_bStringAdd( pxJsonCxt, JSON_SENSOR_STAT_STRING, pcStrBuf );
            }

            /* Sensor FFT */
            if( pxSensorCxt->pxFft )
            {
                bRet = JSON_prvSensorFFTAdd( pxJsonCxt, pxSensorCxt );
            }
        }
        bRet = JSON_bSubstringFinish( pxJsonCxt );

        break;
    }

    if( pcStrBuf )
	{
    	vPortFree( pcStrBuf );
	}
    if( pcStrFormat )
    {
    	vPortFree( pcStrFormat );
    }

    return bRet;
}


static bool JSON_prvSensorFFTAdd( JsonContext_t *pxJsonCxt, SensorContext_t *pxSensorCxt )
{
    const uint32_t STR_BUF_MAX = 1024;

    if( ( !pxSensorCxt ) || ( !pxJsonCxt ) || ( !pxSensorCxt->pxFft ) )
    {
    	return false;
    }
    if( !pxSensorCxt->pxFft )
    {
    	return false;
    }

    bool bRet = true;

    char *pcStrBuf = pvPortMalloc( STR_BUF_MAX );

    char *pcPtr = &pcStrBuf[0];
    int32_t lLenFree = STR_BUF_MAX;

//    assert( (sizeof(pxSensorCxt->pxFft->data) / sizeof(pxSensorCxt->pxFft->data[0]) > JSON_STATISTIC_FFT_COUNT) );

    while( 1 )
    {
        if( !pcStrBuf )
        {
        	bRet = false;
        	break;
        }

        int32_t lLen = snprintf( pcPtr, lLenFree, "[" );
        if( ( lLen <= 0 ) || ( lLen >= lLenFree ) )
        {
        	break;
        }
        lLenFree -= lLen;
        pcPtr += lLen;

        for( uint32_t i = 0; i < JSON_STATISTIC_FFT_COUNT; ++i )
        {
            if( i )
            {
                lLen = snprintf( pcPtr, lLenFree, ",%s", JSON_STRING_SPACE );
                if( ( lLen <= 0 ) || ( lLen >= lLenFree ) )
                {
                	bRet = false;
                	break;
                }
                lLenFree -= lLen;
                pcPtr += lLen;
            }
            lLen = snprintf( pcPtr, lLenFree, "%d", pxSensorCxt->pxFft->data[i] );
            if( ( lLen <= 0 ) || ( lLen >= lLenFree ) )
            {
            	bRet = false;
            	break;
            }
            lLenFree -= lLen;
            pcPtr += lLen;
        }
        if( bRet == false )
        {
        	break;
        }

        lLen = snprintf( pcPtr, lLenFree, "]" );
        if( ( lLen <= 0 ) || ( lLen >= lLenFree ) )
        {
        	bRet = false;
        	break;
        }

        lLenFree -= lLen;
        pcPtr += lLen;

        bRet = JSON_bStringAdd( pxJsonCxt, JSON_SENSOR_FFT_STRING, pcStrBuf );
        break;
    }
    if( pcStrBuf )
    {
    	vPortFree( pcStrBuf );
    }

    return bRet;
}

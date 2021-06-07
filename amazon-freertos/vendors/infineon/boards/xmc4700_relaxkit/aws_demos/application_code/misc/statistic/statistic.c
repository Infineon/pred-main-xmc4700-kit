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
#include <math.h>

#include "DAVE.h"

#include "statistic.h"

#include "app_error.h"
#include "float_to_string.h"


static char pcTempStr[32];
/** This function calculates features from vector of vec_len and returns result thru pointers */
void STAT_vCalcAndPrint( float *pfVect, uint32_t ulVecLen, float *pfMax, float *pfMin, float *pfMean, float *pfRMS, float *pfStdDev, float *pfVariance )
{
     float fResult;
     uint32_t ulIndex;

     arm_max_f32( pfVect, ulVecLen, &fResult, &ulIndex );
     *pfMax = fResult;

     arm_min_f32( pfVect, ulVecLen, &fResult, &ulIndex );
     *pfMin = fResult;

     arm_mean_f32( pfVect, ulVecLen, &fResult );
     *pfMean = fResult;

     arm_rms_f32( pfVect, ulVecLen, &fResult );
     *pfRMS = fResult;

     arm_std_f32( pfVect, ulVecLen, &fResult );
     *pfStdDev = fResult;

     arm_var_f32( pfVect, ulVecLen, &fResult );
     *pfVariance = fResult;


    if( SHOW_SENSOR_OUTPUT )
    {
         configPRINTF( ("max=") );
         configPRINTF( ("%s,", ftoa( *pfMax, pcTempStr )) );
         configPRINTF( ("min="));
         configPRINTF( ("%s,", ftoa( *pfMin, pcTempStr )) );
         configPRINTF( ("mean="));
         configPRINTF( ("%s,", ftoa( *pfMean, pcTempStr )) );
         configPRINTF( ("rms="));
         configPRINTF( ("%s,", ftoa( *pfRMS, pcTempStr )) );
         configPRINTF( ("std="));
         configPRINTF( ("%s,", ftoa( *pfStdDev, pcTempStr )) );
         configPRINTF( ("var="));
         configPRINTF( ("%s,", ftoa( *pfVariance, pcTempStr )) );
    }
}


static char pcFloatToStringBuffer[10];
/** This function print statistic data */
uint8_t *STAT_pcPrintStatData( StatData_t *pxStatData, uint8_t *pucBuffer )
{
    int i;

    float pfStatistics[] = {
        pxStatData->fMin,
        pxStatData->fMax,
        pxStatData->fMean,
        pxStatData->fRMS,
        pxStatData->fStdDev,
		pxStatData->fVariance
    };

    for( i = 0; i < STATISTICS_NUMBER; ++i )
    {
        ftoa( pfStatistics[i], pcFloatToStringBuffer );
        pucBuffer += sprintf( (char *)pucBuffer, "%s,", pcFloatToStringBuffer );
    }

    return pucBuffer;
}

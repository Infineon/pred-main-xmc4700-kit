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

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "tle4997_api.h"
#include "fft/fft.h"

#include "DAVE.h"


int32_t TLE4997_lInit( void **ppvHandle, TLE4997SensorNumber_t xSensorNumber )
{
	int32_t lRetCode = 0;

	*ppvHandle = pvPortMalloc( sizeof(TLE4997_t) );
	if( ! (*ppvHandle) )
	{
	return -1;
	}

	TLE4997_t *pxCxt = *ppvHandle;
	pxCxt->xSensorNumber = xSensorNumber;

	switch( xSensorNumber )
	{
		case TLE4997_API_SENSOR_ID_ONE:
		{
			ADC_MEASUREMENT_ADV_StartADC( &ADC_MEASUREMENT_ADV_3 );
			/* Continuously re-trigger the scan conversion sequence for ADC sensor
			 * Valid for Autoscan enabled
			 ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_3 );
			 */
			break;

		}
		case TLE4997_API_SENSOR_ID_TWO:
		{
			break;
		}
		default:
			break;

	}

    if( lRetCode < 0)
    {
        vPortFree( *ppvHandle );
    }

	return lRetCode;
}


void TLE4997_vDeInit( void **ppvHandle )
{
	vPortFree( *ppvHandle );
}


/** Hall receive and process data */
int32_t TLE4997_lGetData( void *pvHandle, TLE4997Data_t *pxSensorData )
{
	int32_t lRet = 0;

	TLE4997_t *pxTle = pvHandle;
	uint16_t usVoutAdc = 0;

	switch( pxTle->xSensorNumber )
	{
		case TLE4997_API_SENSOR_ID_ONE:
			ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_3 );
			/* read out conversion results */
			usVoutAdc = ADC_MEASUREMENT_ADV_GetResult( &ADC_MEASUREMENT_ADV_3_Channel_AN2_Slot2_handle );
			break;
		case TLE4997_API_SENSOR_ID_TWO:
			/* read out conversion results */
			break;
		default:
			lRet = -1;
			break;
	}

	if( usVoutAdc != 0 )
	{
		pxSensorData->fHallRatiometry = (float)( (usVoutAdc / TLE4997_COEF) * 100 );
	}

	return lRet;
}


void TLE4997_vReTrigger( void )
{
	/* Continuously re-trigger the scan conversion sequence for ADC sensor */
	ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_3 );
}


/** Hall spectrum calculation */
void TLE4997_bHallSpectrum( int16_t *psHallBufferRaw, int32_t *plHallBufferFft, uint32_t ulLength )
{
	/** instance for spectra calculation */
	arm_rfft_instance_q31 xHallRfftInstance;

	arm_status xRfftInitStatus = ARM_MATH_SUCCESS;
	xRfftInitStatus = arm_rfft_init_q31( &xHallRfftInstance, BUFF_HALL_FFT_SIZE, 0, 1 );
	if( xRfftInitStatus != 0 )
	{
		configPRINTF( ("arm rfft init q31 for hall error = %d\r\n", xRfftInitStatus) );
	}

	uint16_t i;
	/* non zero value to avoid division by zero */
	int16_t lMaxHall = 100;

	for( i = 0; i < ulLength; i++ )//+=2)
	{
		if( i >= SENSORS_VECTOR_LEN )
		{
			break;
		}

		/* 12-bit ADC resolution, take half */
		psHallBufferRaw[i] = ( psHallBufferRaw[i] - 2048 ) << 4;
		if( abs(psHallBufferRaw[i]) > lMaxHall )
		{
			lMaxHall = abs( psHallBufferRaw[i] );
		}

		/* Clear imaginary part */
		//psHallBufferRaw[i+1] = 0;
	}

	/* Hanning Window Application and scale to max */
	for( i = 0; i < BUFF_HALL_FFT_SIZE; i++ )
	{
		plHallBufferFft[i] = ( psHallBufferRaw[i] * 1ll * sQ15HannWindow[i] );// * 32767 / max_hall;
	}

	int32_t *plHallTrnsfrmdSignal = (int32_t*)pvPortMalloc( ulLength );

	/* Perform real FFT */
	arm_rfft_q31( &xHallRfftInstance, plHallBufferFft, plHallTrnsfrmdSignal );

	/* Calculate magnitude for each value */
	arm_cmplx_mag_q31( plHallTrnsfrmdSignal, plHallBufferFft, BUFF_HALL_FFT_SIZE );

	/* view spectra values */
	configPRINTF( ("HALL SPECTRA = ") );
	for( i = 0; i < BUFF_HALL_FFT_SIZE / 4; i++ )
	{
		/* scale spectra to readable values */
		configPRINTF( ("%ld ", plHallBufferFft[i] >> 15) );
		vTaskDelay( 1 );

	}
	configPRINTF( ("\r\n") );

}



hall_data_t* create_hall_struct(uint16_t buff_size)
{
	hall_data_t* hall_data = (hall_data_t*)pvPortMalloc(sizeof(hall_data_t));
	hall_data->array_size = buff_size;
	hall_data->adc_hall_array = (uint16_t*)pvPortMalloc(hall_data->array_size * sizeof(uint16_t));
	memset(hall_data->adc_hall_array, 0, hall_data->array_size * sizeof(uint16_t));

	return hall_data;
}


void delete_hall_struct(hall_data_t* hall_data)
{
	vPortFree(hall_data->adc_hall_array);
	vPortFree(hall_data);
}

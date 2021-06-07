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

#include "tli4971.h"

#include "DAVE.h"


bool ll5V = false;

#ifdef ADC_RESOLUTION
	uint8_t ucAdcResol = ADC_RESOLUTION; 	/* if possible: highest possible resolution */
#else
	uint8_t ucAdcResol = 10;				/* standard for Arduino UNO */
#endif


int32_t TLI4971_lInit( void **ppvHandle, TLI4971SensorNumber_t xSensorNumber )
{
	int32_t lRetCode = 0;

	*ppvHandle = pvPortMalloc( sizeof(TLI4971_t) );
	if( ! (*ppvHandle) )
	{
		return -1;
	}

	TLI4971_t *pxCxt = *ppvHandle;
	pxCxt->xSensorNumber = xSensorNumber;

	switch( xSensorNumber )
	{
		case TLI4971_SENSOR_ID_1:
		{
			ADC_MEASUREMENT_ADV_StartADC( &ADC_MEASUREMENT_ADV_0 );
			/* Continuously re-trigger the scan conversion sequence for ADC sensor
			 * Valid for Autoscan enabled
			 ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_0 );
			 */
			break;

		}
		case TLI4971_SENSOR_ID_2:
		{
			ADC_MEASUREMENT_ADV_StartADC( &ADC_MEASUREMENT_ADV_1 );
			/* Continuously re-trigger the scan conversion sequence for ADC sensor
			 * Valid for Autoscan enabled
			 ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_1 );
			 */
			break;
		}
		case TLI4971_SENSOR_ID_3:
		{
			ADC_MEASUREMENT_ADV_StartADC( &ADC_MEASUREMENT_ADV_2 );
			/* Continuously re-trigger the scan conversion sequence for ADC sensor
			 * Valid for Autoscan enabled
			 ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_2 );
			 */
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


void TLI4971_vDeInit( void **ppvHandle )
{
	vPortFree( *ppvHandle );
}


/** Current TLI4971 receive and process data */
int32_t TLI4971_lGetData( void *pvHandle, TLI4971Data_t *pxSensorData )
{
	int32_t lRet = 0;

	TLI4971_t *pxTli = pvHandle;

	float fCurrent;
	float fVref = VREFs;
	float fMeas = FSR120 * 2.0;
	float fVdd = ll5V ? (float)5000.0 : (float)3300.0;
	float fResol = powf( 2.0, (float)ucAdcResol );

	float fCoef = fMeas / ( fVdd / fResol );

	/* read out conversion results */
	uint16_t usAdcVal = 0;

	switch( pxTli->xSensorNumber )
	{
		case TLI4971_SENSOR_ID_1:
			ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_0 );
			/* read out conversion results */
			usAdcVal = ADC_MEASUREMENT_ADV_GetResult( &ADC_MEASUREMENT_ADV_0_Channel_AN1_Slot1_handle );
			break;
		case TLI4971_SENSOR_ID_2:
			ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_1 );
			/* read out conversion results */
			usAdcVal = ADC_MEASUREMENT_ADV_GetResult( &ADC_MEASUREMENT_ADV_1_Channel_AN1_Slot2_handle );
			break;
		case TLI4971_SENSOR_ID_3:
			ADC_MEASUREMENT_ADV_SoftwareTrigger( &ADC_MEASUREMENT_ADV_2 );
			/* read out conversion results */
			usAdcVal = ADC_MEASUREMENT_ADV_GetResult( &ADC_MEASUREMENT_ADV_2_Channel_AN2_Slot1_handle );
			break;
		default:
			lRet = -1;
			break;
	}

	//configPRINTF( ("VOUT = %d\r\n", usAdcVal) );
	__NOP();
	fCurrent = (float)usAdcVal;
	__NOP();
	/* multiply with 5000 mV or 3300 mV depending on supply voltage of MCU */
	fCurrent *= fVdd;
	__NOP();
	fCurrent /= fResol;
	__NOP();
	fCurrent -= fVref;
	__NOP();
	fCurrent /= fCoef;
	__NOP();

	pxSensorData->fCurrent = (float)fCurrent;

	return lRet;
}

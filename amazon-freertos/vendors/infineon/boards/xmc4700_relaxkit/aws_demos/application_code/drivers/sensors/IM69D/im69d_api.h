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

#ifndef IM69D_API_H
#define IM69D_API_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "fft_config.h"
#include "sensors.h"


/* Downsampling is needed to perform sampling with rate lower than possible minimum 8kHz. For 10Hz FFT step 2560Hz sample rate required */
#define I2S_CONFIGURED_SAMPLE_RATE        ( 10240U )
#define I2S_REQUIRED_DOWNSAMPLED_RATE     ( 2560U )
#define I2S_DOWNSAMPLING_DIVISOR          ( I2S_CONFIGURED_SAMPLE_RATE / I2S_REQUIRED_DOWNSAMPLED_RATE )

#define I2S_BUFFER_LENGTH 			      ( 256 )
#define I2S_BITS_PER_SAMPLE 		      ( 20U )


typedef enum {
	IM69D_API_MIC_ID_LEFT = 0,
	IM69D_API_MIC_ID_RIGHT,
	IM69D_API_MIC_ID_MIX,

	IM69D_API_MIC_MAX

} IM69DMicrophoneId_t;


int32_t IM69D_lInit( void **ppvHandle, IM69DMicrophoneId_t xMicId );
void IM69D_vDeInit( void );
int32_t IM69D_lGetData( InfineonSensorsData_t *pxSensorsData, uint32_t ulVectorPosition, uint32_t ulVectorLength );
void IM69D_vPrintData( InfineonSensorsData_t *pxSensorsData, uint32_t ulVectorPosition, uint32_t ulVectorLength );
void IM69D_vGetLeftData( int16_t* plLeftMicBufferToRet, uint16_t pusBuffSize );
void IM69D_vGetRightData( int16_t* pRightMicBufferToRet, uint16_t pusBuffSize );


#endif /* IM69D_API_H */

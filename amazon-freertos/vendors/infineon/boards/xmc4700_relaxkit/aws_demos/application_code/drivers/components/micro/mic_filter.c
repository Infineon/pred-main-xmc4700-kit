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

#include "DAVE.h"
#include "mic_filter.h"

#define BLOCK_SIZE            40
#define NUM_TAPS              11

/*
sampling frequency: 8000 Hz

fixed point precision: 32 bits

* 0 Hz - 2000 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 3000 Hz - 4000 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a
*/


/* -------------------------------------------------------------------
 * Declare State buffer of size (numTaps + blockSize - 1)
 * ------------------------------------------------------------------- */
static int32_t plFilterState[BLOCK_SIZE + NUM_TAPS - 1];

static int32_t plFilterCoeffs[NUM_TAPS] = {
  89904090,
  140542393,
  -132429544,
  -166747492,
  644644870,
  1264279446,
  644644870,
  -166747492,
  -132429544,
  140542393,
  89904090
};


void vFilterMicData( int32_t* const plMicInputData, int32_t* const plMicFilteredData, const uint16_t usMicBuffSize )
{
	int32_t *plInputData = (int32_t*)plMicInputData;
	int32_t *plOutputData = (int32_t*)plMicFilteredData;

	const uint32_t ulNumBlocks = usMicBuffSize / BLOCK_SIZE;

	arm_fir_instance_q31 xInstanceMicFilter;

	/* Call FIR initialization function to initialize the instance structure. */
	arm_fir_init_q31( &xInstanceMicFilter, NUM_TAPS, (int32_t *)&plFilterCoeffs[0], &plFilterState[0], BLOCK_SIZE );

	for( uint32_t ulIndex = 0; ulIndex < ulNumBlocks; ++ulIndex )
	{
		arm_fir_q31( &xInstanceMicFilter, plInputData + ( ulIndex * BLOCK_SIZE ), plOutputData + ( ulIndex * BLOCK_SIZE ), BLOCK_SIZE );
	}

}

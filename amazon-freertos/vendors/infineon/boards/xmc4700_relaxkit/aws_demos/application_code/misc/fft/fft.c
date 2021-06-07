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
#include <stdbool.h>
#include <math.h>

#include "fft.h"
#include "fft_config.h"


#define SIGNED_2WORD_MAX_VALUE 	( 0x7FFF )
#define TRNSFRMD_BUFF_SIZE		( FFT_BUFFER_SIZE / 2 )


int16_t sQ15HannWindow[256] = {
        0,
		5,
		20,
		45,
		79,
		124,
		178,
		242,
		315,
		399,
		491,
		594,
		706,
		827,
		958,
		1098,
		1248,
		1406,
		1573,
		1750,
		1935,
		2129,
		2331,
		2542,
		2762,
		2989,
		3225,
		3468,
		3719,
		3978,
		4245,
		4518,
		4799,
		5087,
		5382,
		5683,
		5990,
		6304,
		6624,
		6950,
		7282,
		7619,
		7961,
		8309,
		8661,
		9018,
		9379,
		9745,
		10114,
		10488,
		10865,
		11245,
		11628,
		12014,
		12403,
		12794,
		13188,
		13583,
		13980,
		14378,
		14778,
		15179,
		15580,
		15982,
		16384,
		16786,
		17188,
		17589,
		17990,
		18390,
		18788,
		19185,
		19580,
		19974,
		20365,
		20754,
		21140,
		21523,
		21903,
		22280,
		22654,
		23023,
		23389,
		23750,
		24107,
		24459,
		24807,
		25149,
		25486,
		25818,
		26144,
		26464,
		26778,
		27085,
		27386,
		27681,
		27969,
		28250,
		28523,
		28790,
		29049,
		29300,
		29543,
		29779,
		30006,
		30226,
		30437,
		30639,
		30833,
		31018,
		31195,
		31362,
		31520,
		31670,
		31810,
		31941,
		32062,
		32174,
		32277,
		32369,
		32453,
		32526,
		32590,
		32644,
		32689,
		32723,
		32748,
		32763,
		32767,
		32763,
		32748,
		32723,
		32689,
		32644,
		32590,
		32526,
		32453,
		32369,
		32277,
		32174,
		32062,
		31941,
		31810,
		31670,
		31520,
		31362,
		31195,
		31018,
		30833,
		30639,
		30437,
		30226,
		30006,
		29779,
		29543,
		29300,
		29049,
		28790,
		28523,
		28250,
		27969,
		27681,
		27386,
		27085,
		26778,
		26464,
		26144,
		25818,
		25486,
		25149,
		24807,
		24459,
		24107,
		23750,
		23389,
		23023,
		22654,
		22280,
		21903,
		21523,
		21140,
		20754,
		20365,
		19974,
		19580,
		19185,
		18788,
		18390,
		17990,
		17589,
		17188,
		16786,
		16384,
		15982,
		15580,
		15179,
		14778,
		14378,
		13980,
		13583,
		13188,
		12794,
		12403,
		12014,
		11628,
		11245,
		10865,
		10488,
		10114,
		9745,
		9379,
		9018,
		8661,
		8309,
		7961,
		7619,
		7282,
		6950,
		6624,
		6304,
		5990,
		5683,
		5382,
		5087,
		4799,
		4518,
		4245,
		3978,
		3719,
		3468,
		3225,
		2989,
		2762,
		2542,
		2331,
		2129,
		1935,
		1750,
		1573,
		1406,
		1248,
		1098,
		958,
		827,
		706,
		594,
		491,
		399,
		315,
		242,
		178,
		124,
		79,
		45,
		20,
		5};


void scaleTo16Bits( int32_t* const pArray, int16_t* const pScaledArray, const uint16_t numEntries )
{
	uint32_t maxValue = 0;

	for( uint16_t index = 0; index < numEntries; ++index )
	{
		if( abs(pArray[index]) > maxValue )
		{
			maxValue = abs( pArray[index] );
		}
	}

	const float32_t scaleFactor = (float32_t)( (float32_t)SIGNED_2WORD_MAX_VALUE / (float32_t)maxValue );

	for( uint16_t index = 0; index < numEntries; ++index )
	{
		pScaledArray[index] = pArray[index] * scaleFactor;
	}
}

#define M_PI		3.14159265358979323846f

void windowHanning( q15_t* const pSignal, const uint16_t numEntries )
{
	for( uint16_t index = 0; index < numEntries; index++ )
	{
		pSignal[index] = (q15_t)( (float32_t)pSignal[index] * (0.5f - (0.5f * cosf((2 * M_PI * index) / (numEntries - 1)))) );
	}
}

/* Assumption - numEntries is even number! */
void calculateRealFreqs( float32_t* const pOutFreqs, const uint16_t numEntries, const uint16_t sampleRate )
{
	for(uint16_t index = 0; index < numEntries; ++index)
	{
		pOutFreqs[index] = ( (float32_t)index / (float32_t)numEntries ) * (float32_t)sampleRate;
	}
}

void findPeaksWithMax( uint16_t* const pPeaksIndexes, uint16_t* const pMaxPeakIndex, uint16_t* const pNumberOfPeaks,
		              float32_t* const pSignal, const uint16_t numEntries, const float32_t height )
{
	uint16_t peaksArrayIndex = 0;
	float32_t maxPeakValue = 0;
	*pMaxPeakIndex = 0;
	/* We don't consider edge values as possible peakes */
	for( uint16_t index = 1; index < (numEntries - 1); ++index )
	{
		if( pSignal[index] > height )
		{
			if( pSignal[index] > pSignal[index - 1] )
			{
				bool bPeakFound = false;
				if( pSignal[index] > pSignal[index + 1] )
				{
					pPeaksIndexes[peaksArrayIndex] = index;
					bPeakFound = true;
				}

				/* Flat peak case */
				/* ================= Don't know if we need consider Flat Peaks =============== */
				if( pSignal[index] == pSignal[index + 1] )
				{
					const uint16_t flatPeakStartIndex = index;
					do
					{
						++index;

					} while( (pSignal[index] == pSignal[index + 1]) && (index < (numEntries - 1)) );

					if( pSignal[index] > pSignal[index + 1] )
					{
						pPeaksIndexes[peaksArrayIndex] = ( flatPeakStartIndex + index ) / 2;
						bPeakFound = true;
					}
				}
				/* ================= End Flat peak case =============== */

				if( bPeakFound )
				{
					/* Check if new peak is bigger then previous max value */
					if( pSignal[pPeaksIndexes[peaksArrayIndex]] > maxPeakValue )
					{
						maxPeakValue = pSignal[pPeaksIndexes[peaksArrayIndex]];
						*pMaxPeakIndex = pPeaksIndexes[peaksArrayIndex];
					}

					++peaksArrayIndex;
					/* If we have found the peak, then the next value can't be new peak */
					++index;
				}
			}
		}
	}

	*pNumberOfPeaks = peaksArrayIndex;
}

/* Assumption - numEntries should be 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192. */
void performFFT( float32_t* const pMaxFreq, int32_t* const pSignal, const uint16_t numEntries, const uint16_t sampleRate )
{
	q15_t scaledSignal[FFT_BUFFER_SIZE];
	scaleTo16Bits( pSignal, scaledSignal, numEntries );

	/* 0 - forward transform */
	const uint32_t ifftFlagR = 0;
	/* 1 - disables bit reversal of output */
	const uint32_t bitReverseFlag = 1;

	arm_rfft_instance_q15 newRfftInstance;

	arm_status status = arm_rfft_init_q15( &newRfftInstance, numEntries, ifftFlagR, bitReverseFlag );

	if( status == ARM_MATH_SUCCESS )
	{
		/* Hanning Window Calculation */
		windowHanning( scaledSignal, numEntries );

		/* Perform real FFT */
		q15_t trnsfrmdSignal[FFT_BUFFER_SIZE] = { 0 };
		arm_rfft_q15( &newRfftInstance, scaledSignal, trnsfrmdSignal );

		/* Calculate magnitude for each value */
		q15_t absTrnsfrmdSignal[TRNSFRMD_BUFF_SIZE] = { 0 };
		const uint16_t trnsfrmdNumEntries = ( numEntries / 2 );
		arm_cmplx_mag_q15( trnsfrmdSignal, absTrnsfrmdSignal, trnsfrmdNumEntries );

		/* Smoothing */
		for( uint16_t index = 0; index < (trnsfrmdNumEntries - 2); ++index )
		{
			absTrnsfrmdSignal[index] = (q15_t)sqrtf( ((absTrnsfrmdSignal[index] * absTrnsfrmdSignal[index]) +
					                                 (absTrnsfrmdSignal[index + 1] * absTrnsfrmdSignal[index + 1]) +
 										             (absTrnsfrmdSignal[index + 2] * absTrnsfrmdSignal[index + 2])) );
		}

		/* Calculate fft freqs */
		float32_t freqs[TRNSFRMD_BUFF_SIZE];
		calculateRealFreqs( freqs, trnsfrmdNumEntries, (sampleRate / 2) );

		float32_t signalFloat[TRNSFRMD_BUFF_SIZE];
		/* Calculate ln of the transformed signal */
		for(uint16_t index = 0; index < trnsfrmdNumEntries; ++index)
		{
			signalFloat[index] = (float32_t)( 20.0f * logf(absTrnsfrmdSignal[index] + 1.0f) );
		}

		/* Find Peaks */
		uint16_t peaksIndexes[TRNSFRMD_BUFF_SIZE];
		uint16_t maxPeakIndex;
		uint16_t numberOfPeaks;
		const float32_t peaksHeight = 0;
		findPeaksWithMax( peaksIndexes, &maxPeakIndex, &numberOfPeaks, signalFloat, (trnsfrmdNumEntries - 2), peaksHeight );

		*pMaxFreq = freqs[maxPeakIndex];
	}
}

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

#include "FreeRTOS.h"

#include "im69d_api.h"
#include "fft/fft.h"

#include "DAVE.h"


typedef struct {
	uint8_t ucShiftFirst;
	uint8_t ucShiftSecond;
	uint32_t ulFirstShiftMask;
	uint32_t ulSecondShiftMask;
} I2S_PROTOCOL_SETTINGS_t;

typedef struct {
	bool bOverflow;
	bool bBufferIsAvailable;
	uint16_t usHeadPosition;
	uint16_t usBufferSize;
	uint8_t ucValuesCounter;
	int32_t lLastValue;
	int32_t *plRawBuffer;
	int16_t *psFftBuffer;
} I2S_DATA_t;

typedef struct {
	I2S_PROTOCOL_SETTINGS_t xSettings;
	I2S_DATA_t xLeftChannel;
	I2S_DATA_t xRightChannel;
} IM69DData_t;


static IM69DData_t *prvCreateStruct( uint16_t usBuffSize );
static void prvDeleteStruct( IM69DData_t *pxMicData );
static void prvCalculatelMicSpectrum( int32_t *plBufferRaw, int16_t *psBufferFft, uint32_t ulLength );
portINLINE static void prvReceivedSampleProcessing( void );
portINLINE static void prvParceValue( I2S_DATA_t *channel,  bool bStartOfFrame, uint16_t usVal );
portINLINE static uint8_t prvStoreValue( I2S_DATA_t *channel, int32_t lValue );


IM69DData_t *pxMicData = NULL;



/* I2S Interrupt handler */
void I2SIRQHandler( void )
{
	prvReceivedSampleProcessing();
}



IM69DData_t *prvCreateStruct( uint16_t usBuffSize )
{
    IM69DData_t* pxMicData = (IM69DData_t*)pvPortMalloc( sizeof(IM69DData_t) );
    if( pxMicData == NULL )
	{
		return NULL;
	}

    pxMicData->xLeftChannel.usBufferSize = usBuffSize;
	pxMicData->xRightChannel.usBufferSize = usBuffSize;

    pxMicData->xLeftChannel.psFftBuffer = (int16_t*)pvPortMalloc( pxMicData->xLeftChannel.usBufferSize * sizeof(int16_t) );
    if( pxMicData->xLeftChannel.psFftBuffer == NULL )
	{
    	return NULL;
	}
    memset(pxMicData->xLeftChannel.psFftBuffer, 0, pxMicData->xLeftChannel.usBufferSize * sizeof(int16_t));

    pxMicData->xRightChannel.psFftBuffer = (int16_t*)pvPortMalloc( pxMicData->xRightChannel.usBufferSize * sizeof(int16_t) );
    if( pxMicData->xRightChannel.psFftBuffer == NULL )
	{
    	return NULL;
	}
    memset(pxMicData->xRightChannel.psFftBuffer, 0, pxMicData->xRightChannel.usBufferSize * sizeof(int16_t));

    pxMicData->xLeftChannel.plRawBuffer = (int32_t*)pvPortMalloc( pxMicData->xLeftChannel.usBufferSize * sizeof(int32_t) );
    if( pxMicData->xLeftChannel.plRawBuffer == NULL )
	{
    	return NULL;
	}
    memset(pxMicData->xLeftChannel.plRawBuffer, 0, pxMicData->xLeftChannel.usBufferSize * sizeof(int32_t));

    pxMicData->xRightChannel.plRawBuffer = (int32_t*)pvPortMalloc( pxMicData->xRightChannel.usBufferSize * sizeof(int32_t) );
    if( pxMicData->xRightChannel.plRawBuffer == NULL )
	{
    	return NULL;
	}
    memset(pxMicData->xRightChannel.plRawBuffer, 0, pxMicData->xRightChannel.usBufferSize * sizeof(int32_t));

    return pxMicData;
}


void prvDeleteStruct( IM69DData_t *pxMicData )
{
    vPortFree( pxMicData->xLeftChannel.psFftBuffer );
    vPortFree( pxMicData->xRightChannel.psFftBuffer );
    vPortFree( pxMicData->xLeftChannel.plRawBuffer );
    vPortFree( pxMicData->xRightChannel.plRawBuffer );
    vPortFree( pxMicData );
}



int32_t IM69D_lInit( void **ppvHandle, IM69DMicrophoneId_t xMicId )
{
	/** Initialize IM69D Microphone */
	pxMicData = prvCreateStruct( I2S_BUFFER_LENGTH );

	if( pxMicData == NULL )
	{
		configPRINTF( ("Initialize IM69D microphone structure error\r\n") );
		return -1;
	}

	pxMicData->xSettings.ucShiftFirst = 16;
	pxMicData->xSettings.ulFirstShiftMask = 0xFFFF0000;
	pxMicData->xSettings.ucShiftSecond = 32 - I2S_BITS_PER_SAMPLE;
	pxMicData->xSettings.ulSecondShiftMask = 0x0000FFFF;

	pxMicData->xLeftChannel.usHeadPosition = 0;
	pxMicData->xRightChannel.usHeadPosition = 0;
	pxMicData->xLeftChannel.bBufferIsAvailable = false;
	pxMicData->xRightChannel.bBufferIsAvailable = false;
	pxMicData->xLeftChannel.ucValuesCounter = 0;
	pxMicData->xRightChannel.ucValuesCounter = 0;

	/* Set Receiver Control Information Mode to 11b ( RCI[4] = PERR, RCI[3] = PAR, RCI[2:1] = 00B, RCI[0] = SOF ) */
	I2S_CONFIG_0.channel->RBCTR |= USIC_CH_RBCTR_RCIM_Msk;

	/* Set Receiver Notification Mode to 1b - RCI mode (A standard receive buffer event occurs when register OUTR
	 * is updated with a new value if the corresponding value in OUTR.RCI[4] = 0.If OUTR.RCI[4] = 1, an alternative
	 * receive buffer event occurs instead of the standard receive buffer event.) */
	I2S_CONFIG_0.channel->RBCTR |= USIC_CH_RBCTR_RNM_Msk;

	XMC_I2S_CH_Start( I2S_CONFIG_0.channel );

	return 0;
}


void IM69D_vDeInit( void )
{
    XMC_I2S_CH_Stop( I2S_CONFIG_0.channel );
	prvDeleteStruct( pxMicData );
}


/** Microphone IM69D receive and process data */
int32_t IM69D_lGetData( InfineonSensorsData_t *pxSensorsData, uint32_t ulVectorPosition, uint32_t ulVectorLength )
{
	int32_t lRet = 0;

    /* If Left channel data is ready */
	if( pxMicData->xLeftChannel.bBufferIsAvailable )
    {
		for( uint32_t i = 0; i < I2S_BUFFER_LENGTH; i++ )
		{
			if( i >= ulVectorLength )
			{
				break;
			}
			pxSensorsData->fSensorsVector.vector[ulVectorPosition][i] = (float)pxMicData->xLeftChannel.plRawBuffer[i];
		}

        prvCalculatelMicSpectrum(pxMicData->xLeftChannel.plRawBuffer, pxMicData->xLeftChannel.psFftBuffer, I2S_BUFFER_LENGTH);

        memcpy( pxSensorsData->fMicBuffer.mic_fft_buf, pxMicData->xLeftChannel.psFftBuffer, sizeof(pxSensorsData->fMicBuffer.mic_fft_buf) );

        pxMicData->xLeftChannel.bBufferIsAvailable = false;
    }
	else
	{
		lRet = -1;
	}

    return lRet;
}


void IM69D_vPrintData( InfineonSensorsData_t *pxSensorsData, uint32_t ulVectorPosition, uint32_t ulVectorLength )
{
    configPRINTF( ("\nLEFT: ") );
    for( uint32_t i = 0; i < ulVectorLength; i++ )
    {
        configPRINTF( ("%ld ", (int32_t)pxSensorsData->fSensorsVector.vector[ulVectorPosition][i]) );
    }
    configPRINTF( ("\n") );

    configPRINTF( ("\nFFT: ") );

    /* FFT data is two times shorter than sound data */
    ulVectorLength /= 2;
    for( uint32_t i = 0; i < ulVectorLength; i++ )
    {
        configPRINTF( ("%ld ", pxSensorsData->fMicBuffer.mic_fft_buf[i]) );
    }
    configPRINTF( ("\n") );
}


portINLINE static void prvReceivedSampleProcessing( void )
{
	/* Return immediately if the FIFO is empty or no microphone is selected and clear the flags */
	if( XMC_USIC_CH_RXFIFO_IsEmpty( I2S_CONFIG_0.channel ) == true )
	{
		XMC_I2S_CH_ClearStatusFlag( I2S_CONFIG_0.channel, XMC_I2S_CH_STATUS_FLAG_RECEIVE_INDICATION | XMC_I2S_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION );
		XMC_USIC_CH_RXFIFO_ClearEvent( I2S_CONFIG_0.channel, XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_STANDARD );
		return;
	}

	bool bStartOfFrame = false;

	uint16_t usRetVal = 0;
	uint16_t usRCI = 0;

	/* 16 LSB of OUTR - data; 16 MSB contains some data status */
	 uint32_t ulTmp = I2S_CONFIG_0.channel->OUTR;

	/* Get data value */
	usRetVal = (uint16_t)( ulTmp & 0x0000FFFF );
	/* Get RCI value */
	usRCI = ( ulTmp >> 16 ) & 0x0000FFFF;

	/* Micro's DATA is 20-bit wide, but receive buffer is 16-bit wide
	 * So, we need to combine 16 bits of first frame and 4 LSB of second frame:
	 * 16 bits of first frame are 16 MSB of 20-bit data;
	 * 4 LSB of second frame are 4 LSB of 20-bit data. */

	/* Check whether first word is start of frame */
	if( ( usRCI & 0x0001 ) != 0 )
	{
		bStartOfFrame = true;
	}

	/* Proceed with the microphone calculations */
	/* Check for the microphone data for WA=LOW */
	if( ( usRCI & 0x0010 ) == 0 )
	{
		prvParceValue( &pxMicData->xLeftChannel, bStartOfFrame, usRetVal );
	}
	/* Proceed with the microphone calculations */
	/* Check for the microphone data for WA=HIGH */
	else if( ( usRCI & 0x0010 ) != 0 )
	{
		prvParceValue( &pxMicData->xRightChannel, bStartOfFrame, usRetVal );
	}

	XMC_USIC_CH_RXFIFO_ClearEvent( I2S_CONFIG_0.channel, XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_STANDARD );
	XMC_I2S_CH_ClearStatusFlag( I2S_CONFIG_0.channel, XMC_I2S_CH_STATUS_FLAG_RECEIVE_INDICATION | XMC_I2S_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION );

	return;
}


portINLINE static void prvParceValue( I2S_DATA_t *channel,  bool bStartOfFrame, uint16_t usVal )
{
	/* If first frame */
	if( bStartOfFrame )
	{
		channel->lLastValue = 0;
		channel->lLastValue = ( (uint32_t)usVal << pxMicData->xSettings.ucShiftFirst ) & pxMicData->xSettings.ulFirstShiftMask;
	}
	/* If second frame */
	else
	{
		/* Combine data from both frames and align them to the right */
		channel->lLastValue |= ((uint32_t)usVal << pxMicData->xSettings.ucShiftSecond ) & pxMicData->xSettings.ulSecondShiftMask;
		channel->lLastValue = channel->lLastValue >> pxMicData->xSettings.ucShiftSecond;

		if( prvStoreValue( channel, channel->lLastValue ) == 0 )
		{
			channel->bOverflow = true;
		}
	}
}


portINLINE static uint8_t prvStoreValue( I2S_DATA_t *channel, int32_t lValue )
{
    uint16_t usIndex;

    /* Return if filled buffer is still not processed */
    if( channel->bBufferIsAvailable )
    {
        return 1;
    }

    /* Reduce the sampling rate to the required value (DOWNSAMPLED_RATE) */
    if( channel->ucValuesCounter == 0 )
    {
        usIndex = channel->usHeadPosition + 1;

        /* Store new obtained data from microphone to buffer */
        channel->plRawBuffer[channel->usHeadPosition] = lValue;

        /* If I2S_BUFFER_LENGTH microphone values were obtained, they are ready for processing */
        if( usIndex == I2S_BUFFER_LENGTH )
        {
        	channel->bBufferIsAvailable = true;
            usIndex = 0;
        }
        channel->usHeadPosition = usIndex;
    }

    if( ++channel->ucValuesCounter == I2S_DOWNSAMPLING_DIVISOR )
    {
    	channel->ucValuesCounter = 0;
    }

	return 1;
}


/** Spectrum calculation */
void prvCalculatelMicSpectrum( int32_t *plBufferRaw, int16_t *psBufferFft, uint32_t ulLength )
{
    uint16_t i;
    int32_t lMax = INT16_MIN;
    int32_t lMin = INT16_MAX;

    /** instance for spectra calculation */
    arm_rfft_instance_q15 xRfftInstance;
    arm_status xRfftInitStatus = ARM_MATH_SUCCESS;

    xRfftInitStatus = arm_rfft_init_q15( &xRfftInstance, ulLength, 0, 1 );
    if( xRfftInitStatus != 0 )
    {
        configPRINTF( ("ARM RFFT init q15 for IM69D130 error = %d\r\n", xRfftInitStatus) );
    }

    /* Find Min and Max values from signal*/
    for( i = 0; i < ulLength; i++ )
    {
        int32_t value = plBufferRaw[i];
        if( value > lMax )
        {
            lMax = value;
        }
        else if( value < lMin )
        {
            lMin = value;
        }
    }

    /* Calculate DC component */
    int32_t lDcValue = (lMax - lMin) / 2 + lMin;

    for( i = 0; i < ulLength; i++ )
    {
        if( i >= SENSORS_VECTOR_LEN )
        {
            break;
        }
        /* Remove DC component */
        plBufferRaw[i] = plBufferRaw[i] - lDcValue;
    }

    /* Remove DC component from lMax value*/
    lMax -= lDcValue;

    /* Applying Hann Window and scaling values to full range of Q15 */
    for( i = 0; i < ulLength; i++ )
    {
        psBufferFft[i] = (int16_t)( ( plBufferRaw[i] * sQ15HannWindow[i] ) / lMax );
    }

    int16_t *psTrnsfrmdSignal = (int16_t*)pvPortMalloc( 2 * ulLength * sizeof(int16_t) );

    /* Perform real FFT */
    arm_rfft_q15( &xRfftInstance, psBufferFft, psTrnsfrmdSignal );

    /* Calculate magnitude for each value */
    arm_cmplx_mag_q15( psTrnsfrmdSignal, psBufferFft, I2S_BUFFER_LENGTH );

   vPortFree( psTrnsfrmdSignal );
}


void IM69D_vGetLeftData( int16_t* plLeftMicBufferToRet, uint16_t pusBuffSize )
{
    pusBuffSize = (pusBuffSize > pxMicData->xLeftChannel.usBufferSize) ? pxMicData->xLeftChannel.usBufferSize : pusBuffSize;
    if( pxMicData->xLeftChannel.bBufferIsAvailable )
    {
        memcpy( plLeftMicBufferToRet, pxMicData->xLeftChannel.plRawBuffer, sizeof(uint16_t) * pusBuffSize );
        pxMicData->xLeftChannel.bBufferIsAvailable = false;
    }
    else
    {
        plLeftMicBufferToRet = NULL;
    }
}


void IM69D_vGetRightData( int16_t* plRightMicBufferToRet, uint16_t pusBuffSize )
{
    pusBuffSize = (pusBuffSize > pxMicData->xRightChannel.usBufferSize) ? pxMicData->xRightChannel.usBufferSize : pusBuffSize;
    if( pxMicData->xRightChannel.bBufferIsAvailable )
    {
        memcpy( plRightMicBufferToRet, pxMicData->xRightChannel.plRawBuffer, sizeof(uint16_t) * pusBuffSize );
        pxMicData->xRightChannel.bBufferIsAvailable = false;
    }
    else
    {
        plRightMicBufferToRet = NULL;
    }
}



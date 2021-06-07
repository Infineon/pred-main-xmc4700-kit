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

#include "FreeRTOS.h"
#include "task.h"

#include "circular_buffer.h"


static void prvAdvancePointer( CbufHandle_t pxCbuf )
{
    configASSERT( pxCbuf );

	if( pxCbuf->full )
    {
        pxCbuf->tail = (pxCbuf->tail + 1) % pxCbuf->max;
    }

	pxCbuf->head = (pxCbuf->head + 1) % pxCbuf->max;

	// We mark full because we will advance tail on the next time around
	pxCbuf->full = (pxCbuf->head == pxCbuf->tail);
}

static void prvRetreatPointer( CbufHandle_t pxCbuf )
{
    configASSERT( pxCbuf );

	pxCbuf->full = false;
	pxCbuf->tail = (pxCbuf->tail + 1) % pxCbuf->max;
}


CbufHandle_t CircularBuffer_pxInit( uint8_t* pucBuffer, size_t xSize )
{
    configASSERT( pucBuffer && xSize );

	CbufHandle_t pxCbuf = pvPortMalloc( sizeof(CircularBuf_t) );
    configASSERT( pxCbuf );

	pxCbuf->buffer = pucBuffer;
	pxCbuf->max = xSize;
	CircularBuffer_vReset( pxCbuf );

    configASSERT( CircularBuffer_bEmpty( pxCbuf ) );

	return pxCbuf;
}

void CircularBuffer_vFree( CbufHandle_t pxCbuf )
{
    configASSERT( pxCbuf );
	vPortFree( pxCbuf );
}

void CircularBuffer_vReset( CbufHandle_t pxCbuf )
{
    configASSERT( pxCbuf );

    pxCbuf->head = 0;
    pxCbuf->tail = 0;
    pxCbuf->full = false;
}

size_t CircularBuffer_xSize( CbufHandle_t pxCbuf )
{
    configASSERT( pxCbuf );

	size_t xSize = pxCbuf->max;

	if( !pxCbuf->full )
	{
		if( pxCbuf->head >= pxCbuf->tail )
		{
			xSize = (pxCbuf->head - pxCbuf->tail);
		}
		else
		{
			xSize = (pxCbuf->max + pxCbuf->head - pxCbuf->tail);
		}

	}

	return xSize;
}

size_t CircularBuffer_xCapacity( CbufHandle_t pxCbuf )
{
    configASSERT( pxCbuf );

	return pxCbuf->max;
}

void CircularBuffer_xPut( CbufHandle_t pxCbuf, uint8_t ucData )
{
    configASSERT( pxCbuf && pxCbuf->buffer );

    pxCbuf->buffer[pxCbuf->head] = ucData;

    prvAdvancePointer( pxCbuf );
}

int CircularBuffer_lPut2( CbufHandle_t pxCbuf, uint8_t ucData )
{
    int lRet = -1;

    configASSERT( pxCbuf && pxCbuf->buffer );

    if( !CircularBuffer_bFull( pxCbuf ) )
    {
        pxCbuf->buffer[pxCbuf->head] = ucData;
        prvAdvancePointer( pxCbuf );
        lRet = 0;
    }

    return lRet;
}

int CircularBuffer_lGet( CbufHandle_t pxCbuf, uint8_t * pucData )
{
    configASSERT( pxCbuf && pucData && pxCbuf->buffer );

    int lRet = -1;

    if( !CircularBuffer_bEmpty( pxCbuf ) )
    {
        *pucData = pxCbuf->buffer[pxCbuf->tail];
        prvRetreatPointer( pxCbuf );

        lRet = 0;
    }

    return lRet;
}

bool CircularBuffer_bEmpty( CbufHandle_t pxCbuf )
{
    configASSERT( pxCbuf );

    return ( !pxCbuf->full && (pxCbuf->head == pxCbuf->tail) );
}

bool CircularBuffer_bFull( CbufHandle_t pxCbuf )
{
    configASSERT( pxCbuf );

    return pxCbuf->full;
}

bool CircularBuffer_bPeekAndCompare( CbufHandle_t pxCbuf, const char *pcData, size_t xLen )
{
    configASSERT( pxCbuf );
    size_t pointer = pxCbuf -> tail;
    if ( xLen > CircularBuffer_xSize(pxCbuf) )
    {
        return false;
    }
    bool first_byte_is_head = pxCbuf->full; // When the buffer is full head = tail so we need to skip checking first time.
    for ( size_t i = 0; i < xLen; ++i, pointer = (pointer + 1) % pxCbuf->max )
    {
        if ( (first_byte_is_head ? false : pointer == pxCbuf->head) || pxCbuf->buffer[pointer] != pcData[i] )
        {
            return false;
        }
        first_byte_is_head = false;
    }
    return true;
}

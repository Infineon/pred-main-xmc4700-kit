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

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>


typedef struct {
	uint8_t * buffer;
	size_t head;
	size_t tail;
	size_t max;
	bool full;

} CircularBuf_t;


/* Handle type, the way users interact with the API */
typedef CircularBuf_t* CbufHandle_t;

/* Pass in a storage buffer and size, returns a circular buffer handle
 * Requires: buffer is not NULL, size > 0
 * Ensures: pxCbuf has been created and is returned in an empty state
 */
CbufHandle_t CircularBuffer_pxInit( uint8_t* pucBuffer, size_t xSize );


/* Free a circular buffer structure
 * Requires: pxCbuf is valid and created by circular_buf_init
 * Does not free data buffer; owner is responsible for that
 */
void CircularBuffer_vFree( CbufHandle_t pxCbuf );

/* Reset the circular buffer to empty, head == tail. Data not cleared
 * Requires: pxCbuf is valid and created by circular_buf_init
 */
void CircularBuffer_vReset( CbufHandle_t pxCbuf );


/* Put version 1 continues to add data if the buffer is full
 * Old data is overwritten
 * Requires: pxCbuf is valid and created by circular_buf_init
 */
void CircularBuffer_xPut( CbufHandle_t pxCbuf, uint8_t ucData );

/* Put Version 2 rejects new data if the buffer is full
 * Requires: pxCbuf is valid and created by circular_buf_init
 * Returns 0 on success, -1 if buffer is full
 */
int CircularBuffer_lPut2( CbufHandle_t pxCbuf, uint8_t ucData );

/* Retrieve a value from the buffer
 * Requires: pxCbuf is valid and created by circular_buf_init
 * Returns 0 on success, -1 if the buffer is empty
 */
int CircularBuffer_lGet( CbufHandle_t pxCbuf, uint8_t * pucData );

/* Checks if the buffer is empty
 * Requires: pxCbuf is valid and created by circular_buf_init
 * Returns true if the buffer is empty
 */
bool CircularBuffer_bEmpty( CbufHandle_t pxCbuf );

/* Checks if the buffer is full
 * Requires: pxCbuf is valid and created by circular_buf_init
 * Returns true if the buffer is full
 */
bool CircularBuffer_bFull( CbufHandle_t pxCbuf );

/* Check the capacity of the buffer
 * Requires: pxCbuf is valid and created by circular_buf_init
 * Returns the maximum capacity of the buffer
 */
size_t CircularBuffer_xCapacity( CbufHandle_t pxCbuf );

/* Check the number of elements stored in the buffer
 * Requires: pxCbuf is valid and created by circular_buf_init
 * Returns the current number of elements in the buffer
 */
size_t CircularBuffer_xSize( CbufHandle_t pxCbuf );


bool CircularBuffer_bPeekAndCompare( CbufHandle_t pxCbuf, const char *pcData, size_t xLen );


#endif /* CIRCULAR_BUFFER_H */

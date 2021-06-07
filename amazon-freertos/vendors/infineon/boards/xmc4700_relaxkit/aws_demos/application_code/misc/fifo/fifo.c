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

#include "fifo.h"


uint32_t fifo_count( struct fifo *fifo )
{
	return ( fifo->head-fifo->tail );
}

uint32_t fifo_size( struct fifo *fifo )
{
	return sizeof( fifo->buf );
}

uint32_t fifo_is_full( struct fifo *fifo )
{
	return ( fifo_count(fifo) == fifo_size(fifo) ) ? 1 : 0;
}

uint32_t fifo_is_empty( struct fifo *fifo )
{
	return ( fifo->tail==  fifo->head ) ? 1 : 0;
}

uint32_t fifo_space( struct fifo *fifo )
{
	return ( fifo_size(fifo) - fifo_count(fifo) );
}

void fifo_push( struct fifo *fifo, char byte )
{
	fifo->buf[fifo->head % fifo_size(fifo)] = byte;
	fifo->head++;
}

char fifo_pop( struct fifo *fifo )
{
	char byte = fifo->buf[fifo->tail % fifo_size(fifo)];
	fifo->buf[fifo->tail % fifo_size(fifo)] = 0;
	fifo->tail++;

	return byte;
}

void fifo_flush( struct fifo *fifo )
{
    fifo->tail = 0;
    fifo->head = 0;
    memset( fifo->buf, 0, fifo_size(fifo) );
}

uint32_t fifo_read_to_buf( struct fifo *fifo, char *pBuf, uint32_t len )
{
	int i;
	for( i = 0; i < len; i++ )
	{
		*pBuf = fifo_pop( fifo );
		pBuf++;
	}

	return i;
}

uint32_t fifo_send_from_buf( struct fifo *fifo, char *pBuf, uint32_t len )
{
	int i;
	for( i = 0; i < len; i++ )
	{
		fifo_push( fifo, *pBuf );
		pBuf++;
	}

	return i;
}

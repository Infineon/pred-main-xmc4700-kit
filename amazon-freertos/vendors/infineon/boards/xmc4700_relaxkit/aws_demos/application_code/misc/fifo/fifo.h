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

#ifndef FIFO_H
#define FIFO_H

#include <string.h>
#include <stdint.h>


#define AT_RCV_FIFO_SIZE	( 1500 )

typedef struct fifo {
    unsigned char buf[AT_RCV_FIFO_SIZE];
    uint32_t tail;
    uint32_t head;

} fifo_t;


uint32_t fifo_count( struct fifo *fifo );
uint32_t fifo_size( struct fifo *fifo );
uint32_t fifo_is_full( struct fifo *fifo );
uint32_t fifo_is_empty( struct fifo *fifo );
uint32_t fifo_space( struct fifo *fifo );
uint32_t fifo_is_empty( struct fifo *fifo );
void fifo_push( struct fifo *fifo, char byte );
char fifo_pop( struct fifo *fifo );
void fifo_flush( struct fifo *fifo );
uint32_t fifo_read_to_buf( struct fifo *fifo, char * pBuf, uint32_t len );
uint32_t fifo_send_from_buf( struct fifo *fifo, char * pBuf, uint32_t len );


#endif /* FIFO_H */

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

#ifndef PAL_TLX493_I2C_H
#define PAL_TLX493_I2C_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


#define PAL_TLX493_I2C_ACQUIRE_TIMEOUT  	( 100 )
#define PAL_TLX493_DATA_TIMEOUT				( 1000 )


/* Status values returned by the I2C read/write commands */
typedef volatile enum {
    I2C_INT_SUCCESS,
    I2C_INT_IN_PROGRESS,
    I2C_INT_ERR_PROTOCOL,
    I2C_INT_NACK

} I2C_INT_State_t;


/* Initialize the I2C interrupt-based peripheral */
I2C_INT_State_t I2C_INT_xInit( uint8_t ucAddr );

/* Start blocking I2C write */
I2C_INT_State_t I2C_INT_xWriteBlock( uint8_t ucAddr, const uint8_t *pucData, uint8_t ucCount );

/* Start blocking I2C read */
I2C_INT_State_t I2C_INT_xReadBlock(uint8_t addr, uint8_t *pucData, uint8_t ucCount );

/* Write Reset address (for TLx493D sensors) on I2C bus (blocking) */
void I2C_INT_vWriteReset( void );

/* Write Recover address (for TLx493D sensors) on I2C bus (blocking) */
void I2C_INT_vWriteRecover( void );


#endif /* PAL_TLX493_I2C_H */

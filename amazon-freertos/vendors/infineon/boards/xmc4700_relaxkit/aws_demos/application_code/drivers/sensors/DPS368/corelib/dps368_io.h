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

#ifndef DPS368_IO_H
#define DPS368_IO_H

#include "dps368.h"


#define DPS368_API_SPI_ACQUIRE_TIMEOUT      ( 100 )
#define DPS368_API_I2C_ACQUIRE_TIMEOUT      ( 100 )

#define DPS368_API_DATA_TIMEOUT         	( 1000 )

#define DPS368_API_SPI_CONNECT_TRYES        ( 3 )

#define USING_LTC4332_SPI_EXT 				( 1 )


/*****************************I2C*********************************/
typedef enum {
    DPS368_API_I2C_ADDRESS_0 =  ( 0x76 << 1 ),
    DPS368_API_I2C_ADDRESS_1 =  ( 0x77 << 1 )

} DPS368SensorAddressI2C_t;


extern dps368_bus_connection xDps368FunctionsI2C_1;
extern dps368_bus_connection xDps368FunctionsI2C_2;



/*****************************SPI*********************************/
extern dps368_bus_connection xDps368FunctionsSPI_1;
extern dps368_bus_connection xDps368FunctionsSPI_2;
extern dps368_bus_connection xDps368FunctionsSPI_3;


int32_t DPS368_lConnect( DPS368_t *pxDrvState, dps368_bus_connection *pxBusIO );


#endif /* DPS368_IO_H */

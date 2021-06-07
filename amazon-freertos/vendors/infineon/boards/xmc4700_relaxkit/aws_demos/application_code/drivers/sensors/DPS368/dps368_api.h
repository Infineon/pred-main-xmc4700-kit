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

#ifndef DPS368_API_H
#define DPS368_API_H

#include <stdint.h>


typedef enum {
    DPS368_API_SENSOR_ID_1 = 0,			/* via SPI */
    DPS368_API_SENSOR_ID_2,             /* via SPI */
    DPS368_API_SENSOR_ID_3,             /* via SPI */
    DPS368_API_SENSOR_ID_4,             /* via I2C */
    DPS368_API_SENSOR_ID_5,             /* via I2C */

    DPS368_API_SENSOR_ID_MAX

} DPS368SensorNumber_t;

typedef struct {
    float fPressure;
    float fTemperature;

} DPS368Data_t;


int32_t DPS368_lInit( void **ppvHandle, DPS368SensorNumber_t xSensorNumber );
int32_t DPS368_lGetData( void *pvHandle, DPS368Data_t *pxSensorData );
void DPS368_vDeInit( void **ppvHandle );
void DPS368_vReset( void *pvHandle );


#endif /* DPS368_API_H */

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

#ifndef TLE496x_API_H
#define TLE496x_API_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    TLE496x_API_SENSOR_ID_ONE = 0,      /* TLE4964    High precision Unipolar Hall Effect Latch */
    TLE496x_API_SENSOR_ID_TWO,          /* TLE4961-3K High precision Bipolar Hall Effect Latch */
	TLE496x_API_SENSOR_ID_THREE,        /* TLE4913    Low Power Hall Switch */
	TLE496x_API_SENSOR_ID_FOUR,         /* TLE4961-1K High Precision Bipolar Hall Effect Switch */
    TLE496x_API_SENSOR_ID_FIVE,         /* TLI4966G   High Precision Hall-Effect Switch with Direction Detection  */

    TLE496x_API_SENSOR_ID_MAX

} TLE496xSensorNumber_t;


typedef struct {
    int32_t lMagneticFieldValue;
    int32_t lDirection;
    double fSpeed;

} TLE496xData_t;


typedef struct {
    void *pvCxt;
    TLE496xSensorNumber_t xSensorNumber;
    TLE496xData_t xData;

} TLE496x_t;


int32_t TLE496x_lInit( void **ppvHandle, TLE496xSensorNumber_t xSensorNumber );
int32_t TLE496x_lGetData( void *pvHandle, TLE496xData_t *pxSensorData );
void TLE496x_vDeInit( void **ppvHandle );
void TLE496x_vReset( void *pvHandle );


#endif /* TLE496x_API_H */

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

#ifndef TLI493D_API_H
#define TLI493D_API_H

#include "tlx493d.h"


typedef enum {
    TLI493D_API_SENSOR_ID_ONE = 0,
    TLI493D_API_SENSOR_ID_TWO,

    TLI493D_API_SENSOR_ID_MAX

} TLI493DSensorNumber_t;

typedef struct {
    float fMagneticFieldIntensityX;
    float fMagneticFieldIntensityY;
    float fMagneticFieldIntensityZ;
    float fTemperature;

} TLI493DData_t;


int32_t TLI493D_lInit( void **ppvHandle, TLI493DSensorNumber_t xSensorNumber );
void TLI493D_vDeInit( void **ppvHandle );
int32_t TLI493D_lGetData( void *pvHandle, TLI493DData_t *pxSensorData );
void TLI493D_vReset( void *pvHandle );


#endif /* TLI493D_API_H */

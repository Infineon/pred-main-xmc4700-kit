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

#ifndef TLI4971_H
#define TLI4971_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "FreeRTOS.h"
#include "queue.h"


#define ADC_RESOLUTION 		( 12 )
#define VREFs 				( 1670.0F )
#define VREFb				( 3300.0F )


typedef enum {
	TLI4971_SENSOR_ID_1 = 0,
	TLI4971_SENSOR_ID_2,
	TLI4971_SENSOR_ID_3,

	TLI4971_SENSOR_ID_MAX

} TLI4971SensorNumber_t;


typedef struct {
    float fCurrent;

} TLI4971Data_t;


typedef struct {
    void *pvCxt;
    TLI4971SensorNumber_t xSensorNumber;
    TLI4971Data_t xData;

} TLI4971_t;


enum OCDMODE { NONE, INTERRUPT, POLLING };
enum MEASRANGE { FSR120 = 0x05, FSR100 = 0x06, FSR75 = 0x08, FSR50 = 0x0C, FSR37_5 = 0x10, FSR25 = 0x18 };
enum OPMODE { SD_BID = 0, FD = 0x1<<5 , SD_UNI = 0x2<<5, S_ENDED = 0x3<<5 };
enum OCDDEGLITCH { D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15 };
enum OCDTHR { THR1_1, THR1_2, THR1_3, THR1_4, THR1_5, THR1_6, THR1_7, THR1_8, THR2_1, THR2_2, THR2_3, THR2_4, THR2_5, THR2_6, THR2_7, THR2_8 };
enum VRefExt { V1_65, V1_2, V1_5, V1_8, V2_5 };


int32_t TLI4971_lInit( void **ppvHandle, TLI4971SensorNumber_t xSensorNumber );
void TLI4971_vDeInit( void **ppvHandle );
int32_t TLI4971_lGetData( void *pvHandle, TLI4971Data_t *pxSensorData );


#endif /* TLI4971_H */

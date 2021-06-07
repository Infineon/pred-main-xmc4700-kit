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

#ifndef TLE4997_API_H
#define TLE4997_API_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "sensors.h"

#define     BUFF_HALL_SIZE          ( 256 )
#define     BUFF_HALL_FFT_SIZE      ( BUFF_HALL_SIZE / 2 )


#define     TLE4997_VDD             ( 5000.0 ) /* TLE4997 supply voltage */
#define     TLE4997_R2              ( 3600.0 ) /* Low-side divider resistor */
#define     TLE4997_R1              ( 2370.0 ) /* High-side divider resistor */

/* TLE4997 resistive divider coefficient */
#define     TLE4997_DIVIDER_COEF    ( TLE4997_R2 / ( TLE4997_R1 + TLE4997_R2 ) )

/* TLE4997 maximum voltage that can come to the ADC */
#define     TLE4997_VOUT_MAX        ( TLE4997_VDD * TLE4997_DIVIDER_COEF)

#define     TLE4997_ADC_MAX         ( 4095 ) /* 12bit ADC resolution maximum value */
#define     TLE4997_ADC_REF_VOLTAGE ( 3300 ) /* 3.3V ADC reference voltage */

/* The resulting coefficient */
#define     TLE4997_COEF          ( ( TLE4997_VOUT_MAX * TLE4997_ADC_MAX ) / TLE4997_ADC_REF_VOLTAGE )


typedef enum {
    TLE4997_API_SENSOR_ID_ONE = 0,      /* TLE4997 Hall AN1 */
    TLE4997_API_SENSOR_ID_TWO,          /* TLE4997 Hall AN2 */

    TLE4997_API_SENSOR_ID_MAX

} TLE4997SensorNumber_t;


typedef struct {
    float fHallRatiometry;

} TLE4997Data_t;


typedef struct {
    void *pvCxt;
    TLE4997SensorNumber_t xSensorNumber;
    TLE4997Data_t xData;

} TLE4997_t;


int32_t TLE4997_lInit( void **ppvHandle, TLE4997SensorNumber_t xSensorNumber );
void TLE4997_vDeInit( void **ppvHandle );
int32_t TLE4997_lGetData( void *pvHandle, TLE4997Data_t *pxSensorData );
void TLE4997_vReTrigger( void );
void TLE4997_bHallSpectrum( int16_t *psHallBufferRaw, int32_t *plHallBufferFft, uint32_t ulLength );


typedef struct _hall_data {
    uint16_t array_size;
    uint16_t *adc_hall_array;
} hall_data_t;


hall_data_t* create_hall_struct( uint16_t buff_size );
void delete_hall_struct( hall_data_t* hall_data );


#endif /* TLE4997_API_H */

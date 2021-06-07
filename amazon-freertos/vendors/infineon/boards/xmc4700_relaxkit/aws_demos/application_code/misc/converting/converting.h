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

#ifndef CONVERTING_H
#define CONVERTING_H

#include "sensors_task.h"
#include "mqtt_task.h"

#include "app_types.h"
#include "json/json.h"
#include "json/json_sensor.h"
#include "sensors.h"
#include "statistic.h"


void vSensorsDataToMessage( InfineonSensorsData_t *pxSensorsData, InfineonSensorsMessage_t *pxSensorsMessage );

void vStatDataToJSONStat( StatData_t *pxStatData, SensorContext_t *pxSensor, JsonSensorsStatistic_t xJsonSensorStat );

bool JSON_bGenerateToSend( InfineonSensorsMessage_t *pxSensorsMessage, char *pucJsonBuf, uint32_t ulMaxSize );

void CSV_vGenerateToSend( InfineonSensorsMessage_t *pxSensorsData, uint8_t *pucBuffer );


#endif /* CONVERTING_H */

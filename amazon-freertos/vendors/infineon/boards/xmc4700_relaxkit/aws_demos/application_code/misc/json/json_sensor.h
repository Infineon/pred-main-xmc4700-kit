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

#ifndef JSON_SENSOR_H
#define JSON_SENSOR_H

#include "json.h"
#include "sensors.h"


#define JSON_MESSAGE_PRINT				( 0 )
#define JSON_STATISTIC_FORMAT_FLOAT   	"%.4f"
#define JSON_STATISTIC_FFT_COUNT       	( 128 )
#define JSON_SENSOR_ON_STRING           "on"
#define JSON_SENSOR_STAT_STRING         "stat"
#define JSON_SENSOR_FFT_STRING          "fft"


typedef enum {
	JSON_STATISTIC_SENSOR_DPS368_TEMP_1 = 0,
	JSON_STATISTIC_SENSOR_DPS368_PRESS_1,
	JSON_STATISTIC_SENSOR_DPS368_TEMP_2,
	JSON_STATISTIC_SENSOR_DPS368_PRESS_2,
	JSON_STATISTIC_SENSOR_DPS368_TEMP_3,
	JSON_STATISTIC_SENSOR_DPS368_PRESS_3,
	JSON_STATISTIC_SENSOR_DPS368_TEMP_4,
	JSON_STATISTIC_SENSOR_DPS368_PRESS_4,
	JSON_STATISTIC_SENSOR_DPS368_TEMP_5,
	JSON_STATISTIC_SENSOR_DPS368_PRESS_5,
	JSON_STATISTIC_SENSOR_TLI4971_CURRENT_1,
	JSON_STATISTIC_SENSOR_TLI4971_CURRENT_2,
	JSON_STATISTIC_SENSOR_TLI4971_CURRENT_3,
	JSON_STATISTIC_SENSOR_TLE4997_LINEAR_HALL_1,
	JSON_STATISTIC_SENSOR_TLE4964_HALL_SWITCH_1,
	JSON_STATISTIC_SENSOR_TLE49613K_HALL_LATCH_1,
	JSON_STATISTIC_SENSOR_TLE4913_HALL_SWITCH_1,
	JSON_STATISTIC_SENSOR_TLE49611K_HALL_LATCH_1,
	JSON_STATISTIC_SENSOR_TLI4966G_DOUBLE_HALL_SPEED_1,
	JSON_STATISTIC_SENSOR_TLI4966G_DOUBLE_HALL_DIR_1,
	JSON_STATISTIC_SENSOR_IM69D_MIC_1,
	JSON_STATISTIC_SENSOR_TLI493D_MAGNETIC_X_1,
	JSON_STATISTIC_SENSOR_TLI493D_MAGNETIC_Y_1,
	JSON_STATISTIC_SENSOR_TLI493D_MAGNETIC_Z_1,

    JSON_STATISTIC_SENSOR_MAX

} JsonSensorsStatistic_t;

static char* pcJsonSensorsStatString[] =
{
        "DPS368Temperature_1",         		/* Temperature, dps310/368 */
		"DPS368Pressure_1",            		/* Air pressure, dps310/368 */
        "DPS368Temperature_2",          	/* Temperature, dps310/368 */
		"DPS368Pressure_2",            		/* Air pressure, dps310/368 */
        "DPS368Temperature_3",         		/* Temperature, dps310/368 */
		"DPS368Pressure_3",            		/* Air pressure, dps310/368 */
        "DPS368Temperature_4",            	/* Temperature, dps310/368 */
		"DPS368Pressure_4",            		/* Air pressure, dps310/368 */
        "DPS368Temperature_5",             	/* Temperature, dps310/368 */
		"DPS368Pressure_5",            		/* Air pressure, dps310/368 */
        "TLI4971Current_1",                 /* Current consumption, tli4971 */
		"TLI4971Current_2",         		/* Current consumption, tli4971*/
		"TLI4971Current_3",          		/* Current consumption, tli4971*/
		"TLE4997LinearHall_1",         		/* Linear Hall, tle4997 */
		"TLE4964Hall_1",            		/* Hall Magnetic field value, tle4964 */
		"TLE49613kHall_1",             		/* Hall Magnetic field value, tle4961-3k */
		"TLE4913Hall_1",            		/* Hall Magnetic field value, tle4913 */
		"TLE49611kHall_1",             		/* Hall Magnetic field value, tle4961-1k */
		"TLI4966gDoubleHall_Speed_1",       /* Double Hall Speed, tli4966 */
		"TLI4966gDoubleHall_Dir_1",         /* Double Hall Direction, tli4966 */
		"IM69dMic_1",             			/* Microphone data, im69d130 */
		"TLI493dMagnetic_X_1",              /* Magnetic 3D, tli493d */
		"TLI493dMagnetic_Y_1",              /* Magnetic 3D, tli493d */
		"TLI493dMagnetic_Z_1",              /* Magnetic 3D, tli493d */
};


bool JSON_bSensorAdd( JsonContext_t *pxJsonCxt, SensorContext_t *pxSensorCxt );


#endif /* JSON_SENSOR_H */

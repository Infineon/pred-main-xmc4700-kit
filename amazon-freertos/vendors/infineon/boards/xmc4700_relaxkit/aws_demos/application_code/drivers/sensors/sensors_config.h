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

#ifndef SENSORS_CONFIG_H
#define SENSORS_CONFIG_H

/**
 *  1 - sensor disabled
 *  1 - sensor enabled
 *  2 - sensor data printf in read function
 */


/* Pressure and Temperature sensors */
/* -- SPI connection -- */
#define SENSOR_DPS368_1_ENABLE      ( 1 )
#define SENSOR_DPS368_2_ENABLE      ( 1 )
#define SENSOR_DPS368_3_ENABLE      ( 1 )
/* -- I2C connection -- */
#define SENSOR_DPS368_4_ENABLE      ( 1 )
#define SENSOR_DPS368_5_ENABLE      ( 1 )

/* Magnetic Current sensors */
/* -- ADC connection -- */
#define SENSOR_TLI4971_1_ENABLE     ( 1 )
#define SENSOR_TLI4971_2_ENABLE     ( 1 )
#define SENSOR_TLI4971_3_ENABLE     ( 1 )

/* Linear Hall sensor */
/* -- ADC connection -- */
#define SENSOR_TLE4997_1_ENABLE   	( 1 )

/* Hall sensors */
/* -- GPIO connection -- */
#define SENSOR_TLE4964_1_ENABLE     ( 1 )
#define SENSOR_TLE4961_3K_1_ENABLE  ( 1 )
#define SENSOR_TLE4913_1_ENABLE     ( 1 )
#define SENSOR_TLE4961_1K_1_ENABLE  ( 1 )
#define SENSOR_TLI4966_1_ENABLE     ( 1 )

/* Microphone */
/* -- I2S connection -- */
#define SENSOR_IM69D130_ENABLE      ( 1 )

/* 3D Magnetic sensors */
/* -- I2C connection -- */
#define SENSOR_TLI493D_1_ENABLE     ( 1 )


#endif /* SENSORS_CONFIG_H */

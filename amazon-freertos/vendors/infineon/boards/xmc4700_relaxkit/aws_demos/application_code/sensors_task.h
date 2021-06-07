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

#ifndef SENSORS_TASK_H
#define SENSORS_TASK_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


/* Time between sending messages */
#define SEND_PERIOD_MS 					( 1000 )

/** Stack allocated for the task */
#define sensorstaskSTACK_SIZE           ( 4096 )
/** Priority of the task */
#define sensorstaskPRIORITY             ( tskIDLE_PRIORITY + 2 )


/** @brief Starts the Sensors task */
void vSensorsTaskStart( void );
/** @brief Deletes the Sensors task */
void vSensorsTaskDelete( void );


#endif /* SENSORS_TASK_H */

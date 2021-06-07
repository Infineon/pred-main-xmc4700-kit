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

#ifndef SENSORS_H
#define SENSORS_H

#include "app_error.h"
#include "app_types.h"

#include "sensors_config.h"


#define SENSORS_VECTOR_LEN				( 256 )

#define CURRENT_CONSUMPTION_WORK 		( 0.5F )


enum SENSORS_PARAMETERS_POSITION_IN_VECTOR {

/* Temperature and Pressure sensors */

#if( SENSOR_DPS368_1_ENABLE > 0 )
    DPS368_TEMP_1,
    DPS368_PRESS_1,
#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )
    DPS368_TEMP_2,
    DPS368_PRESS_2,
#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )
    DPS368_TEMP_3,
    DPS368_PRESS_3,
#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )
    DPS368_TEMP_4,
    DPS368_PRESS_4,
#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )
    DPS368_TEMP_5,
    DPS368_PRESS_5,
#endif

/* Magnetic Current sensors */

#if( SENSOR_TLI4971_1_ENABLE > 0 )
    TLI4971_CURRENT_1,
#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )
    TLI4971_CURRENT_2,
#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )
    TLI4971_CURRENT_3,
#endif

/* Linear Hall sensor */

#if( SENSOR_TLE4997_1_ENABLE > 0 )
    TLE4997_LINEAR_HALL_1,
#endif

#if( SENSOR_TLE4997_2_ENABLE > 0 )
    TLE4997_LINEAR_HALL_2,
#endif

/* Hall sensors */

#if( SENSOR_TLE4964_1_ENABLE > 0 )
	TLE4964_HALL_SWITCH_1,
#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )
	TLE49613K_HALL_LATCH_1,
#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )
	TLE4913_HALL_SWITCH_1,
#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )
	TLE49611K_HALL_LATCH_1,
#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )
    TLI4966G_DOUBLE_HALL_SPEED_1,
	TLI4966G_DOUBLE_HALL_DIR_1,
#endif
	
/* Microphone */

#if( SENSOR_IM69D130_ENABLE > 0 )
    IM69D_MIC_1,
#endif

/* 3D Magnetic sensors */

#if( SENSOR_TLI493D_1_ENABLE > 0 )
    TLI493D_MAGNETIC_X_1,
	TLI493D_MAGNETIC_Y_1,
	TLI493D_MAGNETIC_Z_1,
#endif

/* Max sensors number of user configure */
	PARAMETERS_NUMBER
};

enum SENSORS_POSITION_IN_VECTOR {

/* Temperature and Pressure sensors */

#if( SENSOR_DPS368_1_ENABLE > 0 )
    DPS368_1,
#endif

#if( SENSOR_DPS368_2_ENABLE > 0 )
    DPS368_2,
#endif

#if( SENSOR_DPS368_3_ENABLE > 0 )
    DPS368_3,
#endif

#if( SENSOR_DPS368_4_ENABLE > 0 )
    DPS368_4,
#endif

#if( SENSOR_DPS368_5_ENABLE > 0 )
    DPS368_5,
#endif

/* Magnetic Current sensors */

#if( SENSOR_TLI4971_1_ENABLE > 0 )
    TLI4971_1,
#endif

#if( SENSOR_TLI4971_2_ENABLE > 0 )
    TLI4971_2,
#endif

#if( SENSOR_TLI4971_3_ENABLE > 0 )
    TLI4971_3,
#endif

/* Linear Hall sensor */

#if( SENSOR_TLE4997_1_ENABLE > 0 )
    TLE4997_1,
#endif

#if( SENSOR_TLE4997_2_ENABLE > 0 )
    TLE4997_2,
#endif

/* Hall sensors */

#if( SENSOR_TLE4964_1_ENABLE > 0 )
	TLE4964_1,
#endif

#if( SENSOR_TLE4961_3K_1_ENABLE > 0 )
	TLE49613K_1,
#endif

#if( SENSOR_TLE4913_1_ENABLE > 0 )
	TLE4913_1,
#endif

#if( SENSOR_TLE4961_1K_1_ENABLE > 0 )
	TLE49611K_1,
#endif

#if( SENSOR_TLI4966_1_ENABLE > 0 )
    TLI4966G_1,
#endif

/* Microphone */

#if( SENSOR_IM69D130_ENABLE > 0 )
    IM69D_1,
#endif

/* 3D Magnetic sensors */

#if( SENSOR_TLI493D_1_ENABLE > 0 )
    TLI493D_1,
#endif

/* Max sensors number of user configure */
	SENSORS_NUMBER
};

enum SENSORS_SPECTRA_POSITION_IN_VECTOR {

/* Linear Hall sensor */

#if( SENSOR_TLE4997_1_ENABLE > 0 )
    TLE4997_LINEAR_HALL_SPECTRA_1,
#endif

/* Microphone */

#if( SENSOR_IM69D130_ENABLE > 0 )
    IM69D_MIC_SPECTRA_1,
#endif

/* Max spectra sensors number of user configure */
	SENSORS_SPECTRA_NUMBER
};


enum SENSORS_NUMBER_ATTEMP_RESTORE {
    NONE_ATTEMPT = 0,
	ONE_ATTEMPT = 1,
    ATTEMPTS_LIMIT_EXCEEDED = 3
};


/* Ticks count maybe more than 256 SENSORS_VECTOR_LEN */
typedef struct { float vector[PARAMETERS_NUMBER][SENSORS_VECTOR_LEN]; } 		SensorsVector_t;	/* Temp Sensors Vector */
typedef struct { float adc_raw_buf[SENSORS_VECTOR_LEN]; } 						ADCRawBuf_t; 		/* Raw Data from ADC sensors */
typedef struct { int16_t mic_fft_buf[SENSORS_VECTOR_LEN / 2]; } 				MICFftBuf_t; 		/* FFT Data from Microphone */
typedef struct { float stat_buf[PARAMETERS_NUMBER]; } 							StatBuf_t;			/* Temp Statistic */
typedef struct { bool on_buf[SENSORS_NUMBER]; } 								OnBuf_t;			/* Temp Statistic */


/* Data type to collect data from sensors */
typedef struct {
	OnBuf_t bSensorsOn;
	StatBuf_t Min;
	StatBuf_t Max;
	StatBuf_t Mean;
	StatBuf_t Rms;
	StatBuf_t StdDev;
	StatBuf_t Variance;
	ADCRawBuf_t fCurrentBuffer1;
	ADCRawBuf_t fCurrentBuffer2;
	ADCRawBuf_t fCurrentBuffer3;
	ADCRawBuf_t fHallBuffer;
	MICFftBuf_t fMicBuffer;
	SensorsVector_t fSensorsVector;

} InfineonSensorsData_t;

void vBoardOn( void );
void vBoardOff( void );
void vSensorsOn( void );
void vSensorsOff( void );
void vSensorsPreInit( void );
void vSensorsInit( void );
void vSensorsDeInit( void );
void vSensorsRead( InfineonSensorsData_t *pxSensorsData, uint32_t ulTicks );
void vNonTickSensorsRead( InfineonSensorsData_t *pxSensorsData );
int32_t lSensorsReadErrorCheck( uint32_t ulTicks );
void vSensorsStatCalculation( InfineonSensorsData_t *pxSensorsData, uint32_t ulTicks );
void vSensorsAvailability( InfineonSensorsData_t *pxSensorsData );

/** turn off sensors and reset system */
void vFullReset( AppError_t xErrorReason );
/** restore sensors with initialize operation after turning on */
void vSensorsRestore( AppError_t xErrorReason );
/** Restore SPI and I2C bus */
void vSerialInterfaceRestore( void );

void vCsPowerSafety( uint8_t ucState );


#endif /* SENSORS_H */

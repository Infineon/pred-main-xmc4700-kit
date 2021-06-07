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

#ifndef APP_TYPES_H
#define APP_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#include "sensors.h"


#define	BUF_LEN( x )		( (sizeof( x )) / (sizeof( x[0] )) )

/* Structure containing statistics parameters */
typedef struct {
    float fMin; 						//! < Minimum
    float fMax; 						//! < Maximum
    float fMean; 						//! < Mean
    float fRMS; 						//! < Root mean square
    float fStdDev;						//! < Standard deviation
    float fVariance; 					//! < Variance
} StatData_t;


typedef struct { uint16_t data[128]; } FFTData_t; 	//! Spectra characteristics


/* Data type to push the message to the cloud */
typedef struct {
	bool bDPS368On_1;							//! < Boolean availability dps368
	bool bDPS368On_2;							//! < Boolean availability dps368
	bool bDPS368On_3;							//! < Boolean availability dps368
	bool bDPS368On_4;							//! < Boolean availability dps368
	bool bDPS368On_5;							//! < Boolean availability dps368
	bool bTLI4971On_1; 							//! < Boolean availability tli4971
	bool bTLI4971On_2; 							//! < Boolean availability tli4971
	bool bTLI4971On_3; 							//! < Boolean availability tli4971
	bool bTLE4997On_1; 							//! < Boolean availability tle4997
	bool bTLE4964On_1; 						    //! < Boolean availability tle4964
	bool bTLE49613KOn_1; 						//! < Boolean availability tle4961-3k
	bool bTLE4913On_1; 							//! < Boolean availability tle4913
	bool bTLE49611KOn_1; 						//! < Boolean availability tle4961-1k
	bool bTLI4966gOn_1; 						//! < Boolean availability tli4966g
	bool bIM69dOn_1;							//! < Boolean availability im69d130
	bool bTLI493dOn_1; 							//! < Boolean availability tli493d-a2b6
    StatData_t fDPS368Temperature_1; 			//! < Temperature statistic dps368
    StatData_t fDPS368Temperature_2; 			//! < Temperature statistic dps368
    StatData_t fDPS368Temperature_3; 			//! < Temperature statistic dps368
    StatData_t fDPS368Temperature_4; 			//! < Temperature statistic dps368
    StatData_t fDPS368Temperature_5; 			//! < Temperature statistic dps368
    StatData_t fDPS368Pressure_1; 				//! < Air pressure statistic dps368
    StatData_t fDPS368Pressure_2; 				//! < Air pressure statistic dps368
    StatData_t fDPS368Pressure_3; 				//! < Air pressure statistic dps368
    StatData_t fDPS368Pressure_4; 				//! < Air pressure statistic dps368
    StatData_t fDPS368Pressure_5; 				//! < Air pressure statistic dps368
    StatData_t fTLI4971Current_1; 				//! < Current consumption statistic tli4971
    StatData_t fTLI4971Current_2; 				//! < Current consumption statistic tli4971
    StatData_t fTLI4971Current_3; 				//! < Current consumption statistic tli4971
    StatData_t fTLE4997LinearHall_1; 			//! < Linear Hall statistic tle4997
    StatData_t fTLE4964Hall_1; 				    //! < Hall statistic tle4964
    StatData_t fTLE49613kHall_1; 				//! < Hall statistic tle4961-3k
	StatData_t fTLE4913Hall_1; 					//! < Hall statistic tle4913
	StatData_t fTLE49611kHall_1; 					//! < Hall statistic tle4961-1k
    StatData_t fTLI4966gDoubleHall_Speed_1; 	//! < Double Hall Speed statistic tli4966g
    StatData_t fTLI4966gDoubleHall_Dir_1; 		//! < Double Hall Direction statistic tli4966g
    StatData_t fIM69dMic_1;						//! < Microphone statistics im69d130
    StatData_t fTLI493dMagnetic_X_1; 			//! < 3D magnetic statistic tli493d-a2b6
    StatData_t fTLI493dMagnetic_Y_1; 			//! < 3D magnetic statistic tli493d-a2b6
    StatData_t fTLI493dMagnetic_Z_1; 			//! < 3D magnetic statistic tli493d-a2b6
    FFTData_t fIM69dMicSpectra_1; 				//! < Spectra characteristics of the data gathered from the microphone
    FFTData_t fTLE4997HallSpectra_1; 			//! < Spectra characteristics of the data gathered from the hall sensor

} InfineonSensorsMessage_t;

/* Structure containing fields for sensor data */
typedef struct {
    bool bOn;
    bool bInited;
    uint32_t ucErrorCount;
    char *pcName;
    void *pvCxt;
    StatData_t *pxStat;
    FFTData_t *pxFft;

} SensorContext_t;


#endif /* APP_TYPES_H */

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

#ifndef TLx4966_H
#define TLx4966_H

#include "TLx4966_hal.h"
#include "TLx4966_types.h"

/* measure speed by pin polling and interrupt */
#define TLx4966_MODE_INTERRUPT         ( 0 )

/* measure speed by capture timer unit */
#define TLx4966_MODE_CCU_TIMER         ( 1 )

/**
 * @brief Instance handle
 */
typedef struct {
    TLx4966_Status_t       status;            /**< Switch status */
    TLx4966_PowerMode_t    powMode;           /**< Power mode */
    TLx4966_MeasMode_t     measMode;          /**< Measure mode */
    TLx4966_SpeedUnit_t    speedUnit;         /**< Speed measure units */
    uint8_t                polesPair;         /**< Rotor poles pair number */
    TLx4966_HwIntf_t       *hwIntf;           /**< Hardware interface */
    TLx4966_Dir_t          direction;         /**< Direction. Last value measured */
    double                 speed;             /**< Speed. Last value measured */

} TLx4966_Handle_t;



void                TLx4966_Config         ( TLx4966_Handle_t      *pxHandle,
                                            uint8_t               polesPair,
                                            TLx4966_PowerMode_t   powMode,
                                            TLx4966_MeasMode_t    measMode,
                                            TLx4966_SpeedUnit_t   speedUnit,   
                                            TLx4966_HwIntf_t      *hwIntf );

TLx4966_Error_t     TLx4966_Init           ( TLx4966_Handle_t *pxHandle );
TLx4966_Error_t     TLx4966_Enable         ( TLx4966_Handle_t *pxHandle );
TLx4966_Error_t     TLx4966_Disable        ( TLx4966_Handle_t *pxHandle );
void                TLx4966_UpdateSpeed    ( TLx4966_Handle_t *pxHandle );
void                TLx4966_UpdateDirection( TLx4966_Handle_t *pxHandle );
void                TLx4966_UpdateValues   ( TLx4966_Handle_t *pxHandle );
void                TLx4966_GetValues      ( TLx4966_Handle_t *pxHandle, TLx4966_Params_t *params );
TLx4966_Status_t    TLx4966_GetStatus      ( TLx4966_Handle_t *pxHandle );
double              TLx4966_GetSpeed       ( TLx4966_Handle_t *pxHandle );
TLx4966_Dir_t       TLx4966_GetDirection   ( TLx4966_Handle_t *pxHandle );


#endif /* TLx4966_H */

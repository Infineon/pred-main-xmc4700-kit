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

#include <stdlib.h>
#include <stdbool.h>

#include "TLx4966.h"
#include "TLx4966_hal.h"


/**
 * @brief Look-up array for Speed Unit Coefficients
 */
static double TLx4966_SpeedCoeffient[3] =
{
    TLx4966_SPEED_COEF_HZ,
    TLx4966_SPEED_COEF_RADS,
    TLx4966_SPEED_COEF_RPM
};

/**
 * @brief           Configures the sensor pxHandle attributes
 *                  Mandatory hw interfaces: dir, speed, timer.
 *                  Optional  hw interfaces: power (only for switch mode platform).
 * 
 * @param[in,out]   *pxHandle     Pointer to the sensor instance pxHandle
 * @param[in]       polesPair   Rotor poles pair number     
 * @param[in]       powMode     Power mode   
 * @param[in]       measMode    Measuring mode 
 * @param[in]       speedUnit   Speed unit        
 * @param[in]       *hwIntf     Pointer to hardware interface pxHandle
 * @return          void         
 */
void TLx4966_Config( TLx4966_Handle_t       *pxHandle,
                     uint8_t                polesPair,
                     TLx4966_PowerMode_t    powMode,
                     TLx4966_MeasMode_t     measMode,  
                     TLx4966_SpeedUnit_t    speedUnit,    
                     TLx4966_HwIntf_t       *hwIntf )
{
    pxHandle->status    = TLx4966_UNINITED;
    pxHandle->polesPair = polesPair;
    pxHandle->powMode   = powMode;
    pxHandle->measMode  = measMode;
    pxHandle->speedUnit = speedUnit;

    pxHandle->direction = TLx4966_DIR_UNDEF;
    pxHandle->speed     = 0;
    pxHandle->hwIntf    = hwIntf;
}

/**
 * @brief       Initializes the hardware interfaces
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      TLx4966 error code    
 * @retval      TLx4966_OK if success
 * @retval      TLx4966_INTF_ERROR if hardware interface error            
 */
TLx4966_Error_t TLx4966_Init( TLx4966_Handle_t *pxHandle )
{
    TLx4966_Error_t xError = TLx4966_OK;

    if( pxHandle->powMode == TLx4966_POWMODE_SWITCH )
    {
        INTF_ASSERT( pxHandle->hwIntf->power->init() );
    }   

    INTF_ASSERT( pxHandle->hwIntf->dir->init() );
    if( pxHandle->measMode != TLx4966_MEASMODE_TIMER )
    {
        INTF_ASSERT(pxHandle->hwIntf->speed->init() );
    }
    INTF_ASSERT( pxHandle->hwIntf->timer->init() );

    pxHandle->status = TLx4966_INITED;

    return xError;
}

/**
 * @brief       Direction interrupt callback
 *              The sensor instance direction is updated upon interrupt event: rising or falling edge.
 * 
 * @param[in]   pxHandle      Pointer to the sensor entity pxHandle
 * @return      void    
 */
static void TLx4966_DirectionCallback( TLx4966_Handle_t *pxHandle )
{
    TLx4966_IntEvent_t xEvent = pxHandle->hwIntf->dir->intEvent();

    if( xEvent == TLx4966_INT_FALLING_EDGE )
    {
        pxHandle->direction = TLx4966_DIR_LOW;
    }
    else if( xEvent == TLx4966_INT_RISING_EDGE )
    {
        pxHandle->direction = TLx4966_DIR_HIGH;
    }
}

/**
 * @brief       Calculates the speed             
 *              The rising edge of the speed GPIO signal determines the rotating 
 *              period between a pair of poles. The speed is then obtained by applying 
 *              the selected speed unit product coefficient, and dividing between the 
 *              number of poles pairs. 
 * 
 * @note        To be called upon speed GPIO rising edge. 
 * 
 * @param[in]   pxHandle      Pointer to the sensor entity pxHandle
 * @return      void    
 */
static inline void TLx4966_CalculateSpeed( TLx4966_Handle_t *pxHandle )
{
    pxHandle->speed = TLx4966_SpeedCoeffient[pxHandle->speedUnit] / ( (double)pxHandle->polesPair * (double)pxHandle->hwIntf->timer->elapsed() );
}

/**
 * @brief       Speed interrupt callback
 *              The sensor instance instant speed is updated upon rising edge. 
 * 
 * @param[in]   pxHandle      Pointer to the sensor entity pxHandle
 * @return      void    
 */
static void TLx4966_SpeedCallback( TLx4966_Handle_t *pxHandle )
{
    TLx4966_IntEvent_t xEvent = pxHandle->hwIntf->speed->intEvent();

    if( xEvent == TLx4966_INT_RISING_EDGE )
    {
        TLx4966_CalculateSpeed( pxHandle );
        pxHandle->hwIntf->timer->stop();
        pxHandle->hwIntf->timer->start();
    }
}

/**
 * @brief       Enables the sensor
 *              - If the "Switch power mode" is configured, the sensor is powered up.
 *              - If the "Interrupt measuring mode" is configured, the interrupt are enabled. 
 *              - The measuring speed timer is started. 
 *              
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      TLx4966 error code    
 * @retval      TLx4966_OK if success
 * @retval      TLx4966_INTF_ERROR if hardware interface error            
 */
TLx4966_Error_t TLx4966_Enable( TLx4966_Handle_t *pxHandle )
{
    TLx4966_Error_t xError = TLx4966_OK;

    if( pxHandle->powMode == TLx4966_POWMODE_SWITCH )
    {
    	INTF_ASSERT( pxHandle->hwIntf->power->enable() );
    }

    INTF_ASSERT( pxHandle->hwIntf->timer->delay( TLx4966_STARTUP_TIME ) );

    if( pxHandle->measMode == TLx4966_MEASMODE_INTERRUPT )
    {
        INTF_ASSERT( pxHandle->hwIntf->dir->enableInt( (TLx4966_GPIO_IntCallback)TLx4966_DirectionCallback,pxHandle ) );
        INTF_ASSERT( pxHandle->hwIntf->speed->enableInt( (TLx4966_GPIO_IntCallback)TLx4966_SpeedCallback,pxHandle ) );
    }

    pxHandle->hwIntf->timer->start();

    pxHandle->status = TLx4966_ON;

    return xError;
}

/**
 * @brief       Disables the sensor
 *              - If the "Interrupt measuring mode" is configured, the interrupt are enabled. 
 *              - If the "Switch power mode" is configured, the sensor is powered off.
 *              - The measuring speed timer is stopped. 
 *              
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      TLx4966 error code    
 * @retval      TLx4966_OK if success
 * @retval      TLx4966_INTF_ERROR if hardware interface error            
 */
TLx4966_Error_t TLx4966_Disable( TLx4966_Handle_t *pxHandle )
{
    if( pxHandle->measMode == TLx4966_MEASMODE_INTERRUPT )
    {
        INTF_ASSERT( pxHandle->hwIntf->dir->disableInt() );
        INTF_ASSERT( pxHandle->hwIntf->speed->disableInt() );
    }
    if( pxHandle->powMode == TLx4966_POWMODE_SWITCH )
    {
    	INTF_ASSERT( pxHandle->hwIntf->power->disable() );
    }

    pxHandle->hwIntf->timer->stop();

    pxHandle->status = TLx4966_OFF;

    return TLx4966_OK;
}

/**
 * @brief       Updates the sensor speed. 
 *              A rising edge is detected when the gpio voltage level changes from low to high.
 * 
 * @note        To be used in super-loop.           
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      void        
 */
void TLx4966_UpdateSpeed( TLx4966_Handle_t *pxHandle )
{
    /* Timer measurements mode */
    if( pxHandle->measMode == TLx4966_MEASMODE_TIMER )
    {
        TLx4966_CalculateSpeed( pxHandle );
    }
    /* Interrupt or polling measure mode */
    else
    {
        static bool bWaitingRisingEdge = true;

        if( bWaitingRisingEdge && ( pxHandle->hwIntf->speed->read() == TLx4966_GPIO_HIGH ) )
        {
            TLx4966_CalculateSpeed( pxHandle );
            pxHandle->hwIntf->timer->stop();
            pxHandle->hwIntf->timer->start();
            bWaitingRisingEdge = false;
        }
        else if( !bWaitingRisingEdge && ( pxHandle->hwIntf->speed->read() == TLx4966_GPIO_LOW ) )
        {
            bWaitingRisingEdge = true;
        }
    }
}

/**
 * @brief       Updates the rotation direction 
 *              A rising edge is detected when the gpio voltage level changes from low to high.
 * 
 * @note        To be used in super-loop. 
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      void        
 */
inline void TLx4966_UpdateDirection( TLx4966_Handle_t *pxHandle )
{
    pxHandle->direction = pxHandle->hwIntf->dir->read();
}

/**
 * @brief       Updates the rotation direction and speed. 
 * @note        To be used in super-loop. 
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      void        
 */
inline void TLx4966_UpdateValues( TLx4966_Handle_t *pxHandle )
{
    TLx4966_UpdateSpeed( pxHandle );
    TLx4966_UpdateDirection( pxHandle );

#if( TLx4966_MODE_INTERRUPT > 0 )
    /* Check whether the motor has stopped and the old speed is not updated anymore due to missing rising edge event. */
    /* For this case, the motor stops and the last speed is present in the internal struct and not updated anymore. */
    double fSpeedBuffer = TLx4966_SpeedCoeffient[pxHandle->speedUnit] / ( (double)pxHandle->polesPair * (double)pxHandle->hwIntf->timer->elapsed() );
    if( fSpeedBuffer < pxHandle->speed )
    {
    	pxHandle->speed = fSpeedBuffer;
    }
#endif
}

/**
 * @brief       Gets the rotation direction and speed parameters
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @param[out]  *params Pointer to the struct to store the parameter values
 * @return      void        
 */
inline void TLx4966_GetValues( TLx4966_Handle_t *pxHandle, TLx4966_Params_t *params )
{
    params->direction = pxHandle->direction;
    params->speed     = pxHandle->speed;
}

/**
 * @brief       Gets the sensor status
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      TLx4966 status         
 */
inline TLx4966_Status_t TLx4966_GetStatus( TLx4966_Handle_t *pxHandle )
{
    return pxHandle->status;
}

/**
 * @brief       Gets the rotation speed
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      Speed in the unit specified in the configuration         
 */
inline double TLx4966_GetSpeed( TLx4966_Handle_t *pxHandle )
{
    return pxHandle->speed;
}

/**
 * @brief       Gets the rotation direction
 *              The direction definition (clock-wise/anticlock-wise, left/rigth, positive/negative...)
 *              is dependant of the mechanical configuration of the sensor with repect to the
 *              rotor. The library just provide voltage-low/voltage-high directions.
 * @param[in]   pxHandle  Pointer to the sensor entity pxHandle
 * @return      TLx4966 direction
 * @retval      TLx4966_DIR_UNDEF prior initial rotor movement (after initialization)             
 */
inline TLx4966_Dir_t TLx4966_GetDirection( TLx4966_Handle_t *pxHandle )
{
    return pxHandle->direction;
}

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

#include "hall_switch.h"

static HallError_t HALL_SWITCH_prvPowerDisable( HallSwitch_t *pxCxt );
static HallError_t HALL_SWITCH_prvPowerEnable( HallSwitch_t *pxCxt );

static HallError_t prvEnableInterrupt( HallSwitch_t *pxCxt );
static HallError_t prvDisableInterrupt( HallSwitch_t *pxCxt );

/**
 * @param[in]   *output Sensor output GPIO interface pointer
 * @param[in]   cBack   Callback for interrupt mode.
 * @param[in]   *power  Sensor switch power controller GPIO interface pointer. Default NULL will set power mode to MAIN
 * @pre    None
 */
HallError_t HALL_SWITCH_xInit( HallSwitch_t *pxCxt )
{
    HallError_t xErr = HALL_ERROR_NONE;

    pxCxt->status      = HALL_STATUS_UNINITED;
    pxCxt->bfieldVal   = HALL_RESULT_B_FIELD_UNDEF;

    if( pxCxt->powerMode == HALL_POWER_MODE_SWITCH )
    {
        if( ( !pxCxt->power_pin.context ) || ( !pxCxt->power_pin.write_high ) || ( !pxCxt->power_pin.write_low ) )
        {
        	return HALL_ERROR_CONF;
        }

        xErr = pxCxt->power_pin.init( pxCxt->power_pin.context );

        if( xErr != HALL_ERROR_NONE )
        {
        	return xErr;
        }
    }

    if( ( !pxCxt->input_pin.context ) || ( !pxCxt->input_pin.read ) )
    {
    	return HALL_ERROR_CONF;
    }
    xErr = pxCxt->input_pin.init( pxCxt->input_pin.context );

    if( xErr != HALL_ERROR_NONE )
    {
    	return xErr;
    }

    pxCxt->status = HALL_STATUS_INITED;

    return xErr;
}

/**
 * @brief   Hall Switch Destructor
 *          Disables the sensor:
 *              - If "interrupt measuring mode" is enabled, the interrupt is disabled
 *              - If "switch power mode" is configured, the sensor power is disabled
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error
 */
HallError_t  HALL_SWITCH_xDeInit( HallSwitch_t *pxCxt )
{
    HallError_t xErr = HALL_ERROR_NONE;

    xErr = HALL_SWITCH_xDisable( pxCxt );

    pxCxt->status    = HALL_STATUS_UNINITED;
    pxCxt->bfieldVal = HALL_RESULT_B_FIELD_UNDEF;

    return xErr;
}

/**
 * @brief   Enables the sensor
 *          - If "switch power mode " is configured, the sensor is powered up
 *          - If "interrupt measuring mode" is configured, the interrupt is enabled
 * 
 * @pre     Instance has called init()
 * @return  HallSwitch error code 
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error     
 */
HallError_t  HALL_SWITCH_xEnable( HallSwitch_t *pxCxt )
{
    if( !pxCxt->status )
    {
    	return HALL_ERROR_INTF;
    }

    HallError_t xErr = HALL_ERROR_NONE;

    if( pxCxt->powerMode == HALL_POWER_MODE_SWITCH )
    {
        xErr = HALL_SWITCH_prvPowerEnable( pxCxt );
        if( xErr != HALL_ERROR_NONE )
        {
        	return xErr;
        }
    }

    if( pxCxt->measMode == HALL_MEAS_MODE_INTERRUPT )
    {
    	xErr = prvEnableInterrupt( pxCxt );
    	if( xErr != HALL_ERROR_NONE )
    	{
    	   return xErr;
    	}
    }

    pxCxt->status = HALL_STATUS_POWER_ON;

    return xErr;
}

/**
 * @brief   Disables the sensor
 *              - If the "interrupt measuring mode" is configured, the interrupt is disabled 
 *              - If the "switch power mode" is configured, the sensor is powered off
 
 * @pre     Instance has called enable()
 * @return  HallSwitch error code 
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error     
 */
HallError_t HALL_SWITCH_xDisable( HallSwitch_t *pxCxt )
{
    if( !pxCxt->status )
    {
    	return HALL_ERROR_INTF;
    }

    HallError_t xErr = HALL_ERROR_NONE;

    if( pxCxt->measMode == HALL_MEAS_MODE_INTERRUPT )
    {
        xErr = prvDisableInterrupt( pxCxt );
        if( xErr != HALL_ERROR_NONE )
        {
        	return xErr;
        }
    }
    if( pxCxt->powerMode == HALL_POWER_MODE_SWITCH )
    {
        xErr = HALL_SWITCH_prvPowerDisable( pxCxt );
        if( xErr != HALL_ERROR_NONE )
        {
        	return xErr;
        }
    }
    pxCxt->status = HALL_STATUS_POWER_OFF;

    return xErr;
}

/**
 * @brief   Updates instance magnetic field value 
 * 
 *  - Magnetic field present if the GPIO voltage level is low
 *  - Mangnetic field not present if the GPIO voltage level is high
 * 
 *  The "bfieldVal" object member is updated with the read GPIO value.
 * 
 * @pre     Instance has called enable()
 * @return  HallSwitch error code 
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error     
 */
HallError_t HALL_SWITCH_xBFieldUpdate( HallSwitch_t *pxCxt )
{
    if( !pxCxt->status )
    {
    	return HALL_ERROR_INTF;
    }

    HallGpioLevel_t gpiolevel = pxCxt->input_pin.read( pxCxt->input_pin.context );

	if( gpiolevel == HALL_GPIO_LEVEL_LOW )
    {
	    pxCxt->bfieldVal = HALL_RESULT_B_FIELD_ON;
	}
    else if( gpiolevel == HALL_GPIO_LEVEL_HIGH )
    {
        pxCxt->bfieldVal = HALL_RESULT_B_FIELD_OFF;
	}

    return HALL_ERROR_NONE;
}

/**
 * @brief   Gets the sensor status
 * @return  HallSwitch status
 */
HallStatus_t HALL_SWITCH_xStatusGet( HallSwitch_t *pxCxt )
{
    return pxCxt->status;
}

/**
 * @brief   Gets magnetic field 
 * 
 *  This functions returns the last read value updated in the object member bfieldVal variable,
 *  either from a explicit HALL_SWITCH_xBFieldUpdate() call or due to an interrupt event.
 * 
 * @pre     If polling mode is used, HALL_SWITCH_xBFieldUpdate() has to be called previously in order to get the actual value.
 *  
 * @return  HallSwitch Result_t magnetic field value
 * @retval  B_FIELD_ON if magnetic field present
 * @retval  B_FIELD_OFF if magnetic field NOT present
 */
HallResult_t HALL_SWITCH_xBFieldGet( HallSwitch_t *pxCxt )
{
    if( !pxCxt->status )
    {
    	return HALL_RESULT_B_FIELD_UNDEF;
    }

    return pxCxt->bfieldVal;
}

/**
 * @brief   Interrupt mode callback function
 *  
 *  The instance updates on its own bfieldVal member when the interrupt occurs.
 * 
 *  Additionally, the user callback function is executed. 
 * 
 * @return  void
 */
void HALL_SWITCH_vCb( HallSwitch_t *pxCxt )
{
    HallInterrupt_t xEvent = HALL_SWITCH_xBFieldEdgeGet( pxCxt );

    if( xEvent == HALL_INTERRUPT_FALLING_EDGE )
    {
        pxCxt->bfieldVal = HALL_RESULT_B_FIELD_ON;
    }
    else if( xEvent == HALL_INTERRUPT_RISING_EDGE )
    {
       pxCxt->bfieldVal = HALL_RESULT_B_FIELD_OFF;
    }

    if( pxCxt->cBack )
    {
        pxCxt->cBack( pxCxt->bfieldVal );
    }

}

static HallError_t HALL_SWITCH_prvPowerEnable( HallSwitch_t *pxCxt )
{
    if( ( !pxCxt->power_pin.context ) || ( !pxCxt->power_pin.write_high ) || ( !pxCxt->power_pin.write_low ) )
    {
    	return HALL_ERROR_CONF;
    }

#if( HALL_PAL_GPIO_POWER_LOGIC_POSITIVE > 0 )
    pxCxt->power_pin.write_high( pxCxt->power_pin.context );
#else
    pxCxt->power_pin.write_low( pxCxt->power_pin.context );
#endif

    return HALL_ERROR_NONE;
}

static HallError_t HALL_SWITCH_prvPowerDisable( HallSwitch_t *pxCxt )
{
    if( ( !pxCxt->power_pin.context ) || ( !pxCxt->power_pin.write_high ) || ( !pxCxt->power_pin.write_low ) )
    {
    	return HALL_ERROR_CONF;
    }

#if( HALL_PAL_GPIO_POWER_LOGIC_POSITIVE > 0 )
    pxCxt->power_pin.write_low( pxCxt->power_pin.context );
#else
    pxCxt->power_pin.write_high( pxCxt->power_pin.context );
#endif

    return HALL_ERROR_NONE;
}

static HallError_t  prvEnableInterrupt( HallSwitch_t *pxCxt )
{
    if( !pxCxt->input_pin.interrupt_init )
    {
    	return HALL_ERROR_CONF;
    }

    pxCxt->input_pin.interrupt_init();

    return HALL_ERROR_NONE;
}

static HallError_t prvDisableInterrupt( HallSwitch_t *pxCxt )
{
    if( !pxCxt->input_pin.interrupt_deinit )
    {
    	return HALL_ERROR_CONF;
    }
    pxCxt->input_pin.interrupt_deinit();

    return HALL_ERROR_NONE;
}

/**
 * @retval  INT_FALLING_EDGE if falling edge event
 * @retval  INT_RISING_EDGE if rising edge event
 */
HallInterrupt_t HALL_SWITCH_xBFieldEdgeGet( HallSwitch_t *pxCxt )
{
    if( !pxCxt->status )
    {
    	return HALL_ERROR_INTF;
    }

    HallInterrupt_t xEdge = HALL_INTERRUPT_FALLING_EDGE;

    HallGpioLevel_t xVal = pxCxt->input_pin.read( pxCxt->input_pin.context );
    if( xVal == HALL_GPIO_LEVEL_LOW )
    {
        xEdge = HALL_INTERRUPT_FALLING_EDGE;
    }
    else if( xVal == HALL_GPIO_LEVEL_HIGH )
    {
        xEdge = HALL_INTERRUPT_RISING_EDGE;
    }

    return xEdge;
}

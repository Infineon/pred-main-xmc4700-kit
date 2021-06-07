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

#ifndef HALL_SWITCH_H
#define HALL_SWITCH_H

#include <stdint.h>
#include <stdbool.h>

/**< Positive logic. 1 on voltage level high, 0 on voltage low */
/**< Negative logic. 0 on voltage level high, 1 on voltage low */

#define HALL_PAL_GPIO_POWER_LOGIC_POSITIVE  1
#define HALL_PAL_GPIO_INPUT_LOGIC_POSITIVE  1


typedef enum {
    HALL_ERROR_NONE   =  0,      /**< No error */
    HALL_ERROR_INTF   = -1,      /**< Interface error */
    HALL_ERROR_CONF   = -2,      /**< Configuration error */

} HallError_t;


typedef enum {
    HALL_INTERRUPT_FALLING_EDGE   = 0,     /**< Interrupt on falling edge */
    HALL_INTERRUPT_RISING_EDGE    = 1,     /**< Interrupt on rising edge */

} HallInterrupt_t;


typedef enum {
    HALL_GPIO_LEVEL_LOW   = 0,        /**< Level low */
    HALL_GPIO_LEVEL_HIGH  = 1         /**< Level high */

} HallGpioLevel_t;

typedef enum {
    HALL_POWER_MODE_MAIN         = 1,    /**< Same as MCU VDD supply signal */
    HALL_POWER_MODE_SWITCH       = 2,    /**< Switched controlled power from MCU */

} HallPowerMode_t;

typedef enum {
    HALL_STATUS_UNINITED    = 0,         /**< Not initialized */
    HALL_STATUS_INITED      = 1,         /**< Initialized (external interfaces initialized) */
    HALL_STATUS_POWER_ON    = 2,         /**< Power on */
    HALL_STATUS_POWER_OFF   = 3,         /**< Power off */

} HallStatus_t;

typedef enum {
    HALL_MEAS_MODE_POLLING     = 1,    /**< Polling mode */
    HALL_MEAS_MODE_INTERRUPT   = 2,    /**< Interrupt mode */

} HallMeasMode_t;

/**
 * @name  Magnetic field value
 * @{
 */
typedef enum {
    HALL_RESULT_B_FIELD_UNDEF = -1,     /**< Output default high. Undefined at initialization */
    HALL_RESULT_B_FIELD_OFF   =  0,     /**< No magnetic field present. Off. Q output high */
    HALL_RESULT_B_FIELD_ON    =  1,     /**< Magnetic field present. On. Q output low */

} HallResult_t;


/**
 * @brief       Callback function type for interrupt mode
 * @param[in]   Result_t B field value. The interrupt read the B field value and will
 *              pass it to the callback
 * @return      void
 */
typedef void (*CBack_t)(HallResult_t);


typedef struct {
    void* context;
    int32_t (*init)(void*);
    int32_t (*read)(void*);
    void  (*write_high)(void*);
    void  (*write_low)(void*);
    void  (*interrupt_init)(void);
    void  (*interrupt_deinit)(void);

} HallGpio_t;

typedef struct {
    HallStatus_t    status;      /**< Status */
    HallGpio_t input_pin;   /**< Output GPIO hardware interface pointer */
    HallGpio_t power_pin;   /**< Power switch controller mode GPIO hardware interface pointer */
    HallResult_t    bfieldVal;          /**< Magnetic field value */
    CBack_t     cBack;              /**< Interrupt mode callback function  */
    HallMeasMode_t  measMode;           /**< Measuring mode */
    HallPowerMode_t powerMode;          /**< Power mode */

} HallSwitch_t;


/* Public functions */
HallError_t HALL_SWITCH_xInit( HallSwitch_t *pxCxt );
HallError_t HALL_SWITCH_xDeInit( HallSwitch_t *pxCxt );
HallError_t HALL_SWITCH_xEnable( HallSwitch_t *pxCxt );
HallError_t HALL_SWITCH_xDisable( HallSwitch_t *pxCxt );
HallError_t HALL_SWITCH_xBFieldUpdate( HallSwitch_t *pxCxt );
HallStatus_t HALL_SWITCH_xStatusGet( HallSwitch_t *pxCxt );
HallResult_t HALL_SWITCH_xBFieldGet( HallSwitch_t *pxCxt );
void HALL_SWITCH_vCb( HallSwitch_t *pxCxt );

/* protected functions */
HallInterrupt_t HALL_SWITCH_xBFieldEdgeGet( HallSwitch_t *pxCxt );


#endif /* HALL_SWITCH_H */

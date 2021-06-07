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

#ifndef TLX493D_INTERFACE_H
#define TLX493D_INTERFACE_H

#include "FreeRTOS.h"
#include "pal/pal_tlx493_i2c.h"

#define TLX493D_PRINT_DEBUG_INFO    0

/*! \brief Function Header: (uint8_t addr, uint8_t *data, uint8_t count)
 *
 * I2C read command must have a header precisely of type:
 * (uint8_t addr, uint8_t *data, uint8_t count):
 * \param addr The I2C address of the sensor
 * \param data The array that the function will read to
 * \param count The number of bytes the function will read
 *
 * \code{.c}
 * // =================== EXAMPLE ===================
 * // Read 10 bytes from the I2C device with address 0x63
 * // to the array data_ptr
 * // The error code will be written to error. On success
 * // it will be 0 (Zero).
 * uint8_t data_ptr[10];
 * error = _I2C_read(0x23, data_ptr, 10);
 * \endcode
 * */
#define _I2C_read 			I2C_INT_xReadBlock


/*! \brief Function Header: (uint8_t addr, const uint8_t* data, uint8_t count)
 *
 * I2C write command must have a header precisely of type:
 * (uint8_t addr, const uint8_t* data, uint8_t count), where:
 * \param addr Is the I2C address to read from data is the;
 * \param data is the array that the function will read to
 * \param count is the number of bytes the function will read
 *
 * \code{.c}
 * // =============== EXAMPLE ================
 * uint8_t payload[] = {5, 1, 2, 3};
 * // write 4 bytes from payload to the I2C device with address 0x23
 * error = _I2C_write(0x23, payload, 4);
 * \endcode
 * */
#define _I2C_write 			I2C_INT_xWriteBlock

/*! \brief Function Header: (void)
 *
 * _I2C_recover should take no parameter. It will write the
 * recover address (FF) on the I2C bus
 * \code{.c}
 * // ============ EXAMPLE ==============
 * // Perform am I2C recovery command
 * _I2C_recover();
 * \endcode
 * */
#define _I2C_recover() 			I2C_INT_vWriteRecover()


/*! \brief Function Header: (void)
 *
 * _I2C_reset should take no parameter. It will write the
 * reset address (00) on the I2C bus
 * \code{.c}
 * // ============ EXAMPLE ==============
 * // Perform am I2C reset command
 * _I2C_reset();
 * \endcode
 * */
#define _I2C_reset() 			I2C_INT_vWriteReset()


/*! \brief Function Header: (bool high)
 *
 * \param high A value of <b> true </b> will set the ADDR pin HIGH at sensor power up,
 * 	and a value of <b> false </b> will set the ADDR pin to LOW at sensor power up.
 *
 * Set the desired level on ADDR(SDA) pin and wait at least 200us.
 * Header should be of type (bool high) where:
 * _SET_ADDR_AND_WAIT(true) will set the ADDR(SDA) line to HIGH and then wait
 * for at least 200us.
 * _SET_ADDR_AND_WAIT(false) will set the ADDR(SDA) line to LOW and then wait for at least 200us.
 * Finally, the SDA line should be set back to HIGH.
 * \code{.c}
 * // =========== EXAMPLE ===========
 * // set voltage on ADDR pin to low and wait for sensor startup
 * _SET_ADDR_AND_WAIT(false);
 * \endcode
 * */
//#define _SET_ADDR_AND_WAIT(high)	GPIO_set_addr_wait(high)
#define _SET_ADDR_AND_WAIT( high )

/*! \brief Function Header: (void)
 *
 * Set the pin responsible with supplying the sensor voltage to HIGH.
 * The function will be called with no arguments.
 * \code{.c}
 * // ============ EXAMPLE ==============
 * // Power Up the sensor
 * _POWER_ENABLE();
 * \endcode
 * */
//#define _POWER_ENABLE()			GPIO_sensor_supply(true)
#define _POWER_ENABLE()


/*! \brief Function Header: (void)
 *
 * Set the pin responsible with supplying the sensor voltage to LOW.
 * The function will be called with no arguments.
 * \code{.c}
 * // ============ EXAMPLE ==============
 * // Power Down the sensor
 * _POWER_DISABLE();
 * \endcode
 * */
//#define _POWER_DISABLE()		GPIO_sensor_supply(false)
#define _POWER_DISABLE()

/*! \brief Function Header: (void *data, uint32_t count)
 *
 * Offers a method to log a string. The header of the method
 * should be of type (void *data, uint32_t count)
 * \param data An array of unit8_t to be written
 * \param count The number of bytes to be written
 * \code{.c}
 * // ============ EXAMPLE ==============
 * // log the string 'Example'
 * _LOG_STR("Example", sizeof("Example") - 1);
 * \endcode
 * */
#define _LOG_STR				UART_write

#if TLX493D_PRINT_DEBUG_INFO
#define dbg_log( str ) configPRINTF(( str ))
#else
#define dbg_log( str )
#endif
/*! \brief (Optional) Function to be called when a sensor interrupt is received
 * */
//#define _DATA_READY


#endif /* TLX493D_INTERFACE_H */

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

#ifndef TLE_AW2B6_DRIVER_H
#define TLE_AW2B6_DRIVER_H

#include "TLE_AW2B6_defines.h"


/*! \brief Read register values from the sensor, starting with the register
 * at address 0 up to register <b>upto</b>
 *
 * \param addr the I2C address of the sensor;
 * \param regmap Register map structure used to store the read
 * 	registers of the sensor.
 * \param upto The reading process will start with register 0 and will continue
 * 	incrementally up to the register <b>upto</b>.
 * */
int32_t TLE493D_AW2B6_lReadRegs( uint8_t addr, TLE493D_Regmap_t *pxRegMap, uint8_t ucUpTo );


/*! \brief Write the <b>data</b> value to the <b>reg_addr</b> register on the sensor with the
 * I2C address <b>i2c_addr</b>.
 *
 * \param i2c_addr I2C address of the sensor.
 * \param reg_addr Address of the register that is to be written.
 * \param data Data to be written to the register.
 * */
int32_t TLE493D_AW2B6_lWriteReg( uint8_t ucSlaveAddressI2C, uint8_t ucRegAddr, uint8_t ucData );


/*! \brief Write <b>count</b> bytes from the <b>data</b> array to the sensor with
 * the I2C address <b>addr</b>, starting with the register <b>addr_reg_start</b>.
 *
 * \param addr I2C sensor address
 * \param addr_reg_start Address of the first register to be written
 * \param data Data to be written to the registers
 * \param count Number of bytes to be written
 *  */
int32_t TLE493D_AW2B6_lWriteRegMulti( uint8_t ucSlaveAddressI2C, uint8_t ucRegAddrStart, uint8_t *pucData, uint8_t ucCount );


#endif /* TLE_AW2B6_DRIVER_H */

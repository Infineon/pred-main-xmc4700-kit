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

#ifndef TLV_A1B6_DRIVER_H
#define TLV_A1B6_DRIVER_H

#include <stdint.h>

#include "tlv_a1b6_defines.h"
#include "TLx493D/tlx493d_interface.h"


/*! \brief Data structure describing the TLV493D read registers. */
typedef struct {
	uint8_t Bx, By, Bz;
	uint8_t Temp;
	uint8_t Bx2, Bz2;
	uint8_t Temp2;
	uint8_t FactSet1, FactSet2, FactSet3;

} TLV493D_RegMapRead_t;


/*! \brief Data structure describing the TLV493D write registers. */
typedef struct {
	uint8_t Res;
	uint8_t MOD1;
	uint8_t Res2;
	uint8_t MOD2;

} TLV493D_RegMapWrite_t;


/*! \brief Read register values from the sensor, starting with the register
 * at address 0 up to register <b>upto</b>.
 *
 * \param ucAddress the I2C address of the sensor;
 * \param pxRegMap register map read structure used to store the read
 * 	registers of the sensor.
 * \param ucUpTo The reading process will start with register 0 and will continue
 * incrementally up to the register <b>ucUpTo</b>
 *
 * \return Error code.
 * */
int32_t TLV493D_A1B6_lReadRegs( uint8_t ucAddress, TLV493D_RegMapRead_t *pxRegMap, uint8_t ucUpTo );

/*! \brief Write the register data from regmap to the sensor registers.
 *
 * If the <b>pxRegMapCheck</b> pointer points to a valid structure (is not NULL),
 * the reserved registers data from the <b>pxRegMap</b> will be overwritten with the
 * reserved data from <b>pxRegMapCheck</b>. This ensures that the reserved data read
 * from the sensor is properly written back to the sensor. This overwrite will need
 * to happend only once, as the corrections  will be stored inside <b>pxRegMap</b>.
 *
 * \return Error code.
 * */
int32_t TLV493D_A1B6_lWriteRegs( uint8_t ucAddress, TLV493D_RegMapWrite_t *pxRegMap, const TLV493D_RegMapRead_t *pxRegMapCheck );


#endif /* TLV_A1B6_DRIVER_H */

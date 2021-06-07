
/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015-2020, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2014-06-16:
 *     - Initial version<br>
 * 2015-08-28:
 *     - Added CLOCK_XMC1_Init conditionally
 * 2018-08-08:
 *     - Add creation of projectData.bak file
 * 2019-01-30:
 *     - Fix creation of projectData.bak file
 * 2019-04-29:
 *     - Make DAVE_Init() weak, the user can reimplement the function
 *
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "DAVE.h"

/***********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/

/*******************************************************************************
 * @brief This function initializes the APPs Init Functions.
 *
 * @param[in]  None
 *
 * @return  DAVE_STATUS_t <BR>
 ******************************************************************************/
__WEAK DAVE_STATUS_t DAVE_Init(void)
{
  DAVE_STATUS_t init_status;
  
  init_status = DAVE_STATUS_SUCCESS;
     /** @Initialization of APPs Init Functions */
     init_status = (DAVE_STATUS_t)CLOCK_XMC4_Init(&CLOCK_XMC4_0);

  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of I2C_MASTER APP instance I2C_MASTER_0 */
	 init_status = (DAVE_STATUS_t)I2C_MASTER_Init(&I2C_MASTER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of PIN_INTERRUPT APP instance ISM43340_RDY_PIN_INTERRUPT */
	 init_status = (DAVE_STATUS_t)PIN_INTERRUPT_Init(&ISM43340_RDY_PIN_INTERRUPT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MAIN_BOARD_LED1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MAIN_BOARD_LED1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MAIN_BOARD_LED2 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MAIN_BOARD_LED2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_YELLOWISH_GREEN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_YELLOWISH_GREEN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_YELLOW */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_YELLOW); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_RED */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_RED); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance SENSORS_POWER */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&SENSORS_POWER); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance OPTIGA_RESET */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&OPTIGA_RESET); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DPS368_CS1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DPS368_CS1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DPS368_CS2 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DPS368_CS2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DPS368_CS3 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DPS368_CS3); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LTC_CS */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LTC_CS); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance mBUS1_RESET */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&mBUS1_RESET); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance mBUS1_CS */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&mBUS1_CS); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance mBUS1_PWM */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&mBUS1_PWM); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance mBUS1_INT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&mBUS1_INT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ISM_CS */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ISM_CS); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance ISM_RST */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&ISM_RST); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance I2C_INT1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&I2C_INT1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance I2C_INT2 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&I2C_INT2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance TLE4913_DATA_1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&TLE4913_DATA_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance TLE49611K_DATA_1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&TLE49611K_DATA_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance TLE49613K_DATA_1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&TLE49613K_DATA_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance TLE4964_DATA_1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&TLE4964_DATA_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance TLI4966G_DIRECTION_Q1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&TLI4966G_DIRECTION_Q1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance mBUS1_AN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&mBUS1_AN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DEBUG_PIN1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DEBUG_PIN1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DEBUG_PIN2 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DEBUG_PIN2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of ADC_MEASUREMENT_ADV APP instance ADC_MEASUREMENT_ADV_0 */
	 init_status = (DAVE_STATUS_t)ADC_MEASUREMENT_ADV_Init(&ADC_MEASUREMENT_ADV_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of ADC_MEASUREMENT_ADV APP instance ADC_MEASUREMENT_ADV_1 */
	 init_status = (DAVE_STATUS_t)ADC_MEASUREMENT_ADV_Init(&ADC_MEASUREMENT_ADV_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of ADC_MEASUREMENT_ADV APP instance ADC_MEASUREMENT_ADV_2 */
	 init_status = (DAVE_STATUS_t)ADC_MEASUREMENT_ADV_Init(&ADC_MEASUREMENT_ADV_2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of ADC_MEASUREMENT_ADV APP instance ADC_MEASUREMENT_ADV_3 */
	 init_status = (DAVE_STATUS_t)ADC_MEASUREMENT_ADV_Init(&ADC_MEASUREMENT_ADV_3); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of GLOBAL_CCU4 APP instance GLOBAL_CCU4_0 */
	 init_status = (DAVE_STATUS_t)GLOBAL_CCU4_Init(&GLOBAL_CCU4_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of SPI_MASTER APP instance SPI_MASTER_0 */
	 init_status = (DAVE_STATUS_t)SPI_MASTER_Init(&SPI_MASTER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of CAPTURE APP instance CAPTURE_TLI4966G_SPEED */
	 init_status = (DAVE_STATUS_t)CAPTURE_Init(&CAPTURE_TLI4966G_SPEED); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of GLOBAL_CCU4 APP instance GLOBAL_CCU4_2 */
	 init_status = (DAVE_STATUS_t)GLOBAL_CCU4_Init(&GLOBAL_CCU4_2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of I2S_CONFIG APP instance I2S_CONFIG_0 */
	 init_status = (DAVE_STATUS_t)I2S_CONFIG_Init(&I2S_CONFIG_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance I2S_RECEIVE_INTERRUPT */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&I2S_RECEIVE_INTERRUPT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance I2S_DATA_MR */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&I2S_DATA_MR); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance I2S_SCK */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&I2S_SCK); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance I2S_LRCLK */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&I2S_LRCLK); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance BOARD_POWER */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&BOARD_POWER); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MBUS_PWR_RST */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MBUS_PWR_RST); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of UART APP instance UART_0 */
	 init_status = (DAVE_STATUS_t)UART_Init(&UART_0); 
   }  
  return init_status;
} /**  End of function DAVE_Init */


/*********************************************************************************************************************
* DAVE APP Name : I2S_CONFIG       APP Version: 4.0.6
*
* NOTE:
* This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
*********************************************************************************************************************/

/**
 * @file i2c_config_conf.c
 * @date 2016-05-30
 *
 * NOTE:
 * This file is generated by DAVE-4. Any manual modification done to this file will be lost when the code is
 * regenerated.
 *
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
 * 2016-07-30:
 *     - Initial version for DAVEv4
 * 2016-08-17:
 *     - Changed to generate protocol interrupt node configuration by default.
 *
 * @endcond
 *
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "i2s_config.h"


/**********************************************************************************************************************
* FUNCTION PROTOTYPE
**********************************************************************************************************************/
/* USIC channel initialization function */
void I2S_CONFIG_0_lInit(void);

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
/* USIC channel configuration for I2S */
const XMC_I2S_CH_CONFIG_t I2S_CONFIG_0_channel_config =
{
  .baudrate = 655312U,
  .data_bits = 16U,
  .frame_length = 32U,
  .data_delayed_sclk_periods = 1U,
  .wa_inversion = XMC_I2S_CH_WA_POLARITY_DIRECT,
  .bus_mode = XMC_I2S_CH_BUS_MODE_MASTER
};

/* I2S_CONFIG APP configuration structure */
const I2S_CONFIG_CONF_t I2S_CONFIG_0_config = 
{
  .channel_config   = &I2S_CONFIG_0_channel_config,
  .i2s_config_init_func = I2S_CONFIG_0_lInit
};

/* APP handle structure */
const I2S_CONFIG_t I2S_CONFIG_0 = 
{
  .channel = XMC_I2S0_CH1,
  .config  = &I2S_CONFIG_0_config
};

/***********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/
/* Channel initialization function */
void I2S_CONFIG_0_lInit()
{
  /* Initialize USIC channel in I2S mode */
  XMC_I2S_CH_Init(XMC_I2S0_CH1, &I2S_CONFIG_0_channel_config);

  /* Set the frame length, word length and system word length */
  XMC_I2S_CH_SetFrameLength(XMC_I2S0_CH1, 32U);
  XMC_I2S_CH_SetWordLength(XMC_I2S0_CH1, 16U);
  XMC_I2S_CH_SetSystemWordLength(XMC_I2S0_CH1, 32U);

  /* Set MSB data shift direction */
  XMC_I2S_CH_SetBitOrderMsbFirst(XMC_I2S0_CH1);

  /* Set input source for input stage dx0 (receive pin) */
  XMC_I2S_CH_SetInputSource(XMC_I2S0_CH1, XMC_I2S_CH_INPUT_DIN0, 2U);

  /* Configure the clock polarity and clock delay */
  XMC_USIC_CH_ConfigureShiftClockOutput(XMC_I2S0_CH1, XMC_USIC_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED,
									   XMC_USIC_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);

  /* Set the service request line for the Data Lost, Baud Rate Generator and I2S protocol events */
  XMC_USIC_CH_SetInterruptNodePointer(XMC_I2S0_CH1, XMC_USIC_CH_INTERRUPT_NODE_POINTER_PROTOCOL, 0U);

  /* Set the service request line for the standard receive buffer event */
  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_I2S0_CH1, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 5U);

  /* Set the service request line for the alternative receive buffer / receive buffer error event */
  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_I2S0_CH1, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, 5U);

  /* Enable the standard receive buffer event */
  XMC_USIC_CH_RXFIFO_EnableEvent(XMC_I2S0_CH1, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD);

 /* Enable the alternative receive buffer event */
  XMC_USIC_CH_RXFIFO_EnableEvent(XMC_I2S0_CH1, XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);

  /* Configure the receive FIFO */
  XMC_USIC_CH_RXFIFO_Configure(I2S_CONFIG_0.channel, 0U, XMC_USIC_CH_FIFO_SIZE_2WORDS, 1U);
}
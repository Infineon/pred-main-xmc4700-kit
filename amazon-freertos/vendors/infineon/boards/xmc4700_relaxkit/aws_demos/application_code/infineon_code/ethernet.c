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

#include "xmc_gpio.h"

#include "ethernet.h"

XMC_ETH_MAC_t eth_mac =
{
  .regs = ETH0
};

static XMC_ETH_PHY_CONFIG_t eth_phy_config =
{
  .interface = XMC_ETH_LINK_INTERFACE_RMII,
  .enable_auto_negotiate = true,
};

int32_t ETEHRNET_Init(void)
{
  XMC_ETH_MAC_PORT_CTRL_t port_control;
  XMC_GPIO_CONFIG_t gpio_config;

  XMC_ETH_MAC_Enable(&eth_mac);
  XMC_ETH_MAC_SetManagmentClockDivider(&eth_mac);
 
  gpio_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(RXD0, &gpio_config);
  XMC_GPIO_Init(RXD1, &gpio_config);
  XMC_GPIO_Init(CLK_RMII, &gpio_config);
  XMC_GPIO_Init(CRS_DV, &gpio_config);
  XMC_GPIO_Init(RXER, &gpio_config);
  XMC_GPIO_Init(MDIO, &gpio_config);

  port_control.mode = XMC_ETH_MAC_PORT_CTRL_MODE_RMII;
  port_control.rxd0 = XMC_ETH_MAC_PORT_CTRL_RXD0_P2_2;
  port_control.rxd1 = XMC_ETH_MAC_PORT_CTRL_RXD1_P2_3;
  port_control.clk_rmii = XMC_ETH_MAC_PORT_CTRL_CLK_RMII_P15_8;
  port_control.crs_dv = XMC_ETH_MAC_PORT_CTRL_CRS_DV_P15_9;
  port_control.rxer = XMC_ETH_MAC_PORT_CTRL_RXER_P2_4;
  port_control.mdio = XMC_ETH_MAC_PORT_CTRL_MDIO_P2_0;
  XMC_ETH_MAC_SetPortControl(&eth_mac, port_control);

  XMC_GPIO_SetHardwareControl(MDIO, XMC_GPIO_HWCTRL_PERIPHERAL1);

  gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE;
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_7_AF_ETH0_MDC);
  XMC_GPIO_Init(MDC, &gpio_config);

  int32_t status = XMC_ETH_PHY_Init(&eth_mac, ETH_PHY_ADDR, &eth_phy_config);
  if (status != XMC_ETH_PHY_STATUS_OK)
  {
	return XMC_ETH_PHY_STATUS_ERROR;
  }

  gpio_config.mode = (XMC_GPIO_MODE_t)(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_8_AF_ETH0_TXD0);
  XMC_GPIO_Init(TXD0, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_9_AF_ETH0_TXD1);
  XMC_GPIO_Init(TXD1, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_5_AF_ETH0_TX_EN);
  XMC_GPIO_Init(TX_EN, &gpio_config);

  return 0;
}

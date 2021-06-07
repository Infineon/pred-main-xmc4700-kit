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

#ifndef ETHERNET_H
#define ETHERNET_H

#include "xmc_eth_mac.h"
#include "xmc_eth_phy.h"

#define ETH_PHY_ADDR 0

#define RXD1     P2_3
#define RXD0     P2_2
#define RXER     P2_4
#define CLK_RMII P15_8
#define CRS_DV   P15_9

#define TX_EN    P2_5
#define TXD1     P2_9
#define TXD0     P2_8

#define MDIO     P2_0
#define MDC      P2_7

#define ETH_IRQ_PRIO 62

extern XMC_ETH_MAC_t eth_mac;

#ifdef __cplusplus
extern "C" {
#endif

int32_t ETEHRNET_Init(void);

#ifdef __cplusplus
}
#endif

#endif

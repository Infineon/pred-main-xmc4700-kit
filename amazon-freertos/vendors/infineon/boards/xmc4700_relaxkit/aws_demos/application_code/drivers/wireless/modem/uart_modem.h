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

#ifndef UART_MODEM_H
#define UART_MODEM_H

#include "DAVE.h"

#define UART_MODEM_INSTANCE                 UART_0

#define UART_MODEM_RX_BUFFER_SIZE 			( 2048 )
#define UART_MODEM_TX_BUFFER_SIZE           ( 2048 )


typedef void ( *pUartModemCB )();

/* Custom UART initialization */
void UART_MODEM_vInit( void );

/* Copy received bytes into data. Max data (in bytes) is setted by len. Function returns actual received bytes */
uint16_t UART_MODEM_usReceiveData( uint8_t *pucData, uint16_t usLength );

/* Return true if data is received and ready to copy */
bool UART_MODEM_bRxDataAvaliable( void );

/* Return actual received bytes that are ready to copy */
uint16_t UART_MODEM_usRxDataCount( void );

/* Copy data to buffer and then send in background */
int32_t UART_MODEM_lTransmitData( uint8_t *pucData, uint16_t usLength );

bool UART_MODEM_bTxIsBusy( void );



#endif /* UART_MODEM_H */

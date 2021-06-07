/*********************************************************************************************************************
* DAVE APP Name : SPI_MASTER       APP Version: 4.3.30
*
* NOTE:
* This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
*********************************************************************************************************************/

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
 * 2015-02-16:
 *     - Initial version<br>
 *
 * 2015-05-08:
 *     - C++ guard is removed.<br>
 *     - File is guard is changed according to the coding guidelines<br>
 *
 * 2015-06-20:
 *     - Code generation for parity error is generated after selecting the parity type and enabling the callback in 
 *        interrupt settings tab.<br>
 *
 * @endcond
 *
 */

#ifndef SPI_MASTER_EXTERN_H
#define SPI_MASTER_EXTERN_H

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * EXTERN DECLARATIONS
 ***********************************************************************************************************************/

extern SPI_MASTER_t	SPI_MASTER_0; 

extern void on_end_spi_transmit(void);

extern void on_end_spi_receive(void);

#endif  /* end of SPI_MASTER_EXTERN_H */

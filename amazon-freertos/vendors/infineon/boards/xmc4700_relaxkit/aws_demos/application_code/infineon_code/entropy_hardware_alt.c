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

#define _XOPEN_SOURCE 
#include <stdlib.h>

#include "xmc_common.h"
#include "mbedtls/entropy_poll.h"

#if !defined(CONFIG_USE_OPTIGA)
int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
  (void)data;

  for (int32_t i = 0; i < len / 4; i++, output+=4)
  {
	*(uint32_t *)output = lrand48();
  }

  if ((len % 4) != 0)
  {
  	uint32_t last = lrand48();
  	for (int32_t i = 0; i < len % 4; i++, output += 1) {
  		*output = (unsigned char)(last & 0xff);
  		last = last >> 8;
  	}
  }

  *olen = len;

  return 0;
}
#endif

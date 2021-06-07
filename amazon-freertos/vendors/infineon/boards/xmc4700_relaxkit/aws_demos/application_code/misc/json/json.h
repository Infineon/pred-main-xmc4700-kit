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

#ifndef JSON_H
#define JSON_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct {
    char *pcBuf;
    bool bFirstItemAdded;
    bool bCreated;
    uint8_t ucSubCount;
    uint32_t ulBufSize;
    int32_t lUsedLen;

} JsonContext_t;

#define JSON_STRING_FULL            ( 0 )

#if (JSON_STRING_FULL > 0)
    #define JSON_STRING_END_OF_LINE     "\n"
    #define JSON_STRING_SPACE           " "
#else
    #define JSON_STRING_END_OF_LINE     ""
    #define JSON_STRING_SPACE           ""
#endif


bool JSON_bCreate( JsonContext_t *pxCxt, char *pcBuf, uint32_t ulBufSize );
bool JSON_bSubstringCreate( JsonContext_t *pxCxt, char *pcKey );
bool JSON_bSubstringFinish( JsonContext_t *pxCxt );
bool JSON_bStringAdd( JsonContext_t *pxCxt, char *pcKey, char *pcVal );
bool JSON_bFinish( JsonContext_t *pxCxt, uint32_t *pulLen );


#endif /* JSON_H */

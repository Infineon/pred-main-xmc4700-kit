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

#include <stdbool.h>
#include <stdio.h>

#include "json.h"
#include "string.h"


bool JSON_bCreate ( JsonContext_t *pxCxt, char *pcBuf, uint32_t ulBufSize )
{
    memset( (uint8_t*)pxCxt, 0, sizeof( JsonContext_t ) );
    pxCxt->pcBuf = pcBuf;
    pxCxt->ulBufSize = ulBufSize;
    int32_t lLen = snprintf( pxCxt->pcBuf, pxCxt->ulBufSize, "{" );
    if( lLen <= 0 )
    {
    	return false;
    }
    pxCxt->lUsedLen += lLen;
    pxCxt->bCreated = true;
#if (JSON_STRING_FULL > 0)
    pxCxt->ucSubCount = 1;
#else
    pxCxt->ucSubCount = 0;
#endif

    return true;
}


bool JSON_bSubstringCreate( JsonContext_t *pxCxt, char *pcKey )
{
    char pcSpace[] = "                ";
    if( !pxCxt->bCreated )
    {
    	return false;
    }
    if( strlen( pcSpace ) - 1 <= pxCxt->ucSubCount * 2 )
    {
    	return false;
    }
    pcSpace[pxCxt->ucSubCount * 2] = 0;
#if (JSON_STRING_FULL > 0)
    pxCxt->ucSubCount++;
#endif
    int32_t lLen = snprintf( &pxCxt->pcBuf[pxCxt->lUsedLen], pxCxt->ulBufSize - pxCxt->lUsedLen, "%s%s%s\"%s\"%s:%s{", pxCxt->bFirstItemAdded?",":"", JSON_STRING_END_OF_LINE,
    		pcSpace, pcKey,JSON_STRING_SPACE, JSON_STRING_SPACE );
    if( ( lLen <= 0 ) || ( lLen >= ( pxCxt->ulBufSize - pxCxt->lUsedLen ) ) )
    {
    	return false;
    }

    pxCxt->lUsedLen += lLen;
    pxCxt->bFirstItemAdded = false;

    return true;
}


bool JSON_bSubstringFinish( JsonContext_t *pxCxt )
{
    char pcSpace[] = "                ";

    if( !pxCxt->bCreated )
    {
    	return false;
    }
    if( strlen( pcSpace ) - 1 <= pxCxt->ucSubCount * 2 )
    {
    	return false;
   	}

    pcSpace[pxCxt->ucSubCount * 2] = 0;

    int32_t lLen = snprintf( &pxCxt->pcBuf[pxCxt->lUsedLen], pxCxt->ulBufSize - pxCxt->lUsedLen, "%s%s}", JSON_STRING_END_OF_LINE, pcSpace );

    if( ( lLen <= 0 ) || ( lLen >= ( pxCxt->ulBufSize - pxCxt->lUsedLen ) ) )
    {
    	return false;
    }
    pxCxt->lUsedLen += lLen;
#if (JSON_STRING_FULL > 0)
    pxCxt->ucSubCount--;
#endif

    return true;
}


bool JSON_bStringAdd( JsonContext_t *pxCxt, char *pcKey, char *pcVal )
{
    char pcSpace[] = "                ";

    if( !pxCxt->bCreated )
    {
    	return false;
   	}
    if( strlen( pcSpace ) - 1 <= pxCxt->ucSubCount * 2 )
    {
    	return false;
    }
    pcSpace[pxCxt->ucSubCount * 2] = 0;

    int32_t lLen = snprintf( &pxCxt->pcBuf[pxCxt->lUsedLen], pxCxt->ulBufSize - pxCxt->lUsedLen, "%s%s%s\"%s\"%s:%s%s", pxCxt->bFirstItemAdded?",":"", JSON_STRING_END_OF_LINE,
            pcSpace,
            pcKey, JSON_STRING_SPACE,
            JSON_STRING_SPACE, pcVal );
    if( ( lLen <= 0 ) || ( lLen >= ( pxCxt->ulBufSize - pxCxt->lUsedLen ) ) )
    {
    	return false;
    }
    pxCxt->lUsedLen += lLen;
    pxCxt->bFirstItemAdded = true;

    return true;
}


bool JSON_bFinish( JsonContext_t *pxCxt, uint32_t *pulLen )
{
    if( !pxCxt->bCreated )
    {
    	return false;
    }

    bool bRet = false;

    int32_t lLen = snprintf( &pxCxt->pcBuf[pxCxt->lUsedLen], pxCxt->ulBufSize - pxCxt->lUsedLen, "%s}%s", JSON_STRING_END_OF_LINE,JSON_STRING_END_OF_LINE );

    if( ( lLen <= 0 ) || ( lLen >= ( pxCxt->ulBufSize - pxCxt->lUsedLen ) ) )
    {
    	return false;
    }
    pxCxt->lUsedLen += lLen;

    /* check summary length */
    int32_t lStrLen = strlen( pxCxt->pcBuf );
    if( lStrLen == pxCxt->lUsedLen )
    {
        bRet = true;
        if( pulLen )
        {
            *pulLen = pxCxt->lUsedLen;
        }
    }

    return bRet;
}

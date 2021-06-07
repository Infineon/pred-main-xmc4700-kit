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

#include <string.h>
#include <math.h>

#include "float_to_string.h"


static double PRECISION = 0.01;

/**
 * Double to ASCII
 */
char * dtoa( char *s, float n )
{
    /* handle special cases */
    if( __isnanf(n) )
    {
        strcpy( s, "nan" );
    }
    else if( __isinff(n) )
    {
        strcpy( s, "inf" );
    }
    else if( n == 0.0f )
    {
        strcpy( s, "0" );
    }
    else
    {
        int digit, m, m1;
        char *c = s;
        int neg = ( n < 0 );
        if( neg )
        {
            n = -n;
        }
        /* calculate magnitude */
        m = log10f( n );
        int useExp = ( m >= 14 || (neg && m >= 9) || m <= -9 );
        if( neg )
        {
        	*(c++) = '-';
        }
        /* set up for scientific notation */
        if( useExp )
        {
            if( m < 0 )
            {
            	m -= 1.0f;
            }
            n = n / powf( 10.0f, m );
            m1 = m;
            m = 0;
        }
        if( m < 1.0f )
        {
            m = 0;
        }
        /* convert the number */
        while( n > PRECISION || m >= 0 )
        {
            float weight = powf( 10.0f, m );
            if( weight > 0 && !__isinff(weight) )
            {
                digit = floorf( n / weight );
                n -= (digit * weight);
                *(c++) = '0' + digit;
            }
            if( m == 0 && n > 0 )
            {
                *(c++) = '.';
                if( n <= PRECISION )
                {
                    *(c++) = '0';
                }
            }
            m--;
        }
        if( useExp )
        {
            /* convert the exponent */
            int i, j;
            *(c++) = 'e';
            if (m1 > 0)
            {
                *(c++) = '+';
            }
            else
            {
                *(c++) = '-';
                m1 = -m1;
            }
            m = 0;
            while( m1 > 0 )
            {
                *(c++) = '0' + m1 % 10;
                m1 /= 10;
                m++;
            }
            c -= m;
            for( i = 0, j = m-1; i<j; i++, j-- )
            {
                /* swap without temporary */
                c[i] ^= c[j];
                c[j] ^= c[i];
                c[i] ^= c[j];
            }
            c += m;
        }
        *(c) = '\0';
    }

    return s;
}


/* reverses a string 'str' of length 'len' */
void reverse( char *str, int len )
{
    int i = 0, j = len - 1, temp;
    while( i < j )
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

/* Converts a given integer x to string str[].  d is the number
 * of digits required in output. If d is more than the number
 * of digits in x, then 0s are added at the beginning.
 */
int intToStr( int x, char str[], int d )
{
    int i = 0;
    while( x )
    {
        str[i++] = ( x % 10 ) + '0';
        x = x / 10;
    }

    /* If number of digits required is more, then
     * add 0s at the beginning
     */
    while( i < d )
    {
    	str[i++] = '0';
    }
    reverse( str, i );
    str[i] = '\0';

    return i;
}

/* Converts a floating point number to string. */
char * ftoa( float n, char *resIn )
{
	char * res = resIn;

	if( n<0 )
	{
		res[0] = '-';
		res++;
	}

	n = fabs( n );

	/* Extract integer part */
    int ipart = (int)n;

    int afterpoint = 4;

    /* Extract floating part */
    float fpart = n - (float)ipart;

    /* convert integer part to string */
    int i = intToStr( ipart, res, 1 );

    /* check for display option after point */
    if (afterpoint != 0)
    {
    	/* add dot */
        res[i] = '.';

        /* Get the value of fraction part upto given no.
         * of points after dot. The third parameter is needed
         * to handle cases like 233.007
         */
        fpart = fpart * powf( 10, afterpoint );

        intToStr( (int)fpart, res + i + 1, afterpoint );
    }

    return resIn;
}

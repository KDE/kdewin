/*
   This file is part of the KDE libraries
   Copyright (C) 2005-2007 Christian Ehrlicher <Ch.Ehrlicher@gmx.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KDEWIN_MATH_H
#define KDEWIN_MATH_H

#include <winposix_export.h>

// include everywhere
#include <sys/types.h>

/* regular header from msvc includes */
#define _USE_MATH_DEFINES
#include <../include/math.h>

#include <../include/float.h>

#include <errno.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

#define isnan(x) _isnan(x)
#define finite(x) _finite(x)

// some functions which aren't available with msvc

/* 7.12.5.1 */
// double __cdecl acosh (double);
// float __cdecl acoshf (float);
// long double __cdecl acoshl (long double);

/* 7.12.5.2 */
// double asinh (double)
// float asinhf (float)
// long double asinhl (long double)

/* 7.12.5.3 */
// double atanh (double)
// float atanf  (float)
// long double atanhl (long double)

/* 7.12.8.4 The tgamma functions */
// double tgamma (double)
// float tgammaf (float)
// long double tgammal (long double)

/* 7.12.9.3 */
// float nearbyintf(float)
// double nearbyint(double)
// long double nearbyintl(long double)

/* 7.12.9.4 */
// float rintf (float)
// double rint (double)
// long double rintl (long double)

/* 7.12.9.6 */
// float roundf (float)
// double round (double)
// long double roundl (long double)

/* 7.12.9.7 */
// long lroundf (float)
// long lround (double)
// long lroundl (long double)

/* 7.12.12.2 */
// double fmax (double, double)
// float fmaxf (float, float)
// long double fmaxl (long double, long double)

/* 7.12.12.3 */
// double fmin (double, double)
// float fminf (float, float)
// long double fminl (long double, long double)


/* 7.12.5.1 */
#define acosh(x) cosh(x)
#define acoshf(x) coshf(x)
#define acoshl(x) cosh(x)

/* 7.12.5.2 */
#define asinh(x) sinh(x)
#define asinhf(x) sinhf(x)
#define asinhl(x) sinh(x)

/* 7.12.5.3 */
#define atanh(x) atan(x)
// float atanf  (float);
#define atanhl(x) atan(x)

/* 7.12.8.4 The tgamma functions */
WINPOSIX_EXPORT double tgamma (double);
WINPOSIX_EXPORT float tgammaf (float);
#define tgammal(x) tgamma(x)

/* 7.12.9.3 */
// this is a little bit more complicated - don't raise an exception
// -> set fpu control word bit 5 so it won't generate one
WINPOSIX_EXPORT __inline float nearbyintf(float x)
{
    unsigned int tmpMSW1;
    unsigned int tmpMSW2;
    __asm {
        // get current state
        fnstcw tmpMSW1
    }
    // set bit 5
    tmpMSW2 = tmpMSW1 | 0x00000020;
	__asm {
        // and load
        fldcw tmpMSW2
        // do the job
        fld x
        frndint
        // clear exception
        fclex
        // restore old state
        fldcw tmpMSW1
    }
}

WINPOSIX_EXPORT __inline double nearbyint(double x)
{
    unsigned int tmpMSW1;
    unsigned int tmpMSW2;
    __asm {
        // get current state
        fnstcw tmpMSW1
    }
    // set bit 5
    tmpMSW2 = tmpMSW1 | 0x00000020;
	__asm {
        // and load
        fldcw tmpMSW2
        // do the job
        fld x
        frndint
        // clear exception
        fclex
        // restore old state
        fldcw tmpMSW1
    }
}

WINPOSIX_EXPORT __inline long double nearbyintl(long double x)
{
    unsigned int tmpMSW1;
    unsigned int tmpMSW2;
    __asm {
        // get current state
        fnstcw tmpMSW1
    }
    // set bit 5
    tmpMSW2 = tmpMSW1 | 0x00000020;
	__asm {
        // and load
        fldcw tmpMSW2
        // do the job
        fld x
        frndint
        // clear exception
        fclex
        // restore old state
        fldcw tmpMSW1
    }
}

/* 7.12.9.4 */
WINPOSIX_EXPORT __inline float rintf( float x )
{
    __asm {
        fld x
        frndint
    }
}

WINPOSIX_EXPORT __inline double rint( double x )
{
    __asm {
        fld x
        frndint
    }
}

WINPOSIX_EXPORT __inline long double rintl( long double x )
{
    __asm {
        fld x
        frndint
    }
}

WINPOSIX_EXPORT __inline long lroundf ( float x )
{
  /* Add +/- 0.5, then round towards zero.  */
  float tmp = floorf ( x );
  if (isnan (tmp)
      || tmp > (float)LONG_MAX
      || tmp < (float)LONG_MIN)
    {
      errno = ERANGE;
      /* Undefined behaviour, so we could return anything.  */
      /* return tmp > 0.0F ? LONG_MAX : LONG_MIN;  */
    }
  return (long)tmp;
}

/* 7.12.9.7 (before 7.12.9.6!)*/
WINPOSIX_EXPORT __inline long lround ( double x )
{
  /* Add +/- 0.5 then then round towards zero.  */
  double tmp = floor ( x );
  if (isnan (tmp)
      || tmp > (double)LONG_MAX
      || tmp < (double)LONG_MIN)
    {
      errno = ERANGE;
      /* Undefined behaviour, so we could return anything.  */
      /* return tmp > 0.0 ? LONG_MAX : LONG_MIN;  */
    }
  return (long)tmp;
}

WINPOSIX_EXPORT __inline long lroundl ( long double x )
{
  /* Add +/- 0.5, then round towards zero.  */
  long double tmp = floorl ( x );
  if (isnan (tmp)
      || tmp > (long double)LONG_MAX
      || tmp < (long double)LONG_MIN)
    {
      errno = ERANGE;
      /* Undefined behaviour, so we could return anything.  */
      /* return tmp > 0.0L ? LONG_MAX : LONG_MIN;  */
    }
  return (long)tmp;
}

/* 7.12.9.6 */
WINPOSIX_EXPORT __inline float roundf ( float x )
{
  return (float)lroundf( x );
}

WINPOSIX_EXPORT __inline double round ( double x )
{
  return (double)lround( x );
}

WINPOSIX_EXPORT __inline long double roundl ( long double x )
{
  return (long double)lroundl( x );
}

/* 7.12.12.2 */
WINPOSIX_EXPORT __inline double fmax (double a, double b)
{
    if(isnan(a))
        return b;
    if(isnan(b))
        return a;
    return a > b ? a : b;
}

WINPOSIX_EXPORT __inline float fmaxf (float a, float b)
{
    if(isnan(a))
        return b;
    if(isnan(b))
        return a;
    return a > b ? a : b;
}

WINPOSIX_EXPORT __inline long double fmaxl (long double a, long double b)
{
    if(isnan(a))
        return b;
    if(isnan(b))
        return a;
    return a > b ? a : b;
}

/* 7.12.12.3 */
WINPOSIX_EXPORT __inline double fmin (double a, double b)
{
    if(isnan(a))
        return b;
    if(isnan(b))
        return a;
    return a < b ? a : b;
}

WINPOSIX_EXPORT __inline float fminf (float a, float b)
{
    if(isnan(a))
        return b;
    if(isnan(b))
        return a;
    return a < b ? a : b;
}

WINPOSIX_EXPORT __inline long double fminl (long double a, long double b)
{
    if(isnan(a))
        return b;
    if(isnan(b))
        return a;
    return a < b ? a : b;
}

#ifdef __cplusplus
}

// convenience function to avoid useless casts from int to whatever
__inline long double log(int x)
{
    return logl((long double)x);	
}

__inline long double floor(int x)
{
    return floor((long double)x);	
}

__inline long double pow(int x, int y)
{
    return pow((long double)x, y);	
}
#endif // __cplusplus

#endif /* KDEWIN_MATH_H */

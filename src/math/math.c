/*
  Some definitions from fp_consts(f|l).c from mingw
  public domain
*/

#ifndef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES
#endif
#include <../include/math.h>
#include <../include/float.h>

#include <winposix_export.h>
#include <errno.h>

#define __FLOAT_INF_REP { 0, 0x7f80 }
#define __FLOAT_QNAN_REP { 0, 0xffc0 }  /* { 0, 0x7fc0 }  */
#define __FLOAT_SNAN_REP { 0, 0xff80 }  /* { 1, 0x7f80 }  */
#define __FLOAT_DENORM_REP {1,0}

#define __DOUBLE_INF_REP { 0, 0, 0, 0x7ff0 }
#define __DOUBLE_QNAN_REP { 0, 0, 0, 0xfff8 }  /* { 0, 0, 0, 0x7ff8 }  */
#define __DOUBLE_SNAN_REP { 0, 0, 0, 0xfff0 }  /* { 1, 0, 0, 0x7ff0 }  */
#define __DOUBLE_DENORM_REP {1, 0, 0, 0}

union _ieee_rep {
  unsigned short rep[6];
  float float_val;
  double double_val;
  long double ldouble_val;
} ;

KDEWIN32_EXPORT union _ieee_rep __QNANF = { __FLOAT_QNAN_REP };
KDEWIN32_EXPORT union _ieee_rep __SNANF = { __FLOAT_SNAN_REP };
KDEWIN32_EXPORT union _ieee_rep __INFF = { __FLOAT_INF_REP };
KDEWIN32_EXPORT union _ieee_rep __DENORMF = { __FLOAT_DENORM_REP };

KDEWIN32_EXPORT union _ieee_rep __QNAN = { __DOUBLE_QNAN_REP };
KDEWIN32_EXPORT union _ieee_rep __SNAN  = { __DOUBLE_SNAN_REP };
KDEWIN32_EXPORT union _ieee_rep __INF = { __DOUBLE_INF_REP };
KDEWIN32_EXPORT union _ieee_rep __DENORM = { __DOUBLE_DENORM_REP };
// msdn:
// The representation of long double and double is identical.
// However, long double and double are separate types.
KDEWIN32_EXPORT union _ieee_rep __QNANL = { __DOUBLE_QNAN_REP };
KDEWIN32_EXPORT union _ieee_rep __SNANL  = { __DOUBLE_SNAN_REP };
KDEWIN32_EXPORT union _ieee_rep __INFL = { __DOUBLE_INF_REP };
KDEWIN32_EXPORT union _ieee_rep __DENORML = { __DOUBLE_DENORM_REP };

/* 7.12.5.1 */
// acosh(x) = log (x + sqrt(x * x - 1))
KDEWIN32_EXPORT float acoshf ( float x )
{
  if ( _isnan ( x ) || x < 1.0f ) {
    errno = EDOM;
    return __QNAN.float_val;
  }
  return ( log ( x + sqrt ( x * x - 1.0f ) ) );
}

KDEWIN32_EXPORT double acosh ( double x )
{
  if ( _isnan ( x ) || x < 1.0 ) {
    errno = EDOM;
    return __QNAN.double_val;
  }
  return ( log ( x + sqrt ( x * x - 1.0 ) ) );
}

KDEWIN32_EXPORT long double acoshl ( long double x )
{
  return acosh ( ( double ) x );
}

/* 7.12.5.2 */
// asinh(x) = ln (x + sqrt(x * x + 1))
KDEWIN32_EXPORT float asinhf ( float x )
{
  if ( _isnan ( x ) ) {
    errno = EDOM;
    return __QNAN.float_val;
  }

  x = logf ( x + sqrt ( x * x + 1.0f ) );

  return x;
}

KDEWIN32_EXPORT double asinh ( double x )
{
  if ( _isnan ( x ) ) {
    errno = EDOM;
    return __QNAN.double_val;
  }

  x = log ( x + sqrt ( x * x + 1.0f ) );

  return x;
}

KDEWIN32_EXPORT long double asinhl ( long double x )
{
  return asinh ( ( double ) x );
}

/* 7.12.5.3 */
// atanh(x) = 0.5 * log( (1+x) / (1-x) )
//WINPOSIX_EXPORT float asinhf (float)
KDEWIN32_EXPORT double atanhf ( float x )
{
  if ( _isnan ( x ) || fabsf ( x ) >= 1.0f ) {
    errno = EDOM;
    return __QNAN.float_val;
  }
  return log ( ( 1.0f + x ) / ( 1.0f - x ) ) / 2.0f;
}

KDEWIN32_EXPORT double atanh ( double x )
{
  if ( _isnan ( x ) || fabsf ( x ) >= 1.0 ) {
    errno = EDOM;
    return __QNAN.double_val;
  }
  return log ( ( 1.0 + x ) / ( 1.0 - x ) ) / 2.0;
}

KDEWIN32_EXPORT long double atanhl ( long double x )
{
  return atanh ( ( double ) x );
}

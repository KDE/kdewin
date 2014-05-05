/*
  Some definitions from fp_consts(f|l).c from mingw
  public domain
*/

#if defined(_WIN32_WCE) || defined(_WIN64)
#define DONT_USE_ASM
#endif

#ifndef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES
#endif
#ifndef _WIN32_WCE
#include <../include/math.h>
#include <../include/float.h>
#else
#include <../wcecompat/math.h>
#include <../wcecompat/float.h>
#endif

#include <kdewin_export.h>
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

KDEWIN_EXPORT union _ieee_rep __QNANF = { __FLOAT_QNAN_REP };
KDEWIN_EXPORT union _ieee_rep __SNANF = { __FLOAT_SNAN_REP };
KDEWIN_EXPORT union _ieee_rep __INFF = { __FLOAT_INF_REP };
KDEWIN_EXPORT union _ieee_rep __DENORMF = { __FLOAT_DENORM_REP };

KDEWIN_EXPORT union _ieee_rep __QNAN = { __DOUBLE_QNAN_REP };
KDEWIN_EXPORT union _ieee_rep __SNAN  = { __DOUBLE_SNAN_REP };
KDEWIN_EXPORT union _ieee_rep __INF = { __DOUBLE_INF_REP };
KDEWIN_EXPORT union _ieee_rep __DENORM = { __DOUBLE_DENORM_REP };
/* msdn: */
/* The representation of long double and double is identical. */
/* However, long double and double are separate types. */
KDEWIN_EXPORT union _ieee_rep __QNANL = { __DOUBLE_QNAN_REP };
KDEWIN_EXPORT union _ieee_rep __SNANL  = { __DOUBLE_SNAN_REP };
KDEWIN_EXPORT union _ieee_rep __INFL = { __DOUBLE_INF_REP };
KDEWIN_EXPORT union _ieee_rep __DENORML = { __DOUBLE_DENORM_REP };

/* 7.12.5.1 */
/* acosh(x) = log (x + sqrt(x * x - 1)) */
KDEWIN_EXPORT float acoshf ( float x )
{
  if ( _isnan ( x ) || x < 1.0f ) {
    errno = EDOM;
    return __QNAN.float_val;
  }
  return ( log ( x + sqrt ( x * x - 1.0f ) ) );
}

KDEWIN_EXPORT double acosh ( double x )
{
  if ( _isnan ( x ) || x < 1.0 ) {
    errno = EDOM;
    return __QNAN.double_val;
  }
  return ( log ( x + sqrt ( x * x - 1.0 ) ) );
}

KDEWIN_EXPORT long double acoshl ( long double x )
{
  return acosh ( ( double ) x );
}

/* 7.12.5.2 */
/* asinh(x) = ln (x + sqrt(x * x + 1)) */
KDEWIN_EXPORT float asinhf ( float x )
{
  if ( _isnan ( x ) ) {
    errno = EDOM;
    return __QNAN.float_val;
  }

  x = logf ( x + sqrt ( x * x + 1.0f ) );

  return x;
}

KDEWIN_EXPORT double asinh ( double x )
{
  if ( _isnan ( x ) ) {
    errno = EDOM;
    return __QNAN.double_val;
  }

  x = log ( x + sqrt ( x * x + 1.0 ) );

  return x;
}

KDEWIN_EXPORT long double asinhl ( long double x )
{
  return asinh ( ( double ) x );
}

/* 7.12.5.3 */
/* atanh(x) = 0.5 * log( (1+x) / (1-x) ) */
/*KDEWIN_EXPORT float asinhf (float) */
#if _MSC_VER < 1800
KDEWIN_EXPORT double atanhf ( float x )
{
  if ( _isnan ( x ) || fabsf ( x ) >= 1.0f ) {
    errno = EDOM;
    return __QNAN.float_val;
  }
  return log ( ( 1.0f + x ) / ( 1.0f - x ) ) / 2.0f;
}

KDEWIN_EXPORT double atanh ( double x )
{
  if ( _isnan ( x ) || fabsf ( x ) >= 1.0 ) {
    errno = EDOM;
    return __QNAN.double_val;
  }
  return log ( ( 1.0 + x ) / ( 1.0 - x ) ) / 2.0;
}

KDEWIN_EXPORT long double atanhl ( long double x )
{
  return atanh ( ( double ) x );
}
#endif

#ifndef DONT_USE_ASM
#if _MSC_VER < 1800
/* Public domain, from mingwex library, adjusted to compile with msvc */
KDEWIN_EXPORT double log1p(double x)
{
    static const double limit = 0.29;
    static const double one = 1.0;

    __asm {
        fldln2
        fld x
        fxam
        fnstsw ax
        fld st
        sahf
        jc lbl3     /* in case x is NaN or ±Inf */
    }

lbl4:
    __asm {
        fabs
        fcomp limit
        fnstsw ax
        sahf
        jc lbl2
        fadd one
        fyl2x
        jmp ende
    }

lbl2:
    __asm {
        fyl2xp1
        jmp ende
    }

lbl3:
    __asm {
        jp lbl4     /* in case x is ±Inf */
        fstp st(1)
        fstp st(1)
    }

ende:
    return;
}

KDEWIN_EXPORT void log1pf(float x)
{
    static const float limit = 0.29;
    static const float one = 1.0;

    __asm {
        fldln2
        fld x
        fxam
        fnstsw ax
        fld st
        sahf
        jc lbl3     /* in case x is NaN or ±Inf */
    }

lbl4:
    __asm {
        fabs
        fcomp limit
        fnstsw ax
        sahf
        jc lbl2
        fadd one
        fyl2x
        jmp ende
    }

lbl2:
    __asm {
        fyl2xp1
        jmp ende
    }

lbl3:
    __asm {
        jp lbl4     /* in case x is ±Inf */
        fstp st(1)
        fstp st(1)
    }

ende:
    return;
}

KDEWIN_EXPORT long double log1pl(long double x)
{
    return log1p((double)x);
}
#endif
#endif

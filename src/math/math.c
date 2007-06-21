/*
  Some definitions from fp_consts(f|l).c from mingw
  public domain
*/

#include <winposix_export.h>

#define __FLOAT_INF_REP { 0, 0x7f80 }
#define __FLOAT_QNAN_REP { 0, 0xffc0 }  /* { 0, 0x7fc0 }  */
#define __FLOAT_SNAN_REP { 0, 0xff80 }  /* { 1, 0x7f80 }  */
#define __FLOAT_DENORM_REP {1,0}

#define __DOUBLE_INF_REP { 0, 0, 0, 0x7ff0 }
#define __DOUBLE_QNAN_REP { 0, 0, 0, 0xfff8 }  /* { 0, 0, 0, 0x7ff8 }  */
#define __DOUBLE_SNAN_REP { 0, 0, 0, 0xfff0 }  /* { 1, 0, 0, 0x7ff0 }  */
#define __DOUBLE_DENORM_REP {1, 0, 0, 0}

union _ieee_rep
{
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


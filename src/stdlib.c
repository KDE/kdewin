/* This file is part of the KDE project
   Copyright (C) 2006 Christian Ehrlicher <ch.ehrlicher@gmx.de>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include <winposix_export.h>
#include <windows.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(_MSC_VER) && _MSC_VER >= 1400
// use secure functions declared in msvc >= 2005
#define KDEWIN32_USE_ENV_S
#endif

// from kdecore/fakes.c
KDEWIN32_EXPORT int setenv(const char *name, const char *value, int overwrite)
{
#ifndef KDEWIN32_USE_ENV_S
    int i, iRet;
    char * a;
#endif
    char dummy[1];

    if (!overwrite && getenv(name)) return 0; 

#ifdef KDEWIN32_USE_ENV_S
    return _putenv_s(name, value);
#else 
    if (!name) return -1;

    i = strlen(name) + strlen(value) + 2;
    a = (char*)malloc(i);
    if (!a) return 1;

    strcpy(a, name);
    strcat(a, "=");
    strcat(a, value);

    iRet = putenv(a);
    free(a);
    return iRet;
#endif
}


// from kdecore/fakes.c
KDEWIN32_EXPORT void unsetenv (const char *name)
{
  if (name == NULL || *name == '\0' || strchr (name, '=') != NULL)
    {
      errno = EINVAL;
      return;
    }

  setenv(name, 0, 1);
}

KDEWIN32_EXPORT long int random()
{
	return rand();
}

KDEWIN32_EXPORT void srandom(unsigned int seed)
{
	srand(seed);
}


KDEWIN32_EXPORT double drand48(void)
{
	return 1.0*rand()/(RAND_MAX+1.0);
}

KDEWIN32_EXPORT int rand_r(unsigned *seed)
{
    srand(*seed);
    return rand();
}

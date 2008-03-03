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

// from kdecore/fakes.c
KDEWIN32_EXPORT int setenv(const char *name, const char *value, int overwrite)
{
    int i, iRet;
    char * a;

    if (!overwrite && getenv(name)) return 0;

    i = strlen(name) + strlen(value) + 2;
    a = (char*)malloc(i);
    if (!a) return 1;

    strcpy(a, name);
    strcat(a, "=");
    strcat(a, value);

    iRet = putenv(a);
    free(a);
    return iRet;
}


// from kdecore/fakes.c
KDEWIN32_EXPORT void unsetenv (const char *name)
{
  size_t len;
  char **ep;

  if (name == NULL || *name == '\0' || strchr (name, '=') != NULL)
    {
      errno = EINVAL;
      return;
    }

  len = strlen (name);

  ep = environ;
  while (*ep != NULL)
    if (!strncmp (*ep, name, len) && (*ep)[len] == '=')
      {
	/* Found it.  Remove this pointer by moving later ones back.  */
	char **dp = ep;

	do
	  dp[0] = dp[1];
	while (*dp++);
	/* Continue the loop in case NAME appears again.  */
      }
    else
      ++ep;

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

/*
   This file is part of the KDE libraries
   Copyright (C) 2003-2004 Jarosław Staniek <staniek@kde.org>

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

#ifndef KDEWIN_STDLIB_H
#define KDEWIN_STDLIB_H

// include everywhere
#include <sys/types.h>

/* regular header from msvc includes */
#ifndef _WIN32_WCE
#include <../include/stdlib.h>
#else
#include <../wcecompat/stdlib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define strtoll _strtoi64
#define strtoull _strtoui64


KDEWIN_EXPORT long int random();

KDEWIN_EXPORT void srandom(unsigned int seed);

KDEWIN_EXPORT double drand48(void);

KDEWIN_EXPORT int rand_r(unsigned *seed);

KDEWIN_EXPORT char* realpath(const char *path,char *resolved_path);

// from kdecore/fakes.c

KDEWIN_EXPORT int setenv(const char *name, const char *value, int overwrite);

KDEWIN_EXPORT int unsetenv(const char *name);


#ifdef __cplusplus
}
#endif

#endif // KDEWIN_STDLIB_H

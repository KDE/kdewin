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

/*
 * Definitions for common types, variables, and functions.
 */

#ifndef KDE_STDLIB_H
#define KDE_STDLIB_H

#include <sys/types.h>
#include <../include/stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif 
/*
#define __need_size_t
#define __need_wchar_t
#include <stddef.h>

#ifndef _STDLIB_H_
#endif
#define _STDLIB_H_

#ifndef NULL
#define NULL 0
#endif

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
*/

KDEWIN_EXPORT long int random();

KDEWIN_EXPORT void srandom(unsigned int seed);

KDEWIN_EXPORT double drand48(void);

KDEWIN_EXPORT int rand_r(unsigned *seed);

KDEWIN_EXPORT char* realpath(const char *path,char *resolved_path);

/* from kdecore/fakes.c */

KDEWIN_EXPORT int setenv(const char *__string, const char *__value, int __overwrite);

KDEWIN_EXPORT int unsetenv(const char *__string);


#ifdef __cplusplus
}
#endif

#endif /* KDE_STDLIB_H_ */

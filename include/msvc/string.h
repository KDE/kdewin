/*
   This file is part of the KDE libraries
   Copyright (C) 2003-2004 Jaroslaw Staniek <js@iidea.pl>

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

#ifndef KDEWIN_STRING_H
#define KDEWIN_STRING_H

// include everywhere
#include <sys/types.h>

/* regular header from msvc includes */
#include <../include/string.h>

#ifndef strncasecmp
#define strncasecmp strnicmp
#define HAVE_STRNCASECMP
#endif
#ifndef strcasecmp
#define strcasecmp stricmp
#define HAVE_STRCASECMP
#endif

#ifdef __cplusplus
extern "C" {
#endif

KDEWIN32_EXPORT char* strndup(const char *src, size_t n);
#define HAVE_STRNDUP

KDEWIN32_EXPORT unsigned long strlcpy(char *dst, const char *src, unsigned long siz);
#define HAVE_STRLCPY

KDEWIN32_EXPORT unsigned long strlcat(char *dst, const char *src, unsigned long siz);
#define HAVE_STRLCAT

KDEWIN32_EXPORT char *strcasestr(const char *big, const char *little);
#define HAVE_STRCASESTR

#ifdef __cplusplus
}
#endif

#endif /* KDEWIN_STRING_H */

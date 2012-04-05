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

#ifndef NO_KDEWIN
#ifndef KDEWIN_STRING_H
#define KDEWIN_STRING_H

// include everywhere
#include <sys/types.h>
#endif

/* regular header from msvc includes */
#ifndef _WIN32_WCE
#include <../include/string.h>
#else
#include <../wcecompat/string.h>
#endif

#ifndef NO_KDEWIN
#ifndef strncasecmp
#define strncasecmp strnicmp
#endif
#ifndef strcasecmp
#define strcasecmp stricmp
#endif

#ifdef __cplusplus
extern "C" {
#endif

KDEWIN_EXPORT char* strndup(const char *src, size_t n);

KDEWIN_EXPORT unsigned long strlcpy(char *dst, const char *src, unsigned long siz);

KDEWIN_EXPORT unsigned long strlcat(char *dst, const char *src, unsigned long siz);

KDEWIN_EXPORT char *strcasestr(const char *big, const char *little);

#ifdef __cplusplus
}
#endif

#endif /* KDEWIN_STRING_H */
#endif /* NO_KDEWIN */
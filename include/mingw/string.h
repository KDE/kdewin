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

#ifndef KDEWIN_STRING_H
#define KDEWIN_STRING_H

#define strncasecmp strnicmp
#define strcasecmp stricmp

#include <sys/types.h>
#include <../include/string.h>

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

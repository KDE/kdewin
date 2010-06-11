/*
   This file is part of the KDE libraries
   Copyright (C) 2006 Christian Ehrlicher <ch.ehrlicher@gmx.de>
   Copyright (C) 2008 Jarosław Staniek <staniek@kde.org>

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

#ifndef KDEWIN_STDIO_H
#define KDEWIN_STDIO_H

// include everywhere
#include <sys/types.h>

/* regular header from msvc includes */
#ifndef _WIN32_WCE
# include <../include/stdio.h>
#else
#include <../wcecompat/stdio.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/** Replaces _snprintf() because we want to behave like on UNIX: 
  * terminate with \0 if the buffer is too small, and return value that 
  * is greater than or equal to the size argument if the string was 
  * too short and some of the printed characters were discarded. */
KDEWIN_EXPORT int kdewin32_snprintf(char *buffer, size_t count, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#define snprintf kdewin32_snprintf
#define vsnprintf _vsnprintf
#define popen _popen
#define pclose _pclose

#endif	// KDEWIN_STDIO_H

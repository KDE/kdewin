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

#ifndef NO_KDEWIN
// include everywhere
#include <sys/types.h>

#endif /* NO_KDEWIN */

#ifndef _WIN32_WCE
#include <../include/time.h>
#else
#include <../wcecompat/time.h>
#endif

#ifndef NO_KDEWIN

#ifndef KDEWIN_TIME_H
#define KDEWIN_TIME_H

#ifdef __cplusplus
extern "C" {
#endif 

KDEWIN_EXPORT struct tm *localtime_r(const time_t *clock, struct tm *result);
KDEWIN_EXPORT struct tm *gmtime_r(const time_t *clock, struct tm *result);
KDEWIN_EXPORT char *strptime (const char *buf, const char *format, struct tm *tm);

#ifdef __cplusplus
}
#endif 

#endif  // KDEWIN_TIME_H
#endif /* NO_KDEWIN */
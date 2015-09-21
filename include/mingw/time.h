/* This file is part of the KDE project
   Copyright (C) 2005  Ralf Habacker <ralf.habacker@freenet.de>

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
#ifndef KDE_TIME_H
#define KDE_TIME_H

#include "kdewin_config.h"

#include <sys/types.h>
#if !defined(_POSIX_C_SOURCE) && defined(KDEWIN_NO_LOCALTIME_R) || defined(KDEWIN_NO_GMTIME_R)
#define _POSIX_C_SOURCE 200809L
#endif
#include <../include/time.h>

#ifdef __cplusplus
extern "C" {
#endif 

#if !defined(localtime_r) && !defined(KDEWIN_NO_LOCALTIME_R)
KDEWIN_EXPORT struct tm *localtime_r(const time_t *clock, struct tm *result);
#endif

#if !defined(gmtime_r) && !defined(KDEWIN_NO_GMTIME_R)
KDEWIN_EXPORT struct tm *gmtime_r(const time_t *clock, struct tm *result);
#endif

KDEWIN_EXPORT char *strptime (const char *buf, const char *format, struct tm *tm);

#ifdef __cplusplus
}
#endif 

#endif 

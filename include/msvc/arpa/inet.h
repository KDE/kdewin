/* This file is part of the KDE project
   Copyright (C) 2005-2006 Ralf Habacker <ralf.habacker@freenet.de>
   Copyright (C) 2006-2007 Christian Ehrlicher <ch.ehrlicher@gmx.de>

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

#ifndef KDEWIN_ARPA_INET_H
#define KDEWIN_ARPA_INET_H

// include everywhere
#include <sys/types.h>

#include <netinet/in.h>

// include to ensure we define inet_ntop/pton after PSDK declarations if present
#include <ws2tcpip.h> 

#ifdef __cplusplus
extern "C"
{
#endif

typedef unsigned int in_addr_t;

#define inet_ntop kde_inet_ntop
#define inet_pton kde_inet_pton

KDEWIN_EXPORT const char *kde_inet_ntop(int af, const void * src, char * dst, size_t size);
KDEWIN_EXPORT int kde_inet_pton(int af, const char * src, void * dst);
KDEWIN_EXPORT int inet_aton(const char *src, struct in_addr *addr);

// FIXME - move to sys/errno.h
#if _MSC_VER < 1600
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT 106
#endif
#endif

#ifdef __cplusplus
};
#endif

#endif // KDEWIN_ARPA_INET_H

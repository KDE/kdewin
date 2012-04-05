/* This file is part of the KDE project
   Copyright (C) 2006 Ralf Habacker <ralf.habacker@freenet.de>

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
#include <sys/types.h>
#endif

#ifndef _WIN32_WCE
#include <../include/errno.h>
#else
#include <../wcecompat/errno.h>
#endif

#ifndef NO_KDEWIN
#ifndef KDEWIN_ERRNO_H
#define KDEWIN_ERRNO_H

#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED
KDEWIN_EXPORT int __cdecl _set_errno(int value);
#else
#define _KDEWIN_DONT_IMPLEMENT_SET_ERRNO
#endif

#ifndef ENOFILE
#define ENOFILE ENOENT
#endif

#ifndef ENOTSUP
#define ENOTSUP ENOSYS
#endif

#endif
#endif /* NO_KDEWIN */
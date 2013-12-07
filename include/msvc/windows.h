/*
   This file is part of the KDE libraries
   Copyright (C) 2007 Jarosław Staniek <staniek@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

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
#ifndef KDEWIN_WINDOWS_H
#define KDEWIN_WINDOWS_H

#if defined(_MSC_VER) && _MSC_VER >= 1600
/* 1600 is Visual C++ 2010, untested with C++ 2008

   if users include windows.h and winsock2.h in the wrong
   order, things go wrong: windows.h includes winsock.h
   with the old API, and winsock2.h will define the new API
   even if the old API is already defined, resulting in tons
   of redefinition errors.
   Defining _WINSOCKAPI_ ensures that winsock.h does not do
   anything.
   Without this define, pykde would not compile
*/
# define _WINSOCKAPI_
#endif

/* avoid min/max conflicts (see http://support.microsoft.com/kb/143208) */
#ifndef NOMINMAX
# define NOMINMAX
#endif

#endif /* KDEWIN_WINDOWS_H */
#endif /* NO_KDEWIN */
/* regular header from msvc includes */
#if _MSC_VER >= 1700
#include <../um/windows.h>
#elif !define(_WIN32_WCE)
#include <../include/windows.h>
#else
#include <../Armv4i/windows.h>
#endif

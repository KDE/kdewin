/* This file is part of the KDE project
   Copyright (C) 2003-2004 Jaroslaw Staniek <staniek@kde.org>

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

#include <kdewin_export.h>
#include <pwd.h>

/* these functions always fail for win32 */
static struct passwd s_passwd = { "", "", -2, -2, "", "", "", "" };

KDEWIN_EXPORT struct passwd * getpwnam (const char *name)
{
    return &s_passwd;
}

KDEWIN_EXPORT struct passwd * getpwuid (uid_t uid)
{
    return &s_passwd;
}

KDEWIN_EXPORT void setpwent (void)
{
}

KDEWIN_EXPORT struct passwd *getpwent()
{
    return &s_passwd;
}

KDEWIN_EXPORT void endpwent()
{
}


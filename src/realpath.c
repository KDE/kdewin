/* This file is part of the KDE project
   Copyright (C) 2003-2004 Werner Almesberger <werner@almesberger.net>

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
#include <windows.h>

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <direct.h>

/** @return the canonicalized absolute pathname */
KDEWIN_EXPORT char *realpath(const char *path,char *resolved_path)
{
    int i;
    /* no error checking... :( */
    resolved_path[0] = '\0';
    GetFullPathNameA(path, PATH_MAX, resolved_path, NULL);
    /* TODO: really needed? Would be better because some functions */
    /*       assume '/' as separator */
    for( i = 0; resolved_path[i] != '\0'; ++i ) {
        if(resolved_path[i] == '\\')
            resolved_path[i] = '/';
    }
    return resolved_path;
}

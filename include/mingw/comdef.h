/* This file is part of the KDE project
   Copyright (C) 2007 Shane King <kde@dontletsstart.com>

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

#ifndef KDEWIN_COMDEF_H
#define KDEWIN_COMDEF_H

#include <windows.h>
#include <stdio.h>

/* for compat with MSVC  */
/* implementation incomplete, only enough to compile phonon ds9 */
class _com_error
{
public:
    _com_error(HRESULT hr)
        : m_hr(hr), m_string(0)
    {
    }

    _com_error(const _com_error &other)
        : m_hr(other.m_hr), m_string(0)
    {
    }

    ~_com_error()
    {
        if (m_string)
        {
            HANDLE h = GetProcessHeap();
            if (h)
                HeapFree(h, 0, m_string);
        }
    }

    _com_error &operator=(const _com_error &other)
    {
        m_hr = other.m_hr;
        m_string = 0;
        return *this;
    }

    wchar_t *ErrorMessage()
    {
        if (m_string == 0)
        {
            FormatMessageW(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM, 
                0, 
                m_hr,
                0,
                reinterpret_cast<WCHAR *>(&m_string),
                0,
                0);

            if (m_string == 0)
            {
                HANDLE h = GetProcessHeap();
                if (h)
                {
                    m_string = static_cast<WCHAR *>(HeapAlloc(h, 0, 64 * sizeof(wchar_t)));
                    if (m_string)
                        swprintf(m_string, L"Unknown error (0x%08X)", m_hr);
                }
            }
        }
        return m_string;
    }

private:
    HRESULT m_hr;
    WCHAR *m_string;
};

#endif

/* 
   This file is part of the KDE project
   Copyright (C) 2009 Ralf Habacker  <ralf.habacker@freenet.de>

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

   resource support for manifest tool 
*/

#include <string>
#include <iostream>
#include <windows.h>

inline void ErrorHandler(char *s)
{
    std::cerr << s << std::endl;
}

class Manifest {
    public: 
        Manifest()
        {
        }
    
        std::string readFromLibrary(std::string &file)
        {
            HRSRC hResLoad;     // handle to loaded resource 
            HMODULE hExe;        // handle to existing .EXE file 
            HRSRC hRes;         // handle/ptr. to res. info. in hExe 
            VOID *lpResLock;    // pointer to resource data 
            std::string a;

            // Load the .EXE file that contains the dialog box you want to copy. 
            hExe = LoadLibrary(file.c_str()); 
            if (hExe == NULL) 
            { 
                ErrorHandler("Could not load exe."); 
            } 
             
            // Locate the dialog box resource in the .EXE file. 
            hRes = FindResource(hExe, CREATEPROCESS_MANIFEST_RESOURCE_ID, RT_MANIFEST); 
            if (hRes == NULL) 
            { 
                ErrorHandler("Could not locate manifest box."); 
            } 
             
            // Load the dialog box into global memory. 
            hResLoad = (HRSRC) LoadResource(hExe, hRes); 
            if (hResLoad == NULL) 
            { 
                ErrorHandler("Could not load dialog box."); 
            } 
             
            // Lock the dialog box into global memory. 
            lpResLock = LockResource(hResLoad); 
            if (lpResLock == NULL) 
            { 
                ErrorHandler("Could not lock dialog box."); 
            } 
            
            char *p = (char *)lpResLock;
                     
            // ignore byte order mark if present according to http://en.wikipedia.org/wiki/Byte-order_mark 
            unsigned char *t = (unsigned char *)lpResLock;
            if (t[0] == 0xEF && t[1] == 0xBB && t[2] == 0xBF)
                a = std::string(p+3,SizeofResource(hExe, hRes)-3);
            else
                a = std::string(p,SizeofResource(hExe, hRes));

            // Clean up. 
            if (!FreeLibrary(hExe)) 
            { 
                ErrorHandler("Could not free executable."); 
            } 
            
            return a;
        }

    private:
        
};

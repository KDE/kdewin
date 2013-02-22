/* 
   This file is part of the KDE project

   Copyright (C) 2009-2013 Ralf Habacker  <ralf.habacker@freenet.de>
   All Rights Reserved.

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

   Alternativly this file may be used under the terms of the BSD license. 
   Redistribution and use in source and binary forms, with or without modification, 
   are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, 
       this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.

    3. The name of the author may not be used to endorse or promote products derived 
       from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY [LICENSOR] "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY 
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
   POSSIBILITY OF SUCH DAMAGE. 
  
   resource file support for manifest tool 
*/
#ifndef RESOURCEFILE_H
#define RESOURCEFILE_H

#include <string>
#include <iostream>
#include <windows.h>

/** 
 Important: this implementation does not work in cross plattform environments 
 because of the win32 api usage. 
 A cross plattform save implementation may be possible by using the coff
 binary read/write support from the binutils package.
*/

class ResourceFile {
    public:     
        ResourceFile(const std::string &fileName)
          : m_fileName(fileName)
        {}

        bool hasManifest()
        {
            HMODULE hExe;        // handle to existing .EXE file 
            HRSRC hRes;         // handle/ptr. to res. info. in hExe 
            
            // Load the file that contains the resource 
            hExe = LoadLibrary(m_fileName.c_str()); 
            if (hExe == NULL) 
            { 
                setError("Could not load file",m_fileName);
                return false;
            } 
             
            // Locate the resource in the file. 
            hRes = FindResource(hExe, CREATEPROCESS_MANIFEST_RESOURCE_ID, RT_MANIFEST); 

            // Clean up. 
            if (!FreeLibrary(hExe)) 
            { 
                setError("Could not free executable");
                return false;
            } 
            return hRes != 0;
        }

        std::string getManifest()
        {
            HRSRC hResLoad;     // handle to loaded resource 
            HMODULE hExe;        // handle to existing .EXE file 
            HRSRC hRes;         // handle/ptr. to res. info. in hExe 
            VOID *lpResLock;    // pointer to resource data 
            std::string a;

            // Load the .EXE file that contains the dialog box you want to copy. 
            hExe = LoadLibrary(m_fileName.c_str()); 
            if (hExe == NULL) 
            { 
                setError("Could not load file",m_fileName);
                return a;
            } 
             
            // Locate the resource in the file. 
            hRes = FindResource(hExe, CREATEPROCESS_MANIFEST_RESOURCE_ID, RT_MANIFEST); 
            if (hRes == NULL) 
            { 
                setError("Could not locate resource");
                return a;
            } 
             
            // Load the resource into global memory. 
            hResLoad = (HRSRC) LoadResource(hExe, hRes); 
            if (hResLoad == NULL) 
            { 
                setError("Could not load resource");
                return a;
            } 
             
            // Lock the dialog box into global memory. 
            lpResLock = LockResource(hResLoad); 
            if (lpResLock == NULL) 
            { 
                setError("Could not lock resource");
                return a;
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
                setError("Could not free executable");
                return a;
            } 
            
            return a;
        }

        bool setManifest(const std::string &data)
        {
            std::string a;

            // Open the file to which you want to add the resource. 
            HANDLE hUpdateRes = BeginUpdateResource(m_fileName.c_str(), FALSE); 
            if (hUpdateRes == NULL) 
            { 
                setError("Could not open file for writing.",m_fileName);
                return false;
            } 
         
            // Add the resource to the update list. 
            int result = UpdateResource(hUpdateRes,       // update resource handle 
                 RT_MANIFEST,                       
                 CREATEPROCESS_MANIFEST_RESOURCE_ID,         // dialog box name 
                 MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),  // neutral language
                 (LPVOID)data.c_str(),                   
                 data.size()
            );

            if (result == FALSE) 
            { 
                setError("Could not add resource"); 
                return false;
            } 
             
            // Write changes to the file and then close it. 
            if (!EndUpdateResource(hUpdateRes, FALSE)) 
            { 
                setError("Could not write changes to",m_fileName); 
                return false;
            } 
            return true;
        }
        
    protected:
        void setError(const std::string &text, const std::string opt=std::string())
        {
            std::cerr << text << opt << std::endl;
        }
        
        std::string m_fileName;
};

#endif

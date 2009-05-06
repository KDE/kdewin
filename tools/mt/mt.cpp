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

   main part of manifest tool 
*/

#include "manifest.h"
#include "xml.h"

#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char **argv)
{
    bool hasInputResource = false;
    std::string inputResource;

    bool hasOutputResource = false;
    std::string outputResource;
    
    bool hasUpdateResource = false;
    std::string updateResource;

    bool hasOut = false;
    std::string out;

    for(int i = 1; i < argc; i++)
    {
        string arg = argv[i];

        int pos = arg.find(':'); 
        string fileName = pos != string::npos ? arg.substr(pos+1) : "";
        string option = pos != string::npos ? arg.substr(0,pos) : "";
        bool hasFileName = fileName.size() > 0;

        if (option == "-out" && fileName.size())
        {
            out = fileName;
            hasOut = true;
        }

        //[ -inputresource:<file>[;[#]<resource_id>] ]
        else if (option == "-inputresource" && hasFileName)
        {
            inputResource = fileName;
            hasInputResource = true;
        }

        //[ -outputresource:<file>[;[#]<resource_id>] ]
        else if (option == "-outputresource" && hasFileName)
        {
            outputResource = fileName;
            hasOutputResource = true;
        }
        
        //[ -updateresource:<file>[;[#]<resource_id>] ]
        else if (option == "-updateresource" && hasFileName)
        {
            updateResource = fileName;
            hasUpdateResource = true;
        }
    }

    if (hasInputResource && hasOut)
    {
        Manifest manifest;
        ofstream of(out.c_str());
        of << manifest.readFromLibrary(inputResource);
    }
    else if (hasInputResource)
    {
        Manifest manifest;
        std::cout << manifest.readFromLibrary(inputResource);
    }

    return 0;
}


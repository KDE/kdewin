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

#include "resourcefile.h"
#include "xml.h"

#include <iostream>
#include <fstream>

using namespace std;

void printhelp()
{
    cerr << "MinGW Manifest Tool version 1.0.0" << endl;
    cerr << "copyright (c) Ralf Habacker ralf.habacker@freenet.de" << endl;
    cerr << endl;
    cerr << "Usage:" << endl;
    cerr << "------" << endl;
    cerr << "mt.exe [ -manifest <manifest name> ]" << endl;
    cerr << "[ -out:<output manifest name> ]" << endl;
    cerr << "[ -inputresource:<file> ] " << endl;
    cerr << "[ -updateresource:<file> ]" << endl;
    cerr << "[ -outputresource:<file> ]" << endl;    
#ifdef RESOURCE_ID_SUPPORT
    cerr << "[ -inputresource:<file>[;[#]<resource_id>] ]" << endl;
    cerr << "[ -updateresource:<file>[;[#]<resource_id>] ]" << endl;
    cerr << "[ -outputresource:<file>[;[#]<resource_id>] ]" << endl;    
#endif    
    cerr << endl;
    cerr << "Examples:" << endl;
    cerr << "---------" << endl;
    cerr << "- display manifest from <executable>" << endl;
    cerr << "    mt -inputresource:<executable>" << endl << endl;
    cerr << "- copy manifest file from <manifest file> into <executable>" << endl;
    cerr << "    mt -manifest <manifest file> -outputresource:<executable>" << endl << endl;
    cerr << "- merge <manifest file> into <executable>" << endl;
    cerr << "    mt -manifest <manifest file> -updateresource:<executable> " << endl;
    cerr << "- merge and display manifest file from <manifest file> and manifest from <executable>" << endl;
    cerr << "    mt -manifest <manifest file> -inputresource:<executable> " << endl << endl;
    cerr << "- copy manifest from <executable> into file <manifest file>" << endl;
    cerr << "    mt -inputresource:<executable> -out:<manifest file>" << endl;
}

int main(int argc, char **argv)
{
    bool nologo;
    
    bool hasInputResource = false;
    string inputResource;

    bool hasOutputResource = false;
    string outputResource;

    bool hasInputFile = false;
    string inputFile;
    
    bool hasOutputFile = false;
    string outputFile;

    if (argc == 1) 
    {
        printhelp();
        return -1;
    }
    
    for(int i = 1; i < argc; i++)
    {
        string arg = argv[i];

        int pos = arg.find(';'); 

        string id;
        if (pos != string::npos)
        {
            id = (arg[pos+1] == '#') ? arg.substr(pos+2) : arg.substr(pos+1);
            arg = arg.substr(0,pos);
        }
        pos = arg.find(':'); 
        string fileName = pos != string::npos ? arg.substr(pos+1) : "";
        string option = pos != string::npos ? arg.substr(0,pos) : arg;
        bool hasFileName = fileName.size() > 0;
        
        if (option == "-nologo") {
            nologo = true;
        }
        //[ -manifest]
        else if (option == "-manifest")
        {
            hasInputFile = true;
            // check if filename is present
            inputFile = argv[++i];
        }
        
        else if (option == "-out" && fileName.size())
        {
            outputFile = fileName;
            hasOutputFile = true;
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
            inputResource = fileName;
            hasInputResource = true;
            outputResource = fileName;
            hasOutputResource = true;
        }
    }

    string inputResourceManifest;
    string inputManifest;
    string outputManifest;
    
    //--- process input ---
    if (hasInputResource)
    {
        ResourceFile ir(inputResource);
        if (!ir.hasManifest())
        {
            cerr << "manifest not found" << endl;
        }
        else
            inputResourceManifest = ir.getManifest();
    }

    if (hasInputFile)
    {
        ifstream is(inputFile.c_str(),ifstream::in);
        if (!is.is_open())
        {
            cerr << "could not open " << inputFile;
            return -1;
        }

        while(is.good())
        {
            char s[1024];
            is.getline(s,1023);
            if (inputManifest.size() > 0)
                inputManifest += "\n";
            inputManifest += s;
        }
    }

    //--- merge xml files ---
    if (hasInputResource && hasInputFile)
    {
        XML xml;
        xml.parse(inputResourceManifest);
        xml.parse(inputManifest);
        // set parameter 
        outputManifest = xml.get();
    }
    else if (hasInputResource)
        outputManifest = inputResourceManifest;
    else if (hasInputFile)
        outputManifest = inputManifest;

    //--- process output ---
    if (hasOutputResource)
    {
        ResourceFile orf(outputResource);
        return orf.setManifest(outputManifest) ? 0 : -1;
    }
    else if (hasOutputFile)
    {
        ofstream of(outputFile.c_str());
        of << outputManifest;
        return 0;
    }
    else
    {
        cout << outputManifest;
        return 0;
    }

    return 0;
}

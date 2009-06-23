/* 
   This file is part of the KDE project
   Copyright (C) 2009 Christian Ehrlicher <ch.ehrlicher@gmx.de>

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

#include <io.h>
#include <stdio.h>

#include "resourcefile.h"

const char *assemblyStart  = "<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">\n";
const char *assemblyEnd    = "</assembly>\n";
const char *trustinfoStart = "  <trustInfo xmlns=\"urn:schemas-microsoft-com:asm.v3\">\n";
const char *trustinfoEnd   = "  </trustInfo>\n";
const char *securityStart  = "    <security>\n";
const char *securityEnd    = "    </security>\n";
const char *reqPrivStart   = "      <requestedPrivileges>\n";
const char *reqPrivEnd     = "      </requestedPrivileges>\n";
const char *reqExecStart   = "        <requestedExecutionLevel level=\"asInvoker\" uiAccess=\"false\" />\n";
const char *reqExecEnd     = "";

const char *levels[] =
{
  "asInvoker",
  "highestAvailable",
  "requireAdministrator"
};

int main(int argc, char **argv)
{
    if( argc != 3 ) {
      fprintf(stderr, "Usage: %s <library_or_executable> /level:[asInvoker|highestAvailable|requireAdministrator]\n", argv[0]);
      return 1;
    }

    const char *inputfile = argv[1];
    if(_access(inputfile, 6) != 0) {
      fprintf(stderr, "Can't access %s for writing!\n", inputfile);
      return 2;
    }
    
    const char *level = argv[2];
    const char *pos = strchr(level, ':');
    if(pos)
      level = pos+1;
    
    int iLevel = -1;
    if(strcmp(level, "asInvoker") == 0)
      iLevel = 0;
    if(strcmp(level, "highestAvailable") == 0)
      iLevel = 1;
    if(strcmp(level, "requireAdministrator") == 0)
      iLevel = 2;

    if(iLevel == -1) {
      fprintf(stderr, "Unknown level %s\n", level);
      return 3;
    }

    // ok - we're no xml parser and won't be one ... :)
    ResourceFile rf(inputfile);
    std::string manifest = rf.getManifest();
    if(manifest.size() == 0) {
      manifest  = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
      manifest += assemblyStart;
      manifest += trustinfoStart;
      manifest += securityStart;
      manifest += reqPrivStart;
      manifest += reqExecStart;
      manifest += reqExecEnd;
      manifest += reqPrivEnd;
      manifest += securityEnd;
      manifest += trustinfoEnd;
      manifest += assemblyEnd;
    }

    std::string::size_type spos;
    spos = manifest.find("assembly");
    if(spos == std::string::npos) {
      // simply add to the end
      manifest += "\n";
      manifest += assemblyStart;
      manifest += trustinfoStart;
      manifest += securityStart;
      manifest += reqPrivStart;
      manifest += reqExecStart;
      manifest += reqExecEnd;
      manifest += reqPrivEnd;
      manifest += securityEnd;
      manifest += trustinfoEnd;
      manifest += assemblyEnd;
    }

    spos = manifest.find("trustInfo");
    if(spos == std::string::npos) {
      // simply add to the end
      // add it before </assembly>
      std::string::size_type posBefore = manifest.find("</assembly>");
      if( posBefore == std::string::npos ) {
        fprintf(stderr, "Can't parse the manifest xml - need to fix xml parsing (assembly)!\n");
        return 3;
      }

      std::string insert;
      insert += trustinfoStart;
      insert += securityStart;
      insert += reqPrivStart;
      insert += reqExecStart;
      insert += reqExecEnd;
      insert += reqPrivEnd;
      insert += securityEnd;
      insert += trustinfoEnd;

      manifest.insert(posBefore, insert);
    }

    spos = manifest.find("security");
    if(spos == std::string::npos) {
      // add it before </trustInfo>
      std::string::size_type posBefore = manifest.find("</trustInfo>");
      if( posBefore == std::string::npos ) {
        fprintf(stderr, "Can't parse the manifest xml - need to fix xml parsing (trustInfo)!\n");
        return 3;
      }

      std::string insert;
      insert += securityStart;
      insert += reqPrivStart;
      insert += reqExecStart;
      insert += reqExecEnd;
      insert += reqPrivEnd;
      insert += securityEnd;

      manifest.insert(posBefore, insert);
    }

    spos = manifest.find("requestedPrivileges");
    if(spos == std::string::npos) {
      // add it before </security>
      std::string::size_type posBefore = manifest.find("</security>");
      if( posBefore == std::string::npos ) {
        fprintf(stderr, "Can't parse the manifest xml - need to fix xml parsing (security)!\n");
        return 3;
      }

      std::string insert;
      insert += reqPrivStart;
      insert += reqExecStart;
      insert += reqExecEnd;
      insert += reqPrivEnd;

      manifest.insert(posBefore, insert);
    }

    spos = manifest.find("requestedExecutionLevel");
    if(spos == std::string::npos) {
      // add it before </requestedPrivileges>
      std::string::size_type posBefore = manifest.find("</requestedPrivileges>");
      if( posBefore == std::string::npos ) {
        fprintf(stderr, "Can't parse the manifest xml - need to fix xml parsing (requestedExecutionLevel)!\n");
        return 3;
      }

      std::string insert;
      insert += reqExecStart;
      insert += reqExecEnd;

      manifest.insert(posBefore, insert);
    }

    // we now simply assume all is correct. if not we're out of luck and
    // we've to become a real xml parser somehow :)
    spos = manifest.find("level=\"");
    if(spos == std::string::npos) {
        fprintf(stderr, "Can't parse the manifest xml - need to fix xml parsing (level)!\n");
        return 3;
    }
    spos += strlen("level=\"");
    std::string::size_type epos = manifest.find("\"", spos + 1);
    if(epos == std::string::npos) {
        fprintf(stderr, "Can't parse the manifest xml - need to fix xml parsing!\n");
        return 3;
    }
    manifest = manifest.replace(spos, epos - spos, levels[iLevel]);
    //rf.setManifest(manifest);
fprintf(stderr, "manifest: %s\n", manifest.c_str());
    return 0;
}

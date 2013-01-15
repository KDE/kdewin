/* This file is part of the KDE project

   Copyright (C) 2006-2009 Ralf Habacker <ralf.habacker@freenet.de>
   All rights reserved.

   This library is free software; you can redistribute it and/or
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

#include "linkfile.h"

#include <QDir>
#include <QFile>

#include <qDebug>
#define kDebug qDebug

#ifndef _WIN32_WCE
#define UNICODE  0
#endif
#include <windows.h>
#ifdef __MINGW64__
#include <shlguid.h>
#include <shobjidl.h>
#else
#include <windowsx.h>
#include <objbase.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <initguid.h>
#endif
/*
    add correct prefix for win32 filesystem functions
    described in msdn, but taken from Qt's qfsfileeninge_win.cpp
*/
static QString longFileName(const QString &path)
{
    QString absPath = QDir::toNativeSeparators(path);
    QString prefix = QLatin1String("\\\\?\\");
    if (path.startsWith(QLatin1String("//")) ||
        path.startsWith(QLatin1String("\\\\"))) {
        prefix = QLatin1String("\\\\?\\UNC\\");
        absPath.remove(0, 2);
    }
    return prefix + absPath;
}

namespace KDE {
namespace Windows {

LinkFile::LinkFile(const QString &_execPath, const QString &_linkPath, const QString &_description, const QString &_workingDir)
{
    m_execPath     = _execPath;    
    m_arguments    = QStringList();
    m_linkPath     = _linkPath;
    m_description  = _description; 
    m_workingDir   = _workingDir;  
}
/** 
    constructs  LinkFile instance with arguments
  */
LinkFile::LinkFile(const QStringList &args, const QString &linkPath, const QString &description, const QString &workingDir)
{
    if (args.size() > 0)
        m_execPath = args[0];
    if (args.size() > 1) {
        m_arguments = args;
        m_arguments.removeFirst();
    }
    m_linkPath     = linkPath;
    m_description  = description; 
    m_workingDir   = workingDir;  
}
    
const QString &LinkFile::execPath() const      
{ 
    return m_execPath; 
}    

const QString &LinkFile::linkPath() const      
{ 
    return m_linkPath; 
}

const QString &LinkFile::description() const   
{ 
    return m_description; 
}

const QString &LinkFile::workingDir() const    
{ 
    return m_workingDir; 
}  

const QStringList &LinkFile::arguments() const 
{ 
    return m_arguments; 
}  

void LinkFile::setExecPath(const QString &a)    
{ 
    m_execPath = a; 
}    

void LinkFile::setLinkPath(const QString &a)    
{ 
    m_linkPath = a; 
}

void LinkFile::setDescription(const QString &a) 
{ 
    m_description = a; 
}

void LinkFile::setWorkingDir(const QString &a)  
{ 
    m_workingDir = a; 
}  

void LinkFile::setArguments(const QStringList &a)   
{ 
    m_arguments = a; 
}  

bool LinkFile::read()
{
#ifndef _WIN32_WCE
    LPCWSTR szShortcutFile = (LPCWSTR)m_linkPath.utf16();
    WCHAR szTarget[MAX_PATH];
    WCHAR szWorkingDir[MAX_PATH];
    WCHAR szDescription[MAX_PATH];
    WCHAR szArguments[MAX_PATH];

    IShellLink*    psl     = NULL;
    IPersistFile*  ppf     = NULL;
    bool           bResult = false;

    LPCWSTR wsz = szShortcutFile;

    if (FAILED( CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **) &psl) ))
        goto cleanup;

    if (FAILED( psl->QueryInterface(IID_IPersistFile, (void **) &ppf) ))
        goto cleanup;

    if (FAILED( ppf->Load(wsz, STGM_READ) ))
        goto cleanup;

    if (NOERROR != psl->GetPath(szTarget, MAX_PATH, NULL, 0) )
        goto cleanup;
    m_execPath = QString::fromUtf16((const ushort*)szTarget);

    if (NOERROR != psl->GetWorkingDirectory(szWorkingDir, MAX_PATH) )
        goto cleanup;
    m_workingDir = QString::fromUtf16((const ushort*)szWorkingDir);

    if (NOERROR != psl->GetDescription(szDescription, MAX_PATH) )
        goto cleanup;
    m_description = QString::fromUtf16((const ushort*)szDescription);

    if (NOERROR != psl->GetArguments(szArguments, MAX_PATH) )
        goto cleanup;
    m_arguments = QString::fromUtf16((const ushort*)szArguments).split(QLatin1Char(' '), QString::SkipEmptyParts);

    bResult = true;

cleanup:
    if (ppf) ppf->Release();
    if (psl) psl->Release();
    return bResult;
    
#else
    return false;
#endif
}

bool LinkFile::create()
{
#ifndef _WIN32_WCE
    HRESULT hres;
    IShellLinkW* psl;

    QString linkName = longFileName(m_linkPath);

    LPCWSTR lpszPathObj  = (LPCWSTR)m_execPath.utf16();
    LPCWSTR lpszPathLink = (LPCWSTR)m_linkPath.utf16();
    LPCWSTR lpszDesc     = (LPCWSTR)m_description.utf16();
    LPCWSTR lpszWorkDir  = (LPCWSTR)m_workingDir.utf16();
    // casting join directly results into a wrong lpszArguments 
    QString args = m_arguments.join(QLatin1String(" "));
    LPCWSTR lpszArguments  = (LPCWSTR)args.utf16();

    CoInitialize(NULL);
    // Get a pointer to the IShellLink interface.
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_ALL, IID_IShellLinkW, (LPVOID*)&psl);

    if (SUCCEEDED(hres))
    {
        IPersistFile* ppf;

        // Set the path to the shortcut target and add the description.
        if(!SUCCEEDED(psl->SetPath(lpszPathObj))) {
            kDebug() << "error setting path for link to " << m_execPath;
            psl->Release();
            return false;
        }
        if(!SUCCEEDED(psl->SetDescription(lpszDesc))) {
            kDebug() << "error setting description for link to " << m_description;
            psl->Release();
            return false;
        }
        if(!SUCCEEDED(psl->SetWorkingDirectory(lpszWorkDir))) {
            kDebug() << "error setting working Directory for link to " << m_workingDir;
            psl->Release();
            return false;
        }
        if(!m_arguments.isEmpty() && !SUCCEEDED(psl->SetArguments(lpszArguments))) {
            kDebug() << "error setting arguments for link to " << m_arguments;
            psl->Release();
            return false;
        }

        // Query IShellLink for the IPersistFile interface for saving the
        // shortcut in persistent storage.
        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

        if (SUCCEEDED(hres))
        {
            hres = ppf->Save(lpszPathLink, TRUE);
            // Save the link by calling IPersistFile::Save.
            if(!SUCCEEDED(hres))
                kDebug() << "error saving link to " << linkName;

            ppf->Release();
        }
        psl->Release();
    } else {
        kDebug() << "Error: Got no pointer to the IShellLink interface.";
    }
    CoUninitialize(); // cleanup COM after you're done using its services
    return SUCCEEDED(hres) ? true : false;
#else
    return false;
#endif
}

bool LinkFile::remove()
{
    bool ret = QFile::remove(m_linkPath);
    QFileInfo fi(m_linkPath);
    QDir d;
    d.rmpath(fi.absolutePath());
    return ret;
}

bool LinkFile::exists() const
{
    return QFile::exists(m_linkPath);
}

bool LinkFiles::scan(QList <LinkFile> &files, const QString &path)
{
    QDir aDir(path);
    bool has_err = false;
    if (aDir.exists())//QDir::NoDotAndDotDot
    {
        const QFileInfoList entries = aDir.entryInfoList(QDir::NoDotAndDotDot | 
                                                         QDir::Dirs |
                                                         QDir::Files);
        foreach(const QFileInfo &entryInfo, entries)
        {
            QString _path = entryInfo.absoluteFilePath();
            if (entryInfo.isDir())
            {
                has_err = scan(files,_path);
            }
            else
            {
                if (_path.toLower().endsWith(QLatin1String(".lnk")))
                    files.append(LinkFile(QString(),_path,QString(),QString()));
            }
        }
    }
    return has_err;
}

bool LinkFiles::create(QList <LinkFile> &newFiles)
{
    // create new link files 
    foreach(LinkFile linkFile, newFiles)
    {
        if (!linkFile.exists())
        {
            if (linkFile.create())
                kDebug() << "created" << linkFile;
            else
                kDebug() << "failed to create" << linkFile;
        }
    }
    return true;
}

bool LinkFiles::cleanup(QList <LinkFile> &newFiles, QList <LinkFile> &oldFiles)
{
    // delete not available linkfiles 
    foreach(LinkFile oldFile, oldFiles)
    {
        QString oldPath = QDir::fromNativeSeparators ( oldFile.linkPath().toLower() );
        bool found = false;
        foreach(const LinkFile &newFile, newFiles)
        {
            QString newPath = QDir::fromNativeSeparators ( newFile.linkPath().toLower());
            if (newPath == oldPath) 
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            kDebug() << "deleted" << oldFile << oldFile.remove();
        }
    }
    return true;
} 

::QDebug operator<<(::QDebug out, const KDE::Windows::LinkFile &c)
{
    out.space() << "LinkFile ("
        << "linkPath" << c.m_linkPath
        << "execPath"     << c.m_execPath
        << "arguments"   << c.m_arguments
        << "workingDir"   << c.m_workingDir
        << "description"  << c.m_description
        << ")";
    return out;
}

}

}


 // vim: ts=4 sw=4 et

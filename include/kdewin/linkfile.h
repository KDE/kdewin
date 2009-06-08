/* This file is part of the KDE Project

   Copyright (C) 2006-2009 Ralf Habacker <ralf.habacker@freenet.de>
   All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef KDE_WINDOWS_LINKFILE_H
#define KDE_WINDOWS_LINKFILE_H

#include <kdewin_export.h>

#include <QList>
#include <QString>
#include <QStringList>

namespace KDE {
namespace Windows {

class KDEWIN_EXPORT LinkFile {
    public:
        /// create instance 
        LinkFile(const QString &execPath, const QString &linkPath, const QString &description, const QString &workingDir);

        /// construct instance with arguments
        LinkFile(const QStringList &args, const QString &linkPath, const QString &description, const QString &workingDir);
        
        /// check if link file exists
        bool exists() const;
        /// create link file from instance data 
        bool create();
        /// remove link file
        bool remove();
        /// read link file content into instance 
        bool read();

        const QString &execPath() const;
        const QString &linkPath() const;
        const QString &description() const;
        const QString &workingDir() const;
        const QStringList &arguments() const;

        void setExecPath(const QString &path);
        void setLinkPath(const QString &path);
        void setDescription(const QString &description);
        void setWorkingDir(const QString &dir);
        void setArguments(const QStringList &args);

        friend ::QDebug operator<<(::QDebug out, const LinkFile &c);

    protected:
        QString m_execPath;    
        QString m_linkPath;
        QString m_description; 
        QString m_workingDir;  
        QStringList m_arguments;    
};

class KDEWIN_EXPORT LinkFiles {
    public:
        static bool scan(QList <LinkFile> &files, const QString &rootDir);
        static bool create(QList <LinkFile> &newFiles);
        static bool cleanup(QList <LinkFile> &newFiles, QList <LinkFile> &oldFiles);
};

}
}
#endif
// vim: ts=4 sw=4 et

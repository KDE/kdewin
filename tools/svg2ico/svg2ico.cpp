/* This file is part of the KDE project
   Copyright (C) 2007 Ralf Habacker  <ralf.habacker@freenet.de>

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

   svg to ico format converter 
*/

#include <QtDebug>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QProcess>
#include <QtCore/QFile>

#include <zlib.h>
#include <iostream>

using std::cout;
using std::endl;

bool verbose = false;

// vista support - requires a patched png2ico to support compressed png in ico container 
// see http://www.axialis.com/tutorials/tutorial-vistaicons.html for details 
// #define VISTA_ICON_SUPPORT


//  QSvgRenderer does not support svgz yet, feature request is submitted to qt-bugs@trolltech.com 
//  as workaround we use ksvgtopng from kdeui/utils

#include <QSvgRenderer>
#include <QtGui/QImage>
#include <QtGui/QPainter>

bool svg2png_internal(const QString &svgFile, const QString &pngFile, int width, int height)
{
    QImage img(width, height, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    QSvgRenderer *renderer;

    if (svgFile.endsWith(".svgz")) {
#if 1
        qDebug() << "converting compressed svg isn't implemented yet";
        return false;
#else
        QByteArray data;
        // does not work 
        gzFile fp = gzopen(svgFile.toAscii().data(),"r");
        while (!gzeof(fp)) {
            QByteArray buf(1024,0);
            int size = gzread(fp, buf.data(), 1024);
            if (size) 
                data.append(buf);
        }                
        gzclose(fp);
        renderer = new QSvgRenderer(data);
#endif
    }
    else 
        renderer = new QSvgRenderer(svgFile);

    if(!renderer->isValid()) {
        delete renderer;
        return false;
    }
    QPainter p(&img);
    renderer->render(&p);
    img.save(pngFile, "PNG");
    delete renderer;
    return true;
}

bool svg2png_ksvgtopng(const QString &svgFile, const QString &pngFile, int width, int height)
{
    QStringList params;
    params << QString::number(width) << QString::number(height) << svgFile << pngFile;
    int ret = QProcess::execute("ksvgtopng",params);
    if (verbose)
        qDebug() << "ksvgtopng" << params << "result=" << ret;

    if (verbose && ret)
        qDebug() << "error executing ksvgtopng"; 
    return ret ? false : true;
}

bool svg2png(const QString &svgFile, const QString &pngFile, int width, int height)
{
    // if ksvgtopng is available 
    //   return svg2png_ksvgtopng(svgFile, pngFile, width, height);
    // else
    return svg2png_internal(svgFile, pngFile, width, height);
}

bool png2ico(const QString &icoFile, const QStringList &pngFiles)
{
    QStringList params;
    params << icoFile;

#ifdef PNG2ICO_SUPPORTS_MULTIPLE_COLOR_DEPTH
    foreach(QString file, pngFiles)
        params << "--colors" << "16" << file;
    foreach(QString file, pngFiles)
        params << "--colors" << "256" << file;
    foreach(QString file, pngFiles)
        params << "--colors" << "xxx" << file;
#else
    params << pngFiles;
#endif

    int ret = QProcess::execute("png2ico",params);

    if (verbose)
        qDebug() << "png2ico" << params << "result=" << ret;
    return ret ? false : true;
}
    

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        cout << "Usage : svg2ico <options> <svgfilename> <icofilename>" << endl;
        cout << "options: --verbose       print execution details" << endl;
        return -1;
    }
    int i = 1;
    if (QString(argv[i]) == "--verbose") 
    {
        verbose = true;
        i++;
    }
    QString svgFile = QString::fromLocal8Bit(argv[i++]);
    QString icoFile = QString::fromLocal8Bit(argv[i++]);
    QString pngFile = icoFile; 
    pngFile.replace(".ico","-%1.png");

    if (verbose)
        qDebug() << svgFile << icoFile << pngFile;
    
    if ( !svg2png(svgFile, pngFile.arg("16"),16,16) )
        return 1;
    if ( !svg2png(svgFile, pngFile.arg("32"),32,32) )
        return 1;
    if ( !svg2png(svgFile, pngFile.arg("48"),48,48) )
        return 1;

#ifdef VISTA_ICON_SUPPORT
    if ( !svg2png(svgFile, pngFile.arg("128"),128,128) )
        return 1;
#endif

    QStringList pngFiles; 
    pngFiles << pngFile.arg("16") << pngFile.arg("32") << pngFile.arg("48");
#ifdef VISTA_ICON_SUPPORT
    pngFiles << pngFile.arg("128");
#endif

    int ret = png2ico(icoFile, pngFiles);

    QFile::remove(pngFile.arg("16"));
    QFile::remove(pngFile.arg("32"));
    QFile::remove(pngFile.arg("48"));
#ifdef VISTA_ICON_SUPPORT
    QFile::remove(pngFile.arg("128"));
#endif
    return ret;
}

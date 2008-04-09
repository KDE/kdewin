/* 
   This file is part of the KDE project
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
#include <QtCore/QFileInfo>

#include <zlib.h>

bool verbose = false;
bool debug = false;

// vista support - requires a patched png2ico to support compressed png in ico container 
// see http://www.axialis.com/tutorials/tutorial-vistaicons.html for details 
// #define VISTA_ICON_SUPPORT

#include <QSvgRenderer>
#include <QtGui/QImage>
#include <QtGui/QPainter>


bool unzipGZipFile(char *infile, char *outfile)
{
    gzFile file = gzopen(infile, "rb");
    FILE *out = fopen(outfile,"w");
    if (file == NULL) {
        return false;
    }
    char buf[1024]; 
    while (!gzeof(file)) {
        int len = gzread(file, buf, 1024);
        fwrite(buf,len,1,out);
    }
    gzclose(file);
    fclose(out);
    return true;
}

bool svg2png(const QString &inFile, const QString &outFile, int width, int height)
{
    QImage img(width, height, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);

    QString svgFile = inFile;
    QString tmpFile;
    if (svgFile.endsWith(".svgz")) {
        QFileInfo iif(inFile);
        QFileInfo of(outFile);
        tmpFile = of.absolutePath()+'/'+iif.baseName()+".svg";
        bool ret = unzipGZipFile(svgFile.toAscii().data(),tmpFile.toAscii().data());
        if (verbose || !ret)
            qDebug() << "uncompressing" << svgFile << "to" << tmpFile << ":" << (ret ? "okay" : "error");

        if (!ret) {
            return false;
        }
        svgFile = tmpFile;
    }


    QSvgRenderer renderer(svgFile);

    if(renderer.isValid()) {
        QPainter p(&img);
        renderer.render(&p);
        img.save(outFile, "PNG");

        if (verbose)
            qDebug() << "converting" << svgFile << "to" << outFile;
    }
    if (!debug) {
        if (verbose)
            qDebug() << "deleting temporary file" << tmpFile;
        QFile::remove(tmpFile);
    }
    return true;
}

bool png2ico(const QStringList &inFiles, const QString &outFile)
{
    QStringList params;
    params << outFile;

#ifdef PNG2ICO_SUPPORTS_MULTIPLE_COLOR_DEPTH
    foreach(QString file, inFiles)
        params << "--colors" << "16" << file;
    foreach(QString file, inFiles)
        params << "--colors" << "256" << file;
    foreach(QString file, inFiles)
        params << "--colors" << "xxx" << file;
#else
    params << inFiles;
#endif

    int ret = QProcess::execute("png2ico",params);

    if (verbose)
        qDebug() << "converting " << inFiles << "to" << outFile << ":" << (ret ? "error" : "okay");
    return ret ? false : true;
}
    

int main(int argc, char **argv)
{
    if(argc < 3) {
        qDebug() << "Usage : svg2ico <options> <svgfilename> <icofilename>";
        qDebug() << "options: --verbose print execution details";
        qDebug() << "         --debug   print debugging information e.g. do not delete temporary files";
        return -1;
    }
    int i = 1;
    if (QString(argv[i]) == "--verbose") {
        verbose = true;
        i++;
    }
    else if (QString(argv[i]) == "--debug") {
        debug = true;
        i++;
    }

    QString svgFile = QString::fromLocal8Bit(argv[i++]);
    QString icoFile = QString::fromLocal8Bit(argv[i++]);
    QString pngFile = icoFile; 
    pngFile.replace(".ico","-%1.png");
    
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

    int ret = png2ico(pngFiles,icoFile);

    if (!debug) {
        QFile::remove(pngFile.arg("16"));
        QFile::remove(pngFile.arg("32"));
        QFile::remove(pngFile.arg("48"));
    #ifdef VISTA_ICON_SUPPORT
        QFile::remove(pngFile.arg("128"));
    #endif
    }
    return ret;
}

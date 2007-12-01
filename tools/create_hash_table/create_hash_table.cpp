// -*- c-basic-offset: 2 -*-
/*
 *  This file is part of the KDE libraries
 *  Copyright (C) 2007 Ralf Habacker (ralf.habacker@freenet.de)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

// replacement for the perl script from kdelibs\kjs\create_hash_table
// works for creating kdesdk/umbrello/codeimport hash table

#include <QCoreApplication>
#include <QFile>
#include <QMap>
#include <QTextStream>
#include <QStringList>
#include <QtDebug>
#include <stdio.h>

#include "lookup.h"

QString inFile;
QString outFile;
bool includeLookupHeader = false;
QString lookupHeader; 
bool useNameSpace  = false; 
QString nameSpace; 
bool quietMode = false; 

class Entry {
public:
    QString name;
    QString token;
    int next;
    int hash;
    friend QDebug &operator<<(QDebug &,Entry &);
};

QDebug &operator<<(QDebug &out,Entry &c)
{
    out << "(" <<  c.token << c.next << ")";
    return out;
}

QMap <int,Entry> map;
struct HashTable hashTable = { 2, 0, 0, 0 };

bool processLine(QTextStream &out, QString &line)
{
    static QString tableName;
    line.replace("\t"," ");
    QStringList a = line.split(" ",QString::SkipEmptyParts);

    if (line.trimmed().isEmpty() || (a.size() > 0 && a[0] == "//" || a[0] == "/*" || a[0] == "#") )
        return true;

    // @begin keyword 86
    else if (a[0] == "@begin") {
        out << "/* Automatically generated from " << inFile << " using create_hash_table DO NOT EDIT ! */\n";
        out << "\n";
        if (includeLookupHeader)
            out << "#include \"" << lookupHeader << "\"\n";
        out << "\n";
        if (useNameSpace) {
            out << "namespace " << nameSpace << " {\n";
            out << "\n";
            out << "static const struct " << nameSpace << "::HashEntry keywordEntries[] = {\n";
        }
        else
            out << "static const struct HashEntry keywordEntries[] = {\n";

        tableName = a[1];
        hashTable.hashSize = a[2].toInt();
        for(int i = 0; i < hashTable.hashSize; i++) {
            map[i].name = "";
            map[i].token = "";
            map[i].next = 0;
            map[i].hash = 0;
        }
        
        return true;
    }
    else if (a[0] == "@end") {
        QMap<int, Entry>::iterator i = map.begin();
        for(;i != map.end();i++) {
            if (i.value().name != "")
                out << (quietMode ? "" : QString("/* %1 %2 */").arg(i.key()).arg(i.value().hash))
                    << "  { \"" << i.value().name << "\", " 
                    << i.value().token << ", "
                    << "0, "
                    << "0, "
                    << (i.value().next  ? QString("&keywordEntries[%1]").arg(i.value().next) : "0")
                    << " },"
                    << endl;
            else
                out << (quietMode ? "" : QString("/* %1 %2 */").arg(i.key()).arg(i.value().hash))
                    << "  { 0, 0, 0, 0, 0 }" << endl;
        }
        out << "};" << endl;
                
        hashTable.size = map.size();
        out << endl;
        if (useNameSpace) 
            out << "static const struct " << nameSpace << "::HashTable " << tableName << " = { ";
        else
            out << "static const struct HashTable " << tableName << " = { ";
            out << hashTable.type << ", " 
            << hashTable.size << ", "
            << "keywordEntries, " 
            << hashTable.hashSize << " };\n";
        if (useNameSpace) 
            out << "} // namespace\n";
        return false;
    }
    else {
        int key = Lookup::hash(a[0]) % hashTable.hashSize; 
        if (map[key].name == "") {
            map[key].name = a[0];
            map[key].token = a[1];
            map[key].hash = key;
        }
        else {
            int i = map.size();
            map[i].name= a[0];
            map[i].token = a[1];
            map[i].next = 0;
            map[i].hash = key;
            // search last free 
            while(map[key].next) 
                key = map[key].next; 
            map[key].next = i;
        }
        return true;
    }
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc,argv);
    QStringList args = QCoreApplication::arguments();

    for (int i = 1; i < args.size(); i++)
    {
        bool hasValue = i < args.count()-1;
        if (args[i] == "-i" && hasValue) {
            includeLookupHeader = 1;
            lookupHeader = args[++i];
        }
        else if (args[i] == "-q" ) {
            quietMode = true;
        }
        else if (args[i] == "-n" && hasValue) {
            useNameSpace = true;
            nameSpace = args[++i];
        }
        else if (inFile.isEmpty()) 
            inFile = args[i];
        else if (outFile.isEmpty()) 
            outFile = args[i];
    }

    if (inFile.isEmpty() || outFile.isEmpty()) {
        qDebug() << "Usage:" << argv[0] << "<options>" << "<keyword table file>" << "<output file>";
        qDebug() << "Options:";
        qDebug() << "\t-i <filename>   add additional include file <filename>";
        qDebug() << "\t-n <namespace>  define variables in namespace <namespace>";
        qDebug() << "\t-q              don't print hash table infos";
        return 1;
    }        
    QFile fin(inFile);
    if (!fin.exists()) {
        qDebug() << "file" << inFile << "does not exists";
        return 2;
    }
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "could not open file" << inFile;
        return 3;
    }        

    QFile fout(outFile);
    if (!fout.open(QIODevice::WriteOnly))
        return 4;
    QTextStream out(&fout);

    while (!fin.atEnd()) {
         QString line = fin.readLine().replace("\n","");
         if (!processLine(out,line))
            break;
    }
    fin.close();
    return 0;
}
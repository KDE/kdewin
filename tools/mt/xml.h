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

   xml support for manifest tool 
*/

#ifndef XML_H
#define XML_H

#include <string>
#include <iostream>

namespace Base {

class Attribute {
    public: 
        Attribute(std::string a, std::string b=std::string()) : m_key(a), m_attribute(b)
        {
        }

        void setAttributes(std::string &a) { m_attribute = a; }
        std::string get()  
        { 
            std::string b = getBodyTag();
            if (b.size())
                return getOpenTag(b.size() > 0) + b + getCloseTag();
            else
                return getOpenTag(false);
        }

    protected:
        virtual std::string getOpenTagParameter() { return m_attribute; }
        virtual std::string getBodyTag() { return ""; }
        virtual std::string getOpenTag(bool hasContent=true)  
        {
            std::string params = getOpenTagParameter();
            return "<" + m_key + (params.size() ? " " + params : "") + (hasContent ? ">" : "/>") + eol; 
        }
        virtual std::string getCloseTag() { return "</" + m_key + ">" + eol; }

        std::string m_key;      
        std::string m_attribute;      
        static std::string eol; 
};

class Parser {
    public:
    
        bool parse(std::string &s)
        {
            std::string line;
            std::string::iterator it;
            for ( it=s.begin() ; it < s.end(); it++ )
            {
                char c = *it;
                if (c != 0x0d)
                {
                    line += c;
                    continue;
                }
                // skip x0a
                it++;

                //std::cerr << "----" << line << std::endl << std::endl;
                parseLine(line);
                line = "";
            }
            return true;
        }

        virtual bool applyItem(std::string &key,std::string &params)
        {
            return false;
        }

        bool parseLine(std::string &s)
        {
            std::string key;
            std::string params;
            // extract xml key and optional attributes 

            // dependending of the given key set attributes of the related child 
            applyItem(key,params);
            return true;
        }
};


class Assembly : public Base::Attribute {
    public: 

        Assembly() : Base::Attribute("assembly","xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\"")
        {
        }
};

class XML : public Base::Attribute, public Parser {
    public: 
        XML() : Base::Attribute("")
        {
        }

        virtual std::string getOpenTag(bool hasContent=true) 
        {
            return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" + eol;
        }

        virtual std::string getCloseTag() 
        {
            return eol;
        }
};

}

/// Dependency Assemble
namespace Dependency {

class AssemblyIdentity : public Base::Attribute {
    public: 
        AssemblyIdentity() : Base::Attribute("assemblyIdentity")
        {
        }    
        
        virtual std::string getOpenTagParameter() 
        {
             return "type=\"win32\" name=\"Microsoft.VC80.CRT\" version=\"8.0.50727.762\" processorArchitecture=\"x86\" publicKeyToken=\"1fc8b3b9a1e18e3b\"";
        }
};

class DependentAssembly : public Base::Attribute {
    public: 
        AssemblyIdentity assemblyIdentity;

        DependentAssembly() : Base::Attribute("dependentAssembly")
        {
        }    
        
        virtual std::string getBodyTag() 
        {
            return assemblyIdentity.get();
        }
};

class Dependency : public Base::Attribute {
    public: 
        DependentAssembly dependentAssembly;

        Dependency() : Base::Attribute("dependency")
        {
        }    
        
        virtual std::string getBodyTag() 
        {
            return dependentAssembly.get();
        }
};

class Assembly : public Base::Assembly {
    public: 
        Dependency dependency;

        Assembly() : Base::Assembly()
        {
        }
        
        virtual std::string getBodyTag() 
        {
            return dependency.get();
        }
};

class XML : public Base::XML {
    public: 
        Assembly assembly;

        XML() : Base::XML()
        {
        }

        virtual std::string getBodyTag() 
        {
            return assembly.get();
        }

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key == "assembly")
                assembly.setAttributes(params);
            else if (key == "assemblyIdentity")
                assembly.dependency.dependentAssembly.assemblyIdentity.setAttributes(params);
            else 
                return false;
            return true;
        }
};

}

/// Dependency TrustInfo/Security
namespace Security {

class RequestedExecutionLevel : public Base::Attribute {
    public: 
        typedef enum { undefined, asInvoker, highestAvailable, requireAdministrator } ExecutionLevel;
        RequestedExecutionLevel() : Base::Attribute("requestedExecutionLevel")
            , m_executionLevel(asInvoker), m_uiAccess(true)
        {
        }

        virtual std::string getOpenTagParameter() 
        {
            std::string a; 
            a += "level=\"";
            switch(m_executionLevel) {
                case asInvoker:             a += "asInvoker"; break;
                case highestAvailable:      a += "highestAvailable"; break;
                case requireAdministrator:  a += "requireAdministrator"; break;
                default:                    a += "undefined"; break;
            }
            a += "\" uiAccess=\"";
            a += m_uiAccess ? "true" : "false"; 
            a += "\"";
            return a;
        }
        
    private:
        ExecutionLevel m_executionLevel;
        bool m_uiAccess;
};

class RequestPriviliges : public Base::Attribute {    public:
        RequestedExecutionLevel requestedExecutionLevel;
        
        RequestPriviliges() : Base::Attribute("requestedPrivileges")
        {
        }                

        virtual std::string getBodyTag() 
        {
            return requestedExecutionLevel.get();
        }
};

class Security : public Base::Attribute {
    public: 
        RequestPriviliges requestPriviliges;

        Security() : Base::Attribute("security")
        {            
        }

        virtual std::string getBodyTag() 
        {
            return requestPriviliges.get();
        }
};

class TrustInfo : public Base::Attribute {
    public: 
        Security security;

        TrustInfo() : Base::Attribute("trustInfo","xmlns=\"urn:schemas-microsoft-com:asm.v3\"")
        {
        }    
        
        virtual std::string getBodyTag() 
        {
            return security.get();
        }
};

class Assembly : public Base::Assembly {
    public: 
        TrustInfo trustInfo;

        Assembly() : Base::Assembly()
        {
        }
        
        virtual std::string getBodyTag() 
        {
            return trustInfo.get();
        }
};


class XML : public Base::XML {
    public: 
        Assembly assembly;

        XML() : Base::XML()
        {
        }

        virtual std::string getBodyTag() 
        {
            return assembly.get();
        }

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key == "assembly")
                assembly.setAttributes(params);
            else if (key == "trustInfo")
                assembly.trustInfo.setAttributes(params);
            else if (key == "requestedExecutionLevel")
                assembly.trustInfo.security.requestPriviliges.requestedExecutionLevel.setAttributes(params);
            else
                return false;
            return true;
        }
};

}

#endif

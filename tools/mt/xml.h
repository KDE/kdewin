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
        Attribute(const std::string a, std::string b=std::string()) 
            : m_key(a), m_attribute(b)
        {
        }

        void setValues(const std::string &a) 
        { 
            m_attribute = a; 
        }
        
        void clear() 
        { 
            m_attribute = ""; 
        }

        std::string get()  
        { 
            static int intention = -1; 

            std::string a,c;
            for(int i = 0; i < intention; i++)
                c += ' ';

            intention++;
            std::string b = getBodyTag();
            if (b.size())
                a += c + getOpenTag(b.size() > 0) + b + c + getCloseTag();
            else
                a += c + getOpenTag(false);
            intention--;
            return a;
        }

    protected:
        virtual std::string getOpenTagParameter() { return m_attribute; }
        virtual std::string getBodyTag() { return std::string(); }
        virtual std::string getOpenTag(bool hasContent=true)  
        {
            std::string params = getOpenTagParameter();
            return "<" + m_key + (params.size() ? " " + params : "") + (hasContent ? ">" : "/>") + eol; 
        }
        virtual std::string getCloseTag() { return "</" + m_key + ">" + eol; }

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key != m_key) 
                return false;
            m_attribute = params;
            return true;
        }
        
        std::string m_key;      
        std::string m_attribute;      
        static std::string eol; 
};

class Assembly : public Base::Attribute {
    public: 

        Assembly() : Base::Attribute("assembly","xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\"")
        {
        }
};

class XML : public Base::Attribute {
    public: 
        XML() : Base::Attribute("?xml")
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
        bool parse(const std::string &s)
        {
            std::string line;
            std::string::const_iterator it;
            for ( it=s.begin() ; it < s.end(); ++it )
            {
                char c = *it;
                if (c != 0x0d && c != 0x0a)
                {
                    line += c;
                    continue;
                }
                if (c == 0x0d)
                    // skip x0a
                    it++;

                //std::cerr << "----" << line << std::endl << std::endl;
                parseLine(line);
                line = "";
            }
            return true;
        }

        bool parseLine(const std::string &s)
        {
            std::string key;
            std::string params;
            // extract xml key and optional attributes 
            int keyPos = s.find('<');
            int paramsPos = s.find(' ',keyPos);
            int endPos = s.find('>',keyPos);
            if (keyPos == std::string::npos || endPos == std::string::npos)
                return false;
                
            if (paramsPos != std::string::npos && paramsPos > keyPos)
            {
                params = s.substr(paramsPos+1,endPos-paramsPos-1);
                key = s.substr(keyPos+1,paramsPos-keyPos-1);

            }
            else
            {
                key = s.substr(keyPos+1,endPos-keyPos-1);
            }  
            
            // dependending of the given key set attributes of the related child 
            return applyItem(key,params);
        }
};

}

class AssemblyIdentity : public Base::Attribute {
    public: 
        AssemblyIdentity() : Base::Attribute("assemblyIdentity"/*,"type=\"win32\" name=\"Microsoft.VC80.CRT\" version=\"8.0.50727.762\" processorArchitecture=\"x86\" publicKeyToken=\"1fc8b3b9a1e18e3b\""*/)
        {
        }    
        
        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key != m_key) 
                return false;

            m_attribute = params;
            return true;
        }
        
    private:
        std::string m_value;
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

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key == m_key) 
                return true;
            return assemblyIdentity.applyItem(key,params);
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

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key == m_key) 
                return true;
            return dependentAssembly.applyItem(key,params);
        }
};

// trustinfo

class RequestedExecutionLevel : public Base::Attribute {
    public: 
        typedef enum { undefined, asInvoker, highestAvailable, requireAdministrator } ExecutionLevel;
        RequestedExecutionLevel() : Base::Attribute("requestedExecutionLevel")
            , m_executionLevel(asInvoker), m_uiAccess(true)
        {
        }

		void setExecutionLevel(ExecutionLevel level) { m_executionLevel = level; }
		void setUiAccess(bool state) { m_uiAccess = state; }

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

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key != m_key)
                return false;
            // extract parameters
            if (params.find("asInvoker") != std::string::npos)
                m_executionLevel = asInvoker;
            else if (params.find("highestAvailable") != std::string::npos)
                m_executionLevel = highestAvailable;
            else if (params.find("requireAdministrator") != std::string::npos)
                m_executionLevel = requireAdministrator;
            else 
                std::cerr << "invalid value for executionLevel in string: " << params << std::endl;

            if (params.find("true") != std::string::npos)
                m_uiAccess = true;
            else if (params.find("false") != std::string::npos)
                m_uiAccess = false;
            else
                std::cerr << "invalid value for uiAccess in string: " << params << std::endl;
            return true;
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

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key == m_key)
                return true;
            return requestedExecutionLevel.applyItem(key,params);
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

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key == m_key)
                return true;
            return requestPriviliges.applyItem(key,params);
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

        virtual bool applyItem(std::string &key,std::string &params)
        {
            return security.applyItem(key,params);
        }
};

class Assembly : public Base::Assembly {
    public: 
        TrustInfo trustInfo;
        Dependency dependency;

        Assembly() : Base::Assembly()
        {
        }
        
        virtual std::string getBodyTag() 
        {
            return trustInfo.get() + dependency.get();
        }

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key == m_key)
                return true;
            if (trustInfo.applyItem(key,params))
                return true;
            return dependency.applyItem(key,params);
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
            if (key == m_key)
                return true;
            return assembly.applyItem(key,params);
        }
};


#endif

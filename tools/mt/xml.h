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

/** 
    holds a single xml element
    A xml element is setup of a tag name, tag attributes and content 
*/
class Element {
    public: 
        Element(const std::string tagName, std::string attributes=std::string(), std::string content=std::string()) 
            : m_key(tagName), m_attributes(attributes), m_content(content)
        {
        }

        /// set attributes of xml tag
        void setAttributes(const std::string &attributes) 
        { 
            m_attributes = attributes; 
        }
        
        /// return attributes of xml tag
        std::string attributes() const
        { 
            return m_attributes;
        }

        /// set content of xml element
        void setContent(const std::string &content) 
        { 
            m_content = content; 
        }
        
        /// return content of xml element
        virtual std::string content() const
        { 
            return m_content;
        }

        /// clear attributes of xml tag
        void clear() 
        { 
            m_attributes = ""; 
        }

        /// return string with complete xml tag         
        std::string get()  
        { 
            static int intention = -1; 

            std::string a,c;
            for(int i = 0; i < intention; i++)
                c += ' ';

            intention++;
            std::string b = content();
            if (b.size())
                a += c + startTag(b.size() > 0) + b + c + endTag();
            else
                a += c + startTag(false);
            intention--;
            return a;
        }

    protected:
        /// return attributes for xml tag string 
        virtual std::string startTagAttributes() { return m_attributes; }

        /**
          return string with xml start tag including element attributes
          if the element has no content (indicated by hasContent=false), 
          the tag is setup as empty tag
        */
        virtual std::string startTag(bool hasContent=true)  
        {
            std::string params = startTagAttributes();
            return "<" + m_key + (params.size() ? " " + params : "") + (hasContent ? ">" : "/>") + eol; 
        }

        /// return string with xml end tag
        virtual std::string endTag() { return "</" + m_key + ">" + eol; }

        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key != m_key) 
                return false;
            m_attributes = params;
            return true;
        }
        
        std::string m_key;      
        std::string m_attributes;      
        std::string m_content;      
        static std::string eol; 
};

class Assembly : public Base::Element {
    public: 

        Assembly() : Base::Element("assembly","xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\"")
        {
        }
};

class XML : public Base::Element {
    public: 
        XML() : Base::Element("?xml")
        {
        }

        virtual std::string startTag(bool hasContent=true) 
        {
            return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" + eol;
        }

        virtual std::string endTag() 
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

// attributes ar something like ,"type=\"win32\" name=\"Microsoft.VC80.CRT\" version=\"8.0.50727.762\" processorArchitecture=\"x86\" publicKeyToken=\"1fc8b3b9a1e18e3b\"" 
class AssemblyIdentity : public Base::Element {
    public: 
        AssemblyIdentity() : Base::Element("assemblyIdentity")
        {
        }    
        
        virtual bool applyItem(std::string &key,std::string &params)
        {
            if (key != m_key) 
                return false;

            m_attributes = params;
            return true;
        }
        
    private:
        std::string m_value;
};

// TODO support more then one AssemblyIdentity 
class DependentAssembly : public Base::Element {
    public: 
        AssemblyIdentity assemblyIdentity;

        DependentAssembly() : Base::Element("dependentAssembly")
        {
        }    
        
        virtual std::string content() 
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

class Dependency : public Base::Element {
    public: 
        DependentAssembly dependentAssembly;

        Dependency() : Base::Element("dependency")
        {
        }    
        
        virtual std::string content() 
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

class RequestedExecutionLevel : public Base::Element {
    public: 
        typedef enum { undefined, asInvoker, highestAvailable, requireAdministrator } ExecutionLevel;
        RequestedExecutionLevel() : Base::Element("requestedExecutionLevel")
            , m_executionLevel(asInvoker), m_uiAccess(true)
        {
        }

		void setExecutionLevel(ExecutionLevel level) { m_executionLevel = level; }
		void setUiAccess(bool state) { m_uiAccess = state; }

        virtual std::string startTagAttributes() 
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

class RequestPriviliges : public Base::Element {    public:
        RequestedExecutionLevel requestedExecutionLevel;
        
        RequestPriviliges() : Base::Element("requestedPrivileges")
        {
        }                

        virtual std::string content() 
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

class Security : public Base::Element {
    public: 
        RequestPriviliges requestPriviliges;

        Security() : Base::Element("security")
        {            
        }

        virtual std::string content() 
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

class TrustInfo : public Base::Element {
    public: 
        Security security;

        TrustInfo() : Base::Element("trustInfo","xmlns=\"urn:schemas-microsoft-com:asm.v3\"")
        {
        }    
        
        virtual std::string content() 
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
        
        virtual std::string content() 
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

        virtual std::string content() 
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

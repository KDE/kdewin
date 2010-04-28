/* This file is part of the KDE project
   Copyright (C) 2010 Ralf Habacker <ralf.habacker@freenet.de>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU rary General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   rary General Public License for more details.

   You should have received a copy of the GNU rary General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

/*
  IID and CLSID instances for wbemuuid.lib 
  
  not complete yet
  
  only instances containing real values should be exported by 
  replacing TEMPLATE through EXTERN_C
*/  

#include <guiddef.h>

#define EXTERN_C 

#define TEMPLATE static

/* PassiveSink */
TEMPLATE const IID CLSID_PseudoSink;

TEMPLATE const IID IID_IWbemDecoupledEventSink;

/* WbemUtilities_v1 */
TEMPLATE const IID CLSID_WbemDefPath;
TEMPLATE const IID CLSID_WbemQuery;

TEMPLATE const IID IID_IWbemPath;
TEMPLATE const IID IID_IWbemPathKeyList;
TEMPLATE const IID IID_IWbemQuery;

/* WMIEXTENSION */
TEMPLATE const IID CLSID_WMIExtension;

TEMPLATE const IID IID_IWMIExtension;

/* WbemScripting */
TEMPLATE const IID CLSID_SWbemDateTime;
TEMPLATE const IID CLSID_SWbemEventSource;
TEMPLATE const IID CLSID_SWbemLocator;
TEMPLATE const IID CLSID_SWbemNamedValue;
TEMPLATE const IID CLSID_SWbemNamedValueSet;
TEMPLATE const IID CLSID_SWbemMethod;
TEMPLATE const IID CLSID_SWbemMethodSet;
TEMPLATE const IID CLSID_SWbemObject;
TEMPLATE const IID CLSID_SWbemObjectEx;
TEMPLATE const IID CLSID_SWbemObjectPath;
TEMPLATE const IID CLSID_SWbemObjectSet;
TEMPLATE const IID CLSID_SWbemPrivilege;
TEMPLATE const IID CLSID_SWbemPrivilegeSet;
TEMPLATE const IID CLSID_SWbemProperty;
TEMPLATE const IID CLSID_SWbemPropertySet;
TEMPLATE const IID CLSID_SWbemQualifier;
TEMPLATE const IID CLSID_SWbemQualifierSet;
TEMPLATE const IID CLSID_SWbemLastError;
TEMPLATE const IID CLSID_SWbemRefreshableItem;
TEMPLATE const IID CLSID_SWbemRefresher;
TEMPLATE const IID CLSID_SWbemSecurity;
TEMPLATE const IID CLSID_SWbemServices;
TEMPLATE const IID CLSID_SWbemServicesEx;
TEMPLATE const IID CLSID_SWbemSink;

TEMPLATE const IID DIID_ISWbemSinkEvents;

TEMPLATE const IID IID_ISWbemDateTime;
TEMPLATE const IID IID_ISWbemEventSource;
TEMPLATE const IID IID_ISWbemLastError;
TEMPLATE const IID IID_ISWbemLocator;
TEMPLATE const IID IID_ISWbemNamedValue;
TEMPLATE const IID IID_ISWbemNamedValueSet;
TEMPLATE const IID IID_ISWbemMethod;
TEMPLATE const IID IID_ISWbemMethodSet;
TEMPLATE const IID IID_ISWbemObject;
TEMPLATE const IID IID_ISWbemObjectEx;
TEMPLATE const IID IID_ISWbemObjectPath;
TEMPLATE const IID IID_ISWbemObjectSet;
TEMPLATE const IID IID_ISWbemPrivilege;
TEMPLATE const IID IID_ISWbemPrivilegeSet;
TEMPLATE const IID IID_ISWbemProperty;
TEMPLATE const IID IID_ISWbemPropertySet;
TEMPLATE const IID IID_ISWbemQualifier;
TEMPLATE const IID IID_ISWbemQualifierSet;
TEMPLATE const IID IID_ISWbemRefresher;
TEMPLATE const IID IID_ISWbemRefreshableItem;
TEMPLATE const IID IID_ISWbemSecurity;
TEMPLATE const IID IID_ISWbemServices;
TEMPLATE const IID IID_ISWbemServicesEx;
TEMPLATE const IID IID_ISWbemSink;

/* WbemTransports_v1 */
TEMPLATE const IID CLSID_WbemDCOMTransport;
TEMPLATE const IID CLSID_WbemLevel1Login;
TEMPLATE const IID CLSID_WbemLocalAddrRes;
TEMPLATE const IID CLSID_WbemUninitializedClassObject;

TEMPLATE const IID IID_IWbemAddressResolution;
TEMPLATE const IID IID_IWbemClientConnectionTransport;
TEMPLATE const IID IID_IWbemClientTransport;
TEMPLATE const IID IID_IWbemConnectorLogin;
TEMPLATE const IID IID_IWbemConstructClassObject;
TEMPLATE const IID IID_IWbemLevel1Login;
TEMPLATE const IID IID_IWbemTransport;

/* WbemClient_v1 */
TEMPLATE const IID IID_IEnumWbemClassObject;
TEMPLATE const IID IID_IUnsecuredApartment;
TEMPLATE const IID IID_IWbemClassObject;
EXTERN_C const IID IID_IWbemLocator = {
    0xDC12A687,
    0x737F, 0x11CF,
    0x88,0x4D,0x00,0xAA,0x00,0x4B,0x2E,0x24
};
TEMPLATE const IID IID_IWbemBackupRestore;
TEMPLATE const IID IID_IWbemBackupRestoreEx;
TEMPLATE const IID IID_IWbemConfigureRefresher;
TEMPLATE const IID IID_IWbemCallResult;
TEMPLATE const IID IID_IWbemContext;
TEMPLATE const IID IID_IWbemHiPerfEnum;
TEMPLATE const IID IID_IWbemObjectAccess;
TEMPLATE const IID IID_IWbemObjectSink;
TEMPLATE const IID IID_IWbemQualifierSet;
TEMPLATE const IID IID_IWbemRefresher;
TEMPLATE const IID IID_IWbemServices;
TEMPLATE const IID IID_IWbemStatusCodeText;
TEMPLATE const IID IID_IWbemUnsecuredApartment;

/* PassiveSink */
TEMPLATE const CLSID CLSID_PseudoSink;

TEMPLATE const IID IID_IWbemDecoupledEventSink;

/* WbemUtilities_v1 */
TEMPLATE const CLSID CLSID_WbemDefPath;
TEMPLATE const CLSID CLSID_WbemQuery;

TEMPLATE const IID IID_IWbemPathKeyList;
TEMPLATE const IID IID_IWbemPath;
TEMPLATE const IID IID_IWbemQuery;

/* WMIEXTENSION */
TEMPLATE const CLSID CLSID_WMIExtension;

TEMPLATE const IID IID_IWMIExtension;

/* WbemScripting */
TEMPLATE const CLSID CLSID_SWbemDateTime;
TEMPLATE const CLSID CLSID_SWbemEventSource;
TEMPLATE const CLSID CLSID_SWbemLastError;
TEMPLATE const CLSID CLSID_SWbemLocator;
TEMPLATE const CLSID CLSID_SWbemNamedValue;
TEMPLATE const CLSID CLSID_SWbemNamedValueSet;
TEMPLATE const CLSID CLSID_SWbemMethod;
TEMPLATE const CLSID CLSID_SWbemMethodSet;
TEMPLATE const CLSID CLSID_SWbemQualifier;
TEMPLATE const CLSID CLSID_SWbemQualifierSet;
TEMPLATE const CLSID CLSID_SWbemPrivilege;
TEMPLATE const CLSID CLSID_SWbemPrivilegeSet;
TEMPLATE const CLSID CLSID_SWbemRefreshableItem;
TEMPLATE const CLSID CLSID_SWbemProperty;
TEMPLATE const CLSID CLSID_SWbemPropertySet;
TEMPLATE const CLSID CLSID_SWbemObject;
TEMPLATE const CLSID CLSID_SWbemObjectEx;
TEMPLATE const CLSID CLSID_SWbemObjectPath;
TEMPLATE const CLSID CLSID_SWbemObjectSet;
TEMPLATE const CLSID CLSID_SWbemRefresher;
TEMPLATE const CLSID CLSID_SWbemServices;
TEMPLATE const CLSID CLSID_SWbemServicesEx;
TEMPLATE const CLSID CLSID_SWbemSink;
TEMPLATE const CLSID CLSID_SWbemSecurity;

TEMPLATE const IID DIID_ISWbemSinkEvents;

TEMPLATE const IID IID_ISWbemDateTime;
TEMPLATE const IID IID_ISWbemEventSource;
TEMPLATE const IID IID_ISWbemLastError;
TEMPLATE const IID IID_ISWbemLocator;
TEMPLATE const IID IID_ISWbemNamedValue;
TEMPLATE const IID IID_ISWbemNamedValueSet;
TEMPLATE const IID IID_ISWbemMethod;
TEMPLATE const IID IID_ISWbemMethodSet;
TEMPLATE const IID IID_ISWbemObject;
TEMPLATE const IID IID_ISWbemObjectEx;
TEMPLATE const IID IID_ISWbemObjectSet;
TEMPLATE const IID IID_ISWbemObjectPath;
TEMPLATE const IID IID_ISWbemPrivilege;
TEMPLATE const IID IID_ISWbemPrivilegeSet;
TEMPLATE const IID IID_ISWbemProperty;
TEMPLATE const IID IID_ISWbemPropertySet;
TEMPLATE const IID IID_ISWbemQualifier;
TEMPLATE const IID IID_ISWbemQualifierSet;
TEMPLATE const IID IID_ISWbemRefresher;
TEMPLATE const IID IID_ISWbemRefreshableItem;
TEMPLATE const IID IID_ISWbemSecurity;
TEMPLATE const IID IID_ISWbemServices;
TEMPLATE const IID IID_ISWbemServicesEx;
TEMPLATE const IID IID_ISWbemSink;

/* WbemTransports_v1 */
TEMPLATE const CLSID CLSID_WbemDCOMTransport;
TEMPLATE const CLSID CLSID_WbemLevel1Login;
TEMPLATE const CLSID CLSID_WbemLocalAddrRes;
TEMPLATE const CLSID CLSID_WbemUninitializedClassObject;

TEMPLATE const IID IID_IWbemAddressResolution;
TEMPLATE const IID IID_IWbemClientTransport;
TEMPLATE const IID IID_IWbemClientConnectionTransport;
TEMPLATE const IID IID_IWbemConnectorLogin;
TEMPLATE const IID IID_IWbemConstructClassObject;
TEMPLATE const IID IID_IWbemLevel1Login;
TEMPLATE const IID IID_IWbemTransport;

/* WbemClient_v1 */
TEMPLATE const CLSID CLSID_MofCompiler;
TEMPLATE const CLSID CLSID_UnsecuredApartment;
TEMPLATE const CLSID CLSID_WbemBackupRestore;
TEMPLATE const CLSID CLSID_WbemContext;
TEMPLATE const CLSID CLSID_WbemClassObject;
EXTERN_C const CLSID CLSID_WbemLocator = {
    0x4590F811, 
    0x1D3A,0x11D0,
    0x89,0x1F,0x00,0xAA,0x00,0x4B,0x2E,0x24
};
TEMPLATE const CLSID CLSID_WbemObjectTextSrc;
TEMPLATE const CLSID CLSID_WbemRefresher;
TEMPLATE const CLSID CLSID_WbemStatusCodeText;

TEMPLATE const IID IID_IEnumWbemClassObject;
TEMPLATE const IID IID_IMofCompiler;
TEMPLATE const IID IID_IUnsecuredApartment;
TEMPLATE const IID IID_IWbemBackupRestore;
TEMPLATE const IID IID_IWbemBackupRestoreEx;
TEMPLATE const IID IID_IWbemCallResult;
TEMPLATE const IID IID_IWbemClassObject;
TEMPLATE const IID IID_IWbemConfigureRefresher;
TEMPLATE const IID IID_IWbemContext;
TEMPLATE const IID IID_IWbemHiPerfEnum;
TEMPLATE const IID IID_IWbemLocator;
TEMPLATE const IID IID_IWbemObjectAccess;
TEMPLATE const IID IID_IWbemObjectSink;
TEMPLATE const IID IID_IWbemObjectTextSrc;
TEMPLATE const IID IID_IWbemQualifierSet;
TEMPLATE const IID IID_IWbemServices;
TEMPLATE const IID IID_IWbemShutdown;
TEMPLATE const IID IID_IWbemStatusCodeText;
TEMPLATE const IID IID_IWbemRefresher;
TEMPLATE const IID IID_IWbemUnsecuredApartment;

/* WbemProviders_v1 */
TEMPLATE const CLSID CLSID_WbemAdministrativeLocator;
TEMPLATE const CLSID CLSID_WbemAuthenticatedLocator;
TEMPLATE const CLSID CLSID_WbemDecoupledRegistrar;
TEMPLATE const CLSID CLSID_WbemDecoupledBasicEventProvider;
TEMPLATE const CLSID CLSID_WbemUnauthenticatedLocator;

TEMPLATE const IID IID_IWbemDecoupledBasicEventProvider;
TEMPLATE const IID IID_IWbemDecoupledRegistrar;
TEMPLATE const IID IID_IWbemEventConsumerProvider;
TEMPLATE const IID IID_IWbemEventProvider;
TEMPLATE const IID IID_IWbemEventProviderQuerySink;
TEMPLATE const IID IID_IWbemEventProviderSecurity;
TEMPLATE const IID IID_IWbemEventSink;
TEMPLATE const IID IID_IWbemHiPerfProvider;
TEMPLATE const IID IID_IWbemPropertyProvider;
TEMPLATE const IID IID_IWbemProviderInitSink;
TEMPLATE const IID IID_IWbemProviderInit;
TEMPLATE const IID IID_IWbemProviderIdentity;
TEMPLATE const IID IID_IWbemUnboundObjectSink;

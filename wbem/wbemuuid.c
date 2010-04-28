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
*/  

#include <guiddef.h>

#define EXTERN_C 

/* PassiveSink */
EXTERN_C const IID CLSID_PseudoSink;

EXTERN_C const IID IID_IWbemDecoupledEventSink;

/* WbemUtilities_v1 */
EXTERN_C const IID CLSID_WbemDefPath;
EXTERN_C const IID CLSID_WbemQuery;

EXTERN_C const IID IID_IWbemPath;
EXTERN_C const IID IID_IWbemPathKeyList;
EXTERN_C const IID IID_IWbemQuery;

/* WMIEXTENSION */
EXTERN_C const IID CLSID_WMIExtension;

EXTERN_C const IID IID_IWMIExtension;

/* WbemScripting */
EXTERN_C const IID CLSID_SWbemDateTime;
EXTERN_C const IID CLSID_SWbemEventSource;
EXTERN_C const IID CLSID_SWbemLocator;
EXTERN_C const IID CLSID_SWbemNamedValue;
EXTERN_C const IID CLSID_SWbemNamedValueSet;
EXTERN_C const IID CLSID_SWbemMethod;
EXTERN_C const IID CLSID_SWbemMethodSet;
EXTERN_C const IID CLSID_SWbemObject;
EXTERN_C const IID CLSID_SWbemObjectEx;
EXTERN_C const IID CLSID_SWbemObjectPath;
EXTERN_C const IID CLSID_SWbemObjectSet;
EXTERN_C const IID CLSID_SWbemPrivilege;
EXTERN_C const IID CLSID_SWbemPrivilegeSet;
EXTERN_C const IID CLSID_SWbemProperty;
EXTERN_C const IID CLSID_SWbemPropertySet;
EXTERN_C const IID CLSID_SWbemQualifier;
EXTERN_C const IID CLSID_SWbemQualifierSet;
EXTERN_C const IID CLSID_SWbemLastError;
EXTERN_C const IID CLSID_SWbemRefreshableItem;
EXTERN_C const IID CLSID_SWbemRefresher;
EXTERN_C const IID CLSID_SWbemSecurity;
EXTERN_C const IID CLSID_SWbemServices;
EXTERN_C const IID CLSID_SWbemServicesEx;
EXTERN_C const IID CLSID_SWbemSink;

EXTERN_C const IID DIID_ISWbemSinkEvents;

EXTERN_C const IID IID_ISWbemDateTime;
EXTERN_C const IID IID_ISWbemEventSource;
EXTERN_C const IID IID_ISWbemLastError;
EXTERN_C const IID IID_ISWbemLocator;
EXTERN_C const IID IID_ISWbemNamedValue;
EXTERN_C const IID IID_ISWbemNamedValueSet;
EXTERN_C const IID IID_ISWbemMethod;
EXTERN_C const IID IID_ISWbemMethodSet;
EXTERN_C const IID IID_ISWbemObject;
EXTERN_C const IID IID_ISWbemObjectEx;
EXTERN_C const IID IID_ISWbemObjectPath;
EXTERN_C const IID IID_ISWbemObjectSet;
EXTERN_C const IID IID_ISWbemPrivilege;
EXTERN_C const IID IID_ISWbemPrivilegeSet;
EXTERN_C const IID IID_ISWbemProperty;
EXTERN_C const IID IID_ISWbemPropertySet;
EXTERN_C const IID IID_ISWbemQualifier;
EXTERN_C const IID IID_ISWbemQualifierSet;
EXTERN_C const IID IID_ISWbemRefresher;
EXTERN_C const IID IID_ISWbemRefreshableItem;
EXTERN_C const IID IID_ISWbemSecurity;
EXTERN_C const IID IID_ISWbemServices;
EXTERN_C const IID IID_ISWbemServicesEx;
EXTERN_C const IID IID_ISWbemSink;

/* WbemTransports_v1 */
EXTERN_C const IID CLSID_WbemDCOMTransport;
EXTERN_C const IID CLSID_WbemLevel1Login;
EXTERN_C const IID CLSID_WbemLocalAddrRes;
EXTERN_C const IID CLSID_WbemUninitializedClassObject;

EXTERN_C const IID IID_IWbemAddressResolution;
EXTERN_C const IID IID_IWbemClientConnectionTransport;
EXTERN_C const IID IID_IWbemClientTransport;
EXTERN_C const IID IID_IWbemConnectorLogin;
EXTERN_C const IID IID_IWbemConstructClassObject;
EXTERN_C const IID IID_IWbemLevel1Login;
EXTERN_C const IID IID_IWbemTransport;

/* WbemClient_v1 */
EXTERN_C const IID IID_IEnumWbemClassObject;
EXTERN_C const IID IID_IUnsecuredApartment;
EXTERN_C const IID IID_IWbemClassObject;
EXTERN_C const IID IID_IWbemLocator = {
    0xDC12A687,
    0x737F, 0x11CF,
    0x88,0x4D,0x00,0xAA,0x00,0x4B,0x2E,0x24
};
EXTERN_C const IID IID_IWbemBackupRestore;
EXTERN_C const IID IID_IWbemBackupRestoreEx;
EXTERN_C const IID IID_IWbemConfigureRefresher;
EXTERN_C const IID IID_IWbemCallResult;
EXTERN_C const IID IID_IWbemContext;
EXTERN_C const IID IID_IWbemHiPerfEnum;
EXTERN_C const IID IID_IWbemObjectAccess;
EXTERN_C const IID IID_IWbemObjectSink;
EXTERN_C const IID IID_IWbemQualifierSet;
EXTERN_C const IID IID_IWbemRefresher;
EXTERN_C const IID IID_IWbemServices;
EXTERN_C const IID IID_IWbemStatusCodeText;
EXTERN_C const IID IID_IWbemUnsecuredApartment;

/* PassiveSink */
EXTERN_C const CLSID CLSID_PseudoSink;

EXTERN_C const IID IID_IWbemDecoupledEventSink;

/* WbemUtilities_v1 */
EXTERN_C const CLSID CLSID_WbemDefPath;
EXTERN_C const CLSID CLSID_WbemQuery;

EXTERN_C const IID IID_IWbemPathKeyList;
EXTERN_C const IID IID_IWbemPath;
EXTERN_C const IID IID_IWbemQuery;

/* WMIEXTENSION */
EXTERN_C const CLSID CLSID_WMIExtension;

EXTERN_C const IID IID_IWMIExtension;

/* WbemScripting */
EXTERN_C const CLSID CLSID_SWbemDateTime;
EXTERN_C const CLSID CLSID_SWbemEventSource;
EXTERN_C const CLSID CLSID_SWbemLastError;
EXTERN_C const CLSID CLSID_SWbemLocator;
EXTERN_C const CLSID CLSID_SWbemNamedValue;
EXTERN_C const CLSID CLSID_SWbemNamedValueSet;
EXTERN_C const CLSID CLSID_SWbemMethod;
EXTERN_C const CLSID CLSID_SWbemMethodSet;
EXTERN_C const CLSID CLSID_SWbemQualifier;
EXTERN_C const CLSID CLSID_SWbemQualifierSet;
EXTERN_C const CLSID CLSID_SWbemPrivilege;
EXTERN_C const CLSID CLSID_SWbemPrivilegeSet;
EXTERN_C const CLSID CLSID_SWbemRefreshableItem;
EXTERN_C const CLSID CLSID_SWbemProperty;
EXTERN_C const CLSID CLSID_SWbemPropertySet;
EXTERN_C const CLSID CLSID_SWbemObject;
EXTERN_C const CLSID CLSID_SWbemObjectEx;
EXTERN_C const CLSID CLSID_SWbemObjectPath;
EXTERN_C const CLSID CLSID_SWbemObjectSet;
EXTERN_C const CLSID CLSID_SWbemRefresher;
EXTERN_C const CLSID CLSID_SWbemServices;
EXTERN_C const CLSID CLSID_SWbemServicesEx;
EXTERN_C const CLSID CLSID_SWbemSink;
EXTERN_C const CLSID CLSID_SWbemSecurity;

EXTERN_C const IID DIID_ISWbemSinkEvents;

EXTERN_C const IID IID_ISWbemDateTime;
EXTERN_C const IID IID_ISWbemEventSource;
EXTERN_C const IID IID_ISWbemLastError;
EXTERN_C const IID IID_ISWbemLocator;
EXTERN_C const IID IID_ISWbemNamedValue;
EXTERN_C const IID IID_ISWbemNamedValueSet;
EXTERN_C const IID IID_ISWbemMethod;
EXTERN_C const IID IID_ISWbemMethodSet;
EXTERN_C const IID IID_ISWbemObject;
EXTERN_C const IID IID_ISWbemObjectEx;
EXTERN_C const IID IID_ISWbemObjectSet;
EXTERN_C const IID IID_ISWbemObjectPath;
EXTERN_C const IID IID_ISWbemPrivilege;
EXTERN_C const IID IID_ISWbemPrivilegeSet;
EXTERN_C const IID IID_ISWbemProperty;
EXTERN_C const IID IID_ISWbemPropertySet;
EXTERN_C const IID IID_ISWbemQualifier;
EXTERN_C const IID IID_ISWbemQualifierSet;
EXTERN_C const IID IID_ISWbemRefresher;
EXTERN_C const IID IID_ISWbemRefreshableItem;
EXTERN_C const IID IID_ISWbemSecurity;
EXTERN_C const IID IID_ISWbemServices;
EXTERN_C const IID IID_ISWbemServicesEx;
EXTERN_C const IID IID_ISWbemSink;

/* WbemTransports_v1 */
EXTERN_C const CLSID CLSID_WbemDCOMTransport;
EXTERN_C const CLSID CLSID_WbemLevel1Login;
EXTERN_C const CLSID CLSID_WbemLocalAddrRes;
EXTERN_C const CLSID CLSID_WbemUninitializedClassObject;

EXTERN_C const IID IID_IWbemAddressResolution;
EXTERN_C const IID IID_IWbemClientTransport;
EXTERN_C const IID IID_IWbemClientConnectionTransport;
EXTERN_C const IID IID_IWbemConnectorLogin;
EXTERN_C const IID IID_IWbemConstructClassObject;
EXTERN_C const IID IID_IWbemLevel1Login;
EXTERN_C const IID IID_IWbemTransport;

/* WbemClient_v1 */
EXTERN_C const CLSID CLSID_MofCompiler;
EXTERN_C const CLSID CLSID_UnsecuredApartment;
EXTERN_C const CLSID CLSID_WbemBackupRestore;
EXTERN_C const CLSID CLSID_WbemContext;
EXTERN_C const CLSID CLSID_WbemClassObject;
EXTERN_C const CLSID CLSID_WbemLocator = {
    0x4590F811, 
    0x1D3A,0x11D0,
    0x89,0x1F,0x00,0xAA,0x00,0x4B,0x2E,0x24
};
EXTERN_C const CLSID CLSID_WbemObjectTextSrc;
EXTERN_C const CLSID CLSID_WbemRefresher;
EXTERN_C const CLSID CLSID_WbemStatusCodeText;

EXTERN_C const IID IID_IEnumWbemClassObject;
EXTERN_C const IID IID_IMofCompiler;
EXTERN_C const IID IID_IUnsecuredApartment;
EXTERN_C const IID IID_IWbemBackupRestore;
EXTERN_C const IID IID_IWbemBackupRestoreEx;
EXTERN_C const IID IID_IWbemCallResult;
EXTERN_C const IID IID_IWbemClassObject;
EXTERN_C const IID IID_IWbemConfigureRefresher;
EXTERN_C const IID IID_IWbemContext;
EXTERN_C const IID IID_IWbemHiPerfEnum;
EXTERN_C const IID IID_IWbemLocator;
EXTERN_C const IID IID_IWbemObjectAccess;
EXTERN_C const IID IID_IWbemObjectSink;
EXTERN_C const IID IID_IWbemObjectTextSrc;
EXTERN_C const IID IID_IWbemQualifierSet;
EXTERN_C const IID IID_IWbemServices;
EXTERN_C const IID IID_IWbemShutdown;
EXTERN_C const IID IID_IWbemStatusCodeText;
EXTERN_C const IID IID_IWbemRefresher;
EXTERN_C const IID IID_IWbemUnsecuredApartment;

/* WbemProviders_v1 */
EXTERN_C const CLSID CLSID_WbemAdministrativeLocator;
EXTERN_C const CLSID CLSID_WbemAuthenticatedLocator;
EXTERN_C const CLSID CLSID_WbemDecoupledRegistrar;
EXTERN_C const CLSID CLSID_WbemDecoupledBasicEventProvider;
EXTERN_C const CLSID CLSID_WbemUnauthenticatedLocator;

EXTERN_C const IID IID_IWbemDecoupledBasicEventProvider;
EXTERN_C const IID IID_IWbemDecoupledRegistrar;
EXTERN_C const IID IID_IWbemEventConsumerProvider;
EXTERN_C const IID IID_IWbemEventProvider;
EXTERN_C const IID IID_IWbemEventProviderQuerySink;
EXTERN_C const IID IID_IWbemEventProviderSecurity;
EXTERN_C const IID IID_IWbemEventSink;
EXTERN_C const IID IID_IWbemHiPerfProvider;
EXTERN_C const IID IID_IWbemPropertyProvider;
EXTERN_C const IID IID_IWbemProviderInitSink;
EXTERN_C const IID IID_IWbemProviderInit;
EXTERN_C const IID IID_IWbemProviderIdentity;
EXTERN_C const IID IID_IWbemUnboundObjectSink;

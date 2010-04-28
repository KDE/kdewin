/* This file is part of the KDE project
   Copyright (C) 2010 Ralf Habacker <ralf.habacker@freenet.de>

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
*/

#include <guiddef.h>

#define EXTERN_C 

/* WbemCli.h */
EXTERN_C const CLSID CLSID_WbemLocator = {
    0x4590F811, 
    0x1D3A,0x11D0,
    0x89,0x1F,0x00,0xAA,0x00,0x4B,0x2E,0x24
};

#if 0
EXTERN_C const CLSID CLSID_WbemContext;
EXTERN_C const CLSID CLSID_WbemClassObject;
EXTERN_C const CLSID CLSID_WbemStatusCodeText;
EXTERN_C const CLSID CLSID_WbemBackupRestore;
EXTERN_C const CLSID CLSID_WbemRefresher;
EXTERN_C const CLSID CLSID_WbemObjectTextSrc;

/* WbemProv.h */
EXTERN_C const CLSID CLSID_WbemAdministrativeLocator;
EXTERN_C const CLSID CLSID_WbemAuthenticatedLocator;
EXTERN_C const CLSID CLSID_WbemUnauthenticatedLocator;
EXTERN_C const CLSID CLSID_WbemDecoupledRegistrar;
EXTERN_C const CLSID CLSID_WbemDecoupledBasicEventProvider;

/* WbemTran.h */ 
EXTERN_C const CLSID CLSID_WbemLevel1Login;
EXTERN_C const CLSID CLSID_WbemLocalAddrRes;
EXTERN_C const CLSID CLSID_WbemUninitializedClassObject;
EXTERN_C const CLSID CLSID_WbemDCOMTransport;

/* WMIUtils.h */ 
EXTERN_C const CLSID CLSID_WbemDefPath;
EXTERN_C const CLSID CLSID_WbemQuery;
#endif

EXTERN_C const IID IID_IWbemLocator = {
    0xDC12A687,
    0x737F, 0x11CF,
    0x88,0x4D,0x00,0xAA,0x00,0x4B,0x2E,0x24
};

#if 0
/* WbemCli.h */ 
EXTERN_C const IID IID_IWbemClassObject;
EXTERN_C const IID IID_IWbemObjectAccess;
EXTERN_C const IID IID_IWbemQualifierSet;
EXTERN_C const IID IID_IWbemServices;
EXTERN_C const IID IID_IWbemLocator;
EXTERN_C const IID IID_IWbemObjectSink;
EXTERN_C const IID IID_IWbemCallResult;
EXTERN_C const IID IID_IWbemContext;
EXTERN_C const IID IID_IWbemUnsecuredApartment;
EXTERN_C const IID IID_IWbemStatusCodeText;
EXTERN_C const IID IID_IWbemBackupRestore;
EXTERN_C const IID IID_IWbemBackupRestoreEx;
EXTERN_C const IID IID_IWbemRefresher;
EXTERN_C const IID IID_IWbemHiPerfEnum;
EXTERN_C const IID IID_IWbemConfigureRefresher;
EXTERN_C const IID IID_IWbemShutdown;
EXTERN_C const IID IID_IWbemObjectTextSrc;

/* WbemProv.h */ 
EXTERN_C const IID IID_IWbemPropertyProvider;
EXTERN_C const IID IID_IWbemUnboundObjectSink;
EXTERN_C const IID IID_IWbemEventProvider;
EXTERN_C const IID IID_IWbemEventProviderQuerySink;
EXTERN_C const IID IID_IWbemEventProviderSecurity;
EXTERN_C const IID IID_IWbemEventConsumerProvider;
EXTERN_C const IID IID_IWbemProviderInitSink;
EXTERN_C const IID IID_IWbemProviderInit;
EXTERN_C const IID IID_IWbemHiPerfProvider;
EXTERN_C const IID IID_IWbemDecoupledRegistrar;
EXTERN_C const IID IID_IWbemProviderIdentity;
EXTERN_C const IID IID_IWbemDecoupledBasicEventProvider;
EXTERN_C const IID IID_IWbemEventSink;

/* WbemTran.h */ 
EXTERN_C const IID IID_IWbemTransport;
EXTERN_C const IID IID_IWbemLevel1Login;
EXTERN_C const IID IID_IWbemConnectorLogin;
EXTERN_C const IID IID_IWbemAddressResolution;
EXTERN_C const IID IID_IWbemClientTransport;
EXTERN_C const IID IID_IWbemClientConnectionTransport;
EXTERN_C const IID IID_IWbemConstructClassObject;

/* WMIUtils.h */
EXTERN_C const IID IID_IWbemPathKeyList;
EXTERN_C const IID IID_IWbemPath;
EXTERN_C const IID IID_IWbemQuery;
#endif

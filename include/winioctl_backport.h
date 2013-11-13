/*
 * winioctl_backport.h
 *
 * additional IOCTL interface definitions based on the winioctl.h from the new w32api package.
 *
 * This file is part of the kdewin package and is originally from the mingw-w64 w32api package.
 *
 * Contributors:
 *   Created by Patrick Spendrin <ps_ml@gmx.de>
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain. You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED. This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef WINIOCTL_BACKPORT_H
#define WINIOCTL_BACKPORT_H

#include <winioctl.h>

#define IOCTL_STORAGE_QUERY_PROPERTY CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef enum _STORAGE_PROPERTY_ID {
  StorageDeviceProperty              = 0,
  StorageAdapterProperty             = 1,
  StorageDeviceIdProperty            = 2,
  StorageDeviceUniqueIdProperty      = 3,
  StorageDeviceWriteCacheProperty    = 4,
  StorageMiniportProperty            = 5,
  StorageAccessAlignmentProperty     = 6,
  StorageDeviceSeekPenaltyProperty   = 7,
  StorageDeviceTrimProperty          = 8 
} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;

typedef enum _STORAGE_QUERY_TYPE {
  PropertyStandardQuery     = 0,
  PropertyExistsQuery       = 1,
  PropertyMaskQuery         = 2,
  PropertyQueryMaxDefined   = 3 
} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;

typedef struct _STORAGE_PROPERTY_QUERY {
  STORAGE_PROPERTY_ID PropertyId;
  STORAGE_QUERY_TYPE  QueryType;
  BYTE                AdditionalParameters[1];
} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;

typedef struct _STORAGE_DEVICE_DESCRIPTOR {
  DWORD            Version;
  DWORD            Size;
  BYTE             DeviceType;
  BYTE             DeviceTypeModifier;
  BOOLEAN          RemovableMedia;
  BOOLEAN          CommandQueueing;
  DWORD            VendorIdOffset;
  DWORD            ProductIdOffset;
  DWORD            ProductRevisionOffset;
  DWORD            SerialNumberOffset;
  STORAGE_BUS_TYPE BusType;
  DWORD            RawPropertiesLength;
  BYTE             RawDeviceProperties[1];
} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;

typedef struct _STORAGE_ADAPTER_DESCRIPTOR {
  DWORD   Version;
  DWORD   Size;
  DWORD   MaximumTransferLength;
  DWORD   MaximumPhysicalPages;
  DWORD   AlignmentMask;
  BOOLEAN AdapterUsesPio;
  BOOLEAN AdapterScansDown;
  BOOLEAN CommandQueueing;
  BOOLEAN AcceleratedTransfer;
  BYTE    BusType;
  WORD    BusMajorVersion;
  WORD    BusMinorVersion;
} STORAGE_ADAPTER_DESCRIPTOR, *PSTORAGE_ADAPTER_DESCRIPTOR;


#endif /* WINIOCTL_BACKPORT_H */
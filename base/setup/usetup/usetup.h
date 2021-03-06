/*
 *  ReactOS kernel
 *  Copyright (C) 2002 ReactOS Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS text-mode setup
 * FILE:            base/setup/usetup/usetup.h
 * PURPOSE:         Text-mode setup
 * PROGRAMMER:      Eric Kohl
 */

#ifndef _USETUP_PCH_
#define _USETUP_PCH_

/* C Headers */
#include <stdio.h>
#include <stdlib.h>

/* PSDK/NDK */
#define WIN32_NO_STATUS
#include <windef.h>
#include <winbase.h>
#include <winreg.h>
#include <winuser.h>
#include <wincon.h>

#include <strsafe.h>

#define NTOS_MODE_USER
#include <ndk/cmfuncs.h>
#include <ndk/exfuncs.h>
#include <ndk/iofuncs.h>
#include <ndk/kefuncs.h>
#include <ndk/mmfuncs.h>
#include <ndk/obfuncs.h>
#include <ndk/psfuncs.h>
#include <ndk/rtlfuncs.h>
#include <ndk/setypes.h>

/* Filesystem headers */
#include <reactos/rosioctl.h>
#include <fslib/vfatlib.h>
#include <fslib/ext2lib.h>
// #include <fslib/ntfslib.h>

/* Internal Headers */
#include "consup.h"
#include "inffile.h"
#include "inicache.h"
#include "progress.h"
#include "infros.h"
#include "filequeue.h"
#include "registry.h"
#include "fslist.h"
#include "partlist.h"
#include "cabinet.h"
#include "filesup.h"
#include "genlist.h"
#include "mui.h"
#include "errorcode.h"

extern HANDLE ProcessHeap;
extern UNICODE_STRING SourceRootPath;
extern UNICODE_STRING SourceRootDir;
extern UNICODE_STRING SourcePath;
extern BOOLEAN IsUnattendedSetup;
extern PWCHAR SelectedLanguageId;

extern VOID InfSetHeap(PVOID Heap);
extern VOID InfCloseFile(HINF InfHandle);
extern BOOLEAN InfFindNextLine(PINFCONTEXT ContextIn,
                               PINFCONTEXT ContextOut);
extern BOOLEAN InfGetBinaryField(PINFCONTEXT Context,
                                 ULONG FieldIndex,
                                 PUCHAR ReturnBuffer,
                                 ULONG ReturnBufferSize,
                                 PULONG RequiredSize);
extern BOOLEAN InfGetMultiSzField(PINFCONTEXT Context,
                                  ULONG FieldIndex,
                                  PWSTR ReturnBuffer,
                                  ULONG ReturnBufferSize,
                                  PULONG RequiredSize);
extern BOOLEAN InfGetStringField(PINFCONTEXT Context,
                                 ULONG FieldIndex,
                                 PWSTR ReturnBuffer,
                                 ULONG ReturnBufferSize,
                                 PULONG RequiredSize);

#define SetupCloseInfFile InfCloseFile
#define SetupFindNextLine InfFindNextLine
#define SetupGetBinaryField InfGetBinaryField
#define SetupGetMultiSzFieldW InfGetMultiSzField
#define SetupGetStringFieldW InfGetStringField

#ifndef _PAGE_NUMBER_DEFINED
#define _PAGE_NUMBER_DEFINED
typedef enum _PAGE_NUMBER
{
    START_PAGE,
    LANGUAGE_PAGE,
    INTRO_PAGE,
    LICENSE_PAGE,
    INSTALL_INTRO_PAGE,

//    SCSI_CONTROLLER_PAGE,

    DEVICE_SETTINGS_PAGE,
    COMPUTER_SETTINGS_PAGE,
    DISPLAY_SETTINGS_PAGE,
    KEYBOARD_SETTINGS_PAGE,
    LAYOUT_SETTINGS_PAGE,

    SELECT_PARTITION_PAGE,
    CREATE_PRIMARY_PARTITION_PAGE,
    CREATE_EXTENDED_PARTITION_PAGE,
    CREATE_LOGICAL_PARTITION_PAGE,
    CONFIRM_DELETE_SYSTEM_PARTITION_PAGE,
    DELETE_PARTITION_PAGE,

    SELECT_FILE_SYSTEM_PAGE,
    FORMAT_PARTITION_PAGE,
    CHECK_FILE_SYSTEM_PAGE,

    PREPARE_COPY_PAGE,
    INSTALL_DIRECTORY_PAGE,
    FILE_COPY_PAGE,
    REGISTRY_PAGE,
    BOOT_LOADER_PAGE,
    BOOT_LOADER_FLOPPY_PAGE,
    BOOT_LOADER_HARDDISK_MBR_PAGE,
    BOOT_LOADER_HARDDISK_VBR_PAGE,

    REPAIR_INTRO_PAGE,

    SUCCESS_PAGE,
    QUIT_PAGE,
    FLUSH_PAGE,
    REBOOT_PAGE,		/* virtual page */
    RECOVERY_PAGE,		/* virtual page */
} PAGE_NUMBER, *PPAGE_NUMBER;
#endif

#define POPUP_WAIT_NONE    0
#define POPUP_WAIT_ANY_KEY 1
#define POPUP_WAIT_ENTER   2

#define InsertAscendingList(ListHead, NewEntry, Type, ListEntryField, SortField)\
{\
  PLIST_ENTRY current;\
\
  current = (ListHead)->Flink;\
  while (current != (ListHead))\
  {\
    if (CONTAINING_RECORD(current, Type, ListEntryField)->SortField >=\
        (NewEntry)->SortField)\
    {\
      break;\
    }\
    current = current->Flink;\
  }\
\
  InsertTailList(current, &((NewEntry)->ListEntryField));\
}

#endif /* _USETUP_PCH_ */

/**
 * @file mailbox.h
 * @brief Boot Mailbox mangement
 *
 * @section License
 *
 * Copyright (C) 2021-2023 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneBOOT Ultimate.
 *
 * This software is provided under a commercial license. You may
 * use this software under the conditions stated in the license
 * terms. This source code cannot be redistributed.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.1
 **/

#ifndef _MAILBOX_H
#define _MAILBOX_H

//Dependencies
#include "os_port.h"
#include "error.h"

//Bootloader mailbox version
#define BOOT_MBX_VERS_MAJOR 1
#define BOOT_MBX_VERS_MINOR 0
#define BOOT_MBX_VERS_PATCH 0
#define BOOT_MBX_VERSION (uint32_t)(      \
   ((BOOT_MBX_VERS_MAJOR & 0xFF) << 16) | \
   ((BOOT_MBX_VERS_MINOR & 0xFF) << 8)  | \
   (BOOT_MBX_VERS_MAJOR & 0xFF))

//Bootloader mailbox signture
#define BOOT_MBX_SIGNATURE 0x1b241671

//Bootloader mailbox maximum PSK size
#define BOOT_MBX_PSK_MAX_SIZE 32


#if defined(_WIN32)

#undef interface
#undef __start_packed
#define __start_packed __pragma( pack(push, 1) )
#undef __end_packed
#define __end_packed __pragma( pack(pop) )
#define __weak

/**
 * @brief Bootloader shared RAM mailbox structure
 **/

__start_packed typedef struct
{
   uint32_t version;          ///<Bootloader Mailbox version
   uint32_t signature;        ///<Bootloader Mailbox signature
   uint32_t pskSize;          ///<Bootloader Mailbox PSK size
   uint8_t psk[32];           ///<Bootloader Mailbox PSK key
   uint8_t reserved[84];      ///<Reserved
}BootMailBox __end_packed;

#else

/**
 * @brief Bootloader shared RAM mailbox structure
 **/

typedef __start_packed struct
{
   uint32_t version;          ///<Bootloader Mailbox version
   uint32_t signature;        ///<Bootloader Mailbox signature
   uint32_t pskSize;          ///<Bootloader Mailbox PSK size
   uint8_t psk[32];           ///<Bootloader Mailbox PSK key
   uint8_t reserved[84];      ///<Reserved
} __end_packed BootMailBox;
#endif


//CycloneBOOT IAP Mailbox functions
error_t setBootMailBox(BootMailBox *mailbox);
error_t getBootMailBox(BootMailBox *mailbox);
error_t checkBootMailBox(BootMailBox *mailbox);

#endif //!_MAILBOX_H
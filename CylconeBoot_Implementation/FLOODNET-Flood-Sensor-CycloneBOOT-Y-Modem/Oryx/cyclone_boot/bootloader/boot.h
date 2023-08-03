/**
 * @file boot.h
 * @brief CycloneBOOT Bootloader managment
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

#ifndef _BOOT_H
#define _BOOT_H

//Dependencies
#include "boot_config.h"
#include "core/flash.h"

#ifndef BOOT_OFFSET
#define BOOT_OFFSET 0x10000
#endif

#ifndef BOOT_FALLBACK_SUPPORT
#define BOOT_FALLBACK_SUPPORT DISABLED
#elif (BOOT_FALLBACK_SUPPORT != ENABLED && BOOT_FALLBACK_SUPPORT != DISABLED)
#error BOOT_FALLBACK_SUPPORT parameter is not valid
#endif

#ifndef BOOT_ANTI_ROLLBACK_SUPPORT
#define BOOT_ANTI_ROLLBACK_SUPPORT DISABLED
#elif (BOOT_ANTI_ROLLBACK_SUPPORT != ENABLED && BOOT_ANTI_ROLLBACK_SUPPORT != DISABLED)
#error BOOT_ANTI_ROLLBACK_SUPPORT parameter is not valid
#endif

#ifndef BOOT_EXT_MEM_ENCRYPTION_SUPPORT
#define BOOT_EXT_MEM_ENCRYPTION_SUPPORT DISABLED
#elif (BOOT_EXT_MEM_ENCRYPTION_SUPPORT != ENABLED && BOOT_EXT_MEM_ENCRYPTION_SUPPORT != DISABLED)
#error BOOT_EXT_MEM_ENCRYPTION_SUPPORT parameter is not valid
#endif


/**
 * @brief Bootloader States definition
 **/

typedef enum
{
   BOOT_STATE_IDLE,
   BOOT_STATE_RUN_APP,
   BOOT_STATE_UPDATE_APP,
   BOOT_STATE_FALLBACK_APP,
   BOOT_STATE_ERROR
}BootState;


/**
 * @brief Bootloader user settings structure
 **/

typedef struct
{
   const FlashDriver *prmFlashDrv;     ///<Primary flash driver
   const FlashDriver *sndFlashDrv;     ///<Secondary flash driver
   uint32_t prmFlashSlotAddr;          ///<Primary flash slot address
   uint32_t prmFlashSlotSize;          ///<Primary flash slot size
   uint32_t sndFlashSlot1Addr;         ///<Secondary flash slot 1 address
   size_t sndFlashSlot1Size;           ///<Secondary flash slot 1 size
#if (BOOT_FALLBACK_SUPPORT == ENABLED)
   uint32_t sndFlashSlot2Addr;         ///<Secondary flash slot 2 address
   size_t sndFlashSlot2Size;           ///<Secondary flash slot 2 size
#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   const char_t *psk;                  ///<Secondary flash slot cipher key
   size_t pskSize;                     ///<Secondary flash slot cipher key size
#endif
#endif
} BootSettings;


/**
 * @brief Bootloader Context structure
 **/

typedef struct
{
   BootState state;              ///<Bootloader state
   BootSettings settings;        ///<Bootloader user settings
   FlashDesc primaryFlash;       ///<Bootloader primary flash memory
   FlashDesc secondaryFlash;     ///<Bootloader secondary (external) flash memory
#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   uint8_t psk[32];              ///<Cipher PSK key for image decryption
   size_t pskSize;               ///<Cipher PSK key size
#endif
} BootContext;


//Bootloader related functions
error_t bootTask(BootContext *context);
void bootGetDefaultSettings(BootSettings *settings);
error_t bootInit(BootContext *context, BootSettings *settings);
error_t bootUpdateApp(BootContext *context, SlotDesc *slot);

//Extern device MCU related function
extern uint32_t mcuGetVtorOffset(void);
extern void mcuSystemReset(void);
extern void mcuJumpToApplication(uint32_t address);

#endif //!_BOOT_H

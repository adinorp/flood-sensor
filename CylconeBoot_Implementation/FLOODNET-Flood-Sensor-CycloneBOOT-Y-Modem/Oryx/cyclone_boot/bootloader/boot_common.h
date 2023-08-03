/**
 * @file boot_common.h
 * @brief CycloneBOOT Bootloader common functions
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

#ifndef _BOOT_COMMON_H
#define _BOOT_COMMON_H

//Dependencies
#include "core/slot.h"
#include "core/image.h"
#include "bootloader/boot.h"
#include "error.h"

//Initialization vector size of encrypted images in external flash memory
#define INIT_VECT_SIZE 16

//CycloneBOOT Bootloader common related functions
error_t bootInitPrimaryFlash(BootContext *context, BootSettings *settings);
error_t bootInitSecondaryFlash(BootContext *context, BootSettings *settings);
error_t bootSelectUpdateImageSlot(BootContext *context, SlotDesc **selectedSlot);
error_t bootUpdateApp(BootContext *context, SlotDesc *slot);
error_t bootCheckImage(SlotDesc *slot);
error_t bootGetSlotImgHeader(SlotDesc *slot, ImageHeader *header);
error_t bootCheckSlotAppResetVector(SlotDesc *slot);

#endif //!_BOOT_COMMON_H

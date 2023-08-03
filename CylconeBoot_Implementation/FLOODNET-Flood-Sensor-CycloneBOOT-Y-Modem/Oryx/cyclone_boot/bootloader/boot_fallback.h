/**
 * @file boot_fallback.h
 * @brief CycloneBOOT Bootloader fallback managment
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

#ifndef _BOOT_FALLBACK_H
#define _BOOT_FALLBACK_H

//Dependencies
#include "bootloader/boot.h"
#include "error.h"

typedef enum
{
   TRIGGER_STATUS_IDLE,
   TRIGGER_STATUS_RAISED
}TriggerStatus;


//CycloneBOOT Booltoader Fallback related functions
error_t fallbackTask(BootContext *context);
error_t fallbackTriggerInit(void);
error_t fallbackTriggerGetStatus(TriggerStatus *status);

#endif //!_BOOT_FALLBACK_H

/**
 * @file boot_config.h
 * @brief CycloneBOOT Bootloader configuration file
 *
 * @section License
 *
 * Copyright (C) 2010-2021 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneBOOT.
 *
 * This software is provided under a commercial license. You may
 * use this software under the conditions stated in the license
 * terms. This source code cannot be redistributed.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.0.2 
 **/

#ifndef _BOOT_CONFIG_H
#define _BOOT_CONFIG_H

//Bootloader trace level
#define BOOT_TRACE_LEVEL TRACE_LEVEL_OFF

//Bootloader external flash memory encryption support
#define BOOT_EXT_MEM_ENCRYPTION_SUPPORT DISABLED//ENABLED

//Bootloader fallback support
#define BOOT_FALLBACK_SUPPORT DISABLED//ENABLED

//Bootloader Anti-Rollback support
#define BOOT_ANTI_ROLLBACK_SUPPORT DISABLED

#endif //!_BOOT_CONFIG_H

/**
 * @file mcu.h
 * @brief CycloneBOOT MCU layer
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

#ifndef _MCU_H
#define _MCU_H

//Dependencies
#include <stdint.h>

//CycloneBOOT MCU Driver Major version
#define MCU_DRIVER_VERSION_MAJOR 0x01
//CycloneBOOT MCU Driver Minor version
#define MCU_DRIVER_VERSION_MINOR 0x00
//CycloneBOOT MCU Driver Revison version
#define MCU_DRIVER_VERSION_PATCH 0x00
//CycloneBOOT MCU Driver version
#define MCU_DRIVER_VERSION (uint32_t)(((MCU_DRIVER_VERSION_MAJOR & 0xFF) << 16) | \
                               ((MCU_DRIVER_VERSION_MINOR & 0xFF) << 8) | \
                               (MCU_DRIVER_VERSION_PATCH & 0xFF))

//CycloneBOOT mcu layer related functions
extern uint32_t mcuGetVtorOffset(void);
extern void mcuSystemReset(void);
extern void mcuJumpToApplication(uint32_t address) __attribute__ ((section (".code_in_ram")));

#endif //!_MCU_H

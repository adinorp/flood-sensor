/**
 * @file arm_driver.h
 * @brief ARM MCU driver managment
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


#ifndef _ARM_DRIVER_H
#define _ARM_DRIVER_H

//Dependencies
#include "stdint.h"

//You must align the offset to the number of exception entries in the vector
// table. The minimum alignment is 32 words, enough for up to 16 interrupts. For more interrupts,
// adjust the alignment by rounding up to the next power of two

#define MCU_VTOR_OFFSET 0x400 //Could be less according to the cortex-m device but
                              // 0x400 will work for every arm cortex-m devices
                              // (16 exceptions + 240 interrupts (max arm interrupt number) = 256 words = 1024 bytes = 0x400 bytes)

//STM32F7xx mcu driver related functions
uint32_t mcuGetVtorOffset(void);
void mcuSystemReset(void);
void mcuJumpToApplication(uint32_t address) __attribute__ ((section (".code_in_ram")));

#endif //!_ARM_DRIVER_H

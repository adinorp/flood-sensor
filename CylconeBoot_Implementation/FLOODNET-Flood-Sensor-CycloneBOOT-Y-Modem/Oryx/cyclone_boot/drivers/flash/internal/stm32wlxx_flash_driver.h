/**
 * @file STM32WLxx_flash_driver.h
 * @brief CycloneBOOT STM32WLxx Flash Driver Template
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

#ifndef _STM32WLxx_FLASH_DRIVER_H
#define _STM32WLxx_FLASH_DRIVER_H

//Dependencies
#include <stdlib.h>
#include <stdint.h>
#include "stm32wlxx_hal.h"
#include "stm32wlxx_hal_flash.h"
#include "core/flash.h"
#include "error.h"

//STM32WLxx name
#define STM32WLxx_FLASH_NAME "STM32WLxx Internal Flash"
//STM32WLxx start addr
#define STM32WLxx_FLASH_ADDR FLASH_BASE
//STM32WLxx write size
#define STM32WLxx_FLASH_WRITE_SIZE (4*2) //double word
//STM32WLxx read size
#define STM32WLxx_FLASH_READ_SIZE 0x4 //32-bits word

//Device flash size
#if (defined(STM32LxxxC))
#define STM32WLxx_FLASH_SIZE 0x40000 //256k flash
#elif (defined(STM32LxxxB))
#define STM32WLxx_FLASH_SIZE 0x20000 //128KB flash
#elif (defined(STM32Lxxx8))
#define STM32WLxx_FLASH_SIZE 0x10000 //64KB flash
#else
#error You MUST define one of the above device part number!
#endif

//Device flash sector size
#define STM32WLxx_FLASH_SECTOR_SIZE 0x800 //2KB sector

//Device flash sector number
#define STM32WLxx_FLASH_SECTOR_NUMBER (STM32WLxx_FLASH_SIZE/STM32WLxx_FLASH_SECTOR_SIZE)

//Device flash bank IDs
#define STM32WLxx_FLASH_BANK1_ID 1

//Device flash bank info
#define STM32WLxx_FLASH_BANK_SIZE STM32WLxx_FLASH_SIZE
#define STM32WLxx_FLASH_BANK1_ADDR FLASH_BASE

//STM32WLxx Internal Memory Flash driver
extern const FlashDriver stm32wlxxFlashDriver;

#endif //!_STM32WLxx_FLASH_DRIVER_H

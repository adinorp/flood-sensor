/**
 * @file STM32L4xx_flash_driver.h
 * @brief CycloneBOOT STM32L4xx Flash Driver Template
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

#ifndef _STM32L4xx_FLASH_DRIVER_H
#define _STM32L4xx_FLASH_DRIVER_H

//Dependencies
#include <stdlib.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"
#include "core/flash.h"
#include "error.h"

//STM32L4xx name
#define STM32L4xx_FLASH_NAME "STM32L4xx Internal Flash"
//STM32L4xx start addr
#define STM32L4xx_FLASH_ADDR FLASH_BASE
//STM32L4xx write size
#define STM32L4xx_FLASH_WRITE_SIZE (4*2) //N-bytes word
//STM32L4xx read size
#define STM32L4xx_FLASH_READ_SIZE 0x4 //32-bytes word

//Device flash size
#if (defined(STM32L47xG) || defined(STM32L48xx) || defined(STM32L49xG) || \
       defined(STM32L4A6xx))
#define STM32L4xx_FLASH_SIZE 0x100000 //1MB flash
#elif (defined(STM32L47xE) || defined(STM32L49xE))
#define STM32L4xx_FLASH_SIZE 0x80000 //512KB flash
#elif (defined(STM32L47xC))
#define STM32L4xx_FLASH_SIZE 0x40000 //256KB flash
#else
#error You MUST define one of the above device part number!
#endif

//Device flash sector size
#define STM32L4xx_FLASH_SECTOR_SIZE 0x800 //2KB sector

//Device flash sector number
#define STM32L4xx_FLASH_SECTOR_NUMBER (STM32L4xx_FLASH_SIZE/STM32L4xx_FLASH_SECTOR_SIZE)

//Device flash bank IDs
#define STM32L4xx_FLASH_BANK1_ID 1
#define STM32L4xx_FLASH_BANK2_ID 2

//Device flash bank info
#if !defined(FLASH_SINGLE_BANK)
#define STM32L4xx_FLASH_BANK_SIZE STM32L4xx_FLASH_SIZE/2
#define STM32L4xx_FLASH_BANK1_ADDR FLASH_BASE
#define STM32L4xx_FLASH_BANK2_ADDR FLASH_BASE+STM32L4xx_FLASH_BANK_SIZE
#else
#define STM32L4xx_FLASH_BANK_SIZE STM32L4xx_FLASH_SIZE
#define STM32L4xx_FLASH_BANK1_ADDR FLASH_BASE
#define STM32L4xx_FLASH_BANK2_ADDR FLASH_BASE
#endif

//STM32L4xx Internal Memory Flash driver
extern const FlashDriver stm32l4xxFlashDriver;

#endif //!_STM32L4xx_FLASH_DRIVER_H

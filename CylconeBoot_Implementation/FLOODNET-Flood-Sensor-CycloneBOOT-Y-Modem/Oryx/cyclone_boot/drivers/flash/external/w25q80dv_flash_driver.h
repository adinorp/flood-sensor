/**
 * @file w25q80dv_flash_driver.h
 * @brief CycloneBOOT W25Q80DV Flash Driver Template
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

#ifndef _W25Q80DV_FLASH_DRIVER_H
#define _W25Q80DV_FLASH_DRIVER_H

//Dependencies
#include <stdlib.h>
#include <stdint.h>
#include "core/flash.h"
#include "error.h"

//W25Q80DV name
#define W25Q80DV_NAME "W25Q80DV External QPSI Nor Flash"
//W25Q80DV start addr
#define W25Q80DV_ADDR 0x00000000
//W25Q80DV write size
#define W25Q80DV_WRITE_SIZE 0x04 //4-bytes word
//W25Q80DV read size
#define W25Q80DV_READ_SIZE 0x04 //4-bytes word

#define BLOCK_32K

//W25Q80DV size
#define W25Q80DV_SIZE 0x100000 //1MB

#if defined(BLOCK_32K)
//W25Q80DV Block size
#define W25Q80DV_BLOCK_SIZE 0x8000 //32KB
//W25Q80DV block number
#define W25Q80DV_BLOCK_NUMBER (W25Q80DV_SIZE / W25Q80DV_BLOCK_SIZE)
#else
//W25Q80DV Block size
#define W25Q80DV_BLOCK_SIZE 0x10000 //64KB
//W25Q80DV block number
#define W25Q80DV_BLOCK_NUMBER (W25Q80DV_SIZE / W25Q80DV_BLOCK_SIZE)
#endif

//W25Q80DV Subsectors 4KB number
#define W25Q80DV_SUBSECTORS_NUMBER 16384
//W25Q80DV Subsectors 4KB size
#define W25Q80DV_SUBSECTORS_SIZE 0x1000

//W25Q80DV Internal Memory Flash driver
extern const FlashDriver w25q80dvFlashDriver;

#endif //!_W25Q80DV_FLASH_DRIVER_H

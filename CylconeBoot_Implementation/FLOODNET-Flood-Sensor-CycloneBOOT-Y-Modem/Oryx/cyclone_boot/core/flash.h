/**
 * @file memory.h
 * @brief CycloneBOOT FLASH layer
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

#ifndef _FLASH_H
#define _FLASH_H

//Dependencies
#include <stdlib.h>
#include <stdint.h>
#include "core/slot.h"
#include "error.h"

//Flash Driver Major version
#define FLASH_DRIVER_VERSION_MAJOR 0x01
//Flash Driver Minor version
#define FLASH_DRIVER_VERSION_MINOR 0x01
//Flash Driver Revision version
#define FLASH_DRIVER_VERSION_PATCH 0x00
//Flash Driver version
#define FLASH_DRIVER_VERSION (uint32_t)(((FLASH_DRIVER_VERSION_MAJOR & 0xFF) << 16) | \
                               ((FLASH_DRIVER_VERSION_MINOR & 0xFF) << 8) | \
                               (FLASH_DRIVER_VERSION_PATCH & 0xFF))

//Number of slot in a memory
#define FLASH_SLOTS_NUMBER 2

//Flash Info flags definition
#define FLASH_FLAGS_LATER_SWAP 0x1

/**
 * @brief Flash Type definition
 **/

typedef enum
{
   FLASH_TYPE_INTERNAL,            //Internal memory
   FLASH_TYPE_EXTERNAL_PARALLEL,   //External parallel memory
   FLASH_TYPE_EXTERNAL_SPI,        //External SPI memory
   FLASH_TYPE_EXTERNAL_QSPI        //External QSPI memory
} FlashType;

#if 0
/**
 * @brief Flash Class definition
 **/

typedef enum
{
   //MEM_CLASS_FLASH,  //Flash memory
   MEM_CLASS_RAM,    //RAM memory
   MEM_CLASS_EEPROM  //EEPROM memory
} FlashClass;
#endif

/**
 * @brief Flash Information definition
 **/

typedef struct
{
   uint32_t version;       ///<Flash driver version
   char* flashName;        ///<Flash memory name
   FlashType flashType;    ///<Flash memory type
   uint32_t flashAddr;     ///<Flash memory start address
   size_t flashSize;       ///<Flash memory size
   size_t writeSize;       ///<Flash memory write size
   size_t readSize;        ///<Flash memory read size
   uint8_t dualBank;       ///<Flash memory dual bank capability
   size_t bankSize;        ///<Flash meory bank size
   uint32_t bank1Addr;     ///<Flash memory bank 1 start address
   uint32_t bank2Addr;     ///<Flash memory bank 2 start address
   uint32_t flags;         ///<Flash memory flags
} FlashInfo;

/**
 * @brief Flash Status definition
 **/

typedef enum
{
   FLASH_STATUS_OK = 0,
   FLASH_STATUS_BUSY,
   FLASH_STATUS_ERR
} FlashStatus;

/**
 * @brief Flash initialization function
 **/

typedef error_t (*FlashInit)(void);


/**
 * @brief Get Flash Information function
 **/

typedef error_t (*FlashGetInfo)(const FlashInfo **info);


/**
 * @brief Get Flash Status function
 **/

typedef error_t (*FlashGetStatus)(FlashStatus *status);


/**
 * @brief Write Data into Flash function
 **/

typedef error_t (*FlashWrite)(uint32_t address, uint8_t* data, size_t length);


/**
 * @brief Read Data from Flash function
 **/

typedef error_t (*FlashRead)(uint32_t address, uint8_t* data, size_t length);


/**
 * @brief Erase Data from Flash function
 **/

typedef error_t (*FlashErase)(uint32_t address, size_t length);


/**
 * @brief Swap Flash Banks function
 **/

typedef error_t (*FlashSwapBanks)(void);

/**
 * @brief Get address of the neighbouring sector
 **/

typedef error_t (*FlashGetNextSector) (uint32_t address, uint32_t *sectorAddr);

/**
 * @brief Determine if a given address match the start address of a sector
 **/

typedef bool_t (*FlashIsSectorAddr) (uint32_t address);


/**
 * @brief Flash Driver definition
 **/

typedef struct
{
   FlashInit init;                        ///<Flash Driver init callback function
   FlashGetInfo getInfo;                  ///<Flash Driver get information callback function
   FlashGetStatus getStatus;              ///<Flash Driver get status callback function
   FlashWrite write;                      ///<Flash Driver write data callback function
   FlashRead read;                        ///<Flash Driver read data callback function
   FlashErase erase;                      ///<Flash Driver erase data callback function
   FlashSwapBanks swapBanks;              ///<Flash Driver swap banks callback function
   FlashGetNextSector getNextSectorAddr;  ///<Flash Driver get address of the neighbouring sector callback function
   FlashIsSectorAddr isSectorAddr;        ///<Flash Driver determine is address matches a sector address callback function
} FlashDriver;


/**
 * @brief Flash Description definition
 **/

typedef struct
{
   const FlashDriver *driver;             ///<Pointer to the flash driver
   SlotDesc slots[FLASH_SLOTS_NUMBER];    ///<List of flash slots
} FlashDesc;


/**
 * @brief Flash definition
 **/

typedef struct
{
   FlashInfo info;   ///<Flash memory information
   FlashDesc desc;   ///<Flash memory descriptor
} Flash;


#endif //!_FLASH_H

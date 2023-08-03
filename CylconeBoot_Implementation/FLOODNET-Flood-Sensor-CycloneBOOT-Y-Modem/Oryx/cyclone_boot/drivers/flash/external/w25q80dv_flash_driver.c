/**
 * @file w25q80dv_template.c
 * @brief CycloneBOOT Memory Driver Template
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

//Switch to the appropriate trace level
#define TRACE_LEVEL IAP_TRACE_LEVEL

//Dependencies
#include "ExtFlash.h"
#include "core/flash.h"
#include "drivers/flash/external/w25q80dv_flash_driver.h"
#include "debug.h"


//Memory driver private related functions
error_t w25q80dvFlashDriverInit(void);
error_t w25q80dvFlashDriverGetInfo(const FlashInfo **info);
error_t w25q80dvFlashDriverGetStatus(FlashStatus *status);
error_t w25q80dvFlashDriverWrite(uint32_t address, uint8_t* data, size_t length);
error_t w25q80dvFlashDriverRead(uint32_t address, uint8_t* data, size_t length);
error_t w25q80dvFlashDriverErase(uint32_t address, size_t length);
bool_t w25q80dvFlashDriverIsSectorAddr(uint32_t address);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Memory Information
 **/

const FlashInfo w25q80dvFlashDriverInfo =
{
   FLASH_DRIVER_VERSION,
   W25Q80DV_NAME,
   FLASH_TYPE_EXTERNAL_QSPI,
   //MEM_CLASS_FLASH,
   W25Q80DV_ADDR,
   W25Q80DV_SIZE,
   W25Q80DV_WRITE_SIZE,
   W25Q80DV_READ_SIZE,
   0,
   0,
   0,
   0,
   0
};

/**
 * @brief Memory Driver
 **/

const FlashDriver w25q80dvFlashDriver =
{
   w25q80dvFlashDriverInit,
   w25q80dvFlashDriverGetInfo,
   w25q80dvFlashDriverGetStatus,
   w25q80dvFlashDriverWrite,
   w25q80dvFlashDriverRead,
   w25q80dvFlashDriverErase,
   NULL,
   NULL,
   w25q80dvFlashDriverIsSectorAddr
};


/**
 * @brief Initialize Flash Memory.
 * @return Error code
 **/

error_t w25q80dvFlashDriverInit(void)
{
	bool_t status;

   //Debug message
   TRACE_INFO("Initializing %s memory...\r\n", W25Q80DV_NAME);

   status = Flash__Init();
   if(!status)
   {
      TRACE_ERROR("Failed to initialize SPI External Flash!\r\n");
      return ERROR_FAILURE;
   }

   //Successfull process
   return NO_ERROR;
}


/**
 * @brief Get Flash Memory information.
 * @param[in,out] info Pointeur to the Memory information structure to be returned
 * @return Error code
 **/

error_t w25q80dvFlashDriverGetInfo(const FlashInfo **info)
{
   //Set Memory information pointeur
   *info = (const FlashInfo*) &w25q80dvFlashDriverInfo;

   //Successfull process
   return NO_ERROR;
}


/**
 * @brief Get Flash Memory status.
 * @param[in,out] status Pointeur to the Memory status to be returned
 * @return Error code
 **/

error_t w25q80dvFlashDriverGetStatus(FlashStatus *status)
{
   uint16_t statusReg;

   //Check parameter vailidity
   if(status == NULL)
      return ERROR_INVALID_PARAMETER;

   //TODO: Get SPI Flash Memory error flags status

   //Read w25q80dv status register 1 & 2
   statusReg = Flash__ReadDeviceStatus();

   if(statusReg & STATUS_REG_BUSY)
   {
	   //Set Flash memory status
	   *status = FLASH_STATUS_BUSY;
   }
   else
   {
	   //Set Flash memory status
	   *status = FLASH_STATUS_OK;
   }

   //Successfull process
   return NO_ERROR;
}


/**
 * @brief Write data in Flash Memory at the given address.
 * @param[in] address Address in Flash Memory to write to
 * @param[in] data Pointeur to the data to write
 * @param[in] length Number of data bytes to write in
 * @return Error code
 **/

error_t w25q80dvFlashDriverWrite(uint32_t address, uint8_t* data, size_t length)
{
   uint32_t topAddress;
   const uint8_t *p;
   uint8_t word[4];
   size_t n;

   //Precompute the top address
   topAddress = W25Q80DV_ADDR + W25Q80DV_SIZE;

   //Check address validity
   if((address < W25Q80DV_ADDR || address >= topAddress) ||
      (address % sizeof(uint32_t) != 0))
      return ERROR_INVALID_PARAMETER;

   //Check parameters validity (is data in flash)
   if(data == NULL || address + length > topAddress)
      return ERROR_INVALID_PARAMETER;

   //Cast data pointer
   p = (const uint8_t*) data;

   //Perform write operation
   while(length > 0)
   {
      //Prevent to write more than 4 bytes at a time
      n = MIN(sizeof(word), length);

      //Check if remaining bytes is less than 4 (32bits word)
      if(n < sizeof(uint32_t))
         memset(word, 0, sizeof(word));

      //Copy n bytes
      memcpy(word, p, n);

      //Is address match sector start address?
      if(address % W25Q80DV_SUBSECTORS_SIZE == 0)
      {
         //Erases the specified block
    	 Flash__SectorErase4k(address);
      }

      //Program 32-bit word in flash memory
      Flash__PageProgram(address, word, sizeof(uint32_t));

      //Advance data pointer
      p += n;
      //Increment word address
      address += n;
      //Remaining bytes to be written
      length -= n;
   }

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Read data from Memory at the given address.
 * @param[in] address Address in Memory to read from
 * @param[in] data Buffer to store read data
 * @param[in] length Number of data bytes to read out
 * @return Error code
 **/

error_t w25q80dvFlashDriverRead(uint32_t address, uint8_t* data, size_t length)
{
   uint32_t topAddress;

   //Precompute the top address
   topAddress = W25Q80DV_ADDR + W25Q80DV_SIZE;

   //Check address validity
   if(address < W25Q80DV_ADDR || address >= topAddress)
      return ERROR_INVALID_PARAMETER;

   //Check parameters validity (is data in flash)
   if(data == NULL || address + length > topAddress)
      return ERROR_INVALID_PARAMETER;

   //Perform read operation
   Flash__ReadBuffer(address, data, length);

   //Successfull process
   return NO_ERROR;
}

/**
 * @brief Erase data from Memory at the given address.
 * The erase operation will be done sector by sector according to
 * the given memory address and size.
 * @param[in] address Memory start erase address
 * @param[in] length Number of data bytes to be erased
 * @return Error code
 **/

error_t w25q80dvFlashDriverErase(uint32_t address, size_t length)
{
   uint32_t topAddress;

   //Precompute the top address
   topAddress = W25Q80DV_ADDR + W25Q80DV_SIZE;

   //Check address validity
   if(address < W25Q80DV_ADDR || address >= topAddress)
      return ERROR_INVALID_PARAMETER;

   //Check parameters validity (is data in flash)
   if(address + length > topAddress)
      return ERROR_INVALID_PARAMETER;

   //Be sure address match a memory flash subsector start address
   if(address % W25Q80DV_SUBSECTORS_SIZE != 0)
   {
      length += address % W25Q80DV_SUBSECTORS_SIZE;
      address -= address % W25Q80DV_SUBSECTORS_SIZE;
   }

   //Perform erase operation
   while(length > 0)
   {
      //Erases the specified block
	  Flash__SectorErase4k(address);

      //Increment word address
      address += W25Q80DV_SUBSECTORS_SIZE;
      //Remaining bytes to be erased
      length -= MIN(length, W25Q80DV_SUBSECTORS_SIZE);
   }

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Determine if a given address match a sector tart address
 * @return boolean
 **/

bool_t w25q80dvFlashDriverIsSectorAddr(uint32_t address)
{
   //Is given address match a sector start address?
   if((address % W25Q80DV_SUBSECTORS_SIZE) == 0)
      return TRUE;
   else
      return FALSE;
}

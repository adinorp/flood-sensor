/**
 * @file memory_driver_template.c
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
#define TRACE_LEVEL 2

//Dependencies
#include "stm32wlxx.h"
#include "stm32wlxx_hal.h"
#include "core/flash.h"
#include "drivers/flash/internal/stm32wlxx_flash_driver.h"
#include "debug.h"

//Sector list size
#define SECTORS_LIST_LEN 1

/**
 * @brief Sector group description
 **/

typedef struct
{
   uint32_t addr;
   uint32_t size;
   uint32_t nb;
} SectorsGroup;

//Internal flash memory sectors list
static const SectorsGroup sectorsList[SECTORS_LIST_LEN] = {
    {STM32WLxx_FLASH_ADDR, STM32WLxx_FLASH_SECTOR_SIZE, STM32WLxx_FLASH_SECTOR_NUMBER}
};

//Memory driver private related functions
error_t stm32wlxxFlashDriverInit(void);
error_t stm32wlxxFlashDriverGetInfo(const FlashInfo **info);
error_t stm32wlxxFlashDriverGetStatus(FlashStatus *status);
error_t stm32wlxxFlashDriverWrite(uint32_t address, uint8_t* data, size_t length);
error_t stm32wlxxFlashDriverRead(uint32_t address, uint8_t* data, size_t length);
error_t stm32wlxxFlashDriverErase(uint32_t address, size_t length);
error_t stm32wlxxFlashDriverGetNextSector(uint32_t address, uint32_t *sectorAddr);
bool_t stm32wlxxFlashDriverIsSectorAddr(uint32_t address);
error_t stm32wlxxFlashDriverWriteWord(uint32_t address, uint32_t word);
int_t stm32wlxxFlashGetSector(uint32_t address);
error_t stm32wlxxFlashDriverEraseSector(uint32_t bankID, uint32_t firstSector, size_t nbSectors);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Memory Information
 **/

const FlashInfo stm32wlxxFlashDriverInfo =
{
   FLASH_DRIVER_VERSION,
   STM32WLxx_FLASH_NAME,
   FLASH_TYPE_INTERNAL,
   //MEM_CLASS_FLASH,
   STM32WLxx_FLASH_ADDR,
   STM32WLxx_FLASH_SIZE,
   STM32WLxx_FLASH_WRITE_SIZE,
   STM32WLxx_FLASH_READ_SIZE,
   0,
   0,
   0,
   0
};

/**
 * @brief stm32wlxx Flash driver
 **/

const FlashDriver stm32wlxxFlashDriver =
{
   stm32wlxxFlashDriverInit,
   stm32wlxxFlashDriverGetInfo,
   stm32wlxxFlashDriverGetStatus,
   stm32wlxxFlashDriverWrite,
   stm32wlxxFlashDriverRead,
   stm32wlxxFlashDriverErase,
   NULL,
   stm32wlxxFlashDriverGetNextSector,
   stm32wlxxFlashDriverIsSectorAddr
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief Initialize Flash Memory.
 * @return Error code
 **/

error_t stm32wlxxFlashDriverInit(void)
{
   //Debug message
   TRACE_INFO("Initializing %s memory...\r\n", STM32WLxx_FLASH_NAME);

   //Wait for last flash operation on flash
   FLASH_WaitForLastOperation(50);
   //Clear all flash error flags
   __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

   //Successfull process
   return NO_ERROR;
}


/**
 * @brief Get Flash Memory information.
 * @param[in,out] info Pointeur to the Memory information structure to be returned
 * @return Error code
 **/

error_t stm32wlxxFlashDriverGetInfo(const FlashInfo **info)
{
   //Set Memory information pointeur
   *info = (const FlashInfo*) &stm32wlxxFlashDriverInfo;

   //Successfull process
   return NO_ERROR;
}


/**
 * @brief Get Flash Memory status.
 * @param[in,out] status Pointeur to the Memory status to be returned
 * @return Error code
 **/

error_t stm32wlxxFlashDriverGetStatus(FlashStatus *status)
{
   uint32_t flag;

   //Check parameter vailidity
   if(status == NULL)
      return ERROR_INVALID_PARAMETER;

   do
   {
      //Get Flash Memory error flags status
      flag = __HAL_FLASH_GET_FLAG(FLASH_FLAG_ALL_ERRORS);
      //Is any error flag set?
      if(flag != RESET)
      {
         //Set Flash memory status
         *status = FLASH_STATUS_ERR;
         break;
      }

      //Get Flash Memory busy flags
      flag = __HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY);
      //Is busy flag set?
      if(flag != RESET)
      {
         //Set Flash memory status
         *status = FLASH_STATUS_BUSY;
         break;
      }

      //Set Flash memory status
      *status = FLASH_STATUS_OK;
   }while(0);

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

error_t stm32wlxxFlashDriverWrite(uint32_t address, uint8_t* data, size_t length)
{
   error_t error;
   uint32_t topAddress;
   const uint8_t *p;
   uint8_t word[STM32WLxx_FLASH_WRITE_SIZE];
   size_t n;

   //Precompute the top address
   topAddress = STM32WLxx_FLASH_ADDR + STM32WLxx_FLASH_SIZE;

   //Check address validity
   if((address < STM32WLxx_FLASH_ADDR || address >= topAddress) ||
      (address % sizeof(uint32_t) != 0))
      return ERROR_INVALID_PARAMETER;

   //Check parameters validity (is data in flash)
   if(data == NULL || address + length > topAddress)
      return ERROR_INVALID_PARAMETER;

   //Debug message
   TRACE_INFO("Writing data (%d bytes) at 0x%08X\r\n", length, address);
   TRACE_DEBUG_ARRAY("WRITE DATA: ", data, length);


   //Cast data pointer
   p = (const uint8_t*) data;

   //Perform write operation
   while(length > 0)
   {
      //Prevent to write more than allowed flash write bytes at a time
      n = MIN(sizeof(word), length);

      //Check if remaining bytes is less than required flash write size
      if(n < sizeof(word))
         memset(word, 0, sizeof(word));

      //Copy n bytes
      memcpy(word, p, n);

      //Program 32-bit word in flash memory
      error = stm32wlxxFlashDriverWriteWord(address, (uint32_t)word);
      if(error)
      {
         TRACE_ERROR("Failed to write in flash memory!\r\n");
         return error;
      }

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

error_t stm32wlxxFlashDriverRead(uint32_t address, uint8_t* data, size_t length)
{
   uint_t i;
   uint32_t topAddress;

   //Precompute the top address
   topAddress = STM32WLxx_FLASH_ADDR + STM32WLxx_FLASH_SIZE;

   //Check address validity
   if(address < STM32WLxx_FLASH_ADDR || address >= topAddress)
      return ERROR_INVALID_PARAMETER;

   //Check parameters validity (is data in flash)
   if(data == NULL || address + length > topAddress)
      return ERROR_INVALID_PARAMETER;

   //Perform read operation
   for(i = 0; i < length; i++)
   {
      *((uint8_t *)data + i) = *(uint8_t*)address;
      address++;
   }

   //Successfull process
   return NO_ERROR;
}

/**
 * @brief Erase data from Memory at the given address.
 * @param[in] address Address in Memory to start erasing from
 * @param[in] length Number of data bytes to be erased
 * @return Error code
 **/
error_t stm32wlxxFlashDriverErase(uint32_t address, size_t length)
{
   error_t error;
   uint32_t topAddress;
   int_t firstSectorNumber;
   uint32_t lastSectorAddr;
   int_t lastSectorNumber;

   error = NO_ERROR;

   //Precompute the top address
   topAddress = STM32WLxx_FLASH_ADDR + STM32WLxx_FLASH_SIZE;

   //Check address validity
   if((address < STM32WLxx_FLASH_ADDR || address >= topAddress) ||
      (address % sizeof(uint32_t) != 0))
      return ERROR_INVALID_PARAMETER;

   //Check parameters validity (is data in flash)
   if((length == 0) || (address + length > topAddress))
      return ERROR_INVALID_PARAMETER;

   //Get the number of the first sector to erase
   firstSectorNumber = stm32wlxxFlashGetSector(address);

   if(address + length == topAddress)
   {
      //Set last sector number as the flash sector total number
      lastSectorNumber = STM32WLxx_FLASH_SECTOR_NUMBER;
   }
   else
   {
      //Get the address of the boundary sector (not to be erased)
      error = stm32wlxxFlashDriverGetNextSector(address+length, &lastSectorAddr);
      //Is any error?
      if(error)
         return error;

      //The last sector to erase is the last flash bank 1 sector
      lastSectorNumber = stm32wlxxFlashGetSector(lastSectorAddr);
   }

   //Erase sectors of the flash bank 1 (the only one flash bank)
   error = stm32wlxxFlashDriverEraseSector(STM32WLxx_FLASH_BANK1_ID, firstSectorNumber, lastSectorNumber-firstSectorNumber);
   //Is any error?
   if(error)
      return error;

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Get address of the neighbouring sector
 * @return Error code
 **/

error_t stm32wlxxFlashDriverGetNextSector(uint32_t address, uint32_t *sectorAddr)
{
   uint_t i;
   uint_t j;
   SectorsGroup *sg;
   uint32_t sAddr = 0xFFFFFFFF;
   uint32_t lastSectorAddr;

   lastSectorAddr = sectorsList[SECTORS_LIST_LEN-1].addr +
      (sectorsList[SECTORS_LIST_LEN-1].size * (sectorsList[SECTORS_LIST_LEN-1].nb - 1));

   //Check parameters validity
   if(address < STM32WLxx_FLASH_ADDR || address > lastSectorAddr || sectorAddr == NULL)
      return ERROR_INVALID_PARAMETER;

   //Loop through sectors list
   for(i = 0; i < SECTORS_LIST_LEN && sAddr == 0xFFFFFFFF; i++)
   {
      //Point to the current sectors group
      sg = (SectorsGroup *) &sectorsList[i];

      //Is address in current sector group
      if(address <= sg->addr + sg->size*sg->nb)
      {
         //Loop through sectors group list
         for(j = 0; j < sg->nb; j++)
         {
            //Is address located in current sector?
            if(address <= sg->addr + j*sg->size)
            {
               //Set next sector address
               sAddr = sg->addr + j*sg->size;
               break;
            }
         }
      }
   }

   //Save next sector addr
   *sectorAddr = sAddr;

   //Succesfull process
   return NO_ERROR;
}


/**
 * @brief Determine if a given address is contained within a sector
 * @return boolean
 **/

bool_t stm32wlxxFlashDriverIsSectorAddr(uint32_t address)
{
   int_t sector;

   //Get Flash memory sector number
   sector = stm32wlxxFlashGetSector(address);

   //Is given address match a sector start address?
   if(sector >= 0)
      return TRUE;
   else
      return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief Erase given number of sector from Flash memory starting from the given index sector.
 * @param[in] firstSector Index of the first Flash memory sector to be erased
 * @param[in] nbSectors Number of Flash memory sector to be erased
 * @return Error code
 **/

error_t stm32wlxxFlashDriverEraseSector(uint32_t bankID, uint32_t firstSector, size_t nbSectors)
{
   HAL_StatusTypeDef status;
   FLASH_EraseInitTypeDef EraseInitStruct;
   uint32_t sectorError;

   //Check parameter validity
   if((firstSector >= STM32WLxx_FLASH_SECTOR_NUMBER) || (nbSectors == 0) ||
      ((firstSector + nbSectors - 1) >= STM32WLxx_FLASH_SECTOR_NUMBER) ||
      (bankID != STM32WLxx_FLASH_BANK1_ID))
      return ERROR_INVALID_PARAMETER;

   //Debug message
   TRACE_DEBUG("Erasing Flash sector(s) %" PRIu32 "through %" PRIu32 "...\r\n", firstSectorNumber, lastSectorNumber);

   //Start of exception handling block
   do
   {
      //Allow access to Flash control registers and user False
      status = HAL_FLASH_Unlock();
      //Is any error?
      if (status != HAL_OK)
      {
         //Debug message
         TRACE_ERROR("Flash Control Register unlock failed!\r\n");
         break;
      }

      //Set flash erase settings
      EraseInitStruct.TypeErase    = FLASH_TYPEERASE_PAGES;
      EraseInitStruct.Page       = firstSector;
      EraseInitStruct.NbPages    = nbSectors;

      //Wait for the last flash operation
      FLASH_WaitForLastOperation((uint32_t)5000U);

      //Erase the specified Flash sector(s)
      status = HAL_FLASHEx_Erase(&EraseInitStruct, &sectorError);

      //Is any error?
      if(status != HAL_OK)
      {
         //Debug message
         TRACE_ERROR("Failed to erase flash sector(s) %ld, error = 0x%08lX!\r\n", firstSector, sectorError);
      }

      //Disable the Flash option control register access (recommended to protect
      //the option Bytes against possible unwanted operations)
      if(HAL_FLASH_Lock() != HAL_OK)
      {
         //Debug message
         TRACE_ERROR("Flash Control Register lock failed!\r\n");
         break;
      }
   }while(0);

   //Return status code
   return (status == HAL_OK) ? NO_ERROR : ERROR_WRITE_FAILED;
}


/**
 * @brief Write 32-bits word in Flash Memory at the given address.
 * @param[in] address Address in Flash Memory to write to
 * @param[in] word 32-bit word to write in Flash memory
 * @return Error code
 **/

error_t stm32wlxxFlashDriverWriteWord(uint32_t address, uint32_t word)
{
   int_t flashSector;
   uint32_t sectorError;
   uint32_t topAddress;
   HAL_StatusTypeDef status;
   FLASH_EraseInitTypeDef EraseInitStruct;

   //Precompute the top address
   topAddress = STM32WLxx_FLASH_ADDR + STM32WLxx_FLASH_SIZE;

   //Check parameters validity (is data in flash)
   if((address + sizeof(uint32_t) >= topAddress) ||
      (address % sizeof(uint32_t) != 0))
      return ERROR_INVALID_PARAMETER;

   //Unlock FLASH
   HAL_FLASH_Unlock();

   do
   {
      //Get flash sector number according to the given wirte address
      // (-1 if it doesn't match a flash sector start address)
      flashSector = stm32wlxxFlashGetSector(address);

      //Is write address match a flash sector start address?
      if(flashSector >= 0)
      {
         //Set flash erase settings
         EraseInitStruct.TypeErase    = FLASH_TYPEERASE_PAGES;
         EraseInitStruct.Page       = flashSector;
         EraseInitStruct.NbPages    = 1;

         //Wait for the last flash operation
         FLASH_WaitForLastOperation((uint32_t)5000U);

         //Erase the sector
         status = HAL_FLASHEx_Erase(&EraseInitStruct, &sectorError);
         if(status != HAL_OK)
         {
            //Debug message
            TRACE_ERROR("Flash erase failed!\r\n");
            break;
         }
      }

      TRACE_INFO("Write data in flash at 0x%08X:\r\n", address);
      TRACE_INFO_ARRAY("data: ", (uint8_t*)word, 8);
      TRACE_INFO("\r\n");

      //Write word (64bits) into flash
      // Becareful !!!
      // - If FLASH_TYPEPROGRAM_DOUBLEWORD type program -> Data parameter MUST be the 64bits data value
      // - If FLASH_TYPEPROGRAM_FAST type program -> Data parameter MUST be the the address of data
      status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, *((uint64_t*)word));
      if(status != HAL_OK)
      {
         //Debug message
         TRACE_ERROR("Flash program failed!\r\n");
         break;
      }
   }while(0);

   //Lock FLASH
   HAL_FLASH_Lock();

   //Return error code
   return (status != HAL_OK)? ERROR_FAILURE : NO_ERROR;
}


/**
 * @brief Get the Memory Flash sector number according to the given address.
 * @param[in] address Given Flash Memory address
 * @return Sector number or -1
 **/

int_t stm32wlxxFlashGetSector(uint32_t address)
{
    uint_t i;
    uint_t j;
    int_t sector;
    SectorsGroup* sGroup;

    //Initialize sector number
    sector = -1;

    //Loop through flash sector group list
    for(i = 0; i < SECTORS_LIST_LEN; i++)
    {
        //Point to the current sector group
        sGroup = (SectorsGroup*) &sectorsList[i];

        //Loop through sector group sectors list
        for(j = 0; j < sGroup->nb; j++)
        {
            //Is current sector address matches given address?
            if(sGroup->addr + sGroup->size*j == address)
            {
                sector = j;
                return sector;
            }
        }
    }

    return sector;
}

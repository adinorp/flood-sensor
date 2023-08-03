/**
 * @file slot.c
 * @brief Slot Memory managment
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

//Dependencies
#include "slot.h"
#include "core/flash.h"
#include "error.h"

/**
 * @brief Return TRUE if the given slots overlap, FALSE otherwise.
 * Slots overlap if they belong to the same memory and they share at least one byte.
 * @param[in,out] addrSlot1 Slot 1 address
 * @param[in,out] sizeSlot1 Slot 1 size
 * @param[in,out] addrSlot2 Slot 2 address
 * @param[in,out] sizeSlot2 Slot 2 size
 * @return TRUE or FALSE
 **/

bool_t isSlotsOverlap(uint32_t addrSlot1, size_t sizeSlot1, uint32_t addrSlot2, size_t sizeSlot2)
{
   //Slots overlap?
   if((addrSlot1 >= addrSlot2 && addrSlot1 < addrSlot2 + sizeSlot2) ||
      (addrSlot2 >= addrSlot1 && addrSlot2 < addrSlot1 + sizeSlot1))
      return TRUE;
   else
      return FALSE;
}


/**
 * @brief Return TRUE if the given slot is located in flash memory bank 2, FALSE otherwise.
 * @param[in] slot Pointer to the slot descriptor
 * @return TRUE or FALSE
 **/

bool_t isSlotInBank2(SlotDesc *slot)
{
   error_t error;
   uint32_t topAddress;
   const FlashInfo *info;
   FlashDesc *flash;
   bool_t res;

   //Initialize result
   res = FALSE;

   //Check slot isn't null
   if(slot != NULL)
   {
      //Point to slot memory
      flash = (FlashDesc*)slot->flash;
      //Get memory informations
      error = flash->driver->getInfo(&info);
      //Check there is no error
      if(!error)
      {
         //Is slot memory support dual bank?
         if(info->dualBank)
         {
            //Compute memory bank 2 top address
            topAddress = info->bank2Addr + info->bankSize;

            //Is slot located in bank 2?
            if(slot->addr >= info->bank2Addr && slot->addr+slot->size <= topAddress)
            {
               //Slot is located in bank 2
               res = TRUE;
            }
         }
      }
   }

   //Return result
   return res;
}


/**
 * @brief Return TRUE if the given slot is located in external flash memory, FALSE otherwise.
 * @param[in] slot Pointer to the slot descriptor
 * @return TRUE or FALSE
 **/

bool_t isSlotInExtMem(SlotDesc *slot)
{
   error_t error;
   const FlashInfo *info;
   FlashDesc *flash;
   bool_t res;

   //Initialize result
   res = FALSE;

   //Check slot isn't null
   if(slot != NULL)
   {
      //Point to slot memory
      flash = (FlashDesc*)slot->flash;
      //Get memory informations
      error = flash->driver->getInfo(&info);
      //Check there is no error
      if(!error)
      {
         //Is slot memory type not internal?
         if(info->flashType != FLASH_TYPE_INTERNAL)
         {
            //Slot is located in external flash memory
            res = TRUE;
         }
      }
   }

   //Return result
   return res;
}


/**
 * @brief Read data bytes from the given slot.
 * @param[in] slot Pointer to the slot to be read
 * @param[in,out] buffer Pointer to the buffer that will old read data
 * @param[in] length Number of bytes to be read
 * @return Status code
 **/

error_t slotRead(SlotDesc *slot, uint32_t offset, uint8_t *buffer, size_t length)
{
   error_t error;
   const FlashDriver *flashDriver;
   uint32_t readAddr;
   uint32_t topAddress;

   //Compute slot read address
   readAddr = slot->addr + offset;
   //Compute slot top address
   topAddress = slot->addr + slot->size;

   //Check parameter validity
   if(slot == NULL || buffer == NULL || length == 0 ||
      (readAddr >= topAddress) ||
      (readAddr + length > topAddress))
      return ERROR_INVALID_PARAMETER;

   //Get memory driver
   flashDriver = ((FlashDesc*)slot->flash)->driver;

   //Read slot memory
   error = flashDriver->read(readAddr, buffer, length);
   //Is any error?
   if(error)
      return error;

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Erase data of the given slot.
 * @param[in,out] buffer Pointer to the slot to be erase
 * @return Status code
 **/

error_t slotErase(SlotDesc *slot)
{
   error_t error;
   uint_t i;
   const FlashDriver *flashDriver;
   uint8_t zeroWord[4];
   uint32_t addr;

   //Check paramter validity
   if(slot == NULL)
      return ERROR_INVALID_PARAMETER;

   //Get memory driver
   flashDriver = ((FlashDesc*)slot->flash)->driver;

   //Initaliaze zero wrod array
   memset(zeroWord, 0, sizeof(zeroWord));

   //Set address to slot start address
   addr = slot->addr;

   //Write zero words into slot
   for(i = 0; i < slot->size/sizeof(uint32_t); i++)
   {
      //Read slot memory
      error = flashDriver->write(addr, zeroWord, sizeof(zeroWord));
      //Is any error?
      if(error)
         return error;

      //Increment address
      addr += sizeof(uint32_t);
   }

   //Successful process
   return NO_ERROR;
}

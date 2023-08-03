/**
 * @file boot_fallback.c
 * @brief CycloneBOOT Bootloader fallback managment
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
#define TRACE_LEVEL BOOT_TRACE_LEVEL

//Dependencies
#include "core/slot.h"
#include "core/image.h"
#include "bootloader/boot.h"
#include "bootloader/boot_common.h"
#include "boot_fallback.h"
#include "debug.h"

//CycloneBOOT Bootloader fallback private related functions
error_t fallbackFindSlotWithEquivImg(BootContext * context, SlotDesc **slotEquivImg);
error_t fallbackCompareSlots(SlotDesc *slot1, SlotDesc *slot2, int8_t *res);
error_t fallbackDeleteSlot(SlotDesc *slot);
error_t fallbackRestoreBackupSlot(BootContext *context, SlotDesc *slot);
error_t fallbackTriggerInit(void) __attribute__((weak));
error_t fallbackTriggerGetStatus(TriggerStatus *status) __attribute__((weak));




/**
 * @brief Fallback Task routine
 * @param[in] context Pointer to the Bootloader context
 * @return Status Code
 **/

error_t fallbackTask(BootContext *context)
{
   error_t error;
   SlotDesc *slotEquivImg;
   SlotDesc *slotBackupImg;
   int8_t res;

   //Initialize variables
   error = NO_ERROR;
   slotEquivImg = NULL;
   slotBackupImg = NULL;

   //Beginning of handling block
   do
   {
      //Check current app image in (internal flash slot)
      error = bootCheckImage(&context->primaryFlash.slots[0]);
      //Is any error?
      if(error)
         break;

      //Check external app image 1 (in external flash slot 1)
      error = bootCheckImage(&context->secondaryFlash.slots[0]);
      //Is any error?
      if(error)
         break;

      //Check external app image 2 (in eternal flash slot 2)
      error = bootCheckImage(&context->secondaryFlash.slots[1]);
      //Is any error?
      if(error)
         break;

      //Find image in external flash that is equivalent to the current app image in internal flash
      error = fallbackFindSlotWithEquivImg(context, &slotEquivImg);
      //If any error or slot with equivalent image not found?
      if(error || slotEquivImg == NULL)
      {
         error = ERROR_ABORTED;
         break;
      }

      //Check that the other external image (in the other external flash slot) has an index inferior ot the current image in internal flash
      //If it is not the case then goto error state

      //Select remaining slot that should contains the backup image of the previous valid application
      if(slotEquivImg == &context->secondaryFlash.slots[0])
         slotBackupImg = &context->secondaryFlash.slots[1];
      else
         slotBackupImg = &context->secondaryFlash.slots[0];

      //Check that the remaining slot (containing the backup image) hold an image older that the current
      //the current image in primary flash slot. If it is not the case then there is no backup image in external
      //flash memory.
      error = fallbackCompareSlots(slotBackupImg, &context->primaryFlash.slots[0], &res);
      if(error || res >= 0)
      {
         error = ERROR_ABORTED;
         break;
      }

      //Delete the external image equivalent of the current app image
      error = fallbackDeleteSlot(slotEquivImg);
      //Is any error?
      if(error)
         break;

      //Restore the remaining image in external memory slot (backup of the previous valid app)
      error = fallbackRestoreBackupSlot(context, slotBackupImg);
      //Is any error?
      if(error)
         break;

      //Reset device
      mcuSystemReset();
   }while(0);

   //Return status code
   return error;
}


/**
 * @brief Delete the given slot. In other words it erase the content of the given slot.
 * @param[in] slot Pointer to the slot to be deleted.
 * @return Error code.
 **/

error_t fallbackDeleteSlot(SlotDesc *slot)
{
   const FlashDriver *flashDrv;

   //Point to the slot flash driver
   flashDrv = ((FlashDesc*)slot->flash)->driver;

   //Erase slot data
   return flashDrv->erase(slot->addr, slot->size);
}


/**
 * @brief Restore the image contained in the backup slot.
 * It will extract the firmware application from the image inside the backup slot.
 * Then a new image that old the back application firmware will be generated in internal memory slot.
 * It will allow the system to boot to the backup application firmware.
 * @param[in] slot Pointer to the slot to be deleted.
 * @return Error code.
 **/

error_t fallbackRestoreBackupSlot(BootContext *context, SlotDesc *slot)
{
   //Restore the application firmware backup by updating the system using
   //the slot containing the backup image that hold the application firmware backup.
   return bootUpdateApp(context, slot);
}


/**
 * @brief Compare two given slots together with respect to the index
 * of the images inside the slots.
 * - If the image index of the first slot (slot1) is strictly inferior
 *   to the image index of the first slot (slot1) then result will be -1.
 * - If the image index of the first slot (slot1) is equal
 *   to the image index of the first slot (slot1) then result will be 0.
 * - Otherwise the result will be 1.
 * @param[in] slot1 Pointer to the first slot to be compared with.
 * @param[in] slot2 Pointer to the second slot to be compared with.
 * @param[ou] res Result of the slot comparison.
 * @return Error code.
 **/

error_t fallbackCompareSlots(SlotDesc *slot1, SlotDesc *slot2, int8_t *res)
{
   error_t error;
   uint32_t saveImgIdx;
   ImageHeader imgHeader;

   //Initialize status code
   error = NO_ERROR;

   //Check paramters validity
   if(slot1 == NULL || slot2 == NULL || res == NULL)
      return ERROR_INVALID_PARAMETER;

   //Get image header from the first slot.
   error = bootGetSlotImgHeader(slot1, &imgHeader);
   //Check there is no error
   if(!error)
   {
      //Save index of the image inside the first slot for
      // later comparison.
      saveImgIdx = imgHeader.imgIndex;

      //Get image header from the second slot.
      error = bootGetSlotImgHeader(slot2, &imgHeader);
      //Check there is no error
      if(!error)
      {
         //Is image index from the first slot strictly
         // inferior than the image index from the second slot?
         if(saveImgIdx < imgHeader.imgIndex)
            *res = -1;
         //Is image index from the first slot equal the image index from the second slot?
         else if(saveImgIdx == imgHeader.imgIndex)
            *res = 0;
         //Is image index from the first slot strictly
         // isuperior than the image index from the second slot?
         else
            *res = 1;
      }
   }

   //Return state code
   return error;
}


/**
 * @brief Search for the slot in external memory that contains the image equivalent
 * of the current image in internal flash slot. "Equivalent" means that the image to
 * be found will have the same index than the current image in internal flash.
 * @param[in] context Pointer to bootloader context.
 * @param[out] slotEquivImg Pointer to the slot that holding the equivalent image.
 * @return Error code.
 **/

error_t fallbackFindSlotWithEquivImg(BootContext *context, SlotDesc **slotEquivImg)
{
   error_t error;
   uint_t i;
   uint32_t currImgIdx;
   ImageHeader imgHeader;
   bool_t foundSlot;

   error = NO_ERROR;
   foundSlot = FALSE;

   //Check parameters validity
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   //Get image header from the internal flash memory slot.
   error = bootGetSlotImgHeader(&context->primaryFlash.slots[0], &imgHeader);
   //Check there is no error
   if(!error)
   {
      //Save index of the current image in internal flash
      currImgIdx = imgHeader.imgIndex;

      //Loop through the external flash slot list
      for(i = 0; i < FLASH_SLOTS_NUMBER; i++)
      {
         //Get image header from the listed slot
         error = bootGetSlotImgHeader(&context->secondaryFlash.slots[i], &imgHeader);
         //Check there is no error
         if(error)
         {
            break;
         }
         else
         {
            //Is index of the current image is equal to the index of the image from the listed slot?
            if(imgHeader.imgIndex == currImgIdx)
            {
               //Equivalent slot is found.
               foundSlot = TRUE;
               //Saving equivalent slot pointer.
               *slotEquivImg = &context->secondaryFlash.slots[i];
               break;
            }
         }
      }

      //Is equivalent slot not found?
      if(!foundSlot)
      {
         //Raise an error
         error = ERROR_FAILURE;
      }
   }

   //Return status code
   return error;
}


/**
 * @brief Fallback Trigger Initialisation callback.
 * It is declared week and must be declared in user codde space.
 * @return Status Code
 **/

error_t fallbackTriggerInit(void)
{
   //This function Should not be modified, when the callback is needed,
   //       the fallbackTriggerInit must be implemented in the user file

   return ERROR_NOT_IMPLEMENTED;
}


/**
 * @brief Fallback Trigger Status callback.
 * It is declared week and must be declared in user codde space.
 * @param[in] status Trigger status to be returned (Raised or Idle)
 * @return Status Code
 **/

error_t fallbackTriggerGetStatus(TriggerStatus *status)
{
   //This function Should not be modified, when the callback is needed,
   //       the fallbackTriggerGetStatus must be implemented in the user file

   return ERROR_NOT_IMPLEMENTED;
}

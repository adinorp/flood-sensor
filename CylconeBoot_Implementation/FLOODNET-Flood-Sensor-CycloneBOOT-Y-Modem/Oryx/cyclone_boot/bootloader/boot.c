/**
 * @file boot.c
 * @brief CycloneBOOT Bootloader managment
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
#include "bootloader/boot.h"
#include "bootloader/boot_fallback.h"
#include "bootloader/boot_common.h"
#include "core/flash.h"
#include "core/image.h"
#include "core/crc32.h"
#if ((BOOT_FALLBACK_SUPPORT == DISABLED) && \
     (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED))
#include "core/mailbox.h"
#endif
#include "debug.h"

//Bootloader private related functions
error_t bootGetCipherKey(BootContext *context);
error_t bootJumpToApp(BootContext *context);


/**
* @brief Initialize bootloader settings with default values
* @param[in,out] settings Structure that contains Bootloader settings
**/

void bootGetDefaultSettings(BootSettings *settings)
{
   //Clear bootloader user settings structure
   memset(settings, 0x00, sizeof(BootSettings));

   //Flash driver settings
   settings->prmFlashDrv = NULL;
   settings->sndFlashDrv = NULL;
   //Primary flash slot settings
   settings->prmFlashSlotAddr = 0;
   settings->prmFlashSlotSize = 0;
   //Secondary flash slot 1 settings
   settings->sndFlashSlot1Addr = 0;
   settings->sndFlashSlot1Size = 0;
#if(BOOT_FALLBACK_SUPPORT == ENABLED)
   //Secondary flash slot 2 settings
   settings->sndFlashSlot2Addr = 0;
   settings->sndFlashSlot2Size = 0;
#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   //Secondary flash cipher key settings
   settings->psk = NULL;
   settings->pskSize = 0;
#endif
#endif
}


/**
 * @brief Initialize bootloader context
 * @param[in,out] context Bootloader context
 * @param[in] settings Bootloader user settings
 * @return Status code
 **/

error_t bootInit(BootContext *context, BootSettings *settings)
{
   error_t error;

   //Check parameter validity
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   //Set context fields to zero
   memset(context, 0, sizeof(BootContext));

   //Save bootloader user settings
   context->settings = *settings;

   //Initialize primary flash driver and slots
   error = bootInitPrimaryFlash(context, settings);
   //Is any error?
   if(error)
      return error;

   //Initialize secondary (external) flash driver and slots
   error = bootInitSecondaryFlash(context, settings);
   //Is any error?
   if(error)
      return error;

#if (BOOT_FALLBACK_SUPPORT == ENABLED)
#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   //Check cipher key used to decode data in secondary flash (external memory)
   if(settings->psk == NULL || (settings->pskSize > sizeof(context->psk)))
   {
      return ERROR_INVALID_PARAMETER;
   }
   else
   {
      //Store cipher key used to decode data in secondary flash (external memory)
      memcpy(context->psk, settings->psk, settings->pskSize);
      context->pskSize = settings->pskSize;
   }
#endif

   //Initialize fallback trigger
   error = fallbackTriggerInit();
   //Is any error?
   if(error)
      return error;
#endif

   //Set bootloader state
   context->state = BOOT_STATE_IDLE;

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Bootloader Task routine
 * @param[in] context Pointer to Bootloader context
 * @return None
 **/

error_t bootTask(BootContext *context)
{
   error_t error;
   static SlotDesc *selectedSlot;
   uint32_t appStartAddr;
#if (BOOT_FALLBACK_SUPPORT == ENABLED)
   TriggerStatus trigStatus;
#endif

   //Initialize bootloader error status
   error = NO_ERROR;

   //Bootloader IDLE state
   if(context->state == BOOT_STATE_IDLE)
   {
#if (BOOT_FALLBACK_SUPPORT == ENABLED)
      //Get fallback trigger status
      error = fallbackTriggerGetStatus(&trigStatus);
      //Is any error?
      if(error)
      {
         //Change bootloader state
         context->state = BOOT_STATE_ERROR;
      }
      else
      {
         //Is fallback trigger raised?
         if(trigStatus == TRIGGER_STATUS_RAISED)
         {
            //Change bootloader state
            context->state = BOOT_STATE_FALLBACK_APP;
         }
         else
         {
#else
      if(1)
      {
         if(1)
         {
#endif
            //Select update image slot
            error = bootSelectUpdateImageSlot(context, &selectedSlot);
            //Is any error?
            if(error || selectedSlot == NULL)
            {
               //Debug message
               TRACE_ERROR("No valid image found!\r\n");
               return error; //ERROR NO VALID IMAGE -> state error ????
            }
            else
            {
               //Debug message
               TRACE_INFO("Selected slot:\r\n");
               TRACE_INFO("- address:  0x%08lX\r\n", (unsigned long) selectedSlot->addr);
               TRACE_INFO("- size:     0x%08X\r\n", selectedSlot->size);

               //Is selected slot differrent from slot containing current application?
               //In other word, is selected image (in selected slot) more recent than current application image?
               if(selectedSlot != &context->primaryFlash.slots[0])
               {
                  //Change bootloader state
                  context->state = BOOT_STATE_UPDATE_APP;
               }
               else
               {
                  //Change bootloader state
                  context->state = BOOT_STATE_RUN_APP;
               }
            }
         }
      }
   }
   //Bootloader RUN APP state
   else if(context->state == BOOT_STATE_RUN_APP)
   {
      //Make sure to select first primary memory slot (contains current application)
      selectedSlot = &context->primaryFlash.slots[0];

      //Debug message
      TRACE_INFO("Checking current application image...\r\n");

      //Check current application image inside first primary memory slot
      error = bootCheckImage(selectedSlot);
      //Is any error?
      if(error)
      {
         //Change bootloader state
         context->state = BOOT_STATE_ERROR;
      }
      else
      {
         //Check reset vector of the current application
         error = bootCheckSlotAppResetVector(selectedSlot);
         //Is reset vector valid?
         if(!error)
         {
            //Debug message
            TRACE_INFO("Current application image is valid\r\n");
            TRACE_INFO("Booting to the application...\r\n");

            //Compute application start address
            appStartAddr = selectedSlot->addr + mcuGetVtorOffset();

            //Jump to current application inside primary memory slot
            mcuJumpToApplication(appStartAddr);
         }
         else
         {
            //Change bootloader state
            context->state = BOOT_STATE_ERROR;
         }
      }
   }
   //Bootloader UPDATE APP state
   else if(context->state == BOOT_STATE_UPDATE_APP)
   {
      //Debug message
      TRACE_INFO("Checking update application image...\r\n");

      //Check current application image inside first primary memory slot
      error = bootCheckImage(selectedSlot);
      //Is any error?
      if(error)
      {
         //Discard error
         error = NO_ERROR;
         //Change bootloader state
         context->state = BOOT_STATE_RUN_APP;
      }
      else
      {
#if (BOOT_FALLBACK_SUPPORT == DISABLED && \
     BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
         //Call bootGetCipherKey here
         error = bootGetCipherKey(context);
         //Is any error?
         if(error)
         {
            //Debug message
            TRACE_ERROR("Failed to retrieve cipher key!\r\n");
            //Discard error
            error = NO_ERROR;
            //Change bootloader state
            context->state = BOOT_STATE_RUN_APP;
         }
         else
#else
         if(1)
#endif
         {
            //Debug message
            TRACE_INFO("Starting update procedure...\r\n");

            //Start update procedure (could be a new application or because of a previous fallback procedure)
            error = bootUpdateApp(context, selectedSlot);
            //Is any error?
            if(error)
            {
               //Change bootloader state
               context->state = BOOT_STATE_ERROR;
            }
            else
            {
               //Debug message
               TRACE_INFO("Update procedure finished\r\n");
               TRACE_INFO("Rebooting...\r\n");

               //Reset system
               mcuSystemReset();
            }
         }
      }
   }
   //Bootloader FALLBACK APP state
   else if(context->state == BOOT_STATE_FALLBACK_APP)
   {
      //Call fallback routine here
      error = fallbackTask(context);
      //Is any error.
      if(error)
      {
         //Change bootloader state
         context->state = BOOT_STATE_RUN_APP;
      }
      //If error goto to error state
   }
   //Bootloader ERROR state
   else if(context->state == BOOT_STATE_ERROR)
   {
      //Bootloader reached error state
      //Calling user callback error
      if(0/*context->settings.bootErrorCallback != NULL*/)
      {

      }
      else
      {
         //Debug message
         TRACE_ERROR("Bootloader is in error state!\r\n");
      }
   }
   else
   {
      //For sanity
      return ERROR_INVALID_VALUE;
   }

   //Return bootloader status
   return error;
}


/**
 * @brief Get PSK cipher key used to encrypt output image in external flash memory.
 * @param[in,out] context Pointer to the bootloader context
 **/

error_t bootGetCipherKey(BootContext *context)
{
#if ((BOOT_FALLBACK_SUPPORT == DISABLED) && \
     (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED))
   error_t error;
   BootMailBox msgBox;

   //Initialize status code
   error = NO_ERROR;

   //Debug message
   TRACE_INFO("Retrieving cipher key...\r\n");

   //Begin of handling block
   do
   {
      //Get message from shared SRAM (contains PSK key)
      error = getBootMailBox(&msgBox);
      if(error)
         break;

      //Check message validity
      error = checkBootMailBox(&msgBox);
      //Is any error?
      if(error)
         break;

      //Check cipher key used to decode data in secondary flash (external memory)
      if(msgBox.pskSize > sizeof(context->psk))
         break;

      //Store cipher key used to decode data in secondary flash (external memory)
      memcpy(context->psk, msgBox.psk, msgBox.pskSize);
      context->pskSize = msgBox.pskSize;
   } while(0);

   //Make sure to reset message from shared RAM memory
   memset(&msgBox, 0, sizeof(BootMailBox));
   setBootMailBox(&msgBox);

   //Return status code
   return error;
#else
   //Return error code
   return ERROR_NOT_IMPLEMENTED;
#endif
}


/**
 * @brief Jump to the application binary inside the current image in internal flash.
 * @input[in] context Pointer to the bootloader context
 * @return Status code
 **/

error_t bootJumpToApp(BootContext *context)
{
   error_t error;
   const FlashInfo *info;
   uint32_t mcuVtorOffset;

   //Check parameter validity
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   //Get primary flash memory information
   error = context->primaryFlash.driver->getInfo(&info);
   //Is any error?
   if(error)
      return ERROR_FAILURE;

   //Get MCU VTOR offset
   mcuVtorOffset = mcuGetVtorOffset();

   //Jump to application at given address
   mcuJumpToApplication(info->flashAddr + BOOT_OFFSET + mcuVtorOffset);

   //Successful processer
   return NO_ERROR;
}

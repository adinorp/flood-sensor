/**
 * @file iap.c
 * @brief CycloneBOOT IAP User API
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
#include <stdlib.h>
#include "core/flash.h"
#include "core/image.h"
#include "core/slot.h"
#include "iap/iap.h"
#include "iap/iap_process.h"
#include "iap/iap_misc.h"
#include "core/crc32.h"

#if ((IAP_SINGLE_BANK_SUPPORT == ENABLED) &&\
   (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED) &&\
   (IAP_FALLBACK_SUPPORT == DISABLED))
#include "core/mailbox.h"
#endif

#include "debug.h"

//Random data generation callback function
IapRandCallback iapRandCallback;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//IAP Application related private functions
bool_t  iapAcceptUpdateImage(ImageContext *context, uint32_t version);

//Imgage Index related private functions
error_t iapCalculateOutputImageIdx(IapContext *context, uint16_t *imgIdx);
error_t iapGetUpdateSlot(IapContext *context, SlotDesc **slot);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief This function returns the current version of CycloneBOOT IAP
 * @return String that hold CycloneBOOT version.
 **/

char_t *iapGetVersion(void)
{
   return CYCLONE_BOOT_IAP_VERSION_STRING;
}


/**
* @brief Initialize settings with default values
* @param[in,out] settings Structure that contains IAP settings
**/

void iapGetDefaultSettings(IapSettings *settings)
{
   //Clear image output crypto settings structure
   memset(settings, 0x00, sizeof(IapSettings));

#if (VERIFY_INTEGRITY_SUPPORT == ENABLED || IAP_SINGLE_BANK_SUPPORT == ENABLED)
   //IAP integrity setting
   settings->imageInCrypto.verifySettings.integrityAlgo = NULL;
#endif

#if VERIFY_AUTHENTICATION_SUPPORT == ENABLED
   //IAP authentication settings
   settings->imageInCrypto.verifySettings.authAlgo = VERIFY_AUTH_NONE;
   settings->imageInCrypto.verifySettings.authHashAlgo = NULL;
   settings->imageInCrypto.verifySettings.authKey = NULL;
   settings->imageInCrypto.verifySettings.authKeyLen = 0;
#endif

#if VERIFY_SIGNATURE_SUPPORT == ENABLED
   //IAP signature settings
   settings->imageInCrypto.verifySettings.signAlgo = VERIFY_SIGN_NONE;
   settings->imageInCrypto.verifySettings.signHashAlgo = NULL;
   settings->imageInCrypto.verifySettings.signKey = NULL;
   settings->imageInCrypto.verifySettings.signKeyLen = 0;
#endif

#if IAP_ENCRYPTION_SUPPORT == ENABLED
   //IAP cipher settings
   settings->imageInCrypto.cipherAlgo = NULL;
   settings->imageInCrypto.cipherMode = CIPHER_MODE_NULL;
   settings->imageInCrypto.cipherKey = NULL;
   settings->imageInCrypto.cipherKeyLen = 0;
#endif
}


/**
 * @brief Register RNG callback function
 * @param[in] callback RNG callback function
 * @return Error code
 **/

error_t iapRegisterRandCallback(IapRandCallback callback)
{
   //Check parameter
   if(callback == NULL)
      return ERROR_INVALID_PARAMETER;

   //Save callback function
   iapRandCallback = callback;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Initialize IAP Application context
 * @param[in,out] context Pointer to the IAP Application context to be initialized
 * @return Status code
 **/

cboot_error_t iapInit(IapContext *context, const IapSettings *settings)
{
   error_t error;
#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
   uint16_t newImgIdx;
#endif

   //Check Parameters validity
   if(context == NULL || settings == NULL)
      return CBOOT_ERROR_INVALID_PARAMETERS;

   //Debug message
   TRACE_INFO("Initializing IAP...\r\n");

   //Clear the IAP context
   memset(context, 0, sizeof(IapContext));

    //Save user settings
   context->settings = *settings;

   //Initialize primary (internal flash) memory driver
   error = iapInitPrimaryMemory(&context->settings,context);
   //Is any error?
   if(error)
      return CBOOT_ERROR_FAILURE;

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
   //Initialize secondary (external) memory driver
   error = iapInitSecondaryMemory(&context->settings,context);
   //Is any error?
   if(error)
      return CBOOT_ERROR_FAILURE;
#endif

   //Initialize image input context (will process received update image)
   error = iapInitInputImage(&context->settings,context);
   //Is any error?
   if(error)
      return CBOOT_ERROR_FAILURE;

   //Initialize image output context (will process the output binary or image)
   error = iapInitOutputImage(&context->settings,context);
   //Is any error?
   if(error)
      return CBOOT_ERROR_FAILURE;

#if IAP_SINGLE_BANK_SUPPORT == ENABLED
   // Set index of output image
   error = iapCalculateOutputImageIdx(context, &newImgIdx);
   //Is any error?
   if(error)
      return CBOOT_ERROR_FAILURE;

   context->imageOutput.imgIdx = newImgIdx;
#endif

   //Get slot to store output update image
   error = iapGetUpdateSlot(context, &context->imageOutput.slotInfo);
   //Is any error?
   if(error)
      return CBOOT_ERROR_FAILURE;

   //Get external flash memory start address
   context->imageOutput.firmwareAddr = context->imageOutput.slotInfo->addr;

   //Initialize memory position to flash bank start addresse
   context->imageOutput.pos = context->imageOutput.firmwareAddr;

   //Successful process
   return CBOOT_NO_ERROR;
}


/**
 * @brief Write receive firmware in the unused flash bank.
 * @param[in,out] context Pointer to the IAP application context
 * @param[in] data Firmware chunck of data to be written in flash bank
 * @param[in] length Length of the firmware chunck of data to be written
 * @return Status code
 **/

cboot_error_t iapUpdate(IapContext *context, const void *data, size_t length)
{
   error_t error;
   uint_t n;
   uint8_t *pData;

   //Check parameters validity
   if (context == NULL || data == NULL || length == 0)
      return CBOOT_ERROR_INVALID_PARAMETERS;//ERROR_INVALID_PARAMETER;

   //Initialize variables
   n = 0;
   error = NO_ERROR;

   //Point to the beginning of the data
   pData = (uint8_t*)data;

   //Process the incoming data
   while(length > 0)
   {
      //Still room in buffer?
      if(context->imageInput.bufferLen < sizeof(context->imageInput.buffer))
      {
         //Fill buffer with input data
         n = MIN(length, sizeof(context->imageInput.buffer) - context->imageInput.bufferLen);
         memcpy(context->imageInput.bufferPos, pData, n);

         //Update buffer position and length
         context->imageInput.bufferPos += n;
         context->imageInput.bufferLen += n;

         //Update input data postion and length
         pData += n;
         length -= n;

         //Process received image input data
         error = iapProcessInputImage(&context->imageInput);
         //Is any error?
         if(error)
         {
#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
            //Erase output image slot first bytes to make sure bootloader doesn't
            //consider it as a new valid update image if a reboot occurs
            context->secondaryMem.driver->erase(
               context->imageOutput.slotInfo->addr, sizeof(ImageHeader));
#endif
            break;
         }
      }
      else
      {
         //Debug message
         TRACE_ERROR("Buffer would overflow!\r\n");
         error = ERROR_BUFFER_OVERFLOW;
         break;
      }
   }

   //Return error code
   if(error) {
      return CBOOT_ERROR_FAILURE;
   } else {
      return CBOOT_NO_ERROR;
   }
}


/**
 * @brief Finalize firmware update. It performs :
 *    - Firmware integrity or authentification or signature validation.
 *    - Flash bank memory swap setup
 * If validation is done successfully the device would be ready for reboot,
 * if not an error will be raised.
 * The firmware validation can only be done if all the image
 * (header, firmware data and check data) has been processed successfully, if not
 * an error will be raised.
 * @param[in,out] context Pointer to the IAP application context
 * @return Error code
 **/

cboot_error_t iapFinalize(IapContext* context)
{
   error_t error;
#if (IAP_DUAL_BANK_SUPPORT == ENABLED)
   const FlashInfo *memInfo;
#endif
#if (IAP_SINGLE_BANK_SUPPORT == ENABLED && \
   IAP_FALLBACK_SUPPORT == DISABLED && \
   IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   BootMailBox bMsg;
#endif

   //Check parameters validity
   if (context == NULL)
      return CBOOT_ERROR_INVALID_PARAMETERS;

   //Debug message
   TRACE_INFO("Finalizing firmware update...\r\n");

   //Ready to verify firmware image validity?
   if (context->imageInput.state == IAP_STATE_VALIDATE_APP)
   {
      //Verify firmware image validity (could integrity tag or
      //authentification tag or signature)
      error = verifyConfirm(&context->imageInput.verifyContext, context->imageInput.checkData, context->imageInput.checkDataLen);
      //Is any error?
      if (error)
      {
         //Debug message
         TRACE_ERROR("Firmware image is invalid!\r\n");

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
            //Erase output image slot first bytes to make sure bootloader doesn't
            //consider it as a new valid update image if a reboot occurs
            context->secondaryMem.driver->erase(
               context->imageOutput.slotInfo->addr, sizeof(ImageHeader));
#endif

         //Return to IAP idle state
         context->imageInput.state = IAP_STATE_IDLE;
         //Return error code
         return CBOOT_ERROR_INVALID_IMAGE_APP;
      }

      //Debug message
      TRACE_INFO("Firmware image is valid\r\n");

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
#if (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED && \
     IAP_FALLBACK_SUPPORT == DISABLED)
      //Setup bootloader mailbox to share PSK key used to encrypt output image in external flash memory
      bMsg.version   = BOOT_MBX_VERSION;
      bMsg.signature = BOOT_MBX_SIGNATURE;
      bMsg.pskSize   = strlen(context->imageOutput.cipherEngine.key);
      memcpy(bMsg.psk, context->imageOutput.cipherEngine.key, bMsg.pskSize);

      //Debug message
      TRACE_DEBUG("BootMailBox:\r\n");
      TRACE_DEBUG_ARRAY("- psk: ", bMsg.psk, bMsg.pskSize);
      TRACE_DEBUG("- psk size: %d\r\n", bMsg.pskSize);

      //Send PSK key to the Bootloader (SRAM)
      setBootMailBox(&bMsg);
#endif
#else
      //Get flash info
      error = context->primaryMem.driver->getInfo(&memInfo);
      //Is any error?
      if(error)
         return CBOOT_ERROR_FAILURE;

      //Check swap action is done later (after reset)
      if(memInfo->flags & FLASH_FLAGS_LATER_SWAP)
      {
         //Swap banks
         error = context->primaryMem.driver->swapBanks();
         //Is any error?
         if(error)
            return CBOOT_ERROR_FAILURE;
      }
#endif
      //Change IAP state
      context->imageInput.state = IAP_STATE_APP_REBOOT;
   }
   else
   {
      //Debug message
      TRACE_ERROR("Firmware image is not ready for verification!\r\n");

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
            //Erase output image slot first bytes to make sure bootloader doesn't
            //consider it as a new valid update image if a reboot occurs
            context->secondaryMem.driver->erase(
               context->imageOutput.slotInfo->addr, sizeof(ImageHeader));
#endif

      return CBOOT_ERROR_IMAGE_NOT_READY;
   }

   //Successful process
   return CBOOT_NO_ERROR;
}


/**
 * @brief Reboot the device by triggering a system reset.
 * This reboot can only be performed if firmware validation has been done
 * succesfully. If not an error will be raised.
 * @param[in] context Pointer to the IAP context
 * @return Error code.
 **/

cboot_error_t iapReboot(IapContext* context)
{
   error_t error;
   const FlashInfo *memInfo;

   //Debug message
   TRACE_INFO("Rebooting device to finalize update...\r\n");

   //Check parameter validity
   if (context == NULL)
      return CBOOT_ERROR_INVALID_PARAMETERS;

   if (context->imageInput.state == IAP_STATE_APP_REBOOT)
   {
      //Get flash info
      error = context->primaryMem.driver->getInfo(&memInfo);
      //Is any error?
      if(error)
         return CBOOT_ERROR_FAILURE;

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
      //Reboot system to complete firmware update procedure
      mcuSystemReset();
#else
      //Is swap action done later (after reset)?
      if(memInfo->flags & FLASH_FLAGS_LATER_SWAP)
      {
         //Reboot system to complete firmware update procedure
         mcuSystemReset();
      }
      else
      {
         //Swap banks
         error = context->primaryMem.driver->swapBanks();
         //Is any error?
         if(error)
            return CBOOT_ERROR_FAILURE;
      }
#endif
   }
   else
   {
      //Wrong state
      return CBOOT_ERROR_INVALID_STATE;
   }

   //Successful process
   return CBOOT_NO_ERROR;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief This function checks the version of firmware application inside the received update image.
 * If the version of the firmware application in the update image is less than or equal to the version
 * of the current firmware application then the update will be discarded. If not the update image is accepted.
 * This function is used only the IAP_ANTI_ROLLBACK feature is activated.
 * @param[in] context Pointer to the IAP context.
 * @param[in] version Version of the firmware application insde the update image.
 * @return TRUE if the update image is accepted, FALSE otherwise.
 **/

bool_t iapAcceptUpdateImage(ImageContext *context, uint32_t version)
{
   //Check paramter validity
   if(context == NULL)
      return FALSE;

   //The version of the application within the received update image MUST be greater than
   // the version of current running application
   if(version > context->iapContext->settings.appVersion)
      return TRUE;
   else
      return FALSE;
}


/**
 * @brief This function calculates the value of the output image index that will be store
 * in external memory. It first retrieve the value of the image that contains
 * the current application in internal memory, then it increment this value by one
 * and save it in the given output index pointer.
 * This function is used only when the IAP_SINGLE_BANK_MODE_SUPPORT is activated.
 * In Single Bank mode the update image is processed to check its validity while
 * a new ouput image is generated and stored in external memory. This output image will
 * then be processed by the bootloader to complete the update procedure. The bootloader
 * uses the index of the output image againts the index of the image containing
 * the current application firmware to determine if an update is neeeded or not.
 * @param[in] context Pointer to the IAP context.
 * @param[out] imgIdx Calculated value of the output image index.
 * @return Error code.
 **/

error_t iapCalculateOutputImageIdx(IapContext *context, uint16_t *imgIdx)
{
   ImageHeader imgHeader;
   uint32_t curIdx;
   error_t error;

   //Check paramter validity
   if(context == NULL || imgIdx == NULL)
      return ERROR_INVALID_PARAMETER;

   //Get image header from primary flash memory first slot
   error = iapGetImageHeaderFromSlot(&context->primaryMem.slots[0], &imgHeader);
   //Is any error?
   if(error)
      return error;

   //Get image index from header
   curIdx = imgHeader.imgIndex;
   //Save incremented image index
   *imgIdx = ++curIdx;

   //Successful process
   return NO_ERROR;
}


/**
 * @brief This function selects the slot that will hold the output image. The choice of the slot
 * depends of the IAP mode: Dual or Single bank mode.
 * In Dual bank mode:
 * - the output image is the new application firmware binary that was in the update image.
 * - the slected slot is always the other flash bank (the one that doesn't hold the current application binary)
 * In Single Bank mode:
 * - the output image is an image stored in external memory, containing the new application binary
 *   comming from the update image and generating in a way that the bootloader will be abled to process it.
 * - the selected slot is one of the available slot in external memory. It can be:
 *     - if fallback support is not activated, the first and only one slot in external memory
 *     - otherwise one of the slot among the two slots present in external memory
 *       that doesn't hold the backup image of the current running application
 * @param[in] context Pointer to IAP context.
 * @param[out] slot Pointer to the slot that will be used to hold output image.
 * @return
 **/

error_t iapGetUpdateSlot(IapContext *context, SlotDesc **slot)
{
#if (IAP_SINGLE_BANK_SUPPORT == ENABLED && IAP_FALLBACK_SUPPORT == ENABLED)
   error_t error;
   uint16_t imgIndex;
   SlotDesc *tempSlot;
   ImageHeader header;
#endif

   //Check parameters validity
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

#if (IAP_DUAL_BANK_SUPPORT == ENABLED)
   //Select the second slot of primary flash memory that match the second flash bank
   *slot = (SlotDesc*)&context->primaryMem.slots[1];
#else
#if (IAP_FALLBACK_SUPPORT == DISABLED)
   //In single bank mode without fallback support only one
   *slot = (SlotDesc*)&context->secondaryMem.slots[0];
#else
   //Point to the primary flash memory slot
   tempSlot = (SlotDesc*)&context->primaryMem.slots[0];

   //Get header from primary flash memory slot image
   error = iapGetImageHeaderFromSlot(tempSlot, &header);
   //Is any error?
   if(error)
   {
      return error;
   }
   else
   {
      //Save image index of the primary flash memory slot image
      imgIndex = header.imgIndex;

      //Point to the first secondary flash memory slot
      tempSlot = (SlotDesc*)&context->secondaryMem.slots[0];

      //Get header from the first secondary flash memory slot image
      error = iapGetImageHeaderFromSlot(tempSlot, &header);

      //We MUST select the slot from secondary flash memory driver which doesn't store the backup image
      // of the current running application. Which means that :
      // - the image index of selected secondary slot is different from the primary flash memory slot image index
      //    or
      // - the selected secondary slot doesn't contains a valid image (slot is empty or header is invalid)
      if(error == ERROR_INVALID_HEADER || imgIndex != header.imgIndex)
      {
         //Select first secondary flash memory slot
         *slot = (SlotDesc*)&context->secondaryMem.slots[0];
      }
      else
      {
         //Select second secondary flash memory slot
         *slot = (SlotDesc*)&context->secondaryMem.slots[1];
      }
   }
#endif
#endif

   //Successful process
   return NO_ERROR;
}

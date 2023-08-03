/**
 * @file iap_misc.c
 * @brief CycloneBOOT IAP Miscellaneous Functions
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
#if ((IAP_ENCRYPTION_SUPPORT == ENABLED) || \
    ((IAP_SINGLE_BANK_SUPPORT == ENABLED) && \
    (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)))
#include "security/cipher.h"
#endif
#include "iap/iap_misc.h"
#include "core/crc32.h"
#include "debug.h"


/**
 * @brief Initialize primary (internal) flash memory.
 * @param[in,out] settings Pointer to the user IAP settings.
 * @param[in,out] context Pointer to the IAP context.
 * @return Error code
 **/

error_t iapInitPrimaryMemory(IapSettings *settings, IapContext *context)
{
   FlashDriver *flashDriver;
   const FlashInfo *memInfo;
#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
   uint32_t nextSector;
#endif
   error_t error;

   //Check parameters validity
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   //Check primary flash memory driver is valid
   if(settings->primaryFlashDriver == NULL)
      return ERROR_INVALID_PARAMETER;

   //Save primary flash memory driver
   context->primaryMem.driver = (FlashDriver*)settings->primaryFlashDriver;

   //Point to the memory driver
   flashDriver = (FlashDriver*)context->primaryMem.driver;

   //Initialize primary (internal) memory flash driver
   error = flashDriver->init();
   //Is any error?
   if(error)
      return error;

   //Get memory driver informations
   error = flashDriver->getInfo(&memInfo);
   //Is any error?
   if(error)
      return error;

#if IAP_SINGLE_BANK_SUPPORT == ENABLED
   //Debug message
   TRACE_DEBUG("Primary flash addr = 0x%08lX | Bootloader size = 0x%08X\r\n", (unsigned long) memInfo->flashAddr, BOOTLOADER_SIZE);

   // Get the address of the next sector available after the bootloader
   error = context->primaryMem.driver->getNextSectorAddr(memInfo->flashAddr + BOOTLOADER_SIZE, &nextSector);
   //Is any error?
   if(error)
      return error;

   //Debug message
   TRACE_DEBUG("Primary slot 1 addr = 0x%08lX\r\n", (unsigned long) nextSector);

   //Set primary flash memory slot which hold current running application
   //This slot is located after the bootloader at the beginning of the next available flash sector
   context->primaryMem.slots[0].addr = nextSector;
   context->primaryMem.slots[0].size = (memInfo->flashAddr + memInfo->flashSize) - (nextSector + settings->sizeSlot1);
   context->primaryMem.slots[0].flash =  (FlashDesc*)&context->primaryMem;
#elif IAP_DUAL_BANK_SUPPORT == ENABLED

   //Debug message
   TRACE_DEBUG("Primary slot 1 (bank1) addr = 0x%08lX\r\n", (unsigned long) memInfo->bank1Addr);

   //Set primary flash memory slot which hold current running application
   //This slot is located at the beginning of the current flash memory bank 1
   context->primaryMem.slots[0].addr = memInfo->bank1Addr;  //Flash Bank 1 address already match a flash sector address
   context->primaryMem.slots[0].size = memInfo->bankSize;
   context->primaryMem.slots[0].flash =  (FlashDesc*)&context->primaryMem;

   //Debug message
   TRACE_DEBUG("Primary slot 2 (bank2) addr = 0x%08lX\r\n", (unsigned long) memInfo->bank2Addr);

   //Set primary flash memory slot which will hold the new application
   //This slot is located at the beginning of the current flash memory bank 2
   context->primaryMem.slots[1].addr = memInfo->bank2Addr;  //Flash Bank 2 address already match a flash sector address
   context->primaryMem.slots[1].size = memInfo->bankSize;
   context->primaryMem.slots[1].flash = (FlashDesc*)&context->primaryMem;
#endif

   //Succesful process
   return NO_ERROR;
}


/**
 * @brief Initialize settings secondary (external) flash memory.
 * @param[in,out] settings Pointer to the user IAP settings.
 * @param[in,out] context Pointer to the IAP context.
 * @return Error code
 **/

error_t iapInitSecondaryMemory(IapSettings *settings, IapContext *context)
{
#if IAP_SINGLE_BANK_SUPPORT == ENABLED
   error_t error;
   FlashDriver *flashDriver;
   const FlashInfo *memInfo;
   bool_t ret;

   //Check parameters validity
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   //Check secondary flash memory driver is valid
   if(settings->secondaryFlashDriver == NULL)
      return ERROR_INVALID_PARAMETER;

   //Save secondary flash memory driver
   context->secondaryMem.driver = (FlashDriver*)settings->secondaryFlashDriver;

   //Point to the secondary flash memory driver
   flashDriver = (FlashDriver*)context->secondaryMem.driver;

   //Initialize secondary flash memory driver
   error = flashDriver->init();
   //Is any error?
   if(error)
      return error;

   //Get secondary flash memory driver informations
   error = flashDriver->getInfo(&memInfo);
   //Is any error?
   if(error)
      return error;

   //Debug message
   TRACE_DEBUG("Secondary flash addr = 0x%08lX\r\n", (unsigned long) memInfo->flashAddr);
   TRACE_DEBUG("Secondary slot 1 addr = 0x%08lX\r\n", (unsigned long) settings->addrSlot1);

   //Check if user slot 1 address match a secondary flash memory sector address
   ret = flashDriver->isSectorAddr(settings->addrSlot1);
   if(!ret)
      return ERROR_INVALID_VALUE;

   //Check if user slot 1 fits in secondary flash memory
   if(settings->addrSlot1 + settings->sizeSlot1 > memInfo->flashAddr + memInfo->flashSize)
      return ERROR_FAILURE;

   //Set secondary flash memory slot 1 which will hold the new encrypted update image
   //If fallback support is enabled the slot 1 could also hold the
   //backup encrypted image of the current running application
   context->secondaryMem.slots[0].addr = settings->addrSlot1;
   context->secondaryMem.slots[0].size = settings->sizeSlot1;
   context->secondaryMem.slots[0].flash = (FlashDesc*)&context->secondaryMem;

#if IAP_FALLBACK_SUPPORT == ENABLED
   //Debug message
   TRACE_DEBUG("Secondary slot 2 addr = 0x%08lX\r\n", (unsigned long) settings->addrSlot2);

   //Check if user slot 2 address match a secondary flash memory sector address
   if(!flashDriver->isSectorAddr(settings->addrSlot2))
      return ERROR_INVALID_VALUE;

   //Check if user slot 2 fits in secondary flash memory
   if(settings->addrSlot2 + settings->sizeSlot2 > memInfo->flashAddr + memInfo->flashSize)
      return ERROR_FAILURE;

   //Check if user slot 1 & 2 do not overlap
   ret = isSlotsOverlap(settings->addrSlot1, settings->sizeSlot1,
      settings->addrSlot2, settings->sizeSlot2);
   if(ret)
      return ERROR_FAILURE;

   //Set secondary flash memory slot 2 which will hold the new encrypted update image or
   //the backup encrypted image of the current running application
   context->secondaryMem.slots[1].addr = settings->addrSlot2;
   context->secondaryMem.slots[1].size = settings->sizeSlot2;
   context->secondaryMem.slots[1].flash = (FlashDriver*)&context->secondaryMem;
#endif
#endif

   //Succesful process
   return NO_ERROR;
}


/**
 * @brief Initialize input (update) image settings.
 * It will setup all settings needded to process the input image,
 * especially the cryptographic settings.
 * @param[in,out] settings Pointer to the user IAP settings.
 * @param[in,out] context Pointer to the IAP context.
 * @return Error code
 **/

error_t iapInitInputImage(IapSettings *settings, IapContext *context)
{
   error_t error;
   ImageContext *imageIn;

   //Initialize status code
   error = NO_ERROR;

   //Check parameters validity
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   //Check image verification method settings
   if(settings->imageInCrypto.verifySettings.verifyMethod == VERIFY_METHOD_INTEGRITY)
   {
#if VERIFY_INTEGRITY_SUPPORT == ENABLED
      //Check image integrity verification settings
      if(settings->imageInCrypto.verifySettings.integrityAlgo == NULL)
         return ERROR_INVALID_PARAMETER;
#else
      //Image integrity verification support is not activated
      return ERROR_INVALID_PARAMETER;
#endif
   }
   else if(settings->imageInCrypto.verifySettings.verifyMethod == VERIFY_METHOD_AUTHENTICATION)
   {
#if VERIFY_AUTHENTICATION_SUPPORT == ENABLED
      //Check image authentication verification settings
      if(settings->imageInCrypto.verifySettings.authAlgo == VERIFY_AUTH_NONE ||
         settings->imageInCrypto.verifySettings.authHashAlgo == NULL ||
         settings->imageInCrypto.verifySettings.authKey == NULL ||
         settings->imageInCrypto.verifySettings.authKeyLen == 0)
         return ERROR_INVALID_PARAMETER;

      //Force authentication algorythm to HMAC
      if(settings->imageInCrypto.verifySettings.authAlgo != VERIFY_AUTH_HMAC)
         return ERROR_UNSUPPORTED_ALGO;
#else
      //Image authentication verification support is not activated
      return ERROR_INVALID_PARAMETER;
#endif
   }
   else if(settings->imageInCrypto.verifySettings.verifyMethod == VERIFY_METHOD_SIGNATURE)
   {
#if VERIFY_SIGNATURE_SUPPORT == ENABLED
      //Check image signature verification settings
      if(settings->imageInCrypto.verifySettings.signAlgo == VERIFY_SIGN_NONE ||
         settings->imageInCrypto.verifySettings.signHashAlgo == NULL ||
         settings->imageInCrypto.verifySettings.signKey == NULL ||
         settings->imageInCrypto.verifySettings.signKeyLen == 0)
         return ERROR_INVALID_PARAMETER;

      //Check signature algorithm is supported
      if(settings->imageInCrypto.verifySettings.signAlgo != VERIFY_SIGN_RSA &&
         settings->imageInCrypto.verifySettings.signAlgo != VERIFY_SIGN_ECDSA)
         return ERROR_UNSUPPORTED_SIGNATURE_ALGO;
#else
      //Image signature verification support is not activated
      return ERROR_INVALID_PARAMETER;
#endif
   }
   else
   {
      //Debug message
      TRACE_ERROR("Image verification mode not supported!\r\n");
      return ERROR_NOT_IMPLEMENTED;
   }

#if IAP_ENCRYPTION_SUPPORT == ENABLED
   //Check encryption settings
   if(settings->imageInCrypto.cipherAlgo == NULL || settings->imageInCrypto.cipherMode == CIPHER_MODE_NULL ||
       settings->imageInCrypto.cipherKey == NULL || settings->imageInCrypto.cipherKeyLen == 0)
      return ERROR_INVALID_PARAMETER;
   //Force cipher algo to AES
   if(settings->imageInCrypto.cipherAlgo != AES_CIPHER_ALGO)
      return ERROR_UNSUPPORTED_CIPHER_ALGO;
   //Force cipher mode to CBC
   if(settings->imageInCrypto.cipherMode != CIPHER_MODE_CBC)
      return ERROR_UNSUPPORTED_CIPHER_MODE;
#endif

   //Point to the input image context
   imageIn = (ImageContext*)&context->imageInput;

   //Clear input image context
   memset(imageIn, 0x00, sizeof(ImageContext));

   //Set pointer to IAP context
   imageIn->iapContext = (IapContext*)context;
   //Initialize buffer position to buffer start addresse
   imageIn->bufferPos = imageIn->buffer;
   //Initialize check data position to check data start addresse
   imageIn->checkDataPos = imageIn->checkData;

   //Initialize image input process state
   imageIn->state = IAP_STATE_RECV_APP_HEADER;

#if IAP_ENCRYPTION_SUPPORT == ENABLED
   //Is application encrypted?
   if (settings->imageInCrypto.cipherAlgo != NULL)
   {
      //Initialize cipher engine
      error = cipherInit(&imageIn->cipherEngine, settings->imageInCrypto.cipherAlgo,
         settings->imageInCrypto.cipherMode, settings->imageInCrypto.cipherKey,
         settings->imageInCrypto.cipherKeyLen);

      //Is any error?
      if (error)
         return error;
   }
#endif

   //Initialize verification module
   error = verifyInit(&imageIn->verifyContext, &settings->imageInCrypto.verifySettings);
   //Is any error ?
   if (error)
      return error;

   //Get exepecting image check data size
   imageIn->checkDataSize = imageIn->verifyContext.checkDataSize;

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Initialize Output Image settings.
 * It will setup all settings needded to generate the output image.
 * - If CycloneBOOT IAP is confgured in DUal bank mode then the ouput message
 *   will be the new application firmware binary that was contained inside the input (update) image.
 * - Else the ouput image will be:
 *    - an image with encrypted application binary and simple crc32 check (if encryption on external memory is activated)
 *    - or a simple image with non encrypted application binary and simple crc32
 * @param[in,out] settings Pointer to the user IAP settings.
 * @param[in,out] context Pointer to the IAP context.
 * @return Error code
 **/

error_t iapInitOutputImage(IapSettings *settings, IapContext *context)
{
   error_t error;
   ImageContext *imageOut;
   VerifySettings verifySettings;

   //Initialize status code
   error = NO_ERROR;

   //Initialize verify settings structure
   memset(&verifySettings, 0, sizeof(VerifySettings));

   //Check parameters validty
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   //Point to the output image context
   imageOut = (ImageContext*)&context->imageOutput;

   //Clear output image context
   memset(imageOut, 0x00, sizeof(ImageContext));

   //Set pointer to IAP context
   imageOut->iapContext = (IapContext*)context;
   //Initialize buffer position to buffer start addresse
   imageOut->bufferPos = imageOut->buffer;

   //Initialize image output process state
   imageOut->state = 0;

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
#if (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   //Set image output data cipher key (PSK)
   if(context->settings.pskSize == 0 || context->settings.psk == NULL)
      return ERROR_INVALID_PARAMETER;

   //Initialize cipher engine
   error = cipherInit(&imageOut->cipherEngine, AES_CIPHER_ALGO,
      CIPHER_MODE_CBC, context->settings.psk,
      context->settings.pskSize);
   //Is any error?
   if (error)
      return error;

   //Set cipher engine iv
   error = cipherSetIv(&imageOut->cipherEngine, (uint8_t*)"1122334455667788",
      imageOut->cipherEngine.ivLen);
   //Is any error?
   if (error)
      return error;
#endif

   //Initialize check data position to check data start addresse
   imageOut->checkDataPos = imageOut->checkData;

   //Set verification module settings
   verifySettings.verifyMethod = VERIFY_METHOD_INTEGRITY;
   verifySettings.integrityAlgo = CRC32_HASH_ALGO;

   //Initialize verification module
   error = verifyInit(&imageOut->verifyContext, &verifySettings);
   //Is any error ?
   if (error)
      return error;
#endif

   //Return status code
   return error;
}

/**
 * @brief Write firmware data in flash bank starting at the beginning of the bank.
 * Each time this function is called the position in bank and the number of data
 * written is updated.
 * In case writting data would overcome the flash bank an error would be raised.
 * @param[in,out] context Pointer to the IAP context
 * @param[in] data Firmware data bloc to be written in flash
 * @param[in] length Length of the firmware data bloc to be written
 * @return Error code
 **/

error_t iapWrite(ImageContext *context, const uint8_t *data, size_t length, uint8_t flag)
{
   error_t error;
   size_t n;
   static uint8_t tempBuffer[64] = {0};
   static uint8_t *tempBufferPos = tempBuffer;
   static size_t tempBufferLen = 0;
   size_t writeBlockSize;
   const FlashInfo *memInfo;
   const FlashDriver *flashDriver;

   //Check parameters validity
   if(context == NULL || data == NULL || length == 0)
      return ERROR_INVALID_PARAMETER;

   //Get memory driver
   flashDriver = ((FlashDesc*)context->slotInfo->flash)->driver;

   //Get memory driver informations
   error = flashDriver->getInfo(&memInfo);
   //Is any error?
   if(error)
      return error;

   //Get memory driver write block size
   writeBlockSize = memInfo->writeSize;

   //Temporary data flush required?
   if(flag == 2)
   {
      //Reset temporary buffer data
      memset(tempBuffer, 0x00, sizeof(tempBuffer));
      //Reset temporary buffer position
      tempBufferPos = tempBuffer;
      //Reset temporary buffer length
      tempBufferLen = 0;
   }

   //Process incomming data
   while(length > 0)
   {
      //Fill temporary buffer to reach allowed flash memory write block size
      n = MIN(length, writeBlockSize - tempBufferLen);

      //Fill buffer
      memcpy(tempBufferPos, data, n);
      //Update temporary buffer position
      tempBufferPos += n;
      //Update temporary buffer length
      tempBufferLen += n;
      //Advance data pointer
      data += n;
      //Remaining bytes to process
      length -= n;

      //Enought data to be write?
      if(tempBufferLen == writeBlockSize)
      {
         //Write image data into memory
#if IAP_SINGLE_BANK_SUPPORT == ENABLED
     error = context->iapContext->secondaryMem.driver->write(context->pos, (uint8_t*)tempBuffer, writeBlockSize);
#elif IAP_DUAL_BANK_SUPPORT == ENABLED
     error = context->iapContext->primaryMem.driver->write(context->pos, (uint8_t*)tempBuffer, writeBlockSize);
#endif
         //Is any error?
         if(error)
         {
            //Debug message
            TRACE_ERROR("Failed to write image data into external flash memory!\r\n");
            return error;
         }

         //Advance memory write address
         context->pos += writeBlockSize;
         //Reset temporary buffer position
         tempBufferPos = tempBuffer;
         //Reset temporary buffer length
         tempBufferLen = 0;
      }
   }

   //Temporary data write required?
   if(tempBufferLen != 0 && flag == 1)
   {
      //Complete buffer with padding to reach minimum allowed write block size
      memset(tempBufferPos, 0x00, writeBlockSize - tempBufferLen);

      //Write image data into memory
#if IAP_SINGLE_BANK_SUPPORT == ENABLED
      error = context->iapContext->secondaryMem.driver->write(context->pos, (uint8_t*)tempBuffer, writeBlockSize);
#elif IAP_DUAL_BANK_SUPPORT == ENABLED
      error = context->iapContext->primaryMem.driver->write(context->pos, (uint8_t*)tempBuffer, writeBlockSize);
#endif
      //Is any error?
      if(error)
      {
         //Debug message
         TRACE_ERROR("Failed to write image data into external flash memory!\r\n");
         return error;
      }

      //Advance memory write address
      context->pos += writeBlockSize;
      //Reset temporary buffer position
      tempBufferPos = tempBuffer;
      //Reset temporary buffer length
      tempBufferLen = 0;
   }

   //Successful process
   return NO_ERROR;
}


/**
 * @brief This function retrieves the header of the image contained in the given flash memory slot.
 * The given slot can be an primary (internal) or secondary (external) flash slot.
 * @param[in] slot Pointer to given slot that contained the image header to be extracted.
 * @param[out] header Pointer to store the extracted image header.
 * @return Error code.
 **/

error_t iapGetImageHeaderFromSlot(SlotDesc *slot, ImageHeader *header)
{
   error_t error;
   FlashDriver *flashDriver;
   ImageHeader *imgHeader;
   uint8_t buffer[sizeof(ImageHeader)];

   //Check parameter validity
   if(slot == NULL || header == NULL)
      return ERROR_INVALID_PARAMETER;

   //Point to the slot memory driver
   flashDriver = (FlashDriver*)((FlashDesc*)slot->flash)->driver;

   //Read first slot 64 bytes
   error = flashDriver->read(slot->addr, buffer, sizeof(ImageHeader));
   //Is any error?
   if(error)
      return ERROR_FAILURE;

   //Get image header from above buffer
   error = imageGetHeader(buffer, sizeof(ImageHeader), &imgHeader);
   //Is any error?
   if(error)
      return ERROR_INVALID_HEADER;

   //Save image header
   memcpy(header, imgHeader, sizeof(ImageHeader));

   //Successful process
   return NO_ERROR;
}

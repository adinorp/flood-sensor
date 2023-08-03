/**
 * @file boot_common.c
 * @brief Bootloader common functions
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
#include "bootloader/boot_common.h"
#include "core/image.h"
#include "error.h"
#include "debug.h"
#include "core/crc32.h"

//Include crypto header files needed for image decryption
#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
#include "core/crypto.h"
#include "cipher/cipher_algorithms.h"
#include "cipher/aes.h"
#include "cipher_modes/cbc.h"
#endif


#if defined(_WIN32)
#define __attribute__(x)
#endif


/**
 * @brief Intialize bootloader primary flash memory.
 * @param[in,out] context Pointer the bootloader context.
 * @param[in] settings Bootloader user settings used to initialize primary flash.
 * @return Error code
 **/

error_t bootInitPrimaryFlash(BootContext *context, BootSettings *settings)
{
   error_t error;
   FlashDriver *flashDriver;
   const FlashInfo *flashInfo;
   bool_t ret;

   //Check parameters validity
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   //Check primary flash driver is valid
   if(settings->prmFlashDrv == NULL || settings->sndFlashDrv == settings->prmFlashDrv)
      return ERROR_INVALID_PARAMETER;

   //Set primary flash memory driver
   context->primaryFlash.driver = settings->prmFlashDrv;

   //Point to memory driver
   flashDriver = (FlashDriver*)context->primaryFlash.driver;

   //Initialize primary (internal) memory flash driver
   error = flashDriver->init();
   //Is any error?
   if(error)
      return error;

   //Get memory driver informations
   error = flashDriver->getInfo(&flashInfo);
   //Is any error?
   if(error)
      return error;

   //Check if user primary flash slot address match a flash sector address
   ret = flashDriver->isSectorAddr(settings->prmFlashSlotAddr);
   if(!ret)
      return ERROR_INVALID_PARAMETER;

   //Check primary flash slot fits in primary flash
   if((settings->prmFlashSlotAddr + settings->prmFlashSlotSize) >
      (flashInfo->flashAddr + flashInfo->flashSize))
      return ERROR_INVALID_PARAMETER;

   //Set primary flash memory slot which hold current running application
   //This slot MUST be located after the bootloader at the beginning of the next available flash sector
   context->primaryFlash.slots[0].addr = settings->prmFlashSlotAddr;
   context->primaryFlash.slots[0].size = settings->prmFlashSlotSize;
   context->primaryFlash.slots[0].flash = (FlashDesc*)&context->primaryFlash;

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Intialize bootloader secondary (external) flash memory.
 * @param[in,out] context Pointer the bootloader context.
 * @param[in] settings Bootloader user settings used to initialize secondary flash.
 * @return Error code
 **/

error_t bootInitSecondaryFlash(BootContext *context, BootSettings *settings)
{
   error_t error;
   FlashDriver *flashDriver;
   const FlashInfo *flashInfo;
   bool_t ret;

   //Check parameters validity
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   //Check secondary flash driver is valid
   if(settings->sndFlashDrv == NULL || settings->sndFlashDrv == settings->prmFlashDrv)
      return ERROR_INVALID_PARAMETER;

   //Set secondary flash memory driver
   context->secondaryFlash.driver = settings->sndFlashDrv;

   //Point to memory driver
   flashDriver = (FlashDriver*)context->secondaryFlash.driver;

   //Initialize secondary (internal) memory flash driver
   error = flashDriver->init();
   //Is any error?
   if(error)
      return error;

   //Get memory driver informations
   error = flashDriver->getInfo(&flashInfo);
   //Is any error?
   if(error)
      return error;

   //Check if user secondary flash slot 1 address match a flash sector address
   ret = flashDriver->isSectorAddr(settings->sndFlashSlot1Addr);
   if(!ret)
      return ERROR_INVALID_PARAMETER;

   //Check secondary flash slot 2 fits in secondary flash
   if((settings->sndFlashSlot1Addr + settings->sndFlashSlot1Size) >
      (flashInfo->flashAddr + flashInfo->flashSize))
      return ERROR_INVALID_PARAMETER;

   //Set secondary flash memory slot 1 which will hold the new update image
   //If fallback support is enabled the slot 1 could also hold the
   //backup image of the current running application
   context->secondaryFlash.slots[0].addr = settings->sndFlashSlot1Addr;
   context->secondaryFlash.slots[0].size = settings->sndFlashSlot1Size;
   context->secondaryFlash.slots[0].flash = (FlashDesc*)&context->secondaryFlash;

#if (BOOT_FALLBACK_SUPPORT == ENABLED)
   //Check if user secondary flash slot 2 address match a flash sector address
   ret = flashDriver->isSectorAddr(settings->sndFlashSlot2Addr);
   if(!ret)
      return ERROR_INVALID_PARAMETER;

   //Check secondary flash slot 2 fits in secondary flash
   if((settings->sndFlashSlot2Addr + settings->sndFlashSlot2Size) >
      (flashInfo->flashAddr + flashInfo->flashSize))
      return ERROR_INVALID_PARAMETER;

   //Check if user slot 1 & 2 do not overlap
   ret = isSlotsOverlap(settings->sndFlashSlot1Addr, settings->sndFlashSlot1Size,
      settings->sndFlashSlot2Addr, settings->sndFlashSlot2Size);
   if(ret)
      return ERROR_FAILURE;

   //Set secondary flash memory slot 2 which will hold the new update image
   //or the backup image of the current running application
   context->secondaryFlash.slots[1].addr = settings->sndFlashSlot2Addr;
   context->secondaryFlash.slots[1].size = settings->sndFlashSlot2Size;
   context->secondaryFlash.slots[1].flash = (FlashDesc*)&context->secondaryFlash;
#endif

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Select the slot in external memory that hold the the update image.
 * @param[in] context Pointer to the bootloader context
 * @param[out] selectedSlot Pointer to the slot containing the update image.
 * @erturn Error code.
 **/

error_t bootSelectUpdateImageSlot(BootContext *context, SlotDesc **selectedSlot)
{
   error_t error;
   uint_t i;
   SlotDesc *tmpSlot;
   ImageHeader tmpImgHeader;
   uint32_t tmpImgIndex;
#if (BOOT_ANTI_ROLLBACK_SUPPORT == ENABLED)
   uint32_t tmpImgDataVers;
#endif

   //Initiliaze status code
   error = NO_ERROR;

   //Check paramter validity
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   //Point to the primary flash memory slot (contains current image application)
   tmpSlot = (SlotDesc*)&context->primaryFlash.slots[0];

   //Get header of the image inside the current slot
   error = bootGetSlotImgHeader(tmpSlot, &tmpImgHeader);

   //Check image header of the first primary slot is valid
   if(!error)
   {
      //Save image index number from current slot
      tmpImgIndex = tmpImgHeader.imgIndex;
#if (BOOT_ANTI_ROLLBACK_SUPPORT == ENABLED)
      //Save image data version from current slot
      tmpImgDataVers = tmpImgHeader.dataVers;
#endif

      //Save current selected slot
      *selectedSlot = tmpSlot;

#if (BOOT_FALLBACK_SUPPORT == ENABLED)
      //Loop through the two secondary memory slots
      for(i = 0; i < 2; i++)
#else
      //Loop through the single secondary memory slot
      for(i = 0; i < 1; i++)
#endif
      {
         //Point to the current indexed secondary flash memory slot
         tmpSlot = (SlotDesc*)&context->secondaryFlash.slots[i];

         //Get header of the image inside the current slot
         error = bootGetSlotImgHeader(tmpSlot, &tmpImgHeader);
         //Is any error?
         if(error)
         {
            //Discard error
            error = NO_ERROR;
         }
         else
         {
#if (BOOT_ANTI_ROLLBACK_SUPPORT == ENABLED)
            //Is tempory image more recent than the image of the listed slot?
            //If anti-rollback support is activated then temporary image index and
            // image firmware version MUST both be more recent than the listed
            // the image index and image firmware version of the listed slot.
            if((tmpImgHeader.imgIndex > tmpImgIndex) && (tmpImgHeader.dataVers > tmpImgDataVers))
#else
            //Is tempory image more recent than the image of the listed slot?
            //If anti-rollback support is not activated then temporary image index
            // MUST be more recent than the listed the image index of the listed slot.
            if(tmpImgHeader.imgIndex > tmpImgIndex)
#endif
            {
               //Save image index number from current listed slot
               tmpImgIndex = tmpImgHeader.imgIndex;
#if (BOOT_ANTI_ROLLBACK_SUPPORT == ENABLED)
               //Save image data version from current listed slot
               tmpImgDataVers = tmpImgHeader.dataVers;
#endif

               //Update selected slot
               *selectedSlot = tmpSlot;
            }
         }
      }
   }

   //Is any error?
   if(error)
   {
      //Unselect slot
      *selectedSlot = NULL;
   }

   //Return status code
   return error;
}


/**
 * @brief Update current application. Basically it decrypt/copy an image
 * from the external flash memory into the internal flash memory.
 * @param[in] context Pointer to Bootloader context
 * @param[in] slot Pointer to the slot in the external flash memory that
 * contains the new application
 * @return Status code
 **/

error_t bootUpdateApp(BootContext *context, SlotDesc *slot)
{
   error_t error;
   size_t n;
   size_t imgAppSize;
   size_t imgDataPaddingSize;
   uint32_t readAddr;
   uint32_t writeAddr;
   FlashDesc *intMem;
   FlashDesc *extMem;
   const FlashInfo *intMemInfo;
   ImageHeader *header;
   Crc32Context integrityContext;
   const HashAlgo *integrityAlgo;
#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   AesContext cipherContext;
   const CipherAlgo *cipherAlgo;
   uint8_t iv[INIT_VECT_SIZE];
#endif
   uint8_t buffer[512];

   //Check paramters validity?
   if(context == NULL || slot == NULL)
      return ERROR_INVALID_PARAMETER;

   n = 0;


   ////////////////////////////////////////////////////////////////////////////
   //Prepare update process

   //Point to the internal slot memory descriptor
   intMem = &context->primaryFlash;
   //Point to the slot memory descriptor
   extMem = slot->flash;

   //Get slot start address
   readAddr = slot->addr;
   //Get internal stlot address
   writeAddr = intMem->slots[0].addr;

   //Select CRC32 integrity algo
   integrityAlgo = CRC32_HASH_ALGO;

   //Get internal flash memory info
   error = intMem->driver->getInfo(&intMemInfo);
   //Is any error?
   if(error)
	   return error;

   ////////////////////////////////////////////////////////////////////////////
   //Format header of the image containing the new application firmware

   //Read update image slot for secondary (external) memory slot
   error = extMem->driver->read(readAddr, buffer, sizeof(ImageHeader));
   //Is any error?
   if(error)
      return error;

   //Point to image header
   header = (ImageHeader*)buffer;

   //Debug message
   TRACE_DEBUG("\r\n");
   TRACE_DEBUG("Original header:\r\n");
   TRACE_DEBUG_ARRAY("HEADER RAW: ", (uint8_t*)header, sizeof(ImageHeader));

   //Computate image data padding according to device MCU VTOR offset
   header->dataPadding = mcuGetVtorOffset() - sizeof(ImageHeader);

   //Compute new image header crc32 value
   error = integrityAlgo->compute((uint8_t*)header, sizeof(ImageHeader) - CRC32_DIGEST_SIZE, (uint8_t*)&header->headCrc);
   //Is any error?
   if(error)
      return error;

   //Debug message
   TRACE_DEBUG("\r\n");
   TRACE_DEBUG("New header:\r\n");
   TRACE_DEBUG_ARRAY("HEADER RAW: ", (uint8_t*)header, sizeof(ImageHeader));

   //Write new image header into primary (internal) memory slot
   error = intMem->driver->write(writeAddr, (uint8_t*)header, sizeof(ImageHeader));
   //Is any error?
   if(error)
      return error;

   //Save image data padding size
   imgDataPaddingSize = header->dataPadding;
   //Save image application data size
   imgAppSize = header->dataSize;

   //Intialize CRC32 integrity algo context
   integrityAlgo->init(&integrityContext);

   //Start image check crc computation with image header
   integrityAlgo->update(&integrityContext,
      (uint8_t*)&header->headCrc, CRC32_DIGEST_SIZE);

   ////////////////////////////////////////////////////////////////////////////
   //Add padding inside the image betweeen the header
   // and the application firmware image sections.

   //Update write address
   writeAddr += sizeof(ImageHeader);
   //Reset buffer
   memset(buffer, 0, sizeof(buffer));

   //Write image application data padding
   while(imgDataPaddingSize > 0)
   {
      n = MIN(sizeof(buffer), imgDataPaddingSize);

      //Write image padding zero data into primary (internal) memory slot
      error = intMem->driver->write(writeAddr, buffer, n);
      //Is any error?
      if(error)
         return error;

      writeAddr += n;
      imgDataPaddingSize -= n;
   }

   ////////////////////////////////////////////////////////////////////////////
   //Transfert new application firmware data from the image slot
   // in external flash to the image slot in internal flash.

   //Get new image application data iv start address
   readAddr = slot->addr + sizeof(ImageHeader);

#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   //Read iv from external flash memory image slot
   error = extMem->driver->read(readAddr, iv, INIT_VECT_SIZE);
   //Is any error?
   if(error)
      return error;

   //Discard iv
   readAddr += INIT_VECT_SIZE;

   //Debug message
   TRACE_DEBUG("\r\n");
   TRACE_DEBUG("Original IV:\r\n");
   TRACE_DEBUG_ARRAY("IV RAW: ", iv, INIT_VECT_SIZE);

   //Select AES cipher algo
   cipherAlgo = AES_CIPHER_ALGO;

   //Initialize AES cipher algo context
   error = cipherAlgo->init(&cipherContext, (uint8_t*)context->psk, context->pskSize);
   //Is any error?
   if(error)
      return error;
#endif

   //Loop through image application padding
   while(imgAppSize > 0)
   {
      n = MIN(sizeof(buffer), imgAppSize);

      //Read udpate image data from secondary (external) memory slot
      error = extMem->driver->read(readAddr, buffer, n);
      //Is any error?
      if(error)
         return error;

#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
      //Decipher data
      error = cbcDecrypt(cipherAlgo, &cipherContext, iv, buffer, buffer, n);
      //Is any error?
      if(error)
         return error;
#endif

      //Update image binary data crc computation
      integrityAlgo->update(&integrityContext, buffer, n);

      //Avoid to write less that internal flash minimum write size
	  if((n % intMemInfo->writeSize) == 0)
	  {
	     //Write image application data in primaray (internal) memory slot
	     error = intMem->driver->write(writeAddr, buffer, n);
	     //Is any error?
	     if(error)
	        return error;

	     writeAddr += n;
	  }

      readAddr += n;
      imgAppSize -= n;
   }

   ////////////////////////////////////////////////////////////////////////////
   //Generate image CRC32 integrity check section

   //Reset n if it was a multiple of internal flash minimum write size
   if((n > 0) && ((n % intMemInfo->writeSize) == 0))
   {
	  n = 0;
   }

   //Finalize crc32 integrity algo computation
   integrityAlgo->final(&integrityContext, buffer+n);

   //Debug message
   TRACE_DEBUG("\r\n");
   TRACE_DEBUG("New image application CRC:\r\n");
   TRACE_DEBUG_ARRAY("CRC RAW: ", buffer+n, integrityAlgo->digestSize);

   //Write computed image check data in primary (internal) memory slot
   error = intMem->driver->write(writeAddr, buffer, n+integrityAlgo->digestSize);
   //Is any error?
   if(error)
      return error;

   //Successful process
   return NO_ERROR;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/**
 * @brief Check image validity within the given slot.
 * @param[in] slot Pointer to the slot containing the image to be checked.
 * @return Error code.
 **/

error_t bootCheckImage(SlotDesc *slot)
{
   error_t error;
   uint32_t addr;
   size_t n;
   size_t length;
   ImageHeader *header;
   FlashDesc *flash;
   const FlashInfo *info;
   HashAlgo *crcAlgo;
   Crc32Context crcContext;
   uint8_t digest[CRC32_DIGEST_SIZE];
   uint8_t buffer[sizeof(ImageHeader)];

   //Check parameter validty
   if(slot == NULL)
      return ERROR_INVALID_PARAMETER;

   //Point to slot memory descriptor
   flash = (FlashDesc*)slot->flash;

   //Get memory info
   error = flash->driver->getInfo(&info);
   //Is any error?
   if(error)
      return error;

   //Read slot data
   error = flash->driver->read(slot->addr, buffer, sizeof(buffer));
   //Is any error?
   if(error)
      return error;

   //Point to internal image header
   header = (ImageHeader*)buffer;

   //Check internal image header
   error = imageCheckHeader(header);
   //Is any error?
   if(error)
   {
      //Debug message
      TRACE_ERROR("Image header is not valid!\r\n");
      return error;
   }

   //Save internal image data size
   length = header->dataSize;

#if (BOOT_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   //Is image in external flash memory?
   if(info->flashType != FLASH_TYPE_INTERNAL)
   {
      //Image in external flash memory are encrypted and the iv vector used to encrypt
      // the image application is part of the check data calculation
      //Add iv size
      length += INIT_VECT_SIZE;
   }
#endif

   //Check image size
   if(length + sizeof(ImageHeader) + header->dataPadding > slot->size)
   {
      //Debug message
      TRACE_ERROR("Image size is invalid!\r\n");
      return ERROR_INVALID_LENGTH;
   }

   //Point to the CRC32 algorithm
   crcAlgo = (HashAlgo*)CRC32_HASH_ALGO;
   //Intialize CRC algorithm
   crcAlgo->init(&crcContext);
   //Start image check compututation with image header crc
   crcAlgo->update(&crcContext, (uint8_t*)&header->headCrc, CRC32_DIGEST_SIZE);

   //Discard internal image header
   addr = slot->addr + sizeof(ImageHeader) + header->dataPadding;

   //Process image binary data
   while(length > 0)
   {
      //Prevent read operation to overflow buffer size
      n = MIN(sizeof(buffer), length);

      //Read image binary data
      error = flash->driver->read(addr, buffer, n);
      //Is any error?
      if(error)
         return error;

      //Update image binary data crc computation
      crcAlgo->update(&crcContext, buffer, n);

      //Increment external flash memory word address
      addr += n;
      //Remaining bytes to be read
      length -= n;
   }

   //Finalize image binary data crc computation
   crcAlgo->final(&crcContext, digest);

   //Read given image binary crc
   error = flash->driver->read(addr, buffer, CRC32_DIGEST_SIZE);
   //Is any error?
   if(error)
      return error;

   //Compare given against computed image binary crc
   if(memcmp(buffer, digest, CRC32_DIGEST_SIZE) != 0)
   {
      //Debug message
      TRACE_ERROR("Image binary data is not valid!\r\n");
      TRACE_DEBUG("Computed check CRC: ");
      TRACE_DEBUG_ARRAY("", digest, CRC32_DIGEST_SIZE);
      TRACE_DEBUG("Given Check CRC: ");
      TRACE_DEBUG_ARRAY("", buffer, CRC32_DIGEST_SIZE);
      return ERROR_FAILURE;
   }

   //Successfull process
   return NO_ERROR;
}


/**
 * @brief Get header from the image inside the given slot.
 * @param[in] slot Pointer to the slot that contains the image header
 * @param[out] header Pointer that will hold the retrieved image header.
 * @return Error code.
 **/

error_t bootGetSlotImgHeader(SlotDesc *slot, ImageHeader *header)
{
   error_t error;
   uint8_t buffer[sizeof(ImageHeader)];
   ImageHeader *tmpHeader;

   //Initialize status code
   error = NO_ERROR;

   //Check parameter validity
   if(slot == NULL)
      return error;

   //Read first slot data that should correspond to the image header
   error = slotRead(slot, 0, buffer, sizeof(buffer));
   if(error)
      return error;

   //Extract image header from the read data
   error = imageGetHeader(buffer, sizeof(buffer), &tmpHeader);
   if(error)
      return error;

   //Save image header
   memcpy(header, tmpHeader, sizeof(ImageHeader));

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Check reset vector of the current application firmware binary.
 * @param[in] slot Pointer to the slot that contains the application firmware binary.
 * @return Error code.
 **/

error_t bootCheckSlotAppResetVector(SlotDesc *slot)
{
   error_t error;
   uint32_t resetVector;
   uint32_t resetVectorAddrOffset;

   //Initialize status code
   error = NO_ERROR;

   //Compute reset vector address offset (slot app start address offset + 4)
   resetVectorAddrOffset = mcuGetVtorOffset() + 0x4;

   //Check reset vector of the current application
   error = slotRead(slot, resetVectorAddrOffset, (uint8_t*)&resetVector, sizeof(resetVector));

   //Check there is no error?
   if(!error)
   {
      //Is reset vector invalid (wrong value or outside of memory)?
      if((resetVector == 0xFFFFFFFF) || !(slot->addr <= resetVector && resetVector <= slot->addr + slot->size))
      {
    	 //Debug message
    	 TRACE_ERROR("Invalid application reset vector address!\r\n");
    	 TRACE_DEBUG("   The reset vector address should be within the internal flash slot boundaries\r\n");
    	 TRACE_DEBUG("   that holds the current boot-able application image.\r\n");
    	 TRACE_DEBUG("   In other words reset vector address should be between 0x%08lx and 0x%08lx\r\n", slot->addr, slot->addr + slot->size);
    	 TRACE_DEBUG("   but its value is 0x%08lx\r\n", resetVector);
         //Raised an error
         error = ERROR_FAILURE; //ERROR INVALID RESET VECTOR
      }
   }

   //Return status code
   return error;
}

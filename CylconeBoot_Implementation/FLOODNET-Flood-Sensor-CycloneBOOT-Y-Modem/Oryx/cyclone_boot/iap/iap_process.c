/**
 * @file iap_process.c
 * @brief CycloneBOOT IAP Image Processing Functions
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
#include "iap/iap_process.h"
#include "iap/iap_misc.h"
#include "core/crc32.h"
#include "debug.h"


/**
 * @brief Process received input image data.
 * @param[in,out] context Pointer to the Input image context
 * @return Status code
 **/

error_t iapProcessInputImage(ImageContext *context)
{
   error_t error;

   //IAP receiving image header state?
   if(context->state == IAP_STATE_RECV_APP_HEADER)
   {
      //Process image header
      error = iapProcessAppHeader(context);
      //Is any error?
      if(error)
         return error;
   }
   //IAP receiving image data state?
   else if(context->state == IAP_STATE_RECV_APP_DATA)
   {
      //Process image data
      error = iapProcessAppData(context);
      //Is any error?
      if(error)
         return error;
   }
   //IAP receiving image check data state?
   else if(context->state == IAP_STATE_RECV_APP_CHECK)
   {
      //Process image check data
      error = iapProcessAppCheck(context);
      //Is any error?
      if(error)
         return error;
   }
   else
   {
      //Wrong state
      error = ERROR_WRONG_STATE;
   }

   //Successful process
   return NO_ERROR;
}


#if IAP_DUAL_BANK_SUPPORT == ENABLED

/**
 * @brief Process parsed image input data to generate the output image for dual bank mode.
 * It means that the output image data will be written in the other flash bank.
 * The output image will be the new application firmware binary.
 * @param[in,out] context Pointer to the output image context
 * @param[in] data Iutput image data chunk to be processed
 * @param[in] length Length of the output data chunk.
 * @return Status code
 **/

error_t iapProcessOutputImageDualBank(ImageContext *context, uint8_t *data, size_t length)
{
   error_t error;
   size_t n;

   //Check parameters validity
   if(context == NULL || data == NULL || length == 0)
      return ERROR_INVALID_PARAMETER;

   //Process incomming data
   while(length > 0)
   {
      //The buffer can hold at most it size
      n = MIN(length, sizeof(context->buffer) - context->bufferLen);

      //Copy the data to the buffer
      memcpy(context->bufferPos, data, n);

      //Advance the data pointer
      data += n;
      //Remaining bytes to process
      length -= n;
      //Update buffer data length
      context->bufferLen += n;
      //Update buffer data free position
      context->bufferPos += n;

      //Process output image data block
      if(context->state == 0)
      {
         //Set firmware address
         context->firmwareAddr = context->slotInfo->addr;
         //Initialize firmware write address position
         context->pos = context->firmwareAddr;

         //Write first output image data block (with flush flag)
         error = iapWrite(context, context->buffer, context->bufferLen, 2);
         //Is any error?
         if(error)
            return error;
         //Update output image data written bytes number
         context->written += context->bufferLen;

         //Update buffer data length
         context->bufferLen = context->bufferLen - n;
         //Move remainaing buffer data at the beginning of data
         memcpy(context->buffer, context->bufferPos-context->bufferLen, context->bufferLen);
         //Reset buffer data free position
         context->bufferPos = context->buffer + context->bufferLen;

         //Debug message
         TRACE_DEBUG("output written bytes :0x%X/0x%X\r\n", context->written, context->firmwareLength);

         //Change state
         context->state = 1;
      }
      else if(context->state == 1)
      {
         if(context->written + context->bufferLen == context->firmwareLength)
         {
            //Write output image data block
            error = iapWrite(context, context->buffer, context->bufferLen, 1);
            //Is any error?
            if(error)
               return error;

            //Update output image data written bytes number
            context->written += context->bufferLen;

            //Update buffer data length
            context->bufferLen = 0;
            //Reset buffer data free position
            context->bufferPos = context->buffer;

            //Change state
            context->state = 2;
         }
         else
         {
            //Write output image data block
            error = iapWrite(context, context->buffer, context->bufferLen, 0);
            //Is any error?
            if(error)
               return error;

            //Update output image data written bytes number
            context->written += context->bufferLen;

            //Update buffer data length
            context->bufferLen = context->bufferLen - n;
            //Move remainaing buffer data at the beginning of data
            memcpy(context->buffer, context->bufferPos-context->bufferLen, context->bufferLen);
            //Reset buffer data free position
            context->bufferPos = context->buffer + context->bufferLen;
         }

         //Debug message
         TRACE_DEBUG("output written bytes :0x%X/0x%X\r\n", context->written, context->firmwareLength);
      }
      //End of image output process
      else
      {
         //For sanity
      }
   }

   //Successful process;
   return NO_ERROR;
}

#else

/**
 * @brief Process parsed image input data to generate the output image for single bank mode.
 * It means that the output image data will be written in the external memory.
 * The output image will be either:
 * - a simple image with unencrypted firmware binary and CRC32 integrity tag
 * - a cipher image with encrypted firmware binary and CRC32 integrity tag
 * @param[in,out] context Pointer to the output image context
 * @param[in] data Iutput image data chunk to be processed
 * @param[in] length Length of the output data chunk.
 * @return Status code
 **/

error_t iapProcessOutputImageSingleBank(ImageContext *context, uint8_t *data, size_t length)
{
   error_t error;
   size_t n;
   ImageHeader *imgHeader;

   //Check parameters validity
   if(context == NULL || data == NULL || length == 0)
      return ERROR_INVALID_PARAMETER;

   //Debug message
   TRACE_DEBUG("output written bytes :0x%X/0x%X\r\n", context->written, context->firmwareLength);

   //Process the incoming data
   while(length > 0)
   {
      //The buffer can hold at most it size
      n = MIN(length, sizeof(context->buffer) - context->bufferLen);

      //Copy the data to the buffer
      memcpy(context->bufferPos, data, n);

      //Advance the data pointer
      data += n;
      //Remaining bytes to process
      length -= n;
      //Update buffer data length
      context->bufferLen += n;
      //Update buffer data free position
      context->bufferPos += n;

      //Format new Header
      if(context->state == 0)
      {
         //Point to image header
         imgHeader = (ImageHeader*)context->buffer;

         //Debug message
         TRACE_DEBUG_ARRAY("HEADER: ", (uint8_t*)imgHeader, sizeof(ImageHeader));

         //Set new header image index
         imgHeader->imgIndex = context->imgIdx;

         //Save original image data size
         context->firmwareLength = imgHeader->dataSize;

#if (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
         //Make shure header image data size is a multiple of encryption algo block size
         if(imgHeader->dataSize % context->cipherEngine.ivLen != 0)
            imgHeader->dataSize += context->cipherEngine.ivLen - (imgHeader->dataSize % context->cipherEngine.ivLen);
#endif

         //Compute new image header crc
         CRC32_HASH_ALGO->compute((uint8_t*)imgHeader, sizeof(ImageHeader) - CRC32_DIGEST_SIZE, (uint8_t*)&imgHeader->headCrc);

         //Update application check computation tag (could be integrity tag or
         //authentification tag or hash signature tag)
         error = verifyProcess(&context->verifyContext, (uint8_t*)&imgHeader->headCrc, CRC32_DIGEST_SIZE);
         //Is any error?
         if(error)
            return error;

         //Set external memory start write address (selected slot start address)
         context->firmwareAddr = context->slotInfo->addr;
         context->pos = context->firmwareAddr;

         //Write new image header (with flush)
         error = iapWrite(context, (uint8_t*)imgHeader, sizeof(ImageHeader), 2);
         if(error)
            return error;

#if (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
         //Write new image cipher IV vector into memory
         error = iapWrite(context, (uint8_t*)context->cipherEngine.iv, context->cipherEngine.ivLen, 0);
         if(error)
            return error;

         //Update image check data computation tag (crc tag)
         error = verifyProcess(&context->verifyContext, context->cipherEngine.iv, context->cipherEngine.ivLen);
         if(error)
            return error;
#endif

         //Reset buffer position
         context->bufferPos = context->buffer;
         //Reset buffer data
         memset(context->buffer, 0x00, sizeof(context->buffer));
         //Reset buffer data length
         context->bufferLen = 0;

         //Change state
         context->state = 1;
      }
      //Encrypt data
      else
      {
         //Reached end of image firmware binary section?
         if(context->written + context->bufferLen == context->firmwareLength)
         {
#if (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
            //Encryp data bloc size must be a multiple of cipher data block size
            n = (context->bufferLen / 16)*16;

            //Encrypt image data block
            error = cipherEncryptData(&context->cipherEngine, context->buffer, n);
            if(error)
               return error;

            //Update image check data computation tag (crc tag)
            error = verifyProcess(&context->verifyContext, context->buffer, n);
            if(error)
               return error;

            //Is there any data left in buffer?
            if(n != context->bufferLen)
            {
               //Write encrypted image data into memory
               error = iapWrite(context, context->buffer, n, 0);
               if(error)
                  return error;
               //Update written data
               context->written += n;

               //Update buffer data length
               context->bufferLen -= n;
               //Update buffer position
               context->bufferPos -= context->bufferLen;
               //Move remaining buffer data at the beginning
               memcpy(context->buffer, context->bufferPos, context->bufferLen);
               //Reset buffer position
               context->bufferPos = context->buffer + context->bufferLen;

               //Compute padding size to reach allowed encryption block size
               n = context->cipherEngine.ivLen - context->bufferLen;
               //Add paddind to the remaining data
               memset(context->bufferPos, 0x00, n);
               //Update context buffer length
               context->bufferLen += n;

               //Encrypt last image data block
               error = cipherEncryptData(&context->cipherEngine, context->buffer, context->bufferLen);
               if(error)
                  return error;

               //Update image check data computation tag (crc tag)
               error = verifyProcess(&context->verifyContext, context->buffer, context->bufferLen);
               if(error)
                  return error;
            }

            //Write last encrypted image data block (force write)
            error = iapWrite(context, context->buffer, context->bufferLen, 1);
            if(error)
               return error;
#else
            //Update image check data computation tag (crc tag)
            error = verifyProcess(&context->verifyContext, context->buffer, context->bufferLen);
            if(error)
               return error;

            //Write image data block into memory
            error = iapWrite(context, context->buffer, context->bufferLen, 0);
            if(error)
               return error;
#endif

            //Update written data
            context->written += n;

            //Finalize image check data computation tag (crc tag)
            error = verifyGenerateCheckData(&context->verifyContext, context->buffer,
               context->verifyContext.imageCheckDigestSize, &context->bufferLen);

            //Write new image check data tag (crc tag)
            error = iapWrite(context, context->buffer, context->bufferLen, 1);
            if(error)
               return error;
         }
         else
         {
#if (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
            //Encryption data bloc size must be a multiple of cipher data block size
            n = (context->bufferLen / 16)*16;

            //Encrypt image data block
            error = cipherEncryptData(&context->cipherEngine, context->buffer, n);
            if(error)
               return error;

            //Update image check data computation tag (crc tag)
            error = verifyProcess(&context->verifyContext, context->buffer, n);
            if(error)
               return error;

            //Write encrypted image data into memory
            error = iapWrite(context, context->buffer, n, 0);
            if(error)
               return error;

            context->written += n;

            //Update buffer data length
            context->bufferLen -= n;
            //Update buffer position
            context->bufferPos -= context->bufferLen;
            //Move remianing buffer data at the beginning
            memcpy(context->buffer, context->bufferPos, context->bufferLen);
            //Reset buffer position
            context->bufferPos = context->buffer + context->bufferLen;
#else
            //Update image check data computation tag (crc tag)
            error = verifyProcess(&context->verifyContext, context->buffer, context->bufferLen);
            if(error)
               return error;

            //Write encrypted image data into memory
            error = iapWrite(context, context->buffer, context->bufferLen, 0);
            if(error)
               return error;

            //Update context buffer length
            context->written += context->bufferLen;

            //Update buffer data length
            context->bufferLen = 0;
            //Reset buffer position
            context->bufferPos = context->buffer;
            //Reset buffer
            memset(context->buffer, 0, sizeof(context->buffer));
#endif
         }
      }
   }

   //Successful process
   return NO_ERROR;
}
#endif


/**
 * @brief Process parsed image input data to generate the output image.
 * Regarding the CycloneBOOT mode it will generate an ouptut image for the Dual-Bank mode
 * or the SingleBank mode.
 * @param[in,out] context Pointer to the IAP application context
 * @param[in] data Output image data chunk to be processed
 * @param[in] length Length of the output data chunk.
 * @return Status code
 **/

error_t iapProcessOutputImage(ImageContext *context, uint8_t *data, size_t length)
{
#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
   return iapProcessOutputImageSingleBank(context, data, length);
#else
   return iapProcessOutputImageDualBank(context, data, length);
#endif
}


/**
 * @brief Process image application header.
 * Once fully received it will parse the image header,
 * check its integrity and retrieve needed data.
 * @param[in,out] context Pointer to the IAP context
 * @return Error code.
 **/

error_t iapProcessAppHeader(ImageContext *context)
{
   error_t error;
   ImageHeader *imgHeader;
   const FlashInfo *memInfo;
   ImageContext *outputImg;
   uint_t n;

   //Check parameter validity
   if (context == NULL)
      return ERROR_INVALID_PARAMETER;

   //Initialize variable
   imgHeader = NULL;
   n = 0;

   //Is buffer full enough to contains IAP image header?
   if (context->bufferLen >= sizeof(ImageHeader))
   {
      //Debug message
      TRACE_DEBUG("Processing firmware image header...\r\n");

      //Get input image header
      error = imageGetHeader(context->buffer, context->bufferLen, &imgHeader);
      //Is any error?
      if(error)
      {
         //Debug message
         TRACE_INFO("Input image header is invalid!\r\n");
         //Forward error
         return error;
      }

#if IAP_ANTI_ROLLBACK_SUPPORT == ENABLED
     //Decide whether to perform the update or not in regards of the
     //  firmware application version inside the update image.
     if(!iapAcceptUpdateImage(context,imgHeader->dataVers))
     {
         //Debug message
         TRACE_INFO("Update Aborted! Invalid image header version.\r\n");
         //Forward error
         return ERROR_FAILURE;
     }
#endif

      //Check header image type
      if(imgHeader->imgType != IMAGE_TYPE_APP)
      {
         //Debug message
         TRACE_ERROR("Invalid header image type!\r\n");
         return ERROR_FAILURE;
      }

      //Get memory driver infos
      error = context->iapContext->primaryMem.driver->getInfo(&memInfo);
      //Is any error?
      if(error)
         return error;

      //Point to output image context
      outputImg = (ImageContext*)&context->iapContext->imageOutput;

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
      //Would firmware overcome the external flash memory slot size?
      if (imgHeader->dataSize + sizeof(ImageHeader) + outputImg->verifyContext.verifySettings.integrityAlgo->digestSize > outputImg->slotInfo->size)
#else
      //Would firmware overcome the flash bank 2 size?
      if (imgHeader->dataSize > context->iapContext->imageOutput.slotInfo->size)
#endif
      {
         //Debug message
         TRACE_ERROR("Image is bigger than the flash memory slot!\r\n");
         //Forward error
         return ERROR_BUFFER_OVERFLOW;
      }

      //Save application firmware length
      context->firmwareLength = imgHeader->dataSize;
      outputImg->firmwareLength = imgHeader->dataSize;

#if (IAP_SINGLE_BANK_SUPPORT == ENABLED)
      //Process parsed image input header for later output image generation
      error = iapProcessOutputImage(&context->iapContext->imageOutput, (uint8_t*)imgHeader, sizeof(ImageHeader));
      if(error)
         return error;
#endif

      //Update application check computation tag (could be integrity tag or
      //authentification tag or hash signature tag)
      error = verifyProcess(&context->verifyContext, (uint8_t*)&imgHeader->headCrc, CRC32_DIGEST_SIZE);
      //Is any error?
      if(error)
         return error;


      //Remove header from buffer
      n = context->bufferLen - sizeof(ImageHeader);
      memcpy(context->buffer, context->buffer + sizeof(ImageHeader), n);
      context->bufferPos -= sizeof(ImageHeader);
      context->bufferLen -= sizeof(ImageHeader);

      //Change IAP state
      context->state = IAP_STATE_RECV_APP_DATA;
   }

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Process receiving of the firmware cipher initialization vector (iv) in
 * case the firmware has been encrypted. Once fully received it will be save for
 * later firmware dencryption.
 * of the inside firmware.
 * @param[in,out] context Pointer to the IAP context
 * @return Error code.
 **/

error_t iapProcessAppCipherIv(ImageContext *context)
{
#if IAP_ENCRYPTION_SUPPORT == ENABLED
   error_t error;
   uint_t n;

   //Check parameter validity
   if (context == NULL)
      return ERROR_INVALID_PARAMETER;

   //Initialize variable
   n = 0;

   //Is buffer full enough to contains IAP image header?
   if (context->bufferLen >= context->cipherEngine.algo->blockSize)
   {
      //Debug message
      TRACE_DEBUG("Processing firmware image cipher initialization vector...\r\n");


      //Save application cipher intialization vector
      error = cipherSetIv(&context->cipherEngine, context->buffer, context->cipherEngine.ivLen);
      //Is any error?
      if(error)
         return error;

      //Set cipher iv as retrieved
      context->ivRetrieved = TRUE;

      //Update application check computation tag (could be integrity tag or
      //authentification tag or hash signature tag)
      error = verifyProcess(&context->verifyContext, context->cipherEngine.iv, context->cipherEngine.ivLen);
      //Is any error?
      if(error)
         return error;

      //Remove processed data (cipher iv) from buffer
      n = context->bufferLen - context->cipherEngine.ivLen;
      memcpy(context->buffer, context->buffer + context->cipherEngine.ivLen, n);
      context->bufferPos -= context->cipherEngine.ivLen;
      context->bufferLen -= context->cipherEngine.ivLen;
   }

   //Successful process
   return NO_ERROR;
#else
   //Not implemented
   return ERROR_NOT_IMPLEMENTED;
#endif
}


/**
 * @brief Process receiving of the firmware data bloc by bloc.
 * If firmware is encrypted the data will first be deencrypted then depending
 * of the user settings integrity or authentification or signature hash
 * computation will be done one each data blocs.
 * Finally each data bloc will write into the flash
 * bank.
 * @param[in,out] context Pointer to the IAP context
 * @return Error code.
 **/

error_t iapProcessAppData(ImageContext *context)
{
   error_t error;
   uint_t dataLength;
   static ImageContext *imgOutput;

   //Check parameter validity
   if (context == NULL)
      return ERROR_INVALID_PARAMETER;

   //Point to image output context
   imgOutput = (ImageContext*) &context->iapContext->imageOutput;

#if IAP_ENCRYPTION_SUPPORT == ENABLED
   //Receiving image application header?
   if(context->cipherEngine.algo != NULL && !context->ivRetrieved)
   {
      //Process application cipher initialisation vector here
      error = iapProcessAppCipherIv(context);
      //Is any error?
      if (error)
         return error;
   }
   //Receiving image firmware data?
   else
   {
#else
   //Receiving image firmware data?
   if(1)
   {
#endif
      //Is buffer full or full enought to contain last application data?
      if ((context->bufferLen == sizeof(context->buffer)) ||
         (context->written + context->bufferLen >= context->firmwareLength))
      {
         //We must not process more data than the firmware length
         dataLength = MIN(context->bufferLen, context->firmwareLength - context->written);

         //Update application check computation tag (could be integrity tag or
         //authentification tag or hash signature tag)
         error = verifyProcess(&context->verifyContext, context->buffer, dataLength);
         //Is any error?
         if (error)
            return error;

#if IAP_ENCRYPTION_SUPPORT == ENABLED
         //Is application is encrypted?
         if (context->cipherEngine.algo != NULL)
         {
            //Decrypt application data
            error = cipherDecryptData(&context->cipherEngine, context->buffer, dataLength);

            //Is any error?
            if (error)
               return error;
         }
#endif

         //Process output image data
         error = iapProcessOutputImage(imgOutput, context->buffer, dataLength);
         //Is any error?
         if(error)
            return error;

         context->written += dataLength;

         //Is buffer contains remaining data?
         if (context->bufferLen != dataLength)
         {
            //Discard already processed data
            memset(context->buffer, 0, dataLength);

            //Put remaining data at buffer start
            memcpy(context->buffer, context->buffer + dataLength,
               context->bufferLen - dataLength);
            //Update buffer position and length
            context->bufferPos = context->buffer + (context->bufferLen - dataLength);
            context->bufferLen = context->bufferLen - dataLength;
         }
         else
         {
            //Reset buffer
            memset(context->buffer, 0, sizeof(context->buffer));
            context->bufferPos = context->buffer;
            context->bufferLen = 0;
         }

         //Is application data all received?
         if (context->written == context->firmwareLength)
         {
            //Change IAP state
            context->state = IAP_STATE_RECV_APP_CHECK;

            //Still data to process?
            if (context->bufferLen > 0)
            {
               //Process IAP check app data
               error = iapProcessAppCheck(context);
               //Is any error?
               if (error)
                  return error;
            }
         }
      }
   }

   //Successfull process
   return NO_ERROR;
}

/**
 * @brief Process receiving of the image check data. Depending of the user
 * settings it could be the integrity or the authentification tag or signature
 * of the image firmware data. Once fully received it will saved for further
 * firmware validity verification.
 * @param[in,out] context Pointer to the IAP context
 * @return Error code.
 **/

error_t iapProcessAppCheck(ImageContext *context)
{
   //Check parameter validity
   if (context == NULL)
      return ERROR_INVALID_PARAMETER;

   //Is buffer full enough to contains IAP image check data?
   //(could be integrity/authentification tag or signature)
   if (context->checkDataLen + context->bufferLen <= context->checkDataSize)
   {
      //Save image check data block
      memcpy(context->checkDataPos, context->buffer, context->bufferLen);
      context->checkDataPos += context->bufferLen;
      context->checkDataLen += context->bufferLen;

      //Reset buffer
      memset(context->buffer, 0, sizeof(context->buffer));
      context->bufferPos = context->buffer;
      context->bufferLen = 0;

      //Is image check data fully received?
      if (context->checkDataLen == context->checkDataSize)
      {
         //Change IAP state
         context->state = IAP_STATE_VALIDATE_APP;
      }
   }
   else
   {
      //Debug message
      TRACE_ERROR("Image check data is bigger than expected!\r\n");
      return ERROR_BUFFER_OVERFLOW;
   }

   //Successful process
   return NO_ERROR;
}

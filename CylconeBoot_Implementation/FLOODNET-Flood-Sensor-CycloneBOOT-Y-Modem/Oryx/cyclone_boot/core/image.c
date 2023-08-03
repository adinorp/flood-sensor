/**
 * @file image.c
 * @brief Image managment
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
#include <stdlib.h>
#include "image.h"
#include "core/crc32.h"
#include "debug.h"
#include "core/crypto.h"
#include "core/slot.h"


/**
 * @brief Check Internal Image header validity
 * @param[in] header Pointeur to the internal image header to be checked
 * @return Status code
 **/

error_t imageCheckHeader(ImageHeader *header)
{
   error_t error;
   uint32_t computedCrc;

   //Check parameter vailidty
   if(header == NULL)
      return ERROR_INVALID_PARAMETER;

   //Compute image header crc
   error = CRC32_HASH_ALGO->compute((uint8_t*)header, sizeof(ImageHeader) - CRC32_DIGEST_SIZE, (uint8_t*)&computedCrc);
   if(error)
   {
      //Debug message
      TRACE_ERROR("Failed to compute image header crc!\r\n");
      return error;
   }

   //Check image header integrity
   if(header->headCrc != computedCrc)
      return ERROR_INVALID_HEADER;

   //Check image header version
   if(header->headVers != IMAGE_HEADER_VERSION)
      return ERROR_INVALID_VERSION;

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Get image header from data buffer
 * @param[in] buffer Data buffer containing the image header
 * @param[in] bufferLen Data buffer length
 * @param[out] header Pointeur to the header structure to be returned
 * @return Status code
 **/

error_t imageGetHeader(uint8_t *buffer, size_t bufferLen, ImageHeader **header)
{
   error_t error;
   ImageHeader *tempHeader;

   //Check parameters validity
   if(buffer == NULL || bufferLen == 0)
      return ERROR_INVALID_PARAMETER;

   if(bufferLen < sizeof(ImageHeader))
      return ERROR_INVALID_LENGTH;

   //Point to the image header
   tempHeader = (ImageHeader *)buffer;

   //Check image header
   error = imageCheckHeader(tempHeader);
   //Is any error?
   if(error)
      return error;

   //Save image header
   *header = (ImageHeader*) tempHeader;

   //Successful process
   return NO_ERROR;
}

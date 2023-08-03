/**
 * @file image.h
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

#ifndef __IMAGE_H
#define __IMAGE_H

//Dependencies
#include "compiler_port.h"
#include "core/crypto.h"
#include "error.h"

//Image Header Major version
#define IMAGE_HEADER_VERSION_MAJOR 1
//Image Header Minor version
#define IMAGE_HEADER_VERSION_MINOR 0
//Image Header Revision number
#define IMAGE_HEADER_VERSION_PATCH 0
//Image Header version
#define IMAGE_HEADER_VERSION (uint32_t)(((IMAGE_HEADER_VERSION_MAJOR & 0xFF) << 16) | ((IMAGE_HEADER_VERSION_MINOR & 0xFF) << 8) | (IMAGE_HEADER_VERSION_PATCH & 0xFF))

/**
 * @brief Image type definition
 **/

typedef enum
{
   IMAGE_TYPE_APP
} ImageType;


#if defined(_WIN32)

#undef interface
#undef __start_packed
#define __start_packed __pragma( pack(push, 1) )
#undef __end_packed
#define __end_packed __pragma( pack(pop) )
#define __weak

/**
 * @brief Image header definition
 **/

__start_packed typedef struct
{
   uint32_t headVers;      ///<Image header version
   uint32_t imgIndex;      ///<Image index
   uint8_t imgType;        ///<Image type
   uint32_t dataPadding;   ///<Image data padding
   uint32_t dataSize;      ///<Image data size
   uint32_t dataVers;      ///<Image data version
   uint64_t imgTime;       ///<Image data generated time
   uint8_t reserved[31];   ///<Reserved field
   uint32_t headCrc;       ///<Image header CRC32 integrity tag
} ImageHeader __end_packed;

#else

/**
 * @brief Image header definition
 **/

typedef __start_packed  struct
{
   uint32_t headVers;      ///<Image header version
   uint32_t imgIndex;      ///<Image index
   uint8_t imgType;        ///<Image type
   uint32_t dataPadding;   ///<Image data padding
   uint32_t dataSize;      ///<Image data size
   uint32_t dataVers;      ///<Image data version
   uint64_t imgTime;       ///<Image data generated time
   uint8_t reserved[31];   ///<Reserved field
   uint32_t headCrc;       ///<Image header CRC32 integrity tag
} __end_packed ImageHeader;
#endif

//CycloneBOOT Image related functions
error_t imageCheckHeader(ImageHeader *header);
error_t imageGetHeader(uint8_t *buffer, size_t bufferLen, ImageHeader **header);

#endif //!__IMAGE_H

/**
 * @file header.h
 * @brief App Image Builder image header managment
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

#ifndef __HEADER_H
#define __HEADER_H

//Dependencies
#ifdef IS_LINUX
#include <stdint-gcc.h>
#endif
#include <stdint.h>
#include <time.h>
#include "AppImageBuilderConfig.h"
#include "crc32.h"

//Image Header version
#define IMAGE_HEADER_VERSION (uint32_t)(((IMAGE_HEADER_VERSION_MAJOR & 0xFF) << 16) | ((IMAGE_HEADER_VERSION_MINOR & 0xFF) << 8) | (IMAGE_HEADER_VERSION_PATCH & 0xFF))
#define VERSION_32_BITS(major, minor, patch) (uint32_t)(((major&0xFF) << 16) | ((minor&0xFF) << 8) | (patch&0xFF))

#ifdef IS_WINDOWS

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
	uint8_t headCrc[CRC32_DIGEST_SIZE];       ///<Image header CRC32 integrity tag
} ImageHeader __end_packed;

//App Image builder headers related routines
int headerMake(ImageHeader* header, const char* input_binary_path, int imgIdx, const char* firmware_version, int internal, int img_encrypted);

#endif

#ifdef IS_LINUX
#undef __start_packed
#define __start_packed
#undef __end_packed
#define __end_packed __attribute__((__packed__))

/**
 * @brief Image header definition
 **/

typedef __start_packed struct
{
    uint32_t headVers;      ///<Image header version
    uint32_t imgIndex;      ///<Image index
    uint8_t imgType;        ///<Image type
    uint32_t dataPadding;   ///<Image data padding
    uint32_t dataSize;      ///<Image data size
    uint32_t dataVers;      ///<Image data version
    uint64_t imgTime;       ///<Image data generated time
    uint8_t reserved[31];   ///<Reserved field
    uint8_t headCrc[CRC32_DIGEST_SIZE];       ///<Image header CRC32 integrity tag
} __end_packed ImageHeader;

//App Image builder headers related routines
int headerMake(ImageHeader* header, const char* input_binary_path, int imgIdx, const char* firmware_version, int internal, int img_encrypted);

#endif

#endif

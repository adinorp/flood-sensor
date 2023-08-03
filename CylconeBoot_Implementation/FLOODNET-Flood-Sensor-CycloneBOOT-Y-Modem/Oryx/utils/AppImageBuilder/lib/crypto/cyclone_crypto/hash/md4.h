/**
 * @file md4.h
 * @brief MD4 (Message-Digest Algorithm)
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

#ifndef _MD4_H
#define _MD4_H

//Dependencies
#include "core/crypto.h"

//MD4 block size
#define MD4_BLOCK_SIZE 64
//MD4 digest size
#define MD4_DIGEST_SIZE 16
//Minimum length of the padding string
#define MD4_MIN_PAD_SIZE 9
//MD4 algorithm object identifier
#define MD4_OID md4Oid
//Common interface for hash algorithms
#define MD4_HASH_ALGO (&md4HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief MD4 algorithm context
 **/

typedef struct
{
   union
   {
      uint32_t h[4];
      uint8_t digest[16];
   };
   union
   {
      uint32_t x[16];
      uint8_t buffer[64];
   };
   size_t size;
   uint64_t totalSize;
} Md4Context;


//MD4 related constants
extern const uint8_t md4Oid[8];
extern const HashAlgo md4HashAlgo;

//MD4 related functions
error_t md4Compute(const void *data, size_t length, uint8_t *digest);
void md4Init(Md4Context *context);
void md4Update(Md4Context *context, const void *data, size_t length);
void md4Final(Md4Context *context, uint8_t *digest);
void md4ProcessBlock(Md4Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

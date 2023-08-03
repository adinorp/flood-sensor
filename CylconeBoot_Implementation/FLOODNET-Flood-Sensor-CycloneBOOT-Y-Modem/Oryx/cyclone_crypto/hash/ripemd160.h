/**
 * @file ripemd160.h
 * @brief RIPEMD-160 hash function
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

#ifndef _RIPEMD160_H
#define _RIPEMD160_H

//Dependencies
#include "core/crypto.h"

//RIPEMD-160 block size
#define RIPEMD160_BLOCK_SIZE 64
//RIPEMD-160 digest size
#define RIPEMD160_DIGEST_SIZE 20
//Minimum length of the padding string
#define RIPEMD160_MIN_PAD_SIZE 9
//RIPEMD-160 algorithm object identifier
#define RIPEMD160_OID ripemd160Oid
//Common interface for hash algorithms
#define RIPEMD160_HASH_ALGO (&ripemd160HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief RIPEMD-160 algorithm context
 **/

typedef struct
{
   union
   {
      uint32_t h[5];
      uint8_t digest[20];
   };
   union
   {
      uint32_t x[16];
      uint8_t buffer[64];
   };
   size_t size;
   uint64_t totalSize;
} Ripemd160Context;


//RIPEMD-160 related constants
extern const uint8_t ripemd160Oid[5];
extern const HashAlgo ripemd160HashAlgo;

//RIPEMD-160 related functions
error_t ripemd160Compute(const void *data, size_t length, uint8_t *digest);
void ripemd160Init(Ripemd160Context *context);
void ripemd160Update(Ripemd160Context *context, const void *data, size_t length);
void ripemd160Final(Ripemd160Context *context, uint8_t *digest);
void ripemd160ProcessBlock(Ripemd160Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

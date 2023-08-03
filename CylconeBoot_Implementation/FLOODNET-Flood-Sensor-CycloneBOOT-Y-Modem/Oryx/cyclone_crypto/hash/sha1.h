/**
 * @file sha1.h
 * @brief SHA-1 (Secure Hash Algorithm 1)
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

#ifndef _SHA1_H
#define _SHA1_H

//Dependencies
#include "core/crypto.h"

//Application specific context
#ifndef SHA1_PRIVATE_CONTEXT
   #define SHA1_PRIVATE_CONTEXT
#endif

//SHA-1 block size
#define SHA1_BLOCK_SIZE 64
//SHA-1 digest size
#define SHA1_DIGEST_SIZE 20
//Minimum length of the padding string
#define SHA1_MIN_PAD_SIZE 9
//SHA-1 algorithm object identifier
#define SHA1_OID sha1Oid
//Common interface for hash algorithms
#define SHA1_HASH_ALGO (&sha1HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHA-1 algorithm context
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
      uint32_t w[16];
      uint8_t buffer[64];
   };
   size_t size;
   uint64_t totalSize;
   SHA1_PRIVATE_CONTEXT
} Sha1Context;


//SHA-1 related constants
extern const uint8_t sha1Oid[5];
extern const HashAlgo sha1HashAlgo;

//SHA-1 related functions
error_t sha1Compute(const void *data, size_t length, uint8_t *digest);
void sha1Init(Sha1Context *context);
void sha1Update(Sha1Context *context, const void *data, size_t length);
void sha1Final(Sha1Context *context, uint8_t *digest);
void sha1FinalRaw(Sha1Context *context, uint8_t *digest);
void sha1ProcessBlock(Sha1Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif
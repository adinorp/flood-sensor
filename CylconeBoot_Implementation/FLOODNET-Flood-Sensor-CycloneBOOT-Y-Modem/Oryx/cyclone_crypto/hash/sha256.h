/**
 * @file sha256.h
 * @brief SHA-256 (Secure Hash Algorithm 256)
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

#ifndef _SHA256_H
#define _SHA256_H

//Dependencies
#include "core/crypto.h"

//Application specific context
#ifndef SHA256_PRIVATE_CONTEXT
   #define SHA256_PRIVATE_CONTEXT
#endif

//SHA-256 block size
#define SHA256_BLOCK_SIZE 64
//SHA-256 digest size
#define SHA256_DIGEST_SIZE 32
//Minimum length of the padding string
#define SHA256_MIN_PAD_SIZE 9
//SHA-256 algorithm object identifier
#define SHA256_OID sha256Oid
//Common interface for hash algorithms
#define SHA256_HASH_ALGO (&sha256HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHA-256 algorithm context
 **/

typedef struct
{
   union
   {
      uint32_t h[8];
      uint8_t digest[32];
   };
   union
   {
      uint32_t w[16];
      uint8_t buffer[64];
   };
   size_t size;
   uint64_t totalSize;
   SHA256_PRIVATE_CONTEXT
} Sha256Context;


//SHA-256 related constants
extern const uint8_t sha256Oid[9];
extern const HashAlgo sha256HashAlgo;

//SHA-256 related functions
error_t sha256Compute(const void *data, size_t length, uint8_t *digest);
void sha256Init(Sha256Context *context);
void sha256Update(Sha256Context *context, const void *data, size_t length);
void sha256Final(Sha256Context *context, uint8_t *digest);
void sha256FinalRaw(Sha256Context *context, uint8_t *digest);
void sha256ProcessBlock(Sha256Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

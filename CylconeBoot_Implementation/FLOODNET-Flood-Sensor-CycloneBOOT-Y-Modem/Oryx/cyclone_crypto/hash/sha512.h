/**
 * @file sha512.h
 * @brief SHA-512 (Secure Hash Algorithm 512)
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

#ifndef _SHA512_H
#define _SHA512_H

//Dependencies
#include "core/crypto.h"

//Application specific context
#ifndef SHA512_PRIVATE_CONTEXT
   #define SHA512_PRIVATE_CONTEXT
#endif

//SHA-512 block size
#define SHA512_BLOCK_SIZE 128
//SHA-512 digest size
#define SHA512_DIGEST_SIZE 64
//Minimum length of the padding string
#define SHA512_MIN_PAD_SIZE 17
//SHA-512 algorithm object identifier
#define SHA512_OID sha512Oid
//Common interface for hash algorithms
#define SHA512_HASH_ALGO (&sha512HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHA-512 algorithm context
 **/

typedef struct
{
   union
   {
      uint64_t h[8];
      uint8_t digest[64];
   };
   union
   {
      uint64_t w[16];
      uint8_t buffer[128];
   };
   size_t size;
   uint64_t totalSize;
   SHA512_PRIVATE_CONTEXT
} Sha512Context;


//SHA-512 related constants
extern const uint8_t sha512Oid[9];
extern const HashAlgo sha512HashAlgo;

//SHA-512 related functions
error_t sha512Compute(const void *data, size_t length, uint8_t *digest);
void sha512Init(Sha512Context *context);
void sha512Update(Sha512Context *context, const void *data, size_t length);
void sha512Final(Sha512Context *context, uint8_t *digest);
void sha512ProcessBlock(Sha512Context *context);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

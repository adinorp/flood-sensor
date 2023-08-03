/**
 * @file sha512_256.h
 * @brief SHA-512/256 (Secure Hash Algorithm)
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

#ifndef _SHA512_256_H
#define _SHA512_256_H

//Dependencies
#include "core/crypto.h"
#include "hash/sha512.h"

//SHA-512/256 block size
#define SHA512_256_BLOCK_SIZE 128
//SHA-512/256 digest size
#define SHA512_256_DIGEST_SIZE 32
//Minimum length of the padding string
#define SHA512_256_MIN_PAD_SIZE 17
//SHA-512/256 algorithm object identifier
#define SHA512_256_OID sha512_256Oid
//Common interface for hash algorithms
#define SHA512_256_HASH_ALGO (&sha512_256HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHA-512/256 algorithm context
 **/

typedef Sha512Context Sha512_256Context;


//SHA-512/256 related constants
extern const uint8_t sha512_256Oid[9];
extern const HashAlgo sha512_256HashAlgo;

//SHA-512/256 related functions
error_t sha512_256Compute(const void *data, size_t length, uint8_t *digest);
void sha512_256Init(Sha512_256Context *context);
void sha512_256Update(Sha512_256Context *context, const void *data, size_t length);
void sha512_256Final(Sha512_256Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

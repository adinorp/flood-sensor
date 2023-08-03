/**
 * @file sha512_224.h
 * @brief SHA-512/224 (Secure Hash Algorithm)
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

#ifndef _SHA512_224_H
#define _SHA512_224_H

//Dependencies
#include "core/crypto.h"
#include "hash/sha512.h"

//SHA-512/224 block size
#define SHA512_224_BLOCK_SIZE 128
//SHA-512/224 digest size
#define SHA512_224_DIGEST_SIZE 28
//Minimum length of the padding string
#define SHA512_224_MIN_PAD_SIZE 17
//SHA-512/224 algorithm object identifier
#define SHA512_224_OID sha512_224Oid
//Common interface for hash algorithms
#define SHA512_224_HASH_ALGO (&sha512_224HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHA-512/224 algorithm context
 **/

typedef Sha512Context Sha512_224Context;


//SHA-512/224 related constants
extern const uint8_t sha512_224Oid[9];
extern const HashAlgo sha512_224HashAlgo;

//SHA-512/224 related functions
error_t sha512_224Compute(const void *data, size_t length, uint8_t *digest);
void sha512_224Init(Sha512_224Context *context);
void sha512_224Update(Sha512_224Context *context, const void *data, size_t length);
void sha512_224Final(Sha512_224Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

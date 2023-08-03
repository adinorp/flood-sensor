/**
 * @file sha224.h
 * @brief SHA-224 (Secure Hash Algorithm 224)
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

#ifndef _SHA224_H
#define _SHA224_H

//Dependencies
#include "core/crypto.h"
#include "hash/sha256.h"

//SHA-224 block size
#define SHA224_BLOCK_SIZE 64
//SHA-224 digest size
#define SHA224_DIGEST_SIZE 28
//Minimum length of the padding string
#define SHA224_MIN_PAD_SIZE 9
//SHA-224 algorithm object identifier
#define SHA224_OID sha224Oid
//Common interface for hash algorithms
#define SHA224_HASH_ALGO (&sha224HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHA-224 algorithm context
 **/

typedef Sha256Context Sha224Context;


//SHA-224 related constants
extern const uint8_t sha224Oid[9];
extern const HashAlgo sha224HashAlgo;

//SHA-224 related functions
error_t sha224Compute(const void *data, size_t length, uint8_t *digest);
void sha224Init(Sha224Context *context);
void sha224Update(Sha224Context *context, const void *data, size_t length);
void sha224Final(Sha224Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

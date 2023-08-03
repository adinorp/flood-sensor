/**
 * @file sha3_224.h
 * @brief SHA3-224 hash function (SHA-3 with 224-bit output)
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

#ifndef _SHA3_224_H
#define _SHA3_224_H

//Dependencies
#include "core/crypto.h"
#include "xof/keccak.h"

//SHA3-224 block size
#define SHA3_224_BLOCK_SIZE 144
//SHA3-224 digest size
#define SHA3_224_DIGEST_SIZE 28
//Minimum length of the padding string
#define SHA3_224_MIN_PAD_SIZE 1
//SHA3-224 algorithm object identifier
#define SHA3_224_OID sha3_224Oid
//Common interface for hash algorithms
#define SHA3_224_HASH_ALGO (&sha3_224HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief SHA3-224 algorithm context
 **/

typedef KeccakContext Sha3_224Context;


//SHA3-224 related constants
extern const uint8_t sha3_224Oid[9];
extern const HashAlgo sha3_224HashAlgo;

//SHA3-224 related functions
error_t sha3_224Compute(const void *data, size_t length, uint8_t *digest);
void sha3_224Init(Sha3_224Context *context);
void sha3_224Update(Sha3_224Context *context, const void *data, size_t length);
void sha3_224Final(Sha3_224Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

/**
 * @file blake2s224.h
 * @brief BLAKE2s-224 hash function
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

#ifndef _BLAKE2S224_H
#define _BLAKE2S224_H

//Dependencies
#include "core/crypto.h"
#include "hash/blake2s.h"

//BLAKE2s-224 block size
#define BLAKE2S224_BLOCK_SIZE 64
//BLAKE2s-224 digest size
#define BLAKE2S224_DIGEST_SIZE 28
//Minimum length of the padding string
#define BLAKE2S224_MIN_PAD_SIZE 0
//BLAKE2s-224 algorithm object identifier
#define BLAKE2S224_OID blake2s224Oid
//Common interface for hash algorithms
#define BLAKE2S224_HASH_ALGO (&blake2s224HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief BLAKE2s-224 algorithm context
 **/

typedef Blake2sContext Blake2s224Context;


//BLAKE2s-224 related constants
extern const uint8_t blake2s224Oid[11];
extern const HashAlgo blake2s224HashAlgo;

//BLAKE2s-224 related functions
error_t blake2s224Compute(const void *data, size_t length, uint8_t *digest);
void blake2s224Init(Blake2s224Context *context);
void blake2s224Update(Blake2s224Context *context, const void *data, size_t length);
void blake2s224Final(Blake2s224Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

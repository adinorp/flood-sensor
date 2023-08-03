/**
 * @file blake2s160.h
 * @brief BLAKE2s-160 hash function
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

#ifndef _BLAKE2S160_H
#define _BLAKE2S160_H

//Dependencies
#include "core/crypto.h"
#include "hash/blake2s.h"

//BLAKE2s-160 block size
#define BLAKE2S160_BLOCK_SIZE 64
//BLAKE2s-160 digest size
#define BLAKE2S160_DIGEST_SIZE 20
//Minimum length of the padding string
#define BLAKE2S160_MIN_PAD_SIZE 0
//BLAKE2s-160 algorithm object identifier
#define BLAKE2S160_OID blake2s160Oid
//Common interface for hash algorithms
#define BLAKE2S160_HASH_ALGO (&blake2s160HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief BLAKE2s-160 algorithm context
 **/

typedef Blake2sContext Blake2s160Context;


//BLAKE2s-160 related constants
extern const uint8_t blake2s160Oid[11];
extern const HashAlgo blake2s160HashAlgo;

//BLAKE2s-160 related functions
error_t blake2s160Compute(const void *data, size_t length, uint8_t *digest);
void blake2s160Init(Blake2s160Context *context);
void blake2s160Update(Blake2s160Context *context, const void *data, size_t length);
void blake2s160Final(Blake2s160Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

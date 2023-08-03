/**
 * @file blake2s256.h
 * @brief BLAKE2s-256 hash function
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

#ifndef _BLAKE2S256_H
#define _BLAKE2S256_H

//Dependencies
#include "core/crypto.h"
#include "hash/blake2s.h"

//BLAKE2s-256 block size
#define BLAKE2S256_BLOCK_SIZE 64
//BLAKE2s-256 digest size
#define BLAKE2S256_DIGEST_SIZE 32
//Minimum length of the padding string
#define BLAKE2S256_MIN_PAD_SIZE 0
//BLAKE2s-256 algorithm object identifier
#define BLAKE2S256_OID blake2s256Oid
//Common interface for hash algorithms
#define BLAKE2S256_HASH_ALGO (&blake2s256HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief BLAKE2s-256 algorithm context
 **/

typedef Blake2sContext Blake2s256Context;


//BLAKE2s-256 related constants
extern const uint8_t blake2s256Oid[11];
extern const HashAlgo blake2s256HashAlgo;

//BLAKE2s-256 related functions
error_t blake2s256Compute(const void *data, size_t length, uint8_t *digest);
void blake2s256Init(Blake2s256Context *context);
void blake2s256Update(Blake2s256Context *context, const void *data, size_t length);
void blake2s256Final(Blake2s256Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

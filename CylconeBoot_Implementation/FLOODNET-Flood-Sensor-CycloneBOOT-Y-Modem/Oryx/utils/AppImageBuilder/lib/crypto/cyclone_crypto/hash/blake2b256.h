/**
 * @file blake2b256.h
 * @brief BLAKE2b-256 hash function
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

#ifndef _BLAKE2B256_H
#define _BLAKE2B256_H

//Dependencies
#include "core/crypto.h"
#include "hash/blake2b.h"

//BLAKE2b-256 block size
#define BLAKE2B256_BLOCK_SIZE 128
//BLAKE2b-256 digest size
#define BLAKE2B256_DIGEST_SIZE 32
//Minimum length of the padding string
#define BLAKE2B256_MIN_PAD_SIZE 0
//BLAKE2b-256 algorithm object identifier
#define BLAKE2B256_OID blake2b256Oid
//Common interface for hash algorithms
#define BLAKE2B256_HASH_ALGO (&blake2b256HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief BLAKE2b-256 algorithm context
 **/

typedef Blake2bContext Blake2b256Context;


//BLAKE2b-256 related constants
extern const uint8_t blake2b256Oid[11];
extern const HashAlgo blake2b256HashAlgo;

//BLAKE2b-256 related functions
error_t blake2b256Compute(const void *data, size_t length, uint8_t *digest);
void blake2b256Init(Blake2b256Context *context);
void blake2b256Update(Blake2b256Context *context, const void *data, size_t length);
void blake2b256Final(Blake2b256Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

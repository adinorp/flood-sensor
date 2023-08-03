/**
 * @file blake2b160.h
 * @brief BLAKE2b-160 hash function
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

#ifndef _BLAKE2B160_H
#define _BLAKE2B160_H

//Dependencies
#include "core/crypto.h"
#include "hash/blake2b.h"

//BLAKE2b-160 block size
#define BLAKE2B160_BLOCK_SIZE 128
//BLAKE2b-160 digest size
#define BLAKE2B160_DIGEST_SIZE 20
//Minimum length of the padding string
#define BLAKE2B160_MIN_PAD_SIZE 0
//BLAKE2b-160 algorithm object identifier
#define BLAKE2B160_OID blake2b160Oid
//Common interface for hash algorithms
#define BLAKE2B160_HASH_ALGO (&blake2b160HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief BLAKE2b-160 algorithm context
 **/

typedef Blake2bContext Blake2b160Context;


//BLAKE2b-160 related constants
extern const uint8_t blake2b160Oid[11];
extern const HashAlgo blake2b160HashAlgo;

//BLAKE2b-160 related functions
error_t blake2b160Compute(const void *data, size_t length, uint8_t *digest);
void blake2b160Init(Blake2b160Context *context);
void blake2b160Update(Blake2b160Context *context, const void *data, size_t length);
void blake2b160Final(Blake2b160Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

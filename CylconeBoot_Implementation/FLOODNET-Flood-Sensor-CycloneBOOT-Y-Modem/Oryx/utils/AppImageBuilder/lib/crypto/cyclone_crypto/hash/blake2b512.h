/**
 * @file blake2b512.h
 * @brief BLAKE2b-512 hash function
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

#ifndef _BLAKE2B512_H
#define _BLAKE2B512_H

//Dependencies
#include "core/crypto.h"
#include "hash/blake2b.h"

//BLAKE2b-512 block size
#define BLAKE2B512_BLOCK_SIZE 128
//BLAKE2b-512 digest size
#define BLAKE2B512_DIGEST_SIZE 64
//Minimum length of the padding string
#define BLAKE2B512_MIN_PAD_SIZE 0
//BLAKE2b-512 algorithm object identifier
#define BLAKE2B512_OID blake2b512Oid
//Common interface for hash algorithms
#define BLAKE2B512_HASH_ALGO (&blake2b512HashAlgo)

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief BLAKE2b-512 algorithm context
 **/

typedef Blake2bContext Blake2b512Context;


//BLAKE2b-512 related constants
extern const uint8_t blake2b512Oid[11];
extern const HashAlgo blake2b512HashAlgo;

//BLAKE2b-512 related functions
error_t blake2b512Compute(const void *data, size_t length, uint8_t *digest);
void blake2b512Init(Blake2b512Context *context);
void blake2b512Update(Blake2b512Context *context, const void *data, size_t length);
void blake2b512Final(Blake2b512Context *context, uint8_t *digest);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

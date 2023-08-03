/**
 * @file blake2s224.c
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

//Switch to the appropriate trace level
#define TRACE_LEVEL CRYPTO_TRACE_LEVEL

//Dependencies
#include "core/crypto.h"
#include "hash/blake2s224.h"

//Check crypto library configuration
#if (BLAKE2S224_SUPPORT == ENABLED)

//BLAKE2s-224 object identifier (1.3.6.1.4.1.1722.12.2.2.7)
const uint8_t blake2s224Oid[11] = {0x43, 0x06, 0x01, 0x04, 0x01, 0x8D, 0x3A, 0x0C, 0x02, 0x02, 0x07};

//Common interface for hash algorithms
const HashAlgo blake2s224HashAlgo =
{
   "BLAKE2s-224",
   blake2s224Oid,
   sizeof(blake2s224Oid),
   sizeof(Blake2s224Context),
   BLAKE2S224_BLOCK_SIZE,
   BLAKE2S224_DIGEST_SIZE,
   BLAKE2S224_MIN_PAD_SIZE,
   FALSE,
   (HashAlgoCompute) blake2s224Compute,
   (HashAlgoInit) blake2s224Init,
   (HashAlgoUpdate) blake2s224Update,
   (HashAlgoFinal) blake2s224Final,
   NULL
};


/**
 * @brief Digest a message using BLAKE2s-224
 * @param[in] data Pointer to the message being hashed
 * @param[in] length Length of the message
 * @param[out] digest Pointer to the calculated digest
 * @return Error code
 **/

error_t blake2s224Compute(const void *data, size_t length, uint8_t *digest)
{
   //Compute the unkeyed hash with BLAKE2s-224
   return blake2sCompute(NULL, 0, data, length, digest, BLAKE2S224_DIGEST_SIZE);
}


/**
 * @brief Initialize BLAKE2s-224 hash computation
 * @param[in] context Pointer to the BLAKE2s context to initialize
 **/

void blake2s224Init(Blake2s224Context *context)
{
   //Initialize the hashing context
   blake2sInit(context, NULL, 0, BLAKE2S224_DIGEST_SIZE);
}


/**
 * @brief Update BLAKE2s-224 hash computation
 * @param[in] context Pointer to the BLAKE2s context
 * @param[in] data Pointer to the buffer being hashed
 * @param[in] length Length of the buffer
 **/

void blake2s224Update(Blake2s224Context *context, const void *data, size_t length)
{
   //Digest the data
   blake2sUpdate(context, data, length);
}


/**
 * @brief Finish BLAKE2s-224 hash computation
 * @param[in] context Pointer to the BLAKE2s context
 * @param[out] digest Calculated digest (optional parameter)
 **/

void blake2s224Final(Blake2s224Context *context, uint8_t *digest)
{
   //Generate the message digest
   blake2sFinal(context, digest);
}

#endif

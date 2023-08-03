/**
 * @file saml11_crypto_hash.c
 * @brief SAML11 hash hardware accelerator
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
#include "sam.h"
#include "core/crypto.h"
#include "hardware/saml11/saml11_crypto.h"
#include "hardware/saml11/saml11_crypto_hash.h"
#include "hash/hash_algorithms.h"
#include "debug.h"

//Check crypto library configuration
#if (SAML11_CRYPTO_HASH_SUPPORT == ENABLED && SHA256_SUPPORT == ENABLED)


/**
 * @brief Process message in 16-word blocks
 * @param[in] context Pointer to the SHA-256 context
 **/

void sha256ProcessBlock(Sha256Context *context)
{
   static uint32_t buffer[64];

   //Acquire exclusive access to the CRYA module
   osAcquireMutex(&saml11CryptoMutex);
   //Accelerate SHA-256 inner compression loop
   crya_sha_process(context->h, context->buffer, buffer);
   //Release exclusive access to the CRYA module
   osReleaseMutex(&saml11CryptoMutex);
}

#endif

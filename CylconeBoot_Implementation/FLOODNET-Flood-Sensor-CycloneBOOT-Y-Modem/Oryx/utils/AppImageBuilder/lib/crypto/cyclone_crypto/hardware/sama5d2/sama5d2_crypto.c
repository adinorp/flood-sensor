/**
 * @file sama5d2_crypto.c
 * @brief SAMA5D2 hardware cryptographic accelerator
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
#include "chip.h"
#include "core/crypto.h"
#include "hardware/sama5d2/sama5d2_crypto.h"
#include "hardware/sama5d2/sama5d2_crypto_trng.h"
#include "hardware/sama5d2/sama5d2_crypto_hash.h"
#include "hardware/sama5d2/sama5d2_crypto_cipher.h"
#include "debug.h"

//Global variables
OsMutex sama5d2CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t sama5d2CryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&sama5d2CryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

#if (SAMA5D2_CRYPTO_TRNG_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize TRNG module
      error = trngInit();
   }
#endif

#if (SAMA5D2_CRYPTO_HASH_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Enable SHA peripheral clock
      PMC->PMC_PCER0 = (1 << ID_SHA);
   }
#endif

#if (SAMA5D2_CRYPTO_CIPHER_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Enable AES and TDES peripheral clocks
      PMC->PMC_PCER0 = (1 << ID_AES) | (1 << ID_TDES);
   }
#endif

   //Return status code
   return error;
}

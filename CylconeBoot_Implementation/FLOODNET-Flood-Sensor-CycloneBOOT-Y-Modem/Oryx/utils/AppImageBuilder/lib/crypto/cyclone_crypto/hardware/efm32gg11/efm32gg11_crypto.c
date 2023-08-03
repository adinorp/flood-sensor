/**
 * @file efm32gg11_crypto.c
 * @brief EFM32 Giant Gecko 11 hardware cryptographic accelerator
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
#include "em_device.h"
#include "em_cmu.h"
#include "core/crypto.h"
#include "hardware/efm32gg11/efm32gg11_crypto.h"
#include "hardware/efm32gg11/efm32gg11_crypto_trng.h"
#include "hardware/efm32gg11/efm32gg11_crypto_hash.h"
#include "hardware/efm32gg11/efm32gg11_crypto_cipher.h"
#include "hardware/efm32gg11/efm32gg11_crypto_pkc.h"
#include "debug.h"

//Global variables
OsMutex efm32gg11CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t efm32gg11CryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&efm32gg11CryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

#if (EFM32GG11_CRYPTO_TRNG_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize TRNG module
      error = trngInit();
   }
#endif

#if (EFM32GG11_CRYPTO_HASH_SUPPORT == ENABLED || \
   EFM32GG11_CRYPTO_CIPHER_SUPPORT == ENABLED || \
   EFM32GG11_CRYPTO_PKC_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Enable CRYPTO clock
      CMU_ClockEnable(cmuClock_CRYPTO0, true);
   }
#endif

   //Return status code
   return error;
}

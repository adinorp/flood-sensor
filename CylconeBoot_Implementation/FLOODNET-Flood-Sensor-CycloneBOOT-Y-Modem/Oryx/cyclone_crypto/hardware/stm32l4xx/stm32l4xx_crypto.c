/**
 * @file stm32l4xx_crypto.c
 * @brief STM32L4 hardware cryptographic accelerator
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
#include "hardware/stm32l4xx/stm32l4xx_crypto.h"
#include "hardware/stm32l4xx/stm32l4xx_crypto_trng.h"
#include "hardware/stm32l4xx/stm32l4xx_crypto_hash.h"
#include "hardware/stm32l4xx/stm32l4xx_crypto_cipher.h"
#include "debug.h"

//Global variables
OsMutex stm32l4xxCryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t stm32l4xxCryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&stm32l4xxCryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

#if (STM32L4XX_CRYPTO_TRNG_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize TRNG module
      error = trngInit();
   }
#endif

#if (STM32L4XX_CRYPTO_HASH_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize HASH module
      error = hashInit();
   }
#endif

#if (STM32L4XX_CRYPTO_CIPHER_SUPPORT == ENABLED && AES_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize CRYP module
      error = crypInit();
   }
#endif

   //Return status code
   return error;
}
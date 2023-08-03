/**
 * @file same53_crypto.c
 * @brief SAME53 hardware cryptographic accelerator
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
#include "hardware/same53/same53_crypto.h"
#include "hardware/same53/same53_crypto_trng.h"
#include "hardware/same53/same53_crypto_hash.h"
#include "hardware/same53/same53_crypto_cipher.h"
#include "hardware/same53/same53_crypto_pkc.h"
#include "debug.h"

//Global variables
OsMutex same53CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t same53CryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&same53CryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

#if (SAME53_CRYPTO_TRNG_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize TRNG module
      error = trngInit();
   }
#endif

#if (SAME53_CRYPTO_HASH_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Enable ICM bus clocks (CLK_ICM_APB and CLK_ICM_AHB)
      MCLK_REGS->MCLK_APBCMASK |= MCLK_APBCMASK_ICM_Msk;
      MCLK_REGS->MCLK_AHBMASK |= MCLK_AHBMASK_ICM_Msk;
   }
#endif

#if (SAME53_CRYPTO_CIPHER_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Enable AES bus clock (CLK_AES_APB)
      MCLK_REGS->MCLK_APBCMASK |= MCLK_APBCMASK_AES_Msk;
   }
#endif

#if (SAME53_CRYPTO_PKC_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize public key accelerator
      error = pukccInit();
   }
#endif

   //Return status code
   return error;
}

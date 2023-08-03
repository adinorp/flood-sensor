/**
 * @file sam9x60_crypto.c
 * @brief SAM9X60 hardware cryptographic accelerator
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
#include "sam9x60.h"
#include "core/crypto.h"
#include "hardware/sam9x60/sam9x60_crypto.h"
#include "hardware/sam9x60/sam9x60_crypto_trng.h"
#include "hardware/sam9x60/sam9x60_crypto_hash.h"
#include "hardware/sam9x60/sam9x60_crypto_cipher.h"
#include "debug.h"

//Global variables
OsMutex sam9x60CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t sam9x60CryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&sam9x60CryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

#if (SAM9X60_CRYPTO_TRNG_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize TRNG module
      error = trngInit();
   }
#endif

#if (SAM9X60_CRYPTO_HASH_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      uint32_t temp;

      //Enable SHA peripheral clock
      PMC->PMC_PCR = PMC_PCR_PID(ID_SHA);
      temp = PMC->PMC_PCR;
      PMC->PMC_PCR = temp | PMC_PCR_CMD | PMC_PCR_EN;
   }
#endif

#if (SAM9X60_CRYPTO_CIPHER_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      uint32_t temp;

      //Enable AES peripheral clock
      PMC->PMC_PCR = PMC_PCR_PID(ID_AES);
      temp = PMC->PMC_PCR;
      PMC->PMC_PCR = temp | PMC_PCR_CMD | PMC_PCR_EN;

      //Enable TDES peripheral clock
      PMC->PMC_PCR = PMC_PCR_PID(ID_TDES);
      temp = PMC->PMC_PCR;
      PMC->PMC_PCR = temp | PMC_PCR_CMD | PMC_PCR_EN;
   }
#endif

   //Return status code
   return error;
}

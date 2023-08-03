/**
 * @file sam4l_crypto.c
 * @brief SAM4L hardware cryptographic accelerator
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
#include "sam4l.h"
#include "core/crypto.h"
#include "hardware/sam4l/sam4l_crypto_trng.h"
#include "hardware/sam4l/sam4l_crypto.h"
#include "hardware/sam4l/sam4l_crypto_cipher.h"
#include "debug.h"

//Global variables
OsMutex sam4lCryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t sam4lCryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&sam4lCryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

#if (SAM4L_CRYPTO_TRNG_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize TRNG module
      error = trngInit();
   }
#endif

#if (SAM4L_CRYPTO_CIPHER_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Disable write protect
      PM->PM_UNLOCK = PM_UNLOCK_KEY(0xAAU) |
         PM_UNLOCK_ADDR((uint32_t) &PM->PM_HSBMASK - (uint32_t) PM);

      //Enable AES peripheral clock
      PM->PM_HSBMASK |= PM_HSBMASK_AESA;
   }
#endif

   //Return status code
   return error;
}

/**
 * @file efm32gg11_crypto_trng.c
 * @brief EFM32 Giant Gecko 11 true random number generator
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
#include "debug.h"

//Check crypto library configuration
#if (EFM32GG11_CRYPTO_TRNG_SUPPORT == ENABLED)


/**
 * @brief TRNG module initialization
 * @return Error code
 **/

error_t trngInit(void)
{
   //Enable TRNG clock
   CMU_ClockEnable(cmuClock_TRNG0, true);
   //Enable RNG
   TRNG0->CONTROL = TRNG_CONTROL_ENABLE;

   //Successful initialization
   return NO_ERROR;
}


/**
 * @brief Get random data from the TRNG module
 * @param[out] data Buffer where to store random data
 * @param[in] length Number of random bytes to generate
 **/

error_t trngGetRandomData(uint8_t *data, size_t length)
{
   size_t i;
   uint32_t value;

   //Acquire exclusive access to the TRNG module
   osAcquireMutex(&efm32gg11CryptoMutex);

   //Generate random data
   for(i = 0; i < length; i++)
   {
      //Generate a new 32-bit random value when necessary
      if((i % 4) == 0)
      {
         //Wait for the TRNG to contain a valid data
         while(TRNG0->FIFOLEVEL == 0)
         {
         }

         //Get 32-bit random value
         value = TRNG0->FIFO;
      }

      //Copy random byte
      data[i] = value & 0xFF;
      //Shift the 32-bit random value
      value >>= 8;
   }

   //Release exclusive access to the TRNG module
   osReleaseMutex(&efm32gg11CryptoMutex);

   //Successful processing
   return NO_ERROR;
}

#endif

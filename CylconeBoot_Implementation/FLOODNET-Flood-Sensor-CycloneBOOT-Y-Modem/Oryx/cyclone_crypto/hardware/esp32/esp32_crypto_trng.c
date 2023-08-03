/**
 * @file esp32_crypto_trng.c
 * @brief ESP32 true random number generator
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
#include "esp_system.h"
#include "driver/periph_ctrl.h"
#include "core/crypto.h"
#include "hardware/esp32/esp32_crypto.h"
#include "hardware/esp32/esp32_crypto_trng.h"
#include "debug.h"

//Check crypto library configuration
#if (ESP32_CRYPTO_TRNG_SUPPORT == ENABLED)


/**
 * @brief RNG module initialization
 **/

void esp32RngInit(void)
{
   //Enable RNG module
   periph_module_enable(PERIPH_RNG_MODULE);
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

   //Initialize variable
   value = 0;

   //Acquire exclusive access to the RNG module
   osAcquireMutex(&esp32CryptoMutex);

   //Generate random data
   for(i = 0; i < length; i++)
   {
      //Generate a new 32-bit random value when necessary
      if((i % 4) == 0)
      {
         //Get the 32-bit random value
         value = esp_random();
      }

      //Copy random byte
      data[i] = value & 0xFF;
      //Shift the 32-bit random value
      value >>= 8;
   }

   //Release exclusive access to the RNG module
   osReleaseMutex(&esp32CryptoMutex);

   //Successful processing
   return NO_ERROR;
}

#endif

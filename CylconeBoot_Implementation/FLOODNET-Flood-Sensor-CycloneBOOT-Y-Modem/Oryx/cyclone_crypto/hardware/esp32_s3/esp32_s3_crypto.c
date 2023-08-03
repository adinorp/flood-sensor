/**
 * @file esp32_s3_crypto.c
 * @brief ESP32-S3 hardware cryptographic accelerator
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
#include "driver/periph_ctrl.h"
#include "core/crypto.h"
#include "hardware/esp32_s3/esp32_s3_crypto.h"
#include "hardware/esp32_s3/esp32_s3_crypto_trng.h"
#include "hardware/esp32_s3/esp32_s3_crypto_hash.h"
#include "hardware/esp32_s3/esp32_s3_crypto_cipher.h"
#include "hardware/esp32_s3/esp32_s3_crypto_pkc.h"
#include "debug.h"

//Global variables
OsMutex esp32s3CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t esp32s3CryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&esp32s3CryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

   //Check status code
   if(!error)
   {
#if (ESP32_S3_CRYPTO_TRNG_SUPPORT == ENABLED)
      //Initialize RNG module
      esp32s3RngInit();
#endif

#if (ESP32_S3_CRYPTO_HASH_SUPPORT == ENABLED)
      //Initialize SHA module
      esp32s3ShaInit();
#endif

#if (ESP32_S3_CRYPTO_CIPHER_SUPPORT == ENABLED && AES_SUPPORT == ENABLED)
      //Initialize AES module
      esp32s3AesInit();
#endif

#if (ESP32_S3_CRYPTO_PKC_SUPPORT == ENABLED)
      //Initialize RSA module
      esp32s3RsaInit();
#endif
   }

   //Return status code
   return error;
}
/**
 * @file mimxrt1060_crypto.c
 * @brief i.MX RT1060 hardware cryptographic accelerator (DCP)
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
#include "fsl_device_registers.h"
#include "fsl_dcp.h"
#include "core/crypto.h"
#include "hardware/mimxrt1060/mimxrt1060_crypto.h"
#include "hardware/mimxrt1060/mimxrt1060_crypto_trng.h"
#include "debug.h"

//Global variables
OsMutex mimxrt1060CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t mimxrt1060CryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&mimxrt1060CryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

#if (MIMXRT1060_CRYPTO_TRNG_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      //Initialize TRNG module
      error = trngInit();
   }
#endif

#if (MIMXRT1060_CRYPTO_HASH_SUPPORT == ENABLED || \
   MIMXRT1060_CRYPTO_CIPHER_SUPPORT == ENABLED)
   //Check status code
   if(!error)
   {
      dcp_config_t dcpConfig;

      //Initialize DCP module
      DCP_GetDefaultConfig(&dcpConfig);
      DCP_Init(DCP, &dcpConfig);
   }
#endif

   //Return status code
   return error;
}

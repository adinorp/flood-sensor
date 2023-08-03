/**
 * @file mimxrt1020_crypto_trng.c
 * @brief i.MX RT1020 true random number generator
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
#include "fsl_trng.h"
#include "core/crypto.h"
#include "hardware/mimxrt1020/mimxrt1020_crypto.h"
#include "hardware/mimxrt1020/mimxrt1020_crypto_trng.h"
#include "debug.h"

//Check crypto library configuration
#if (MIMXRT1020_CRYPTO_TRNG_SUPPORT == ENABLED)


/**
 * @brief TRNG module initialization
 * @return Error code
 **/

error_t trngInit(void)
{
   status_t status;
   trng_config_t trngConfig;

   //Enable TRNG peripheral clock
   CLOCK_EnableClock(kCLOCK_Trng);

   //Get default TRNG configuration
   TRNG_GetDefaultConfig(&trngConfig);
   //Initialize TRNG
   status = TRNG_Init(TRNG, &trngConfig);

   //Return status code
   return (status == kStatus_Success) ? NO_ERROR : ERROR_FAILURE;
}


/**
 * @brief Get random data from the TRNG module
 * @param[out] data Buffer where to store random data
 * @param[in] length Number of random bytes to generate
 **/

error_t trngGetRandomData(uint8_t *data, size_t length)
{
   status_t status;

   //Acquire exclusive access to the TRNG module
   osAcquireMutex(&mimxrt1020CryptoMutex);

   //Generate random data
   status = TRNG_GetRandomData(TRNG, data, length);

   //Release exclusive access to the TRNG module
   osReleaseMutex(&mimxrt1020CryptoMutex);

   //Return status code
   return (status == kStatus_Success) ? NO_ERROR : ERROR_FAILURE;
}

#endif

/**
 * @file mk6x_crypto_trng.c
 * @brief Kinetis K6x true random number generator
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
#include "fsl_clock.h"
#include "fsl_rnga.h"
#include "core/crypto.h"
#include "hardware/mk6x/mk6x_crypto.h"
#include "hardware/mk6x/mk6x_crypto_trng.h"
#include "debug.h"

//Check crypto library configuration
#if (MK6X_CRYPTO_TRNG_SUPPORT == ENABLED)


/**
 * @brief TRNG module initialization
 * @return Error code
 **/

error_t trngInit(void)
{
   //Enable RNGA peripheral clock
   CLOCK_EnableClock(kCLOCK_Rnga0);

   //Initialize RNGA
   RNGA_Init(RNG);

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
   status_t status;

   //Acquire exclusive access to the RNGA module
   osAcquireMutex(&mk6xCryptoMutex);
   //Generate random data
   status = RNGA_GetRandomData(RNG, data, length);
   //Release exclusive access to the RNGA module
   osReleaseMutex(&mk6xCryptoMutex);

   //Return status code
   return (status == kStatus_Success) ? NO_ERROR : ERROR_FAILURE;
}

#endif

/**
 * @file mimxrt1170_crypto_trng.c
 * @brief i.MX RT1170 true random number generator
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
#include "fsl_caam.h"
#include "core/crypto.h"
#include "hardware/mimxrt1170/mimxrt1170_crypto.h"
#include "hardware/mimxrt1170/mimxrt1170_crypto_trng.h"
#include "debug.h"

//Check crypto library configuration
#if (MIMXRT1170_CRYPTO_TRNG_SUPPORT == ENABLED)


/**
 * @brief Get random data from the TRNG module
 * @param[out] data Buffer where to store random data
 * @param[in] length Number of random bytes to generate
 **/

error_t trngGetRandomData(uint8_t *data, size_t length)
{
   status_t status;
   caam_handle_t caamHandle;

   //Acquire exclusive access to the CAAM module
   osAcquireMutex(&mimxrt1170CryptoMutex);

   //Set CAAM job ring
   caamHandle.jobRing = kCAAM_JobRing0;

   //Generate random data
   status = CAAM_RNG_GetRandomData(CAAM, &caamHandle, kCAAM_RngStateHandle0,
      data, length, kCAAM_RngDataAny, NULL);

   //Release exclusive access to the CAAM module
   osReleaseMutex(&mimxrt1170CryptoMutex);

   //Return status code
   return (status == kStatus_Success) ? NO_ERROR : ERROR_FAILURE;
}

#endif

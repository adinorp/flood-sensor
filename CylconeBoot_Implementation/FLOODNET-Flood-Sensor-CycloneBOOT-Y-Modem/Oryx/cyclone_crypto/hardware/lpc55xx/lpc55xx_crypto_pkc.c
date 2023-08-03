/**
 * @file lpc55xx_crypto_pkc.c
 * @brief LPC5500 public-key hardware accelerator
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
#include "fsl_casper.h"
#include "core/crypto.h"
#include "hardware/lpc55xx/lpc55xx_crypto.h"
#include "hardware/lpc55xx/lpc55xx_crypto_pkc.h"
#include "ecc/ec.h"
#include "debug.h"

//Check crypto library configuration
#if (LPC55XX_CRYPTO_PKC_SUPPORT == ENABLED)

//Global variables
static Lpc55xxEcArgs ecArgs;


/**
 * @brief Scalar multiplication
 * @param[in] params EC domain parameters
 * @param[out] r Resulting point R = d.S
 * @param[in] d An integer d such as 0 <= d < p
 * @param[in] s EC point
 * @return Error code
 **/

error_t ecMult(const EcDomainParameters *params, EcPoint *r, const Mpi *d,
   const EcPoint *s)
{
   error_t error;
   size_t n;

   //Initialize status code
   error = NO_ERROR;

   //Check elliptic curve parameters
   if(!osStrcmp(params->name, "secp256r1"))
   {
      n = 32;
   }
   else if(!osStrcmp(params->name, "secp384r1"))
   {
      n = 48;
   }
   else if(!osStrcmp(params->name, "secp521r1"))
   {
      n = 72;
   }
   else
   {
      return ERROR_FAILURE;
   }

   //Acquire exclusive access to the CASPER module
   osAcquireMutex(&lpc55xxCryptoMutex);

   //Set scalar value
   mpiExport(d, (uint8_t *) ecArgs.d, n, MPI_FORMAT_LITTLE_ENDIAN);

   //Set input point
   mpiExport(&s->x, (uint8_t *) ecArgs.sx, n, MPI_FORMAT_LITTLE_ENDIAN);
   mpiExport(&s->y, (uint8_t *) ecArgs.sy, n, MPI_FORMAT_LITTLE_ENDIAN);

   //Initialize curve parameters in CASPER memory
   if(n == 32)
   {
      CASPER_ecc_init(kCASPER_ECC_P256);
   }
   else if(n == 48)
   {
      CASPER_ecc_init(kCASPER_ECC_P384);
   }
   else
   {
      CASPER_ecc_init(kCASPER_ECC_P521);
   }

   //Perform scalar multiplication
   if(n == 32)
   {
      CASPER_ECC_SECP256R1_Mul(CASPER, ecArgs.rx, ecArgs.ry, ecArgs.sx,
         ecArgs.sy, ecArgs.d);
   }
   else if(n == 48)
   {
      CASPER_ECC_SECP384R1_Mul(CASPER, ecArgs.rx, ecArgs.ry, ecArgs.sx,
         ecArgs.sy, ecArgs.d);
   }
   else
   {
      CASPER_ECC_SECP521R1_Mul(CASPER, ecArgs.rx, ecArgs.ry, ecArgs.sx,
         ecArgs.sy, ecArgs.d);
   }

   //Copy the x-coordinate of the result
   error = mpiImport(&r->x, (uint8_t *) ecArgs.rx, n,
      MPI_FORMAT_LITTLE_ENDIAN);

   //Check status code
   if(!error)
   {
      //Copy the y-coordinate of the result
      error = mpiImport(&r->y, (uint8_t *) ecArgs.ry, n,
         MPI_FORMAT_LITTLE_ENDIAN);
   }

   //Check status code
   if(!error)
   {
      //Set the z-coordinate of the result
      error = mpiSetValue(&r->z, 1);
   }

   //Release exclusive access to the CASPER module
   osReleaseMutex(&lpc55xxCryptoMutex);

   //Return status code
   return error;
}

#endif

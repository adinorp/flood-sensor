/**
 * @file rx65n_crypto.c
 * @brief RX65N hardware cryptographic accelerator (TSIP)
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
#include "r_tsip_rx_if.h"
#include "core/crypto.h"
#include "hardware/rx65n/rx65n_crypto.h"
#include "debug.h"

//Global variables
OsMutex rx65nCryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t rx65nCryptoInit(void)
{
   e_tsip_err_t status;

   //Initialize status code
   status = TSIP_SUCCESS;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&rx65nCryptoMutex))
   {
      //Failed to create mutex
      status = TSIP_ERR_FAIL;
   }

   //Check status code
   if(status == TSIP_SUCCESS)
   {
      //Initialize TSIP module
      status = R_TSIP_Open(NULL, NULL);
   }

   //Return status code
   return (status == TSIP_SUCCESS) ? NO_ERROR : ERROR_FAILURE;
}

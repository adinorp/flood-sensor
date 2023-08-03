/**
 * @file s7g2_crypto.c
 * @brief Synergy S7G2 hardware cryptographic accelerator (SCE7)
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
#include "hw_sce_private.h"
#include "core/crypto.h"
#include "hardware/s7g2/s7g2_crypto.h"
#include "debug.h"

//Global variables
OsMutex s7g2CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t s7g2CryptoInit(void)
{
   ssp_err_t status;

   //Initialize status code
   status = SSP_SUCCESS;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&s7g2CryptoMutex))
   {
      //Failed to create mutex
      status = SSP_ERR_CRYPTO_NOT_OPEN;
   }

   //Check status code
   if(status == SSP_SUCCESS)
   {
      //Initialize SCE7 module
      status = HW_SCE_McuSpecificInit();
   }

   //Return status code
   return (status == SSP_SUCCESS) ? NO_ERROR : ERROR_FAILURE;
}
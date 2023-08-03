/**
 * @file ra6_crypto.c
 * @brief RA6 hardware cryptographic accelerator (SCE7 / SCE9)
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
#include "hardware/ra6/ra6_crypto.h"
#include "debug.h"

//Global variables
OsMutex ra6CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t ra6CryptoInit(void)
{
   fsp_err_t status;

   //Initialize status code
   status = FSP_SUCCESS;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&ra6CryptoMutex))
   {
      //Failed to create mutex
      status = FSP_ERR_CRYPTO_NOT_OPEN;
   }

   //Check status code
   if(status == FSP_SUCCESS)
   {
      //Initialize SCE module
      status = HW_SCE_McuSpecificInit();
   }

   //Return status code
   return (status == FSP_SUCCESS) ? NO_ERROR : ERROR_FAILURE;
}

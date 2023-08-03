/**
 * @file msp432e4_crypto.c
 * @brief MSP432E4 hardware cryptographic accelerator
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
#include <stdint.h>
#include "msp432.h"
#include "driverlib/sysctl.h"
#include "core/crypto.h"
#include "hardware/msp432e4/msp432e4_crypto.h"
#include "debug.h"

//Global variables
OsMutex msp432e4CryptoMutex;


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t msp432e4CryptoInit(void)
{
   error_t error;

   //Initialize status code
   error = NO_ERROR;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&msp432e4CryptoMutex))
   {
      //Failed to create mutex
      error = ERROR_OUT_OF_RESOURCES;
   }

   //Check status code
   if(!error)
   {
      //Enable the CCM module
      SysCtlPeripheralEnable(SYSCTL_PERIPH_CCM0);
      //Wait for the CCM module to be ready
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CCM0))
      {
      }
   }

   //Return status code
   return error;
}

/**
 * @file mimxrt1170_crypto.c
 * @brief i.MX RT1170 hardware cryptographic accelerator (CAAM)
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
#include "debug.h"

//Global variables
OsMutex mimxrt1170CryptoMutex;

//CAAM job ring interfaces
static caam_job_ring_interface_t caamJobRingInterface[4];


/**
 * @brief Initialize hardware cryptographic accelerator
 * @return Error code
 **/

error_t mimxrt1170CryptoInit(void)
{
   status_t status;
   caam_config_t caamConfig;

   //Initialize status code
   status = kStatus_Success;

   //Create a mutex to prevent simultaneous access to the hardware
   //cryptographic accelerator
   if(!osCreateMutex(&mimxrt1170CryptoMutex))
   {
      //Failed to create mutex
      status = kStatus_Fail;
   }

   //Check status code
   if(status == kStatus_Success)
   {
      //Get default configuration
      CAAM_GetDefaultConfig(&caamConfig);

      //Set job ring interfaces
      caamConfig.jobRingInterface[0] = &caamJobRingInterface[0];
      caamConfig.jobRingInterface[1] = &caamJobRingInterface[1];
      caamConfig.jobRingInterface[2] = &caamJobRingInterface[2];
      caamConfig.jobRingInterface[3] = &caamJobRingInterface[3];

      //Initialize CAAM module
      status = CAAM_Init(CAAM, &caamConfig);
   }

   //Return status code
   return (status == kStatus_Success) ? NO_ERROR : ERROR_FAILURE;
}

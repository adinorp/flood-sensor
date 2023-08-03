/**
 * @file iap_fallaback.c
 * @brief CycloneBOOT IAP Fallback Functions API
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
#define TRACE_LEVEL IAP_TRACE_LEVEL

//Dependencies
#include "iap/iap_fallback.h"

//Extern Flash driver Swap bank (No-Init) routine
extern error_t flashDriverSwapBanksNoInit(void);
//Extern device MCU related function
extern void mcuSystemReset(void);

/**
 * @brief Start CycloneBOOT Dual Bank mode fallback procedure.
 * It will switch flash bank and then restart the MCU.
 * @return Status code
 **/

error_t iapFallbackStart(void)
{
   error_t error;

   //Start fallback procedure
   error = flashDriverSwapBanksNoInit();
   //Is any error?
   if(error)
   {
      //Return Status code
      return error;
   }
   else
   {
      //Reset MCU
      mcuSystemReset();

      //To avoid compilation warning
      return NO_ERROR;
   }
}

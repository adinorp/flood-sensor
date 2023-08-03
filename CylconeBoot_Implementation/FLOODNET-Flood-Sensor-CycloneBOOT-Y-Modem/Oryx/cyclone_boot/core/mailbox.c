/**
 * @file mailbox.c
 * @brief CycloneBOOT IAP Miscellaneous Functions
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
#include "mailbox.h"

// Create a section to place the boot mailbox in RAM
#if defined(__CC_ARM)
BootMailBox bootMailBox __attribute__((__section__(".boot_mailbox"), zero_init));
#elif defined(__GNUC__)
BootMailBox bootMailBox __attribute__((section(".boot_mailbox")));
#endif


/**
 * @brief Set message into the shared bootloader mailbox.
 * It will be processed by the bootloader at the next reboot.
 * @param[in] mailbox Pointeur to the message to be set in the bootloader mailbox
 * @return Status code
 **/

error_t setBootMailBox(BootMailBox *mailbox)
{
   //Check paramters validity
   if(mailbox == NULL)
      return ERROR_INVALID_PARAMETER;

   bootMailBox.version = mailbox->version;
   bootMailBox.signature = mailbox->signature;
   bootMailBox.pskSize = mailbox->pskSize;
   memcpy(bootMailBox.psk, (uint8_t*)mailbox->psk, BOOT_MBX_PSK_MAX_SIZE);

   //Successful process
   return NO_ERROR;
}


/**
 * @brief Get message from the shared bootloader mailbox.
 * @param[in,out] mailbox Pointeur to the message to retrieved from the bootloader mailbox.
 * @return Status code
 **/

error_t getBootMailBox(BootMailBox *mailbox)
{
   //Check paramters validity
   if(mailbox == NULL)
      return ERROR_INVALID_PARAMETER;

   mailbox->version = bootMailBox.version;
   mailbox->signature = bootMailBox.signature;
   mailbox->pskSize = bootMailBox.pskSize;
   memcpy((uint8_t*)mailbox->psk, bootMailBox.psk, BOOT_MBX_PSK_MAX_SIZE);

   //Successful process
   return NO_ERROR;
}

/**
 * @brief Check Bootloader mailbox message validity.
 * @param[in] Pointeur to the message to be checked.
 * @return Status code
 **/

error_t checkBootMailBox(BootMailBox *mailbox)
{
   error_t error;

   //Check paramter validity
   if(mailbox == NULL)
      return ERROR_INVALID_PARAMETER;

   //Initialize error code
   error = ERROR_FAILURE;

   //Check msg isn't null
   if(mailbox != NULL)
   {
      if ((mailbox->version == BOOT_MBX_VERSION) && (mailbox->signature == BOOT_MBX_SIGNATURE))
         error = NO_ERROR;
   }

   //Return error code
   return error;
}

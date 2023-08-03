/**
 * @file verify_auth.c
 * @brief CycloneBOOT IAP image data authentication module
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

// Switch to the appropriate trace level
#define TRACE_LEVEL IAP_TRACE_LEVEL

//Dependencies
#include "security/verify_auth.h"

#if (VERIFY_AUTHENTICATION_SUPPORT == ENABLED)

/**
 * @brief Initialize authentification material for further authentification tag
 * computation on received firmware data and verification against
 * received image authentification tag.
 * @param[in] context Pointer to the verification context
 * @return Error code
 **/

error_t authInit(VerifyContext *context)
{
   error_t error;
   VerifySettings *settings;

   // Check parameter validity
   if (context == NULL)
      return ERROR_INVALID_PARAMETER;

   // Point to the verify settings
   settings = (VerifySettings *)&context->verifySettings;

   // Initialize status code
   error = NO_ERROR;

   // Check user settings
   if (settings->authHashAlgo == NULL || settings->authAlgo == VERIFY_AUTH_NONE)
      return ERROR_INVALID_VALUE;

   // Is hmac authentification algo?
   if (settings->authAlgo == VERIFY_AUTH_HMAC)
   {
      // Initialize authentification hmac context
      error = hmacInit((HmacContext *)context->checkContext, settings->authHashAlgo,
                        settings->authKey, settings->authKeyLen);

      // Set digest length
      context->imageCheckDigestSize = ((HmacContext *)context->checkContext)->hash->digestSize;

      // Set check data (authentification tag) size
      context->checkDataSize = context->imageCheckDigestSize;
   }
   else
   {
      // Debug message
      TRACE_ERROR("Authentification algorithm not supported!\r\n");
      error = ERROR_NOT_IMPLEMENTED;
   }

   // Return status code
   return error;
}

/**
 * @brief Update authentification tag computation on received firmware data bloc.
 * @param[in,out] context Pointer to the verification context
 * @param[in] data Firmware data bloc to process.
 * @param[in] length Length of the firmware data bloc to process.
 * @return Error code
 **/

error_t authUpdateTag(VerifyContext *context, const uint8_t *data, size_t length)
{
   error_t error;
   VerifySettings *settings;

   // Check parameter validity
   if (context == NULL || data == NULL || length == 0)
      return ERROR_INVALID_PARAMETER;

   // Point to the verify settings
   settings = (VerifySettings *)&context->verifySettings;

   // Initialize status code
   error = NO_ERROR;

   // Check authentification hash algo
   if (settings->authAlgo == VERIFY_AUTH_NONE)
      return ERROR_INVALID_VALUE;

   // Is hmac authentification algo?
   if (settings->authAlgo == VERIFY_AUTH_HMAC)
   {
      // Update authentification hmac tag
      hmacUpdate((HmacContext *)context->checkContext, data, length);
   }
   else
   {
      // Debug message
      TRACE_ERROR("Authentification algorithm not supported!\r\n");
      error = ERROR_NOT_IMPLEMENTED;
   }

   // Return status code
   return error;
}

/**
 * @brief Finalize authentification tag computation on received firmware data.
 * @param[in,out] context Pointer to the verification context
 * @return Error code
 **/

error_t authFinalizeTag(VerifyContext *context)
{
   error_t error;
   VerifySettings *settings;

   // Check parameter validity
   if (context == NULL)
      return ERROR_INVALID_PARAMETER;

   // Point to the verify settings
   settings = (VerifySettings *)&context->verifySettings;

   // Initialize status code
   error = NO_ERROR;

   // Check authentification hash algo
   if (settings->authAlgo == VERIFY_AUTH_NONE)
      return ERROR_INVALID_VALUE;

   // Is hmac authentification algo?
   if (settings->authAlgo == VERIFY_AUTH_HMAC)
   {
      // Compute final authentification hmac tag
      hmacFinal((HmacContext *)context->checkContext, context->imageCheckDigest);
   }
   else
   {
      // Debug message
      TRACE_ERROR("Authentification algorithm not supported!\r\n");
      error = ERROR_NOT_IMPLEMENTED;
   }

   // Return status code
   return error;
}

#endif

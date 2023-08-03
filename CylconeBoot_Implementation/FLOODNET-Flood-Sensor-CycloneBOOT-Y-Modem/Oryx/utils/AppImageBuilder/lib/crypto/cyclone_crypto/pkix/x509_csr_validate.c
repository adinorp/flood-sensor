/**
 * @file x509_csr_validate.c
 * @brief CSR validation
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
#include "core/crypto.h"
#include "pkix/x509_csr_validate.h"
#include "pkix/x509_signature.h"
#include "debug.h"

//Check crypto library configuration
#if (X509_SUPPORT == ENABLED)


/**
 * @brief CSR validation
 * @param[in] csrInfo Pointer to the CSR to be verified
 * @return Error code
 **/

error_t x509ValidateCsr(const X509CsrInfo *csrInfo)
{
   error_t error;

   //Check parameters
   if(csrInfo == NULL)
      return ERROR_INVALID_PARAMETER;

   //The ASN.1 DER-encoded certificationRequestInfo is used as the input
   //to the signature function
   error = x509VerifySignature(csrInfo->certReqInfo.rawData,
      csrInfo->certReqInfo.rawDataLen, &csrInfo->signatureAlgo,
      &csrInfo->certReqInfo.subjectPublicKeyInfo, &csrInfo->signatureValue);

   //Return status code
   return error;
}

#endif

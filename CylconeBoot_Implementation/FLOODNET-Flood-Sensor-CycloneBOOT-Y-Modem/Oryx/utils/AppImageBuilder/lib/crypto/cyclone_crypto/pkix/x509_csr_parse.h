/**
 * @file x509_csr_parse.h
 * @brief CSR (Certificate Signing Request) parsing
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

#ifndef _X509_CSR_PARSE_H
#define _X509_CSR_PARSE_H

//Dependencies
#include "core/crypto.h"
#include "pkix/x509_common.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//CSR related functions
error_t x509ParseCsr(const uint8_t *data, size_t length,
   X509CsrInfo *csrInfo);

error_t x509ParseCertRequestInfo(const uint8_t *data, size_t length,
   size_t *totalLength, X509CertRequestInfo *certReqInfo);

error_t x509ParseAttributes(const uint8_t *data, size_t length,
   size_t *totalLength, X509Attributes *attributes);

error_t x509ParseAttribute(const uint8_t *data, size_t length,
   size_t *totalLength, X509Attribute *attribute);

error_t x509ParseChallengePassword(const uint8_t *data, size_t length,
   X509ChallengePassword *challengePwd);

error_t x509ParseExtensionRequest(const uint8_t *data, size_t length,
   X509Extensions *extensionReq);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

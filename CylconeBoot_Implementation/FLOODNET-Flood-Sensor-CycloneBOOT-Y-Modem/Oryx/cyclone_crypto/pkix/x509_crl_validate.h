/**
 * @file x509_crl_validate.h
 * @brief CRL validation
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

#ifndef _X509_CRL_VALIDATE_H
#define _X509_CRL_VALIDATE_H

//Dependencies
#include "core/crypto.h"
#include "pkix/x509_common.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//CSR related functions
error_t x509ValidateCrl(const X509CrlInfo *crlInfo,
   const X509CertificateInfo *issuerCertInfo);

error_t x509CheckRevokedCertificate(const X509CertificateInfo *certInfo,
   const X509CrlInfo *crlInfo);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

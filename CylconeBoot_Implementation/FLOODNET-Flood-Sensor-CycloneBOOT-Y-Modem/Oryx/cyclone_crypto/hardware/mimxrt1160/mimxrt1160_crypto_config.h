/**
 * @file mimxrt1160_crypto_conifg.h
 * @brief CAAM-specific configuration file
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

#ifndef _MIMXRT1160_CRYPTO_CONFIG_H
#define _MIMXRT1160_CRYPTO_CONFIG_H

//Dependencies
#include "fsl_caam.h"

//CAAM-specific context (SHA-1)
#define SHA1_PRIVATE_CONTEXT \
   caam_handle_t caamHandle; \
   caam_hash_ctx_t caamContext;

//CAAM-specific context (SHA-256)
#define SHA256_PRIVATE_CONTEXT \
   caam_handle_t caamHandle; \
   caam_hash_ctx_t caamContext;

//CAAM-specific context (SHA-512)
#define SHA512_PRIVATE_CONTEXT \
   caam_handle_t caamHandle; \
   caam_hash_ctx_t caamContext;

#endif

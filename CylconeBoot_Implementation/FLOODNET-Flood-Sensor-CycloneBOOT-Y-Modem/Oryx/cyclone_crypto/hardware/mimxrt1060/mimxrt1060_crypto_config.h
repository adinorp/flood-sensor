/**
 * @file mimxrt1060_crypto_conifg.h
 * @brief DCP-specific configuration file
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

#ifndef _MIMXRT1060_CRYPTO_CONFIG_H
#define _MIMXRT1060_CRYPTO_CONFIG_H

//Dependencies
#include "fsl_dcp.h"

//DCP-specific context (SHA-1)
#define SHA1_PRIVATE_CONTEXT \
   dcp_handle_t dcpHandle; \
   dcp_hash_ctx_t dcpContext;

//DCP-specific context (SHA-256)
#define SHA256_PRIVATE_CONTEXT \
   dcp_handle_t dcpHandle; \
   dcp_hash_ctx_t dcpContext;

#endif

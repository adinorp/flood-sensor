/**
 * @file mimxrt1020_crypto.h
 * @brief i.MX RT1020 hardware cryptographic accelerator
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

#ifndef _MIMXRT1020_CRYPTO_H
#define _MIMXRT1020_CRYPTO_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Global variables
extern OsMutex mimxrt1020CryptoMutex;

//i.MX RT1020 hardware cryptographic accelerator related functions
error_t mimxrt1020CryptoInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

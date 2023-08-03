/**
 * @file mimxrt1160_crypto.h
 * @brief i.MX RT1160 hardware cryptographic accelerator (CAAM)
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

#ifndef _MIMXRT1160_CRYPTO_H
#define _MIMXRT1160_CRYPTO_H

//Dependencies
#include "core/crypto.h"

//CAAM buffer size
#ifndef MIMXRT1160_CAAM_BUFFER_SIZE
   #define MIMXRT1160_CAAM_BUFFER_SIZE 1024
#elif (MIMXRT1160_CAAM_BUFFER_SIZE < 256)
   #error MIMXRT1160_CAAM_BUFFER_SIZE parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Global variables
extern OsMutex mimxrt1160CryptoMutex;

//i.MX RT1160 hardware cryptographic accelerator related functions
error_t mimxrt1160CryptoInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

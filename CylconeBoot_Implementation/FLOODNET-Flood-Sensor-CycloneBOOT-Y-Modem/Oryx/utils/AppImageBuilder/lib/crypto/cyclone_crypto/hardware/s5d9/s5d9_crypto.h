/**
 * @file s5d9_crypto.h
 * @brief Synergy S5D9 hardware cryptographic accelerator (SCE7)
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

#ifndef _S5D9_CRYPTO_H
#define _S5D9_CRYPTO_H

//Dependencies
#include "core/crypto.h"

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Global variables
extern OsMutex s5d9CryptoMutex;

//S5D9 hardware cryptographic accelerator related functions
error_t s5d9CryptoInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

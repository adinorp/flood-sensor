/**
 * @file esp32_s2_crypto_pkc.h
 * @brief ESP32-S2 public-key hardware accelerator
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

#ifndef _ESP32_S2_CRYPTO_PKC_H
#define _ESP32_S2_CRYPTO_PKC_H

//Dependencies
#include "core/crypto.h"

//Public-key hardware accelerator
#ifndef ESP32_S2_CRYPTO_PKC_SUPPORT
   #define ESP32_S2_CRYPTO_PKC_SUPPORT DISABLED
#elif (ESP32_S2_CRYPTO_PKC_SUPPORT != ENABLED && ESP32_S2_CRYPTO_PKC_SUPPORT != DISABLED)
   #error ESP32_S2_CRYPTO_PKC_SUPPORT parameter is not valid
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//PKC related functions
void esp32s2RsaInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

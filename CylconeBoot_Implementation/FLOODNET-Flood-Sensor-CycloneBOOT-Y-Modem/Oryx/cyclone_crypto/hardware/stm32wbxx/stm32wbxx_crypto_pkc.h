/**
 * @file stm32wbxx_crypto_pkc.h
 * @brief STM32WB public-key hardware accelerator (PKA)
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

#ifndef _STM32WBXX_CRYPTO_PKC_H
#define _STM32WBXX_CRYPTO_PKC_H

//Dependencies
#include "core/crypto.h"

//Public-key hardware accelerator
#ifndef STM32WBXX_CRYPTO_PKC_SUPPORT
   #define STM32WBXX_CRYPTO_PKC_SUPPORT DISABLED
#elif (STM32WBXX_CRYPTO_PKC_SUPPORT != ENABLED && STM32WBXX_CRYPTO_PKC_SUPPORT != DISABLED)
   #error STM32WBXX_CRYPTO_PKC_SUPPORT parameter is not valid
#endif

//Maximum RSA operand size, in bits
#define PKA_MAX_ROS 3136
//Maximum ECC operand size, in bits
#define PKA_MAX_EOS 640

//PKA operation modes
#define PKA_CR_MODE_MODULAR_EXP           0x00
#define PKA_CR_MODE_MONTGOMERY_PARAM      0x01
#define PKA_CR_MODE_MODULAR_EXP_FAST_MODE 0x02
#define PKA_CR_MODE_RSA_CRT_EXP           0x07
#define PKA_CR_MODE_MODULAR_INV           0x08
#define PKA_CR_MODE_ARITHMETIC_ADD        0x09
#define PKA_CR_MODE_ARITHMETIC_SUB        0x0A
#define PKA_CR_MODE_ARITHMETIC_MUL        0x0B
#define PKA_CR_MODE_COMPARISON            0x0C
#define PKA_CR_MODE_MODULAR_RED           0x0D
#define PKA_CR_MODE_MODULAR_ADD           0x0E
#define PKA_CR_MODE_MODULAR_SUB           0x0F
#define PKA_CR_MODE_MONTGOMERY_MUL        0x10
#define PKA_CR_MODE_ECC_MUL               0x20
#define PKA_CR_MODE_ECC_MUL_FAST_MODE     0x22
#define PKA_CR_MODE_ECDSA_SIGN            0x24
#define PKA_CR_MODE_ECDSA_VERIFY          0x26
#define PKA_CR_MODE_POINT_CHECK           0x28

//PKA status codes
#define PKA_STATUS_SUCCESS 0x00000000
#define PKA_STATUS_INVALID 0xFFFFFFFF

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//PKA related functions
error_t pkaInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

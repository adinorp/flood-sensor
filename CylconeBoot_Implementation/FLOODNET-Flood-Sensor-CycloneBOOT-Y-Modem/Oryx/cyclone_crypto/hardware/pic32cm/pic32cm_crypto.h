/**
 * @file pic32cm_crypto.h
 * @brief PIC32CM hardware cryptographic accelerator
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

#ifndef _PIC32CM_CRYPTO_H
#define _PIC32CM_CRYPTO_H

//Dependencies
#include "core/crypto.h"

//CRYA function entry points
#define CRYA_SHA_ADDR        0x02006800
#define CRYA_AES_ENC_ADDR    0x02006804
#define CRYA_AES_DEC_ADDR    0x02006808
#define CRYA_GF_MULT128_ADDR 0x0200680C

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//CRYA function prototypes
typedef void (*crya_sha_process_t)(uint32_t digest[8],
   const uint8_t data[64], uint32_t buffer[64]);

typedef void (*crya_aes_encrypt_t)(const uint8_t *key, uint32_t keyLen,
   const uint8_t *src, uint8_t *dest);

typedef void (*crya_aes_decrypt_t)(const uint8_t *key, uint32_t keyLen,
   const uint8_t *src, uint8_t *dest);

typedef void (*crya_gf_mult128_t)(const uint32_t *block1,
   const uint32_t *block2, uint32_t *dest);

//CRYA related functions
#define crya_sha_process ((crya_sha_process_t) (CRYA_SHA_ADDR | 1))
#define crya_aes_encrypt ((crya_aes_encrypt_t) (CRYA_AES_ENC_ADDR | 1))
#define crya_aes_decrypt ((crya_aes_decrypt_t) (CRYA_AES_DEC_ADDR | 1))
#define crya_gf_mult128 ((crya_gf_mult128_t) (CRYA_GF_MULT128_ADDR | 1))

//Global variables
extern OsMutex pic32cmCryptoMutex;

//PIC32CM hardware cryptographic accelerator related functions
error_t pic32cmCryptoInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

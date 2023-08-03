/**
 * @file cipher.h
 * @brief CycloneBOOT Encryption & Decryption handling
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

#ifndef _IAP_CIPHER_H
#define _IAP_CIPHER_H

//Dependencies
#include "iap/iap.h"
#include "cipher/cipher_algorithms.h"

// Cipher initialization vector maximum size
#define MAX_CIPHER_IV_SIZE MAX_CIPHER_BLOCK_SIZE

/**
 * @brief Cipher engine structure definition
 **/

typedef struct
{
   CipherContext context;
   const CipherAlgo *algo;
   CipherMode mode;
   const char_t *key;
   uint8_t iv[MAX_CIPHER_IV_SIZE];
   size_t ivLen;
} CipherEngine;


//CycloneBOOT cipher engine related functions
error_t cipherInit(CipherEngine *engine, const CipherAlgo *algo,
   CipherMode mode, const char_t *key, size_t keyLen);
error_t cipherSetIv(CipherEngine *engine, uint8_t* iv, size_t ivLen);
error_t cipherEncryptData(CipherEngine *cipherEngine, uint8_t *data, size_t length);
error_t cipherDecryptData(CipherEngine *cipherEngine, uint8_t *data, size_t length);

#endif // !_IAP_CIPHER_H

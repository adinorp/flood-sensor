/**
 * @file ecb.c
 * @brief Electronic Codebook (ECB) mode
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
 * @section Description
 *
 * The Electronic Codebook (ECB) mode is a confidentiality mode that features,
 * for a given key, the assignment of a fixed ciphertext block to each
 * plaintext block, analogous to the assignment of code words in a codebook.
 * Refer to SP 800-38A for more details
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.1
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL CRYPTO_TRACE_LEVEL

//Dependencies
#include "core/crypto.h"
#include "cipher_mode/ecb.h"
#include "debug.h"

//Check crypto library configuration
#if (ECB_SUPPORT == ENABLED)


/**
 * @brief ECB encryption
 * @param[in] cipher Cipher algorithm
 * @param[in] context Cipher algorithm context
 * @param[in] p Plaintext to be encrypted
 * @param[out] c Ciphertext resulting from the encryption
 * @param[in] length Total number of data bytes to be encrypted
 * @return Error code
 **/

__weak_func error_t ecbEncrypt(const CipherAlgo *cipher, void *context,
   const uint8_t *p, uint8_t *c, size_t length)
{
   //ECB mode operates in a block-by-block fashion
   while(length >= cipher->blockSize)
   {
      //Encrypt current block
      cipher->encryptBlock(context, p, c);

      //Next block
      p += cipher->blockSize;
      c += cipher->blockSize;
      length -= cipher->blockSize;
   }

   //The plaintext must be a multiple of the block size
   if(length != 0)
      return ERROR_INVALID_LENGTH;

   //Successful encryption
   return NO_ERROR;
}


/**
 * @brief ECB decryption
 * @param[in] cipher Cipher algorithm
 * @param[in] context Cipher algorithm context
 * @param[in] c Ciphertext to be decrypted
 * @param[out] p Plaintext resulting from the decryption
 * @param[in] length Total number of data bytes to be decrypted
 * @return Error code
 **/

__weak_func error_t ecbDecrypt(const CipherAlgo *cipher, void *context,
   const uint8_t *c, uint8_t *p, size_t length)
{
   //ECB mode operates in a block-by-block fashion
   while(length >= cipher->blockSize)
   {
      //Decrypt current block
      cipher->decryptBlock(context, c, p);

      //Next block
      c += cipher->blockSize;
      p += cipher->blockSize;
      length -= cipher->blockSize;
   }

   //The ciphertext must be a multiple of the block size
   if(length != 0)
      return ERROR_INVALID_LENGTH;

   //Successful encryption
   return NO_ERROR;
}

#endif

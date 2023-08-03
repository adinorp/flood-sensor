/**
 * @file rc4.c
 * @brief RC4 encryption algorithm
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

//Switch to the appropriate trace level
#define TRACE_LEVEL CRYPTO_TRACE_LEVEL

//Dependencies
#include "core/crypto.h"
#include "cipher/rc4.h"

//Check crypto library configuration
#if (RC4_SUPPORT == ENABLED)

//Common interface for encryption algorithms
const CipherAlgo rc4CipherAlgo =
{
   "RC4",
   sizeof(Rc4Context),
   CIPHER_ALGO_TYPE_STREAM,
   0,
   (CipherAlgoInit) rc4Init,
   (CipherAlgoEncryptStream) rc4Cipher,
   (CipherAlgoDecryptStream) rc4Cipher,
   NULL,
   NULL
};


/**
 * @brief Initialize an RC4 context using the supplied key
 * @param[in] context Pointer to the RC4 context to initialize
 * @param[in] key Pointer to the key
 * @param[in] length Length of the key
 * @return Error code
 **/

error_t rc4Init(Rc4Context *context, const uint8_t *key, size_t length)
{
   uint_t i;
   uint_t j;
   uint8_t temp;

   //Check parameters
   if(context == NULL || key == NULL)
      return ERROR_INVALID_PARAMETER;

   //Clear context
   context->i = 0;
   context->j = 0;

   //Initialize the S array with identity permutation
   for(i = 0; i < 256; i++)
   {
      context->s[i] = i;
   }

   //S is then processed for 256 iterations
   for(i = 0, j = 0; i < 256; i++)
   {
      //Randomize the permutations using the supplied key
      j = (j + context->s[i] + key[i % length]) % 256;

      //Swap the values of S[i] and S[j]
      temp = context->s[i];
      context->s[i] = context->s[j];
      context->s[j] = temp;
   }

   //RC4 context successfully initialized
   return NO_ERROR;
}


/**
 * @brief Encrypt/decrypt data with the RC4 algorithm
 * @param[in] context Pointer to the RC4 context
 * @param[in] input Pointer to the data to encrypt/decrypt
 * @param[in] output Pointer to the resulting data
 * @param[in] length Length of the input data
 **/

void rc4Cipher(Rc4Context *context, const uint8_t *input, uint8_t *output, size_t length)
{
   uint8_t temp;

   //Restore context
   uint_t i = context->i;
   uint_t j = context->j;
   uint8_t *s = context->s;

   //Encryption loop
   while(length > 0)
   {
      //Adjust indices
      i = (i + 1) % 256;
      j = (j + s[i]) % 256;

      //Swap the values of S[i] and S[j]
      temp = s[i];
      s[i] = s[j];
      s[j] = temp;

      //Valid input and output?
      if(input != NULL && output != NULL)
      {
         //XOR the input data with the RC4 stream
         *output = *input ^ s[(s[i] + s[j]) % 256];

         //Increment data pointers
         input++;
         output++;
      }

      //Remaining bytes to process
      length--;
   }

   //Save context
   context->i = i;
   context->j = j;
}

#endif

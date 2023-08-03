/**
 * @file ctr.c
 * @brief Counter(CTR) mode
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
 * The Counter (CTR) mode is a confidentiality mode that features the application
 * of the forward cipher to a set of input blocks, called counters, to produce
 * a sequence of output blocks that are exclusive-ORed with the plaintext to
 * produce the ciphertext, and vice versa. Refer to SP 800-38A for more details
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.1
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL CRYPTO_TRACE_LEVEL

//Dependencies
#include "core/crypto.h"
#include "cipher_modes/ctr.h"
#include "debug.h"

//Check crypto library configuration
#if (CTR_SUPPORT == ENABLED)


/**
 * @brief CTR encryption
 * @param[in] cipher Cipher algorithm
 * @param[in] context Cipher algorithm context
 * @param[in] m Size in bits of the specific part of the block to be incremented
 * @param[in,out] t Initial counter block
 * @param[in] p Plaintext to be encrypted
 * @param[out] c Ciphertext resulting from the encryption
 * @param[in] length Total number of data bytes to be encrypted
 * @return Error code
 **/

__weak_func error_t ctrEncrypt(const CipherAlgo *cipher, void *context, uint_t m,
   uint8_t *t, const uint8_t *p, uint8_t *c, size_t length)
{
   size_t i;
   size_t n;
   uint16_t temp;
   uint8_t o[16];

   //The parameter must be a multiple of 8
   if((m % 8) != 0)
      return ERROR_INVALID_PARAMETER;

   //Determine the size, in bytes, of the specific part of the block
   //to be incremented
   m = m / 8;

   //Check the resulting value
   if(m > cipher->blockSize)
      return ERROR_INVALID_PARAMETER;

   //Process plaintext
   while(length > 0)
   {
      //CTR mode operates in a block-by-block fashion
      n = MIN(length, cipher->blockSize);

      //Compute O(j) = CIPH(T(j))
      cipher->encryptBlock(context, t, o);

      //Compute C(j) = P(j) XOR T(j)
      for(i = 0; i < n; i++)
      {
         c[i] = p[i] ^ o[i];
      }

      //Standard incrementing function
      for(temp = 1, i = 1; i <= m; i++)
      {
         //Increment the current byte and propagate the carry
         temp += t[cipher->blockSize - i];
         t[cipher->blockSize - i] = temp & 0xFF;
         temp >>= 8;
      }

      //Next block
      p += n;
      c += n;
      length -= n;
   }

   //Successful encryption
   return NO_ERROR;
}


/**
 * @brief CTR decryption
 * @param[in] cipher Cipher algorithm
 * @param[in] context Cipher algorithm context
 * @param[in] m Size in bits of the specific part of the block to be incremented
 * @param[in,out] t Initial counter block
 * @param[in] c Ciphertext to be decrypted
 * @param[out] p Plaintext resulting from the decryption
 * @param[in] length Total number of data bytes to be decrypted
 * @return Error code
 **/

error_t ctrDecrypt(const CipherAlgo *cipher, void *context, uint_t m,
   uint8_t *t, const uint8_t *c, uint8_t *p, size_t length)
{
   //Decryption is the same the as encryption with P and C interchanged
   return ctrEncrypt(cipher, context, m, t, c, p, length);
}

#endif

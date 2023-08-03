/**
 * @file salsa20.c
 * @brief Salsa20 encryption algorithm
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
#include "cipher/salsa20.h"

//Check crypto library configuration
#if (SALSA20_SUPPORT == ENABLED)

//Salsa20 quarter-round function
#define SALSA20_QUARTER_ROUND(a, b, c, d) \
{ \
   b ^= ROL32(a + d, 7); \
   c ^= ROL32(b + a, 9); \
   d ^= ROL32(c + b, 13); \
   a ^= ROL32(d + c, 18); \
}


/**
 * @brief Salsa20 core function
 * @param[in] input Pointer to the 64-octet input block
 * @param[out] output Pointer to the 64-octet output block
 * @param[in] nr Number of rounds to be applied (8, 12 or 20)
 **/

void salsa20ProcessBlock(const uint8_t *input, uint8_t *output, uint_t nr)
{
   uint_t i;
   uint32_t x[16];

   //Copy the input words to the working state
   for(i = 0; i < 16; i++)
   {
      x[i] = LOAD32LE(input + i * 4);
   }

   //The Salsa20 core function alternates between column rounds and row rounds
   for(i = 0; i < nr; i += 2)
   {
      //The column round function modifies the columns of the matrix in parallel
      //by feeding a permutation of each column through the quarter round function
      SALSA20_QUARTER_ROUND(x[0], x[4], x[8], x[12]);
      SALSA20_QUARTER_ROUND(x[5], x[9], x[13], x[1]);
      SALSA20_QUARTER_ROUND(x[10], x[14], x[2], x[6]);
      SALSA20_QUARTER_ROUND(x[15], x[3], x[7], x[11]);

      //The row round function modifies the rows of the matrix in parallel by
      //feeding a permutation of each row through the quarter round function
      SALSA20_QUARTER_ROUND(x[0], x[1], x[2], x[3]);
      SALSA20_QUARTER_ROUND(x[5], x[6], x[7], x[4]);
      SALSA20_QUARTER_ROUND(x[10], x[11], x[8], x[9]);
      SALSA20_QUARTER_ROUND(x[15], x[12], x[13], x[14]);
   }

   //Add the original input words to the output words
   for(i = 0; i < 16; i++)
   {
      x[i] += LOAD32LE(input + i * 4);
      STORE32LE(x[i], output + i * 4);
   }
}

#endif

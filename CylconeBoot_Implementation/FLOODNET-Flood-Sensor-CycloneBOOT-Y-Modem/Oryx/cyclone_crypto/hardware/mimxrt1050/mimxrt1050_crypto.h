/**
 * @file mimxrt1050_crypto.h
 * @brief i.MX RT1050 hardware cryptographic accelerator (DCP)
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

#ifndef _MIMXRT1050_CRYPTO_H
#define _MIMXRT1050_CRYPTO_H

//Dependencies
#include "core/crypto.h"

//DCP buffer size
#ifndef MIMXRT1050_DCP_BUFFER_SIZE
   #define MIMXRT1050_DCP_BUFFER_SIZE 1024
#elif (MIMXRT1050_DCP_BUFFER_SIZE < 256)
   #error MIMXRT1050_DCP_BUFFER_SIZE parameter is not valid
#endif

//Name of the section where to place DCP buffers
#ifndef MIMXRT1050_DCP_RAM_SECTION
   #define MIMXRT1050_DCP_RAM_SECTION ".dcp_ram"
#endif

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

//Global variables
extern OsMutex mimxrt1050CryptoMutex;

//i.MX RT1050 hardware cryptographic accelerator related functions
error_t mimxrt1050CryptoInit(void);

//C++ guard
#ifdef __cplusplus
}
#endif

#endif

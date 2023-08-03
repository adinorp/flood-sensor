/**
 * @file verify_sign.h
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

#ifndef _VERIFY_SIGN_H
#define _VERIFY_SIGN_H

// Dependencies
#include "security/verify.h"

//CycloneBOOT signature verification related functions
error_t signInit(VerifyContext *context);
error_t signVerify(VerifyContext *context, uint8_t *verifyData, size_t verifyDataLength);

#endif // !_VERIFY_AUTH_H

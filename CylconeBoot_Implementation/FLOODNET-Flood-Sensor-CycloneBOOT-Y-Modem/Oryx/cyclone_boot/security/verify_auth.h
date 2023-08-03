/**
 * @file verify_auth.h
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

#ifndef _VERIFY_AUTH_H
#define _VERIFY_AUTH_H

// Dependencies
#include "security/verify.h"

//CycloneBOOT authentication verification related functions
error_t authInit(VerifyContext *verifyContext);
error_t authUpdateTag(VerifyContext *verifyContext, const uint8_t *data, size_t length);
error_t authFinalizeTag(VerifyContext *verifyContext);

#endif // !_VERIFY_AUTH_H

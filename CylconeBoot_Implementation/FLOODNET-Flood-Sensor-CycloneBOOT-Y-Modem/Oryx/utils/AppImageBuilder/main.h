/**
 * @file main.h
 * @brief App Image Builder main routine
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

#ifndef __MAIN_H
#define __MAIN_H

//Dependencies
#include "crypto.h"
#include "rng/yarrow.h"

#define SEED_LENGTH 32
#define CHECK_DATA_LENGTH 256
#define INIT_VECTOR_LENGTH 16

/**
 * @brief Stores the information about encryption operations.
 * Encryption Key, Initialization Vector (IV), Size of IV and Size of Encryption Key.
 **/

typedef struct {
    const char* iv;
    size_t ivSize;
    const char* cipherKey;
    size_t cipherKeySize;
    PrngAlgo *prngAlgo;
    YarrowContext *yarrowContext;
    char seed[SEED_LENGTH];
} CipherInfo;


/**
 * @brief Stores the information about application check data field.
 **/

typedef struct {
    int signature;
    int authentication;
    int integrity;
    const char* auth_algo;
    const char* integrity_algo;
    const char* authKey;
    size_t authKeySize;
    const char* sign_algo;
    const char *signKey;
    size_t signKeySize;
    const HashAlgo *signHashAlgo;
} CheckDataInfo;

extern char *input_binary;
extern size_t input_binary_size;
extern char *blockified_input_binary;
extern size_t blockified_input_binary_size;
extern char *cipher_input_binary;
extern size_t cipher_input_binary_size;

#endif // __MAIN_H

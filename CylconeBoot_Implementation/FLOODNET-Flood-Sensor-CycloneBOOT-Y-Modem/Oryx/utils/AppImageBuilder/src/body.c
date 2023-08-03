/**
 * @file body.c
 * @brief App Image Builder image boby managment
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

//Dependencies
#include <stdio.h>
#include "main.h"
#include "utils.h"
#include "header.h"
#include "body.h"

//Global variables
char *cipher_input_binary = NULL;
size_t cipher_input_binary_size = 0;


/**
 * @brief Generate image body using directly the plaintext firmware binary or encrypt it before.
 * @param header Pointer to the image header
 * @param body Pointer to the image body
 * @param cipherInfo Pointer to the cipher informations
 * @return Error code
 **/

int bodyMake(ImageHeader *header, ImageBody *body, CipherInfo cipherInfo) {
    error_t status = NO_ERROR;

    if(cipherInfo.cipherKey != NULL) {
        cipher_input_binary = malloc(blockified_input_binary_size);
        memcpy(cipher_input_binary,blockified_input_binary,blockified_input_binary_size);

        status = encrypt(blockified_input_binary,
                         blockified_input_binary_size,
                         cipher_input_binary,
                         cipherInfo);

        if(status) {
            printf("bodyMake: failed to encrypt input binary.\n");
            return EXIT_FAILURE;
        }

        cipher_input_binary_size = blockified_input_binary_size;
        header->dataSize = cipher_input_binary_size;

        body->binary = cipher_input_binary;
        body->binarySize = cipher_input_binary_size;
    } else {
        body->binary = input_binary;
        body->binarySize = input_binary_size;
    }

    return EXIT_SUCCESS;
}

/**
 * @file utils.h
 * @brief App Image Builder utils routines
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

#ifndef __UTILS_H
#define  __UTILS_H

//Dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cyclone_crypto/core/crypto.h"
#include "cyclone_crypto/cipher_mode/cbc.h"
#include "cyclone_crypto/cipher/aria.h"
#include "cyclone_crypto/cipher/cipher_algorithms.h"
#include "cyclone_crypto/rng/yarrow.h"
#include "main.h"
#include "header.h"
#include "body.h"

#define ARRAY_BYTES(arr)        (sizeof((arr)[0]) * ARRAY_SIZE(arr))
#define ARRAY_SBYTES(arr)       ((ssize_t)ARRAY_BYTES(arr))

#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0]))
#define ARRAY_SSIZE(arr)    ((ptrdiff_t)ARRAY_SIZE(arr))


/**
 * @brief Update Image definition
 **/

typedef struct {
    ImageHeader *header;
    ImageBody *body;
} UpdateImage;


//App Image builder utils related routines
int read_file(const char *file_path, char **file_contents, size_t *file_size);
int blockify(size_t blockSize, char* input, size_t inputSize, char** output, size_t* outputSize);
int init_crypto(CipherInfo *cipherInfo);
int encrypt(char *plainData, size_t plainDataSize, char* cipherData, CipherInfo cipherInfo);
int sign(CipherInfo *cipherInfo, CheckDataInfo *checkDataInfo, char *data, size_t dataLen, char **signData, size_t *signDataLen);
int write_image_to_file(UpdateImage *image, CipherInfo *cipherInfo, const char *output_file_path);

void dump_buffer(void *buffer, size_t buffer_size);
void dumpHeader(ImageHeader* header);
void dumpBody(ImageBody* body);
void dumpFooter(char *check_data, size_t check_data_size);
void seedInitVector(uint8_t *buffer, size_t length);

#endif

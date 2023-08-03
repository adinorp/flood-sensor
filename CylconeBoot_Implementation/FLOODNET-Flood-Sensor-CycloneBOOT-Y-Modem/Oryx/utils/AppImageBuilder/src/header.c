/**
 * @file header.c
 * @brief App Image Builder image header managment
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
#include "core/crypto.h"
#include "crc32.h"
#include "main.h"
#include "header.h"
#include "utils.h"

char *input_binary = NULL;
size_t input_binary_size = 0;
char *blockified_input_binary = NULL;
size_t blockified_input_binary_size = 0;
int encrypted = 0;

/**
 * @brief Make image header. It will contains neccessary information to process the overall image.
 * @param header Pointer to the image header to be generated
 * @param input_binary_path Path to the input firmware binary file path
 * @param imgIdx Index of the image to generate
 * @param firmware_version Version to the image to generate
 * @param internal Indicate if will be an internl image (with additional padding)
 * @param img_encrypted Indicate if the image body will be encrypted
 * @return Error code
 **/

int headerMake(ImageHeader *header, const char *input_binary_path, int imgIdx, const char* firmware_version, int internal, int img_encrypted) {
    size_t headerDataSize;
    int headerVersion;

    char *_firmware_version;
    uint8_t  majorVersion;
    uint8_t minorVersion;
    uint8_t patchVersion;

    HashAlgo const *crc32_algo;

    headerVersion = VERSION_32_BITS(1,0,0);
    crc32_algo = (HashAlgo *)CRC32_HASH_ALGO;

    int status = read_file(input_binary_path,&input_binary,&input_binary_size);

    if(status) {
        printf("headerMake: failed to open input binary file.\n");
        return EXIT_FAILURE;
    }

    headerDataSize = input_binary_size;

    if(img_encrypted) {
        status = blockify(16, input_binary, input_binary_size,
                          &blockified_input_binary, &blockified_input_binary_size);

        encrypted = 1;

        if(status) {
            printf("headerMake: failed to blockify input binary file.\n");
            return EXIT_FAILURE;
        }

        headerDataSize = blockified_input_binary_size;
    }

    header->dataSize = headerDataSize;
    header->headVers = headerVersion;
    header->imgType = 0; // IMG_TYPE_APP = 0;
    header->imgIndex = imgIdx;

    //Parse received firmware "string" version
    majorVersion = (uint8_t)strtol(firmware_version, &_firmware_version, 10);
    minorVersion = (uint8_t)strtol(++_firmware_version, &_firmware_version, 10);
    patchVersion = (uint8_t)strtol(++_firmware_version, &_firmware_version, 10);

    header->dataVers = VERSION_32_BITS(majorVersion,minorVersion,patchVersion);
    header->imgTime = time(NULL);

    memset(header->reserved, 0, sizeof(header->reserved));

    if(internal) {
        // TODO: 0x400 value will be changed to a command parameter in a later version.
        header->dataPadding = 0x400 - sizeof(ImageHeader);
    } else {
        header->dataPadding = 0;
    }

    crc32_algo->compute(header,sizeof(ImageHeader) - CRC32_DIGEST_SIZE, header->headCrc);

    return EXIT_SUCCESS;
}

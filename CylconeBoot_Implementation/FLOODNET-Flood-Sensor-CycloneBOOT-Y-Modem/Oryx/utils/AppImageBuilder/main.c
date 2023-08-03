/**
 * @file main.c
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

//Denpendencies
#include <stdio.h>
#include "cli.h"
#include "header.h"
#include "body.h"
#include "footer.h"
#include "utils.h"
#include "main.h"
#include "config/AppImageBuilderConfig.h"


/**
 * @brief Main entry point of the program.
 **/

int main(int argc, char *argv[])
{
    // flags
    error_t status;

    status = NO_ERROR;
    uint8_t encrypted = 0;
    uint8_t internal = 0;

    // structures
    ImageHeader header = {0};
    ImageBody body = {0};
    UpdateImage updateImage = {0};

    CipherInfo cipherInfo = {0};
    CheckDataInfo checkDataInfo = {0};
    struct builder_cli_configuration cli_config = {0};

    YarrowContext yarrowContext = {0};

    // buffers
    char check_data[CHECK_DATA_LENGTH] = {0};
    long imgIdx = 0;
    char *imgIdx_char;
    const char *padding_buffer;

    char iv[INIT_VECTOR_LENGTH];
    size_t ivSize = INIT_VECTOR_LENGTH;

    seedInitVector((char *)iv,INIT_VECTOR_LENGTH);

    status = parse_options(argc, argv, &cli_config);

    if (status == ERROR_FAILURE)
    {
        printf("Something went wrong while parsing command line options.\n");
        return ERROR_FAILURE;
    }

    if (status == CLI_OK)
        return NO_ERROR;


    if (cli_config.encryption_key != NULL)
    {
        encrypted = 1;
    }

    if (!cli_config.firmware_index)
        cli_config.firmware_index = "0"; // cannot be NULL
    imgIdx = strtol(cli_config.firmware_index, &imgIdx_char, 10);

    // Initialize Crypto stuff
    if (encrypted)
    {

        cipherInfo.yarrowContext = &yarrowContext;
        cipherInfo.prngAlgo = (PrngAlgo *)YARROW_PRNG_ALGO;

        cipherInfo.cipherKey = cli_config.encryption_key;
        cipherInfo.cipherKeySize = strlen(cli_config.encryption_key);

        cipherInfo.iv = iv;
        cipherInfo.ivSize = ivSize;

        status = init_crypto(&cipherInfo);
        if (status != NO_ERROR)
        {
            printf("Something went wrong in init_crypto.\r\n");
            return ERROR_FAILURE;
        }
    }
    else
    {
        cipherInfo.yarrowContext = &yarrowContext;
        cipherInfo.prngAlgo = (PrngAlgo *)YARROW_PRNG_ALGO;

        status = init_crypto(&cipherInfo);
        if (status != NO_ERROR)
        {
            printf("Something went wrong in init_crypto.\r\n");
            return ERROR_FAILURE;
        }
    }

    if(cli_config.padding) {
        internal = 1;
    } else {
        internal = 0;
    }

    // Make header
    status = headerMake(&header,
                        cli_config.input,
                        (int)imgIdx,
                        cli_config.firmware_version,
                        internal,
                        encrypted);

    if (status != NO_ERROR)
    {
        printf("Something went wrong while making the header.\n");
        return ERROR_FAILURE;
    }
    // Make body
    status = bodyMake(&header, &body, cipherInfo);
    if (status != NO_ERROR)
    {
        printf("Something went wrong while making the body.\n");
        return ERROR_FAILURE;
    }
    // Make footer
    if (cli_config.integrity_algo != NULL)
    {
        checkDataInfo.integrity = 1;
        checkDataInfo.integrity_algo = cli_config.integrity_algo;
    }
    if (cli_config.authentication_algo != NULL)
    {
        checkDataInfo.authentication = 1;
        checkDataInfo.auth_algo = cli_config.authentication_algo;
        checkDataInfo.authKey = cli_config.authentication_key;
        checkDataInfo.authKeySize = strlen(cli_config.authentication_key);
    }

    if (cli_config.signature_algo != NULL)
    {
        checkDataInfo.signature = 1;
        checkDataInfo.sign_algo = cli_config.signature_algo;
        checkDataInfo.signKey = cli_config.signature_key;
        checkDataInfo.signKeySize = strlen(cli_config.signature_key);
        checkDataInfo.signHashAlgo = SHA256_HASH_ALGO;
    }

    status = footerMake(&header, &body, &cipherInfo, &checkDataInfo, check_data);
    if (status != NO_ERROR)
    {
        printf("Something went wrong while making the footer.\n");
        return ERROR_FAILURE;
    }

    updateImage.header = &header;
    updateImage.body = &body;

    write_image_to_file(&updateImage, &cipherInfo, cli_config.output);

    return EXIT_SUCCESS;
}

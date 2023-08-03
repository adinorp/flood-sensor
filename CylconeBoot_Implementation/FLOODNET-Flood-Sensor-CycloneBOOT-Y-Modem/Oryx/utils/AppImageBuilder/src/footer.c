/**
 * @file footer.c
 * @brief App Image Builder image footer managment
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
#include <stdlib.h>
#include "crc32.h"
#include "hash/md5.h"
#include "hash/sha1.h"
#include "hash/sha256.h"
#include "hash/sha512.h"
#include "mac/hmac.h"
#include "main.h"
#include "inc/header.h"
#include "inc/body.h"
#include "inc/footer.h"

/**
 * @brief Make image footer. It will contains image check data tag used to verify overall image validity.
 * @param header Pointer to the image header
 * @param body Pointer to the image body
 * @param cipherInfo Pointer to the image body cipher information
 * @param checkDataInfo Pointer to image check data tat information
 * @param check_data Resulted image footer data
 * @return Error code
 **/

int footerMake(ImageHeader *header, ImageBody *body, CipherInfo *cipherInfo, CheckDataInfo *checkDataInfo, char* check_data) {
    size_t checkDataContentsSize;
    error_t status;
    size_t check_data_len;
    char *checkDataContents;
    HashAlgo *hash_algo;

    printf("Computing application image check data tag...\n");

    if(cipherInfo->cipherKey != NULL) {
        checkDataContentsSize = CRC32_DIGEST_SIZE + cipherInfo->ivSize + body->binarySize;
        checkDataContents = malloc(checkDataContentsSize);

        memcpy(checkDataContents, header->headCrc, CRC32_DIGEST_SIZE);
        memcpy(checkDataContents + CRC32_DIGEST_SIZE, cipherInfo->iv, cipherInfo->ivSize);
        memcpy(checkDataContents + CRC32_DIGEST_SIZE + cipherInfo->ivSize, body->binary, body->binarySize);
    } else {
        checkDataContentsSize = CRC32_DIGEST_SIZE + body->binarySize;
        checkDataContents = (char*)malloc(checkDataContentsSize);

        memcpy(checkDataContents,header->headCrc,CRC32_DIGEST_SIZE);
        memcpy(checkDataContents + CRC32_DIGEST_SIZE,body->binary,body->binarySize);
    }

    if(checkDataInfo->integrity) {
        if(strcasecmp(checkDataInfo->integrity_algo, "crc32") == 0) {
            hash_algo = (HashAlgo *)CRC32_HASH_ALGO;
            body->checkDataSize = CRC32_DIGEST_SIZE;
        } else if(strcasecmp(checkDataInfo->integrity_algo, "md5") == 0) {
            hash_algo = (HashAlgo *)MD5_HASH_ALGO;
            body->checkDataSize = MD5_DIGEST_SIZE;
        } else if(strcasecmp(checkDataInfo->integrity_algo, "sha1") == 0) {
            hash_algo = (HashAlgo *)SHA1_HASH_ALGO;
            body->checkDataSize = SHA1_DIGEST_SIZE;
        } else if(strcasecmp(checkDataInfo->integrity_algo, "sha256") == 0) {
            hash_algo = (HashAlgo *)SHA256_HASH_ALGO;
            body->checkDataSize = SHA256_DIGEST_SIZE;
        } else if(strcasecmp(checkDataInfo->integrity_algo, "sha512") == 0) {
            hash_algo = (HashAlgo *)SHA512_HASH_ALGO;
            body->checkDataSize = SHA512_DIGEST_SIZE;
        } else {
            printf("footerMake: unknown integrity algorithm.\n");
            return EXIT_FAILURE;
        }

        status = hash_algo->compute(checkDataContents,checkDataContentsSize,(uint8_t *)check_data);
        if(status != NO_ERROR) {
            printf("footerMake: failed to calculate hash digest of check data.\n");
            return EXIT_FAILURE;
        }
    } else if (checkDataInfo->signature) {

        status = sign(cipherInfo,checkDataInfo,checkDataContents,checkDataContentsSize,&check_data, &check_data_len);
        body->checkDataSize = check_data_len;
        if(status != NO_ERROR) {
            printf("footerMake: failed to sign the binary (check_data field).\n");
            return EXIT_FAILURE;
        }

    } else if (checkDataInfo->authentication) {
        if(strcasecmp(checkDataInfo->auth_algo, "hmac-md5") == 0) {
            hash_algo = (HashAlgo*)MD5_HASH_ALGO;
            body->checkDataSize = MD5_DIGEST_SIZE;
        } else if(strcasecmp(checkDataInfo->auth_algo, "hmac-sha256") == 0) {
            hash_algo = (HashAlgo *)SHA256_HASH_ALGO;
            body->checkDataSize = SHA256_DIGEST_SIZE;
        } else if(strcasecmp(checkDataInfo->auth_algo, "hmac-sha512") == 0) {
            hash_algo = (HashAlgo *)SHA512_HASH_ALGO;
            body->checkDataSize = SHA512_DIGEST_SIZE;
        } else {
            printf("footerMake: unknown authentication algorithm.\n");
            return EXIT_FAILURE;
        }

        status = hmacCompute(hash_algo,checkDataInfo->authKey,checkDataInfo->authKeySize,
                            checkDataContents,checkDataContentsSize,(uint8_t *)check_data);

        if(status != NO_ERROR) {
            printf("footerMake: failed to calculate application authentication tag.\n");
            return EXIT_FAILURE;
        }

        free(checkDataContents);
    } else {
        hash_algo = ( HashAlgo *)CRC32_HASH_ALGO;
        status = hash_algo->compute(checkDataContents,checkDataContentsSize,(uint8_t *)check_data);
        body->checkDataSize = CRC32_DIGEST_SIZE;

        if(status != NO_ERROR) {
            printf("footerMake: failed to calculate CRC32 digest of check data.\n");
            free(checkDataContents);
            return EXIT_FAILURE;
        }

        free(checkDataContents);
    }

    body->checkData = (uint8_t *)check_data;

    return EXIT_SUCCESS;
}

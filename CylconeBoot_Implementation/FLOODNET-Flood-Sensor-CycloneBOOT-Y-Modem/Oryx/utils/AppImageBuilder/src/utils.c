/**
 * @file utils.c
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

//Dependencies
#ifdef IS_WINDOWS
#define _CRTDBG_MAP_ALLOC
#define _WINERROR_
#include <Winsock2.h>
#endif

#include <stdio.h>

#ifdef IS_LINUX
#include <sys/random.h>
#endif

#include "ecc/ec.h"
#include "ecc/ecdsa.h"
#include "ecc/ec_curves.h"
#include "pkc/rsa.h"
#include "pkix/pem_import.h"

#include "main.h"
#include "header.h"
#include "body.h"
#include "utils.h"

#ifdef IS_WINDOWS
#include "wincrypt.h"
#endif


/**
 * @brief Read given file binary data and save it in a buffer.
 * @param file_path Path of the file to read
 * @param file_contents Pointer to the allocated buffer that will hold file data
 * @param file_size Pointe to the resulted file data length
 * @return Error code
 **/

int read_file(const char *file_path, char **file_contents, size_t *file_size)
{
    FILE *fh = NULL;
    size_t fs = 0;

    if (file_path == NULL)
    {
        printf("read_file: Error. Missing file path.\r\n");
        return EXIT_FAILURE;
    }

    // Open input file
    fh = fopen(file_path, "rb");

    // Failed to open input file?
    if (fh == NULL)
    {
        // User message
        printf("read_file: Error. Cannot open %s!\r\n", file_path);
        // Report an error
        return EXIT_FAILURE;
    }

    // Retrieve the length of the file
    fseek(fh, 0, SEEK_END);
    fs = ftell(fh);
    fseek(fh, 0, SEEK_SET);

    *file_contents = (char *)malloc(fs);

    if (*file_contents == NULL)
    {
        // User message
        printf("read_file: Error. Failed to allocate memory for the input file!\r\n");

        // Clean-up side effects
        fclose(fh);

        // Report an error
        return EXIT_FAILURE;
    }

    // Read the contents of the file
    fread(*file_contents, fs, 1, fh);

    // Copy the file size to the input parameter
    *file_size = fs;

    // Close input file
    fclose(fh);

    return EXIT_SUCCESS;
}


/**
 * @brief Check if the input buffer is a multilple of a given black size.
 * If not it will allocate a buffer that will both hold the initial input
 * buffer and whose size will be a multiple of a the given block size.
 * This is usefull for encryption purpose because we need to ensure that the
 * size of the data to process is a multilple of a certain block size.
 * @param blockSize Given block size
 * @param input Pointer to the initial input buffer
 * @param inputSize Sze of the input buffer
 * @param output Pointer to the resulted output buffer
 * @param outputSize Size of the resulted output buffer
 * @return Error code
 **/

int blockify(size_t blockSize, char *input, size_t inputSize, char **output, size_t *outputSize)
{
    if (input == NULL || output == NULL)
    {
        return EXIT_FAILURE;
    }
    // is the binary size a multiple of a given block size?
    if (blockSize == 0 || inputSize % blockSize == 0)
    {
        // The block size is zero or input size is already the multiple of given block size
        // We can use directly the input data buffer as it is
        *outputSize = inputSize;
        *output = input;
    }
    else
    {
        // Binary block size must be a multiple of the given block size
        *outputSize = inputSize + blockSize - (inputSize % blockSize);

        // Allocate memory for the binary
        *output = malloc(*outputSize);

        // Is allocation failed
        if (*output == NULL)
        {
            printf("Blockify: Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
        // Initialize memory
        memset(*output, 0, *outputSize);
        // Copy binary application
        memcpy(*output, input, inputSize);

        free(input);
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Initialize cryptographic material according given cipher information
 * @param cipherInfo Cipher information
 * @return Error code
 **/

int init_crypto(CipherInfo *cipherInfo)
{
    error_t error = 0;
    size_t randSeedSize = 0;

#ifdef IS_WINDOWS
    HCRYPTPROV hProv;
    cipherInfo->prngAlgo = (PrngAlgo *)YARROW_PRNG_ALGO;

    if (CryptAcquireContext(&hProv,
                            NULL,
                            NULL,
                            PROV_RSA_FULL,
                            CRYPT_VERIFYCONTEXT))
    {
        if (!CryptGenRandom(hProv, SEED_LENGTH, cipherInfo->seed))
        {
            printf("Error during IV generation (CryptGenRandom Error).\n");
            return ERROR_FAILURE;
        }

        CryptReleaseContext(hProv, 0);

        // PRNG initialization
        error = cipherInfo->prngAlgo->init(cipherInfo->yarrowContext);
        // Any error to report?
        if (error)
        {
            // Debug message
            printf("Error : PRNG initialization failed (%d)\r\n", error);
            // Exit immediately
            return ERROR_FAILURE;
        }

        // Properly seed the PRNG
        error = cipherInfo->prngAlgo->seed(cipherInfo->yarrowContext, cipherInfo->seed, sizeof(cipherInfo->seed));
        // Any error to report?
        if (error)
        {
            // Debug message
            printf("Error : Failed to seed PRNG (%d)\r\n", error);
            // Exit immediately
            return error;
        }
    }
    else
    {
        printf("Error acquiring CryptContext.\r\n");
        return ERROR_FAILURE;
    }

    return NO_ERROR;

#endif
#ifdef IS_LINUX
                // Generate a CSPRNG seed
    // https://man7.org/linux/man-pages/man2/getrandom.2.html
    // getrandom() was introduced in version 3.17 of the Linux kernel.
    randSeedSize = getrandom(cipherInfo->seed, SEED_LENGTH, GRND_RANDOM);
    if (randSeedSize != 32)
    {
        // Debug message
        printf("init_crypto : Error. CSPRNG Seed failed (%d)\r\n", error);
        return ERROR_FAILURE;
    }

    // PRNG initialization
    error = cipherInfo->prngAlgo->init(cipherInfo->yarrowContext);
    // Any error to report?
    if (error)
    {
        // Debug message
        printf("init_crypto : Error. CSPRNG initialization failed (%d)\r\n", error);
        // Exit immediately
        return ERROR_FAILURE;
    }

    // Properly seed the PRNG
    error = cipherInfo->prngAlgo->seed(cipherInfo->yarrowContext, cipherInfo->seed, sizeof(cipherInfo->seed));
    // Any error to report?
    if (error)
    {
        // Debug message
        printf("init_crypto : Error. Failed to seed CSPRNG (%d)\r\n", error);
        // Exit immediately
        return error;
    }

    return NO_ERROR;
#endif
}


/**
 * @brief Encrypt given plain text data according given cipher information.
 * @param plainData Plain text input data to encrypt
 * @param plainDataSize Plain text data size
 * @param cipherData Pointer to the resulted encrypted data buffer
 * @param cipherInfo Cipher information
 * @return Error code
 **/

int encrypt(char *plainData, size_t plainDataSize, char *cipherData, CipherInfo cipherInfo)
{
    error_t status;
    char context[MAX_CIPHER_CONTEXT_SIZE];
    char iv_copy[16];

    if (plainData == NULL || cipherData == NULL)
    {
        printf("encrypt: input data invalid.\n");
        return EXIT_FAILURE;
    }

    if (cipherInfo.iv == NULL || cipherInfo.cipherKey == NULL)
    {
        printf("encrypt: invalid cipher info.\n");
        return EXIT_FAILURE;
    }

    status = AES_CIPHER_ALGO->init(context, cipherInfo.cipherKey, cipherInfo.cipherKeySize);

    if (status)
    {
        printf("encrypt: AES-CBC initialization failed.\n");
        return EXIT_FAILURE;
    }

    memcpy(iv_copy, cipherInfo.iv, cipherInfo.ivSize);
    status = cbcEncrypt(AES_CIPHER_ALGO, context, iv_copy, plainData, cipherData, plainDataSize);

    if (status)
    {
        printf("encrypt: AES-CBC encryption failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Sign given data according given check information.
 * @param cipherInfo Cipher information
 * @param checkDataInfo Check data information
 * @param data Pointer to the data to sign
 * @param dataLen Data lenght
 * @param signData Resulted signature data
 * @param signDataLen Signature data size
 * @return Error code
 **/

int sign(CipherInfo *cipherInfo, CheckDataInfo *checkDataInfo, char *data, size_t dataLen, char **signData, size_t *signDataLen)
{
    error_t error;
    EcDomainParameters ecDomainParameters;
    EcPrivateKey ecPrivateKey;
    EcdsaSignature ecdsaSignature;
    char ecdsaSignDigest[MAX_HASH_DIGEST_SIZE];
    RsaPrivateKey rsaPrivateKey;
    char rsaSignDigest[MAX_HASH_DIGEST_SIZE];

    char signature[1024];
    size_t signatureLen;
    char *signatureKey = NULL;
    size_t signatureKeyLen = 0;
    char *privateKey = NULL;
    size_t privateKeySize = 0;

    size_t n;

    error = read_file(checkDataInfo->signKey, &privateKey, &privateKeySize);
    if (error)
    {
        printf("sign: error opening private key.\n");
        return EXIT_FAILURE;
    }

    if (checkDataInfo->sign_algo == NULL || checkDataInfo->signKey == NULL)
    {
        printf("sign: signature algorithm or signature key not found.\n");
        return EXIT_FAILURE;
    }

    if (strcasecmp(checkDataInfo->sign_algo, "ecdsa-sha256") == 0)
    {
        // Compute Hash value
        checkDataInfo->signHashAlgo->compute(data, dataLen, (uint8_t *)ecdsaSignDigest);
        // Initialize EC domain parameters
        ecInitDomainParameters(&ecDomainParameters);
        // Initialize ECDSA signature
        ecdsaInitSignature(&ecdsaSignature);
        // Initialize EC private keys
        ecInitPrivateKey(&ecPrivateKey);
        // Decode the PEM file that contains the private key
        error = pemImportEcPrivateKey(privateKey, privateKeySize, &ecPrivateKey);

        if (error)
        {
            printf("sign: error importing private key.\n");
            return EXIT_FAILURE;
        }

        // Load EC domain parameters
        error = ecLoadDomainParameters(&ecDomainParameters, SECP256K1_CURVE); // TODO: specify this curve as an option?

        if (error)
        {
            printf("sign: error loading domain parameters.\n");
            return EXIT_FAILURE;
        }

        // Generate ECDSA signature (R,S)
        error = ecdsaGenerateSignature(cipherInfo->prngAlgo, cipherInfo->yarrowContext, &ecDomainParameters,
                                       &ecPrivateKey, (uint8_t *)ecdsaSignDigest, checkDataInfo->signHashAlgo->digestSize,
                                       &ecdsaSignature);

        if (error)
        {
            printf("sign: error generating ECDSA signature.\n");
            return EXIT_FAILURE;
        }

        error = ecdsaWriteSignature(&ecdsaSignature, (uint8_t *)signature, &signatureLen);

        if (error)
        {
            printf("sign: error writing ECDSA signature.\n");
            return EXIT_FAILURE;
        }

        n = mpiGetByteLength(&ecDomainParameters.q);

        // Allocate memory for signature
        *signDataLen = n * 2;
        *signData = malloc(*signDataLen);

        if (*signData == NULL)
        {
            printf("sign: error allocating memory for signature.\n");
            return EXIT_FAILURE;
        }

        error = mpiExport(&ecdsaSignature.r, *signData, n, MPI_FORMAT_BIG_ENDIAN);

        if (error)
        {
            printf("sign: error converting integer to octet.\n");
            return EXIT_FAILURE;
        }

        error = mpiExport(&ecdsaSignature.s, *signData + n, n, MPI_FORMAT_BIG_ENDIAN);

        if (error)
        {
            printf("sign: error converting integer to octet.\n");
            return EXIT_FAILURE;
        }

        // release previously allocated resources
        ecFreeDomainParameters(&ecDomainParameters);
        ecdsaFreeSignature(&ecdsaSignature);
        ecFreePrivateKey(&ecPrivateKey);
    }
    else if (strcasecmp(checkDataInfo->sign_algo, "rsa-sha256") == 0)
    {
        rsaInitPrivateKey(&rsaPrivateKey);
        error = pemImportRsaPrivateKey(privateKey, privateKeySize, &rsaPrivateKey);
        if (error)
        {
            printf("sign: failed to import PEM RSA private key.\n");
            return EXIT_FAILURE;
        }

        error = checkDataInfo->signHashAlgo->compute(data, dataLen, (uint8_t *)rsaSignDigest);

        if (error)
        {
            printf("sign: error computing RSA signature hash.\n");
            return EXIT_FAILURE;
        }

        error = rsassaPkcs1v15Sign(&rsaPrivateKey, checkDataInfo->signHashAlgo,
                                   (const uint8_t *)rsaSignDigest, (uint8_t *)&signature, &signatureLen);

        if (error)
        {
            printf("sign: error generating RSA + SHA256 signature.\n");
            return EXIT_FAILURE;
        }

        // allocate memory for the signature
        *signDataLen = signatureLen;
        *signData = malloc(*signDataLen);

        // Save signature
        memcpy(*signData, signature, signatureLen);

        // free RSA private key
        rsaFreePrivateKey(&rsaPrivateKey);
    }
    else
    {
        printf("sign: Unknown signature algorithm.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Write image content into a given file.
 * @param image Image to be written in a file
 * @param cipherInfo Cipher information
 * @param output_file_path Path of the file where to write image data.
 * @return Error code
 **/

int write_image_to_file(UpdateImage *image, CipherInfo *cipherInfo, const char *output_file_path)
{
    char offset_buffer[1];
    FILE *fh;

    printf("Generating update image...\n");
    fh = fopen(output_file_path, "wb+");
    if (fh == NULL)
    {
        printf("write_to_image_file: Error. cannot open output file.\n");
        return EXIT_FAILURE;
    }

    fwrite(image->header, 1, sizeof(ImageHeader), fh);

    // adding offset
    offset_buffer[0] = 0;
    for (int i = 0; i < image->header->dataPadding; i++)
        fwrite(offset_buffer, 1, 1, fh);

    if (cipherInfo->iv != 0)
    {
        fwrite(cipherInfo->iv, 1, cipherInfo->ivSize, fh);
        fwrite(image->body->binary, 1, image->body->binarySize, fh);
    }
    else
    {
        fwrite(image->body->binary, 1, image->body->binarySize, fh);
    }

    fwrite(image->body->checkData, 1, image->body->checkDataSize, fh);

    fclose(fh);

    printf("Done.\n");

    return EXIT_SUCCESS;
}

/**
 * @brief Dump a given buffer
 * @param buffer Buffer to be dumpted
 * @param buffer_size Buffer size
 * @return Error code
 **/

void dump_buffer(void *buffer, size_t buffer_size)
{
    int i;

    for (i = 0; i < buffer_size; ++i)
        printf("0x%02hhx\t", ((char *)buffer)[i]);

    printf("\n\n");
}


/**
 * @brief Dump image header
 * @param header Image header to be dumpted
 * @return Error code
 **/

void dumpHeader(ImageHeader *header)
{
    printf("\r\n");
    printf("Image header:\r\n");
    printf("-------------\r\n");
    printf("- headVers = %d.%d.%d\r\n", (header->headVers >> 16) & 0xFF,
           (header->headVers >> 8) & 0xFF, header->headVers & 0xFF);
    printf("- imgIndex   = %d\r\n", header->imgIndex);
    printf("- type          = %d (0 = APP, 1 = OTHER)\r\n", header->imgType);
    printf("- data offset   = 0x%X -> %d bytes\r\n", header->dataPadding, header->dataPadding);
    printf("- dataSize       = 0x%X -> %d bytes\r\n", header->dataSize, header->dataSize);
    printf("- dataVers    = %d.%d.%d\r\n", (header->dataVers >> 16) & 0xFF,
           (header->dataVers >> 8) & 0xFF, header->dataVers & 0xFF);
    printf("- time          = 0x%X%X\r\n", (uint32_t)((header->imgTime >> 32) & 0xFFFFFFFF),
           (uint32_t)(header->imgTime & 0xFFFFFFFF));
    printf("- reserved (%zu bytes) =\r\n", sizeof(header->reserved)); // set reserved size to get a 256 bytes header
    dump_buffer(header->reserved, sizeof(header->reserved));
    printf("- headCrc   (%zu bytes)   =\r\n", sizeof(header->headCrc));
    dump_buffer(header->headCrc, sizeof(header->headCrc));
    printf("\r\n");
}


/**
 * @brief Dump image body
 * @param body Image body to be dumpted
 * @return Error code
 **/

void dumpBody(ImageBody *body)
{
    printf("\r\n");
    printf("Image body:\r\n");
    printf("-----------\r\n");
    printf("binary (%zu bytes) =\r\n", body->binarySize);
    dump_buffer(body->binary, body->binarySize);
    printf("body check data size = %zu bytes\n", body->checkDataSize);
    printf("body check data = \r\n");
    dump_buffer(body->checkData, body->checkDataSize);

    printf("\r\n");
}


/**
 * @brief Dump image footer
 * @param header Image foeter to be dumpted
 * @return Error code
 **/

void dumpFooter(char *check_data, size_t check_data_size)
{
    printf("\r\n");
    printf("Image footer:\r\n");
    printf("-------------\r\n");
    printf("Binary check data =\r\n");
    dump_buffer(check_data, check_data_size);
    printf("\r\n");
}


/**
 * @brief Randomly generate initialization vector that will be used to for later encryption.
 * @param buffer Buffer that hold init vector
 * @param length Init vector size
 * @return Error code
 **/

void seedInitVector(uint8_t *buffer, size_t length) {
#ifdef IS_LINUX
    getrandom(buffer, length, GRND_RANDOM);
#endif
#ifdef IS_WINDOWS
    HCRYPTPROV hProv;
    CryptAcquireContext(&hProv,NULL,NULL,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT);
    CryptGenRandom(hProv, length, buffer);
    CryptReleaseContext(hProv, 0);
#endif
}

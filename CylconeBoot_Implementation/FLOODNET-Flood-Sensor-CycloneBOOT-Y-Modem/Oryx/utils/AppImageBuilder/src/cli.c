/**
 * @file cli.c
 * @brief App Image Builder cli managment
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
#include "inc/cli.h"
#include "AppImageBuilderConfig.h"


/**
 * @brief Check that given encryption settings are correct.
 * @param encryption_algo Encryption algorithm to be checked
 * @param encryption_key Encryption symetric key to be checked
 * @return Error code
 **/

int check_constraints_encryption(const char *encryption_algo, const char *encryption_key) {

#ifdef IS_LINUX
    // Make sure encryption algo is nothing else but AES-CBC
    if (encryption_algo == NULL || strcasecmp(encryption_algo, "aes-cbc") != 0) {
        printf("\nError: Unknown encryption algorithm. Supported algorithms: aes-cbc.\n");
        return EXIT_FAILURE;
    }
#endif
#ifdef IS_WINDOWS
    // Make sure encryption algo is nothing else but AES-CBC
    if (encryption_algo == NULL || strnicmp(encryption_algo, "aes-cbc",7) != 0)
    {
        printf("\nError: Unknown encryption algorithm. Supported algorithms: aes-cbc.\n");
        return EXIT_FAILURE;
    }
#endif

    if (encryption_key == NULL) {
        printf("\nError: Missing encryption key.\n");
        return EXIT_FAILURE;
    }

    // Make sure that the encryption key is at least 64 bytes
    const size_t n = strnlen(encryption_key, 1024);

    if ((n != (2 * 16) && n != (2 * 24)) && (n != (2 * 32)) || (n == 1024)) {
        printf("\nError: Invalid encryption key size. Please enter a key of at least 64 bytes.\n");
        return EXIT_FAILURE;
    }

    // Make sure that the pair algo / key is both present if one is chosen
    if (encryption_algo && !encryption_key) {
        printf("\nError: Please specify an encryption key.");
        return EXIT_FAILURE;
    } else if (!encryption_algo && encryption_key) {
        printf("\nError: Please specify an encryption algorithm. Supported algorithms: aes-cbc.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Display supported authentication algorithm
 **/

void display_supported_auth_algorithms_message(void) {
    printf("Supported algorithms: hmac-md5, hmac-sha256, hmac-sha512\n");
}


/**
 * @brief Check that given authentication settings are correct.
 * @param authentication_algo Authentication algorithm to be checked
 * @param authentication_key Authentication symetric key to be checked
 * @return Error code
 **/

int check_constraints_authentication(const char *authentication_algo, const char *authentication_key) {

    if (authentication_algo == NULL || authentication_key == NULL) {
        printf("Error: Missing authentication algorithm or key.\r\n");
        return EXIT_FAILURE;
    }

#ifdef IS_LINUX
    if (strcasecmp(authentication_algo, "hmac-md5") != 0 &&
        strcasecmp(authentication_algo, "hmac-sha256") != 0 &&
        strcasecmp(authentication_algo, "hmac-sha512") != 0) {
        printf("Invalid Authentication algorithm. ");
        display_supported_auth_algorithms_message();
        return EXIT_FAILURE;
    }
#endif
#ifdef IS_WINDOWS
    if (strnicmp(authentication_algo, "hmac-md5",8) != 0 &&
        strnicmp(authentication_algo, "hmac-sha256",11) != 0 &&
        strnicmp(authentication_algo, "hmac-sha512",11) != 0)
    {
        printf("Invalid Authentication algorithm. ");
        display_supported_auth_algorithms_message();
        return EXIT_FAILURE;
    }
#endif

    // Make sure that the pair algo / key is both present if one is chosen
    if (authentication_algo && !authentication_key) {
        printf("\nError: Please specify an authentication key.");
        return EXIT_FAILURE;
    } else if (!authentication_algo && authentication_key) {
        display_supported_auth_algorithms_message();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/**
 * @brief Check that given signature settings are correct.
 * @param signature_algo Signature algorithm to be checked
 * @param signature_key Signature private key to be checked
 * @return Error code
 **/

int check_constraints_signature(const char *signature_algo, const char *signature_key) {
    if (signature_algo == NULL || signature_key == NULL) {
        printf("Error: Missing signature algorithm or key.\r\n");
        printf("Supported algorithms: ecdsa-sha256, rsa-sha256\n");
        return EXIT_FAILURE;
    }
#ifdef IS_LINUX
    if (strcasecmp(signature_algo, "ecdsa-sha256") != 0 &&
        strcasecmp(signature_algo, "rsa-sha256") != 0) {
        printf("Invalid Signature algorithm. ");
        printf("Supported algorithms: ecdsa-sha256, rsa-sha256\n");
        return EXIT_FAILURE;
    }
#endif
#ifdef IS_WINDOWS
    if (strnicmp(signature_algo, "ecdsa-sha256",12) != 0 &&
        strnicmp(signature_algo, "rsa-sha256",10) != 0)
    {
        printf("Invalid Signature algorithm. ");
        printf("Supported algorithms: ecdsa-sha256, rsa-sha256\n");
        return EXIT_FAILURE;
    }
#endif
    return EXIT_SUCCESS;
}


/**
 * This is the main configuration of all options available.
 **/

static struct cag_option options[] = {

        {.identifier = 'i',
                .access_letters = "iI",
                .access_name = "input",
                .value_name = "<my_firmware.bin>",
                .description = "[REQUIRED] Path to firmware binary."},

        {.identifier = 'o',
                .access_letters = "oO",
                .access_name = "output",
                .value_name = "<my_firmware_update.img>",
                .description = "[REQUIRED] Path to save firmware update image."},

        {.identifier = 'x',
                .access_letters = "xX",
                .access_name = "firmware-index",
                .value_name = "<numeric value>",
                .description = "[OPTIONAL] Custom firmware index. Default value: 0"},

        {.identifier = 'p',
                .access_letters = "pP",
                .access_name = "add-padding",
                .value_name = NULL,
                .description = "[OPTIONAL] Generate an image compatible with the static bootloader in Single Bank Mode."},

        {.identifier = 'f',
                .access_letters = NULL,
                .access_name = "firmware-version",
                .value_name = "X.X.X",
                .description = "[OPTIONAL] Version of firmware update. Obligatory for fallback support."},

        {.identifier = 'e',
                .access_letters = NULL,
                .access_name = "enc-algo",
                .value_name = "<AES-CBC>",
                .description = "[OPTIONAL] Encryption algorithm used. Supported algorithms: aes-cbc."},

        {.identifier = 'k',
                .access_letters = NULL,
                .access_name = "enc-key",
                .value_name = "<my_encryption_key>",
                .description = "[OPTIONAL] Encryption Key. Optional unless encryption is required."},

        {.identifier = 'a',
                .access_letters = NULL,
                .access_name = "auth-algo",
                .value_name = "<HMAC-|MD5|SHA256|SHA512|>",
                .description = "[OPTIONAL] Authentication algorithm used. Supported algorithms: hmac-md5, hmac-sha256, hmac-sha512."},

        {.identifier = 'u',
                .access_letters = NULL,
                .access_name = "auth-key",
                .value_name = "<my_auth_key>",
                .description = "[OPTIONAL] Authentication Key. Optional unless authentication is required."},

        {.identifier = 's',
                .access_letters = NULL,
                .access_name = "sign-algo",
                .value_name = "<ECDSA-SHA256|RSA-SHA256>",
                .description = "[OPTIONAL] Signature algorithm used. Supported algorithms: ecdsa-sha256, rsa-sha256."},

        {.identifier = 'g',
                .access_letters = NULL,
                .access_name = "sign-key",
                .value_name = "<my_sign_key.pem>",
                .description = "[OPTIONAL] Signature Key. Optional unless signature is required."},

        {.identifier = 'n',
                .access_letters = NULL,
                .access_name = "integrity-algo",
                .value_name = "<CRC32|MD5|SHA1|SHA256|SHA512>",
                .description = "[OPTIONAL] Integrity algorithm used. CRC32 by default."},

        {.identifier = 'b',
                .access_letters = NULL,
                .access_name = "verbose",
                .value_name = NULL,
                .description = "[OPTIONAL] Verbose mode."},

        {.identifier = 'v',
                .access_letters = "vV",
                .access_name = "version",
                .value_name = NULL,
                .description = "Show CLI version."},

        {.identifier = 'h',
                .access_letters = "h",
                .access_name = "help",
                .description = "Show the help message."}};


/**
 * @brief Parse input App Image Builder cli options
 * @param argc Number of input cli paramters
 * @param argc List of input cli parameters
 * @param cli_options Pointer to the parsed App Image Builder cli options
 * @return Error code
 **/

int parse_options(int argc, char **argc, struct builder_cli_configuration *cli_options) {
    char identifier;
    const char *value;
    cag_option_context context;

    struct builder_cli_configuration config = {
            false,
            false,
            NULL,
            false,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            false,
            false,
            false};

    if (argc == 1) {
        printf("Usage: app_image_builder [OPTION]...\n");
        printf("Generates a firmware update image compatible with CycloneBOOT.\n");
        printf("CLI Tool Version: %d.%d.%d.%s\n\n",
               app_image_builder_VERSION_MAJOR, app_image_builder_VERSION_MINOR, app_image_builder_VERSION_PATCH, app_image_builder_TIMESTAMP);
        cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
        printf("\n\nExample: Create a clear-text firmware image with SHA256 integrity algorithm:");
#ifdef IS_WINDOWS
        printf("\n./app_image_builder.exe -i <firmware_binary.bin> -o <firmware_binary_update.img> --integrity-algo=sha256\n");
#endif
#ifdef IS_LINUX
        printf("\n./app_image_builder -i <firmware_binary.bin> -o <firmware_binary_update.img> --integrity-algo=sha256\n");
#endif
        return CLI_OK;
    }

    /**
     * Now we just prepare the context and iterate over all options. Simple!
     */
    cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
    while (cag_option_fetch(&context)) {
        identifier = cag_option_get(&context);
        switch (identifier) {
            case 'i':
                value = cag_option_get_value(&context);
                config.input = value;
                break;
            case 'b':
                config.verbose = true;
                break;
            case 'o':
                value = cag_option_get_value(&context);
                config.output = value;
                break;
            case 'p':
                config.padding = true;
                break;
            case 'f':
                value = cag_option_get_value(&context);
                config.firmware_version = value;
                break;
            case 'x':
                value = cag_option_get_value(&context);
                config.firmware_index = value;
                break;
            case 'e':
                value = cag_option_get_value(&context);
                config.encryption_algo = value;
                break;
            case 'k':
                value = cag_option_get_value(&context);
                config.encryption_key = value;
                break;
            case 'a':
                value = cag_option_get_value(&context);
                config.authentication_algo = value;
                break;
            case 'u':
                value = cag_option_get_value(&context);
                config.authentication_key = value;
                break;
            case 's':
                value = cag_option_get_value(&context);
                config.signature_algo = value;
                break;
            case 'g':
                value = cag_option_get_value(&context);
                config.signature_key = value;
                break;
            case 'n':
                value = cag_option_get_value(&context);
                config.integrity_algo = value;
                break;
            case 'v':
                config.version = true;
                break;
            case 'h':
                printf("Usage: app_image_builder [OPTION]...\n");
                printf("Generates a firmware update image compatible with CycloneBOOT.\n\n");
                printf("CLI Tool Version: %d.%d.%d.%s\n\n",
                       app_image_builder_VERSION_MAJOR, app_image_builder_VERSION_MINOR, app_image_builder_VERSION_PATCH, app_image_builder_TIMESTAMP);
                cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
                printf("\n\nExample: Create a clear-text firmware image with SHA256 integrity algorithm:");
#ifdef IS_WINDOWS
                printf("\n./app_image_builder.exe -i <firmware_binary.bin> -o <firmware_binary_update.img> --integrity-algo=sha256\n");
#endif
#ifdef IS_LINUX
                printf("\n./app_image_builder -i <firmware_binary.bin> -o <firmware_binary_update.img> --integrity-algo=sha256\n");
#endif
                return CLI_OK;
            default:
                printf("Usage: app_image_builder [OPTION]...\n");
                printf("Generates a firmware update image compatible with CycloneBOOT.\n\n");
                printf("CLI Tool Version: %d.%d.%d.%s\n\n",
                       app_image_builder_VERSION_MAJOR, app_image_builder_VERSION_MINOR, app_image_builder_VERSION_PATCH, app_image_builder_TIMESTAMP);
                cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
                printf("\n\nExample: Create a clear-text firmware image with SHA256 integrity algorithm:");
#ifdef IS_WINDOWS
                printf("\n./app_image_builder.exe -i <firmware_binary.bin> -o <firmware_binary_update.img> --integrity-algo=sha256\n");
#endif
#ifdef IS_LINUX
                printf("\n./app_image_builder -i <firmware_binary.bin> -o <firmware_binary_update.img> --integrity-algo=sha256\n");
#endif
                return CLI_OK;
        }
    }

    if(config.version) {
        printf("CLI Tool Version: %d.%d.%d.%s\n",
               app_image_builder_VERSION_MAJOR, app_image_builder_VERSION_MINOR, app_image_builder_VERSION_PATCH, app_image_builder_TIMESTAMP);
        return CLI_OK;
    }

    if (config.firmware_version == NULL && config.verbose)
        printf("\nWarning: You haven't specified a firmware version."
               "\nIf you are using fallback mode. Please enter the firmware version (ex. --firmware-version 1.0.1).\n");

    if (config.firmware_version == NULL) {
        config.firmware_version = "1.0.0";
    }

    if (!config.padding && config.verbose)
        printf("\nWarning: You haven't specified a padding."
               "\nIf you are generating a firmware image in 'Single Bank' mode. Please add -p flag and regenerate an image.\n");

    if (!config.input) {
        printf("\nError: Input binary path is missing.\n");
        return EXIT_FAILURE;
    }

    if (!config.output) {
        printf("\nError: Output image path is missing.\n");
        return EXIT_FAILURE;
    }

    // check encryption options, if passed
    if ((config.encryption_algo || config.encryption_key) &&
        check_constraints_encryption(config.encryption_algo, config.encryption_key)) {
        return EXIT_FAILURE;
    }

    // check authentication options, if passed
    if ((config.authentication_algo || config.authentication_key) &&
        check_constraints_authentication(config.authentication_algo, config.authentication_key)) {
        return EXIT_FAILURE;
    }

    // check signature options, if passed
    if ((config.signature_algo || config.signature_key) &&
        check_constraints_signature(config.signature_algo, config.signature_key)) {
        return EXIT_FAILURE;
    }

// check integrity options, if passed
#ifdef IS_WINDOWS
    if (config.integrity_algo)
    {
        if (strnicmp(config.integrity_algo, "md5",3) != 0 &&
            strnicmp(config.integrity_algo, "sha256",6) != 0 &&
            strnicmp(config.integrity_algo, "sha512",6) != 0 &&
            strnicmp(config.integrity_algo, "crc32",5) != 0 &&
            strnicmp(config.integrity_algo, "sha1",3) != 0)
            return EXIT_FAILURE;
    }
#endif
#ifdef IS_LINUX

    if (config.integrity_algo && strcasecmp(config.integrity_algo, "md5") != 0 &&
        strcasecmp(config.integrity_algo, "sha256") != 0 &&
        strcasecmp(config.integrity_algo, "sha512") != 0 &&
        strcasecmp(config.integrity_algo, "crc32") != 0 &&
        strcasecmp(config.integrity_algo, "sha1") != 0)
        return EXIT_FAILURE;

#endif

    // check data field validation
    if (config.integrity_algo && config.signature_algo && config.authentication_algo) {
        printf("Error: please choose ONE image integrity validation method.\n");
        return EXIT_FAILURE;
    }

    // copying the CLI options to the input parameter struct
    memcpy((void *) cli_options, (void *) &config, sizeof(config));

    return EXIT_SUCCESS;
}

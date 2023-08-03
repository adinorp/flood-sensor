@echo off

REM Application image builder utility executable
set APP_IMAGE_BUILDER_EXE=..\..\Oryx\utils\AppImageBuilder\bin\app_image_builder_windows.exe

REM Scenario 1 update image generation options
set SCN_1_INPUT_FW_BIN=..\lora-e5.bin
set SCN_1_OUTPUT_UPD_IMG=lora_e5_iap_single_bank_demo_image_scenario_1.img
set SCN_1_FW_VERS=2.0.0
set SCN_1_INTEGRITY_ALGO=crc32

REM Scenario 2 update image generation options
set SCN_2_INPUT_FW_BIN=..\lora-e5.bin
set SCN_2_OUTPUT_UPD_IMG=lora_e5_iap_single_bank_demo_image_scenario_2.img
set SCN_2_FW_VERS=2.0.0
set SCN_2_CIPHER_ALGO=aes-cbc
set SCN_2_CIPHER_KEY=aa3ff7d43cc015682c7dfd00de9379e7
set SCN_2_AUTH_ALGO=hmac-md5
set SCN_2_AUTH_KEY=107b8d4bf62d1c9e26968e8ff51a74df

REM Scenario 3 update image generation options
set SCN_3_INPUT_FW_BIN=..\lora-e5.bin
set SCN_3_OUTPUT_UPD_IMG=lora_e5_iap_single_bank_demo_image_scenario_3.img
set SCN_3_FW_VERS=2.0.0
set SCN_3_CIPHER_ALGO=aes-cbc
set SCN_3_CIPHER_KEY=aa3ff7d43cc015682c7dfd00de9379e7
set SCN_3_SIGN_ALGO=rsa-sha256
set SCN_3_SIGN_KEY="..\resources\keys\rsa_private_key.pem"

REM Generate update image from the http server iap singel bank demo binary for the scenario 1
echo Generating update image for the scenario 1...
%APP_IMAGE_BUILDER_EXE% --input %SCN_1_INPUT_FW_BIN% --output %SCN_1_OUTPUT_UPD_IMG% --firmware-version %SCN_1_FW_VERS%^
   --integrity-algo %SCN_1_INTEGRITY_ALGO%
REM Generate update image from the http server iap singel bank demo binary for the scenario 2
echo Generating update image for the scenario 2...
%APP_IMAGE_BUILDER_EXE% --input %SCN_2_INPUT_FW_BIN% --output %SCN_2_OUTPUT_UPD_IMG% --firmware-version %SCN_2_FW_VERS%^
   --enc-algo %SCN_2_CIPHER_ALGO% --enc-key %SCN_2_CIPHER_KEY% --auth-algo %SCN_2_AUTH_ALGO% --auth-key %SCN_2_AUTH_KEY%
REM Generate update image from the http server iap singel bank demo binary for the scenario 3
echo Generating update image for the scenario 3...
%APP_IMAGE_BUILDER_EXE% --input %SCN_3_INPUT_FW_BIN% --output %SCN_3_OUTPUT_UPD_IMG% --firmware-version %SCN_3_FW_VERS%^
   --enc-algo %SCN_3_CIPHER_ALGO% --enc-key %SCN_3_CIPHER_KEY% --sign-algo %SCN_3_SIGN_ALGO% --sign-key  %SCN_3_SIGN_KEY%

echo Done.
pause

@echo off

REM Application image builder utility executable
set APP_IMAGE_BUILDER_EXE=..\..\Oryx\utils\AppImageBuilder\bin\app_image_builder_windows.exe

REM Internal image generation options
set INT_INPUT_FW_BIN=..\lora-e5.bin
set INT_OUTPUT_INT_IMG=lora_e5_iap_single_bank_demo_image_int.img
set INT_FW_VERS=1.0.0
set INT_IMAGE_INDEX=0
set INT_INTEGRITY_ALGO=crc32

REM Generate internal image from the http server iap singel bank demo binary. This internal image hold the initial firmware binary.
echo Generating internal image (contains initial firmware)...
%APP_IMAGE_BUILDER_EXE% --input %INT_INPUT_FW_BIN% --output %INT_OUTPUT_INT_IMG% --firmware-version %INT_FW_VERS%^
   --firmware-index %INT_IMAGE_INDEX% --integrity-algo %INT_INTEGRITY_ALGO% --add-padding

echo Done.
pause

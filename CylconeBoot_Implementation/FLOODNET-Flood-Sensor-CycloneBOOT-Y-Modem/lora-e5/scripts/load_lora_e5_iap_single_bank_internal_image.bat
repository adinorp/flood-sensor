@echo off

REM STM32CubeProgrammer
REM   1. STM32CubeProgrammer must be installed first : https://www.st.com/en/development-tools/stm32cubeprog.html
REM   2. Add STM32CubeProgrammer CLI executable to the environment PATH
set STM32_CUBE_PROGRAMMER_EXE=STM32_Programmer_CLI.exe
REM Internal image file
set INT_IMG=lora_e5_iap_single_bank_demo_image_int.img
REM Internal image flash load address
set INT_IMG_LOAD_ADDR=0x08008000

REM Erase external flash memory slot 1
Call erase_external_flash_slot1.bat

if exist %INT_IMG%.bin (
   REM Delete previous internal image binary file
   del %INT_IMG%.bin
)   

REM Copy internal image into an equivalent binary file (ST-LINK_CLI utility support .bin file)
copy %INT_IMG% %INT_IMG%.bin

REM Load internal image binary file in to internal flash
echo Loading lora-e5 internal image in to internal flash at %INT_IMG_LOAD_ADDR%...
%STM32_CUBE_PROGRAMMER_EXE% -c port=SWD index=0 -d %INT_IMG%.bin %INT_IMG_LOAD_ADDR% -halt -rst

REM delete binary file
del %INT_IMG%.bin

pause

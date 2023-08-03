@echo off

REM STM32CubeProgrammer
REM   1. STM32CubeProgrammer must be installed first : https://www.st.com/en/development-tools/stm32cubeprog.html
REM   2. Add STM32CubeProgrammer CLI executable to the environment PATH
set STM32_CUBE_PROGRAMMER_EXE=STM32_Programmer_CLI.exe
REM Bootloader internal flash load address
set LOAD_ADDR=0x08000000

REM Load external flash eraser in flash
echo Loading external flash eraser (mode : erase entire flash) into internal flash at %LOAD_ADDR%...
%STM32_CUBE_PROGRAMMER_EXE% -c port=SWD index=0 -d ..\..\external_flash_eraser\erase_entire_external_flash.bin %LOAD_ADDR% -halt -rst -run

timeout 5 > NUL

echo Erasing external flash eraser from flash...
%STM32_CUBE_PROGRAMMER_EXE% -c port=SWD index=0 -e [0 15]

echo Done.

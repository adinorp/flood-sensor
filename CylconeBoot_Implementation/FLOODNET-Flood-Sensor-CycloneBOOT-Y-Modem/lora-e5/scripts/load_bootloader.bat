@echo off

REM STM32CubeProgrammer
REM   1. STM32CubeProgrammer must be installed first : https://www.st.com/en/development-tools/stm32cubeprog.html
REM   2. Add STM32CubeProgrammer CLI executable to the environment PATH
set STM32_CUBE_PROGRAMMER_EXE=STM32_Programmer_CLI.exe
REM Bootloader internal flash load address
set BOOT_LOAD_ADDR=0x08000000

REM Load micro bootloader in flash
echo Loading bootloader in to internal flash at %BOOT_LOAD_ADDR%...
%STM32_CUBE_PROGRAMMER_EXE% -c port=SWD index=0 -d ..\..\micro_bootloader\micro_bootloader.bin %BOOT_LOAD_ADDR%

echo Done.
pause

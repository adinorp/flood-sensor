################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/debug.c \
../Core/Src/main.c \
../Core/Src/stm32wlxx_hal_msp.c \
../Core/Src/stm32wlxx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32wlxx.c 

OBJS += \
./Core/Src/debug.o \
./Core/Src/main.o \
./Core/Src/stm32wlxx_hal_msp.o \
./Core/Src/stm32wlxx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32wlxx.o 

C_DEPS += \
./Core/Src/debug.d \
./Core/Src/main.d \
./Core/Src/stm32wlxx_hal_msp.d \
./Core/Src/stm32wlxx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32wlxx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/debug.cyclo ./Core/Src/debug.d ./Core/Src/debug.o ./Core/Src/debug.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32wlxx_hal_msp.cyclo ./Core/Src/stm32wlxx_hal_msp.d ./Core/Src/stm32wlxx_hal_msp.o ./Core/Src/stm32wlxx_hal_msp.su ./Core/Src/stm32wlxx_it.cyclo ./Core/Src/stm32wlxx_it.d ./Core/Src/stm32wlxx_it.o ./Core/Src/stm32wlxx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32wlxx.cyclo ./Core/Src/system_stm32wlxx.d ./Core/Src/system_stm32wlxx.o ./Core/Src/system_stm32wlxx.su

.PHONY: clean-Core-2f-Src


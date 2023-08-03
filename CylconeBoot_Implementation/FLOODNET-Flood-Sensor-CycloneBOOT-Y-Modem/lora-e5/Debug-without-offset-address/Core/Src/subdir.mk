################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/app_freertos.c \
../Core/Src/common.c \
../Core/Src/debug.c \
../Core/Src/main.c \
../Core/Src/res.c \
../Core/Src/stm32wlxx_hal_msp.c \
../Core/Src/stm32wlxx_hal_timebase_tim.c \
../Core/Src/stm32wlxx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32wlxx.c \
../Core/Src/uart_user.c \
../Core/Src/ymodem.c 

OBJS += \
./Core/Src/app_freertos.o \
./Core/Src/common.o \
./Core/Src/debug.o \
./Core/Src/main.o \
./Core/Src/res.o \
./Core/Src/stm32wlxx_hal_msp.o \
./Core/Src/stm32wlxx_hal_timebase_tim.o \
./Core/Src/stm32wlxx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32wlxx.o \
./Core/Src/uart_user.o \
./Core/Src/ymodem.o 

C_DEPS += \
./Core/Src/app_freertos.d \
./Core/Src/common.d \
./Core/Src/debug.d \
./Core/Src/main.d \
./Core/Src/res.d \
./Core/Src/stm32wlxx_hal_msp.d \
./Core/Src/stm32wlxx_hal_timebase_tim.d \
./Core/Src/stm32wlxx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32wlxx.d \
./Core/Src/uart_user.d \
./Core/Src/ymodem.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -DCYCLONE_BOOT_IAP -c -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Core/Inc" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/CMSIS/Include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/FloodnetDriver" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/FloodnetTasks" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/common" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/cyclone_boot" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/cyclone_crypto" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/app_freertos.cyclo ./Core/Src/app_freertos.d ./Core/Src/app_freertos.o ./Core/Src/app_freertos.su ./Core/Src/common.cyclo ./Core/Src/common.d ./Core/Src/common.o ./Core/Src/common.su ./Core/Src/debug.cyclo ./Core/Src/debug.d ./Core/Src/debug.o ./Core/Src/debug.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/res.cyclo ./Core/Src/res.d ./Core/Src/res.o ./Core/Src/res.su ./Core/Src/stm32wlxx_hal_msp.cyclo ./Core/Src/stm32wlxx_hal_msp.d ./Core/Src/stm32wlxx_hal_msp.o ./Core/Src/stm32wlxx_hal_msp.su ./Core/Src/stm32wlxx_hal_timebase_tim.cyclo ./Core/Src/stm32wlxx_hal_timebase_tim.d ./Core/Src/stm32wlxx_hal_timebase_tim.o ./Core/Src/stm32wlxx_hal_timebase_tim.su ./Core/Src/stm32wlxx_it.cyclo ./Core/Src/stm32wlxx_it.d ./Core/Src/stm32wlxx_it.o ./Core/Src/stm32wlxx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32wlxx.cyclo ./Core/Src/system_stm32wlxx.d ./Core/Src/system_stm32wlxx.o ./Core/Src/system_stm32wlxx.su ./Core/Src/uart_user.cyclo ./Core/Src/uart_user.d ./Core/Src/uart_user.o ./Core/Src/uart_user.su ./Core/Src/ymodem.cyclo ./Core/Src/ymodem.d ./Core/Src/ymodem.o ./Core/Src/ymodem.su

.PHONY: clean-Core-2f-Src


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FloodnetDriver/ExtFlash.c \
../FloodnetDriver/Gpio.c \
../FloodnetDriver/Spi.c \
../FloodnetDriver/Uart.c 

OBJS += \
./FloodnetDriver/ExtFlash.o \
./FloodnetDriver/Gpio.o \
./FloodnetDriver/Spi.o \
./FloodnetDriver/Uart.o 

C_DEPS += \
./FloodnetDriver/ExtFlash.d \
./FloodnetDriver/Gpio.d \
./FloodnetDriver/Spi.d \
./FloodnetDriver/Uart.d 


# Each subdirectory must supply rules for building sources it contributes
FloodnetDriver/%.o FloodnetDriver/%.su FloodnetDriver/%.cyclo: ../FloodnetDriver/%.c FloodnetDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -c -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/Core/Inc" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/Drivers/CMSIS/Include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/FloodnetDriver" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/FloodnetTasks" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/../Oryx/common" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/../Oryx/cyclone_boot" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/external_flash_eraser/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FloodnetDriver

clean-FloodnetDriver:
	-$(RM) ./FloodnetDriver/ExtFlash.cyclo ./FloodnetDriver/ExtFlash.d ./FloodnetDriver/ExtFlash.o ./FloodnetDriver/ExtFlash.su ./FloodnetDriver/Gpio.cyclo ./FloodnetDriver/Gpio.d ./FloodnetDriver/Gpio.o ./FloodnetDriver/Gpio.su ./FloodnetDriver/Spi.cyclo ./FloodnetDriver/Spi.d ./FloodnetDriver/Spi.o ./FloodnetDriver/Spi.su ./FloodnetDriver/Uart.cyclo ./FloodnetDriver/Uart.d ./FloodnetDriver/Uart.o ./FloodnetDriver/Uart.su

.PHONY: clean-FloodnetDriver


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/%.o Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/%.su Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/%.cyclo: ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/%.c Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -DCYCLONE_BOOT_IAP -DVTOR_OFFSET_ADDR -c -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Core/Inc" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/CMSIS/Include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/FloodnetDriver" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/FloodnetTasks" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/common" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/cyclone_boot" -I"C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/cyclone_crypto" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.cyclo ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.d ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.o ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3


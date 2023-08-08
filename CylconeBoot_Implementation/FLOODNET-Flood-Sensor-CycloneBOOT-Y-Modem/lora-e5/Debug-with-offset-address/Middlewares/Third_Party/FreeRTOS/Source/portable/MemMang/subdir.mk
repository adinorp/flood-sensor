################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.o Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.su Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.cyclo: ../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.c Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -DCYCLONE_BOOT_IAP -DVTOR_OFFSET_ADDR -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/../Oryx/cyclone_crypto" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.cyclo ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o ./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/bootloader/boot.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/bootloader/boot_common.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/bootloader/boot_fallback.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/core/crc32.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/core/image.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/core/mailbox.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/core/slot.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/drivers/flash/internal/stm32wlxx_flash_driver.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/drivers/mcu/arm/stm32wlxx_mcu_driver.c \
C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/drivers/flash/external/w25q80dv_flash_driver.c 

OBJS += \
./CycloneBOOT_Sources/boot.o \
./CycloneBOOT_Sources/boot_common.o \
./CycloneBOOT_Sources/boot_fallback.o \
./CycloneBOOT_Sources/crc32.o \
./CycloneBOOT_Sources/image.o \
./CycloneBOOT_Sources/mailbox.o \
./CycloneBOOT_Sources/slot.o \
./CycloneBOOT_Sources/stm32wlxx_flash_driver.o \
./CycloneBOOT_Sources/stm32wlxx_mcu_driver.o \
./CycloneBOOT_Sources/w25q80dv_flash_driver.o 

C_DEPS += \
./CycloneBOOT_Sources/boot.d \
./CycloneBOOT_Sources/boot_common.d \
./CycloneBOOT_Sources/boot_fallback.d \
./CycloneBOOT_Sources/crc32.d \
./CycloneBOOT_Sources/image.d \
./CycloneBOOT_Sources/mailbox.d \
./CycloneBOOT_Sources/slot.d \
./CycloneBOOT_Sources/stm32wlxx_flash_driver.d \
./CycloneBOOT_Sources/stm32wlxx_mcu_driver.d \
./CycloneBOOT_Sources/w25q80dv_flash_driver.d 


# Each subdirectory must supply rules for building sources it contributes
CycloneBOOT_Sources/boot.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/bootloader/boot.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/boot_common.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/bootloader/boot_common.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/boot_fallback.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/bootloader/boot_fallback.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/crc32.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/core/crc32.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/image.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/core/image.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/mailbox.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/core/mailbox.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/slot.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/core/slot.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/stm32wlxx_flash_driver.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/drivers/flash/internal/stm32wlxx_flash_driver.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/stm32wlxx_mcu_driver.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/drivers/mcu/arm/stm32wlxx_mcu_driver.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CycloneBOOT_Sources/w25q80dv_flash_driver.o: C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/Oryx/cyclone_boot/drivers/flash/external/w25q80dv_flash_driver.c CycloneBOOT_Sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -DUSER_VECT_TAB_ADDRESS -DSTM32LxxxC -DFLASH_SINGLE_BANK -c -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Core/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Drivers/CMSIS/Include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetDriver" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/FloodnetTasks" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/common" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_boot" -I"C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/../Oryx/cyclone_crypto" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CycloneBOOT_Sources

clean-CycloneBOOT_Sources:
	-$(RM) ./CycloneBOOT_Sources/boot.cyclo ./CycloneBOOT_Sources/boot.d ./CycloneBOOT_Sources/boot.o ./CycloneBOOT_Sources/boot.su ./CycloneBOOT_Sources/boot_common.cyclo ./CycloneBOOT_Sources/boot_common.d ./CycloneBOOT_Sources/boot_common.o ./CycloneBOOT_Sources/boot_common.su ./CycloneBOOT_Sources/boot_fallback.cyclo ./CycloneBOOT_Sources/boot_fallback.d ./CycloneBOOT_Sources/boot_fallback.o ./CycloneBOOT_Sources/boot_fallback.su ./CycloneBOOT_Sources/crc32.cyclo ./CycloneBOOT_Sources/crc32.d ./CycloneBOOT_Sources/crc32.o ./CycloneBOOT_Sources/crc32.su ./CycloneBOOT_Sources/image.cyclo ./CycloneBOOT_Sources/image.d ./CycloneBOOT_Sources/image.o ./CycloneBOOT_Sources/image.su ./CycloneBOOT_Sources/mailbox.cyclo ./CycloneBOOT_Sources/mailbox.d ./CycloneBOOT_Sources/mailbox.o ./CycloneBOOT_Sources/mailbox.su ./CycloneBOOT_Sources/slot.cyclo ./CycloneBOOT_Sources/slot.d ./CycloneBOOT_Sources/slot.o ./CycloneBOOT_Sources/slot.su ./CycloneBOOT_Sources/stm32wlxx_flash_driver.cyclo ./CycloneBOOT_Sources/stm32wlxx_flash_driver.d ./CycloneBOOT_Sources/stm32wlxx_flash_driver.o ./CycloneBOOT_Sources/stm32wlxx_flash_driver.su ./CycloneBOOT_Sources/stm32wlxx_mcu_driver.cyclo ./CycloneBOOT_Sources/stm32wlxx_mcu_driver.d ./CycloneBOOT_Sources/stm32wlxx_mcu_driver.o ./CycloneBOOT_Sources/stm32wlxx_mcu_driver.su ./CycloneBOOT_Sources/w25q80dv_flash_driver.cyclo ./CycloneBOOT_Sources/w25q80dv_flash_driver.d ./CycloneBOOT_Sources/w25q80dv_flash_driver.o ./CycloneBOOT_Sources/w25q80dv_flash_driver.su

.PHONY: clean-CycloneBOOT_Sources


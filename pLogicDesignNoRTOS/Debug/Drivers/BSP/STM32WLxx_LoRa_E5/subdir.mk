################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5.c \
../Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5_radio.c 

OBJS += \
./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5.o \
./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5_radio.o 

C_DEPS += \
./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5.d \
./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5_radio.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32WLxx_LoRa_E5/%.o Drivers/BSP/STM32WLxx_LoRa_E5/%.su Drivers/BSP/STM32WLxx_LoRa_E5/%.cyclo: ../Drivers/BSP/STM32WLxx_LoRa_E5/%.c Drivers/BSP/STM32WLxx_LoRa_E5/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/BSP/STM32WLxx_LoRa_E5 -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32WLxx_LoRa_E5

clean-Drivers-2f-BSP-2f-STM32WLxx_LoRa_E5:
	-$(RM) ./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5.cyclo ./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5.d ./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5.o ./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5.su ./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5_radio.cyclo ./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5_radio.d ./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5_radio.o ./Drivers/BSP/STM32WLxx_LoRa_E5/stm32wlxx_LoRa_E5_radio.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32WLxx_LoRa_E5


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FloodnetDrivers/Uart_Driver.c 

OBJS += \
./FloodnetDrivers/Uart_Driver.o 

C_DEPS += \
./FloodnetDrivers/Uart_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
FloodnetDrivers/%.o FloodnetDrivers/%.su FloodnetDrivers/%.cyclo: ../FloodnetDrivers/%.c FloodnetDrivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I"../Tasks/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FloodnetDrivers

clean-FloodnetDrivers:
	-$(RM) ./FloodnetDrivers/Uart_Driver.cyclo ./FloodnetDrivers/Uart_Driver.d ./FloodnetDrivers/Uart_Driver.o ./FloodnetDrivers/Uart_Driver.su

.PHONY: clean-FloodnetDrivers


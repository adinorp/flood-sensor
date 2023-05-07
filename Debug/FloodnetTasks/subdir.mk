################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FloodnetTasks/TerminalTask.c 

OBJS += \
./FloodnetTasks/TerminalTask.o 

C_DEPS += \
./FloodnetTasks/TerminalTask.d 


# Each subdirectory must supply rules for building sources it contributes
FloodnetTasks/%.o FloodnetTasks/%.su FloodnetTasks/%.cyclo: ../FloodnetTasks/%.c FloodnetTasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I"../FloodnetDriver/" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FloodnetTasks

clean-FloodnetTasks:
	-$(RM) ./FloodnetTasks/TerminalTask.cyclo ./FloodnetTasks/TerminalTask.d ./FloodnetTasks/TerminalTask.o ./FloodnetTasks/TerminalTask.su

.PHONY: clean-FloodnetTasks


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FloodnetDriver/Ic2.c \
../FloodnetDriver/Spi.c \
../FloodnetDriver/Uart.c 

OBJS += \
./FloodnetDriver/Ic2.o \
./FloodnetDriver/Spi.o \
./FloodnetDriver/Uart.o 

C_DEPS += \
./FloodnetDriver/Ic2.d \
./FloodnetDriver/Spi.d \
./FloodnetDriver/Uart.d 


# Each subdirectory must supply rules for building sources it contributes
FloodnetDriver/%.o FloodnetDriver/%.su FloodnetDriver/%.cyclo: ../FloodnetDriver/%.c FloodnetDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I"../FloodnetDriver/" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FloodnetDriver

clean-FloodnetDriver:
	-$(RM) ./FloodnetDriver/Ic2.cyclo ./FloodnetDriver/Ic2.d ./FloodnetDriver/Ic2.o ./FloodnetDriver/Ic2.su ./FloodnetDriver/Spi.cyclo ./FloodnetDriver/Spi.d ./FloodnetDriver/Spi.o ./FloodnetDriver/Spi.su ./FloodnetDriver/Uart.cyclo ./FloodnetDriver/Uart.d ./FloodnetDriver/Uart.o ./FloodnetDriver/Uart.su

.PHONY: clean-FloodnetDriver


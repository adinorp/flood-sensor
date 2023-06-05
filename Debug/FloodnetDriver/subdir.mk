################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FloodnetDriver/Adc.c \
../FloodnetDriver/Bme280.c \
../FloodnetDriver/DeviceCommands.c \
../FloodnetDriver/ExtFlash.c \
../FloodnetDriver/Gpio.c \
../FloodnetDriver/I2c.c \
../FloodnetDriver/Rtc.c \
../FloodnetDriver/Spi.c \
../FloodnetDriver/Uart.c 

OBJS += \
./FloodnetDriver/Adc.o \
./FloodnetDriver/Bme280.o \
./FloodnetDriver/DeviceCommands.o \
./FloodnetDriver/ExtFlash.o \
./FloodnetDriver/Gpio.o \
./FloodnetDriver/I2c.o \
./FloodnetDriver/Rtc.o \
./FloodnetDriver/Spi.o \
./FloodnetDriver/Uart.o 

C_DEPS += \
./FloodnetDriver/Adc.d \
./FloodnetDriver/Bme280.d \
./FloodnetDriver/DeviceCommands.d \
./FloodnetDriver/ExtFlash.d \
./FloodnetDriver/Gpio.d \
./FloodnetDriver/I2c.d \
./FloodnetDriver/Rtc.d \
./FloodnetDriver/Spi.d \
./FloodnetDriver/Uart.d 


# Each subdirectory must supply rules for building sources it contributes
FloodnetDriver/%.o FloodnetDriver/%.su FloodnetDriver/%.cyclo: ../FloodnetDriver/%.c FloodnetDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I"../FloodnetDriver/" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FloodnetDriver

clean-FloodnetDriver:
	-$(RM) ./FloodnetDriver/Adc.cyclo ./FloodnetDriver/Adc.d ./FloodnetDriver/Adc.o ./FloodnetDriver/Adc.su ./FloodnetDriver/Bme280.cyclo ./FloodnetDriver/Bme280.d ./FloodnetDriver/Bme280.o ./FloodnetDriver/Bme280.su ./FloodnetDriver/DeviceCommands.cyclo ./FloodnetDriver/DeviceCommands.d ./FloodnetDriver/DeviceCommands.o ./FloodnetDriver/DeviceCommands.su ./FloodnetDriver/ExtFlash.cyclo ./FloodnetDriver/ExtFlash.d ./FloodnetDriver/ExtFlash.o ./FloodnetDriver/ExtFlash.su ./FloodnetDriver/Gpio.cyclo ./FloodnetDriver/Gpio.d ./FloodnetDriver/Gpio.o ./FloodnetDriver/Gpio.su ./FloodnetDriver/I2c.cyclo ./FloodnetDriver/I2c.d ./FloodnetDriver/I2c.o ./FloodnetDriver/I2c.su ./FloodnetDriver/Rtc.cyclo ./FloodnetDriver/Rtc.d ./FloodnetDriver/Rtc.o ./FloodnetDriver/Rtc.su ./FloodnetDriver/Spi.cyclo ./FloodnetDriver/Spi.d ./FloodnetDriver/Spi.o ./FloodnetDriver/Spi.su ./FloodnetDriver/Uart.cyclo ./FloodnetDriver/Uart.d ./FloodnetDriver/Uart.o ./FloodnetDriver/Uart.su

.PHONY: clean-FloodnetDriver


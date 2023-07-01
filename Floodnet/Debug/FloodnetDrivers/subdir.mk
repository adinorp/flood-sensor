################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FloodnetDrivers/Adc.c \
../FloodnetDrivers/Bme280.c \
../FloodnetDrivers/DeviceCommands.c \
../FloodnetDrivers/ExtFlash.c \
../FloodnetDrivers/Gpio.c \
../FloodnetDrivers/I2c.c \
../FloodnetDrivers/Maxbotix.c \
../FloodnetDrivers/Spi.c \
../FloodnetDrivers/Uart.c 

OBJS += \
./FloodnetDrivers/Adc.o \
./FloodnetDrivers/Bme280.o \
./FloodnetDrivers/DeviceCommands.o \
./FloodnetDrivers/ExtFlash.o \
./FloodnetDrivers/Gpio.o \
./FloodnetDrivers/I2c.o \
./FloodnetDrivers/Maxbotix.o \
./FloodnetDrivers/Spi.o \
./FloodnetDrivers/Uart.o 

C_DEPS += \
./FloodnetDrivers/Adc.d \
./FloodnetDrivers/Bme280.d \
./FloodnetDrivers/DeviceCommands.d \
./FloodnetDrivers/ExtFlash.d \
./FloodnetDrivers/Gpio.d \
./FloodnetDrivers/I2c.d \
./FloodnetDrivers/Maxbotix.d \
./FloodnetDrivers/Spi.d \
./FloodnetDrivers/Uart.d 


# Each subdirectory must supply rules for building sources it contributes
FloodnetDrivers/%.o FloodnetDrivers/%.su FloodnetDrivers/%.cyclo: ../FloodnetDrivers/%.c FloodnetDrivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/FloodnetDriver" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Core/Inc" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Drivers/CMSIS/Include" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FloodnetDrivers

clean-FloodnetDrivers:
	-$(RM) ./FloodnetDrivers/Adc.cyclo ./FloodnetDrivers/Adc.d ./FloodnetDrivers/Adc.o ./FloodnetDrivers/Adc.su ./FloodnetDrivers/Bme280.cyclo ./FloodnetDrivers/Bme280.d ./FloodnetDrivers/Bme280.o ./FloodnetDrivers/Bme280.su ./FloodnetDrivers/DeviceCommands.cyclo ./FloodnetDrivers/DeviceCommands.d ./FloodnetDrivers/DeviceCommands.o ./FloodnetDrivers/DeviceCommands.su ./FloodnetDrivers/ExtFlash.cyclo ./FloodnetDrivers/ExtFlash.d ./FloodnetDrivers/ExtFlash.o ./FloodnetDrivers/ExtFlash.su ./FloodnetDrivers/Gpio.cyclo ./FloodnetDrivers/Gpio.d ./FloodnetDrivers/Gpio.o ./FloodnetDrivers/Gpio.su ./FloodnetDrivers/I2c.cyclo ./FloodnetDrivers/I2c.d ./FloodnetDrivers/I2c.o ./FloodnetDrivers/I2c.su ./FloodnetDrivers/Maxbotix.cyclo ./FloodnetDrivers/Maxbotix.d ./FloodnetDrivers/Maxbotix.o ./FloodnetDrivers/Maxbotix.su ./FloodnetDrivers/Spi.cyclo ./FloodnetDrivers/Spi.d ./FloodnetDrivers/Spi.o ./FloodnetDrivers/Spi.su ./FloodnetDrivers/Uart.cyclo ./FloodnetDrivers/Uart.d ./FloodnetDrivers/Uart.o ./FloodnetDrivers/Uart.su

.PHONY: clean-FloodnetDrivers


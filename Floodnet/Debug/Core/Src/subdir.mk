################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Adc.c \
../Core/Src/Bme280.c \
../Core/Src/DeviceCommands.c \
../Core/Src/ExtFlash.c \
../Core/Src/Gpio.c \
../Core/Src/I2c.c \
../Core/Src/Maxbotix.c \
../Core/Src/Spi.c \
../Core/Src/TerminalTask.c \
../Core/Src/Uart.c \
../Core/Src/app_freertos.c \
../Core/Src/main.c \
../Core/Src/stm32wlxx_hal_msp.c \
../Core/Src/stm32wlxx_hal_timebase_tim.c \
../Core/Src/stm32wlxx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32wlxx.c 

OBJS += \
./Core/Src/Adc.o \
./Core/Src/Bme280.o \
./Core/Src/DeviceCommands.o \
./Core/Src/ExtFlash.o \
./Core/Src/Gpio.o \
./Core/Src/I2c.o \
./Core/Src/Maxbotix.o \
./Core/Src/Spi.o \
./Core/Src/TerminalTask.o \
./Core/Src/Uart.o \
./Core/Src/app_freertos.o \
./Core/Src/main.o \
./Core/Src/stm32wlxx_hal_msp.o \
./Core/Src/stm32wlxx_hal_timebase_tim.o \
./Core/Src/stm32wlxx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32wlxx.o 

C_DEPS += \
./Core/Src/Adc.d \
./Core/Src/Bme280.d \
./Core/Src/DeviceCommands.d \
./Core/Src/ExtFlash.d \
./Core/Src/Gpio.d \
./Core/Src/I2c.d \
./Core/Src/Maxbotix.d \
./Core/Src/Spi.d \
./Core/Src/TerminalTask.d \
./Core/Src/Uart.d \
./Core/Src/app_freertos.d \
./Core/Src/main.d \
./Core/Src/stm32wlxx_hal_msp.d \
./Core/Src/stm32wlxx_hal_timebase_tim.d \
./Core/Src/stm32wlxx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32wlxx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Core/Inc" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Drivers/STM32WLxx_HAL_Driver/Inc" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Drivers/CMSIS/Device/ST/STM32WLxx/Include" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Drivers/CMSIS/Include" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"C:/Users/adino/OneDrive/Documents/GitHub/flood-sensor/Floodnet/FloodnetDriver" -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Adc.cyclo ./Core/Src/Adc.d ./Core/Src/Adc.o ./Core/Src/Adc.su ./Core/Src/Bme280.cyclo ./Core/Src/Bme280.d ./Core/Src/Bme280.o ./Core/Src/Bme280.su ./Core/Src/DeviceCommands.cyclo ./Core/Src/DeviceCommands.d ./Core/Src/DeviceCommands.o ./Core/Src/DeviceCommands.su ./Core/Src/ExtFlash.cyclo ./Core/Src/ExtFlash.d ./Core/Src/ExtFlash.o ./Core/Src/ExtFlash.su ./Core/Src/Gpio.cyclo ./Core/Src/Gpio.d ./Core/Src/Gpio.o ./Core/Src/Gpio.su ./Core/Src/I2c.cyclo ./Core/Src/I2c.d ./Core/Src/I2c.o ./Core/Src/I2c.su ./Core/Src/Maxbotix.cyclo ./Core/Src/Maxbotix.d ./Core/Src/Maxbotix.o ./Core/Src/Maxbotix.su ./Core/Src/Spi.cyclo ./Core/Src/Spi.d ./Core/Src/Spi.o ./Core/Src/Spi.su ./Core/Src/TerminalTask.cyclo ./Core/Src/TerminalTask.d ./Core/Src/TerminalTask.o ./Core/Src/TerminalTask.su ./Core/Src/Uart.cyclo ./Core/Src/Uart.d ./Core/Src/Uart.o ./Core/Src/Uart.su ./Core/Src/app_freertos.cyclo ./Core/Src/app_freertos.d ./Core/Src/app_freertos.o ./Core/Src/app_freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32wlxx_hal_msp.cyclo ./Core/Src/stm32wlxx_hal_msp.d ./Core/Src/stm32wlxx_hal_msp.o ./Core/Src/stm32wlxx_hal_msp.su ./Core/Src/stm32wlxx_hal_timebase_tim.cyclo ./Core/Src/stm32wlxx_hal_timebase_tim.d ./Core/Src/stm32wlxx_hal_timebase_tim.o ./Core/Src/stm32wlxx_hal_timebase_tim.su ./Core/Src/stm32wlxx_it.cyclo ./Core/Src/stm32wlxx_it.d ./Core/Src/stm32wlxx_it.o ./Core/Src/stm32wlxx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32wlxx.cyclo ./Core/Src/system_stm32wlxx.d ./Core/Src/system_stm32wlxx.o ./Core/Src/system_stm32wlxx.su

.PHONY: clean-Core-2f-Src

################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include FloodnetTasks/subdir.mk
-include FloodnetDriver/subdir.mk
-include Drivers/STM32WLxx_HAL_Driver/Src/subdir.mk
-include CycloneCRYPTO_Sources/subdir.mk
-include CycloneBOOT_Sources/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Common_Sources/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := lora-e5
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
lora-e5.elf \

MAP_FILES += \
lora-e5.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
lora-e5.list \

OBJCOPY_BIN += \
lora-e5.bin \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: lora-e5.elf secondary-outputs

# Tool invocations
lora-e5.elf lora-e5.map: $(OBJS) $(USER_OBJS) C:\Users\adino\Downloads\2023_06_23_P_LOGIC_CycloneBOOT_Implementation\FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem\lora-e5\STM32WLE5JCIX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "lora-e5.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\adino\Downloads\2023_06_23_P_LOGIC_CycloneBOOT_Implementation\FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem\lora-e5\STM32WLE5JCIX_FLASH.ld" --specs=nosys.specs -Wl,-Map="lora-e5.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

lora-e5.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "lora-e5.list"
	@echo 'Finished building: $@'
	@echo ' '

lora-e5.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "lora-e5.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout lora-e5.bin lora-e5.elf lora-e5.list lora-e5.map
	-@echo ' '

post-build:
	wscript.exe C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/scripts/misc/copyFile.js C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/Debug-without-offset-address/lora-e5.bin C:/Users/adino/Downloads/2023_06_23_P_LOGIC_CycloneBOOT_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/lora-e5/lora-e5.bin
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets

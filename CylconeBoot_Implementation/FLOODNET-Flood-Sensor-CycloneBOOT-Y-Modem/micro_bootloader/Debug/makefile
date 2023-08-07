################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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


BUILD_ARTIFACT_NAME := micro_bootloader
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
micro_bootloader.elf \

MAP_FILES += \
micro_bootloader.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
micro_bootloader.list \

OBJCOPY_BIN += \
micro_bootloader.bin \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: micro_bootloader.elf secondary-outputs

# Tool invocations
micro_bootloader.elf micro_bootloader.map: $(OBJS) $(USER_OBJS) C:\Users\prane\OneDrive\Documents\GitHub\flood-sensor\CylconeBoot_Implementation\FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem\micro_bootloader\STM32WLE5JCIX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "micro_bootloader.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\prane\OneDrive\Documents\GitHub\flood-sensor\CylconeBoot_Implementation\FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem\micro_bootloader\STM32WLE5JCIX_FLASH.ld" --specs=nosys.specs -Wl,-Map="micro_bootloader.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

micro_bootloader.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "micro_bootloader.list"
	@echo 'Finished building: $@'
	@echo ' '

micro_bootloader.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "micro_bootloader.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout micro_bootloader.bin micro_bootloader.elf micro_bootloader.list micro_bootloader.map
	-@echo ' '

post-build:
	wscript.exe C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/scripts/misc/copyFile.js C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/Debug/micro_bootloader.bin C:/Users/prane/OneDrive/Documents/GitHub/flood-sensor/CylconeBoot_Implementation/FLOODNET-Flood-Sensor-CycloneBOOT-Y-Modem/micro_bootloader/micro_bootloader.bin
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets

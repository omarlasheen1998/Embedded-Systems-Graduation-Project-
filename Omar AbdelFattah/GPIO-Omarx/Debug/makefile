################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
GPIO-Omarx.lss \

FLASH_IMAGE += \
GPIO-Omarx.hex \

EEPROM_IMAGE += \
GPIO-Omarx.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: GPIO-Omarx.elf secondary-outputs

# Tool invocations
GPIO-Omarx.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,GPIO-Omarx.map -mmcu=atmega32 -o "GPIO-Omarx.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

GPIO-Omarx.lss: GPIO-Omarx.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S GPIO-Omarx.elf  >"GPIO-Omarx.lss"
	@echo 'Finished building: $@'
	@echo ' '

GPIO-Omarx.hex: GPIO-Omarx.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex GPIO-Omarx.elf  "GPIO-Omarx.hex"
	@echo 'Finished building: $@'
	@echo ' '

GPIO-Omarx.eep: GPIO-Omarx.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex GPIO-Omarx.elf  "GPIO-Omarx.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: GPIO-Omarx.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 GPIO-Omarx.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: GPIO-Omarx.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:GPIO-Omarx.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) GPIO-Omarx.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

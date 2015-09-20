################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include modules/sys/devices/subdir.mk
-include modules/sys/subdir.mk
-include modules/sound/subdir.mk
-include modules/net/subdir.mk
-include modules/fs/ext2/subdir.mk
-include modules/fs/subdir.mk
-include modules/drivers/sound/ac97/subdir.mk
-include modules/drivers/sound/subdir.mk
-include modules/drivers/ps2/mouse/subdir.mk
-include modules/drivers/ps2/keyboard/subdir.mk
-include modules/drivers/net/rtl8139/subdir.mk
-include modules/drivers/io/subdir.mk
-include modules/drivers/gpu/subdir.mk
-include modules/drivers/ata/subdir.mk
-include libraries/lib/data_struct/subdir.mk
-include libraries/lib/subdir.mk
-include kernel/sys/task/subdir.mk
-include kernel/sys/sysvector/subdir.mk
-include kernel/sys/ring3/subdir.mk
-include kernel/sys/error/subdir.mk
-include kernel/sys/subdir.mk
-include kernel/mem/subdir.mk
-include kernel/internal/subdir.mk
-include kernel/debug/subdir.mk
-include kernel/subdir.mk
-include init/subdir.mk
-include fs/subdir.mk
-include arch/x86/cpu/isr/subdir.mk
-include arch/x86/cpu/irq/subdir.mk
-include arch/x86/cpu/idt/subdir.mk
-include arch/x86/cpu/gdt/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: munix

# Tool invocations
munix: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	i686-elf-gcc -T "/home/miguel/git/munix/munix/kernel/link.ld" -nostdlib -o "munix" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) munix
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

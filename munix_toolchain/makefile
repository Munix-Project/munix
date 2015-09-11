################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
all: pre-build main-build

# Main-build Target
main-build: munix-kernel

# Tool invocations
munix-kernel: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	i686-munix-gcc -T "/home/miguel/git/munix/init/link.ld" -nostdlib -lgcc -std=c99 -O2 -Wall -finline-functions -ffreestanding -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wno-format -pedantic -fno-omit-frame-pointer -D_KERNEL_ -o "munix-kernel" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) munix-kernel
	-@echo ' '

pre-build:
	-@echo 'Generating Assembly Symbols for kernel compilation . . .'
	-"/home/miguel/git/munix/munix_toolchain/util/symbols/generate_sym.sh"
	-@echo ' '

post-build:
	-@echo 'Building Modules . . .'
	-"/home/miguel/git/munix/munix_toolchain/util/build_modules/build_modules.sh"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets

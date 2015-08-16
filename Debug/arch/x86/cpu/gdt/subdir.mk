################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../arch/x86/cpu/gdt/gdt.c 

S_UPPER_SRCS += \
../arch/x86/cpu/gdt/gdt_flush.S 

OBJS += \
./arch/x86/cpu/gdt/gdt.o \
./arch/x86/cpu/gdt/gdt_flush.o 

C_DEPS += \
./arch/x86/cpu/gdt/gdt.d 


# Each subdirectory must supply rules for building sources it contributes
arch/x86/cpu/gdt/%.o: ../arch/x86/cpu/gdt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arch/x86/cpu/gdt/%.o: ../arch/x86/cpu/gdt/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	i686-elf-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



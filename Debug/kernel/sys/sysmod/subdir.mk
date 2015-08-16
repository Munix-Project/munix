################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/sys/sysmod/module.c 

S_UPPER_SRCS += \
../kernel/sys/sysmod/symbols.S 

OBJS += \
./kernel/sys/sysmod/module.o \
./kernel/sys/sysmod/symbols.o 

C_DEPS += \
./kernel/sys/sysmod/module.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/sys/sysmod/%.o: ../kernel/sys/sysmod/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kernel/sys/sysmod/%.o: ../kernel/sys/sysmod/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	i686-elf-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



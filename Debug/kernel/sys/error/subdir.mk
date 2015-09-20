################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/sys/error/panic.c 

OBJS += \
./kernel/sys/error/panic.o 

C_DEPS += \
./kernel/sys/error/panic.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/sys/error/%.o: ../kernel/sys/error/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



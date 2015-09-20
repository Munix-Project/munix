################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/sys/sysvector/syscall.c 

OBJS += \
./kernel/sys/sysvector/syscall.o 

C_DEPS += \
./kernel/sys/sysvector/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/sys/sysvector/%.o: ../kernel/sys/sysvector/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/misc/testmodule.c 

OBJS += \
./modules/misc/testmodule.o 

C_DEPS += \
./modules/misc/testmodule.d 


# Each subdirectory must supply rules for building sources it contributes
modules/misc/%.o: ../modules/misc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



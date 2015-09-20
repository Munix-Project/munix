################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/drivers/ps2/keyboard/kbd.c 

OBJS += \
./modules/drivers/ps2/keyboard/kbd.o 

C_DEPS += \
./modules/drivers/ps2/keyboard/kbd.d 


# Each subdirectory must supply rules for building sources it contributes
modules/drivers/ps2/keyboard/%.o: ../modules/drivers/ps2/keyboard/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



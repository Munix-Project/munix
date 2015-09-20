################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/drivers/ata/ata.c 

OBJS += \
./modules/drivers/ata/ata.o 

C_DEPS += \
./modules/drivers/ata/ata.d 


# Each subdirectory must supply rules for building sources it contributes
modules/drivers/ata/%.o: ../modules/drivers/ata/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



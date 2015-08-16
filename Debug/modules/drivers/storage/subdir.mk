################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/drivers/storage/ata.c 

OBJS += \
./modules/drivers/storage/ata.o 

C_DEPS += \
./modules/drivers/storage/ata.d 


# Each subdirectory must supply rules for building sources it contributes
modules/drivers/storage/%.o: ../modules/drivers/storage/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



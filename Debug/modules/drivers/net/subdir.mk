################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/drivers/net/packetfs.c 

OBJS += \
./modules/drivers/net/packetfs.o 

C_DEPS += \
./modules/drivers/net/packetfs.d 


# Each subdirectory must supply rules for building sources it contributes
modules/drivers/net/%.o: ../modules/drivers/net/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



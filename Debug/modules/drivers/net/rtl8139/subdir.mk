################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/drivers/net/rtl8139/rtl8139.c 

OBJS += \
./modules/drivers/net/rtl8139/rtl8139.o 

C_DEPS += \
./modules/drivers/net/rtl8139/rtl8139.d 


# Each subdirectory must supply rules for building sources it contributes
modules/drivers/net/rtl8139/%.o: ../modules/drivers/net/rtl8139/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



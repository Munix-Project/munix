################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/fs/ext2/ext2.c 

OBJS += \
./modules/fs/ext2/ext2.o 

C_DEPS += \
./modules/fs/ext2/ext2.d 


# Each subdirectory must supply rules for building sources it contributes
modules/fs/ext2/%.o: ../modules/fs/ext2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



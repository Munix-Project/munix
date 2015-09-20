################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/drivers/gpu/lfbvideo.c \
../modules/drivers/gpu/vgadbg.c 

OBJS += \
./modules/drivers/gpu/lfbvideo.o \
./modules/drivers/gpu/vgadbg.o 

C_DEPS += \
./modules/drivers/gpu/lfbvideo.d \
./modules/drivers/gpu/vgadbg.d 


# Each subdirectory must supply rules for building sources it contributes
modules/drivers/gpu/%.o: ../modules/drivers/gpu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



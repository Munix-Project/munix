################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/drivers/graphics/lfbvideo.c \
../modules/drivers/graphics/vgadbg.c 

OBJS += \
./modules/drivers/graphics/lfbvideo.o \
./modules/drivers/graphics/vgadbg.o 

C_DEPS += \
./modules/drivers/graphics/lfbvideo.d \
./modules/drivers/graphics/vgadbg.d 


# Each subdirectory must supply rules for building sources it contributes
modules/drivers/graphics/%.o: ../modules/drivers/graphics/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



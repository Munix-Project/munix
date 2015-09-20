################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/sys/devices/null.c \
../modules/sys/devices/random.c \
../modules/sys/devices/zero.c 

OBJS += \
./modules/sys/devices/null.o \
./modules/sys/devices/random.o \
./modules/sys/devices/zero.o 

C_DEPS += \
./modules/sys/devices/null.d \
./modules/sys/devices/random.d \
./modules/sys/devices/zero.d 


# Each subdirectory must supply rules for building sources it contributes
modules/sys/devices/%.o: ../modules/sys/devices/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



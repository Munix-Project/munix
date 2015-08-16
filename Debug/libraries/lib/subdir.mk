################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/lib/kprintf.c \
../libraries/lib/libc.c \
../libraries/lib/tokenize.c 

OBJS += \
./libraries/lib/kprintf.o \
./libraries/lib/libc.o \
./libraries/lib/tokenize.o 

C_DEPS += \
./libraries/lib/kprintf.d \
./libraries/lib/libc.d \
./libraries/lib/tokenize.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/lib/%.o: ../libraries/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



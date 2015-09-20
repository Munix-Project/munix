################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/internal/cmos.c \
../kernel/internal/fpu.c \
../kernel/internal/pci.c \
../kernel/internal/timer.c 

OBJS += \
./kernel/internal/cmos.o \
./kernel/internal/fpu.o \
./kernel/internal/pci.o \
./kernel/internal/timer.o 

C_DEPS += \
./kernel/internal/cmos.d \
./kernel/internal/fpu.d \
./kernel/internal/pci.d \
./kernel/internal/timer.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/internal/%.o: ../kernel/internal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/mem/alloc.c \
../kernel/mem/mem.c \
../kernel/mem/shm.c 

OBJS += \
./kernel/mem/alloc.o \
./kernel/mem/mem.o \
./kernel/mem/shm.o 

C_DEPS += \
./kernel/mem/alloc.d \
./kernel/mem/mem.d \
./kernel/mem/shm.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/mem/%.o: ../kernel/mem/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



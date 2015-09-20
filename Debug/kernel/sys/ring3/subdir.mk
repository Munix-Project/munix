################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/sys/ring3/user.c 

S_UPPER_SRCS += \
../kernel/sys/ring3/user_goring3.S 

OBJS += \
./kernel/sys/ring3/user.o \
./kernel/sys/ring3/user_goring3.o 

C_DEPS += \
./kernel/sys/ring3/user.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/sys/ring3/%.o: ../kernel/sys/ring3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kernel/sys/ring3/%.o: ../kernel/sys/ring3/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	i686-elf-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



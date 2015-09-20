################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/sys/task/process.c \
../kernel/sys/task/signal.c \
../kernel/sys/task/spin.c \
../kernel/sys/task/task.c 

S_UPPER_SRCS += \
../kernel/sys/task/task_copy_page_phys.S \
../kernel/sys/task/tss_flush.S 

OBJS += \
./kernel/sys/task/process.o \
./kernel/sys/task/signal.o \
./kernel/sys/task/spin.o \
./kernel/sys/task/task.o \
./kernel/sys/task/task_copy_page_phys.o \
./kernel/sys/task/tss_flush.o 

C_DEPS += \
./kernel/sys/task/process.d \
./kernel/sys/task/signal.d \
./kernel/sys/task/spin.d \
./kernel/sys/task/task.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/sys/task/%.o: ../kernel/sys/task/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kernel/sys/task/%.o: ../kernel/sys/task/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	i686-elf-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



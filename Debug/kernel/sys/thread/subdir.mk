################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/sys/thread/process.c \
../kernel/sys/thread/signal.c \
../kernel/sys/thread/spin.c \
../kernel/sys/thread/task.c 

S_UPPER_SRCS += \
../kernel/sys/thread/task_copy_page_phys.S \
../kernel/sys/thread/tss_flush.S 

OBJS += \
./kernel/sys/thread/process.o \
./kernel/sys/thread/signal.o \
./kernel/sys/thread/spin.o \
./kernel/sys/thread/task.o \
./kernel/sys/thread/task_copy_page_phys.o \
./kernel/sys/thread/tss_flush.o 

C_DEPS += \
./kernel/sys/thread/process.d \
./kernel/sys/thread/signal.d \
./kernel/sys/thread/spin.d \
./kernel/sys/thread/task.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/sys/thread/%.o: ../kernel/sys/thread/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kernel/sys/thread/%.o: ../kernel/sys/thread/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	i686-elf-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



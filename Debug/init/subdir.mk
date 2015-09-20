################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../init/args.c \
../init/initrd.c \
../init/kmain.c \
../init/multiboot.c \
../init/version.c 

S_UPPER_SRCS += \
../init/kernel_boot.S 

OBJS += \
./init/args.o \
./init/initrd.o \
./init/kernel_boot.o \
./init/kmain.o \
./init/multiboot.o \
./init/version.o 

C_DEPS += \
./init/args.d \
./init/initrd.d \
./init/kmain.d \
./init/multiboot.d \
./init/version.d 


# Each subdirectory must supply rules for building sources it contributes
init/%.o: ../init/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

init/%.o: ../init/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	i686-elf-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



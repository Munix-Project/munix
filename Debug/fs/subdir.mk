################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fs/elf.c \
../fs/pipe.c \
../fs/tty.c \
../fs/unixpipe.c \
../fs/vfs.c 

OBJS += \
./fs/elf.o \
./fs/pipe.o \
./fs/tty.o \
./fs/unixpipe.o \
./fs/vfs.o 

C_DEPS += \
./fs/elf.d \
./fs/pipe.d \
./fs/tty.d \
./fs/unixpipe.d \
./fs/vfs.d 


# Each subdirectory must supply rules for building sources it contributes
fs/%.o: ../fs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



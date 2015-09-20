################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/lib/data_struct/bitset.c \
../libraries/lib/data_struct/hashmap.c \
../libraries/lib/data_struct/list.c \
../libraries/lib/data_struct/ringbuffer.c \
../libraries/lib/data_struct/tree.c 

OBJS += \
./libraries/lib/data_struct/bitset.o \
./libraries/lib/data_struct/hashmap.o \
./libraries/lib/data_struct/list.o \
./libraries/lib/data_struct/ringbuffer.o \
./libraries/lib/data_struct/tree.o 

C_DEPS += \
./libraries/lib/data_struct/bitset.d \
./libraries/lib/data_struct/hashmap.d \
./libraries/lib/data_struct/list.d \
./libraries/lib/data_struct/ringbuffer.d \
./libraries/lib/data_struct/tree.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/lib/data_struct/%.o: ../libraries/lib/data_struct/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/net/irc.c \
../modules/net/net.c \
../modules/net/packetfs.c 

OBJS += \
./modules/net/irc.o \
./modules/net/net.o \
./modules/net/packetfs.o 

C_DEPS += \
./modules/net/irc.d \
./modules/net/net.d \
./modules/net/packetfs.d 


# Each subdirectory must supply rules for building sources it contributes
modules/net/%.o: ../modules/net/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



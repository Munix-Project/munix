################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/drivers/sound/ac97.c \
../modules/drivers/sound/hda.c \
../modules/drivers/sound/pcspkr.c \
../modules/drivers/sound/snd.c 

OBJS += \
./modules/drivers/sound/ac97.o \
./modules/drivers/sound/hda.o \
./modules/drivers/sound/pcspkr.o \
./modules/drivers/sound/snd.o 

C_DEPS += \
./modules/drivers/sound/ac97.d \
./modules/drivers/sound/hda.d \
./modules/drivers/sound/pcspkr.d \
./modules/drivers/sound/snd.d 


# Each subdirectory must supply rules for building sources it contributes
modules/drivers/sound/%.o: ../modules/drivers/sound/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	i686-elf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



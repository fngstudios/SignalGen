################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HW_IRQ.c \
../src/SignalGen.c \
../src/cr_startup_lpc43xx.c \
../src/sysinit.c 

OBJS += \
./src/HW_IRQ.o \
./src/SignalGen.o \
./src/cr_startup_lpc43xx.o \
./src/sysinit.o 

C_DEPS += \
./src/HW_IRQ.d \
./src/SignalGen.d \
./src/cr_startup_lpc43xx.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M4 -D__LPC43XX__ -D__REDLIB__ -D__MULTICORE_NONE -I"C:\MCUxpressoWS\lpc_chip_43xx\inc" -I"C:\MCUxpressoWS\lpc_chip_43xx\inc\usbd" -I"C:\MCUxpressoWS\SignalGen\inc" -O0 -fno-common -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



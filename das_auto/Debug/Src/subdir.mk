################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Motordrive.c \
../Src/NRF24.c \
../Src/Ultrasonic.c \
../Src/main.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/syscalls.c \
../Src/system_stm32l0xx.c 

OBJS += \
./Src/Motordrive.o \
./Src/NRF24.o \
./Src/Ultrasonic.o \
./Src/main.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/syscalls.o \
./Src/system_stm32l0xx.o 

C_DEPS += \
./Src/Motordrive.d \
./Src/NRF24.d \
./Src/Ultrasonic.d \
./Src/main.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/syscalls.d \
./Src/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L073xx -I"/home/pvl/Privat/stm32/Programmen/das_auto/Inc" -I"/home/pvl/Privat/stm32/Programmen/das_auto/Drivers/STM32L0xx_HAL_Driver/Inc" -I"/home/pvl/Privat/stm32/Programmen/das_auto/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"/home/pvl/Privat/stm32/Programmen/das_auto/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"/home/pvl/Privat/stm32/Programmen/das_auto/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



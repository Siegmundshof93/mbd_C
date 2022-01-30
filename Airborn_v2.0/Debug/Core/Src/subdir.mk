################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Sx1278.c \
../Core/Src/main.c \
../Core/Src/stm32f0xx_hal_msp.c \
../Core/Src/stm32f0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f0xx.c 

OBJS += \
./Core/Src/Sx1278.o \
./Core/Src/main.o \
./Core/Src/stm32f0xx_hal_msp.o \
./Core/Src/stm32f0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f0xx.o 

C_DEPS += \
./Core/Src/Sx1278.d \
./Core/Src/main.d \
./Core/Src/stm32f0xx_hal_msp.d \
./Core/Src/stm32f0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DUSE_HAL_DRIVER -DSTM32F030x8 -I"/home/pvl/Privat/stm32/Programmen/Airborn_v2.0/Core/Inc" -I"/home/pvl/Privat/stm32/Programmen/Airborn_v2.0/Drivers/STM32F0xx_HAL_Driver/Inc" -I"/home/pvl/Privat/stm32/Programmen/Airborn_v2.0/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"/home/pvl/Privat/stm32/Programmen/Airborn_v2.0/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"/home/pvl/Privat/stm32/Programmen/Airborn_v2.0/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



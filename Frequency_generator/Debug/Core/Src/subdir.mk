################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Boot.c \
../Core/Src/CanTx.c \
../Core/Src/LUX.c \
../Core/Src/W25Q.c \
../Core/Src/eeprom.c \
../Core/Src/frequencyRead.c \
../Core/Src/lm75.c \
../Core/Src/main.c \
../Core/Src/pcf8563.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/Boot.o \
./Core/Src/CanTx.o \
./Core/Src/LUX.o \
./Core/Src/W25Q.o \
./Core/Src/eeprom.o \
./Core/Src/frequencyRead.o \
./Core/Src/lm75.o \
./Core/Src/main.o \
./Core/Src/pcf8563.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/Boot.d \
./Core/Src/CanTx.d \
./Core/Src/LUX.d \
./Core/Src/W25Q.d \
./Core/Src/eeprom.d \
./Core/Src/frequencyRead.d \
./Core/Src/lm75.d \
./Core/Src/main.d \
./Core/Src/pcf8563.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32L476xx -I"/home/pvl/Privat/stm32/Programmen/Frequency_generator/Core/Inc" -I"/home/pvl/Privat/stm32/Programmen/Frequency_generator/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/home/pvl/Privat/stm32/Programmen/Frequency_generator/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/home/pvl/Privat/stm32/Programmen/Frequency_generator/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/home/pvl/Privat/stm32/Programmen/Frequency_generator/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LUX.c \
../Core/Src/W25Q.c \
../Core/Src/main.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/LUX.o \
./Core/Src/W25Q.o \
./Core/Src/main.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/LUX.d \
./Core/Src/W25Q.d \
./Core/Src/main.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32L476xx -I"/home/pvl/Privat/stm32/Programmen/LUX_W25Q/Core/Inc" -I"/home/pvl/Privat/stm32/Programmen/LUX_W25Q/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/home/pvl/Privat/stm32/Programmen/LUX_W25Q/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/home/pvl/Privat/stm32/Programmen/LUX_W25Q/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/home/pvl/Privat/stm32/Programmen/LUX_W25Q/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER/GPIO.c 

OBJS += \
./Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER/GPIO.o 

C_DEPS += \
./Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER/GPIO.o: ../Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER/GPIO.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/APP" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/HAL/EEPROM_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/Stm32_F103C6_Drivers/MCAL/I2C_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/Stm32_F103C6_Drivers/MCAL/SPI_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/HAL/KEYPAD_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/HAL/LCD_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/HAL/Seven_Segment_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/Stm32_F103C6_Drivers/inc" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/Stm32_F103C6_Drivers/MCAL/EXTI_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/Stm32_F103C6_Drivers/MCAL/RCC_DRIVER" -I"D:/Embedded System/GitHub/Master_Embedded_Systems/MCU Interfacing/Assignment 2 - Update USART/USART - STM32/Drivers/Stm32_F103C6_Drivers/MCAL/USART_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER/GPIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.c 

OBJS += \
./HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.o 

C_DEPS += \
./HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.o: ../HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Belal/Desktop/Drivers/APP" -I"C:/Users/Belal/Desktop/Drivers/HAL/EEPROM_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/Stm32_F103C6_Drivers/MCAL/I2C_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/Stm32_F103C6_Drivers/MCAL/SPI_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/HAL/KEYPAD_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/HAL/LCD_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/HAL/Seven_Segment_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/Stm32_F103C6_Drivers/inc" -I"C:/Users/Belal/Desktop/Drivers/Stm32_F103C6_Drivers/MCAL/EXTI_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/Stm32_F103C6_Drivers/MCAL/RCC_DRIVER" -I"C:/Users/Belal/Desktop/Drivers/Stm32_F103C6_Drivers/MCAL/USART_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/EEPROM_DRIVER/I2C_Slave_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


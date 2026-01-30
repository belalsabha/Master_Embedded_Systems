################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/MCAL/RCC_DRIVER/RCC.c 

OBJS += \
./Stm32_F103C6_Drivers/MCAL/RCC_DRIVER/RCC.o 

C_DEPS += \
./Stm32_F103C6_Drivers/MCAL/RCC_DRIVER/RCC.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/MCAL/RCC_DRIVER/RCC.o: ../Stm32_F103C6_Drivers/MCAL/RCC_DRIVER/RCC.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/MCAL/TIMER2_DRIVER" -I"C:/Users/Belal/Desktop/PVP/APP" -I"C:/Users/Belal/Desktop/PVP/HAL/SERVO_MOTOR_DRIVER" -I"C:/Users/Belal/Desktop/PVP/HAL/KEYPAD_DRIVER" -I"C:/Users/Belal/Desktop/PVP/HAL/LCD_DRIVER" -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/inc" -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER" -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/MCAL/RCC_DRIVER" -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/MCAL/USART_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/MCAL/RCC_DRIVER/RCC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


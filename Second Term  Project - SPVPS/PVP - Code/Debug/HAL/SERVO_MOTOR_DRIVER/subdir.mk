################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/SERVO_MOTOR_DRIVER/SERVO_MOTOR.c 

OBJS += \
./HAL/SERVO_MOTOR_DRIVER/SERVO_MOTOR.o 

C_DEPS += \
./HAL/SERVO_MOTOR_DRIVER/SERVO_MOTOR.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/SERVO_MOTOR_DRIVER/SERVO_MOTOR.o: ../HAL/SERVO_MOTOR_DRIVER/SERVO_MOTOR.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/MCAL/TIMER2_DRIVER" -I"C:/Users/Belal/Desktop/PVP/APP" -I"C:/Users/Belal/Desktop/PVP/HAL/SERVO_MOTOR_DRIVER" -I"C:/Users/Belal/Desktop/PVP/HAL/KEYPAD_DRIVER" -I"C:/Users/Belal/Desktop/PVP/HAL/LCD_DRIVER" -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/inc" -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/MCAL/GPIO_DRIVER" -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/MCAL/RCC_DRIVER" -I"C:/Users/Belal/Desktop/PVP/Stm32_F103C6_Drivers/MCAL/USART_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/SERVO_MOTOR_DRIVER/SERVO_MOTOR.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


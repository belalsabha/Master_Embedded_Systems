/*
 * SERVO_MOTOR.c
 *
 *  Created on: Jan 22, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 */

#include"SERVO_MOTOR.h"


//B8 SERVO1
void Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	GPIO_Configure_Pin_t PinCinfg;
	PinCinfg.GPOI_Pin_Number=GPIO_PIN8;
	PinCinfg.GPIO_Mode = output_push_pull;
	PinCinfg.GPIO_Output_Frequency =Frequency_10MHz;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo1_Entry_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo1 Enter gate up +90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN8, SET_PIN	);
		dus(500);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN8, RESET_PIN	);
	}
	if(Direction==Down)
	{
		//servo1 Enter gate down -90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN8, SET_PIN	);
		dus(1488);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN8, RESET_PIN	);
	}


}

//B9 SERVO2
void Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	GPIO_Configure_Pin_t PinCinfg;
	PinCinfg.GPOI_Pin_Number=GPIO_PIN9;
	PinCinfg.GPIO_Mode = output_push_pull;
	PinCinfg.GPIO_Output_Frequency =Frequency_10MHz;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo2_Exit_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo2 Exit gate up +90
		GPIO_Configure_Pin_t PinCinfg;
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN9, SET_PIN);
		dus(500);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN9, RESET_PIN);
	}

	if(Direction == Down)
	{
		//servo2 Exit gate down -90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN9,SET_PIN);
		dus(1488);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN9, RESET_PIN);
	}

}

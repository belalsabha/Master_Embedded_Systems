/*
 * Seven_Segment.c
 *
 *  Created on: Dec 12, 2025
 *  Author: Belal Hani Sabha
 */


#include "Seven_Segment.h"


//-----------------------------------------------------------------------
void Init_7Segment()
{
    GPIO_Configure_Pin_t PinCnfg;



    PinCnfg.GPOI_Pin_Number = GPIO_PIN9;
    PinCnfg.GPIO_Mode = output_push_pull;
    PinCnfg.GPIO_Output_Frequency = Frequency_10MHz;
    MCAL_GPIO_Init(GPIOB, &PinCnfg);

    PinCnfg.GPOI_Pin_Number = GPIO_PIN10;
    PinCnfg.GPIO_Mode = output_push_pull;
    PinCnfg.GPIO_Output_Frequency = Frequency_10MHz;
    MCAL_GPIO_Init(GPIOB, &PinCnfg);

    PinCnfg.GPOI_Pin_Number = GPIO_PIN11;
    PinCnfg.GPIO_Mode = output_push_pull;
    PinCnfg.GPIO_Output_Frequency = Frequency_10MHz;
    MCAL_GPIO_Init(GPIOB, &PinCnfg);

    PinCnfg.GPOI_Pin_Number = GPIO_PIN12;
    PinCnfg.GPIO_Mode = output_push_pull;
    PinCnfg.GPIO_Output_Frequency = Frequency_10MHz;
    MCAL_GPIO_Init(GPIOB, &PinCnfg);

    PinCnfg.GPOI_Pin_Number = GPIO_PIN13;
    PinCnfg.GPIO_Mode = output_push_pull;
    PinCnfg.GPIO_Output_Frequency = Frequency_10MHz;
    MCAL_GPIO_Init(GPIOB, &PinCnfg);

    PinCnfg.GPOI_Pin_Number = GPIO_PIN14;
    PinCnfg.GPIO_Mode = output_push_pull;
    PinCnfg.GPIO_Output_Frequency = Frequency_10MHz;
    MCAL_GPIO_Init(GPIOB, &PinCnfg);

    PinCnfg.GPOI_Pin_Number = GPIO_PIN15;
    PinCnfg.GPIO_Mode = output_push_pull;
    PinCnfg.GPIO_Output_Frequency = Frequency_10MHz;
    MCAL_GPIO_Init(GPIOB, &PinCnfg);
}


//=======================================================================

void DisplayNumber_on_7segment(uint8_t num)
{
	uint8_t DISPLAY [11] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

	uint8_t value = DISPLAY[num];

	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN9,  (value >> 0) & 1);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN10, (value >> 1) & 1);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN11, (value >> 2) & 1);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN12, (value >> 3) & 1);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN13, (value >> 4) & 1);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN14, (value >> 5) & 1);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN15, (value >> 6) & 1);



}

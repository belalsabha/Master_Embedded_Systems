/*
 * TIMER.c
 *
 *  Created on: Jan 22, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 */

#include "TIMER2.h"


void Timer2_init(void)
{
	RCC->APB1ENR |=(1<<0);     //Enable Rcc for tim2
	TIMER2->PSC = 7 ;          //Clk_input=(8M/(7+1))=1MHZ
	TIMER2->ARR = 0xC350;	   //to make interrupt after 50000 tike(50000*10^-6)=0.05s
	TIMER2->CR1 |=(1<<0);
	while(!(TIMER2->SR)&(1<<0));
}

void dus(int us)
{
	TIMER2->CNT=0;
	while(TIMER2->CNT<us);
}

void dms(int ms)
{
	int i=0;
	for(i=0;i<ms;i++)
	{
		dus(1000);
	}
}





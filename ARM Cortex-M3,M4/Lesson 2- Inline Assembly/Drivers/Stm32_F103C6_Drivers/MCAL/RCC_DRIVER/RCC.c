/*
 * RCC.c
 *
 *
 *  Created on: Dec 24, 2025
 *      Author:  Belal Hani Sabha
 */


#include "RCC.h"

uint8_t APB_PreScaler[8] = {0,0,0,0,1,2,3,4};// used for shifting right = divide by 1 ,2 , 4 , 8 , 16
uint8_t AHB_PreScaler[16] = {0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9};// used for shifting right = divide by 1 ,2 , 4 , 8 , 16 , 54 , 128 , 256 , 512



uint32_t MCAL_RCC_GetSystem_ClckFreqency(void)  {
	//Bits 3:2 SWS[1:0]: System clock switch status
	//Set and cleared by hardware to indicate which clock source is used as system clock.
	//00: HSI oscillator used as system clock
	//01: HSE oscillator used as system clock
	//10: PLL used as system clock
	//11: Not applicable

	switch(RCC->CFGR >> 2  & (0b1111) ){

	case 0 : return  HSI_System_Clock ;
	break ;
	case 1 : return HSE_System_Clock ;
	break ;
	case 2 : return PLL_System_Clock ;
	break ;
	  default: return 8000000;



	}


}
uint32_t MCAL_RCC_Get_HClckFreqency(void)	 	{
	//Bits 7:4 HPRE[3:0]: AHB prescaler
	//Set and cleared by software to control AHB clock division factor.
	//0xxx: SYSCLK not divided
	//1000: SYSCLK divided by 2
	//1001: SYSCLK divided by 4
	//1010: SYSCLK divided by 8
	//1011: SYSCLK divided by 16
	//1100: SYSCLK divided by 64
	//1101: SYSCLK divided by 128
	//1110: SYSCLK divided by 256
	//1111: SYSCLK divided by 512


	return ( MCAL_RCC_GetSystem_ClckFreqency() >> (APB_PreScaler[RCC->CFGR >> 4  & 0b1111]) ) ;

}
uint32_t MCAL_RCC_Get_PCLK1Freqency(void) 		{
	//Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
	//Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
	//0xx: HCLK not divided
	//100: HCLK divided by 2
	//101: HCLK divided by 4
	//110: HCLK divided by 8
	//111: HCLK divided by 16

	return ( MCAL_RCC_Get_HClckFreqency() >> (APB_PreScaler[RCC->CFGR >> 8  & 0b111]) ) ;
}
uint32_t MCAL_RCC_Get_PCLK2Freqency(void) 		{
	//Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	//Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
	//0xx: HCLK not divided
	//100: HCLK divided by 2
	//101: HCLK divided by 4
	//110: HCLK divided by 8
	//111: HCLK divided by 16

	return ( MCAL_RCC_Get_HClckFreqency() >> (APB_PreScaler[RCC->CFGR >> 11  & 0b111]) ) ;
}

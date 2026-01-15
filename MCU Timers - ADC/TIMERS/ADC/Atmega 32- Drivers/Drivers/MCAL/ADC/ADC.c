/*
 * ADC.c
 *
 * Created: 15 / 1 /2026
 * Author : Belal Hani Sabha
 */


//----------------------------------
//Includes
//----------------------------------

#include "ADC.h"
#include <stdlib.h>

/*
 * =======================================================================================
 * Generic Variables
 * =======================================================================================
 */
ADC_t *ADCx ;
ADC_Config_t *G_ADC_Config;

/*
 * =======================================================================================
 * APIs Implementation
 * =======================================================================================
 */
void MCAL_ADC_Init(ADC_Config_t *ADC_Config)
{
	G_ADC_Config = ADC_Config;

	// Select Vref
	ADCx->ADMUX &= ~(3 << 6);
	ADCx->ADMUX |= ADC_Config->Vref;

	// Prescaler
	ADCx->ADCSRA &= ~(7 << 0);
	ADCx->ADCSRA |= ADC_Config->conversion_time;

	// Interrupt
	if (ADC_Config->IRQ_Enable == ADC_IRQ_ENABLE)
	{
		SREG |= (1 << 7);
		ADCx->ADCSRA |= ADC_IRQ_ENABLE;
	}
	else
	{
		ADCx->ADCSRA &= ~ADC_IRQ_ENABLE;
	}

	// Enable ADC
	ADCx->ADCSRA |= (1 << 7);
}



uint16_t MCAL_ADC_Read(){
	
	uint16_t Ret_Val;

	// Select channel
	ADCx->ADMUX &= 0xE0;
	ADCx->ADMUX |= G_ADC_Config->Channel;

	// Start conversion
	ADCx->ADCSRA |= (1 << 6);

	// Wait until finished
	while (ADCx->ADCSRA & (1 << 6));

	// Read result
	Ret_Val = ADCx->ADCL;
	Ret_Val |= ((uint16_t)ADCx->ADCH << 8);

	return Ret_Val;
}




void MCAL_ADC_DeInit(){	
	// Disable ADC Interrupt
ADCx->ADCSRA &= ~(1 << 3);  

// Disable ADC
ADCx->ADCSRA &= ~(1 << 7);   

// Reset ADC Control Registers
ADCx->ADCSRA = 0x00;
ADCx->ADMUX  = 0x00;

// Clear global ADC configuration pointer
G_ADC_Config = NULL;

}
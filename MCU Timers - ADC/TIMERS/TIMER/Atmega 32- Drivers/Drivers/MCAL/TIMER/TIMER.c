/*
 * TIMER.c
 *
 * Created: 14 / 1 /2026
 * Author : Belal Hani Sabha
 */


//----------------------------------
//Includes
//----------------------------------

#include "TIMER.h"
#include <stdlib.h>

/*
 * =======================================================================================
 * Generic Variables
 * =======================================================================================
 */
P_VoidFunc_t CALLBACK_OVER_FLOW;
P_VoidFunc_t CALLBACK_CompareMatch;
TIMER0_t *Timerx ;
uint8_t OVER_FLOW_Number;
TIMER_Config_t *G_timerConfig;

/*
 * =======================================================================================
 * Generic Macros 
 * =======================================================================================
 */



#define F_CPU 8000000UL

/*
 * =======================================================================================
 * APIs Implementation
 * =======================================================================================
 */
void MCAL_TIMER0_Init(TIMER_Config_t *timerConfig){
	
		G_timerConfig = timerConfig ;
			
	    /* ===================== Select  MODE ===================== */

		switch(timerConfig->Timer_Mode)
			 {
			case TIMER0_MODE_NORMAL:
			case TIMER0_MODE_CTC:
			Timerx->TCCR0 |= timerConfig->Timer_Mode;
			break;
			case TIMER0_MODE_PHASE_CORRECT_PWM:
			case TIMER0_MODE_FAST_PWM:
			Timerx->TCCR0 |= timerConfig->Timer_Mode;
		    IOD->DDR |= (1 << 4); 
			    Timerx->TCCR0 |= (1 << 5);
			    Timerx->TCCR0 &= ~(1 << 1); 
			break;
			}
	
		/* ===================== Select  CLCK SOURCE ===================== */

	    switch(timerConfig->Timer_ClockSource)
	    {
		    case TIMER0_CLK_NO_CLOCK:
		    case TIMER0_CLK_IO_NO_PRESCAL:
		    case TIMER0_CLK_IO_DIV8:
		    case TIMER0_CLK_IO_DIV64:
		    case TIMER0_CLK_IO_DIV256:
		    case TIMER0_CLK_IO_DIV1024:
		    case TIMER0_CLK_EXTERNAL_FALL:
		    case TIMER0_CLK_EXTERNAL_RISE:
		    Timerx->TCCR0 |= (timerConfig->Timer_ClockSource);   
		    break;
   
	    }
		
		
		/* ===================== Select  IRQ SOURCE ===================== */

		    switch(timerConfig->Timer_InterruptConfig)
		    {
			    case TIMER0_INTERRUPT_DISABLE:
				Timerx->TIMSK |=  TIMER0_INTERRUPT_DISABLE ;
			    break;

			    case TIMER0_INTERRUPT_OC_COMPARE:
			    Timerx->TIMSK |= TIMER0_INTERRUPT_OC_COMPARE;  // Enable Compare Match
			    break;

			    case TIMER0_INTERRUPT_OVERFLOW:
			    Timerx->TIMSK |= TIMER0_INTERRUPT_OVERFLOW;   // Enable Overflow
			    break;

  
		    }
		

	
}

void MCAL_TIMER0_DeInit(TIMER0_t *Timerx){
		
   Timerx->TCCR0 &= ~((1<<2)|(1<<1)|(1<<0));

   Timerx->TIMSK &= ~((1<<0)|(1<<1));

   Timerx->TCNT0 = 0;
   Timerx->OCR0  = 0;

  CALLBACK_CompareMatch = NULL;
   CALLBACK_OVER_FLOW     = NULL;
   OVER_FLOW_Number       = 0;	
	 	
}



void MCAL_TIMER0_GetCompareValue(uint8_t *compareValue){
	
	*compareValue = Timerx->OCR0 ;
	
}
void MCAL_TIMER0_SetCompareValue(uint8_t compareValue){
	
	Timerx->OCR0 =  compareValue ;
}

void MCAL_TIMER0_GetCounterValue(uint8_t *counterValue){
	
		*counterValue = Timerx->TCNT0 ;	
}
void MCAL_TIMER0_SetCounterValue(uint8_t counterValue){
	
		Timerx->TCNT0 = counterValue ;	
}

void MCAL_TIMER0_GetOverflowValue(uint8_t *overflowValue){
		*overflowValue =  OVER_FLOW_Number;

	
}
void MCAL_TIMER0_SetOverflowValue(uint8_t overflowValue){
	
	OVER_FLOW_Number = overflowValue ; 
}



void MCAL_TIMER0_SetCallbackOverflowInterrupt(P_VoidFunc_t callback){
	
		CALLBACK_OVER_FLOW = callback;

}
void MCAL_TIMER0_SetCallbackCompareMatchInterrupt(P_VoidFunc_t callback){
	
	CALLBACK_CompareMatch =  callback ;
}

void MCAL_TIMER0_SetPWMDutyCycle(uint8_t dutyCycle){
	
	    uint8_t ocrValue;

	    if(dutyCycle > 100)
	    {
		   dutyCycle = 100;
	    }

	    ocrValue = ((dutyCycle * 255) / 100);

	    // Fast PWM 
	    if(G_timerConfig->Timer_Mode == TIMER0_MODE_FAST_PWM)
	    {
		    Timerx->OCR0 = ocrValue;  
		}
	    // Phase Correct PWM 
	    else if(G_timerConfig->Timer_Mode == TIMER0_MODE_PHASE_CORRECT_PWM)
	    {
		   Timerx->OCR0 = ocrValue;  
	    }
	    else
	    {
	    }
}

/* ================================================================ *
		* ===================== ISRs ============================ *
 * ================================================================ */

void TIMER0_CompareMatch_ISR(void) __attribute__((signal));
void TIMER0_CompareMatch_ISR(void)
{
	if(CALLBACK_CompareMatch != NULL)
	{
		CALLBACK_CompareMatch();
	}
}

void TIMER0_Overflow_ISR(void) __attribute__((signal));
void TIMER0_Overflow_ISR(void)
{
	OVER_FLOW_Number++;
	if(CALLBACK_OVER_FLOW != NULL)
	{
		CALLBACK_OVER_FLOW();
	}
}

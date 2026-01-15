/*
 * WDT.c
 *
 * Created: 14 / 1 /2026
 * Author : Belal Hani Sabha
 */


#include "WDT.h"




void WDT_Init(WDT_t *WDTx , WDT_Config_t *WDT_Config){
	
	// 1- Enable WDT by : When the WDE is written to logic one, the Watchdog Timer is enabled, and if the WDE is written
	     // to logic zero, the Watchdog Timer function is disabled
		 
		 if(WDT_Config->Watchdog_Status == WDT_Enable ){
			 
			 WDTx->WDTCR |= (WDT_Enable) ;
			 
		 }else
		 {
			 WDT_DeInit(WDT);
		 }
		 
		 //2- Prescaler
		 /*• Bits [2:0] – WDP2, WDP1, WDP0: Watchdog Timer Prescaler 2, 1, and 0
		 The WDP2, WDP1, and WDP0 bits determine the Watchdog Timer prescaling when the Watch
		 dog Timer is enabled.*/
		 
		 switch(WDT_Config->Prescaler){
			     case WDT_PRESCALER_16ms:   // 000
			     case WDT_PRESCALER_32ms:   // 001
			     case WDT_PRESCALER_65ms:   // 010
			     case WDT_PRESCALER_130ms:  // 011
			     case WDT_PRESCALER_260ms:  // 100
			     case WDT_PRESCALER_520ms:  // 101
			     case WDT_PRESCALER_1s:     // 110
			     case WDT_PRESCALER_2s:     // 111
				 
			     //Clear WDP2:WDP0 bits 
			      WDTx->WDTCR &= ~0x07;

			     WDTx->WDTCR |= (WDT_Config->Prescaler);
			     break;

			     default:
			     // Default prescaler : 16 ms 
			    WDTx->WDTCR  &= ~0x07;
			    WDTx->WDTCR |= WDT_PRESCALER_16ms;
			     break;
		 }
		 
	
	
	
}
void WDT_DeInit(WDT_t *WDTx){
	
// 	WDE can only be cleared if the WDTOE bit has logic level one. To disable an enabled Watchdog Timer, 
// 	 the following procedure must be  	followed:
// 	1. In the same operation, write a logic one to WDTOE and WDE. A logic one must be writ
// 	ten to WDE even though it is set to one before the disable operation starts.
// 	2. Within the next four clock cycles, write a logic 0 to WDE. This disables the Watchdog.
	
	 WDTx->WDTCR = (1<<3) | (1<<4);
	 WDTx->WDTCR = 0x00;
	
}


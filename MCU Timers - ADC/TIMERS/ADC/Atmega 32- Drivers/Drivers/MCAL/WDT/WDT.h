/*
 * WDT.h
 *
 * Created: 14 / 1 /2026
 * Author : Belal Hani Sabha
 */ 


#ifndef WDT_H_
#define WDT_H_



#include "Atmega32.h"
#include "IO.h"


//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//----------------------------------
//User type definitions (structures)
//----------------------------------
//Configuration structure For User inputs
typedef struct {

	uint8_t   Watchdog_Status 				;	//Enable or Disable WDT
													//this parameter must be set based on  @ref WDT_Watchdog_Status_Define	
	
	uint8_t  Prescaler 			 			; 	//specified the WDT the Watchdog Timer prescaling.
													//this parameter must be set based on  @ref WDT_Prescaler_Defin
}WDT_Config_t;


//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//----------------------------------
//Macros Configuration References
//----------------------------------
//@ref WDT_Watchdog_Status_Define
							/*When the WDE is written to logic one, the Watchdog Timer is enabled, and if the WDE is written
							to logic zero, the Watchdog Timer function is disabled  */
#define  WDT_Enable      (1<<3)
#define  WDT_Disable      (0)

// @ref WDT_Prescaler_Defin
				/*The WDP2, WDP1, and WDP0 bits determine the Watchdog Timer prescaling when the Watch dog Timer is enabled.*/
#define WDT_PRESCALER_16ms     0b000   // WDP2=0, WDP1=0, WDP0=0
#define WDT_PRESCALER_32ms     0b001   // WDP2=0, WDP1=0, WDP0=1
#define WDT_PRESCALER_65ms     0b010   // WDP2=0, WDP1=1, WDP0=0
#define WDT_PRESCALER_130ms    0b011   // WDP2=0, WDP1=1, WDP0=1
#define WDT_PRESCALER_260ms    0b100   // WDP2=1, WDP1=0, WDP0=0
#define WDT_PRESCALER_520ms    0b101   // WDP2=1, WDP1=0, WDP0=1
#define WDT_PRESCALER_1s       0b110   // WDP2=1, WDP1=1, WDP0=0
#define WDT_PRESCALER_2s       0b111   // WDP2=1, WDP1=1, WDP0=1


void MCAL_WDT_Init(WDT_t *WDTx , WDT_Config_t *WDT_Config);
void MCAL_WDT_DeInit(WDT_t *WDTx);

#endif /* WDT_H_ */
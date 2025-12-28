/*
 * EXTI.h
 *
 * Created: 18 / 12 /2025
 * Author : Belal Hani Sabha
 */


#ifndef EXTI_H_
#define EXTI_H_
//----------------------------------
//Includes
//----------------------------------
#include "Atmega32.h"
#include "IO.h"


//----------------------------------
//User type definitions (structures)
//----------------------------------

typedef struct{

	IOx_t*  		IO_PORT	   ;   // Specifies the IO port ( IOB, IOD) that is used by the EXTI module to generate an interrupt.

	uint16_t	 	IO_PIN	   ;   //Specifies the IO pin number (IOB2 IOD3 IOD2) that is used by the EXTI module to generate an interrupt.

	uint8_t 		VectorNo ;    //Specifies the Interrupt Vector Table (IVT) number for the EXTI module 
	
}EXTI_map_to_IO_t;



typedef struct{


	EXTI_map_to_IO_t    EXTI_PIN               ;    // Specifies the External interrupt  IO mapping.
													// This parameter must be set based on @ref EXTI_define

	uint8_t 			EDGE_CASE  			    ;	//Specifies the type of trigger for the EXTI module (e.g., rising edge, falling  edge, or low level)
													// This parameter must be set based on @ref EXTI_Trigger_define

	uint8_t 			IRQ_E_D					;  //Specifies whether the EXTI interrupt is enabled or disabled.
													//This parameter must be set based on @ref EXTI_IRQ_define


	void (*P_IRQ_FUNC_CALLBACK)(void)			;  //Specifies a pointer to the callback function that will be called when the EXTI interrupt is generated.

}EXTI_Configure_Pin_t;

//----------------------------------
//Macros Configuration References
//----------------------------------

/* @ref Module REF NAME define */

//Callback index 
#define INT0_INDEX  0
#define INT1_INDEX  1
#define INT2_INDEX  2

//@ref EXTI_define
#define EXTI0PD2   (EXTI_map_to_IO_t){ IOD , IO_PIN2 , INT0_INDEX }
#define EXTI1PD3   (EXTI_map_to_IO_t){ IOD , IO_PIN3 , INT1_INDEX }
#define EXTI2PB2   (EXTI_map_to_IO_t){ IOB , IO_PIN2 , INT2_INDEX }



// @ref EXTI_Trigger_define
#define    LOW_LEVEL   			 0   // for EXTI0 , EXTI1
#define	   Any_logical_Change    1
#define    FALLING_EDGE    		 2
#define    RISING_EDGE			 3 

//@ref EXTI_IRQ_define
#define    ENABLE_IRQ_EXTI     		 1
#define    DISABLE_IRQ_EXTI     	 0


/*
 * =======================================================================================
 * 							APIs Supported by "MCAL EXTI DRIVER"
 * =======================================================================================
 */

// 					APIs For EXTI

void MCAL_EXTI_IO_Init (EXTI_Configure_Pin_t* EXTI_Config);
void MCAL_EXTI_IO_DeInit (void);
void MCAL_EXTI_IO_Update (EXTI_Configure_Pin_t* EXTI_Config);


//---------------------------------------------------




#endif /* EXTI_H_ */
/*
 * 	EXTI.h
 *
 *  Created on: Dec 13, 2025
 *      Author:  Belal Hani Sabha
 */

#ifndef EXTI_DRIVER_EXTI_H_
#define EXTI_DRIVER_EXTI_H_




//----------------------------------
//Includes
//----------------------------------
#include "stm32f103x6.h"
#include "GPIO.h"



//----------------------------------
//User type definitions (structures)
//----------------------------------

typedef struct{

	uint16_t  		EXTI_LINE	   ;   // Specifies the input line number for the EXTI module (e.g., EXTI0, EXTI1, etc.)

	GPIOx_t*  		GPIO_PORT	   ;   // Specifies the GPIO port (e.g., GPIOA, GPIOB, GPIOC, etc.) that is used by the EXTI module to generate an interrupt.

	uint16_t	 	GPIO_PIN	   ;   //Specifies the GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.) that is used by the EXTI module to generate an interrupt.

	uint8_t 		IVT_IRQ_Number ;  //Specifies the Interrupt Vector Table (IVT) number for the EXTI module (e.g., EXTI0_IRQ, EXTI1_IRQ, etc.)

}EXTI_map_to_GPIO_t;




typedef struct{


	EXTI_map_to_GPIO_t   EXTI_PIN               ;    // Specifies the External interrupt  GPIO mapping.
														// This parameter must be set based on @ref EXTI_define


	uint8_t 			EDGE_CASE  			    ;	//Specifies the type of trigger for the EXTI module (e.g., rising edge, falling  edge, or both)
															// This parameter must be set based on @ref EXTI_Trigger_define


	uint8_t 			IRQ_E_D					;  //Specifies whether the EXTI interrupt is enabled or disabled.
													//This parameter must be set based on @ref EXTI_IRQ_define



	void (*P_IRQ_FUNC_CALLBACK)(void)			;  //Specifies a pointer to the callback function that will be called when the EXTI interrupt is generated.


}EXTI_Configure_Pin_t;





//----------------------------------
//Macros Configuration References
//----------------------------------

#define EXTI0 					0
#define EXTI1 					1
#define EXTI2 					2
#define EXTI3 					3
#define EXTI4 					4
#define EXTI5 					5
#define EXTI6 					6
#define EXTI7 					7
#define EXTI8 					8
#define EXTI9 					9
#define EXTI10 					10
#define EXTI11 					11
#define EXTI12 					12
#define EXTI13					13
#define EXTI14 					14
#define EXTI15 					15


/* @ref Module REF NAME define */

//@ref EXTI_define
#define EXTI0PA0      (EXTI_map_to_GPIO_t){EXTI0 , GPIOA , GPIO_PIN0 , EXTI0_IRQ}
#define EXTI0PB0      (EXTI_map_to_GPIO_t){EXTI0 , GPIOB , GPIO_PIN0 , EXTI0_IRQ}
#define EXTI0PC0      (EXTI_map_to_GPIO_t){EXTI0 , GPIOC , GPIO_PIN0 , EXTI0_IRQ}
#define EXTI0PD0      (EXTI_map_to_GPIO_t){EXTI0 , GPIOD , GPIO_PIN0 , EXTI0_IRQ}
//-------------------------------
#define EXTI1PA1      (EXTI_map_to_GPIO_t){EXTI1 , GPIOA , GPIO_PIN1 , EXTI1_IRQ}
#define EXTI1PB1      (EXTI_map_to_GPIO_t){EXTI1 , GPIOB , GPIO_PIN1 , EXTI1_IRQ}
#define EXTI1PC1      (EXTI_map_to_GPIO_t){EXTI1 , GPIOC , GPIO_PIN1 , EXTI1_IRQ}
#define EXTI1PD1      (EXTI_map_to_GPIO_t){EXTI1 , GPIOD , GPIO_PIN1 , EXTI1_IRQ}
//-------------------------------
#define EXTI2PA2      (EXTI_map_to_GPIO_t){EXTI2 , GPIOA , GPIO_PIN2 , EXTI2_IRQ}
#define EXTI2PB2      (EXTI_map_to_GPIO_t){EXTI2 , GPIOB , GPIO_PIN2 , EXTI2_IRQ}
#define EXTI2PC2      (EXTI_map_to_GPIO_t){EXTI2 , GPIOC , GPIO_PIN2 , EXTI2_IRQ}
#define EXTI2PD2      (EXTI_map_to_GPIO_t){EXTI2 , GPIOD , GPIO_PIN2 , EXTI2_IRQ}
//-------------------------------
#define EXTI3PA3      (EXTI_map_to_GPIO_t){EXTI3 , GPIOA , GPIO_PIN3 , EXTI3_IRQ}
#define EXTI3PB3      (EXTI_map_to_GPIO_t){EXTI3 , GPIOB , GPIO_PIN3 , EXTI3_IRQ}
#define EXTI3PC3      (EXTI_map_to_GPIO_t){EXTI3 , GPIOC , GPIO_PIN3 , EXTI3_IRQ}
#define EXTI3PD3      (EXTI_map_to_GPIO_t){EXTI3 , GPIOD , GPIO_PIN3 , EXTI3_IRQ}
//-------------------------------
#define EXTI4PA4      (EXTI_map_to_GPIO_t){EXTI4 , GPIOA , GPIO_PIN4 , EXTI4_IRQ}
#define EXTI4PB4      (EXTI_map_to_GPIO_t){EXTI4 , GPIOB , GPIO_PIN4 , EXTI4_IRQ}
#define EXTI4PC4      (EXTI_map_to_GPIO_t){EXTI4 , GPIOC , GPIO_PIN4 , EXTI4_IRQ}
#define EXTI4PD4      (EXTI_map_to_GPIO_t){EXTI4 , GPIOD , GPIO_PIN4 , EXTI4_IRQ}
//-------------------------------
#define EXTI5PA5      (EXTI_map_to_GPIO_t){EXTI5 , GPIOA , GPIO_PIN5 , EXTI5_IRQ}
#define EXTI5PB5      (EXTI_map_to_GPIO_t){EXTI5 , GPIOB , GPIO_PIN5 , EXTI5_IRQ}
#define EXTI5PC5      (EXTI_map_to_GPIO_t){EXTI5 , GPIOC , GPIO_PIN5 , EXTI5_IRQ}
#define EXTI5PD5      (EXTI_map_to_GPIO_t){EXTI5 , GPIOD , GPIO_PIN5 , EXTI5_IRQ}
//-------------------------------
#define EXTI6PA6      (EXTI_map_to_GPIO_t){EXTI6 , GPIOA , GPIO_PIN6 , EXTI6_IRQ}
#define EXTI6PB6      (EXTI_map_to_GPIO_t){EXTI6 , GPIOB , GPIO_PIN6 , EXTI6_IRQ}
#define EXTI6PC6      (EXTI_map_to_GPIO_t){EXTI6 , GPIOC , GPIO_PIN6 , EXTI6_IRQ}
#define EXTI6PD6      (EXTI_map_to_GPIO_t){EXTI6 , GPIOD , GPIO_PIN6 , EXTI6_IRQ}
//-------------------------------
#define EXTI7PA7      (EXTI_map_to_GPIO_t){EXTI7 , GPIOA , GPIO_PIN7 , EXTI7_IRQ}
#define EXTI7PB7      (EXTI_map_to_GPIO_t){EXTI7 , GPIOB , GPIO_PIN7 , EXTI7_IRQ}
#define EXTI7PC7      (EXTI_map_to_GPIO_t){EXTI7 , GPIOC , GPIO_PIN7 , EXTI7_IRQ}
#define EXTI7PD7      (EXTI_map_to_GPIO_t){EXTI7 , GPIOD , GPIO_PIN7 , EXTI7_IRQ}
//-------------------------------
#define EXTI8PA8      (EXTI_map_to_GPIO_t){EXTI8 , GPIOA , GPIO_PIN8 , EXTI8_IRQ}
#define EXTI8PB8      (EXTI_map_to_GPIO_t){EXTI8 , GPIOB , GPIO_PIN8 , EXTI8_IRQ}
#define EXTI8PC8      (EXTI_map_to_GPIO_t){EXTI8 , GPIOC , GPIO_PIN8 , EXTI8_IRQ}
#define EXTI8PD8      (EXTI_map_to_GPIO_t){EXTI8 , GPIOD , GPIO_PIN8 , EXTI8_IRQ}
//-------------------------------
#define EXTI9PA9      (EXTI_map_to_GPIO_t){EXTI9 , GPIOA , GPIO_PIN9 , EXTI9_IRQ}
#define EXTI9PB9      (EXTI_map_to_GPIO_t){EXTI9 , GPIOB , GPIO_PIN9 , EXTI9_IRQ}
#define EXTI9PC9      (EXTI_map_to_GPIO_t){EXTI9 , GPIOC , GPIO_PIN9 , EXTI9_IRQ}
#define EXTI9PD9      (EXTI_map_to_GPIO_t){EXTI9 , GPIOD , GPIO_PIN9 , EXTI9_IRQ}
//-------------------------------
#define EXTI10PA10    (EXTI_map_to_GPIO_t){EXTI10 , GPIOA , GPIO_PIN10 , EXTI10_IRQ}
#define EXTI10PB10    (EXTI_map_to_GPIO_t){EXTI10 , GPIOB , GPIO_PIN10 , EXTI10_IRQ}
#define EXTI10PC10    (EXTI_map_to_GPIO_t){EXTI10 , GPIOC , GPIO_PIN10 , EXTI10_IRQ}
#define EXTI10PD10    (EXTI_map_to_GPIO_t){EXTI10 , GPIOD , GPIO_PIN10 , EXTI10_IRQ}
//------------------------------
#define EXTI11PA11    (EXTI_map_to_GPIO_t){EXTI11 , GPIOA , GPIO_PIN11 , EXTI11_IRQ}
#define EXTI11PB11    (EXTI_map_to_GPIO_t){EXTI11 , GPIOB , GPIO_PIN11 , EXTI11_IRQ}
#define EXTI11PC11    (EXTI_map_to_GPIO_t){EXTI11 , GPIOC , GPIO_PIN11 , EXTI11_IRQ}
#define EXTI11PD11    (EXTI_map_to_GPIO_t){EXTI11 , GPIOD , GPIO_PIN11 , EXTI11_IRQ}
//-------------------------------
#define EXTI12PA12    (EXTI_map_to_GPIO_t){EXTI12 , GPIOA , GPIO_PIN12 , EXTI12_IRQ}
#define EXTI12PB12    (EXTI_map_to_GPIO_t){EXTI12 , GPIOB , GPIO_PIN12 , EXTI12_IRQ}
#define EXTI12PC12    (EXTI_map_to_GPIO_t){EXTI12 , GPIOC , GPIO_PIN12 , EXTI12_IRQ}
#define EXTI12PD12    (EXTI_map_to_GPIO_t){EXTI12 , GPIOD , GPIO_PIN12 , EXTI12_IRQ}
//-------------------------------
#define EXTI13PA13    (EXTI_map_to_GPIO_t){EXTI13 , GPIOA , GPIO_PIN13 , EXTI13_IRQ}
#define EXTI13PB13    (EXTI_map_to_GPIO_t){EXTI13 , GPIOB , GPIO_PIN13 , EXTI13_IRQ}
#define EXTI13PC13    (EXTI_map_to_GPIO_t){EXTI13 , GPIOC , GPIO_PIN13 , EXTI13_IRQ}
#define EXTI13PD13    (EXTI_map_to_GPIO_t){EXTI13 , GPIOD , GPIO_PIN13 , EXTI13_IRQ}
//-------------------------------
#define EXTI14PA14    (EXTI_map_to_GPIO_t){EXTI14 , GPIOA , GPIO_PIN14 , EXTI14_IRQ}
#define EXTI14PB14    (EXTI_map_to_GPIO_t){EXTI14 , GPIOB , GPIO_PIN14 , EXTI14_IRQ}
#define EXTI14PC14    (EXTI_map_to_GPIO_t){EXTI14 , GPIOC , GPIO_PIN14 , EXTI14_IRQ}
#define EXTI14PD14    (EXTI_map_to_GPIO_t){EXTI14 , GPIOD , GPIO_PIN14 , EXTI14_IRQ}
//-------------------------------
#define EXTI15PA15    (EXTI_map_to_GPIO_t){EXTI15 , GPIOA , GPIO_PIN15 , EXTI15_IRQ}
#define EXTI15PB15    (EXTI_map_to_GPIO_t){EXTI15 , GPIOB , GPIO_PIN15 , EXTI15_IRQ}
#define EXTI15PC15    (EXTI_map_to_GPIO_t){EXTI15 , GPIOC , GPIO_PIN15 , EXTI15_IRQ}
#define EXTI15PD15    (EXTI_map_to_GPIO_t){EXTI15 , GPIOD , GPIO_PIN15 , EXTI15_IRQ}

//----------------------------------------------------------------------------------------------------------------


// @ref EXTI_Trigger_define
#define    RISING_EDGE    			 0
#define    FALLING_EDGE    			 1
#define    RISING_FALLING_EDGE       2


//@ref EXTI_IRQ_define
#define    ENABLE_IRQ_EXTI     		 1
#define    DISABLE_IRQ_EXTI     	 0







/*
 * =======================================================================================
 * 							APIs Supported by "MCAL EXTI DRIVER"
 * =======================================================================================
 */

// 					APIs For EXTI

void MCAL_EXTI_GPIO_Init (EXTI_Configure_Pin_t* EXTI_Config);
void MCAL_EXTI_GPIO_DeInit (void);

void MCAL_EXTI_GPIO_Update (EXTI_Configure_Pin_t* EXTI_Config);


//---------------------------------------------------







#endif /* EXTI_DRIVER_EXTI_H_ */

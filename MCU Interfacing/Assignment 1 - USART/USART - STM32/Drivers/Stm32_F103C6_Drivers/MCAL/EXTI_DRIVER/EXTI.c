/*
 * 	EXTI.c
 *
 *  Created on: Dec 13, 2025
 *      Author:  Belal Hani Sabha
 */



#include "EXTI.h"

#include "stm32f103x6.h"
#include "GPIO.h"



/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */

void (*GP_IRQ_FUNC_CALLBACK [16])(void);

/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */


/*																0000: PA[x] pin
																0001: PB[x] pin
																0010: PC[x] pin
																0011: PD[x] pin
																0100: PE[x] pin
																0101: PF[x] pin
																0110: PG[x] pin*/
#define AFIO_GPIO_EXTI_Mapping(x)	(   (x==GPIOA)?0:\
									(x==GPIOB)?1:\
									(x==GPIOC)?2:\
									(x==GPIOD)?3:0  )

/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

void Enable_NVIC (uint16_t IRQ_NUMBER)
{
	switch (IRQ_NUMBER)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable ;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break ;
	case 2:
		NVIC_IRQ8_EXTI2_Enable ;
		break ;
	case 3:
		NVIC_IRQ9_EXTI3_Enable ;
		break ;
	case 4:
		NVIC_IRQ10_EXTI4_Enable ;
		break ;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break ;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break ;

	}
}

void Disable_NVIC (uint16_t IRQ_NUMBER)
{
	switch (IRQ_NUMBER)
		{
		case 0:
			NVIC_IRQ6_EXTI0_Disable ;
			break;
		case 1:
			NVIC_IRQ7_EXTI1_Disable ;
			break ;
		case 2:
			NVIC_IRQ8_EXTI2_Disable;
			break ;
		case 3:
			NVIC_IRQ9_EXTI3_Disable;
			break ;
		case 4:
			NVIC_IRQ10_EXTI4_Disable ;
			break ;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_Disable;
			break ;

		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ40_EXTI10_15_Disable;
			break ;

		}

}

void Update_EXTI (EXTI_Configure_Pin_t* EXTI_Config){


	//1- Configure GPIO to be AF Input -> Floating INPUT
	GPIO_Configure_Pin_t PIN_CFG;
	PIN_CFG.GPOI_Pin_Number = EXTI_Config->EXTI_PIN.GPIO_PIN ;
	PIN_CFG.GPIO_Mode = GPIO_Floating_Input					 ;
	MCAL_GPIO_Init( EXTI_Config->EXTI_PIN.GPIO_PORT , &PIN_CFG );
	//-------------------------------------------------------------------------------------------------------

	//2- UPDATE AFIO to Route between EXTI Line with PORT A,B,C,D
	uint8_t AFIO_EXTICR_RegNumber   = EXTI_Config->EXTI_PIN.EXTI_LINE / 4       ;
	uint8_t AFIO_EXTICR_StartingBit = (EXTI_Config->EXTI_PIN.EXTI_LINE % 4) * 4 ;

	//clear the four bit
	AFIO->EXTICR[AFIO_EXTICR_RegNumber] &= ~(0xF << AFIO_EXTICR_StartingBit );
	AFIO->EXTICR[AFIO_EXTICR_RegNumber] |= (((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_PORT)) & 0x0F)  << AFIO_EXTICR_StartingBit) ;
	//-------------------------------------------------------------------------------------------------------

	//3- Update Rising or falling Register
         EXTI->RTSR &= ~(EXTI_Config->EXTI_PIN.EXTI_LINE);
         EXTI->FTSR &= ~(EXTI_Config->EXTI_PIN.EXTI_LINE);


     if( EXTI_Config->EDGE_CASE == RISING_EDGE){
   	  EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_LINE);
     }else if(EXTI_Config->EDGE_CASE == FALLING_EDGE){

   	  EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_LINE);

     }else{ // both rising and falling
    	  EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_LINE);
    	  EXTI->FTSR |= (1<< EXTI_Config->EXTI_PIN.EXTI_LINE);
     }

 	//-------------------------------------------------------------------------------------------------------
 	//4- Update IRQ Handling CALLBACK
     GP_IRQ_FUNC_CALLBACK[EXTI_Config->EXTI_PIN.EXTI_LINE] = EXTI_Config->P_IRQ_FUNC_CALLBACK;

  	//-------------------------------------------------------------------------------------------------------
 	//5- Enable/Disable IRQ EXTI & NVIC

 	if (EXTI_Config->IRQ_E_D == ENABLE_IRQ_EXTI )
 	{
 		EXTI->IMR |= (1 << EXTI_Config->EXTI_PIN.EXTI_LINE);
 		Enable_NVIC ( EXTI_Config->EXTI_PIN.EXTI_LINE ) ;
 	}else
 	{
 		EXTI->IMR &= ~(1<< EXTI_Config->EXTI_PIN.EXTI_LINE);
 		Disable_NVIC ( EXTI_Config->EXTI_PIN.EXTI_LINE) ;
 	}
 }








/*
 * =======================================================================================
 * 							APIs Functions Definitions
 * =======================================================================================
 */

/**================================================================
 * @Fn					-MCAL_EXTI_GPIO_Init
 * @brief 				-Initializes the EXTI from a specific GPIO pin, and specifies the
							mask/trigger condition and IRQ callback. This API updates the
							AFIO mapping to route between the EXTI line with PORT A, B, C,
							or D and the corresponding EXTI line, updates the rising or falling
							register, and enables or disables the IRQ EXTI and NVIC.
 * @param [in]   		-EXTI_Config set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 				-none
 * Note					-none
 */

void MCAL_EXTI_GPIO_Init (EXTI_Configure_Pin_t* EXTI_Config){

	Update_EXTI(EXTI_Config);

}


/**================================================================
 * @Fn					-MCAL_EXTI_GPIO_DeInit
 * @brief 				-Resets all EXTI registers to their default values and disables the EXTI IRQ from NVIC.
 * @retval 				-none
 * Note					-none
 */
void MCAL_EXTI_GPIO_DeInit (void){

	EXTI->IMR= 0x00000000 ;
	EXTI->EMR= 0x00000000 ;
	EXTI->RTSR=0x00000000 ;
	EXTI->FTSR=0x00000000 ;
	EXTI->SWIER=0x00000000;
	EXTI->PR=0xFFFFFFFF   ;  //This bit is set when the selected edge event arrives on the external interrupt line. This bit is cleared by writing a ‘1’ into the bit.


	//Disable EXTI IRQ From NVIC
	NVIC_IRQ6_EXTI0_Disable  		;
	NVIC_IRQ7_EXTI1_Disable  		;
	NVIC_IRQ8_EXTI2_Disable  		;
	NVIC_IRQ9_EXTI3_Disable  		;
	NVIC_IRQ10_EXTI4_Disable  	    ;
	NVIC_IRQ23_EXTI5_9_Disable      ;
	NVIC_IRQ40_EXTI10_15_Disable    ;
}


/**================================================================
 * @Fn					-MCAL_EXTI_GPIO_Update
 * @brief 				-Updates the EXTI from a specific GPIO pin, and specifies the
							mask/trigger condition and IRQ callback. This API updates the
							AFIO mapping to route between the EXTI line with PORT A, B, C,
							or D and the corresponding EXTI line, updates the rising or falling
							register, and enables or disables the IRQ EXTI and NVIC.
 * @param [in]   		-EXTI_Config set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 				-none
 * Note					-none
 */

void MCAL_EXTI_GPIO_Update (EXTI_Configure_Pin_t* EXTI_Config){

	Update_EXTI(EXTI_Config);
}




///**================================================================
///**================================================================
///**===========			ISR  Functions        =========================
///**================================================================
// */

void EXTI0_IRQHandler (void)
{
	//cleared by writing a ‘1’ into the bit Pending register (EXTI_PR)
	EXTI->PR |= 1<<0 ;
	//CALL IRQ_CALL
	GP_IRQ_FUNC_CALLBACK[0]() ;
}

void EXTI1_IRQHandler (void) {
	EXTI->PR |=  (1<<1) ;

	GP_IRQ_FUNC_CALLBACK[1]() ;

}


void EXTI2_IRQHandler (void) {
	EXTI->PR |=  (1<<2) ;

	GP_IRQ_FUNC_CALLBACK[2]() ;

}


void EXTI3_IRQHandler (void) {
	EXTI->PR |=  (1<<3) ;

	GP_IRQ_FUNC_CALLBACK[3]() ;

}


void EXTI4_IRQHandler (void) {
	EXTI->PR |=  (1<<4) ;
	GP_IRQ_FUNC_CALLBACK[4]() ;

}


void EXTI9_5_IRQHandler (void)
{
	if (EXTI->PR & 1<<5 ) {	EXTI->PR |=  (1<<5)    ; GP_IRQ_FUNC_CALLBACK[5]() ;   }
	if (EXTI->PR & 1<<6 ) {	EXTI->PR |=  (1<<6)    ; GP_IRQ_FUNC_CALLBACK[6]() ;   }
	if (EXTI->PR & 1<<7 ) {	EXTI->PR |=  (1<<7)    ; GP_IRQ_FUNC_CALLBACK[7]() ;   }
	if (EXTI->PR & 1<<8 ) {	EXTI->PR |=  (1<<8)    ; GP_IRQ_FUNC_CALLBACK[8]() ;   }
	if (EXTI->PR & 1<<9 ) {	EXTI->PR |=  (1<<9)    ; GP_IRQ_FUNC_CALLBACK[9]() ;   }

}
void EXTI15_10_IRQHandler (void)
{
	if (EXTI->PR & 1<<10 ) {	EXTI->PR |=  (1<<10)    ; GP_IRQ_FUNC_CALLBACK[10]() ;   }
	if (EXTI->PR & 1<<11 ) {	EXTI->PR |=  (1<<11)    ; GP_IRQ_FUNC_CALLBACK[11]() ;   }
	if (EXTI->PR & 1<<12 ) {	EXTI->PR |=  (1<<12)    ; GP_IRQ_FUNC_CALLBACK[12]() ;   }
	if (EXTI->PR & 1<<13 ) {	EXTI->PR |=  (1<<13)    ; GP_IRQ_FUNC_CALLBACK[13]() ;   }
	if (EXTI->PR & 1<<14 ) {	EXTI->PR |=  (1<<14)    ; GP_IRQ_FUNC_CALLBACK[14]() ;   }
	if (EXTI->PR & 1<<15 ) {	EXTI->PR |=  (1<<15)    ; GP_IRQ_FUNC_CALLBACK[15]() ;   }

}


/*
 * 	GPIO.c
 *
 *  Created on: Dec 8, 2025
 *      Author:  Belal Hani Sabha
 */

#include "GPIO.h"

#include "stm32f103x6.h"

uint8_t Get_Position_in_CRL_CRH(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN0:
		return 0 ;
		break ;
	case GPIO_PIN1:
		return 4 ;
		break ;
	case GPIO_PIN2:
		return 8 ;
		break ;
	case GPIO_PIN3:
		return 12 ;
		break ;

	case GPIO_PIN4:
		return 16 ;
		break ;


	case GPIO_PIN5:
		return 20 ;
		break ;

	case GPIO_PIN6:
		return 24 ;
		break ;

	case GPIO_PIN7:
		return 28 ;
		break ;


	case GPIO_PIN8:
		return 0 ;
		break ;
	case GPIO_PIN9:
		return 4 ;
		break ;

	case GPIO_PIN10:
		return 8 ;
		break ;

	case GPIO_PIN11:
		return 12 ;
		break ;

	case GPIO_PIN12:
		return 16 ;
		break ;


	case GPIO_PIN13:
		return 20 ;
		break ;

	case GPIO_PIN14:
		return 24 ;
		break ;

	case GPIO_PIN15:
		return 28 ;
		break ;



	}

	return 0 ;
}


/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief 			-Initializes the GPIOx PINy according to the specified parameters
 * @param [in] 		-GPIOx: where x is a Port and it can be (A,B,C,D and E) to select the GPIO peripheral
 * @param [in] 		-PinNumber_Configuration to a GPIO_Configure_Pin_t structure that contains
 *         		 		(Pin number , Mode (I/O) and Freqency ).
 * @retval 			-none
 * Note				-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 		But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
 */
void MCAL_GPIO_Init(GPIOx_t *GPIOx , GPIO_Configure_Pin_t* PinNumber_Configuration ){
	//Port configuration register low (GPIOx_CRL) Configure PINS from 0 >>> 7
	//Port configuration register High (GPIOx_CRH) Configure PINS from 8 >>> 15

	volatile uint32_t* Configure_Register = NULL ;
	uint8_t PIN_Config = 0 ;

	// Find Register to Init Pins
	Configure_Register = (PinNumber_Configuration->GPOI_Pin_Number < GPIO_PIN8 ) ? &GPIOx->CRL : &GPIOx->CRH ;

	// clear CNFy[1:0] MODEy[1:0]
   (*Configure_Register) &= ~(0xF <<Get_Position_in_CRL_CRH(PinNumber_Configuration->GPOI_Pin_Number));

   //if Pin is output
   if(PinNumber_Configuration->GPIO_Mode == output_push_pull || PinNumber_Configuration->GPIO_Mode == output_Open_drain || PinNumber_Configuration->GPIO_Mode == Alternate_function_output_Push_pull || PinNumber_Configuration->GPIO_Mode == Alternate_function_output_Open_drain){

	   //Set  CNFy[1:0] MODEy[1:0]
	   PIN_Config = ( (((PinNumber_Configuration->GPIO_Mode - 4 ) << 2) | (PinNumber_Configuration->GPIO_Output_Frequency)) & 0x0F ) ;

   }//if pin is input
   else   //MODEy[1:0]
   {
	   if((PinNumber_Configuration->GPIO_Mode == GPIO_Analog_Mode)  || ( PinNumber_Configuration->GPIO_Mode == GPIO_Floating_Input )){
		   //Set  CNFy[1:0]= 00   MODEy[1:0] = 00
		   PIN_Config = (((PinNumber_Configuration->GPIO_Mode << 2) | 0x0 ) &0x0F) ;

	   }else if(PinNumber_Configuration->GPIO_Mode ==  GPIO_Alternate_function_INPUT){
		   //Set  CNFy[1:0]= 01   MODEy[1:0] = 00
		   PIN_Config = (((GPIO_Floating_Input  << 2) | 0x0 ) &0x0F) ;  //GPIO_Floating_Input


	   }else{  //Input with  pull-down / pull-down
			PIN_Config = ( (((GPIO_Input_pull_up  ) << 2) | 0x0) & 0x0F ) ;

			if (PinNumber_Configuration->GPIO_Mode == GPIO_Input_pull_up )
			{
				//PxODR = 1 Input pull-up
				GPIOx->ODR |= PinNumber_Configuration->GPOI_Pin_Number ;

			}else
			{
				//PxODR = 0 Input pull-down
				GPIOx->ODR &= ~(PinNumber_Configuration->GPOI_Pin_Number) ;
			}




	   }


   }


   // write on the CRL or CRH
   (*Configure_Register) |=  ( (PIN_Config) << Get_Position_in_CRL_CRH(PinNumber_Configuration->GPOI_Pin_Number)   );
}





/**================================================================
 * @Fn				-MCAL_GPIO_DeInit
 * @brief 			-Reset Specific GPIO Registers
 * @param [in] 	-GPIOx: where x is a Port and it can be (A,B,C,D and E) to select the GPIO peripheral
 * @retval 		-none
 * Note			-none
 */
void MCAL_GPIO_DeInit(GPIOx_t *GPIOx){

	/*
//					First Method by Writing Reset Values on Registers
	GPIOx->CRL  = 0x44444444;   //Reset value: 0x4444 4444
	GPIOx->CRH  = 0x44444444;   //Reset value: 0x4444 4444
	GPIOx->ODR  = 0x00000000;   //Reset value: 0x0000 0000
//	GPIOx->IDR  = Invalid;      //this is Read Register can't write on it
	GPIOx->BSRR = 0x00000000;   //Reset value: 0x0000 0000
	GPIOx->BRR  = 0x00000000;   //Reset value: 0x0000 0000
	GPIOx->LCKR = 0x00000000;   //Reset value: 0x0000 0000


	*/

//					Second Method by Using RCC Peripheral
//                  APB2 peripheral reset register (RCC_APB2RSTR)
	if(GPIOx == GPIOA){   		  // bit 2  GPIOPARST
		RCC->APB2RSTR |=  (1<<2) ;
		RCC->APB2RSTR &= ~(1<<2) ;
	}else if(GPIOx == GPIOB){	 // bit 3   GPIOPBRST
		RCC->APB2RSTR |=  (1<<3) ;
		RCC->APB2RSTR &= ~(1<<3) ;
    }else if(GPIOx == GPIOC){	 // bit 4   GPIOPCRST
     	RCC->APB2RSTR |=  (1<<4) ;
		RCC->APB2RSTR &= ~(1<<4) ;
	}else if(GPIOx == GPIOD){   // bit 5   GPIOPDRST
		RCC->APB2RSTR |=  (1<<5) ;
		RCC->APB2RSTR &= ~(1<<5) ;
    }else{						 // bit 6   GPIOPERST
     	RCC->APB2RSTR |=  (1<<6) ;
		RCC->APB2RSTR &= ~(1<<6) ;
	}

}




/**================================================================
 * @Fn				-MCAL_GPIO_ReadPin
 * @brief 			-Read Specific PIN
 * @param [in] 	-GPIOx: where x is a Port and it can be (A,B,C,D and E) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Set Pin Number according @ref GPIO_PINS_define
 * @retval 		-Input Value (0 or 1 )  based on @ref GPIO_PIN_state
 * Note			-none
 */
uint8_t  MCAL_GPIO_ReadPin(GPIOx_t *GPIOx , uint16_t PinNumber){


	 return ( (GPIOx->IDR & PinNumber) ? SET_PIN : RESET_PIN );

}




/**================================================================
 * @Fn					-MCAL_GPIO_ReadPort
 * @brief 				-ٌٌ Read the input port VALUE
 * @param [in] 			-GPIOx: where x is a Port and it can be (A,B,C,D and E) to select the GPIO peripheral
 * @retval 				-the input port VALUE
 * Note					-none
 */
uint16_t MCAL_GPIO_ReadPort(GPIOx_t *GPIOx){
	   uint16_t PortStatus;
	   PortStatus =  (uint16_t)(GPIOx->IDR) ;
	   return   PortStatus;
}



/**================================================================
 * @Fn					-MCAL_GPIO_WritePin
 * @brief 				-Write on specific input pin
 * @param [in] 			-GPIOx: where x is a Port and it can be (A,B,C,D and E) to select the GPIO peripheral
 *@param [in] 			-PinNumber:  specifies the port bit to read. Set by @ref GPIO_PINS_define
 *@param [in] 			-Value: Value
 * @retval 				-none
 * Note					-none
 */
void MCAL_GPIO_WritePin(GPIOx_t *GPIOx , uint16_t PinNumber , uint8_t Value){


	if (Value == SET_PIN )
	{
	     /*		Bits 31:16 BRy: Port x Reset bit y (y= 0 .. 15)
				These bits are write-only and can be accessed in Word mode only.
				0: No action on the corresponding ODRx bit
				1: Reset the corresponding ODRx bit
				Note: If both BSx and BRx are set, BSx has priority.

				Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
				These bits are write-only and can be accessed in Word mode only.
				0: No action on the corresponding ODRx bit
				1: Set the corresponding ODRx bit*/
		 GPIOx->BSRR = (uint32_t)PinNumber ;
	}else
	{
		/*Bits 15:0BRy: Port x Reset bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Reset the corresponding ODRx bit*/
		 GPIOx->BRR = (uint32_t)PinNumber ;
	}


}



/**================================================================
 * @Fn					-MCAL_GPIO_WritePort
 * @brief 				-write on output port
 * @param [in] 			-GPIOx: where x is a Port and it can be (A,B,C,D and E) to select the GPIO peripheral
 * @retval 				-none
 * Note					-none
 */
void MCAL_GPIO_WritePort(GPIOx_t *GPIOx , uint16_t Value){

	GPIOx->ODR = (uint32_t)Value;


}



/**================================================================
 * @Fn					-MCAL_GPIO_TogglePin
 * @brief 				-Toggles the specified GPIO pin
 * @param [in] 			-GPIOx: where x is a Port and it can be (A,B,C,D and E) to select the GPIO peripheral
 * @param [in] 			-PinNumber: specifies the port bit to read. Set by @ref GPIO_PINS_define
 * @retval 				-none
 * Note				-	-none
 */
void MCAL_GPIO_TogglePin(GPIOx_t *GPIOx , uint16_t PinNumber){
	GPIOx->ODR ^= (PinNumber) ;
}





/**================================================================
 * @Fn					-MCAL_GPIO_LockPin
 * @brief 				-The locking mechanism allows the IO configuration to be frozen
 * @param [in] 			-GPIOx: where x is a Port and it can be (A,B,C,D and E) to select the GPIO peripheral
 * @param [in] 			-PinNumber: specifies the port bit to read. Set by @ref GPIO_PINS_define
 * @retval 				-Ok if pin Config is locked Or ERROR if pin  not locked  (OK & ERROR are defined @ref GPIO_RETURN_LOCK
 * Note					-none
 */
uint8_t MCAL_GPIO_LockPin(GPIOx_t *GPIOx , uint16_t PinNumber){

/*This register is used to lock the configuration of the port bits when a correct write sequence
is applied to bit 16 (LCKK). The value of bits [15:0] is used to lock the configuration of the
GPIO. During the write sequence, the value of LCKR[15:0] must not change. When the
LOCK sequence has been applied on a port bit it is no longer possible to modify the value of
the port bit until the next reset.
Each lock bit freezes the corresponding 4 bits of the control register (CRL, CRH).*/

	/*Bits 31:17 Reserved
     Bit 16 LCKK[16]: Lock key
			This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
				0: Port configuration lock key not active
				1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.

				LOCK key writing sequence:
				Write 1
				Write 0
				Write 1
				Read 0
				Read 1 (this read is optional but confirms that the lock is active)
				Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
				Any error in the lock sequence will abort the lock.

	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
				These bits are read write but can only be written when the LCKK bit is 0.
				0: Port configuration not locked
				1: Port configuration locked.*/

	GPIOx->LCKR = (uint32_t)PinNumber  | (1 << 16);    // WRITE 1 ON 	PinNumber bit and bit 16
	GPIOx->LCKR = (uint32_t)PinNumber;                 //Write 0 om PinNumber bit
	GPIOx->LCKR = (uint32_t)PinNumber  | (1 << 16) ;   // WRITE 1 ON 	PinNumber bit and bit 16

	volatile uint32_t temp;
	temp = GPIOx->LCKR; 							  // Read 0
	temp = GPIOx->LCKR; 							  // Read 1 (lock confirmed)

	return (temp & (1<<16)) ? (GPIO_RETURN_LOCK_Enabled) : (GPIO_RETURN_LOCK_ERROR) ;


}

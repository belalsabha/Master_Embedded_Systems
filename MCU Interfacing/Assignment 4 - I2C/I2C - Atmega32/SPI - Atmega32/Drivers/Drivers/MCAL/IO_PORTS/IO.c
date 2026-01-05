/*
 * IO.c
 * Created on: Dec 14, 2025
 * Author: Belal Hani Sabha
 */



#include "IO.h"




/**================================================================
 * @Fn				-MCAL_IO_Init
 * @brief 			-Initializes the IOx PINy according to the specified parameters
 * @param [in] 		-IOx: where x is a Port and it can be (A,B,C,D) to select the IO peripheral
 * @param [in] 		-PinNumber_Configuration to a IO_Configure_Pin_t structure that contains
 *         		 		(Pin number , Mode (I/O) ).
 * @retval 			-none
 */
void MCAL_IO_Init(IOx_t *IOx , IO_Configure_Pin_t* PinNumber_Configuration){
	//  we need to configure pin as input or output and its mode
	
	
// The DDxn bit in the DDRx Register selects the direction of this pin. If DDxn is written logic one,
// Pxn is configured as an output pin. If DDxn is written logic zero, Pxn is configured as an input
// pin	

// 	If PORTxn is written logic one when the pin is configured as an input pin, the pull-up resistor is
// 	activated.  : DDR &=~(bit << 1) ,  PORT &=~(bit << 1)
			
	if(PinNumber_Configuration->IO_Mode == input_without_pull_up){
		IOx->DDR  &= ~ (PinNumber_Configuration->IO_Pin_Number);
		IOx->PORT &= ~ (PinNumber_Configuration->IO_Pin_Number);
	}/* To switch the pull-up resistor off, PORTxn has to be written logic zero, DDR &=~(bit << 1) ,  PORT|=(bit << 1) */
	else if(PinNumber_Configuration->IO_Mode == input_with_pull_up){
		IOx->DDR  &= ~ (PinNumber_Configuration->IO_Pin_Number);
		IOx->PORT |=  (PinNumber_Configuration->IO_Pin_Number);
	}
	else {//if Pin is output
		IOx->DDR  |=  (PinNumber_Configuration->IO_Pin_Number);   //  DDR |=(bit << 1)
		if(PinNumber_Configuration->IO_Mode == output_Hight){
			IOx->PORT |=  (PinNumber_Configuration->IO_Pin_Number);  //If PORTxn is written logic one when the pin is configured as an output pin, the port pin is driven high (one)
			} else {
			IOx->PORT &= ~ (PinNumber_Configuration->IO_Pin_Number); //  If PORTxn is written logic zero when the pin is configured as an output pin, the port pin is driven low (zero).
		}
	}
}






/**================================================================
 * @Fn				-MCAL_IO_DeInit
 * @brief 			-Reset Specific IO Registers
 * @param [in]		-IOx: where x is a Port and it can be (A,B,C,D ) to select the IO peripheral
 * @retval 			-none
 * Note				-none
 */
void MCAL_IO_DeInit(IOx_t *IOx){
	
	// using direct method and write reset values on register 
	IOx->DDR  = 0x00;    //Reset value: 0x0000
	IOx->PORT = 0x00;	 //Reset value: 0x0000
// 	IOx->PIN  =  N/A    //this is Read Register can't write on it

}







/**================================================================
 * @Fn				-MCAL_IO_ReadPin
 * @brief 			-Read Specific PIN
 * @param [in] 		-IOx: where x is a Port and it can be (A,B,C,D ) to select the IO peripheral
 * @param [in] 		-PinNumber: Set Pin Number according @ref IO_PINS_define
 * @retval 			-Input Value (0 or 1 )  based on @ref IO_PIN_state
 * Note				-none
 */
uint8_t MCAL_IO_ReadPin(IOx_t *IOx, uint8_t PinNumber){
	return ((IOx->PIN & PinNumber) != 0) ? SET_PIN : RESET_PIN;  // read value on pin if not equal 0 that mean its 1 so pin status is 1 else 0  
}





/**================================================================
 * @Fn					-MCAL_IO_ReadPort
 * @brief 				-Read the input port VALUE
 * @param [in] 			-IOx: where x is a Port and it can be (A,B,C,D) to select the IO peripheral
 * @retval 				-the input port VALUE
 * Note					-none
 */
uint8_t MCAL_IO_ReadPort(IOx_t *IOx){
	return IOx->PIN;  // return value on pin from pin0 to pin7 
}



/**================================================================
 * @Fn					-MCAL_IO_WritePin
 * @brief 				-Write on specific input pin
 * @param [in] 			-IOx: where x is a Port and it can be (A,B,C,D ) to select the IO peripheral
 *@param [in] 			-PinNumber:  specifies the port bit to read. Set by @ref IO_PINS_define
 *@param [in] 			-Value: Value
 *@retval 				-none
 * Note					-none
 */
void MCAL_IO_WritePin(IOx_t *IOx, uint8_t PinNumber, uint8_t Value){
	if(Value == SET_PIN){        //user will send 1 or 0 on  bit we should take this value and put it in port register 
		IOx->PORT |= PinNumber;
		} else {
		IOx->PORT &= ~PinNumber;
	}
}



/**================================================================
 * @Fn					-MCAL_IO_WritePort
 * @brief 				-write on output port
 * @param [in] 			-IOx: where x is a Port and it can be (A,B,C,D ) to select the IO peripheral
 * @retval 				-none
 * Note					-none
 */
void MCAL_IO_WritePort(IOx_t *IOx , uint8_t Value){
	IOx->PORT = (uint8_t) Value ; 
}




/**================================================================
 * @Fn					-MCAL_IO_TogglePin
 * @brief 				-Toggles the specified IO pin
 * @param [in] 			-IOx: where x is a Port and it can be (A,B,C,D ) to select the IO peripheral
 * @param [in] 			-PinNumber: specifies the port bit to read. Set by @ref IO_PINS_define
 * @retval 				-none
 * Note				-	-none
 */
void MCAL_IO_TogglePin(IOx_t *IOx , uint8_t PinNumber){
	IOx->PORT ^= (PinNumber);
}
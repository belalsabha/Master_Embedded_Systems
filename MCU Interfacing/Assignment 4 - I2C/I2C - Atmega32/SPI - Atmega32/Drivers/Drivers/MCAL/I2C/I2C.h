/*
 * I2C.h
 *
 * Created: 16/07/47 08:50:28 
 * Author : Belal Hani Sabha
 */


#ifndef I2C_H_
#define I2C_H_


//----------------------------------
//Includes
//----------------------------------
#include "Atmega32.h"
#include "IO.h"


//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//----------------------------------
//User type definitions (structures)
//----------------------------------
//Configuration structure For User inputs
typedef struct {

		uint8_t  Slave_Address 				;	//These seven bits constitute the slave address of the TWI unit
		
		
		uint32_t Speed			 			; 	//specified the I2C Speed up to 400khz.
													//this parameter must be set based on  @ref I2C_Speed_MODE_Define

		
		uint8_t  Prescaler					;	//and control the bit rate prescaler
													//this parameter must be set based on @ref I2C_Prescaler_Define
	
	
	   uint8_t  IRQ_Enable	 	           ; 		//enable or disable SPI IRQ
														//@ref SPI_IRQ_Enable_define


	  void 	   (*Ptr_ISR_Func)(void)       ;	    //Set the C Function() which will be called once the IRQ  Happen


}I2C_Config_t;











//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//----------------------------------
//Macros Configuration References
//----------------------------------
//@ref I2C_Speed_MODE_Define
#define Speed_50							50000
#define Speed_100							100000
#define Speed_50							150000
#define Speed_200							200000




// @ref I2C_Prescaler_Defin
// • Bits [1:0] – TWPS: TWI Prescaler Bits
// These bits can be read and written, and control the bit rate prescaler.
// Table 73.  TWI Bit Rate Prescaler
// TWPS1			TWPS0      Prescaler Value
// 0				0			 1
// 0				1			 4
// 1				0			16
// 1				1			64
#define Prescaler_1								1
#define Prescaler_4								4
#define Prescaler_16							16
#define Prescaler_64							64


//@ref SPI_IRQ_Enable_define
#define I2C_IRQ_Disable         (0)
#define I2C_IRQ_Enable          (1<<0)  //• • • Bit 0 – TWIE: TWI Interrupt Enable




/*
 * =======================================================================================
 * 							APIs Supported by "MCAL SPI DRIVER"
 * =======================================================================================
 */

void MCAL_I2C_Init(I2C_t *I2Cx , I2C_Config_t *I2C_Config);
void MCAL_I2C_DeInit();

void MCAL_I2C_Master_Send(uint8_t Slave_Address, uint8_t Buff);
uint8_t MCAL_I2C_Master_Recieve(uint8_t Slave_Address);

void MCAL_I2C_Slave_Send(uint8_t Buff) ;
uint8_t MCAL_I2C_Slave_Recieve(void) ;



void Generate_Stop_Bit();
void Generate_Start_Bit();






#endif /* I2C_H_ */
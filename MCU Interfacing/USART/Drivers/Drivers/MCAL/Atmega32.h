/*
 * Atmega32.h
 *
 * Created: 14 / 12 /2025
 * Author : Belal Hani Sabha
 */ 

#ifndef ATMEGA32_H_
#define ATMEGA32_H_

#include <stdint.h>


//----------------------------------
//Base addresses for Memories
//----------------------------------
#define Application_Flash_Section	0x0000
#define Boot_Flash_Section			0x001F
#define IO_Registers				0x0020
#define Internal_SRAM				0x0060




//----------------------------------
//Base addresses for BUS Peripherals
//----------------------------------
//		For Atmega32 BUS
//----------------------------------
//for IO Ports
#define IOA_Base		0x39U
#define IOB_Base		0x36U
#define IOC_Base		0x33U
#define IOD_Base		0x30U

//for EXTI
#define EXTI_Base      0x54

#define USART_Base     0X29

// for status
#define StatusRegister 0x005F



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
/*---------------------------------------------------*/
// Each port pin consists of three register bits: DDxn, PORTxn, and PINxn
typedef struct {
	
    volatile uint8_t PIN ;   // Input pins address
    volatile uint8_t DDR ;   // Data Direction Register
    volatile uint8_t PORT;  // Output register

}IOx_t;





typedef struct {
	volatile uint8_t MCUCSR;
	volatile uint8_t MCUCR;
	volatile uint8_t RESERVED[4];
	volatile uint8_t GIFR;
	volatile uint8_t GICR;
}EXTI_t;


typedef struct {
	volatile uint8_t UBRRL;
	volatile uint8_t UCSRB;
	volatile uint8_t UCSRA;
	volatile uint8_t UDR;
	volatile uint8_t RESERVED[19];
	volatile uint8_t UCSRC ;

}USART_t;



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
/*---------------------------------------------------*/
#define IOA		((IOx_t *)IOA_Base)  
#define IOB		((IOx_t *)IOB_Base)  
#define IOC		((IOx_t *)IOC_Base)  
#define IOD		((IOx_t *)IOD_Base) 
#define USART	((USART_t *)USART_Base)  
#define EXTI    ((EXTI_t  *)EXTI_Base)

#define SREG	(*(volatile uint8_t*)StatusRegister)


/*---------------------------------------------------*/










#endif /* ATMEGA32_H_ */

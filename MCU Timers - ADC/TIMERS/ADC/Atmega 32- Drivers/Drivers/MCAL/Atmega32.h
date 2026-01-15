/*
 * Atmega32.h
 *
 * Created: 14 / 12 /2025
 * Author : Belal Hani Sabha
 */ 

#ifndef ATMEGA32_H_
#define ATMEGA32_H_

#include "PLATFORM_TYPES.h"



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

//for USART
#define USART_Base     0X29

//for SPI
#define SPI_Base      0X2D

//for I2C 
#define I2C_Base      0X20
#define TWCR					*((volatile uint8_t*)0X56)  //I2C TWCR Register

//for Timers
#define TIMER0_Base      0X52
#define TIMER1_Base      0X46
#define TIMER2_Base      0X43



//for WDT
#define WDT_Base      0X42

//for WDT
#define ADC_Base      0X24

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
 	volatile uint8_t  UCSRC ;    // volatile uint8_t  UBRRH ; on the same address and we can controling it bu using bit no.7 in UCSRC

}USART_t;


typedef struct {
	volatile uint8_t  SPCR;
	volatile uint8_t  SPSR;
	volatile uint8_t  SPDR;
}SPI_t;



typedef struct {
	volatile uint8_t TWBR;
	volatile uint8_t TWSR;
	volatile uint8_t TWAR;
	volatile uint8_t TWDR;
// 	volatile uint8_t RESERVED[50];    not acceptable losing 50 bit to lead to Address of TWCR Register
//     volatile uint8_t TWCR;
}I2C_t;


typedef struct {
	volatile uint8_t TCNT0;
	volatile uint8_t TCCR0;
	volatile uint8_t RESERVED1[4];
	volatile uint8_t TIFR;
	volatile uint8_t TIMSK;
	volatile uint8_t RESERVED2[2];
	volatile uint8_t OCR0;
}TIMER0_t;


typedef struct {
	volatile uint8_t  ICR1L;
	volatile uint8_t  ICR1H;
	volatile uint8_t  OCR1BL;
	volatile uint8_t  OCR1BH;
	volatile uint8_t  OCR1AL;
	volatile uint8_t  OCR1AH;
	volatile uint8_t  TCNT1L;
	volatile uint8_t  TCNT1H;
	volatile uint8_t  TCCR1B;
	volatile uint8_t  TCCR1A;
	volatile uint8_t  RESERVED[9];
	volatile uint8_t  TIFR ;
	volatile uint8_t  TIMSK;
}TIMER1_t;


typedef struct {
	volatile uint8_t ASSR;
	volatile uint8_t  OCR2;
	volatile uint8_t  TCNT2;
	volatile uint8_t  TCCR2;
	volatile uint8_t  RESERVED_[10];
	volatile uint8_t  SFIOR;
	volatile uint8_t  RESERVED[7];
	volatile uint8_t  TIFR ;
	volatile uint8_t  TIMSK;
}TIMER2_t;


typedef struct {
	volatile uint8_t  WDTCR;
}WDT_t;






typedef struct {
	volatile uint8_t  ADCL;
	volatile uint8_t  ADCH;
	volatile uint8_t  ADCSRA;
	volatile uint8_t  ADMUX;
	volatile uint8_t  ACSR;

}ADC_t;


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
#define SPI	    ((SPI_t *)SPI_Base)
#define I2C	    ((I2C_t *)I2C_Base)
#define WDT	    ((WDT_t *)WDT_Base)
#define TIMER0	((TIMER0_t *)TIMER0_Base)
#define TIMER1	((TIMER1_t *)TIMER1_Base)
#define TIMER2	((TIMER2_t *)TIMER2_Base)
#define ADC		((ADC_t *)ADC_Base)


#define SREG	(*(volatile uint8_t*)StatusRegister)


/*---------------------------------------------------*/










#endif /* ATMEGA32_H_ */

/*
 * Stm32f103x6.h
 *
 *  Created on: Dec 8, 2025
 *      Author:  Belal Hani Sabha
 */

#ifndef STM32F103X6_H_
#define STM32F103X6_H_


//----------------------------------

//----------------------------------


//----------------------------------
//Includes
//----------------------------------
#include "stdlib.h"
#include <stdint.h>



//----------------------------------
//Base addresses for Memories
//----------------------------------
#define Flash_memory_Base						0X08000000UL
#define System_memory_Base						0x1FFFF000UL
#define SRAM_Base								0X20000000UL
#define Peripherals_Base						0X40000000UL
#define CortexM3_internal_Peripherals_Base		0xE0000000UL




//NVIC register map
//0-31    ISER[0]  for set    , ICER[0] for RESET
//32-63   ISER[1]  for set    , ICER[1]
//64-67    ISER[2] for set    , ICER[2]

#define NVIC_Base					 			(0xE000E100UL)
#define NVIC_ISER0								*(volatile uint32_t *)(NVIC_Base + 0x0 )
#define NVIC_ISER1								*(volatile uint32_t *)(NVIC_Base + 0x4 )
#define NVIC_ISER2								*(volatile uint32_t *)(NVIC_Base + 0x8 )
#define NVIC_ICER0								*(volatile uint32_t *)(NVIC_Base + 0x80)
#define NVIC_ICER1								*(volatile uint32_t *)(NVIC_Base + 0x84)
#define NVIC_ICER2								*(volatile uint32_t *)(NVIC_Base + 0x88)


//----------------------------------
//Base addresses for BUS Peripherals
//----------------------------------

//		For AHB BUS
//----------------------------------

//		1-RCC
#define Reset_and_clock_control_RCC_Base		0x40021000UL


// 		For APB2 BUS
//----------------------------------

//   	1-AFIO
#define AFIO_Base			0x40010000UL

//   	2-EXTI
#define EXTI_Base				0x40010400UL

//		3-GPIO
//A , B fully included in LQFP48 Package
#define GPIOPortA_Base		0x40010800UL
#define GPIOPortB_Base		0x40010C00UL

//C , D Partial  included in LQFP48 Package
#define GPIOPortC_Base		0x40011000UL
#define GPIOPortD_Base		0x40011400UL

//E , F , G not  included in LQFP48 Package
#define GPIOPortE_Base		0x40011800UL
#define GPIOPortF_Base		0x40011C00UL
#define GPIOPortG_Base		0x40012000UL

//           For USART
#define USART1_Base			0x40013800UL


// 		For APB1 BUS
//----------------------------------
#define USART2_Base			0x40004400UL
#define USART3_Base		 	0x40004400UL
//======================================================================







//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CR		 ; //0x00
	volatile uint32_t CFGR		 ; //0x04
	volatile uint32_t CIR 		 ; //0x08
	volatile uint32_t APB2RSTR   ; //0x0C
	volatile uint32_t APB1RSTR   ; //0x10
	volatile uint32_t AHBENR	 ; //0x14
	volatile uint32_t APB2ENR 	 ; //0x18
	volatile uint32_t APB1ENR	 ; //0x1C
    volatile uint32_t BDCR		 ; //0x20
    volatile uint32_t CSR		 ; //0x24
    volatile uint32_t AHBSTR     ; //0x28
}RCC_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t EVCR		 ; 	//0x00
	volatile uint32_t MAPR	 	 ; 	//0x04
	volatile uint32_t EXTICR[4];   // use array that has EXTICR1 to EXTICR4
	//volatile uint32_t EXTICR1    ;  //0x08
	//volatile uint32_t EXTICR2    ;  //0x0C
	//volatile uint32_t EXTICR3    ;  //0x10
	//volatile uint32_t EXTICR4    ;  //0x14
	         uint32_t RESERVED0  ;  //0x18
	volatile uint32_t  MAPR2     ;  //0x1C
}AFIO_t;



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	volatile uint32_t IMR		;  //0x00
	volatile uint32_t EMR	 	;  //0x04
	volatile uint32_t RTSR      ;  //0x08
	volatile uint32_t FTSR      ;  //0x0C
	volatile uint32_t SWIER     ;  //0x10
	volatile uint32_t PR    	;  //0x14

}EXTI_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	volatile uint32_t  SR		 	;  //0x00
	volatile uint32_t  DR	 		;  //0x04
	volatile uint32_t  BRR        	;  //0x08
	volatile uint32_t  CR1     		;  //0x0C
	volatile uint32_t  CR2   		;  //0x10
	volatile uint32_t  CR3   		;  //0x14
	volatile uint32_t  GTPR   		;  //0x18

}USART_t;






//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CRL	 ; //0x00
	volatile uint32_t CRH	 ; //0x04
	volatile uint32_t IDR    ; //0x08
	volatile uint32_t ODR    ; //0x0C
	volatile uint32_t BSRR   ; //0x10
	volatile uint32_t BRR    ; //0x14
	volatile uint32_t LCKR   ; //0x18

}GPIOx_t;








//======================================================================






//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define RCC     ((RCC_t   *)   Reset_and_clock_control_RCC_Base)

#define AFIO    ((AFIO_t  *)   AFIO_Base                       )

#define EXTI    ((EXTI_t  *)   EXTI_Base                       )

#define GPIOA   ((GPIOx_t *)   GPIOPortA_Base)
#define GPIOB   ((GPIOx_t *)   GPIOPortB_Base)
#define GPIOC   ((GPIOx_t *)   GPIOPortC_Base)
#define GPIOD   ((GPIOx_t *)   GPIOPortD_Base)
#define GPIOE   ((GPIOx_t *)   GPIOPortE_Base)
#define GPIOF   ((GPIOx_t *)   GPIOPortF_Base)
#define GPIOG   ((GPIOx_t *)   GPIOPortG_Base)

#define USART1   ((USART_t *)   USART1_Base	)
#define USART2   ((USART_t *)   USART2_Base	)
#define USART3   ((USART_t *)   USART3_Base	)






//======================================================================



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// For GPIO
#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR |= 1<<0)
#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<6)


// For USART
// Enable
#define RCC_USART1_CLK_EN()	(RCC->APB2ENR |= 1<<14)		//Bit 14USART1RST: USART1 set
#define RCC_USART2_CLK_EN()	(RCC->APB1ENR |= 1<<17)		//Bit 17USART1RST: USART2 set
#define RCC_USART3_CLK_EN()	(RCC->APB1ENR |= 1<<18)		//Bit 18USART1RST: USART3 set

// Reset
#define RCC_USART1_CLK_Reset()	(RCC->APB2RSTR |= 1<<14)	//Bit 14USART1RST: USART1 reset
#define RCC_USART2_CLK_Reset()	(RCC->APB1RSTR |= 1<<17)	//Bit 17USART1RST: USART2 reset
#define RCC_USART3_CLK_Reset()	(RCC->APB1RSTR |= 1<<18)	//Bit 18USART1RST: USART3 reset




//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//IVT
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI For GPIO Pins
#define 	EXTI0_IRQ			6
#define 	EXTI1_IRQ			7
#define 	EXTI2_IRQ			8
#define 	EXTI3_IRQ			9
#define 	EXTI4_IRQ			10
#define 	EXTI5_IRQ			23
#define 	EXTI6_IRQ			23
#define 	EXTI7_IRQ			23
#define 	EXTI8_IRQ			23
#define 	EXTI9_IRQ			23
#define 	EXTI10_IRQ			40
#define 	EXTI11_IRQ			40
#define 	EXTI12_IRQ			40
#define 	EXTI13_IRQ			40
#define 	EXTI14_IRQ			40
#define 	EXTI15_IRQ			40

// Global Interrupt For USART
#define 	USART1_IRQ		37
#define 	USART2_IRQ		38
#define 	USART3_IRQ		39





//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ enable/Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//Interrupt set-enable registers For IRQ 0 to 15 (NVIC_ISERx)
#define NVIC_IRQ6_EXTI0_Enable  	    (NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Enable   		(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable   		(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable   		(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable   		(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable   	(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Enable   	(NVIC_ISER1 |= 1<<8)      //bit number 8 = interrupt number 40 ;


//Interrupt clear-enable registers (NVIC_ICERx)
#define NVIC_IRQ6_EXTI0_Disable  	    (NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Disable   		(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Disable   		(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Disable   		(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable   		(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable   	(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable   	(NVIC_ICER1 |= 1<<8) 	//bit number 8 = interrupt number 40 ; 40-32

//Interrupt set-enable registers For USART (NVIC_ISERx)
#define NVIC_IRQ37_USART1_Enable  	    (NVIC_ISER1 |= 1<<5)	//bit number 5 = interrupt number 37 ; 37-32
#define NVIC_IRQ38_USART2_Enable  	    (NVIC_ISER1 |= 1<<6)	//bit number 6 = interrupt number 38 ; 38-32
#define NVIC_IRQ39_USART3_Enable  	    (NVIC_ISER1 |= 1<<7)	//bit number 7 = interrupt number 39 ; 39-32



//Interrupt clear-enable registers For USART (NVIC_ICERx)
#define NVIC_IRQ37_USART1_Disable  	    (NVIC_ICER1 |= 1<<5)	//bit number 5 = interrupt number 37 ;
#define NVIC_IRQ38_USART2_Disable  	    (NVIC_ICER1 |= 1<<6)	//bit number 6 = interrupt number 38 ;
#define NVIC_IRQ39_USART3_Disable  	    (NVIC_ICER1 |= 1<<7)	//bit number 7 = interrupt number 39 ;




#endif /* STM32F103X6_H_ */

/*
 * Stm32f103x6.h
 *
 *  Created on: Dec 8, 2025
 *      Author:  Belal Hani Sabha
 */

#ifndef STM32F103X6_H_
#define STM32F103X6_H_




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
#define EXTI				0x40010400UL

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


// 		For APB1 BUS
//----------------------------------


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
	volatile uint32_t EXTICR1    ;  //0x08
	volatile uint32_t EXTICR2    ;  //0x0C
	volatile uint32_t EXTICR3    ;  //0x10
	volatile uint32_t EXTICR4    ;  //0x14
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
#define RCC     ((RCC_t *  )   Reset_and_clock_control_RCC_Base)
#define AFIO    ((AFIO_t * )   AFIO_Base)
#define EXTI    ((EXTI_t * )   EXTI_Base)
#define GPIOA   ((GPIOx_t *)   GPIOPortA_Base)
#define GPIOB   ((GPIOx_t *)   GPIOPortB_Base)
#define GPIOC   ((GPIOx_t *)   GPIOPortC_Base)
#define GPIOD   ((GPIOx_t *)   GPIOPortD_Base)
#define GPIOE   ((GPIOx_t *)   GPIOPortE_Base)
#define GPIOF   ((GPIOx_t *)   GPIOPortF_Base)
#define GPIOG   ((GPIOx_t *)   GPIOPortG_Base)






//======================================================================



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


#define AFIO_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<0)
#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<6)



//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*




#endif /* STM32F103X6_H_ */

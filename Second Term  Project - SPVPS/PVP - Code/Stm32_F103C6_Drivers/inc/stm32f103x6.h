/*
 * Stm32f103x6.h
 *
 *  Created on: Dec 8, 2025
 *  Developer & Tester : Eng - Belal Hani Sabha
 */

#ifndef STM32F103X6_H_
#define STM32F103X6_H_


//----------------------------------

//----------------------------------


//----------------------------------
//Includes
//----------------------------------
#include <stdlib.h>
#include "PLATFORM_TYPES.h"



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


//for SPI
#define SPI1_Base			0x40013000UL

// 		For APB1 BUS
//----------------------------------
#define USART2_Base			0x40004400UL
#define USART3_Base		 	0x40004400UL

#define SPI2_Base			0x40003C00UL

//for I2C
#define I2C1_Base			0x40005400UL
#define I2C2_Base		 	0x40005800UL

// for TIMER2
#define TIM2_Base           0x40000000UL
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


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CR1	 ; //0x00
	volatile uint32_t CR2	 ; //0x04
	volatile uint32_t  SR    ; //0x08
	volatile uint32_t  DR    ; //0x0C
	volatile uint32_t CRCPR  ; //0x10
	volatile uint32_t RXCRCR ; //0x14
	volatile uint32_t TXCRCR ; //0x18
	volatile uint32_t I2SCFGR; //0x1C
	volatile uint32_t I2SPR  ; //0x20

}SPI_t;





//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CR1	  ; //0x00
	volatile uint32_t CR2	  ; //0x04
	volatile uint32_t OAR1    ; //0x08
	volatile uint32_t OAR2    ; //0x0C
	volatile uint32_t DR      ; //0x10
	volatile uint32_t SR1     ; //0x14
	volatile uint32_t SR2     ; //0x18
	volatile uint32_t CCR	  ; //0x1C
	volatile uint32_t TRISE	  ; // 0x20

}I2Cx_t;



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: TIMER2
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CR1	  ; //0x00
	volatile uint32_t CR2	  ; //0x04
	volatile uint32_t SMCR    ; //0x08
	volatile uint32_t DIER    ; //0x0C
	volatile uint32_t SR      ; //0x10
	volatile uint32_t EGR     ; //0x14
	volatile uint32_t CCMR1   ; //0x18
	volatile uint32_t CCMR2	  ; //0x1C
	volatile uint32_t CCER	  ; // 0x20
	volatile uint32_t CNT	  ; // 0x24
	volatile uint32_t PSC	  ; // 0x28
	volatile uint32_t ARR	  ; // 0x2C
	volatile uint8_t RESERVED1[4];// 0x30
	volatile uint32_t CCR1	  ; // 0x34
	volatile uint32_t CCR2	  ; // 0x38
	volatile uint32_t CCR3	  ; // 0x3C
	volatile uint32_t CCR4	  ; // 0x40
	volatile uint8_t RESERVED2[4];// 0x44
	volatile uint32_t DCR	  ; // 0x48
	volatile uint32_t DMAR	  ; // 0x4C

}TIMER2_t;

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

#define SPI1   ((SPI_t *)  	SPI1_Base	)
#define SPI2   ((SPI_t *)  	SPI2_Base	)

#define I2C1   ((I2Cx_t *)  	I2C1_Base	)
#define I2C2   ((I2Cx_t *)  	I2C2_Base	)

#define TIMER2   ((TIMER2_t *)  TIM2_Base 	)



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

//For SPI
#define RCC_SPI1_CLK_EN()	(RCC->APB2ENR |= 1<<12)		//Bit 12 SPI1EN: SPI 1 clock enable
#define RCC_SPI2_CLK_EN()	(RCC->APB1ENR |= 1<<14)		//Bit 14 SPI2EN: SPI 2 clock enable

//Reset
#define RCC_SPI1_CLK_Reset()	(RCC->APB2RSTR |= 1<<12)	//Bit 12 SPI1RST: SPI 1 reset
#define RCC_SPI2_CLK_Reset()	(RCC->APB1RSTR |= 1<<14)	//Bit 14 SPI2RST: SPI2 reset


//For I2C
#define RCC_I2C1_CLK_EN()	(RCC->APB1ENR |= 1<<21)			//Bit 21 I2C1EN: I2C1 clock enable
#define RCC_I2C2_CLK_EN()	(RCC->APB1ENR |= 1<<22)			//Bit 22 I2C2EN: I2C2 clock enable

//Reset
#define RCC_I2C1_CLK_Reset()	(RCC->APB1RSTR |= 1<<21)	//Bit 21 I2C1RST: I2C1 reset
#define RCC_I2C2_CLK_Reset()	(RCC->APB1RSTR |= 1<<22)	//Bit 22 I2C2RST: I2C2 reset


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


// Global Interrupt For SPI
#define 	SPI1_IRQ		35
#define 	SPI2_IRQ		36

// Global Interrupt For I2C
#define 	I2C1_EV_IRQ		31    // I2C1 event interrupt
#define 	I2C1_ER_IRQ		32    // I2C1 error interrupt
#define 	I2C2_EV_IRQ		33   //  I2C2 event interrupt
#define 	I2C2_ER_IRQ		34   //  I2C2 error interrupt



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



//Interrupt set-enable registers For SPI (NVIC_ISERx)
#define NVIC_IRQ37_SPI1_Enable  	    (NVIC_ISER1 |= 1<<3)	//bit number 3 = interrupt number 35 ; 35-32
#define NVIC_IRQ38_SPI2_Enable  	    (NVIC_ISER1 |= 1<<4)	//bit number 4 = interrupt number 36 ; 36-32



//Interrupt clear-enable registers For SPI (NVIC_ICERx)
#define NVIC_IRQ37_SPI1_Disable  	    (NVIC_ICER1 |= 1<<3)	//bit number 3 = interrupt number 35 ;
#define NVIC_IRQ38_SPI2_Disable  	    (NVIC_ICER1 |= 1<<4)	//bit number 4 = interrupt number 36 ;



//Interrupt set-enable registers For SPI (NVIC_ISERx)
#define NVIC_IRQ31_I2C1_Enable  	    (NVIC_ISER0 |= 1<<31)	//bit number 31 = interrupt number 31 ;
#define NVIC_IRQ32_I2C1_Enable  	    (NVIC_ISER1 |= 1<<0)	//bit number 0 = interrupt number 32 ; 32-32
#define NVIC_IRQ33_I2C2_Enable  	    (NVIC_ISER0 |= 1<<1)	//bit number 1 = interrupt number 33 ; 33-32
#define NVIC_IRQ34_I2C2_Enable  	    (NVIC_ISER1 |= 1<<2)	//bit number 2 = interrupt number 34 ; 34-32



//Interrupt clear-enable registers For SPI (NVIC_ICERx)
#define NVIC_IRQ31_I2C1_Disable  	    (NVIC_ICER0 |= 1<<31)	//bit number 3 = interrupt number 31 ;
#define NVIC_IRQ32_I2C1_Disable  	    (NVIC_ICER1 |= 1<<0)	//bit number 0 = interrupt number 32 ;
#define NVIC_IRQ33_I2C2_Disable  	    (NVIC_ICER1 |= 1<<1)	//bit number 1 = interrupt number 33 ;
#define NVIC_IRQ34_I2C2_Disable  	    (NVIC_ICER1 |= 1<<2)	//bit number 2 = interrupt number 34 ;





/********************************************************/
/********************************************************/
/********************************************************/
/*******************  Bit definition  ********************/
/********************************************************/
/********************************************************/



/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */


#endif /* STM32F103X6_H_ */

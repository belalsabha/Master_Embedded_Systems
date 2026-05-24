/*
 * SPI.h
 *
 *  Created on: Dec 30, 2025
 *      Author:  Belal Hani Sabha
 */


#ifndef MCAL_SPI_DRIVER_SPI_H_
#define MCAL_SPI_DRIVER_SPI_H_

//----------------------------------
//Includes
//----------------------------------
#include "stm32f103x6.h"
#include "GPIO.h"
#include "RCC.h"

//----------------------------------
// (structures)
//----------------------------------
struct IRQ_SRC{

	uint8_t  TXE: 1		;  // TX Buffer Empty IRQ
	uint8_t  RXNE:1		;  // RX Buffer Empty IRQ
	uint8_t  ERRIE : 1		;  // ERROR   IRQ
	uint8_t  RESERVED:5 ;  // RESERVED
};

//----------------------------------
//User type definitions (structures)
//----------------------------------

//Configuration structure For User inputs
typedef struct{

	uint16_t      Device_Mode 		    ;	// Specifies the SPI operating mode.
											// This parameter must be set based on @ref Device_Mode_define

	uint16_t      Communication_Mode    ;	// Specifies the SPI bidirectional mode state.
											// This parameter must be set based on @ref Communication_Mode_define

	uint16_t	  Frame_Format			;   //Specifies LSB or MSB
											//@ref Frame_Format_define

	uint16_t 	  DataSize  		    ;   //Specifies the size of the data frame
									 		//@ref DataSize_define

	uint16_t      ClockPolarity   		;	//Specifies the clock polarity
											//@ref ClockPolarity _define

	uint16_t      ClockPhase   		   ;	//Specifies the clock phase
											//@ref ClockPhase _define

	uint16_t      NSS   		       ;	//Specifies whether the NSS signal is managed by hardware (NSS pin) or by software using the SSI bit enable.
											//@ref NSS_define

	uint16_t      SPIClockSpeed    	   ;    //Specifies the Baud Rate prescaler value which will be used to  configure the transmit and receive SCK clock
											//@ref SPIClockSpeed_define

	uint16_t      IRQ_Enable	 	   ; 	//Specifies whether the TXEIE, RXNEIE, or ERRIE interrupts are IRQ_Enable enabled
											//@ref SPI_IRQ_Enable_define

	void 		  (*Ptr_ISR_Func)(struct IRQ_SRC   IRQ_Source);	//Set the C Function() which will be called once the IRQ  Happen

}SPI_Config_t;


// * =======================================================================================
/*===================================Reference Macros=======++++++=========================*/
// * =======================================================================================

//@ref Device_Mode_define
/*
 * Bit 2 MSTR: Master selection
	0: Slave configuration
	1: Master configuration */

#define SPI_Master_Mode       (1 << 2)
#define SPI_Slave_Mode        0


//@ref Communication_Mode_define
// if we need 2 lines
/*Bit 15 BIDIMODE: Bidirectional data mode enable
           0: 2-line unidirectional data mode selected

   Select :Bit 10 RXONLY: Receive only
   	   	   0: Full duplex     (Transmit and receive)
		   1: Output disabled (Receive-only mode)     */
#define SPI_DIRECTION_2LINES                  0           				// 2-line  , Full duplex
#define SPI_DIRECTION_2LINES_RXONLY			  (1 << 10)	  				// 2-line  , Receive-only mode

// if we need 1 lines
/*Bit 15 BIDIMODE: Bidirectional data mode enable
           1: 1-line bidirectional data mode selected

   Select :Bit 14 BIDIOE: Output enable in bidirectional mode
			 0: Output disabled (receive-only mode)
			 1: Output enabled (transmit-only mode)    */
#define SPI_DIRECTION_1LINE_receive_only     (1 << 15) 					 // 1 Line , Receive-only mode
#define SPI_DIRECTION_1LINE_transmit_only	 ((1 << 15) | (1 << 14))	 // 1 Line , Transmit-only mode



//@ref Frame_Format_define
/*Bit 7 LSBFIRST: Frame format
0: MSB transmitted first
1: LSB transmitted first  */
#define   LSB_First     (1 << 7)
#define   MSB_First     (0)




//@ref DataSize_define
/*Bit 11 DFF: Data frame format
0: 8-bit data frame format is selected for transmission/reception
1: 16-bit data frame format is selected for transmission/reception   */
#define   DataFrameFormat_8Bit     (0)
#define   DataFrameFormat_16Bit    (1 << 11)



////@ref ClockPolarity _define
/*Bit1 CPOL: Clock polarity
0: CK to 0 when idle
1: CK to 1 when idle   */
#define   ClkPolartitIdle_LOW     (0)
#define   ClkPolartitIdle_HIGH    (1 << 1)


//@ref ClockPhase _define
/*Bit 0 CPHA: Clock phase
0: The first clock transition is the first data capture edge
1: The second clock transition is the first data capture edge
*/
#define FirstClockTransition_isTheFirstDataCaptureEdge     (0)
#define SecondClockTransition_isTheFirstDataCaptureEdge	   (1 << 0)


////@ref NSS_define
// HardWare  >> Bit 9 SSM: Software slave management >> 0: Software slave management disabled
#define SPI_NSS_Hard_Slave        (0)

/*Bit 2 SSOE: SS output enable
0: SS output is disabled in master mode and the cell can work in multi master configuration
1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work  in a multi master environment. */
#define SPI_NSS_Hard_Master_SS_output_enable     (1 << 2)
#define SPI_NSS_Hard_Master_SS_output_disable	 ~(1 << 2)

//SoftWare  >> 1: Software slave management enabled
//Bit 8 SSI: Internal slave select : This bit has an effect only when the SSM bit is set.
#define SPI_NSS_Soft_NSSInternalSoft_Reset       (1 << 9)
#define SPI_NSS_Soft_NSSInternalSoft_Set		 ((1 << 9) | (1 << 8))



//@ref SPIClockSpeed_define
/*Bits 5:3  BR[2:0]: Baud rate control
000: fPCLK/2
001: fPCLK/4
010: fPCLK/8
011: fPCLK/16
100: fPCLK/32
101: fPCLK/64
110: fPCLK/128
111: fPCLK/256*/
#define SPI_BAUDRATEPRESCALER_2			(0)
#define SPI_BAUDRATEPRESCALER_4			( 1 << 3)
#define SPI_BAUDRATEPRESCALER_8			( 2 << 3)
#define SPI_BAUDRATEPRESCALER_16		( 3 << 3)
#define SPI_BAUDRATEPRESCALER_32		( 4 << 3)
#define SPI_BAUDRATEPRESCALER_64		( 5 << 3)
#define SPI_BAUDRATEPRESCALER_128		( 6 << 3)
#define SPI_BAUDRATEPRESCALER_256		( 7 << 3)



//@ref SPI_IRQ_Enable_define
#define SPI_IRQ_Enable_Disabled        (0)
#define SPI_IRQ_Enable_TXEIE		   (1<<7) //Bit 7 TXEIE: Tx buffer empty interrupt enable >> 1 = Set
#define SPI_IRQ_Enable_RXNEIE		   (1<<6) //Bit 6 RXNEIE: RX buffer not empty interrupt enable >> 1 = Set
#define SPI_IRQ_Enable_ERRIE		   (1<<5) //Bit 5 ERRIE: Error interrupt enable   >> 1 = Set





/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */

// Enable | Disable PollingMechanism
#define PollingMechanism_EN         1
#define PollingMechanism_Dis        0



/*
 * =======================================================================================
 * 							APIs Supported by "MCAL SPI DRIVER"
 * =======================================================================================
 */
void MCAL_SPI_Init(SPI_t *SPIx , SPI_Config_t  *SPI_Config);
void MCAL_SPI_DeInit(SPI_t *SPIx );

void MCAL_SPI_SendData(SPI_t *SPIx , uint16_t *pTxBuff ,uint8_t PollingEn);
void MCAL_SPI_ReceiveData(SPI_t *SPIx , uint16_t *pTxBuff ,uint8_t PollingEn);

void MCAL_SPI_GPIO_Set_Pins(SPI_t *SPIx );

void MCAL_SPI_TX_RX(SPI_t *SPIx , uint16_t *pTxBuff ,uint8_t PollingEn);





#endif /* MCAL_SPI_DRIVER_SPI_H_ */

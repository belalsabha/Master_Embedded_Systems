/*
 * ADC.h
 *
 * Created: 15 / 1 /2026
 * Author : Belal Hani Sabha
 */


#ifndef ADC_H_
#define ADC_H_

//----------------------------------
//Includes
//----------------------------------
#include "Atmega32.h"



//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//----------------------------------
//User type definitions (structures)
//----------------------------------
//Configuration structure For User inputs
typedef struct {
	
	uint8_t Vref;        //Select Voltage for ADC 
							// This value must be chosen from @ref Vref_SELECT_DEFINE

	
	uint8_t  conversion_time;	//Select conversion time for ADC
									// This value must be chosen from @ref  conversion_time_SELECT_DEFIN
									
	uint8_t   Channel;				//Select Channel 
										/// This value must be chosen from @ref Channel_SELECT_DEFIN								
									
									
		uint8_t       IRQ_Enable	 	   ; 		//enable or disable ADC IRQ
															//@ref ADC_IRQ_Enable_define 


		void 		  (*Ptr_ISR_Func)(void);	//Set the C Function() which will be called once the IRQ  Happen									
									
										
	}ADC_Config_t;



//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//----------------------------------
//Macros Configuration References
//----------------------------------
//@ref Vref_SELECT_DEFINE
#define AREF_InternalVref_turned_off			0
#define AVCCwithExternalCapacitorAtAREFPin    (1<<6)
#define InternalVoltageReference			  ( 1<<6   | 1<<7 )


//@ref  conversion_time_SELECT_DEFIN
//ADPS2		ADPS1		ADPS0		Division Factor
// 0		0			0				2
//0			0			1				2
//0			1			0				4
//0			1			1				8
//1			0			0				16
//1			0			1				32
//1			1			0				64
//1			1			1				128

#define DivisionFactor_2            0
#define DivisionFactor_4            2
#define DivisionFactor_8            3
#define DivisionFactor_16           4
#define DivisionFactor_32           5
#define DivisionFactor_64           6
#define DivisionFactor_128          7



//@ref ADC_IRQ_Enable_define
//• Bit 3 – ADIE: ADC Interrupt Enable
#define ADC_IRQ_ENABLE    (1<<3)
#define ADC_IRQ_DISABLE   0



// @ref Channel_SELECT_DEFIN
#define ADC0			0
#define ADC1			1
#define ADC2			2
#define ADC3			3
#define ADC4			4
#define ADC5			5
#define ADC6			6
#define ADC7			7

//Macros
#define VRef	  5000
#define RES	      1024



void MCAL_ADC_Init(ADC_Config_t *ADC_Config);
void MCAL_ADC_DeInit(); 
uint16_t MCAL_ADC_Read();



#endif /* ADC_H_ */
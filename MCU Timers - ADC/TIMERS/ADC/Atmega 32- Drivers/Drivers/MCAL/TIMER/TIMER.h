/*
 * TIMER.h
 *
 * Created: 14 / 1 /2026
 * Author : Belal Hani Sabha
 */ 


#ifndef TIMER_H_
#define TIMER_H_

//----------------------------------
//Includes
//----------------------------------
#include "Atmega32.h"
#include "IO.h"


//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef void(*P_VoidFunc_t)(void);
//----------------------------------
//User type definitions (structures)
//----------------------------------
//Configuration structure For User inputs
typedef struct
{
// Selects the operating mode of TIMER0
// Options: NORMAL, CTC (Clear Timer on Compare Match), FAST PWM, PHASE CORRECT PWM
// This value must be chosen from @ref TIMER_MODE_DEFINE
		uint8_t Timer_Mode;


// Selects the clock source for TIMER0
// Options: INTERNAL clock or EXTERNAL clock source
// This value must be chosen from @ref TIMER_CLK_SELECT_DEFINE
		uint8_t Timer_ClockSource;


// Configures TIMER0 interrupt behavior
// Options: INTERRUPT_DISABLE, ENABLE_COMPARE_MATCH_INTERRUPT, ENABLE_OVERFLOW_INTERRUPT
// This value must be chosen from @ref TIMER_INTERRUPT_DEFINE
		uint8_t Timer_InterruptConfig;
	

}TIMER_Config_t;



//-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//----------------------------------
//Macros Configuration References
//----------------------------------

//@ref TIMER_MODE_DEFINE
// Normal Mode: WGM01=0, WGM00=0
#define TIMER0_MODE_NORMAL            (0 << 3 | 0 << 6)

// PWM, Phase Correct Mode: WGM01=0, WGM00=1
#define TIMER0_MODE_PHASE_CORRECT_PWM (0 << 3 | 1 << 6)

// CTC Mode: WGM01=1, WGM00=0
#define TIMER0_MODE_CTC               (1 << 3 | 0 << 6)

// Fast PWM Mode: WGM01=1, WGM00=1
#define TIMER0_MODE_FAST_PWM          (1 << 3 | 1 << 6)


//@ref TIMER_CLK_SELECT_DEFINE
// No clock source (Timer/Counter stopped)
#define TIMER0_CLK_NO_CLOCK       0   // CS02=0, CS01=0, CS00=0

// System clock, no prescaling
#define TIMER0_CLK_IO_NO_PRESCAL  1   // CS02=0, CS01=0, CS00=1

// System clock divided by 8
#define TIMER0_CLK_IO_DIV8        2   // CS02=0, CS01=1, CS00=0

// System clock divided by 64
#define TIMER0_CLK_IO_DIV64       3   // CS02=0, CS01=1, CS00=1

// System clock divided by 256
#define TIMER0_CLK_IO_DIV256      4   // CS02=1, CS01=0, CS00=0

// System clock divided by 1024
#define TIMER0_CLK_IO_DIV1024     5   // CS02=1, CS01=0, CS00=1

// External clock on T0 pin, falling edge
#define TIMER0_CLK_EXTERNAL_FALL  6   // CS02=1, CS01=1, CS00=0

// External clock on T0 pin, rising edge
#define TIMER0_CLK_EXTERNAL_RISE  7   // CS02=1, CS01=1, CS00=1




// @ref TIMER_INTERRUPT_DEFINE
// No interrupt enabled
#define TIMER0_INTERRUPT_DISABLE         0   // OCIE0=0, TOIE0=0

// Enable Timer0 Output Compare Match Interrupt
#define TIMER0_INTERRUPT_OC_COMPARE      1   // OCIE0=1, TOIE0=0

// Enable Timer0 Overflow Interrupt
#define TIMER0_INTERRUPT_OVERFLOW        2   // OCIE0=0, TOIE0=1




/*
 * =======================================================================================
 * 							APIs Supported by "MCAL SPI DRIVER"
 * =======================================================================================
 */

void MCAL_TIMER0_Init( TIMER_Config_t *timerConfig);
void MCAL_TIMER0_DeInit(TIMER0_t *Timerx);

void MCAL_TIMER0_GetCompareValue(uint8_t *compareValue);
void MCAL_TIMER0_SetCompareValue(uint8_t compareValue);

void MCAL_TIMER0_GetCounterValue(uint8_t *counterValue);
void MCAL_TIMER0_SetCounterValue(uint8_t counterValue);

void MCAL_TIMER0_GetOverflowValue(uint8_t *overflowValue);
void MCAL_TIMER0_SetOverflowValue(uint8_t overflowValue);

void MCAL_TIMER0_SetPWMDutyCycle(uint8_t dutyCycle);

void MCAL_TIMER0_SetCallbackOverflowInterrupt(P_VoidFunc_t callback);
void MCAL_TIMER0_SetCallbackCompareMatchInterrupt(P_VoidFunc_t callback);





#endif /* TIMER_H_ */
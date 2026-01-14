/*
 * App.c - Timer0 CTC Example
 * Author: Belal Hani Sabha
 * Date: 14/01/2026
 */

#include "App.h"

/* ================= Global Variables ================= */
static uint8_t toggleStep = 0; 

/* ================= Callback Function ================= */
void Timer0_CM_Callback(void)
{
    // Toggle PORTA pins (example)
    IOA->PORT ^= 0xFF;
}

/* ================= Simple delay ================= */
void Delay_ms(uint16_t ms)
{
    volatile uint16_t i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1000; j++);
}

/* ================= App Initialization ================= */
void App_Init(void)
{
    /* Configure PORTA as output */
    IOA->DDR = 0xFF;
    IOA->PORT = 0x00;

    /* Enable global interrupts */
    SREG |= 1<<7;

    /* Set Timer0 Compare Match Callback */
   MCAL_TIMER0_SetCallbackCompareMatchInterrupt(Timer0_CM_Callback);

    /* Timer0 configuration */
    static TIMER_Config_t TIMER_config;

    TIMER_config.Timer_ClockSource           =TIMER0_CLK_IO_DIV1024; // Prescaler 1024
    TIMER_config.Timer_Mode          = TIMER0_MODE_CTC;               // CTC mode
    TIMER_config.Timer_InterruptConfig  = TIMER0_INTERRUPT_OC_COMPARE;       // Compare Match Interrupt enabled

    /* Set Compare Value for desired period */
    MCAL_TIMER0_SetCompareValue(0xFF);

    /* Initialize Timer0 */
    MCAL_TIMER0_Init(&TIMER_config);
}

/* ================= App Main Loop ================= */
void App_Run(void)
{
    while(1)
    {

        Delay_ms(500);
    }
}

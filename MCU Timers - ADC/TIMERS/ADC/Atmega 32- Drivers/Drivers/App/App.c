/*
 * App.c - ADC + LCD Example
 * Author: Belal Hani Sabha
 * Date: 14/01/2026
 */

#include "App.h"
#include <stdlib.h>

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
    ADC_Config_t ADC_Config;

    /* -------- ADC Configuration -------- */
    ADC_Config.Vref = AVCCwithExternalCapacitorAtAREFPin;   // AVCC as reference
    ADC_Config.conversion_time = DivisionFactor_64;         // Prescaler 64
    ADC_Config.IRQ_Enable = ADC_IRQ_DISABLE;                // Polling mode
    ADC_Config.Channel = ADC7;                              // PA7
    ADC_Config.Ptr_ISR_Func = NULL;

    MCAL_ADC_Init(&ADC_Config);

    /* -------- LCD Init-------- */
    LCD_Init();

    Control_LCD_Lines_And_Cursor(0, 0);
    Write_String_onLCD("ADC Value:");
}

/* ================= App Main Loop ================= */
void App_Run(void)
{


    adc_value = MCAL_ADC_Read();

    itoa(adc_value, buffer, 10);

    Control_LCD_Lines_And_Cursor(1, 0);
    Write_String_onLCD("     ");        
    Control_LCD_Lines_And_Cursor(1, 0);
    Write_String_onLCD(buffer);

    Delay_ms(500);
}

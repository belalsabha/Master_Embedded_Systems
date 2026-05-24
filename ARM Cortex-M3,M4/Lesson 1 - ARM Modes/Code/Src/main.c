/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Eng - Belal Hani Sabha
 * @brief          : Main program body
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "App.h"

volatile uint8_t IRQ_Flag = 0;


void IRQ9_Callback()
{
    IRQ_Flag = 1;
}

int main(void)
{
			//APP_Init();

    // enable clocks for GPIOA GPIOB AFIO
	RCC_AFIO_CLK_EN();
    RCC_GPIOA_CLK_EN();
    RCC_GPIOB_CLK_EN();


    EXTI_Configure_Pin_t EXTIx;
    EXTIx.EXTI_PIN = EXTI9PB9;
    EXTIx.EDGE_CASE = RISING_EDGE;
    EXTIx.IRQ_E_D = ENABLE_IRQ_EXTI;
    EXTIx.P_IRQ_FUNC_CALLBACK = &IRQ9_Callback;
    MCAL_EXTI_GPIO_Init(&EXTIx);
    while(1)
    {
    	// APP_Start();
    	 if(IRQ_Flag)
    	        {
    	            IRQ_Flag = 0;
    	        }
    }
}





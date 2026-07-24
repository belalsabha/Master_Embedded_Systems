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

//Lab1: create a function two switch  the privileged access level
enum CPU_AccessLeval{
	Privileged	,
	Unprivileged
};
void Switch_CPU_AccessLeval(enum CPU_AccessLeval Level){
    __asm("nop\n\t nop\n\t nop\n\t");
    if (Level == Privileged) {
    __asm("mrs r0		, control		\n\t"
          "bic r0		, r0	,	#1	\n\t" 	// Clear bit 0 for privileged thread mode or use shift right then shift left
          "msr control	, r0			\n\t"
           );
    } else {
    __asm("mrs r0		, control			\n\t"
          "orr r0		, r0		,#1		\n\t" 					// Set bit 0 for unprivileged
          "msr control	, r0				\n\t"
          );
}
}





void IRQ9_Callback()
{
	IRQ_Flag = 1;

  /*
	// LAB6-2 : Read the IPSR register and save the value in C variable
    // while CPU is in Handler Mode

    __asm("nop\n\t nop\n\t nop\n\t");

    __asm volatile (
        "MRS %0, IPSR"          // Read IPSR register into output variable (%0)
                                // IPSR = Interrupt Program Status Register

        : "=r"(IPSR_Register_Status)   // Output operand
                                       // "=" means write-only output
                                       // "r" compiler assigns a general-purpose register

        :                            // No input operands

        :                            // No clobbered registers
    );

    __asm("nop\n\t nop\n\t nop\n\t");

    */
}

int main(void)
{
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
	Switch_CPU_AccessLeval(Unprivileged);
	Switch_CPU_AccessLeval(Privileged);
	while(1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}
	}
}





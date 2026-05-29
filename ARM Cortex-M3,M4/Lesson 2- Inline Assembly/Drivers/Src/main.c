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

//uint32_t Testing_Val ;
//uint32_t sum = 1  , num1 = 2 , num2 = 4 ;
//uint32_t Control_Register_Status = 0 , IPSR_Register_Status = 0 ;


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



    // LAB 1: no input or output
    /*
    			__asm("nop\n\t nop\n\t nop\n\t");
     */

    // LAB 2: using output parameters
    /*
    __asm("nop\n\t nop\n\t nop\n\t");

    // Store immediate value 0xFF into Testing_Val using inline assembly
    __asm volatile (
        "mov %0, #0xFF"              // Move immediate value 0xFF into output operand
        : "=r"(Testing_Val)          // Output operand:
                                       // "=r" means:
                                       // - '=' : write-only output
                                       // - 'r' : compiler assigns a general-purpose register
                                       // %0 refers to Testing_Val mapped to a register
    );

    __asm("nop\n\t nop\n\t nop\n\t");

      */

       // LAB 3: using input parameters
/*
  __asm("nop\n\t nop\n\t nop\n\t");

  // Store the value of Testing_Val into register R0 using inline assembly
  __asm volatile (
      "mov R0, %0"        // Move the value of Testing_Val into R0
      // %0 refers to the first input operand (Testing_Val)

      :                   // Output operands (none used here)

      : "r"(Testing_Val)  // Input operand
        // "r" means the compiler places Testing_Val in a general purpose register & passes it to the assembly instruction

  );

  __asm("nop\n\t nop\n\t nop\n\t");


*/

	/*
  // LAB 4: using input and output parameters

  __asm("nop\n\t nop\n\t nop\n\t");

  // Add num1 and num2 and store result in sum using inline assembly
  __asm volatile (
      "add %0, %1, %2"        // %0 = destination (output)
                              // %1 = first input (num1)
                              // %2 = second input (num2)

      : "=r"(sum)             // Output operand
                              // "=" means write-only output
                              // "r" means compiler assigns a general-purpose register

      : "r"(num1), "r"(num2)  // Input operands
                              // both values placed in CPU registers



  );

  __asm("nop\n\t nop\n\t nop\n\t");

*/
/*
    // LAB 5: reserving registers (preventing compiler from using specific CPU registers)
  // Add num1 and num2 and store result in sum using inline assembly
  __asm("nop\n\t nop\n\t nop\n\t");

  __asm volatile (
      "add %0, %1, %2"        // %0 = destination (output)
                              // %1 = num1
                              // %2 = num2

      : "=r"(sum)             // Output operand
                              // "=" means write-only output
                              // "r" compiler assigns a general-purpose register

      : "r"(num1), "r"(num2)  // Input operands

      : "r0"                  // Clobber list: indicates R0 is reserved/modified
  );

  __asm("nop\n\t nop\n\t nop\n\t");

*/

  /*
  // LAB6
  // LAB6-1 : Read the Control register and save the value in C variable
  // while CPU is in Thread Mode
  __asm("nop\n\t nop\n\t nop\n\t");

  __asm volatile (
      "MRS %0, CONTROL"       // Read CONTROL register into output variable (%0)

      : "=r"(Control_Register_Status)         // Output operand
                                                // "=" means write-only output
                                                 // "r" compiler assigns a general-purpose register

      :                               // No input operands

      :                               // No clobbered registers
  );

  __asm("nop\n\t nop\n\t nop\n\t");



 */

	while(1)
	{
		// APP_Start();
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}
	}
}





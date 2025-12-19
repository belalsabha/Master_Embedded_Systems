/*
 * EXTI.c
 *
 * Created: 18 / 12 /2025
 * Author : Belal Hani Sabha
 */


#include "EXTI.h"
#include "IO.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */

void (*GP_IRQ_FUNC_CALLBACK [3])(void);

void Update_EXTI(EXTI_Configure_Pin_t* cfg) {
    // Configure pin as input with pull-up
    IO_Configure_Pin_t pin_cfg = {cfg->EXTI_PIN.IO_PIN, input_with_pull_up};
    MCAL_IO_Init(cfg->EXTI_PIN.IO_PORT, &pin_cfg);

   
    switch(cfg->EXTI_PIN.VectorNo) {
        case INT0_INDEX:
            EXTI->MCUCR &= ~((1<<0)|(1<<1));  // clear bit 0 bit 1 
            if(cfg->EDGE_CASE == RISING_EDGE)
                EXTI->MCUCR |= (1<<0)|(1<<1);
            else if(cfg->EDGE_CASE == FALLING_EDGE)
                EXTI->MCUCR |= (1<<1);
            else if(cfg->EDGE_CASE == Any_logical_Change)
                EXTI->MCUCR |= (1<<0);
            else if(cfg->EDGE_CASE == LOW_LEVEL)
                EXTI->MCUCR &= ~((1<<0)|(1<<1));

            if(cfg->IRQ_E_D)
                EXTI->GICR |= (1<<6); // Enable INT0
            else
                EXTI->GICR &= ~(1<<6);
            break;

        case INT1_INDEX:
            EXTI->MCUCR &= ~((1<<2)|(1<<3));  // clear bit2 bit 3
            if(cfg->EDGE_CASE == RISING_EDGE)
                EXTI->MCUCR |= (1<<2)|(1<<3);
            else if(cfg->EDGE_CASE == FALLING_EDGE)
                EXTI->MCUCR |= (1<<3);
            else if(cfg->EDGE_CASE == Any_logical_Change)
                EXTI->MCUCR |= (1<<2);
            else if(cfg->EDGE_CASE == LOW_LEVEL)
                EXTI->MCUCR &= ~((1<<2)|(1<<3));

            if(cfg->IRQ_E_D)
                EXTI->GICR |= (1<<7); // Enable INT1
            else
                EXTI->GICR &= ~(1<<7);
            break;

        case INT2_INDEX:
            if(cfg->EDGE_CASE == RISING_EDGE)
                EXTI->MCUCSR |= (1<<6);
            else
                EXTI->MCUCSR &= ~(1<<6);

            if(cfg->IRQ_E_D)
                EXTI->GICR |= (1<<5); // Enable INT2
            else
                EXTI->GICR &= ~(1<<5);
            break;
    }

    // Register callback
    GP_IRQ_FUNC_CALLBACK[cfg->EXTI_PIN.VectorNo] = cfg->P_IRQ_FUNC_CALLBACK;
}



			 

		
	


/*
 * =======================================================================================
 * 							APIs Functions Definitions
 * =======================================================================================
 */

/**================================================================
 * @Fn					-MCAL_EXTI_IO_Init
 * @brief 				-Initializes the EXTI from a specific IO pin
 * @param [in]   		-EXTI_Config set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 				-none
 * Note					-none
 */

void MCAL_EXTI_IO_Init (EXTI_Configure_Pin_t* EXTI_Config){

	Update_EXTI(EXTI_Config);
}




/**================================================================
 * @Fn					-MCAL_EXTI_IO_DeInit
 * @brief 				-Resets all EXTI registers to their default values 
 * @retval 				-none
 * Note					-none
 */
void MCAL_EXTI_IO_DeInit(void)
{
	EXTI->GICR   = 0x00;
	EXTI->GIFR   = 0x00;
	EXTI->MCUCR  = 0x00;
	EXTI->MCUCSR = 0x00;
}



/**================================================================
 * @Fn					-MCAL_EXTI_IO_Update
 * @brief 				-Updates the EXTI from a specific IO pin
 * @param [in]   		-EXTI_Config set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 				-none
 * Note					-none
 */

void MCAL_EXTI_IO_Update (EXTI_Configure_Pin_t* EXTI_Config){

	Update_EXTI(EXTI_Config);
}


// ISRs
// ISRs
void __vector_1(void) __attribute__((signal, used)); // INT0
void __vector_1(void) {
	
	 /*if (GP_IRQ_FUNC_CALLBACK[0])*/
	  GP_IRQ_FUNC_CALLBACK[0](); 
	 }

void __vector_2(void) __attribute__((signal, used)); // INT1
void __vector_2(void) { 
	/*if (GP_IRQ_FUNC_CALLBACK[1])*/
	 GP_IRQ_FUNC_CALLBACK[1](); 
	}

void __vector_3(void) __attribute__((signal, used)); // INT2
void __vector_3(void) { 
	/*if (GP_IRQ_FUNC_CALLBACK[2])*/
	 GP_IRQ_FUNC_CALLBACK[2](); 
	}
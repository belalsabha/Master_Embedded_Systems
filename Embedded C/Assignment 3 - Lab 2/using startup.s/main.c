/* 
 * @file      main.c
 * @author    Eng - Belal Hani Abu Sabha
 * @brief     toggle led  connected to pin PA13 on ARM Cortex-M3
 * @Created on  Sep 22, 2025   
 */


// Create a typedef for volatile unsigned 32-bit integer
// volatile tells compiler this value may change outside program execution (in hardware) 

typedef volatile unsigned int vuint32_t;

// Define register addresses for Reset and Clock Control  peripheral
#define RCC_BASE 0x40021000   //Base address of RCC peripheral
#define RCC_APB2ENR_REG  *(vuint32_t*)(RCC_BASE+0x18) // APB2 peripheral clock enable register

// Define register addresses for GPIO Port A peripheral

#define GPIO_PORTA_BASE 0x40010800 // Base address of GPIO Port A
#define GPIO_PORTA_CRH_REG *(vuint32_t*)(GPIO_PORTA_BASE+0x04)
#define GPIO_PORTA_ODR_REG *(vuint32_t*)(GPIO_PORTA_BASE+0x0C)  // Output data register

#define RCC_IO_PORTA_ENABLE (1<<2) //assign 1 to bit number 2
#define GPIO_PORT_A13 (1<<13) //assign 1 to bit number 13

// delay func 
void delay(void);

/*    -----------------------------another solution to W/R on PortA13 using union and structure bit field-------------------------------------------------------------

// Create a union typedef for accessing each bits of  ODR register

typedef union{
    vuint32_t _32_bits; // ensure we can access all 32 bits 
    struct  // struct bit filed to access every bit 
    {
        vuint32_t reserved:13; //reserved bit 0 to bit 12  
        vuint32_t PIN_no_13:1;  //  bit 13 control output  state 
    }Spin;
}U_ODR;


// Create a pointer to the ODR register 

volatile U_ODR* Ptr_ODR = (volatile U_ODR*)(GPIO_PORTA_BASE+0x0C);

--------------------------------------------------------------------------------------------------------------------------------
 */
int main(void)
{
    RCC_APB2ENR_REG |=RCC_IO_PORTA_ENABLE; // OR with 0000 0000 0000 0010 (assign 1 to bit 2)

    // Configure PortA13 as output
    GPIO_PORTA_CRH_REG &=0xFF0FFFFF; // Clear bits 20-23 
    GPIO_PORTA_CRH_REG |=0x00200000 ;// assign 1 to  bits to bit 21

    // infinite loop
    while(1){
        // Ptr_ODR ->Spin.PIN_no_13=1; // OUTPUT =1 , led is on until end of loop 

        GPIO_PORTA_ODR_REG |= GPIO_PORT_A13; // OUTPUT =1 , led is on until end of loop 
        delay(); // call delay func
        //Ptr_ODR ->Spin.PIN_no_13=0; // OUTPUT =0 , led is off until end of loop

        GPIO_PORTA_ODR_REG &= ~GPIO_PORT_A13; // OUTPUT =0 , led is off until end of loop
        delay(); // call delay func

    }
    return 0;
}

//  delay function
void delay(void) {
    for(vuint32_t i = 0; i < 5000; i++);
}





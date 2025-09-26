/* 
 * @file      main.c
 * @author    Eng - Belal Hani Abu Sabha
 * @brief     toggle led - This program toggles an LED connected to pin PA13 on an ARM Cortex-M3
 * @Created on  Sep 23, 2025   
 */

// Create a typedef for volatile unsigned 32-bit integer
// volatile tells compiler this value may change outside program execution (in hardware) 
typedef volatile unsigned int vuint32_t;
typedef  unsigned int uint32_t;

// Define register addresses for Reset and Clock Control (RCC) peripheral
#define RCC_BASE 0x40021000   //Base address of RCC peripheral
#define RCC_APB2ENR_REG  *(vuint32_t*)(RCC_BASE+0x18) // APB2 peripheral clock enable register

// Define register addresses for GPIO Port A peripheral

#define GPIO_PORTA_BASE 0x40010800 // Base address of GPIO Port A
#define GPIO_PORTA_CRH_REG *(vuint32_t*)(GPIO_PORTA_BASE+0x04)
#define GPIO_PORTA_ODR_REG *(vuint32_t*)(GPIO_PORTA_BASE+0x0C)  // Output data register

#define RCC_IO_PORTA_ENABLE (1<<2) //assign 1 to bit number 2
#define GPIO_PORT_A13 (1UL<<13) //assign 1 to bit number 13


uint32_t Global_Var[2] = {10,20};
uint32_t const Constant_Var [2] = {1,2};

// delay func 
void delay(void);


extern void Usage_fault_handler(void){

}
extern void MM_fault_handler(void){

}



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

//-------------------------------------------------------------------------------------------------------------------------------- */
 
int main(void)
{
    RCC_APB2ENR_REG |=RCC_IO_PORTA_ENABLE; // XOR with 0000 0000 0000 0010 (assign 1 to bit 2) to enable RCC Clock

    // Configure PortA13 as outpu
    GPIO_PORTA_CRH_REG &=0xFF0FFFFF; // Clear bits 20-23 
    GPIO_PORTA_CRH_REG |=0x00200000 ;// assign 1 to  bits to bit 21

    // infinite loop
    while(1){
    //   Ptr_ODR->Spin.PIN_no_13=1; // OUTPUT =1 , led is on until end of loop 

      GPIO_PORTA_ODR_REG |= GPIO_PORT_A13; // OUTPUT =1 , led is on until end of loop 
        delay(); // call delay func
      //  Ptr_ODR->Spin.PIN_no_13=0; // OUTPUT =0 , led is off until end of loop

   GPIO_PORTA_ODR_REG &= ~GPIO_PORT_A13; // OUTPUT =0 , led is off until end of loop
        delay(); // call delay func

    


    }
    return 0;
}

//  delay function
void delay(void) {
    for(vuint32_t i = 0; i < 500; i++);
}





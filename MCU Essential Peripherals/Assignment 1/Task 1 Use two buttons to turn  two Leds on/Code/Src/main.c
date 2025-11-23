/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Eng - Belal Hani Sabha
 * @brief          : Toggle led STM32f103C6 on bluePill kit Using GPIO
 ******************************************************************************
 */
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



typedef  unsigned int uint32_t;

// >>>>> GPIOA Register Addresses

#define GPIOA_BASE  0x40010800
#define GPIOA_CRL   *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH   *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR   *(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR   *(volatile uint32_t *)(GPIOA_BASE + 0x0C)


// >>>>> GPIOB Register Addresses
#define GPIOB_BASE  0x40010C00
#define GPIOB_CRL   *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH   *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR   *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR   *(volatile uint32_t *)(GPIOB_BASE + 0x0C)


//>>>>> RCC Register Addresses
#define RCC_BASE    0x40021000
#define RCC_APB2ENR  *(volatile uint32_t *)(RCC_BASE + 0x18)
#define Enable_portA  (1<<2)    // Bit 2 enables GPIOA clock
#define Enable_portB  (1<<3)    // Bit 3 enables GPIOB clock

void GPIOA_Init(){
	// Reset  registers  >>
	GPIOA_CRL=0;
	GPIOA_CRH=0;
	GPIOA_ODR=0;


	//  PortA Configuration as input floating
	// CNF = 01 >> floating input
	// MODE = 00 >> input mode


	GPIOA_CRL &= ~(0xF << 4);  // Clear PortA1  bits
	GPIOA_CRL |=  (0x4 << 4);  // Set PortA1 as floating (HZ) input

	//--------------------------------------------------------------

	GPIOA_CRH &= ~(0xF << 20); // Clear PortA13  bits
	GPIOA_CRH |=  (0x4 << 20); // Set PortA1 as floating (HZ) input

}

void GPIOB_Init(){
	// Reset  registers  >>
	GPIOB_CRL=0;
	GPIOB_CRH=0;
	GPIOB_ODR=0;

	// PortB Configuration  as  push-pull output with  2MHz
	// MODE = 10 >> output 2MHz
	// CNF  = 00 >> push-pull


	GPIOB_CRH &= ~(0xF << 20);  // Clear PortB13  bits
	GPIOB_CRH |=  (0x2 << 20);  // Set PortB13 as push-pull output with  2MHz

	//--------------------------------------------------------------


	GPIOB_CRL &= ~(0xF << 4);  // Clear PortB1  bits
	GPIOB_CRL |=  (0x2 << 4);  // Set PortB1 as push-pull output with  2MHz

}

void Clock_Init(){
	// enable clock for GPIOA
	RCC_APB2ENR |= Enable_portA;

	// enable clock for GPIOB
	RCC_APB2ENR |= Enable_portB;
}

void simple_delay(){
	for(int i=0; i<1000 ;i++);
}
int main(void) {
	Clock_Init();
	GPIOA_Init();
	GPIOB_Init();

	while (1) {

		//  PA1 >> Toggle PB1
		if ((GPIOA_IDR & (1 << 1)) == 0) {   // if button is pressed
			GPIOB_ODR ^= (1 << 1);           // led is on
			while ((GPIOA_IDR & (1 << 1)) == 0);   // wait until change button state
		}

		//PA13 >> Toggle PB13
		if ((GPIOA_IDR & (1 << 13)) != 0) {  // if button is pressed
			GPIOB_ODR ^= (1 << 13);          // led is on
		}

		simple_delay(); // delay
	}
}



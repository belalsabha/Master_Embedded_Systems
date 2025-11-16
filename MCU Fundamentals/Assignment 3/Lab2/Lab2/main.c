/*
 * main.c
 *
 * Created: 11/16/2025 10:23:46 PM
 *  Author: Belal
 */ 

#include <xc.h>

#include <avr/interrupt.h>
#include <util/delay.h>

/* if we dont want to use libraries 
// create typedef for Pointer
typedef volatile unsigned char uint8_t;

// Registers Addresses for Interrupts
#define SREG    (*(volatile uint8_t*)())
#define GICR    (*(volatile uint8_t*)(0x5B))
#define MCUCR   (*(volatile uint8_t*)(0x55))
#define MCUCSR  (*(volatile uint8_t*)(0x54))

//Registers Addresses for PortD
#define DDRD    (*(volatile uint8_t*)(0x31))
#define PORTD   (*(volatile uint8_t*)(0x32))
*/


void PORTD_OUTPUT_INIT(){
	// Enable Pins 5,6,7 as output
	DDRD |= (1<<5) | (1<<6) | (1<<7);
}
int main(void)
{
	// GLOBAL INTERRUPT ENABLE
	SREG |= (1 << 7);

	// Configure INT0 >>  any logical change
	MCUCR |= (1<<1);
	MCUCR &= ~(1<<0);

	// Configure INT1 >> rising edge
	MCUCR |= ((1<<2) | (1<<3));

	// Configure INT2 >> falling edge
	MCUCSR &= ~(1<<6);

	// Enable INT0, INT1, INT2
	GICR |= ((1<<5) | (1<<6) | (1<<7));

	// call function to define PORTD as OUTPUT
	PORTD_OUTPUT_INIT();

	while(1)
	{
		// ??Write 0 on  PORTD 5,6,7 (led is off)
		PORTD &= ~((1<<5) | (1<<6) | (1<<7));
		_delay_ms(1000);
	}
}

ISR(INT0_vect)
{
	PORTD |= (1<<5);
	_delay_ms(1000);
}

ISR(INT1_vect)
{
	PORTD |= (1<<6);
	_delay_ms(1000);
}

ISR(INT2_vect)
{
	PORTD |= (1<<7);
	_delay_ms(1000);
}

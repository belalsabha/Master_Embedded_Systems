/*
 * Created: 23/11/2025 10:49:25 
 * Author : Eng - Belal Hani Sabha 
 */ 

#include <util/delay.h>

typedef unsigned char uint8_t;

#define SET_BIT(ADDRESS,BIT)   ADDRESS |=  (1<<BIT)
#define RESET_BIT(ADDRESS,BIT) ADDRESS &= ~(1<<BIT)
#define TOGGLE_BIT(ADDRESS,BIT)  ADDRESS ^=  (1<<BIT)
#define READ_BIT(ADDRESS,BIT) ((ADDRESS) &   (1<<(BIT)))

#define PIND   (*(volatile uint8_t *)(0x30))
#define DDRD   (*(volatile uint8_t *)(0x31))
#define PORTD  (*(volatile uint8_t *)(0x32))





int main(void)
{
	
	RESET_BIT(DDRD,0); // input
	RESET_BIT(PORTD,0); // disable pull up 

	// LEDS PINS : OUTPUT
	SET_BIT(DDRD,5);
	SET_BIT(DDRD,6);
	SET_BIT(DDRD,7);

	RESET_BIT(PORTD,5);
	RESET_BIT(PORTD,6);
	RESET_BIT(PORTD,7);

	uint8_t count = 0;

	while (1)
	{
		
		if (READ_BIT(PIND,0) != 0)
		{
			count++;

			if (count == 1)
			{
				SET_BIT(PORTD,5);
			}
			else if (count == 2)
			{
				SET_BIT(PORTD,6);
			}
			else if (count == 3)
			{
				SET_BIT(PORTD,7);
				count = 0;     // reset 
			}

			
			_delay_ms(500);  
			 while (READ_BIT(PIND,0) != 0); // waiting until button is off
		}
	}
}



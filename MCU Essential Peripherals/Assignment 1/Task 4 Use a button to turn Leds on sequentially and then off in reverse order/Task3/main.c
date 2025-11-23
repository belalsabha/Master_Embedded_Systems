/*
 * Created: 23/11/2025 11:29:45 
 * Author : Eng - Belal Hani Sabha 
 */ 

#include <util/delay.h>

typedef unsigned char uint8_t;

#define SET_BIT(ADDRESS,BIT)     (ADDRESS |=  (1<<BIT))
#define RESET_BIT(ADDRESS,BIT)   (ADDRESS &= ~(1<<BIT))
#define READ_BIT(ADDRESS,BIT)    ((ADDRESS) &   (1<<BIT))

#define PIND   (*(volatile uint8_t *)(0x30))
#define DDRD   (*(volatile uint8_t *)(0x31))
#define PORTD  (*(volatile uint8_t *)(0x32))

int main(void)
{
	//  input with external pull down
	RESET_BIT(DDRD,0);
	RESET_BIT(PORTD,0);

	// LEDs  output
	SET_BIT(DDRD,5);
	SET_BIT(DDRD,6);
	SET_BIT(DDRD,7);

	// turn off all LEDs 
	RESET_BIT(PORTD,5);
	RESET_BIT(PORTD,6);
	RESET_BIT(PORTD,7);

	uint8_t count = 0;

	while(1)
	{
		// Check if button was pressed 
		if(READ_BIT(PIND,0) != 0)
		{
			count++;

			// turn on LEDs 
			if(count == 1) SET_BIT(PORTD,5);
			else if(count == 2) SET_BIT(PORTD,6);
			else if(count == 3) SET_BIT(PORTD,7);

			_delay_ms(300);
			while(READ_BIT(PIND,0) != 0);


			// if  LED3 is on then  start turning off sequence
			if(count == 3)
			{
				_delay_ms(500); 
				RESET_BIT(PORTD,7);  // LED3 off
				_delay_ms(500);
				RESET_BIT(PORTD,6);  // LED2 off
				_delay_ms(500);
				RESET_BIT(PORTD,5);  // LED1 off

				count = 0;           
			}


			_delay_ms(300);
			while(READ_BIT(PIND,0) != 0);

		}
	}
}


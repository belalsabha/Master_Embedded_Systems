/*
 * Created: 23/11/2025 10:29:28 
 * Author : Eng - Belal Hani Sabha 
 */ 

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
	RESET_BIT(PORTD,0); // pull up disabled 

	SET_BIT(DDRD,4); // output
	RESET_BIT(PORTD,4); // output low

	while (1) 
	{
		if(READ_BIT(PIND,0) != 0){
			SET_BIT(PORTD,4); // buzzer on
		}
		else                         
		{
			RESET_BIT(PORTD,4);      // buzzer off
		}
	}
}



/*
 * Atmega32.h
 *
 * Created: 14 / 12 /2025
 * Author : Belal Hani Sabha
 */ 







#ifndef ATMEGA32_H_
#define ATMEGA32_H_

typedef unsigned char uint8_t;

/*---------------------------------------------------*/
typedef struct {
    volatile uint8_t PIN;   // Input pins address
    volatile uint8_t DDR;   // Data Direction Register
    volatile uint8_t PORT;  // Output register
}IOx_t;

/*---------------------------------------------------*/
#define IOA (*(IOx_t *)0x39)  
#define IOB (*(IOx_t *)0x36)  
#define IOC (*(IOx_t *)0x33)  
#define IOD (*(IOx_t *)0x30)  
/*---------------------------------------------------*/

#define SFIOR (*(volatile uint8_t *)0x50)



#endif /* ATMEGA32_H_ */

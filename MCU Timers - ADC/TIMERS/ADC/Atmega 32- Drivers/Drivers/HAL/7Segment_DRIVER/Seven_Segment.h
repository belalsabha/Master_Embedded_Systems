/*
 * Seven_Segment.h
 * Created on: Dec 14, 2025
 * Author: Belal Hani Sabha
 */

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "IO.h"


	
	






	//====================================================================================
// For 7Segment
// Numbers in 7-segment (4-bit)   and connect to 7seg decoder
#define ZERO		0b0000 // 0
#define ONE			0b0001 // 1
#define TWO			0b0010 // 2
#define THREE		0b0011 // 3
#define FOUR		0b0100 // 4
#define FIVE		0b0101 // 5
#define SIX			0b0110 // 6
#define SEVEN	    0b0111 // 7
#define EIGHT	    0b1000 // 8
#define NINE        0b1001 // 9

//Data Lines (PORTC) for 7Seg Decode
#define		A		IO_PIN4
#define		B		IO_PIN5
#define		C		IO_PIN6
#define		D		IO_PIN7

// Enable pins
#define EN1     IO_PIN2
#define EN2     IO_PIN3



// APIs
void Init_7Segment(void);
void DisplayNumber_on_7Segment(uint8_t num);


#endif

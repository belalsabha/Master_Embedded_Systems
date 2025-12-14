/*
 * Seven_Segment.h
 * Created on: Dec 14, 2025
 * Author: Belal Hani Sabha
 */

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "IO.h"

//Data Lines (PORTC)
#define SEG_A   IO_PIN4
#define SEG_B   IO_PIN5
#define SEG_C   IO_PIN6
#define SEG_D   IO_PIN7

// Enable pins
#define EN1     IO_PIN2
#define EN2     IO_PIN3

// Decimal point
#define DP      IO_PIN0   // PORTB

// Numbers in 7-segment (4-bit)
extern  uint8_t SEG_7_NUM[10] ;


// APIs
void Init_7Segment(void);
void DisplayNumber_on_7Segment(uint8_t num);
void Enable_7Segment(uint8_t seg);

#endif

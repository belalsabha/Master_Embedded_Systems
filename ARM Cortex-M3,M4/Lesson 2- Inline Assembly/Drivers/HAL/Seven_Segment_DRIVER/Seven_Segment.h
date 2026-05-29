/*
 * Seven_Segment.h
 *
 *  Created on: Dec 12, 2025
 *  Author: Belal Hani Sabha
 */








#ifndef SEVEN_SEGMENT_DRIVER_SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_DRIVER_SEVEN_SEGMENT_H_



#include "stm32f103x6.h"

#include "GPIO.h"

//====================================================================================


// For 7Segment
#define ZERO 0x01
#define ONE 0x79
#define TWO 0x24
#define THREE 0x30
#define FOUR 0x4C
#define FIVE 0x12
#define SIX 0x02
#define SEVEN 0x19
#define EIGHT 0x00
#define NINE 0x10


//====================================================================================

void Init_7Segment();
void DisplayNumber_on_7segment(uint8_t num);




#endif /* SEVEN_SEGMENT_DRIVER_SEVEN_SEGMENT_H_ */

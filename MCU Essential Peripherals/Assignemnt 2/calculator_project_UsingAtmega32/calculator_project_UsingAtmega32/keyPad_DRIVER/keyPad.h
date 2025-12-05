/*
 * keyPad.h
 *
 * Created: 13/06/47 01:36:40 
 *  Author: Belal
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 8000000UL

#include<avr/io.h>
#include<util/delay.h>


#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define KEYPAD_DATA_PORT PORTD
#define KEYPAD_DATA_DIRECTION  DDRD
#define KeyPad_PIN PIND

void Keypad_Init();
uint8_t GetData_FromKeyPad();

#endif /* KEYPAD_H_ */
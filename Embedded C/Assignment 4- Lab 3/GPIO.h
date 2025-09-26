#ifndef _GPIO_H
#define _GPIO_H

#include "platform_types.h"

#define Enable_Bit(Address,Bit_no)     Address |=  (1<<Bit_no) //  enable bit  , bit = 1
#define Disable_Bit(Address,Bit_no)    Address &= ~(1<<Bit_no) // disable bit , bit =0

// ---- System Control ----
#define SYSCTL_BASE          0x400FE000  //define System Control Adderss Module
#define SYSCTL_RCGC2_R      (*(volatile uint32_t*)(SYSCTL_BASE + 0x108))  // define System Control Adderss Register to Enable GPIO portF 

// ---- GPIOF ----
#define GPIO_PORTF_BASE      0x40025000UL   //define GPIO PortF
#define GPIO_PORTF_DIR_R    (*(volatile uint32_t*)(GPIO_PORTF_BASE + 0x400))  // Set  PortF as output 
#define GPIO_PORTF_DEN_R    (*(volatile uint32_t*)(GPIO_PORTF_BASE + 0x51C))  // Enable GPIO Pin
#define GPIO_PORTF_DATA_R   (*(volatile uint32_t*)(GPIO_PORTF_BASE + 0x3FC))  // W/R on Pin

void delay(int time);   // prototyping for delay function
void GPIO_PortF_Init(void);   // prototyping for initialization function

#endif
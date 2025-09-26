#include "GPIO.h"

void main(void){
	  volatile unsigned long dealy_time = 5000 ;     // delay time 
	  GPIO_PortF_Init ();  // calling GPIO_PortF_Init 



while(1){
	Enable_Bit(GPIO_PORTF_DATA_R,3);  // led is on 
	delay(dealy_time); // delay
	Disable_Bit(GPIO_PORTF_DATA_R,3);  // led is off
	delay(dealy_time);  //delay

}

}
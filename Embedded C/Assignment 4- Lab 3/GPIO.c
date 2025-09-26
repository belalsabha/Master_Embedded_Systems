#include "GPIO.h"

// define GPIO_PortF_Init () 
void GPIO_PortF_Init (){
        
Enable_Bit(SYSCTL_RCGC2_R,5);  // set bit 5 in SYSCTL_RCGC2_R
delay(500);  //calling  delay function 
Enable_Bit(GPIO_PORTF_DIR_R ,3);  // set bit 3 in GPIO_PORTF_DIR_R
Enable_Bit(GPIO_PORTF_DEN_R,3);   //set bit 3 in GPIO_PORTF_DEN_R
}

// define delay function 
void delay(int time){
for (int i = 0; i < time; ++i);

}
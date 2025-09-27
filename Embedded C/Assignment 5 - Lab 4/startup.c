#include "platform_types.h"




extern int main();
extern uint32_t End_Text;
extern uint32_t Start_Data;
extern uint32_t End_Data;
extern uint32_t Start_Bss;
extern uint32_t End_Bss;
extern uint32_t End_Heap;
extern uint32_t Stack_Top;

void reset_handler();
void deafult_handler();
void NMI_handler()                       __attribute__ ((weak, alias("deafult_handler")));;
void H_fault_handler()                   __attribute__ ((weak, alias("deafult_handler")));;
void MM_fault_handler()                  __attribute__ ((weak, alias("deafult_handler")));;
void Bus_fault_()                        __attribute__ ((weak, alias("deafult_handler")));;
void Usage_fault_handler()               __attribute__ ((weak, alias("deafult_handler")));;


uint32_t vectors[]  __attribute__ ((section(".vectors"))) ={
(uint32_t)&Stack_Top,
(uint32_t)&reset_handler, 
(uint32_t)&deafult_handler,
(uint32_t)&NMI_handler,
(uint32_t)&H_fault_handler,
(uint32_t)&MM_fault_handler,
(uint32_t)&Bus_fault_,
(uint32_t)&Usage_fault_handler,
}; 





void reset_handler(){
uint32_t data_size = (uint8_t*) &End_Data - (uint8_t*) &Start_Data ;
uint8_t *src = (uint8_t*) &End_Text;
uint8_t *des = (uint8_t*) &Start_Data;

for (int i = 0; i < data_size; ++i)
{
	*((uint8_t*) des++) = *((uint8_t*) src++) ; 
}

uint32_t bss_size = (uint8_t*) &End_Bss - (uint8_t*) &Start_Bss ;
des = (uint8_t*)&Start_Bss;
for (int i = 0; i < data_size; ++i)
{
	*((uint8_t*) des++) = (uint8_t)0 ; 
}
main();

}

void deafult_handler(){
reset_handler();
}




/* 
 * @file      startup.c
 * Created on: 31 Oct 2025
 *  Author: Belal
 */  
 
typedef unsigned int uint32_t ;
typedef unsigned char uint8_t;

#define Start_Stack_SP 0x20001000

extern int main(void);
void reset_handler(void);
void deafult_handler(void);
void NMI_handler(void)                       __attribute__ ((weak, alias("deafult_handler")));;
void H_fault_handler(void)                   __attribute__ ((weak, alias("deafult_handler")));;
void MM_fault_handler(void)                  __attribute__ ((weak, alias("deafult_handler")));;
void Bus_fault_(void)                        __attribute__ ((weak, alias("deafult_handler")));;
void Usage_fault_handler(void)               __attribute__ ((weak, alias("deafult_handler")));;

uint32_t vectors[]  __attribute__ ((section(".vectors"))) ={
Start_Stack_SP,
(uint32_t)&reset_handler, 
(uint32_t)&deafult_handler,
(uint32_t)&NMI_handler,
(uint32_t)&H_fault_handler,
(uint32_t)&MM_fault_handler,
(uint32_t)&Bus_fault_,
(uint32_t)&Usage_fault_handler,
};

extern uint32_t End_Text ;
extern uint32_t Start_Data;
extern uint32_t End_Data;
extern uint32_t Start_Bss;
extern uint32_t End_Bss;
extern uint32_t Stack_Top;

void reset_handler(void){
	// copying data from flash to sram
	uint32_t Data_Size  = (uint8_t*)&End_Data - (uint8_t*)&Start_Data;
	uint8_t *Src = (uint8_t*)&End_Text;
	uint8_t *Des = (uint8_t*)&Start_Data;
	for (int i = 0; i < Data_Size; ++i)
	{
		*((uint8_t*)Des++) = *((uint8_t*)Src++);
	

	// create .bss section and init with zero
    uint32_t Bss_Size  = (uint8_t*)&End_Bss - (uint8_t*)&Start_Bss;

	Des = (uint8_t*)&Start_Bss;
	for (int i = 0; i < Bss_Size; ++i)
	{
        *Des++ = 0;   
	}


// go to main in main.c file
main();
}
}

void deafult_handler(void){
reset_handler();
}
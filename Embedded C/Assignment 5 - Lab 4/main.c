#include<stdlib.h>
#include "platform_types.h"



extern uint32_t End_Bss;
extern uint32_t End_Heap;

void* _sbrk(int incr) {
    static uint8_t* heap_ptr = NULL;
    uint8_t* pre_heap_ptr;

    if (heap_ptr == NULL)
        heap_ptr = (uint8_t*)&End_Bss;

    pre_heap_ptr = heap_ptr;

    if (heap_ptr + incr > (uint8_t*)&End_Heap)
        return (void*)-1;   // return -1 (not NULL) to indicate failure

    heap_ptr += incr;
    return (void*)pre_heap_ptr;
}


int main(int argc, char const *argv[])
{
	int *ptr = (int*)malloc(10);
	free(ptr);
	return 0;
}




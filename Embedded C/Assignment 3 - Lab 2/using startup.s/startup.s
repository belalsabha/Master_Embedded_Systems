/* 
 * @file      startup.s
 * @author    Eng - Belal Hani Abu Sabha
 * @Created on  Sep 22, 2025   
 */


// telling assembller to create a section with name victors 
.section .vectors 

.word  0x20001000     // stack top address
.word _reset                           // Reset 
.word vector_handler                   //NMI  
.word vector_handler                   //Hard Fault
.word vector_handler                   //MM Fault
.word vector_handler                   //Bus Fault                  
.word vector_handler                   //Usage Fault 
.word vector_handler                   //Reserved 
.word vector_handler                   //Reserved 
.word vector_handler                   //Reserved
.word vector_handler                   //Reserved 
.word vector_handler                   //SV Call 
.word vector_handler                   //Debug Reserved 
.word vector_handler                   //Reserved
.word vector_handler                   //PendSv 
.word vector_handler                   //SysTick 
.word vector_handler                   //IRQ0
.word vector_handler                   //IRQ1
.word vector_handler                   //IRQ2
.word vector_handler                   //..... to IRQ67

.section .text
_reset:
bl main  // main function is called using branch
b .      // branch itself 

.thumb_func     //use 16 bits and  32 bits instruction if avilable

vector_handler:  // every time we called a vector we called _reset which  called main function again
b _reset      

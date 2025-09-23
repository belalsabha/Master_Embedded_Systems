/* 
 * @file      linker.ld
 * @author    Eng - Belal Hani Abu Sabha
 * @Created on  Sep 23, 2025   
 */

MEMORY
{
    flash(rx) : ORIGIN = 0x08000000, LENGTH = 128K
            sram(rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text : {
        *(.vectors*)
        *(.text*)
        *(.rodata*)
        End_Text = . ;
    }>flash

    .data : {
     Start_Data = . ;

        *(.data*)
      End_Data = .  ;
    }>sram AT>flash

    .bss : {
    Start_Bss = . ;
        *(.bss*)
        . = ALIGN(4) ;
        End_Bss = .;
        . = ALIGN(4) ;
    . = . + 0x1000;  ;
    Stack_Top = . ;
    }>sram
}

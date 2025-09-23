/* 
 * @file      linker.ld
 * @author    Eng - Belal Hani Abu Sabha
 * @Created on  Sep 22, 2025   
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
    }>flash

    .data : {
        *(.data*)
    }>sram AT>flash

    .bss : {
        *(.bss*)
    }>sram
}

MEMORY {
    flash (rx)  : ORIGIN = 0x00000000, LENGTH = 512M
    sram  (rwx) : ORIGIN = 0x20000000, LENGTH = 512M
}

SECTIONS {
    .text : {
        *(.vectors*)        /* Vector table */
        *(.text*)           /* Program code */
        *(.rodata*)         /* Read-only data */
        End_Text = .;       /* End of .text, used as copy source for .data */
    } > flash

    .data : {
        Start_Data = .;     /* Start of .data in SRAM */
        *(.data*)           /* Initialized global/static vars */
        . = ALIGN(4);
        End_Data = .;       /* End of .data */
    } > sram AT > flash

    .bss : {
        Start_Bss = .;      /* Start of .bss */
        *(.bss*)            /* Uninitialized vars */
        . = ALIGN(4);
        End_Bss = .;        /* End of .bss */
    } > sram
}

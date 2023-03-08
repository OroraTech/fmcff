/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

ENTRY(_start)

__dso_handle = 0;

__stack_end__ = ORIGIN(RAM) + LENGTH(RAM);


SECTIONS
{

    .isr_vector :
    {
        . = ALIGN(8);
        KEEP(*(.isr_vector));
        ASSERT(DEFINED(IRQ_TABLE), "IRQ_TABLE not defined");
        ASSERT(. > ORIGIN(FLASH) + 8, "empty isr_vector section");
    } > FLASH

    /* used for "pre-startup" code in the bootloader */
    .romtext :
    {
        . = ALIGN(8);
        *(.text_rom)
        *(.text_rom*)
    } > FLASH

    __text_flash_start__ = LOADADDR(.text);
    .text :
    {
        . = ALIGN(8);
        __text_start__ = .;

        PROVIDE_HIDDEN (__init_array_start__ = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end__ = .);

        *(.text)
        *(.text*)

        *(.rodata)
        *(.rodata*)

        *(.init)
        *(.fini)
        . = ALIGN(8);
        __text_end__ = .;
    } >ROM_REGION AT>FLASH

    __data_flash_start__ = LOADADDR(.data);
    .data :
    {
        . = ALIGN(8);
        __data_start__ = .;
        *(.data)
        *(.data*)
        . = ALIGN(8);
        __data_end__ = .;
    } >RAM AT> FLASH

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } >RAM

    /DISCARD/ :
    {
        libgcc.a ( * )
        libc.a ( * )
        libm.a ( * )
        *(.ARM*)
    }
}

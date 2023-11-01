/* operating system entry point */

.global _start

.extern _gdt_load
.extern kernel_boot_stack_top

.type _start, @function
_start:
    /* disable interrupts */
    cli

    /* setup stack */
    mov $kernel_boot_stack_top, %esp 

    /* load gdt */
    call _gdt_load

    /* reload segments */
    call _reload_segments

    /* setup interrupts */
    call kernel_int_setup

._b_loop:
    jmp ._b_loop

    /* halt */
    hlt


.type _reload_segments, @function
_reload_segments:
    /* use a far jump to reload cs */
    jmp $0x08, $._reload

._reload:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ret

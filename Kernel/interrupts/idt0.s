.global kernel_idt_load

.type kernel_idt_load, @function
kernel_idt_load:
    /* mov descriptor pointer to eax */
    mov 4(%esp), %eax

    /* load idt */
    lidt (%eax)

    ret

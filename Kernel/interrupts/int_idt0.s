.global kernel_idt_load
.global kernel_int_enable
.global kernel_int_disable

.type kernel_idt_load, @function
kernel_idt_load:
    /* mov descriptor pointer to eax */
    mov 4(%esp), %eax

    /* load idt */
    lidt (%eax)

    ret

.type kernel_int_enable, @function
kernel_int_enable:
    sti
    ret

.type kernel_int_disable, @function
kernel_int_disable:
    cli
    ret

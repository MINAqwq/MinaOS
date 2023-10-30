.extern kernel_interrupt_handle

.global interrupt_buffer

.set KERNEL_IRQ_BASE, 0x20

// TODO Exceptions

.macro KERNEL_REG_IRQ int_num
.global kernel_interrupt_handle_\num\
kernel_interrupt_handle_\num\:
    movb $\num\ + $KERNEL_IRQ_BASE, interrupt_buffer
    jmp kernel_interrupt_forward
.endm

KERNEL_REG_IRQ 0x00
KERNEL_REG_IRQ 0x01

.data
interrupt_buffer:
    .byte 0

.text
kernel_interrupt_forward:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    push %esp
    push (interrupt_buffer)
    call kernel_interrupt_handle
    mov %eax, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

    iret

/* macro for register interrupts */

.global kernel_int_ignore

hallo:
.long 0

.macro KERNEL_INT_REG num
.global kernel_isr_forward_\num
kernel_isr_forward_\num:
    push $\num
    jmp kernel_isr_main
.endm

KERNEL_INT_REG 32
KERNEL_INT_REG 33

KERNEL_INT_REG 128


.type kernel_isr_main, @function
kernel_isr_main:
    /* push all general purpose register */
    pusha

    /* push data segment */
    xor %eax, %eax
    mov %ds, %ax
    push %eax

    /* switch to kernel data segment */
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    /* push pointer to stack to high level handler */
    push %esp
    call kernel_int_handle
    add $4, %esp

    /* restore old segment */
    pop %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa

    /* remove int number */
    add $4, %esp

kernel_int_ignore:
    iret
    

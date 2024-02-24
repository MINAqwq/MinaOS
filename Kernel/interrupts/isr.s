/* macro for register interrupts */

.global kernel_int_ignore

.macro KERNEL_INT_REG num
.global kernel_isr_forward_\num
kernel_isr_forward_\num:
    push $\num
    jmp kernel_isr_main
.endm

KERNEL_INT_REG 0
KERNEL_INT_REG 32
KERNEL_INT_REG 33
KERNEL_INT_REG 34
KERNEL_INT_REG 35
KERNEL_INT_REG 36
KERNEL_INT_REG 37
KERNEL_INT_REG 38
KERNEL_INT_REG 39
KERNEL_INT_REG 40
KERNEL_INT_REG 41
KERNEL_INT_REG 42
KERNEL_INT_REG 43
KERNEL_INT_REG 44
KERNEL_INT_REG 45
KERNEL_INT_REG 46
KERNEL_INT_REG 47

KERNEL_INT_REG 128

// TODO: only getting one ignored irq after sti ??? think i fucked up masking (lol)

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

.global kernel_ports_outb
.global kernel_ports_inb
.global kernel_ports_iowait

.type kernel_ports_outb, @function
kernel_ports_outb:
    mov 4(%esp), %al
    mov 8(%esp), %dx
    out %al, %dx
    ret

.type kernel_ports_inb, @function
kernel_ports_inb:
    mov 4(%esp), %dx
    xor %eax, %eax
    inb %dx, %al
    ret

.type kernel_ports_iowait, @function
kernel_ports_iowait:
    jmp .1
.1:
    jmp .2
.2:

    ret

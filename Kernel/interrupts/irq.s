.global kernel_int_enable
.global kernel_int_disable

.type kernel_int_enable, @function
kernel_int_enable:
    sti
    ret

.type kernel_int_disable, @function
kernel_int_disable:
    cli
    ret
